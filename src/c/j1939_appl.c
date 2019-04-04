#include <stdio.h>
#include <unistd.h>
#include "j1939_appl.h"
#include "libsocketcan.h"

#define CAN_IFR "can0"
#define BITRATE 250000
#define MAX_NUM_PGNS 250

//Function Prototypes
static int ConfigureCan(const char *interface, uint32_t bitrate);
static int ShutdownCan(const char *interface);
void *readThread(void *arg);

//"SocketCan"
static char sBoardtype[16] = {0x53, 0x6f, 0x63, 0x6b, 0x65, 0x74, 0x43, 0x41, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

//"can0"
static char sBoardID[16] = {0x63, 0x61, 0x6e, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static bool isJ1939ApplRunning = false;
static bool j1939RecThreadShouldRun = false;
static bool isApplControlInterface = false;
static UINT8 j1939StackInst = 0;
static iot_logging_client *loggingClient;
static J1939API_J1939MSG received_msgs[MAX_NUM_PGNS];
static pthread_t thread_id;

/**
 * Creates J1939 stack instance and brings up
 * socketcan interface if application has control
 * of the interface.
 * @param bool isApplCtlIfr - true if application
 * should control the interface
 * @param iot_logging_client* lc - EdgeX logging
 * client to use for debug/error information
 * @return 0 upon success, non-zero upon error
 */
int j1939_appl_init(bool isInterfaceControl, iot_logging_client *lc)
{
   int retval = J1939_APPL_NO_ERROR;
   if (!isJ1939ApplRunning)
   {
      isJ1939ApplRunning = true;
      isApplControlInterface = isInterfaceControl;
      loggingClient = lc;

      memset(&received_msgs, 0, sizeof received_msgs);

      if (isApplControlInterface)
         retval = ConfigureCan(CAN_IFR, BITRATE);

      if (retval == J1939_APPL_NO_ERROR)
      {
         retval = J1939Api_CreateInstance(sBoardtype, sBoardID, J1939_FIRSTLINE, J1939ApiProtocol_J1939, BITRATE / 1000, &j1939StackInst);

         if (retval == J1939_APPL_NO_ERROR)
         {
            iot_log_debug(loggingClient, "J1939 stack instance created");
            j1939RecThreadShouldRun = true;
            pthread_create(&thread_id, NULL, readThread, &j1939RecThreadShouldRun);
         }
         else
         {
            isJ1939ApplRunning = false;
            ShutdownCan(CAN_IFR);
            iot_log_error(loggingClient, "J1939 stack creation failed. Return code: %d", retval);
         }
      }
      else
      {
         isJ1939ApplRunning = false;
         iot_log_error(loggingClient, "Application is not running due to previous CAN configuration error");
      }
   }
   else
   {
      iot_log_error(loggingClient, "J1939 application already initalized");
      retval = J1939_APPL_ERROR;
   }

   return retval;
}

/**
 * Destroys J1939 stack instance and shuts down
 * socketcan interface if application has control
 * of the interface.
 * @return 0 upon success, non-zero upon error
 */
int j1939_appl_stop(void)
{
   void *res;
   int retval = J1939_APPL_NO_ERROR;

   j1939RecThreadShouldRun = false;

   if (isApplControlInterface)
      retval = ShutdownCan(CAN_IFR);

   if (retval == J1939_APPL_NO_ERROR)
   {
      retval = J1939Api_DestroyInstance(j1939StackInst);
      if (retval != J1939_APPL_NO_ERROR)
      {
         iot_log_error(loggingClient, "J1939 stack could not be destroyed");
      }
      else
      {
         isJ1939ApplRunning = false;
         pthread_join(thread_id, &res);
         free(res);
      }
   }
   else
   {
      iot_log_error(loggingClient, "CAN interface could not be brought down");
   }

   return retval;
}

/**
 * Get the last message received for a given PGN
 * @param uint32_t pgn - PGN to be looked up
 * @param J1939API_J1939MSG **msg - pointer to pointer
 * to received J1939 message
 * @return 0 upon success, non-zero upon error
 */
int J1939_Get_Rec_Msg(uint32_t pgn, J1939API_J1939MSG **msg)
{
   for (int pgnIndex = 0; pgnIndex < MAX_NUM_PGNS; pgnIndex++)
   {
      if (received_msgs[pgnIndex].dwPgn == pgn)
      {
         *msg = &received_msgs[pgnIndex];
         return J1939_APPL_NO_ERROR;
      }
   }
   iot_log_warning(loggingClient, "Message for PGN %d not found", pgn);
   return J1939_APPL_ERROR;
}

/**
 * Thread to read data from the J1939 bus
 */
void *readThread(void *arg)
{
   bool *threadShouldRun = arg;
   while (*threadShouldRun)
   {
      J1939API_J1939MSG newmsg;
      int res = J1939Api_ReceiveMessage(j1939StackInst, (char *)&newmsg, sizeof(newmsg));
      if (res == J1939API_S_OK)
      {
         bool existingMsgFound = false;
         bool msgStored = false;

         //Check for an existing message for this PGN
         for (int pgnIndex = 0; pgnIndex < MAX_NUM_PGNS; pgnIndex++)
         {
            if (received_msgs[pgnIndex].dwPgn == newmsg.dwPgn)
            {
               received_msgs[pgnIndex] = newmsg;
               existingMsgFound = true;
               msgStored = true;
               break;
            }
         }

         //No previous message for this PGN was found
         if (!existingMsgFound)
         {
            for (int pgnIndex = 0; pgnIndex < MAX_NUM_PGNS; pgnIndex++)
            {
               //Find an empty index
               if (received_msgs[pgnIndex].dwPgn == 0)
               {
                  received_msgs[pgnIndex] = newmsg;
                  msgStored = true;
                  break;
               }
            }
         }

         if (!msgStored)
            iot_log_error(loggingClient, "Could not store message for PGN: %d", newmsg.dwPgn);
      }
      //No message was received, sleep the thread to reduce load
      else if (res == J1939API_E_MSG_RX_TIMEOUT)
      {
         usleep(10);
      }
   }
   return NULL;
}

/**
 * Configure and bring up the specifed CAN interface
 * @return 0 upon success, non-zero upon error
 */
static int ConfigureCan(const char *interface, uint32_t bitrate)
{
   int retval = J1939_APPL_NO_ERROR;

   if (can_do_stop(interface) == J1939_APPL_ERROR)
   {
      iot_log_error(loggingClient, "CAN interface could not be stopped");
      retval = J1939_APPL_ERROR;
   }

   if (can_set_bitrate(interface, bitrate) == J1939_APPL_ERROR)
   {
      iot_log_error(loggingClient, "CAN interface bitrate could not be set");
      retval = J1939_APPL_ERROR;
   }

   if (can_do_start(interface) == J1939_APPL_ERROR)
   {
      iot_log_error(loggingClient, "CAN interface could not be started");
      retval = J1939_APPL_ERROR;
   }

   if (retval == J1939_APPL_NO_ERROR)
   {
      iot_log_debug(loggingClient, "Can interface started");
   }

   return retval;
}

/**
 * Bring the specified CAN interface down
 * @return 0 upon success, non-zero upon error
 */
static int ShutdownCan(const char *interface)
{
   int retval = J1939_APPL_NO_ERROR;

   if (can_do_stop(interface) == J1939_APPL_ERROR)
   {
      iot_log_error(loggingClient, "CAN interface could not be stopped");
      retval = J1939_APPL_ERROR;
   }
   else
   {
      iot_log_debug(loggingClient, "CAN interface stopped");
   }

   return retval;
}