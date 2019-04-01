/*************************************************************************
**  HMS Networks AB
**************************************************************************
**
**        File: XatJ1939.h
**
**     Summary: IXXAT J1939 API
**              The J1939 API software v2.0 provides a programming interface
**              for the development of J1939 applications on Windows PCs and 
**              on Linux PCs in C and in C++, based on the IXXAT VCI driver 
**              for Windows and for Linux on the SocketCAN driver.
**
**    Compiler: Microsoft VS2010
**              GNU Compiler Collection 5.4.0
**
**************************************************************************
**  Copyright (C) 2009-2018 HMS Technology Center Ravensburg GmbH, all rights reserved
*************************************************************************/

#ifndef XATJ1939_H
#define XATJ1939_H

#ifndef CHAR
  typedef char CHAR;
#endif
#ifndef UINT8
  typedef unsigned char UINT8;
#endif
#ifndef UINT16
  typedef unsigned short UINT16;
#endif
#ifndef UINT32
  typedef unsigned int UINT32;
#endif
#ifndef INT32
  typedef signed int INT32;
#endif
#ifndef _WCHAR_H
  #include "wchar.h"
#endif


/*
** Definition of calling attributes (CALLATTR)
*/
#if defined(_WIN32) || defined(__WIN32__)
  #define CALLATTR   WINAPI
#elif defined(__GNUC__)
  #if defined(__i386__)
    #define CALLATTR __attribute__ ((stdcall))
    #define CALLBACK __attribute__ ((stdcall))
  #else
    #define CALLATTR
    #define CALLBACK
  #endif
#else
  #define CALLATTR   far PASCAL _export _loadds
  #define CALLBACK
#endif


/*************************************************************************
**    Constants for J1939_CreateInstance()
*************************************************************************/
static char const J1939_DEFAULTBOARD[16]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static char const J1939_BOARDDIALOG[16] = {0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F};
static char const J1939_1stBOARD[16]    = {0, 0, 0, 0, 0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F};
static char const J1939_2ndBOARD[16]    = {1, 0, 0, 0, 0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F};
static char const J1939_3rdBOARD[16]    = {2, 0, 0, 0, 0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F};
static char const J1939_4thBOARD[16]    = {3, 0, 0, 0, 0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F};
static char const J1939_5thBOARD[16]    = {4, 0, 0, 0, 0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F};
static char const J1939_6thBOARD[16]    = {5, 0, 0, 0, 0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F};
static char const J1939_7thBOARD[16]    = {6, 0, 0, 0, 0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F};
static char const J1939_8thBOARD[16]    = {7, 0, 0, 0, 0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F};
static char const J1939_9thBOARD[16]    = {8, 0, 0, 0, 0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F};

#define J1939_FIRSTLINE         0x00
#define J1939_SECONDLINE        0x01
#define J1939_THIRDLINE         0x02
#define J1939_FOURTHLINE        0x03


/*************************************************************************
**    Function prototypes
*************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*************************************************************************

 Function:
  J1939Api_GetVersion

 Description:
  Gets the product version of the J1939 API as string.

 Arguments:
  pcProdVersion       OUT   Pointer to the buffer (allocated by the application)
                            that provides the product version.
                            NULL if the version number is not required by
                            the application.
  pbProdVersionSize   IN    Size of the allocated memory in bytes in
                            pcProdVersion
                      OUT   Number of bytes written to pcProdVersion

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_POINTER}          Invalid pointer received
  {J1939API_E_MEMSIZE}          Size of allocated memory insufficient

*************************************************************************/
int CALLATTR  J1939Api_GetVersion       ( CHAR*   pcProdVersion,
                                          UINT8*  pbProdVersionSize );


/*************************************************************************

 Function:
  J1939Api_GetResultString

 Description:
  J1939 API 2 functions return error codes {J1939_t_RESULT} to indicate a
  failure of the function. _
  This function transcripts a particular result to an ASCII string that
  describes the error.

 Arguments:
  iResult             IN    Result from API
  pcDescription       IN    Pointer to the buffer (allocated by the application)
                            that provides the error description (up to
                            255 bytes)
  pbDescriptionSize   IN    Size of the allocated memory in bytes in
                            pcDescription
                      OUT   Used memory in bytes (length of the error
                            description string plus one)

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_MEMSIZE}          Size of allocated memory insufficient

*************************************************************************/
int CALLATTR  J1939Api_GetResultString  ( INT32   iResult,
                                          CHAR*   pcDescription,
                                          UINT8*  pbDescriptionSize );


/*************************************************************************

 Function:
  J1939Api_GetNumberBoards

 Description:
  Provides the number of installed IXXAT CAN interface boards.

 See also:
  J1939Api_GetBoardInfo()

 Arguments:
  pbNumberBoards      OUT   Number of installed IXXAT CAN interface boards

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_DRV_GETBOARDS}    Retrieval of current board list from
                                CAN driver failed
*************************************************************************/
int CALLATTR  J1939Api_GetNumberBoards  ( UINT8*  pbNumberBoards );


/*************************************************************************

 Function:
  J1939Api_GetBoardInfo

 Description:
  Requests general information of an installed IXXAT CAN interface board.

 See also:
  J1939Api_GetNumberBoards()

 Arguments:
  bBoardIndex         IN    Zero-based index of the IXXAT CAN interface board
  pcBoardInfo         IN    Pointer to the buffer (allocated by the application)
                            that provides the board information.
                            The corresponding structured data type 
                            {J1939API_BOARDINFO} is in header file
                            ``XatJ1939_types.h``.	
  pwBoardInfoSize     IN    Size of the allocated memory in bytes in
                            pcBoardInfo
                      OUT   Number of bytes written to pcBoardInfo

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_MEMSIZE}          Size of allocated memory insufficient
  {J1939API_E_INVALIDARG}       Invalid bBoardIndex passed to the function
  {J1939API_E_DRV_GETBOARDS}    Retrieval of current board list from
                                CAN driver failed
  {J1939API_E_DRV_BOARD}        Invalid board

*************************************************************************/
int CALLATTR  J1939Api_GetBoardInfo     ( UINT8   bBoardIndex,
                                          CHAR*   pcBoardInfo,
                                          UINT16* pwBoardInfoSize );


/*************************************************************************

 Function:
  J1939Api_AddSignalBase

 Description:
  Declares a message definitions file to be used with the optional decoding
  and encoding functions of the J1939 API 2. _
  If the function is called more than once the defined PGNs of each file are
  supported. If the same PGN is defined in more than one message definition
  file, the definition of the last added message definition file is used
  (previously added definitions are overwritten).

 See also:
  J1939Api_GetSpnList()
  J1939Api_GetSignalAttributes()
  J1939Api_GetBitFieldState()
  J1939Api_ReadSignal()
  J1939Api_ReadString()
  J1939Api_WriteSignal()
  J1939Api_WriteString()
  J1939Api_CalcDataSize()

 Arguments:
  pcFilePath          IN    Filename and path of a file that contains the J1939
                            message definitions

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_FS_OPEN}          Error opening the file that contains the J1939
                                message definitions
  {J1939API_E_FS_IMPORT}        Error importing the J1939 messages from the
                                given file
*************************************************************************/
int CALLATTR  J1939Api_AddSignalBase    ( const wchar_t*pcFilePath );


/*************************************************************************

 Function:
  J1939Api_CreateInstance

 Description:
  Creates a communication instance and attempts to connect the instance with a
  CAN channel of an IXXAT CAN interface board. _
  If the connection is successful, the CAN channel is started and an instance
  handle is returned. The application has to store the handle to conduct future
  transactions with the newly created instance. _
  When the instance is no longer required, it can be destroyed by
  {J1939Api_DestroyInstance()}.

  J1939 API 2 supports multiple communication instances on one CAN channel,
  but only the first instance is able to set the baudrate.
  Further instances that try to connect to an already connected CAN channel
  have to use the same baudrate as the first one. Otherwise the connection
  establishment between instance and CAN channel fails.

  If exactly one CAN board is present in the system and pBoardtype is set to
  ``J1939_DEFAULTBOARD``, it is not necessary to enter a valid value in
  pBoardtype/pBoardID._
  When pBoardtype is set to ``J1939_BOARDDIALOG``, the IXXAT hardware selection
  dialog opens on Windows.

  pBoardID can be set to ``J1939_1stBOARD``, ``J1939_2ndBOARD``... to select
  the n-th instance of a specific board type.

 See also:
  J1939Api_DestroyInstance()
  J1939Api_GetBoardInfo()

 Arguments:
  guidBoardtype       IN    Type of IXXAT CAN interface board to be used by the
                            created instance, related to {J1939Api_GetBoardInfo()}
                            ECI:      DeviceClass acc.to ``vciguid.h``
                            SocketCAN:``GUID_SOCKETCAN_CLASS`` acc.to ``vciguid.h``
                            VCI:      DeviceClass acc.to ``vciguid.h``
                      OUT   Type of the selected IXXAT CAN interface board
  guidBoardID         IN    Unique global identifier of the CAN board
                            ECI:      ``ECI_HW_INFO.szHwSerial`` as GUID
                            SocketCAN:Interface name e.g. ``can0``, ``can1`` as GUID
                            VCI:      ``UniqueHardwareId.AsGuid``
                      OUT   Unique global identifier of the selected IXXAT CAN
                            interface board
  bCanChannel         IN    Zero-based CAN channel on the IXXAT CAN interface
                            board that is used by the communication instance.
                            Predefined values:
                            ``J1939_FIRSTLINE`` - default (first CAN line)
                            ``J1939_SECONDLINE`` - second CAN line
                            ``J1939_THIRDLINE`` - third CAN line
                            ``J1939_FOURTHLINE`` - fourth CAN line
  eProtocol           IN    Set protocol to 0 (``0`` = J1939).
                            Currently only J1939 protocol is supported.
  wBaudrate           IN    Baudrate of the CAN line in kBit/s
  pbInstHandle        OUT   Handle of the created instance

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_INVALIDARG}       Invalid argument passed to the function
  {J1939API_E_DRV_BOARDSELECT}  Selection of CAN driver board failed
  {J1939API_E_DRV_BOARD}        Invalid board
  {J1939API_E_DRV_CANCHAN}      Invalid CAN channel
  {J1939API_E_MAXINST}          Maximum allowed API instances exceeded
  {J1939API_E_MULTIINST}        Multiple instances want to connect to the
                                same CAN channel with different baudrates
  {J1939API_E_STK_INIT}         Initializing the J1939 stack failed.
                                For SocketCAN, make sure the CAN board is up
                                and is configured as
                                sudo ip link set can0 type can bitrate 250000
  {J1939API_E_STK_START}        Starting the J1939 stack failed.
                                For SocketCAN, make sure the CAN board is up
                                and running as
                                sudo ip link set can0 up
  {J1939API_E_STK_THREADINIT}   Initializing the J1939 thread failed.

*************************************************************************/
int CALLATTR  J1939Api_CreateInstance   ( CHAR    guidBoardtype[16],
                                          CHAR    guidBoardID[16],
                                          UINT8   bCanChannel,
                                          UINT8   eProtocol,
                                          UINT16  wBaudrate,
                                          UINT8*  pbInstHandle );


/*************************************************************************

 Function:
  J1939Api_DestroyInstance

 Description:
  Destroys a communication instance created by {J1939Api_CreateInstance()}.

 See also:
  J1939Api_CreateInstance()

 Arguments:
  bInstHandle         IN    Handle of the communication instance

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_INVALIDHANDLE}    Handle does not match an existing instance

*************************************************************************/
int CALLATTR  J1939Api_DestroyInstance  ( UINT8   bInstHandle );


/*************************************************************************

 Function:
  J1939Api_ReceiveError

 Description:
  Reads an error from the error queue.

  Many errors are not directly related to an actual API function call and
  occur independently of the currently active API function, e.g. in the
  internal timeout guarding, in protocol handling, or due to CAN messages from
  other network participants. The errors happen asynchronously, and
  are not reflected in a result of a direct API function call.
  When such an error occurs, it is entered in the error queue to be read
  by the application regularly and parallel.

 See also:
  J1939Api_CreateInstance()
  J1939Api_GetResultString()
  J1939Api_SendMessage()

 Arguments:
  bInstHandle         IN    Handle of the communication instance
  pwErrorCode         OUT   Unique error code
  pdwAddInfo          OUT   Additional error information,
                            optional argument, can be ``NULL``
  pdwTimestamp        OUT   Time when the receive error occurred,
                            optional argument, can be ``NULL``
  pcDescription       IN    Plain text explanation of the error code,
                            optional argument, can be ``NULL``.
                            Pointer to the buffer (allocated by the
                            application) that provides the error description
                            (up to 255 bytes)
  pbDescriptionSize   IN    Size of the allocated memory in bytes in
                            pcDescription,
                            optional argument, can be ``NULL``
                      OUT   Used memory in bytes (length of the error
                            description string plus one)

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_S_NODATA}           No data available
  {J1939API_E_INVALIDHANDLE}    Handle does not match an existing instance
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_NOTINITIALIZED}   Attempt to use an uninitialized API instance

*************************************************************************/
int CALLATTR  J1939Api_ReceiveError     ( UINT8   bInstHandle,
                                          UINT16* pwErrorCode,
                                          UINT32* pdwAddInfo,
                                          UINT32* pdwTimestamp,
                                          CHAR*   pcDescription,
                                          UINT8*  pbDescriptionSize );


/*************************************************************************

 Function:
  J1939Api_SendMessage

 Description:
  Sends a message on a communication instance, using the selected device and
  protocol. The message is placed in a queue and processed in the receive order
  (FIFO).

  A message is rejected if the transmit queue is full or if any error condition
  is detected.

 See also:
  J1939Api_ReceiveMessage()
  J1939Api_CreateInstance()
  J1939Api_ReceiveError()

 Arguments:
  bInstHandle         IN    Handle of a communication instance
  pcMessage           IN    Pointer to the buffer (allocated by the application)
                            that provides the message to be sent.
                            The message format must be in conformance with the
                            specified protocol of the communication instance.
                            The corresponding structured data type 
                            {J1939API_J1939MSG} can be found in header file 
                            ``XatJ1939_types.h``.
  wMessageSize        IN    Size of the message in bytes

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_NOTINITIALIZED}   Attempt to use an uninitialized API instance
  {J1939API_E_INVALIHANDLE}     Handle does not match an existing instance.
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_MEMSIZE}          Size of allocated memory insufficient
  {J1939API_E_INVALIDPROTOCOL}  Function not applicable to the active protocol
  {J1939API_E_MSG_TOO_LONG}     Message too long
  {J1939API_E_MSG_TX_TIMEOUT}   Message not sent in time
  {J1939API_E_ADDRESSLOST}      Communication instance forced to concede the
                                address to another node on the J1939 network
  {J1939API_E_QUEUEFULL}        Transmit message queue is full.
  {J1939API_E_STK_TX_FAIL}      General error, check {J1939Api_ReceiveError()}
                                for details.
*************************************************************************/
int CALLATTR  J1939Api_SendMessage      ( UINT8   bInstHandle,
                                          CHAR*   pcMessage,
                                          UINT16  wMessageSize );


/*************************************************************************

 Function:
  J1939Api_ReceiveMessage

 Description:
  Reads a J1939 message on a communication instance, using the selected device.

 See also:
  J1939Api_SendMessage()
  J1939Api_CreateInstance()

 Arguments:
  bInstHandle         IN    Handle of a communication instance
  pcMessage           IN    Pointer to the buffer (allocated by the application)
                            that provides the J1939 message.
                            The corresponding structured data type 
                            {J1939API_J1939MSG} is in header file 
                            ``XatJ1939_types.h``.
  wMessageSize        IN    Size of the allocated memory in bytes in
                            pcMessage

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_NOTINITIALIZED}   Attempt to use an uninitialized API instance
  {J1939API_E_INVALIHANDLE}     Handle does not match an existing instance
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_INVALIDPROTOCOL}  Function not applicable to the active protocol
  {J1939API_E_NOINTERFACE}      General error
  {J1939API_E_MSG_TOO_LONG}     Message too long for the given buffer
  {J1939API_E_MSG_RX_TIMEOUT}   Message not received in time

*************************************************************************/
int CALLATTR  J1939Api_ReceiveMessage   ( UINT8   bInstHandle,
                                          CHAR*   pcMessage,
                                          UINT16  wMessageSize );


/*************************************************************************

 Function:
  J1939Api_SendCommand

 Description:
  Provides a command interface, that can be used to configure a
  communication instance according to the application needs.

 See also:
  J1939Api_CreateInstance()

 Remarks:
  The following commands are supported by the J1939 API 2:
  |ID | Command                     |Protocol |
  | 0 | Reset Device                | Common  |
  | 1 | Set Blocking Timeout        | Common  |
  | 2 | reserved for future use     | -       |
  | 3 | Set Filter for J1939        | J1939   |
  | 4 | reserved for future use     | -       |
  | 5 | Protect J1939 Address       | J1939   |
  | 6 | Release J1939 Address       | J1939   |
  | 7 | Set Sniffing Filter mode    | J1939   |
  | 8 | Add rule to Sniffing Filter | J1939   |

  Reset Device
    Attempts to reset the CAN channel (physical device) of an instance.
    Not allowed if multiple communication instances are connected to the CAN
    channel. There is no command buffer for the command.

  Set Blocking Timeout
    Sets the timeout in milliseconds for a command or a message. By default the
    timeout value of a created instance is 0 (polling mode). A current block
    fails if the user destroys the instance. _
    A corresponding structured data type {J1939API_COMMAND_SETBLOCKINGTIMEOUT}
    is in header file ``XatJ1939_types.h``

  Set Filter for J1939
    Creates a filter for J1939 messages. A PGN list is used as inclusive filter.
    To avoid the reception of unwanted messages, the filter of a newly created
    instance is by default closed. _
    The corresponding structured data type {J1939API_COMMAND_SETFILTERFORJ1939}
    is in header file ``XatJ1939_types.h``

  Protect J1939 Address
    J1939 API 2 can claim and protect a J1939 address on the network and
    activate network management functions. When the command is issued, the
    instance attempts to claim the address that is requested by the application.
    If the address is successfully claimed, the API continues to protect the
    address. If the API is forced to concede the address to another node on the
    network, any blocked calls to J1939Api_SendMessage() are released with an
    error. When in polling mode only, the next call to J1939Api_SendMessage()
    returns an error indicating that the address is lost.
    After the application is notified of the lost address, the application
    can either attempt to claim another address, or invoke the command to
    release the previously claimed address and deactivate the network management
    functions. The application must perform one of these tasks before the
    instance allows further network communication from this address.
    Once an address is successfully claimed, the instance may handshake for
    J1939 RTS/CTS sessions to the protected address (when the J1939 transport
    protocols are activated). The instance do not handshake for any messages that
    is not destined to an address that it is protecting. If a protected address
    is lost, the instance aborts current RTS/CTS sessions.
    By default no address is protected by a newly created instance. This means
    the application is able to transmit and receive single frame messages to and
    from any address on the J1939 network. Even if the instance is protecting an
    address, it is allowed to send from any address. _
    The corresponding structured data type {J1939API_COMMAND_PROTECTJ1939ADDRESS}
    is in header file ``XatJ1939_types.h``.

  Release J1939 Address
    Releases a previously claimed J1939 address. When the command is issued, the
    instance releases the claimed address and deactivates the network management
    functions. This means the instance ceases to handshake for RTS/CTS sessions
    and aborts any active RTS/CTS sessions. The command can be used after
    notifying the application about the lost address.
    Once a protected address is released, the instance aborts the current outgoing
    or incoming J1939 transport sessions. If an outgoing transport session is
    aborted by the command, J1939Api_SendMessage() returns an error code.
    An address can also be released by claiming a second address via the Protect
    J1939 Address command. _
    The corresponding structured data type {J1939API_COMMAND_RELEASEJ1939ADDRESS}
    is in header file ``XatJ1939_types.h``.

  Set Sniffing Filter mode
    Sets the operating mode for the Sniffing Filter.
    Default mode is "inclusive filter" (white list)
    but can alternatively be set to "exclusive filter" (black list). _
    The corresponding structured data type 
    {J1939API_COMMAND_SETFILTERMODEFORSNIFFINGJ1939} is in header file 
    ``XatJ1939_types.h``

  Add rule to Sniffing Filter
    The Sniffing Filter is an J1939 message filter that bypasses the J1939 stack
    to allow network monitoring without network interaction. That means, there
    is no handling of the J1939 transport protocol nor other message handling
    for messages that pass this filter.
    Each call adds an additional entry to the Sniffing Filter, based on PGN,
    The corresponding structured data type 
    {J1939API_COMMAND_SETFILTERFORSNIFFINGJ1939} is in header file 
    ``XatJ1939_types.h``.

 Arguments:
  bInstHandle         IN    Handle of a communication instance
  bCommandId          IN    ID specifying the command
  pcCommandBuffer     IN    Pointer to a buffer (allocated by the application).
                            The buffer is utilized based on the command ID.
                            Corresponding structured data types are in header
                            file ``XatJ1939_types.h``
  wCommandBufferSize  IN    Size of the command buffer in bytes

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_NOTINITIALIZED}   Attempt to use an uninitialized API instance
  {J1939API_E_INVALIHANDLE}     Handle does not match an existing instance
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_MEMSIZE}          Size of allocated memory insufficient
  {J1939API_E_NOINTERFACE}      General error
  {J1939API_E_INVALIDCOMMAND}   Invalid command ID (command is not supported)
  {J1939API_E_INVALIDPROTOCOL}  Command not applicable to the active protocol
  {J1939API_E_INVALIDARG}       Invalid value inside command buffer
  {J1939API_E_STK_REG_MAX}      Maximum allowed message registrations
                                exceeded
  {J1939API_E_STK_REG_FAIL}     Registration of a message failed, check
                                {J1939Api_ReceiveError()} for details.
  {J1939API_E_ADDRESSLOST}      Failed to protect the claimed address
                                resp. failed to release the address
*************************************************************************/
int CALLATTR  J1939Api_SendCommand      ( UINT8   bInstHandle,
                                          UINT8   bCommandId,
                                          CHAR*   pcCommandBuffer,
                                          UINT16  wCommandBufferSize );


/*************************************************************************

 Function:
  J1939Api_GetSpnList

 Description:
  Retrieves a list of SPNs within a given PG.

  Two possible use cases are supported by this function. _
  In the first use case, an actual J1939 message payload is given, interpreted,
  and the resulting SPNs are returned. The corresponding combination of function
  arguments is: ``(pbData != NULL)``, and ``wDataSize != 0``. _
  In the second use case, a typical resulting SPN list is returned. No relation
  to an actual J1939 message payload is needed. The corresponding combination of
  function arguments is: ``(pbData == NULL)``, and ``wDataSize = 0``. _

  The memory for the SPN list must be maintained by the user as an array of
  32-bit unsigned integers or as allocated memory.

  The items of the SPN list are ordered in their sequence of occurrence in
  the Program Group. In compliance with J1939 the items of the SPN list are not
  unique, i.e. can appear several times.

  The count argument should initially indicate the number of SPNs for which
  the memory is allocated. If the function succeeds, the actual number of SPNs
  is returned. _
  The number of possible SPNs returned is limited by ``J1939API_MAX_PARAM_COUNT``.

 See also:
  J1939Api_CalcDataSize()
  J1939Api_ReadSignal()
  J1939Api_ReadString()
  J1939Api_WriteSignal()
  J1939Api_WriteString()

 Arguments:
  dwPgn               IN    PGN of a J1939 message for which the SPN list
                            is to be retrieved
  pbData              IN    Pointer to the buffer (allocated by the
                            application) that provides the J1939 message
                            payload to be analyzed,
                            optional argument, can be NULL.
  wDataSize           IN    Size of the J1939 message payload buffer to be
                            analyzed in bytes,
                            optional argument, can be 0.
  pdwSpnList          IN    Pointer to the buffer (allocated by the
                            application) that provides the SPN list
  pwSpnListSize       IN    Size of the allocated memory in bytes in
                            pdwSpnList
                      OUT   Number of **bytes** written to pdwSpnList
                            Number of items = *pwSpnListSize / 4
  pwFrameCount        OUT   Number of groups of SPs (called Frame) the PG
                            consists of,
                            optional argument, can be NULL.

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_S_PRESUMED_MSG}     Function succeeded, but J1939 message
                                contains variable elements of unknown size,
                                returned items may be incorrect or incomplete.
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_FS_OPEN}          Signal database is missing (call
                                {J1939Api_AddSignalBase()} first)
  {J1939API_E_MEMSIZE}          Size of allocated memory insufficient.
                                Check *pwSpnListSize for required buffer size.
                                Or make sure pbData's wDataSize is long enough.
  {J1939API_E_TREE_GETPGNODE}   PGN not defined in any added signal
                                database.
  {J1939API_E_TREE_GETSPLIST}   Retrieval of J1939 message definitions SP list
                                failed
  {J1939API_E_DECODING}         Decoding of the signal from pbData failed

*************************************************************************/
int CALLATTR  J1939Api_GetSpnList       ( UINT32  dwPgn,
                                          UINT8*  pbData,
                                          UINT16  wDataSize,
                                          UINT32* pdwSpnList,
                                          UINT16* pwSpnListSize,
                                          UINT16* pwFrameCount );


/*************************************************************************

 Function:
  J1939Api_GetSignalAttributes

 Description:
  Retrieves attributes corresponding to a specific SPN.

  With the signal attributes the application is able to calculate the
  physical signal value from its raw value and vice versa.
  Some of the signal attributes (e.g. unit name or bit field states)
  can be used for display purposes.

 See also:
  J1939Api_GetSpnList()
  J1939Api_AddSignalBase()

 Arguments:
  dwSpn               IN    SPN of the signal from which the attributes are
                            to be retrieved.
  pcAttributes        IN    Pointer to the buffer (allocated by the
                            application) that provides the signal attributes.
                            The corresponding structured data type 
                            {J1939API_SIGNALATTRIBUTES} is in header file 
                            ``XatJ1939_types.h``.
  pwAttributesSize    IN    Size of the allocated memory in bytes in
                            pcAttributes
                      OUT   Number of bytes written to pcAttributes

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_FS_OPEN}          Signal database is missing (call
                                {J1939Api_AddSignalBase()} first)
  {J1939API_E_MEMSIZE}          Size of allocated memory insufficient
  {J1939API_E_TREE_GETSPNODE}   SPN not defined in any added signal
                                database
*************************************************************************/
int CALLATTR J1939Api_GetSignalAttributes( UINT32 dwSpn,
                                          CHAR*   pcAttributes,
                                          UINT16* pwAttributesSize );


/*************************************************************************

 Function:
  J1939Api_GetBitFieldState

 Description:
  Retrieves the description to a given bit field state.

 Arguments:
  dwSpn               IN    SPN of a signal of type ‘BITFIELD’
  dwValue             IN    State value from which the state description
                            is to be retrieved.
  pcDescription       IN    Pointer to the buffer (allocated by the
                            application) to where the state description
                            is to be written.
                            The corresponding structured data type 
                           {J1939API_BITFIELDSTATE} is in header file 
                           ``XatJ1939_types.h``.
  pbDescriptionSize   IN    Size of the allocated memory in bytes in
                            pcDescription
                      OUT   Number of bytes written to pcDescription

 See also:
  J1939Api_GetSpnList()
  J1939Api_AddSignalBase()

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_FS_OPEN}          Signal database is missing (call
                                {J1939Api_AddSignalBase()} first)
  {J1939API_E_MEMSIZE}          Size of allocated memory insufficient
  {J1939API_E_TREE_GETSPNODE}   SPN not defined in any added signal
                                database
  {J1939API_E_TREE_SPNTYPE}     SPN is not of type ‘BITFIELD’
  {J1939API_E_DECODING}         Decoding of the J1939 parameters failed

*************************************************************************/
int CALLATTR  J1939Api_GetBitFieldState ( UINT32  dwSpn,
                                          UINT32  dwValue,
                                          CHAR*   pcDescription,
                                          UINT8*  pbDescriptionSize );


/*************************************************************************

 Function:
  J1939Api_ReadSignal

 Description:
  Reads a signal of any data type except for ‘ASCII’ and ‘BLOB’ as raw value
  from a J1939 message.

  The bit position and signal size information from the declared message
  definition file (Signal base) are used. _
  The returned signal is delivered as raw, uninterpreted value of a SP in
  little endian format. Conversion to physical value with the signal
  attributes is up to the application.

  Signals of data type ‘ASCII’ or ‘BLOB’ can be read by {J1939Api_ReadString()}

 See also:
  J1939Api_ReadString()
  J1939Api_WriteSignal()
  J1939Api_GetSpnList()
  J1939Api_GetSignalAttributes()
  J1939Api_AddSignalBase()

 Arguments:
  dwPgn               IN    PGN of the J1939 message to which the signal belongs
  dwSpn               IN    SPN of the signal to be read
  wSpnIndex           IN    Zero-based SPN index is required for messages with
                            variable data length. If several signals with the
                            same SPN are included in a message, the index
                            defines which signal is to be read.
                            The index selects the n-th occurrence
                            of the SPN in the J1939 message.
  pbData              IN    Pointer to the buffer (allocated by the
                            application) that provides the J1939 message
                            payload
  wDataSize           IN    Size of the J1939 message payload buffer in bytes
  pdwSignal           OUT   Delivers the read signal value of the given SPN

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_MEMSIZE}          Size of allocated memory insufficient
  {J1939API_E_FS_OPEN}          Signal database missing (call
                                {J1939Api_AddSignalBase()} first)
  {J1939API_E_TREE_GETPGNODE}   PGN not defined in any added signal
                                database
  {J1939API_E_TREE_GETSPNODE}   No signal with the given SPN mapped to the
                                given program group
  {J1939API_E_TREE_GETNODEDATA} No signal with the given SPN index
                                included in the given J1939 message payload
  {J1939API_E_TREE_SPNTYPE}     Signal has the data type ‘ASCII’ or ‘BLOB’.
                                Use {J1939Api_ReadString()} instead.
  {J1939API_E_DECODING}         Decoding of the signal from J1939 message
                                payload failed
*************************************************************************/
int CALLATTR  J1939Api_ReadSignal       ( UINT32  dwPgn,
                                          UINT32  dwSpn,
                                          UINT16  wSpnIndex,
                                          UINT8*  pbData,
                                          UINT16  wDataSize,
                                          UINT32* pdwSignal );


/*************************************************************************

 Function:
  J1939Api_ReadString

 Description:
  Reads a signal of data type ‘ASCII’ or ‘BLOB’ from a J1939 message.

  The bit position and signal size information from the
  declared message definition file (signal base) are used.

  Any data type {eJ1939ApiSPType} can be read by this function. _
  ``eJ1939ApiSPType_FLOAT``, ``eJ1939ApiSPType_INTEGER``, ``eJ1939ApiSPType_BITFIELD``
  are delivered as interpreted string (contrary to {J1939Api_ReadSignal()},
  that delivers the raw value of the signal). _
  ``eJ1939ApiSPType_ASCII`` and ``eJ1939ApiSPType_BLOB`` are delivered "as is". _
  ``eJ1939ApiSPType_BINARY`` are delivered as hexadecimally formatted string
  of single bytes like "4F 0A 91 ". To get the length of the value, divide
  *pwStringSize by 3.

 See also:
  J1939Api_WriteString()
  J1939Api_ReadSignal()
  J1939Api_GetSpnList()
  J1939Api_GetSignalAttributes()
  J1939Api_ReadMessage()
  J1939Api_AddSignalBase()

 Arguments:
  dwPgn               IN    PGN of the J1939 message to which the signal belongs
  dwSpn               IN    SPN of the signal to be read
  wSpnIndex           IN    Zero-based SPN index is required for messages with
                            variable data length. If several signals with the
                            same SPN are included in a message, the index
                            defines which signal is to be read.
                            The index selects the n-th occurrence
                            of the SPN in the J1939 message.
  pbData              IN    Pointer to the buffer (allocated by the
                            application) that provides the J1939 message
                            payload
  wDataSize           IN    Size of the J1939 message payload buffer in bytes.
  pcString            IN    Pointer to the buffer (allocated by the
                            application) that provides the signal string
  pwStringSize        OUT   Signal string size in bytes (including
                            terminating zero)

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_MEMSIZE}          Size of allocated memory insufficient
  {J1939API_E_FS_OPEN}          Signal database is missing (call
                                {J1939Api_AddSignalBase()} first)
  {J1939API_E_TREE_GETPGNODE}   PGN not defined in any added signal
                                database
  {J1939API_E_TREE_GETSPNODE}   No signal with the given SPN mapped to the
                                given program group
  {J1939API_E_TREE_GETNODEDATA} No signal with the given SPN index
                                included in the given J1939 message payload
  {J1939API_E_DECODING}         Decoding of the signal from J1939 message
                                payload failed
*************************************************************************/
int CALLATTR  J1939Api_ReadString       ( UINT32  dwPgn,
                                          UINT32  dwSpn,
                                          UINT16  wSpnIndex,
                                          UINT8*  pbData,
                                          UINT16  wDataSize,
                                          CHAR*   pcString,
                                          UINT16* pwStringSize );


/*************************************************************************

 Function:
  J1939Api_WriteSignal

 Description:
  Writes a signal of any data type except for ‘ASCII’ and ‘BLOB’ to a J1939
  message.

  The bit position and signal size information from the declared message
  definition file (signal base) are used. _
  As signals are always transferred as raw value on a J1939 network, the
  application is assisted to calculate the raw value from the physical value
  with help of the signal attributes.

  Signals of data type ‘ASCII’ or ‘BLOB’ can be written by
  {J1939Api_WriteString()}

 See also:
  J1939Api_WriteString()
  J1939Api_ReadSignal()
  J1939Api_GetSpnList()
  J1939Api_GetSignalAttributes()
  J1939Api_CalcDataSize()
  J1939Api_AddSignalBase()

 Arguments:
  dwPgn               IN    PGN of the J1939 message to which the signal belongs
  dwSpn               IN    SPN of the signal to be written
  wSpnIndex           IN    Zero-based SPN index is required for messages with
                            variable data length. If several signals with the
                            same SPN are included in a message, the index
                            defines which signal is to be written.
                            The index selects the n-th occurrence
                            of the SPN in the J1939 message.
  pbData              IN    Pointer to the buffer (allocated by the
                            application) that provides a J1939 message
                            payload, given that signals are packed into it
  wDataSize           IN    Size of the J1939 message payload buffer in bytes
  dwSignal            IN    Raw signal value of the SPN that is to be
                            written to the payload buffer

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_FS_OPEN}          Signal database is missing (call
                                {J1939Api_AddSignalBase()} first)
  {J1939API_E_MEMSIZE}          Size of allocated memory insufficient
  {J1939API_E_TREE_GETPGNODE}   PGN not defined in any added signal
                                database
  {J1939API_E_TREE_GETSPNODE}   No signal with the given SPN mapped to the
                                given program group
  {J1939API_E_TREE_GETNODEDATA} No signal with the SPN index
                                included in the given J1939 message payload
  {J1939API_E_TREE_SPNTYPE}     Signal has the data type ‘ASCII’ or ‘BLOB’.
                                Use {J1939Api_WriteString()} instead.
  {J1939API_E_ENCODING}         Encoding of the signal to J1939 message payload
                                failed
  {J1939API_S_ENCODING_OUT_OF_RANGE}  Given signal value is out of range acc.to
                                data type, encoded value was cut.
*************************************************************************/
int CALLATTR  J1939Api_WriteSignal      ( UINT32  dwPgn,
                                          UINT32  dwSpn,
                                          UINT16  wSpnIndex,
                                          UINT8*  pbData,
                                          UINT16  wDataSize,
                                          UINT32  dwSignal );


/*************************************************************************

 Function:
  J1939Api_WriteString

 Description:
  Writes a signal of data type ‘ASCII’ or ‘BLOB’ to a J1939 message.

  The bit position and signal size information from the declared message
  definition file (signal base) are used. The function copies the string
  to the proper position in the J1939 message.

  Signals of any other data type can be written by {J1939Api_WriteSignal()}

  There is no conversion of the given string. It is not required to be zero
  terminated. Therefore, the given "signal string" can be considered a byte
  stream.

 See also:
  J1939Api_WriteSignal()
  J1919Api_ReadString()
  J1939Api_GetSpnList()
  J1939Api_GetSignalAttributes()
  J1939Api_CalcDataSize()
  J1939Api_AddSignalBase()

 Arguments:
  dwPgn               IN    PGN of the J1939 message to which the signal belongs
  dwSpn               IN    SPN of the signal to be written
  wSpnIndex           IN    Zero-based SPN index is required for messages with
                            variable data length. If several signals with the
                            same SPN are included in a message, the index
                            defines which signal is to be written.
                            The index selects the n-th occurrence
                            of the SPN in the J1939 message.
  pbData              IN    Pointer to the buffer (allocated by the
                            application) that provides a J1939 message
                            payload
                            The function packs the given string into it.
  wDataSize           IN    Size of the J1939 message payload buffer in bytes
  pcString            IN    Pointer to the "signal string". Not required to
                            be zero terminated nor '*'-terminated acc.to J1939
                            conventions. The length is given in wStringSize.
  wStringSize         IN    Signal string size in bytes; actual payload
                            length of pcString. Since pcString is considered a
                            simple byte buffer, non-printable characters are
                            accepted as the application is responsible for
                            data plausibility.

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_FS_OPEN}          Signal database missing (call
                                {J1939Api_AddSignalBase()} first)
  {J1939API_E_MEMSIZE}          Size of allocated memory insufficient
  {J1939API_E_TREE_GETPGNODE}   PGN not defined in any added signal
                                database
  {J1939API_E_TREE_GETSPNODE}   No signal with the given SPN mapped to the
                                given J1939 message
  {J1939API_E_TREE_GETNODEDATA} No signal with the given SPN index
                                included in the J1939 message payload
  {J1939API_E_TREE_SPNTYPE}     Signal does not have the data type ‘ASCII’
                                or ‘BLOB’. Use {J1939Api_WriteSignal()} instead.
  {J1939API_E_ENCODING}         Encoding of the signal to J1939 message payload
                                failed
*************************************************************************/
int CALLATTR  J1939Api_WriteString      ( UINT32  dwPgn,
                                          UINT32  dwSpn,
                                          UINT16  wSpnIndex,
                                          UINT8*  pbData,
                                          UINT16  wDataSize,
                                          CHAR*   pcString,
                                          UINT16  wStringSize );


/*************************************************************************

 Function:
  J1939Api_CalcDataSize

 Description:
  Calculates the size of a J1939 message to be transmitted.

  For J1939 messages to be transmitted, the payload must be allocated by the
  application.  Typically, the message is static and constant. _
  Additionally there are variable sized PGs that consist of repeated groups
  of SPs, so-called Frames by J1939 API 2.

  When preparing a J1939 message to be transmitted, the frame count must be
  known, because the data payload length depends on it.  The byte size of the
  frame count can be calculated by this function. _
  Usage of this function is not limited to variable size PGs.

  In {J1939Api_ReadSignal()} and {J1939Api_ReadString()}, the frame number is
  congruent with wSpnIndex argument.

 See also:
  J1939Api_ReadSignal()
  J1939Api_ReadString()
  J1939Api_WriteSignal()
  J1939Api_WriteString()
  J1939Api_GetSpnList()
  J1939Api_AddSignalBase()

 Arguments:
  dwPgn               IN    PGN of the J1939 message to be transmitted
  wFrameCount         IN    Number of groups of SPs (called Frame) the PG
                            consists of
  pwDataSize          OUT   Resulting size of the J1939 message payload buffer
                            in bytes

 Results:
  {J1939API_S_OK}               Function succeeded
  {J1939API_S_PRESUMED_MSG}     Function succeeded, but PG contains variable
                                elements of unknown size. Returned data size
                                may be incorrect or incomplete.
  {J1939API_E_POINTER}          NULL pointer passed to the function
  {J1939API_E_FS_OPEN}          Signal database is missing (call
                                {J1939Api_AddSignalBase()} first)
  {J1939API_E_TREE_GETPGNODE}   PGN not defined in any added signal
                                database
  {J1939API_E_DECODING}         General error by decoding engine

*************************************************************************/
int CALLATTR  J1939Api_CalcDataSize     ( UINT32  dwPgn,
                                          UINT16  wFrameCount,
                                          UINT16  *pwDataSize );


#ifdef __cplusplus
};
#endif // __cplusplus


#endif // XATJ1939_H
