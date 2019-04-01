/*************************************************************************
**  HMS Networks AB
**************************************************************************
**
**        File: XatJ1939_err.h
**
**     Summary: Error defines for IXXAT J1939 API 2 (C, C++)
**
**    Compiler: Microsoft VS2010
**              GNU Compiler Collection 5.4.0
**
**************************************************************************
**  Copyright (C) 2009-2018 HMS Technology Center Ravensburg GmbH, all rights reserved
*************************************************************************/

#ifndef XATJ1939_ERR_H
#define XATJ1939_ERR_H


/** J1939_t_RESULT:
    Error codes (return values) of IXXAT J1939 API functions
    - Success has the return value code 0.
    - Actual errors have a negative value code.
    - Non-critical errors have a positive value code.
*/
enum J1939_t_RESULT
{
  J1939API_S_OK               =   0,        /*  Function succeeded */
  J1939API_S_NODATA,                        /*  No data available */
  J1939API_S_TIMEOUT,                       /*  Function timed out */
  J1939API_S_PENDING,                       /*  Function still pending */
  J1939API_S_PRESUMED_MSG,                  /*  J1939 message contains variable elements of unknown size */
  J1939API_S_ENCODING_OUT_OF_RANGE,         /*  Signal value is out of range acc.to data type, encoded value was cut */
  J1939API_E_POINTER          =  -1,        /*  Invalid pointer (null pointer) */
  J1939API_E_OUTOFMEMORY      =  -2,        /*  Memory allocation failed */
  J1939API_E_MEMSIZE          =  -3,        /*  Size of allocated memory insufficient */
  J1939API_E_NOINTERFACE      =  -4,        /*  Requested interface not supported */
  J1939API_E_INVALIDARG       =  -5,        /*  Invalid argument passed to function */
  J1939API_E_INVALIDHANDLE    =  -6,        /*  Invalid instance handle passed to function */
  J1939API_E_MAXINST          =  -7,        /*  Maximum allowed API instances exceeded */
  J1939API_E_MULTIINST        =  -8,        /*  Collision of multiple API instances */
  J1939API_E_NOTINITIALIZED   =  -9,        /*  Attempt to use an uninitialized API instance */
  J1939API_E_ADDRESSLOST      = -10,        /*  Communication instance forced to concede the address to another node on the J1939 network */
  J1939API_E_QUEUEFULL        = -11,        /*  Transmit message queue is full */
  J1939API_E_INVALIDCOMMAND   = -12,        /*  Invalid command ID (command is not supported) */
  J1939API_E_INVALIDPROTOCOL  = -13,        /*  Function or command not applicable to the active protocol */
  J1939API_E_MSG_TOO_LONG     = -15,        /*  Message too long */
  J1939API_E_MSG_TX_TIMEOUT   = -16,        /*  Message not sent in time */
  J1939API_E_MSG_RX_TIMEOUT   = -17,        /*  Message not received in time */
  J1939API_E_DRV_INIT         = -21,        /*  Initialization of CAN driver failed */
  J1939API_E_DRV_GETBOARDS    = -22,        /*  Retrieval of current board list from CAN driver failed */
  J1939API_E_DRV_BOARDSELECT  = -23,        /*  Selection of CAN board failed */
  J1939API_E_DRV_BOARD        = -24,        /*  Invalid board */
  J1939API_E_DRV_CANCHAN      = -25,        /*  Invalid CAN channel/line */
  J1939API_E_STK_INIT         = -31,        /*  Initialization of J1939 stack failed. _
                                                For SocketCAN, make sure that the CAN board is configured as _
                                                sudo ip link set can0 type can bitrate 250000 */
  J1939API_E_STK_START        = -32,        /*  Starting of J1939 stack failed. _
                                                For SocketCAN, make sure that the CAN controller is up and running as _
                                                sudo ip link set can0 up */
  J1939API_E_STK_THREADINIT   = -33,        /*  Initialization of J1939 thread failed */
  J1939API_E_STK_TX_FAIL      = -34,        /*  Transmission of J1939 message failed */
  J1939API_E_STK_TX_NOTACTIVE = -35,        /*  Tried to send a message while device is inactive */
  J1939API_E_STK_REG_FAIL     = -36,        /*  Registration of a message failed */
  J1939API_E_STK_REG_MAX      = -37,        /*  Maximum allowed message registrations has been exceeded */
  J1939API_E_API_RX_OVRN      = -41,        /*  Overrun in the API reception queue */
  J1939API_E_FS_OPEN          = -61,        /*  Error opening the file that contains the J1939 message definitions */
  J1939API_E_FS_IMPORT        = -62,        /*  Error importing the J1939 messages from the given file */
  J1939API_E_TREE_GETROOT     = -71,        /*  Retrieval of J1939 message definitions tree node failed */
  J1939API_E_TREE_GETPGNODE   = -72,        /*  Retrieval of J1939 message definitions PG node failed */
  J1939API_E_TREE_GETSPLIST   = -73,        /*  Retrieval of J1939 message definitions SP list failed */
  J1939API_E_TREE_GETSPNODE   = -74,        /*  Retrieval of J1939 message definitions SP node failed */
  J1939API_E_TREE_GETNODEDATA = -75,        /*  Retrieval of J1939 message definitions node data failed */
  J1939API_E_TREE_SPNTYPE     = -76,        /*  Unsuitable J1939 SPN type */
  J1939API_E_ENCODING         = -81,        /*  Encoding of the signal to J1939 message failed */
  J1939API_E_DECODING         = -82         /*  Decoding of the signal from J1939 message failed */
};


/** Errors originating from J1939 stack
    - Available via {J1939Api_ReceiveError()}
    - Consisting of Error Class; Error Identifier; Error Number
*/
#define ERR_BUILD_ERROR_CODE(errclass,errid,errnum)                       \
                                ((UINT16)((errclass) << 13) | ((errid) << 8) | (errnum))

/** Error Classes:
** The errors are allocated to the three following classes.
** +---------+------------------------------------------------------------+
** |Class    |Description                                                 |
** +---------+------------------------------------------------------------+
** |Warning  |A function (in the sense of a task) can not be performed,   |
** |         |as a prerequisite or an external condition is not           |
** |         |fulfilled. It is possible, that the function can not        |
** |         |be executed currently but can be repeated later.            |
** |         |This type of error can be ignored in a running              |
** |         |system or is handled by the application.                    |
** |         |Statistical analysis or recording of the errors may be      |
** |         |useful.                                                     |
** |         |Examples of these errors are: _                             |
** |         |- CAN controller in warning level _                         |
** |         |- transmit queue full _                                     |
** |         |- communication aborted by the remote station               |
** +---------+------------------------------------------------------------+
** |Error    |An error occurred in the system that does not inhibit       |
** |         |continuous operation but that can not be ignored.           |
** |         |These are often errors caused by overload or incorrect input|
** |         |data. The error can lead to subsequent errors. Depending on |
** |         |the application, the system must be set to an error state or|
** |         |shut down completely. Continued operation of the system in  |
** |         |test or debug mode may be advisable. _                      |
** |         |Examples of these errors are: _                             |
** |         |- data overrun in the receive queue  _                      |
** |         |- protocol aborts due to temporary memory problems _        |
** |         |- timeouts of real-time tasks                               |
** +---------+------------------------------------------------------------+
** |Fatal    |A fatal error occurred in the system. Fatal errors inhibit  |
** |         |further software operation in most cases. Depending on the  |
** |         |application, the system must be shut down completely or     |
** |         |rebooted. _                                                 |
** |         |Examples of these errors are: _                             |
** |         |- stack overrun _                                           |
** |         |- CAN controller in bus off _                               |
** |         |- no more free memory available _                           |
** |         |- error in memory monitoring or HW monitoring _             |
** |         |- invalid system states                                     |
** +---------+------------------------------------------------------------+
** _
*/
#define ERR_CLASS_MASK   0x6000u     /* mask of the error classes    */
#define ERR_WARNING           0u     /* error warning occurred     */
#define ERR_ERROR             1u     /* error occurred             */
#define ERR_FATAL             2u     /* fatal error occurred       */

/** Error Identifiers:
** The error identifiers of the several units use the error unit.
** It is also possible to use the error unit for application errors.
** Therefore the error identifier of the application has to be added.
*/
#define ERR_ID_MASK  0x1F00u        /* mask of the error identifiers  */
#define ERR_ERR_ID        0u        /* error unit identifier          */
#define DLL_ERR_ID        1u        /* data link layer identifier     */
#define MEM_ERR_ID        2u        /* memory unit identifier         */
#define TPL_ERR_ID        3u        /* transport protocol identifier  */
#define NWM_ERR_ID        4u        /* network management identifier  */
#define APL_ERR_ID        5u        /* application layer identifier   */
#define CYC_ERR_ID        6u        /* cycle unit identifier          */
#define REQ_ERR_ID        7u        /* request unit identifier        */
#define L2C_ERR_ID        8u        /* layer 2 unit identifier        */
#define ADR_ERR_ID        9u        /* addressing unit identifier     */
#define NMEA_ERR_ID      10u        /* NMEA 2000 module               */
#define CDP_ERR_ID       11u        /* CAN Diagnostic Protocol        */
#define DIAG_ERR_ID      12u        /* J1939 Diagnostic Module        */
#define USR_ERR_ID       13u        /* user specific code (generated) */
#define SPN_ERR_ID       14u        /* SPN extension module           */


/** APL_ERR_TIME_EXCEEDED:
    APL_Main() not called in the required sequence.
*/
#define APL_ERR_TIME_EXCEEDED   ERR_BUILD_ERROR_CODE(ERR_ERROR, APL_ERR_ID, 1)

/** APL_ERR_TX_LONG:
    Data field of the transmit message is too long.
*/
#define APL_ERR_TX_LONG         ERR_BUILD_ERROR_CODE(ERR_FATAL, APL_ERR_ID, 2)

/** APL_ERR_NO_MEMORY:
    No memory for the data field of the transmit message allocated.
*/
#define APL_ERR_NO_MEMORY       ERR_BUILD_ERROR_CODE(ERR_ERROR, APL_ERR_ID, 3)

/** APL_ERR_REG_REQUEST:
    Error occurred during registration of a request PGN.
*/
#define APL_ERR_REG_REQUEST     ERR_BUILD_ERROR_CODE(ERR_ERROR, APL_ERR_ID, 4)

/** APL_ERR_TX_NO_ADDR:
    Device has no address claimed.
*/
#define APL_ERR_TX_NO_ADDR      ERR_BUILD_ERROR_CODE(ERR_ERROR, APL_ERR_ID, 5)

/** APL_ERR_INVALID_PARAM:
    Invalid parameter passed to a stack function.
*/
#define APL_ERR_INVALID_PARAM   ERR_BUILD_ERROR_CODE(ERR_WARNING, APL_ERR_ID, 6)

/** APL_ERR_REQ_RESPONSE:
    Request message not answered by the request handler due to a queue overrun.
*/
#define APL_ERR_REQ_RESPONSE    ERR_BUILD_ERROR_CODE(ERR_WARNING, APL_ERR_ID, 11)

/** CYC_ERR_NOT_INITIALIZED:
    Unit is not initialized.
*/
#define CYC_ERR_NOT_INITIALIZED  ERR_BUILD_ERROR_CODE(ERR_FATAL, CYC_ERR_ID, 1)

/** CYC_ERR_RX_REGISTRATION:
    Maximal number of receive messages is exceeded.
*/
#define CYC_ERR_RX_REGISTRATION  ERR_BUILD_ERROR_CODE(ERR_FATAL, CYC_ERR_ID, 2)

/** CYC_ERR_TX_REGISTRATION:
    Maximal number of transmit messages is exceeded.
*/
#define CYC_ERR_TX_REGISTRATION  ERR_BUILD_ERROR_CODE(ERR_FATAL, CYC_ERR_ID, 3)

/** CYC_ERR_TIME_EXCEEDED:
    CYC_Main() not called in the required sequence.
*/
#define CYC_ERR_TIME_EXCEEDED   ERR_BUILD_ERROR_CODE(ERR_ERROR, CYC_ERR_ID, 4)

/** CYC_ERR_RX_TIMEOUT:
    A registered message is not received in the given time.
*/
#define CYC_ERR_RX_TIMEOUT      ERR_BUILD_ERROR_CODE(ERR_ERROR, CYC_ERR_ID, 11)

/** CYC_ERR_TX_QUEUE_OVRN:
    A message is not sent due to an overrun of the transmit queue.
*/
#define CYC_ERR_TX_QUEUE_OVRN   ERR_BUILD_ERROR_CODE(ERR_WARNING, CYC_ERR_ID, 12)

/** CYC_ERR_RX_INVALID_LENGTH:
    Received message is too long for the receive buffer.
*/
#define CYC_ERR_RX_INVALID_LENGTH  ERR_BUILD_ERROR_CODE(ERR_ERROR, CYC_ERR_ID, 13)

/** NWM_ERR_LOOSE_ADDR:
    During address protection the claimed address had to give up.
*/
#define NWM_ERR_LOOSE_ADDR      ERR_BUILD_ERROR_CODE(ERR_ERROR, NWM_ERR_ID, 11)

/** TPL_ERR_TX_OVRN:
    No free entry in the TxQueue of the TPL available.
*/
#define TPL_ERR_TX_OVRN         ERR_BUILD_ERROR_CODE(ERR_WARNING, TPL_ERR_ID, 1)

/** TPL_ERR_CONF_FILTER:
    Too many PGNs tried to register in the config filter.
*/
#define TPL_ERR_CONF_FILTER     ERR_BUILD_ERROR_CODE(ERR_FATAL, TPL_ERR_ID, 2)

/** TPL_ERR_UNEXP_BAM_FRM:
    Unexpected BAM frame received.
*/
#define TPL_ERR_UNEXP_BAM_FRM   ERR_BUILD_ERROR_CODE(ERR_WARNING, TPL_ERR_ID,11)

/** TPL_ERR_UNEXP_RTS_FRM:
    Unexpected RTS frame received.
*/
#define TPL_ERR_UNEXP_RTS_FRM   ERR_BUILD_ERROR_CODE(ERR_WARNING, TPL_ERR_ID,12)

/** TPL_ERR_UNEXP_CTS_FRM:
    Unexpected CTS frame received.
*/
#define TPL_ERR_UNEXP_CTS_FRM   ERR_BUILD_ERROR_CODE(ERR_WARNING, TPL_ERR_ID,13)

/** TPL_ERR_UNEXP_EOM_FRM:
    Unexpected EOM frame received.
*/
#define TPL_ERR_UNEXP_EOM_FRM   ERR_BUILD_ERROR_CODE(ERR_WARNING, TPL_ERR_ID,14)

/** TPL_ERR_UNEXP_CA_FRM:
    Unexpected CA frame received.
*/
#define TPL_ERR_UNEXP_CA_FRM    ERR_BUILD_ERROR_CODE(ERR_WARNING, TPL_ERR_ID,15)

/** TPL_ERR_UNEXP_DT_FRM:
    Unexpected DT frame received.
*/
#define TPL_ERR_UNEXP_DT_FRM    ERR_BUILD_ERROR_CODE(ERR_WARNING, TPL_ERR_ID,16)

/** TPL_ERR_RX_OVRN:
    No free Rx Msg buffer in the TPL for a global message available.
*/
#define TPL_ERR_RX_OVRN         ERR_BUILD_ERROR_CODE(ERR_ERROR  , TPL_ERR_ID,17)

/** TPL_ERR_TX_TIMEOUT0:
    Transmit timeout T0 occurred.
*/
#define TPL_ERR_TX_TIMEOUT0     ERR_BUILD_ERROR_CODE(ERR_WARNING, TPL_ERR_ID,18)

/** TPL_ERR_TX_TIMEOUT2:
    Transmit timeout T2 occurred.
*/
#define TPL_ERR_TX_TIMEOUT2     ERR_BUILD_ERROR_CODE(ERR_WARNING, TPL_ERR_ID,19)

/** TPL_ERR_RX_TIMEOUT0:
    Receive timeout T0 occurred.
*/
#define TPL_ERR_RX_TIMEOUT0     ERR_BUILD_ERROR_CODE(ERR_ERROR  , TPL_ERR_ID,20)

/** TPL_ERR_RX_TIMEOUT1:
    Receive timeout T1 occurred.
*/
#define TPL_ERR_RX_TIMEOUT1     ERR_BUILD_ERROR_CODE(ERR_ERROR  , TPL_ERR_ID,21)

/** TPL_ERR_RX_TIMEOUT2:
    Receive timeout T2 occurred.
*/
#define TPL_ERR_RX_TIMEOUT2     ERR_BUILD_ERROR_CODE(ERR_ERROR  , TPL_ERR_ID,22)

/** TPL_ERR_RX_LONG:
    Received message is too long for a segmented message.
*/
#define TPL_ERR_RX_LONG         ERR_BUILD_ERROR_CODE(ERR_FATAL  , TPL_ERR_ID,23)

/** TPL_ERR_SEND_MSG:
    Error by sending: Can not send a segmented message.
*/
#define TPL_ERR_SEND_MSG        ERR_BUILD_ERROR_CODE(ERR_ERROR  , TPL_ERR_ID,24)

/** TPL_ERR_SEND_CA:
    Sending a CA message failed.
*/
#define TPL_ERR_SEND_CA         ERR_BUILD_ERROR_CODE(ERR_ERROR  , TPL_ERR_ID,25)

/** TPL_ERR_SEND_NACK:
    Sending a NACK message failed.
*/
#define TPL_ERR_SEND_NACK       ERR_BUILD_ERROR_CODE(ERR_ERROR  , TPL_ERR_ID,26)

/** DLL_ERR_TX_OVRN:
    Overrun in the transmit queue occurred.
*/
#define DLL_ERR_TX_OVRN         ERR_BUILD_ERROR_CODE(ERR_WARNING, DLL_ERR_ID, 1)

/** DLL_ERR_START_CAN:
    Start of CAN controller failed.
*/
#define DLL_ERR_START_CAN       ERR_BUILD_ERROR_CODE(ERR_FATAL  , DLL_ERR_ID, 2)

/** DLL_ERR_RESET_CAN:
    Reset of CAN controller failed.
*/
#define DLL_ERR_RESET_CAN       ERR_BUILD_ERROR_CODE(ERR_FATAL  , DLL_ERR_ID, 3)

/** DLL_ERR_INIT_CAN:
    Initialization of CAN controller failed.
*/
#define DLL_ERR_INIT_CAN        ERR_BUILD_ERROR_CODE(ERR_FATAL  , DLL_ERR_ID, 4)

/** DLL_ERR_BOFF:
    Bus off interrupt occurred on CAN.
*/
#define DLL_ERR_BOFF            ERR_BUILD_ERROR_CODE(ERR_FATAL, DLL_ERR_ID, 11)

/** DLL_ERR_EPAS:
    CAN controller status changed to error passive.
*/
#define DLL_ERR_EPAS            ERR_BUILD_ERROR_CODE(ERR_WARNING, DLL_ERR_ID, 12)

/** DLL_ERR_EACT:
    CAN controller status changed to error active.
*/
#define DLL_ERR_EACT            ERR_BUILD_ERROR_CODE(ERR_WARNING, DLL_ERR_ID, 13)

/** DLL_ERR_DOI:
    Data overrun interrupt occurred on CAN.
*/
#define DLL_ERR_DOI             ERR_BUILD_ERROR_CODE(ERR_ERROR, DLL_ERR_ID, 14)

/** DLL_ERR_RX_OVRN:
    Overrun in the receive queue occurred.
*/
#define DLL_ERR_RX_OVRN         ERR_BUILD_ERROR_CODE(ERR_ERROR, DLL_ERR_ID, 15)

/** MEM_ERR_ALLOC_MEMORY:
    Allocate memory failed.
*/
#define MEM_ERR_ALLOC_MEMORY    ERR_BUILD_ERROR_CODE(ERR_FATAL, MEM_ERR_ID, 11)

/** MEM_ERR_FREE_MEMORY:
    Free memory failed.
*/
#define MEM_ERR_FREE_MEMORY     ERR_BUILD_ERROR_CODE(ERR_WARNING, MEM_ERR_ID, 12)

/** ERR_ERR_INVALID_PARAM:
    Invalid parameter passed to a stack function.
*/
#define ERR_ERR_INVALID_PARAM   ERR_BUILD_ERROR_CODE(ERR_WARNING , ERR_ERR_ID, 1)

/** REQ_ERR_INVALID_PARAM:
    Invalid parameter passed to a stack function.
*/
#define REQ_ERR_INVALID_PARAM   ERR_BUILD_ERROR_CODE(ERR_WARNING , REQ_ERR_ID, 1)

/** DIAG_ERR_MEM_ABORTED_TX:
    Memory access session aborted due to a transmit problem (sending a memory access message failed).
*/
#define DIAG_ERR_MEM_ABORTED_TX  ERR_BUILD_ERROR_CODE(ERR_ERROR, DIAG_ERR_ID, 11)

/** DIAG_ERR_MEM_ABORTED_RX:
    Memory access session aborted due to a receive problem (memory access message not received in the expected time).
*/
#define DIAG_ERR_MEM_ABORTED_RX  ERR_BUILD_ERROR_CODE(ERR_ERROR, DIAG_ERR_ID, 12)

/** DIAG_ERR_MEM_ABORTED_KEY:
    Memory access session aborted due to security reasons (invalid key received).
*/
#define DIAG_ERR_MEM_ABORTED_KEY  ERR_BUILD_ERROR_CODE(ERR_WARNING, DIAG_ERR_ID, 13)

/** DIAG_ERR_MEM_ABORTED_DATA:
    Memory access session aborted due to addressing problems (invalid data length received).
*/
#define DIAG_ERR_MEM_ABORTED_DATA  ERR_BUILD_ERROR_CODE(ERR_WARNING, DIAG_ERR_ID, 14)

/** DIAG_ERR_MEM_BUSY:
    Memory access session declined because the device is busy (another session in process).
*/
#define DIAG_ERR_MEM_BUSY       ERR_BUILD_ERROR_CODE(ERR_WARNING, DIAG_ERR_ID, 15)

/** DIAG_ERR_MEM_BUSY_FAILED:
    Transmit a memory access response 'busy' failed.
*/
#define DIAG_ERR_MEM_BUSY_FAILED  ERR_BUILD_ERROR_CODE(ERR_WARNING, DIAG_ERR_ID, 16)

/** DIAG_ERR_MEM_INVALID_MSG:
    Invalid message received (received PGN is not registered for the diagnostic unit).
*/
#define DIAG_ERR_MEM_INVALID_MSG  ERR_BUILD_ERROR_CODE(ERR_ERROR, DIAG_ERR_ID, 17)

/** DIAG_ERR_MEM_INVALID_LENGTH:
    Invalid data length of a memory access message.
*/
#define DIAG_ERR_MEM_INVALID_LENGTH  ERR_BUILD_ERROR_CODE(ERR_WARNING, DIAG_ERR_ID, 18)

/** CDP_ERR_TIME_EXCEEDED:
    CDP_Main() not called in the required sequence.
*/
#define CDP_ERR_TIME_EXCEEDED   ERR_BUILD_ERROR_CODE(ERR_ERROR, CDP_ERR_ID, 1)

/** CDP_ERR_ADDR_FORMAT:
    Addressing format of the CAN diagnostic protocol is invalid.
*/
#define CDP_ERR_ADDR_FORMAT     ERR_BUILD_ERROR_CODE(ERR_ERROR, CDP_ERR_ID, 2)

/** CDP_ERR_CONF_PGN:
    No free PGN entry to register a CDP message.
*/
#define CDP_ERR_CONF_PGN        ERR_BUILD_ERROR_CODE(ERR_ERROR, CDP_ERR_ID, 3)

/** CDP_ERR_UNKNOWN_PGN:
    PGN is not registered.
*/
#define CDP_ERR_UNKNOWN_PGN     ERR_BUILD_ERROR_CODE(ERR_ERROR, CDP_ERR_ID, 4)

/** CDP_ERR_STATE_READY_TX:
    PGN is not ready for transmitting a CAN diagnostic message.
*/
#define CDP_ERR_STATE_READY_TX  ERR_BUILD_ERROR_CODE(ERR_WARNING, CDP_ERR_ID, 5)

/** CDP_ERR_NO_MEMORY:
    No memory for the data field allocated.
*/
#define CDP_ERR_NO_MEMORY       ERR_BUILD_ERROR_CODE(ERR_ERROR, CDP_ERR_ID, 6)

/** CDP_ERR_ALLOC_MEMORY:
    Allocate memory failed.
*/
#define CDP_ERR_ALLOC_MEMORY    ERR_BUILD_ERROR_CODE(ERR_ERROR, CDP_ERR_ID, 11)

/** CDP_ERR_FREE_MEMORY:
    Free memory failed.
*/
#define CDP_ERR_FREE_MEMORY     ERR_BUILD_ERROR_CODE(ERR_ERROR, CDP_ERR_ID, 12)

/** CDP_ERR_RX_LENGTH:
    Received CAN diagnostic protocol message is too long for the available receive buffer.
*/
#define CDP_ERR_RX_LENGTH       ERR_BUILD_ERROR_CODE(ERR_ERROR, CDP_ERR_ID, 13)

/** CDP_ERR_RX_TIMEOUT_FC:
    CAN diagnostic protocol flow control message is not received in time.
*/
#define CDP_ERR_RX_TIMEOUT_FC   ERR_BUILD_ERROR_CODE(ERR_ERROR, CDP_ERR_ID, 14)

/** CDP_ERR_RX_TIMEOUT_CF:
    CAN diagnostic protocol consecutive frame message is not received in time.
*/
#define CDP_ERR_RX_TIMEOUT_CF   ERR_BUILD_ERROR_CODE(ERR_ERROR, CDP_ERR_ID, 15)

/** CDP_ERR_TX_TIMEOUT:
    CAN diagnostic protocol message is not sent in time.
*/
#define CDP_ERR_TX_TIMEOUT      ERR_BUILD_ERROR_CODE(ERR_ERROR, CDP_ERR_ID, 16)

/** CDP_ERR_PCI_INVALID:
    CAN diagnostic protocol control information is invalid.
*/
#define CDP_ERR_PCI_INVALID     ERR_BUILD_ERROR_CODE(ERR_ERROR, CDP_ERR_ID, 17)

/** CDP_ERR_STATE_READY_RX:
    PGN is not ready for receiving a CAN diagnostic message.
*/
#define CDP_ERR_STATE_READY_RX  ERR_BUILD_ERROR_CODE(ERR_ERROR, CDP_ERR_ID, 18)

/** NMEA_ERR_TIME_EXCEEDED:
    NMEA_Main() is not called in the required sequence.
*/
#define NMEA_ERR_TIME_EXCEEDED  ERR_BUILD_ERROR_CODE(ERR_ERROR, NMEA_ERR_ID, 1)

/** NMEA_ERR_TX_LONG:
    Sending of a fast-packet protocol message failed, because the message is too long (CNF_TPL_MAX_MSG_LENGTH has to be increased).
*/
#define NMEA_ERR_TX_LONG        ERR_BUILD_ERROR_CODE(ERR_ERROR, NMEA_ERR_ID, 2)

/** NMEA_ERR_TX_NO_BUF:
    No free transmit buffer for the fast-packet protocol available.
*/
#define NMEA_ERR_TX_NO_BUF      ERR_BUILD_ERROR_CODE(ERR_ERROR, NMEA_ERR_ID, 3)

/** NMEA_ERR_INVALID_HDL:
    Maximum number of handle registrations is exceeded.
*/
#define NMEA_ERR_INVALID_HDL    ERR_BUILD_ERROR_CODE(ERR_ERROR, NMEA_ERR_ID, 4)

/** NMEA_ERR_INVALID_DATA:
    Sending a fast-packet protocol message failed, because an invalid data pointer is used (NULL pointer).
*/
#define NMEA_ERR_INVALID_DATA   ERR_BUILD_ERROR_CODE(ERR_ERROR, NMEA_ERR_ID, 5)

/** NMEA_ERR_INVALID_MSG:
    Sending a fast-packet protocol message failed, because an invalid message pointer is used (NULL pointer).
*/
#define NMEA_ERR_INVALID_MSG    ERR_BUILD_ERROR_CODE(ERR_ERROR, NMEA_ERR_ID, 6)

/** NMEA_ERR_INVALID_CLBK:
    Initialization of the NMEA module failed, because an invalid receive callback pointer is used (NULL pointer).
*/
#define NMEA_ERR_INVALID_CLBK   ERR_BUILD_ERROR_CODE(ERR_FATAL, NMEA_ERR_ID, 7)

/** NMEA_ERR_INVALID_ADDR:
    Invalid target address is used (broadcast is not allowed).
*/
#define NMEA_ERR_INVALID_ADDR   ERR_BUILD_ERROR_CODE(ERR_ERROR, NMEA_ERR_ID, 8)

/** NMEA_ERR_INVALID_PGN:
    Maximum number of message registrations is exceeded.
*/
#define NMEA_ERR_INVALID_PGN    ERR_BUILD_ERROR_CODE(ERR_ERROR, NMEA_ERR_ID, 9)

/** NMEA_ERR_RX_NO_BUF:
    Reception of fast-packet protocol message failed, because no free receive buffer is available.
*/
#define NMEA_ERR_RX_NO_BUF      ERR_BUILD_ERROR_CODE(ERR_ERROR, NMEA_ERR_ID, 11)

/** NMEA_ERR_RX_NOT_REG:
    An unregistered message is received.
*/
#define NMEA_ERR_RX_NOT_REG     ERR_BUILD_ERROR_CODE(ERR_WARNING, NMEA_ERR_ID, 12)

/** NMEA_ERR_RX_TIMEOUT:
    Reception of fast-packet protocol message failed, because a timeout occurred.
*/
#define NMEA_ERR_RX_TIMEOUT     ERR_BUILD_ERROR_CODE(ERR_ERROR, NMEA_ERR_ID, 13)

/** NMEA_ERR_TX_FAILED:
    Transmission of fast-packet protocol message failed, because an overrun in the transmit queue occurred.
*/
#define NMEA_ERR_TX_FAILED      ERR_BUILD_ERROR_CODE(ERR_ERROR, NMEA_ERR_ID, 14)

/** NMEA_ERR_OVR_TRANSFER:
    Reception of fast-packet protocol message failed, because a transfer overrun occurred.
*/
#define NMEA_ERR_OVR_TRANSFER   ERR_BUILD_ERROR_CODE(ERR_ERROR, NMEA_ERR_ID, 15)

/** NMEA_ERR_WRONG_FRAME:
    An invalid fast-packet protocol frame is received during the reception of a fast-packet protocol message.
*/
#define NMEA_ERR_WRONG_FRAME    ERR_BUILD_ERROR_CODE(ERR_WARNING, NMEA_ERR_ID, 16)

/** NMEA_ERR_RX_LONG:
    Reception of fast-packet protocol message failed, because the data field is too long (CNF_TPL_MAX_MSG_LENGTH has to be increased).
*/
#define NMEA_ERR_RX_LONG        ERR_BUILD_ERROR_CODE(ERR_ERROR, NMEA_ERR_ID, 17)

/** NMEA_ERR_ACK_RECEIVED:
    Request of a standard NMEA 2000 message is answered with a NACK.
*/
#define NMEA_ERR_ACK_RECEIVED   ERR_BUILD_ERROR_CODE(ERR_WARNING, NMEA_ERR_ID, 18)


#endif
