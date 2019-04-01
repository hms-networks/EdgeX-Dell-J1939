/*************************************************************************
**  HMS Networks AB
**************************************************************************
**
**        File: XatJ1939_types.h
**
**     Summary: Types, defines and structures for IXXAT J1939 API (C, C++)
**              Specifies certain defines and structures related to the
**              J1939 API interface, as well as macros to interpret
**              relevant structures and types.
**
**    Compiler: Microsoft VS2010
**              GNU Compiler Collection 5.4.0
**
**************************************************************************
**  Copyright (C) 2009-2018 HMS Technology Center Ravensburg GmbH, all rights reserved
*************************************************************************/

#ifndef XATJ1939_TYPES_H
#define XATJ1939_TYPES_H


/*************************************************************************
** enumerations
*************************************************************************/
#ifdef __cplusplus
//-----------------------------------------------------------------
// J1939 API Protocol constant _
//  To be used with {J1939Api_CreateInstance()} argument ``eProtocol``
//-----------------------------------------------------------------
enum eJ1939ApiProtocol: UINT8
{
  J1939ApiProtocol_J1939,
  J1939ApiProtocol_CAN
};
//-----------------------------------------------------------------
// J1939 API Command identifiers _
//  To be used with {J1939Api_SendCommand()} argument ``bCommandId``
//-----------------------------------------------------------------
enum eJ3939ApiCommandId: UINT8
{
  J3939ApiCommandId_Reset,
  J3939ApiCommandId_Timeout,
  J3939ApiCommandId_FilterCAN,
  J3939ApiCommandId_FilterJ1939,
  J3939ApiCommandId_SwitchTP,
  J3939ApiCommandId_ProtectAddr,
  J3939ApiCommandId_ReleaseAddr,
  J3939ApiCommandId_FilterModeSniffingJ1939,
  J3939ApiCommandId_SniffingJ1939
};
//-----------------------------------------------------------------
// J1939 Suspect Parameter type constant _
//  To be used with structured data type ``J1939API_SIGNALATTRIBUTES``
//-----------------------------------------------------------------
enum eJ1939ApiSPType: UINT8
{
  eJ1939ApiSPType_INVALID,
  eJ1939ApiSPType_FLOAT,
  eJ1939ApiSPType_INTEGER,
  eJ1939ApiSPType_BITFIELD,
  eJ1939ApiSPType_ASCII,
  eJ1939ApiSPType_BINARY,
  eJ1939ApiSPType_BLOB
};
#else
#define     J1939ApiProtocol_J1939            0
#define     J1939ApiProtocol_CAN              1

#define     J3939ApiCommandId_Reset                   0
#define     J3939ApiCommandId_Timeout                 1
#define     J3939ApiCommandId_FilterCAN               2
#define     J3939ApiCommandId_FilterJ1939             3
#define     J3939ApiCommandId_SwitchTP                4
#define     J3939ApiCommandId_ProtectAddr             5
#define     J3939ApiCommandId_ReleaseAddr             6
#define     J3939ApiCommandId_FilterModeSniffingJ1939 7
#define     J3939ApiCommandId_SniffingJ1939           8

#define     eJ1939ApiSPType_INVALID           0
#define     eJ1939ApiSPType_FLOAT             1
#define     eJ1939ApiSPType_INTEGER           2
#define     eJ1939ApiSPType_BITFIELD          3
#define     eJ1939ApiSPType_ASCII             4
#define     eJ1939ApiSPType_BINARY            5
#define     eJ1939ApiSPType_BLOB              6
#endif


/*************************************************************************
** constants and macros
*************************************************************************/

/** J1939API_MAX_MSG_SIZE:
    Specifies the maximum number of payload bytes per J1939 API message. */
#define     J1939API_MAX_MSG_SIZE          1785

/** J1939API_MAX_PARAM_COUNT:
    Specifies the maximum number of allowable parameters per PGN. */
#define     J1939API_MAX_PARAM_COUNT       1785

/** J1939API_MAX_PGN:
    Specifies the highest possible PGN. */
#define     J1939API_MAX_PGN            0x1FFFF

/** J1939API_PGN_ALL:
    Specifies that all PGNs should be registered with the stack (open filter). */
#define     J1939API_PGN_ALL         0xFFFFFFFF

/** J1939API_PARAM_MAX_NAMELEN:
    Specifies the maximum string length for a parameter name. */
#define     J1939API_PARAM_MAX_NAMELEN      100

/** J1939API_PARAM_MAX_UNITLEN:
    Specifies the maximum string length for a parameter unit. */
#define     J1939API_PARAM_MAX_UNITLEN       10

/** J1939API_MAX_BOARDS:
    Specifies the maximum number of boards supported. */
#define     J1939API_MAX_BOARDS               4

/** J1939API_MAX_CHANNELS:
    Specifies the maximum number of CAN controllers per board. */
#define     J1939API_MAX_CHANNELS             2

/** J1939API_BOARD_NAME_LEN:
    Specifies th maximum length of the {J1939API_BOARDINFO} name string. */
#define     J1939API_BOARD_NAME_LEN         100

/** J1939API_J1939MSG_MIN:
    Specifies the minimum size of {J1939API_J1939MSG} for J1939 data. */
#define     J1939API_J1939MSG_MIN            16

/** J1939API_CANMSG_MIN:
    Specifies the minimum size of {J1939API_CANMSG} for CAN data. */
#define     J1939API_CANMSG_MIN              12

/** J1939API_FLT_xxx:
    Selection which fields to be used for filtering on a CAN identifier using
    J1939 identifier schema.
    See {J1939API_COMMAND_SETFILTERFORSNIFFINGJ1939}->bFltFlag
    Note: Values of #defines used from RP1210 */
#define J1939API_FLT_PGN                     0x01 /* Filter on PGN */
#define J1939API_FLT_SRC                     0x04 /* Filter on source */
#define J1939API_FLT_DST                     0x08 /* Filter on destination */

/** J1939API_FLTTYPE_xxx:
    Selection of filter type to be configured.
    see {J1939API_COMMAND_SETFILTERTYPE}->bFltType */
#define J1939API_FLTTYPE_SNIFFERJ1939      1   /* J1939 sniffer filter */

/** J1939API_FLTMODE_xxx:
    Selection of the filter mode.
    See {J1939API_COMMAND_SETFILTERTYPE}->bFltMode */
#define J1939API_FLTMODE_INC                 0x00  /* FilterMode, inclusive */
#define J1939API_FLTMODE_EXC                 0x01  /* FilterMode, exclusive */
#define J1939API_FLTMODE_ALL                 0x02  /* FilterMode, all. For e.g. 1939 filter => all 29-bit messages */

/** J1939API_J1939MSG_TYPE_xxx:
    Indication from which filter the message was received.
    see {J1939API_J1939MSG}->bType */
#define J1939API_J1939MSG_TYPE_FILTERJ1939    0  /* Configured by means of {J3939ApiCommandId_FilterJ1939} */
#define J1939API_J1939MSG_TYPE_SNIFFINGJ1939  1  /* Configured by means of {J3939ApiCommandId_SniffingJ1939} */


/*************************************************************************
** data types
*************************************************************************/
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__GNUC__)
  #pragma pack(push, 1)       //  Start of byte alignment
#endif

#ifndef __PACKED__
  #if defined __GNUC__
  #define __PACKED__ __attribute__((packed))
  #else
  #define __PACKED__
  #endif
#endif


/** J1939API_BOARDINFO:
    Structured data type that contains data of an available IXXAT CAN interface
    board. _
    To be used with {J1939Api_GetBoardInfo()} argument ``*pcBoardInfo`` */
typedef struct _J1939API_BOARDINFO
{
  CHAR    guidBoardtype[16];  /* Type of IXXAT CAN interface board
                                 acc.to vciguid.h */
  CHAR    guidBoardID[16];    /* Unique global identifier of the IXXAT
                                 CAN interface board */
  UINT8   cntCAN;             /* Number of CAN controllers provided by
                                 the IXXAT CAN interface board */
  UINT8   bFeatures;          /* Feature flags of the IXXAT CAN interface
                                 board */
  UINT16  wFeatures;          /* Additional feature flags of the IXXAT CAN
                                 interface board */
  CHAR    acSerial[20];       /* Serial number of the IXXAT
                                 CAN interface board */
  CHAR    acDescription[J1939API_BOARD_NAME_LEN]; /* Brief board
                                 description string */
} __PACKED__
J1939API_BOARDINFO, *PJ1939API_BOARDINFO;


/** J1939API_J1939MSG:
    Structured data type that contains all J1939 protocol message parameters
    for the transmission and reception of up to {J1939API_MAX_MSG_SIZE} bytes. _
    To be used with {J1939Api_SendMessage()} argument ``*pcMessage`` _
    To be used with {J1939Api_ReceiveMessage()} argument ``*pcMessage`` */
typedef struct _J1939API_J1939MSG
{
  UINT32  dwTimestamp;        /* Time of message reception.
                                 In case of messages with more than
                                 eight data bytes, the timestamp field
                                 contains the time when the last data packet was
                                 received. */
  UINT32  dwPgn;              /* Parameter group number in little endian
                                 format */
  UINT8   bPriority;          /* Message priority (only the lower three
                                 bits are used) */
  UINT8   bSourceAddress;     /* Originating node address. If an address
                                 is used that has not be claimed, the API
                                 still sends the message. */
  UINT8   bDestinationAddress;/* The address of the node for which the
                                 message is bound */
  UINT8   bType;              /* Only for receive messages:
                                 Indication from which filter the message was received.
                                 J1939API_J1939MSG_TYPE_FILTERJ1939: Set by means of command
                                 J3939ApiCommandId_FilterJ1939.
                                 J1939API_J1939MSG_TYPE_SNIFFINGJ1939: Set by means of command
                                 J3939ApiCommandId_SniffingJ1939. */
  UINT16  wDataLen;           /* Number of valid bytes to follow,
                                 used length of data buffer abData */
  UINT16  wRes;               /* UINT32 alignment */
  UINT8   abData[J1939API_MAX_MSG_SIZE]; /* The data must be provided in
                                 raw format (as it shall be transferred on
                                 the bus). To pack signals into the data
                                 field, the functions J1939Api_WriteSignal()
                                 and J1939Api_WriteString() can be used.
                                 To unpack signals from the data field,
                                 the functions J1939Api_ReadSignal() and
                                 J1939Api_ReadString() can be used. */
} __PACKED__
J1939API_J1939MSG, *PJ1939API_J1939MSG;


/** J1939API_CANMSG:
    Structured data type that contains a plain CAN message for the
    transmission resp reception of up to 8 bytes payload. */
typedef struct _J1939API_CANMSG
{
  UINT32  dwTimestamp;        /* Time of message reception */
  UINT32  dwIdentifier;       /* CAN identifier (11 bits resp. 29 bits) */
                              /* MSB 0 = Standard Frame Format (11-bit identifier)
                                     1 = Extended Frame Format (29-bit identifier) */
  UINT16  wDataLen;           /* Number of valid bytes to follow;
                                 used length of data buffer abData */
  UINT16  wRes;               /* UINT32 alignment */
  UINT8   abData[8];          /* Contains the data bytes of a CAN message */
} __PACKED__
J1939API_CANMSG, *PJ1939API_CANMSG;


/** J1939API_COMMAND_SETBLOCKINGTIMEOUT:
    Structured data type that contains command interface specific information. _
    To be used with {J1939Api_SendCommand()} argument ``*pcCommandBuffer`` */
typedef struct _J1939API_COMMAND_SETBLOCKINGTIMEOUT
{
  UINT32  dwTimeout;          /* Timeout time in milliseconds of a
                                 command or a message
                                 (0 = polling mode; 0xFFFFFFFF = infinite block) */
} __PACKED__
J1939API_COMMAND_SETBLOCKINGTIMEOUT, *PJ1939API_COMMAND_SETBLOCKINGTIMEOUT;


/** J1939API_COMMAND_SETFILTERFORCAN:
    Structured data type that contains command interface specific information. _
    To be used with {J1939Api_SendCommand()} argument ``*pcCommandBuffer`` */
typedef struct _J1939API_COMMAND_SETFILTERFORCAN
{
  UINT8   bFrameFormat;       /* 0 = Standard Frame Format (11-bit identifier)
                                 1 = Extended Frame Format (29-bit identifier) */
  UINT32  dwMask;             /* Indicates which bits of the identifier need to
                                 be matched. “1” means that the value of the
                                 bit is relevant; “0” means that the value is
                                 irrelevant. */
  UINT32  dwCode;             /* Indicates what value is required for each bit
                                 of interest. */
} __PACKED__
J1939API_COMMAND_SETFILTERFORCAN, *PJ1939API_COMMAND_SETFILTERFORCAN;


/** J1939API_COMMAND_SETFILTERFORJ1939:
    Structured data type that contains command interface specific information. _
    To be used with {J1939Api_SendCommand()} argument ``*pcCommandBuffer`` */
typedef struct _J1939API_COMMAND_SETFILTERFORJ1939
{
  UINT32  abList[250];        /* List of up to 250 PGNs to be used
                                 as inclusive filter. */
}
J1939API_COMMAND_SETFILTERFORJ1939, *PJ1939API_COMMAND_SETFILTERFORJ1939;


/** J1939API_COMMAND_SETTRANSPORTPROTOCOL:
    Structured data type that contains command interface specific information. _
    To be used with {J1939Api_SendCommand()} argument ``*pcCommandBuffer`` */
typedef struct _J1939API_COMMAND_SETTRANSPORTPROTOCOL
{
  UINT8   bSwitch;            /* 0 = The transport protocol is deactivated.
                                 1 = The transport protocol is activated. */
} __PACKED__
J1939API_COMMAND_SETTRANSPORTPROTOCOL, *PJ1939API_COMMAND_SETTRANSPORTPROTOCOL;


/** J1939API_COMMAND_PROTECTJ1939ADDRESS:
    Structured data type containing command interface specific information. _
    To be used with {J1939Api_SendCommand()} argument ``*pcCommandBuffer`` */
typedef struct _J1939API_COMMAND_PROTECTJ1939ADDRESS
{
  UINT8   bToClaim;           /* 8-bit address from the address range 0-253
                                 that the application attempts to
                                 claim and protect on the J1939 bus */
  CHAR    acDeviceName[8];    /* 8-byte device name of a controller application,
                                 that must be compliance with the J1939 network
                                 management standard. */
} __PACKED__
J1939API_COMMAND_PROTECTJ1939ADDRESS, *PJ1939API_COMMAND_PROTECTJ1939ADDRESS;


/** J1939API_COMMAND_RELEASEJ1939ADDRESS:
    Structured data type that contains command interface specific information. _
    To be used with {J1939Api_SendCommand()} argument ``*pcCommandBuffer`` */
typedef struct _J1939API_COMMAND_RELEASEJ1939ADDRESS
{
  UINT8   bToRelease;           /* 8-bit address from the address range 0-253
                                   that the application attempts to release on
                                   the J1939 bus. */
} __PACKED__
J1939API_COMMAND_RELEASEJ1939ADDRESS, *PJ1939API_COMMAND_RELEASEJ1939ADDRESS;


/** J1939API_COMMAND_SETFILTERMODEFORSNIFFINGJ1939:
Structured data type that contains command interface specific information. _
To be used with {J1939Api_SendCommand()} argument ``*pcCommandBuffer`` */
typedef struct _J1939API_COMMAND_SETFILTERMODEFORSNIFFINGJ1939
{
  UINT8   bFltMode;  /* Selects the filter mode.
                        - J1939API_FLTMODE_INC: FilterMode, inclusive
                        - J1939API_FLTMODE_EXC: FilterMode, exclusive
                        - J1939API_FLTMODE_ALL: FilterMode, all.
                          For e.g. SNIFFER 1939 filter => all 29-bit messages */
} __PACKED__
J1939API_COMMAND_SETFILTERMODEFORSNIFFINGJ1939, *PJ1939API_COMMAND_SETFILTERMODEFORSNIFFINGJ1939;


/** J1939API_COMMAND_SETFILTERFORSNIFFINGJ1939:
Structured data type that contains command interface specific information. _
To be used with {J1939Api_SendCommand()} argument ``*pcCommandBuffer`` */
typedef struct _J1939API_COMMAND_SETFILTERFORSNIFFINGJ1939
{
  UINT8   bFltFlag;   /* Select fields to be used for filtering. Can be logically OR'd.
                         J1939API_FLT_PGN  - use PGN
                                            PDU format <= 239: only upper 10 bit used (0x3FF00)
                                            remaining bit's (destination address shall be zero).
                                            PDU format >= 240: 18bit used (0x3FFFF)
                         J1939API_FLT_SRC  - use Source address
                         J1939API_FLT_DST  - use Destination address (PDU Format <= 239) */
  UINT32  dwPgn;      /* PGN to be filtered, only used when J1939API_FLT_PGN set */
  UINT8   bSrc;       /* Source address, only when J1939API_FLT_SRC set */
  UINT8   bDst;       /* Destination address, only when J1939API_FLT_DST set.
                         When additionally J1939API_FLT_PGN is set, PDU Format shall be
                         <= 239 */
} __PACKED__
J1939API_COMMAND_SETFILTERFORSNIFFINGJ1939, *PJ1939API_COMMAND_SETFILTERFORSNIFFINGJ1939;


/** J1939API_SIGNALATTRIBUTES:
    Structured data type that contains relevant J1939 SP attributes. _
    To be used with {J1939Api_GetSignalAttributes()} argument ``*pcAttributes`` */
typedef struct _J1939API_SIGNALATTRIBUTES
{
  UINT8   bType;                /* Type of signal (Integer, ASCII, Bit Field,
                                   etc.), see {eJ1939ApiSPType} */
  double  dbResolution;         /* Value resolution of signal */
  double  dbOffset;             /* Value offset of signal */
  double  dbValueMin;           /* Minimum allowed value of signal */
  double  dbValueMax;           /* Maximum allowed value of signal */
  char    acUnit[J1939API_PARAM_MAX_UNITLEN];
                                /* Unit of singal as string */
  char    acName[J1939API_PARAM_MAX_NAMELEN];
                                /* Name of signal as string */
} __PACKED__
J1939API_SIGNALATTRIBUTES, *PJ1939API_SIGNALATTRIBUTES;


/** J1939API_BITFIELDSTATE:
    Structured data type that contains relevant J1939 SP attributes. _
    To be used with {J1939Api_GetBitFieldState()} argument ``*pcDescription`` */
typedef struct _J1939API_BITFIELDSTATE
{
  char    acDescription[J1939API_PARAM_MAX_NAMELEN];
                                /* State description of the signal to a bit
                                   field value as string */
} __PACKED__
J1939API_BITFIELDSTATE, *PJ1939API_BITFIELDSTATE;


#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__GNUC__)
  #pragma pack(pop)           //  End of byte alignment
#endif


#endif // XATJ1939_TYPES_H
