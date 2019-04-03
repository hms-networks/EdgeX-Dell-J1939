#include <stdio.h>
#include "j1939_appl.h"
#include "XatJ1939.h"
#include "XatJ1939_err.h"
#include "XatJ1939_types.h"
#include "libsocketcan.h"

#define CAN_IFR "can0"
#define BITRATE 250000

//Function Prototypes
static int ConfigureCan(const char *interface, uint32_t bitrate);
static int ShutdownCan(const char *interface);

//"SocketCan"
static char sBoardtype[16] = {0x53, 0x6f, 0x63, 0x6b, 0x65, 0x74, 0x43, 0x41, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

//"can0"
static char sBoardID[16] = {0x63, 0x61, 0x6e, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static bool isJ1939ApplRunning = false;
static bool isApplControlInterface = false;
static UINT8 j1939StackInst = 0;
static iot_logging_client *loggingClient;

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

      if (isApplControlInterface)
         retval = ConfigureCan(CAN_IFR, BITRATE);

      if (retval == J1939_APPL_NO_ERROR)
      {
         retval = J1939Api_CreateInstance(sBoardtype, sBoardID, J1939_FIRSTLINE, J1939ApiProtocol_J1939, BITRATE / 1000, &j1939StackInst);

         if (retval == J1939_APPL_NO_ERROR)
         {
            iot_log_debug(loggingClient, "J1939 stack instance created");
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
   int retval = J1939_APPL_NO_ERROR;

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
      }
   }
   else
   {
      iot_log_error(loggingClient, "CAN interface could not be brought down");
   }

   return retval;
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