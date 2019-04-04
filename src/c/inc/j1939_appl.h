#include <stdint.h>
#include <stdbool.h>
#include "edgex/devsdk.h"
#include "XatJ1939.h"
#include "XatJ1939_err.h"
#include "XatJ1939_types.h"

#define J1939_APPL_NO_ERROR 0
#define J1939_APPL_ERROR -1

/**
 * Creates J1939 stack instance and brings up
 * socketcan interface if application has control
 * of the interface.
 * @param bool isApplCtlIfr - true if application
 * should control the interface
 * @param char* pgns - string of comma separated
 * pgns that should be added to the inclusive filter
 * @param iot_logging_client* lc - EdgeX logging
 * client to use for debug/error information
 * @return 0 upon success, non-zero upon error
 */
int j1939_appl_init(bool isApplCtlIfr, char *pgns, iot_logging_client *lc);

/**
 * Destroys J1939 stack instance and shuts down
 * socketcan interface if application has control
 * of the interface.
 * @return 0 upon success, non-zero upon error
 */
int j1939_appl_stop(void);

/**
 * Get the last message received for a given PGN
 * @param uint32_t pgn - PGN to be looked up
 * @param J1939API_J1939MSG **msg - pointer to pointer
 * to received J1939 message
 * @return 0 upon success, non-zero upon error
 */
int J1939_Get_Rec_Msg(uint32_t pgn, J1939API_J1939MSG **msg);