#include <stdint.h>
#include <stdbool.h>
#include "edgex/devsdk.h"

#define J1939_APPL_NO_ERROR 0
#define J1939_APPL_ERROR -1

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
int j1939_appl_init(bool isApplCtlIfr, iot_logging_client *lc);

/**
 * Destroys J1939 stack instance and shuts down
 * socketcan interface if application has control
 * of the interface.
 * @return 0 upon success, non-zero upon error
 */
int j1939_appl_stop(void);
