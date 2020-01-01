#ifndef _CONTROLIC_M24SR04Y_NFC_H_
#define _CONTROLIC_M24SR04Y_NFC_H_


#define M24SR_DEBUG_MODE

#ifdef M24SR_DEBUG_MODE
#define M24DbgPrint printc
#else
#define M24DbgPrint
#endif



//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

typedef const unsigned char     uc8;
typedef const unsigned short    uc16;

#define GPIO_RF_DISABLE     MMP_GPIO24
#define GPIO_M24SR_I2C_SCL  MMP_GPIO0
#define GPIO_M24SR_I2C_SDA  MMP_GPIO1

#define NFC_DEVICE_ID   0x56
#define NFC_WRITE       0x0
#define NFC_READ        0x1
#define NFC_DELAY       0x4

#define I2C_SW_MODE     MMP_TRUE
#define I2C_HW_MODE     MMP_FALSE

//#define I2C_READ_ERROR  0xFFFF

#define I2C_CRC_SUCCESS 0x0000

#define M24SR_I2C_SUCCESS       0x9000
#define M24SR_I2C_FAIL          0xFFFC
#define M24SR_ERROR_PARAMETER   0xFFFD
#define M24SR_I2C_ACCESS_ERROR  0xFFFE
#define M24SR_I2C_CRC_ERROR     0xFFFF

#define M24SR_MAX_NDEF_FILE_SIZE 0x0200  // 512 bytes
#define M24SR_NEW_WRITE_PASSWORD_OFFSET (M24SR_MAX_NDEF_FILE_SIZE-4-32)
#define M24SR_CURRENT_WRITE_PASSWORD_OFFSET (M24SR_NEW_WRITE_PASSWORD_OFFSET+16)
#define M24SR_MAX_ACCESS_DATA_SIZE 0xF6


#define I2C_DEBUG
#ifdef I2C_DEBUG
    #define I2C_DBG_Str(x) RTNA_DBG_Str(0,x);
#else
    #define I2C_DBG_Str(x)
#endif

#define GETMSB(val)     ( (MMP_UBYTE)((val & 0xFF00)>>8) ) 
#define GETLSB(val)     ( (MMP_UBYTE)(val & 0x00FF) ) 
#define TOGGLE(val)     ( (val != 0x00)? 0x00 : 0x01 )
 
/* ---------------------- status code ----------------------------------------*/
#define M24SR_ACTION_COMPLETED              0x9000
#define UB_STATUS_OFFSET                    4
#define LB_STATUS_OFFSET                    3

#define M24SR_NBBYTE_INVALID                0xFFFE
 
/*-------------------------- File Identifier ---------------------------------*/	 
#define SYSTEM_FILE_ID                      0xE101
#define CC_FILE_ID                          0xE103
#define NDEF_FILE_ID                        0x0001

/*-------------------------- Password Management -----------------------------*/
#define READ_PWD                            0x0001
#define WRITE_PWD                           0x0002
#define I2C_PWD                             0x0003

/*-------------------------- Verify command answer ----------------------------*/
#define M24SR_PWD_NOT_NEEDE                 0x9000
#define M24SR_PWD_NEEDED                    0x6300
#define M24SR_PWD_CORRECT                   0x9000


/* special M24SR command ----------------------------------------------------------------------*/	 
#define M24SR_OPENSESSION                   0x26
#define M24SR_KILLSESSION                   0x52
 
/*  Length  ----------------------------------------------------------------------------------*/
#define M24SR_STATUS_NBBYTE                 2
#define M24SR_CRC_NBBYTE                    2
#define M24SR_STATUSRESPONSE_NBBYTE         5
#define M24SR_UPDATE_COMMAND_NBBYTE         8
#define M24SR_DESELECTREQUEST_NBBYTE        3
#define M24SR_DESELECTRESPONSE_NBBYTE       3
#define M24SR_WATINGTIMEEXTRESPONSE_NBBYTE  4
#define M24SR_PASSWORD_NBBYTE               0x10

#define M24SR_TX_DATA_LENGTH (16 - M24SR_UPDATE_COMMAND_NBBYTE)
#define M24SR_RX_DATA_LENGTH (I2CM_RX_FIFO_DEPTH - M24SR_STATUSRESPONSE_NBBYTE)

/*  Command structure   ------------------------------------------------------------------------*/
#define M24SR_CMDSTRUCT_SELECTAPPLICATION       0x01FF
#define M24SR_CMDSTRUCT_SELECTCCFILE            0x017F
#define M24SR_CMDSTRUCT_SELECTNDEFFILE          0x017F
#define M24SR_CMDSTRUCT_READBINARY              0x019F
#define M24SR_CMDSTRUCT_UPDATEBINARY            0x017F
#define M24SR_CMDSTRUCT_VERIFYBINARYWOPWD       0x013F
#define M24SR_CMDSTRUCT_VERIFYBINARYWITHPWD     0x017F
#define M24SR_CMDSTRUCT_CHANGEREFDATA           0x017F
#define M24SR_CMDSTRUCT_ENABLEVERIFREQ          0x011F
#define M24SR_CMDSTRUCT_DISABLEVERIFREQ         0x011F
#define M24SR_CMDSTRUCT_SENDINTERRUPT           0x013F
#define M24SR_CMDSTRUCT_GPOSTATE                0x017F

/*  Command structure Mask -------------------------------------------------------------------*/
#define M24SR_PCB_NEEDED                    0x0001  /* PCB byte present or not */
#define M24SR_CLA_NEEDED                    0x0002  /* CLA byte present or not */
#define M24SR_INS_NEEDED                    0x0004  /* Operation code present or not*/ 
#define M24SR_P1_NEEDED                     0x0008  /* Selection Mode  present or not*/
#define M24SR_P2_NEEDED                     0x0010  /* Selection Option present or not*/
#define M24SR_LC_NEEDED                     0x0020  /* Data field length byte present or not */
#define M24SR_DATA_NEEDED                   0x0040  /* Data present or not */
#define M24SR_LE_NEEDED                     0x0080  /* Expected length present or not */
#define M24SR_CRC_NEEDED                    0x0100  /* 2 CRC bytes present	or not */

#define M24SR_DID_NEEDED                    0x08    /* DID byte present or not */

/*  Offset ----------------------------------------------------------------------------------*/
#define M24SR_OFFSET_PCB                    0
#define M24SR_OFFSET_CLASS                  1
#define M24SR_OFFSET_INS                    2
#define M24SR_OFFSET_P                      3


/*  mask ------------------------------------------------------------------------------------*/
#define M24SR_MASK_BLOCK                    0xC0
#define M24SR_MASK_IBLOCK                   0x00
#define M24SR_MASK_RBLOCK                   0x80
#define M24SR_MASK_SBLOCK                   0xC0


/* APDU Command: class list -------------------------------------------*/
#define C_APDU_CLA_DEFAULT                  0x00
#define C_APDU_CLA_ST                       0xA2

/*------------------------ Data Area Management Commands ---------------------*/
#define C_APDU_SELECT_FILE                  0xA4
#define C_APDU_GET_RESPONCE                 0xC0
#define C_APDU_STATUS                       0xF2
#define C_APDU_UPDATE_BINARY                0xD6
#define C_APDU_READ_BINARY                  0xB0
#define C_APDU_WRITE_BINARY                 0xD0
#define C_APDU_UPDATE_RECORD                0xDC
#define C_APDU_READ_RECORD                  0xB2

/*-------------------------- Safety Management Commands ----------------------*/
#define C_APDU_VERIFY                       0x20
#define C_APDU_CHANGE                       0x24
#define C_APDU_DISABLE                      0x26
#define C_APDU_ENABLE                       0x28

/*-------------------------- Gpio Management Commands ------------------------*/
#define C_APDU_INTERRUPT                    0xD6


#define M24SR_STATUS_SUCCESS				0x0000
#define M24SR_ERROR_DEFAULT				    0x0010


//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

/* APDU-Header command structure ---------------------------------------------*/
typedef struct
{
    MMP_UBYTE CLA;  /* Command class */
    MMP_UBYTE INS;  /* Operation code */
    MMP_UBYTE P1;   /* Selection Mode */
    MMP_UBYTE P2;   /* Selection Option */
} C_APDU_Header;

/* APDU-Body command structure -----------------------------------------------*/
typedef struct 
{
    MMP_UBYTE LC;       /* Data field length */
    MMP_UBYTE *pData ;  /* Command parameters */ 
    MMP_UBYTE LE;       /* Expected length of data to be returned */
} C_APDU_Body;

/* APDU Command structure ----------------------------------------------------*/
typedef struct
{
    C_APDU_Header Header;
    C_APDU_Body   Body;
} C_APDU;

/* SC response structure -----------------------------------------------------*/
typedef struct
{
  MMP_UBYTE *pData ;  /* Data returned from the card */ // pointer on the transceiver buffer = ReaderRecBuf[CR95HF_DATA_OFFSET ];
  MMP_UBYTE SW1;      /* Command Processing status */
  MMP_UBYTE SW2;      /* Command Processing qualification */
} R_APDU;

/* GPO mode structure -------------------------------------------------------*/
typedef enum{
    RF_GPO= 0,
    I2C_GPO
}M24SR_GPO_MODE;

/* GPO state structure -------------------------------------------------------*/
typedef enum{
    HIGH_IMPEDANCE= 0,
    SESSION_OPENED,
    WIP,
    I2C_ANSWER_READY,
    INTERRUPT,
    STATE_CONTROL,
    RF_BUSY
}M24SR_GPO_MGMT;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
void MonitorNfcFunc( char* szParam );

#endif
