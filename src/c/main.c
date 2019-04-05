/*
 * Copyright (c) 2018
 * IoTech Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include "edgex/devsdk.h"

#include <unistd.h>
#include <signal.h>
#include "j1939_appl.h"

#define ERR_CHECK(x)                                        \
   if (x.code)                                              \
   {                                                        \
      fprintf(stderr, "Error: %d: %s\n", x.code, x.reason); \
      return x.code;                                        \
   }

typedef struct j1939_driver
{
   iot_logging_client *lc;
   pthread_mutex_t mutex;
} j1939_driver;

static sig_atomic_t running = true;
static void inthandler(int i)
{
   running = (i != SIGINT);
}

/* --- Initialize ---- */
static bool j1939_init(
    void *impl,
    struct iot_logging_client *lc,
    const edgex_nvpairs *config)
{
   char *pgnList = "";
   bool isApplControlInterface = false;
   bool retval = true;
   j1939_driver *driver = (j1939_driver *)impl;
   lc = iot_log_default;
   driver->lc = lc;

   //Read the driver parameters
   while (config != NULL)
   {
      if (strcmp(config->name, "ReceivePGNs") == 0)
         pgnList = config->value;
      if (strcmp(config->name, "ApplControlInterface") == 0)
      {
         if (strcmp(config->value, "true") == 0)
            isApplControlInterface = true;
         else if (strcmp(config->value, "false") == 0)
            isApplControlInterface = false;
         else
         {
            retval = false;
            iot_log_error(driver->lc, "Invalid value for ApplControlInterface in configuration file");
         }
      }
      config = config->next;
   }

   //start the J1939 application
   if ((retval == true) && (j1939_appl_init(isApplControlInterface, pgnList, driver->lc) != J1939_APPL_NO_ERROR))
   {
      retval = false;
   }
   else
   {
      pthread_mutex_init(&driver->mutex, NULL);
      iot_log_debug(driver->lc, "Init");
   }

   return retval;
}

/* ---- Discovery ---- */
static void j1939_discover(void *impl) {}

/* ---- Get ---- */
static bool j1939_get_handler(
    void *impl,
    const edgex_addressable *devaddr,
    uint32_t nreadings,
    const edgex_device_commandrequest *requests,
    edgex_device_commandresult *readings)
{
   j1939_driver *driver = (j1939_driver *)impl;

   /* Access the address of the device to be accessed and log it */
   iot_log_debug(driver->lc, "GET on address: %s", devaddr->address);

   for (uint32_t i = 0; i < nreadings; i++)
   {
      /* Drill into the attributes to differentiate between resources via the
   * SensorType NVP */
      edgex_nvpairs *current = requests->devobj->attributes;
      while (current != NULL)
      {
         current = current->next;
      }
   }
   return true;
}

/* ---- Put ---- */
static bool j1939_put_handler(
    void *impl,
    const edgex_addressable *devaddr,
    uint32_t nvalues,
    const edgex_device_commandrequest *requests,
    const edgex_device_commandresult *values)
{
   j1939_driver *driver = (j1939_driver *)impl;

   /* Access the address of the device to be accessed and log it */
   iot_log_debug(driver->lc, "PUT on address: %s", devaddr->address);
   return true;
}

/* ---- Disconnect ---- */
static bool j1939_disconnect(void *impl, edgex_addressable *device)
{
   return true;
}

/* ---- Stop ---- */
static void j1939_stop(void *impl, bool force)
{
   j1939_appl_stop();
}

static void usage(void)
{
   printf("Options: \n");
   printf("   -h, --help           : Show this text\n");
   printf("   -r, --registry       : Use the registry service\n");
   printf("   -p, --profile <name> : Set the profile name\n");
   printf("   -c, --confdir <dir>  : Set the configuration directory\n");
}

int main(int argc, char *argv[])
{
   bool useRegistry = false;
   char *profile = "";
   char *confdir = "";
   j1939_driver *impl = malloc(sizeof(j1939_driver));
   memset(impl, 0, sizeof(j1939_driver));

   int n = 1;
   while (n < argc)
   {
      if (strcmp(argv[n], "-h") == 0 || strcmp(argv[n], "--help") == 0)
      {
         usage();
         return 0;
      }
      if (strcmp(argv[n], "-r") == 0 || strcmp(argv[n], "--registry") == 0)
      {
         useRegistry = true;
         n++;
         continue;
      }
      if (strcmp(argv[n], "-p") == 0 || strcmp(argv[n], "--profile") == 0)
      {
         profile = argv[n + 1];
         n += 2;
         continue;
      }
      if (strcmp(argv[n], "-c") == 0 || strcmp(argv[n], "--confdir") == 0)
      {
         confdir = argv[n + 1];
         n += 2;
         continue;
      }
      printf("Unknown option %s\n", argv[n]);
      usage();
      return 0;
   }

   edgex_error e;
   e.code = 0;

   /* Device Callbacks */
   edgex_device_callbacks j1939Impls =
       {
           j1939_init,        /* Initialize */
           j1939_discover,    /* Discovery */
           j1939_get_handler, /* Get */
           j1939_put_handler, /* Put */
           j1939_disconnect,  /* Disconnect */
           j1939_stop         /* Stop */
       };

   /* Initalise a new device service */
   edgex_device_service *service = edgex_device_service_new(
       "device-j1939",
       "1.0",
       impl,
       j1939Impls,
       &e);
   ERR_CHECK(e);

   /* Start the device service*/
   edgex_device_service_start(service, useRegistry, NULL, 0, profile, confdir, &e);
   ERR_CHECK(e);

   signal(SIGINT, inthandler);
   running = true;
   while (running)
   {
      sleep(1);
   }

   /* Stop the device service */
   edgex_device_service_stop(service, true, &e);
   ERR_CHECK(e);

   free(impl);
   exit(0);
   return 0;
}
