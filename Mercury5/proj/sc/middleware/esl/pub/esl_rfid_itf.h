/**
 *
 * @file    esl_RFID_itf.h
 *
 * @brief   This module defines the Enhanced Service Layer interafce of RFID service
 *
 * @author  Ian-Y Chen
 * @version $Id: esl_rfid_itf.h 4669 2009-07-08 07:28:12Z ian-y.chen $
 *
 */
#ifndef __ESL_RFID_ITF_H__
#define __ESL_RFID_ITF_H__

#include "vm_types.ht"

//#ifdef __RFID__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_RFID_ITF__
#define DefExtern
#else
#define DefExtern extern
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/
//#ifdef __USE_MSR3110__
#define RFID_FWU_SECTOR_ERASE_START_ADDR 	(0x00000000)
#define RFID_FWU_SECTOR_ERASE_STOP_ADDR 	(0x0001F000)
#define RFID_FWU_SECTOR_ERASE_SIZE 			(0x00001000)
#define RFID_FWU_WRITE_START_ADDR (0x00000000)
#define RFID_FWU_WRITE_STOP_ADDR (0x0001FF80)
#define RFID_FWU_WRITE_SIZE (0x80)
//#endif


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
typedef enum
{
	ESL_RFID_OPEN_CMD,
	ESL_RFID_CLOSE_CMD,
	ESL_RFID_READ_CMD,
	ESL_RFID_WRITE_CMD,
	ESL_RFID_GET_READER_INFO_CMD,
	ESL_RFID_UPGRADE_CMD,
	ESL_RFID_SIM_SWITCH_CMD,

#ifdef __BARCODE__
	ESL_BARCODE_READ_CMD,
#endif	//__BARCODE__

	ESL_RFID_GPS_OPERATION,
	ESL_RFID_LOCK_TAG_CMD,
	ESL_RFID_MF_CMD,

#ifdef __SUPPORT_JSR257__
	ESL_RFID_ADD_NDEF_LISTENER_CMD,
	ESL_RFID_REMOVE_NDEF_LISTENER_CMD,
	ESL_RFID_ADD_TARGET_LISTENER_CMD,
	ESL_RFID_REMOVE_TARGET_LISTENER_CMD,
	ESL_RFID_OPEN_CONNECTION_CMD,
	ESL_RFID_CLOSE_CONNECTION_CMD,
	ESL_RFID_WRITE_NDEF_CMD,
	ESL_RFID_READ_NDEF_CMD,
	ESL_RFID_ISO443_EXCHANGE_DATA_CMD,
	ESL_RFID_TRANSCEIVE_CMD,
	ESL_RFID_AUTO_SCAN,
#endif	//__SUPPORT_JSR257__

	ESL_RFID_CMD_MAX
} esl_RFID_CmdReqType_et;
/**
 *  @brief RFID error code
 */
typedef enum {
    ESL_RFID_OK,                /**< Function complete successfully */
    ESL_RFID_FAIL,              /**< Function common error          */
    ESL_RFID_PARAM_ERROR,       /**< The input parameter is wrong   */
    ESL_RFID_MEM_ALLOC_ERROR,   /**< Can't allocate memory from OS  */
    ESL_RFID_REJECT,            /**< Request reject because of other function's confliction */
    ESL_RFID_ABORT,             /**< Request abort because of incorrect sequence            */
    ESL_RFID_TIMEOUT,           /**< Request no response timeout,this error is returned by call back function  */
    ESL_RFID_RECORD_INDEX_USED, /**< Request Index duplication */
    ESL_RFID_OUT_OF_CAPACITY    /**< Out of Tag Memory Capacity */
} esl_RFID_ErrCode_e;

/**
 *  @brief RFID Module type
 */
typedef enum
{
	ESL_MSR3110,
	ESL_MSR3320,
	ESL_MSR3330,

#ifdef __BARCODE__
	ESL_BARCODE_MODULE, //barcode reader
#endif	//__BARCODE__

	ESL_NO_SPECIFIED,
} esl_RFID_Module_Type_et;

/**
 *  @brief RFID type
 */
typedef enum {
    ESL_RFID_TYPE_ALL = 0,          /**< All supported tags */
    ESL_RFID_TYPE_ISO15693,         /**< ISO15693 type */
    ESL_RFID_TYPE_C1G2,             /**< C1G2 type     */
    ESL_RFID_TYPE_ISO15693_MSTAR,   /**< ISO15693 MStar proprietary */
    ESL_RFID_TYPE_C1G2_MSTAR,       /**< C1G2 MStar proprietary */
    ESL_RFID_TYPE_ISO14443A,        /**< ISO14443A type */
    ESL_RFID_TYPE_ISO14443A_MF4K,        /**< ISO14443A MF4K type */
    ESL_RFID_TYPE_ISO14443A_MF1K,        /**< ISO14443A MF1K type */
    ESL_RFID_TYPE_ISO14443A_UL,         /**< ISO14443A MF_UL type */
    ESL_RFID_TYPE_ISO14443_4A,        /**< ISO14443_4A type */
    ESL_RFID_TYPE_ISO14443A_TOPAZ,  /**< ISO14443A TOPAZ/JEWEL */
    ESL_RFID_TYPE_ISO14443B,        /**< ISO14443B type */
    ESL_RFID_TYPE_ISO14443B_AT88RF04C,        /**< ISO14443B ATMEL  AT88RF04C*/
    ESL_RFID_TYPE_ISO14443B_AT88SC0808CRF,        /**< ISO14443B ATMEL  AT88SC0808CRF*/
    ESL_RFID_TYPE_ISO14443B_AT88SC1616CRF,        /**< ISO14443B ATMEL  AT88SC1616CRF*/
    ESL_RFID_TYPE_ISO14443B_AT88SC3216CRF,        /**< ISO14443B ATMEL  AT88SC3216CRF*/
    ESL_RFID_TYPE_ISO14443B_AT88SC6416CRF,        /**< ISO14443B ATMEL  AT88SC6416CRF*/
    ESL_RFID_TYPE_ST14443B,         /**< ST14443B type  (Boli Add)*/
    ESL_RFID_TYPE_ISO14443_4B,        /**< ISO14443_4B type */
    ESL_RFID_TYPE_UNKNOWN,           /**< Unknown media type */
    ESL_RFID_TYPE_TOTAL
} esl_RFID_TagType_e;

/**
 *  @brief RFID memory type
 */
typedef enum {
    ESL_RFID_MEM_TYPE_RESERVED = 0, /**< reserved */
    ESL_RFID_MEM_TYPE_EPC,          /**< EPC type  */
    ESL_RFID_MEM_TYPE_TID,          /**< TID type  */
    ESL_RFID_MEM_TYPE_USER,         /**< USER type */
    ESL_RFID_MEM_TYPE_UNKNOWN       /**< Unknown media type */
} esl_RFID_MemType_e;

/**
 *  @brief RFID scan type
 */
typedef enum {
    ESL_RFID_SCAN_ONCE = 0,         /**< Once Scan   */
    ESL_RFID_SCAN_REPEAT,           /**< Repeat Scan */
    ESL_RFID_SCAN_UNKNOWN           /**< Unknown mode */
} esl_RFID_ScanMode_e;

/**
 *  @brief RFID block size
 */
typedef enum {
    ESL_RFID_BLOCK_2_BYTE = 0,      /**< 2-byte block */
    ESL_RFID_BLOCK_4_BYTE,          /**< 4-byte block  */
    ESL_RFID_BLOCK_16_BYTE,          /**< 16-byte block  */
    ESL_RFID_BLOCK_UNKNOWN          /**< Unknown block */
} esl_RFID_BlockSize_e;


/**
 *  @brief RFID SIM Switch choice
 */
typedef enum {
    ESL_RFID_SIM2_CTRL_BY_PHONE = 0,
    ESL_RFID_SIM2_CTRL_BY_RFID_MODULE,

	ESL_RFID_SIM2_CTRL_MAX,
} esl_SIM_Switch_e;

typedef enum {
    ESL_RFID_GET_SIMSWITCH,
	ESL_RFID_SET_SIMSWITCH,
} esl_SIM_Switch_Action_e;

/**
 *  @brief RFID Upgrade firmware operation
 */
typedef enum {
    ESL_RFID_UPGRADE_FW_PRE_CONDITION = 0,
    ESL_RFID_UPGRADE_FW_SECTOR_ERASE,
    ESL_RFID_UPGRADE_FW_WRITE,
    ESL_RFID_UPGRADE_FW_POST_CONDITION,
    ESL_RFID_UPGRADE_FW_SPEED_OPTIMIZE,
} esl_Upgrade_Firmware_OP_e;

typedef enum {
	ESL_RFID_WRITE_PWD_CMD		= 0,
	ESL_RFID_LOCK_PWD_CMD		= 1
}esl_RFID_CmdId_e;

typedef enum {
	ESL_GPS_GETPOS		= 0,
}esl_GPS_Operation_e;

/**
 *  @brief Mstar Tag Model ID
 */
typedef enum
{
    ESL_RFID_TAG_MSR3200 = 0,            /* MStar Lyra Series */
    ESL_RFID_TAG_MSR3260,                /* MStar Pavo Series */
    ESL_RFID_TAG_UNKNOWN,                /* UNKNOWN */
    ESL_RFID_TAG_MODEL_MAX               /*  */
} esl_RFID_Tag_Model_et;

/**
 *  @brief RFID MStar ISO15693 Custom Command Category
 */
typedef enum
{
    ESL_RFID_CUS_EAS = 0,            /* EAS Related Operation */
    ESL_RFID_CUS_SECURED_RW,         /* Secured Read / Write */
    ESL_RFID_CUS_PWD,                /* Password Setting */
    ESL_RFID_CUS_MAX                 /*  */
} esl_RFID_Cus_Category_et;


typedef enum {
	ESL_RFID_MF_CMD_AUTH			= 0,
	ESL_RFID_MF_CMD_INCREMENT	= 1,
	ESL_RFID_MF_CMD_DECREMENT	= 2,
	ESL_RFID_MF_CMD_TRANSFER	= 3,
	ESL_RFID_MF_CMD_RESTORE		= 4
}esl_RFID_MFCmdId_e;

typedef enum {
	ESL_RFID_MF_KEYA				= 0,
	ESL_RFID_MF_KEYB				= 1
}esl_RFID_MFKey_e;

typedef enum {
    // Search Tag
    MF_ST_ONE_TAG_FOUND = 0,
    MF_ST_TAG_NOT_MF_CLASSIC,
    MF_ST_NO_TAG_FOUND,
    MF_ST_MORE_THAN_ONE_TAG_FOUND,

    // Authentication
    MF_AU_OK,
    MF_AU_NO_TAG_TIMEOUT_FOR_RB,
    MF_AU_FAIL_TIMEOUT_FOR_TOKENBA,
    MF_AU_FAIL_WRONG_TOKENBA,
    MF_AU_OTHER_THAN_KEYA_KEYB,

    // Write
    MF_WR_OK,
    MF_WR_NO_TAG_TIMEOUT_FOR_1ST_ACK,
    MF_WR_FAIL_1ST_NACK_NOT_ALLOW,
    MF_WR_FAIL_1ST_NACK_TRANSMISSION_ERROR,
    MF_WR_FAIL_TIMEOUT_FOR_2ND_ACK,
    MF_WR_FAIL_2ND_NACK_NOT_ALLOW,
    MF_WR_FAIL_2ND_NACK_TRANSMISSION_ERROR,

    // Read
    MF_RD_OK,
    MF_RD_NO_TAG_TIMEOUT,
    MF_RD_FAIL_GOT_ACK,
    MF_RD_FAIL_NACK_NOT_ALLOW,
    MF_RD_FAIL_NACK_TRANSMISSION_ERROR,
    MF_RD_FAIL_WRONG_LENGTH,
    MF_RD_FAIL_WRONG_PARITY,
    MF_RD_FAIL_WRONG_CRC,

    // Increment/Decrement/Restore/Transfer (Value OP)
    MF_VP_OK,
    MF_VP_NO_TAG_TIMEOUT_FOR_1ST_ACK,
    MF_VP_FAIL_1ST_NACK_NOT_ALLOW,
    MF_VP_FAIL_1ST_NACK_TRANSMISSION_ERROR,

    // Halt
    MF_HT_OK,

    MF_UNEXPECTED_STATUS
}esl_RFID_MFStatus_e;




/**
 *  @brief RFID tag ID
 */
typedef struct {
    u8  uid[12];                    /**< Tag UID      */
} esl_RFID_TagId_t;

typedef struct
{
    u8  pwd[8];
} esl_RFID_Pwd_t;

typedef struct {
    u8  key[8];
}esl_RFID_MFKey_t;

/**
 *  @brief RFID Check tag expiration date parameter
 */
typedef struct {
    u16                  year;         /**< Reader date - year */
    u8                   month;        /**< Reader date - month  [1 .. 12] */
    u8                   day;          /**< Reader date - day    [1 .. 31] */
    u8                   hour;         /**< Reader date - hour   [0 .. 23] */
    u8                   minute;       /**< Reader date - minute [0 .. 59] */
    u8                   second;       /**< Reader date - second [0 .. 59] */
} esl_RFID_Date_t;

/**
 *  @brief RFID tag info
 */
typedef struct {
    esl_RFID_TagType_e       type;        /**< Tag type     */
    u8                    tagIdLen;    /**< Tag UID length */
    esl_RFID_TagId_t      tagId;       /**< Tag UID      */
    u16                   blockNum;    /**< Block number */
    esl_RFID_BlockSize_e  blockSize;   /**< Block size in byte */
    u8                    S43A_SAK;
    u16                   S43A_ATQA;
    u8                    AT43B_APP3;  /**<For ATMEL 43B use> */
    u8                    S43B_Param;    /**< For ATMEL 43B use > */
} esl_RFID_TagInfo_t;

/**
 *  @brief RFID start parameters
 */
typedef struct {
    esl_RFID_TagType_e      type;         /**< RFID type            */
    esl_RFID_ScanMode_e  scanMode;     /**< Scan mode            */
    u32                  repeatTime;   /**< repeat scanning time (ms) (only for repeat scan)    */
    u16                  maxIdSize;    /**< Max number of Tag ID */
    esl_RFID_TagInfo_t  *pTagInfo;     /**< Tag ID pointer arry  */
} esl_RFID_StartConfig_t;

/**
 *  @brief RFID Read parameter
 */
typedef struct {
    esl_RFID_TagType_e      type;        /**< RFID type */
    esl_RFID_TagId_t      	tagId;       /**< Tag UID              */
    esl_RFID_MemType_e    	memType;     /**< memory type          */
    esl_RFID_BlockSize_e  	blockSize;   /**< block size in byte   */
    u16                   	memAddr;     /**< memory address,block ID       */
    u16                   	length;      /**< memory read length (= buffer length) */
    u8                   	*pBuff;       /**< Buffer for data read */
    u8                    	S43B_Param;
    u8						padding[3];

    /* ISO15693 MStar,  Valid, if Tag_Type = ESL_RFID_TYPE_ISO15693_MSTAR */
    struct
    {
        esl_RFID_Tag_Model_et    Tag_Model;      // In, Tag Model Name. Should be set if Tag_Type = ESL_RFID_TYPE_ISO15693_MSTAR
        esl_RFID_Cus_Category_et Cus_Category;   		// In,  Cus_Category = CUS_EAS ==> EAS Read
                                        		//      Cus_Category = CUS_SECURED_RW ==> Secured Read
                                        		//      Others, Not Support
        esl_RFID_Pwd_t PWD;                      // In, Password. If Cus_Category = CUS_SECURED_RW or CUS_PWD, PWD[8] should be set properly
    }Custom;

} esl_RFID_ReadParam_t;

/**
 *  @brief RFID Write parameter
 */
typedef struct {
    esl_RFID_TagType_e    	type;        /**< RFID type */
    esl_RFID_TagId_t      	tagId;       /**< Tag info              */
    esl_RFID_MemType_e    	memType;     /**< memory type           */
    esl_RFID_BlockSize_e  	blockSize;   /**< block size in byte    */

    u16                   	memAddr;     /**< memory address,block ID        */
    u16                   	length;      /**< memory write length (= buffer length) */
    u8                   	*pBuff;       /**< Buffer for data write */

    u8                    	S43B_Param;      /**< for ATMEL 43B > */
    u8						padding[3];

    /* ISO15693 MStar,  Valid, if Tag_Type = ESL_RFID_TYPE_ISO15693_MSTAR */
    struct
    {
        esl_RFID_Tag_Model_et    Tag_Model;      // In, Tag Model Name. Should be set if Tag_Type = ESL_RFID_TYPE_ISO15693_MSTAR
        esl_RFID_Cus_Category_et Cus_Category;   // In,  Cus_Category = CUS_EAS ==> EAS Write
			                                     //      Cus_Category = CUS_SECURED_RW ==> Secured Write
			                                     //      Others, Not Support
        esl_RFID_Pwd_t PWD;                      // In, Password. If Cus_Category = CUS_SECURED_RW or CUS_PWD, PWD[8] should be set properly
    }Custom;

} esl_RFID_WriteParam_t;


/**
 *  @brief RFID SIM switch parameter
 */
typedef struct {
	esl_SIM_Switch_Action_e Action;			/**< Set or Get SimSwitch*/
    esl_SIM_Switch_e    CtrlOwner;         /**< SIM2 is control by which one */
} esl_RFID_SIMSwitch_t;

/**
 *  @brief RFID media file information structure
 */
typedef struct {
    esl_RFID_Module_Type_et    ModuleType;         /**< RFIDModuleType */
} esl_RFID_ModuleInfo_t;

/**
 *  @brief RFID Upgrade firmware parameter
 */
typedef struct {
    esl_RFID_Module_Type_et          ModuleType;        /**< RFIDModuleType */
    esl_Upgrade_Firmware_OP_e    UpgradeOP;         /**< UpgradeOP */
    u32                          TargetAddr;        /**< Target address */
    u8                           *pData;
    u16                          Step;              /**< Upgrade step progress*/
    u8                           DataLen;           /**< Data length for upgrade */
    u8							 padding;
} esl_RFID_UpgradeParam_t;

typedef struct
{
	u16                   idLen;        /**< Reader ID length in bytes */
	u8                    id[32];       /**< Reader ID */
	u8                    FW_VERSION[11];  /**< Firmware Version */
}esl_RFID_GetReaderInfo_t;


#define	BARCODE_MAX_BYTE	(52)

typedef struct
{
	u8	readData[BARCODE_MAX_BYTE];	//read data
	u16	readLen;
    u8 	padding[2];
}esl_RFID_BarcodeParam_t;

#define	GPS_LONGITUDE_LEN	(20)
#define	GPS_LATITUDE_LEN	(20)
#define	GPS_SAT_COUNT_MAX	(12)
#define	GPS_HORIZON_MAX		(12)

typedef struct
{
	esl_GPS_Operation_e Op;
    u8 Longitude[GPS_LONGITUDE_LEN];
    u8 Latitude[GPS_LONGITUDE_LEN];
    u8 Satellite_Count[GPS_SAT_COUNT_MAX];
    u8 Horizontal_Precision[GPS_HORIZON_MAX];
    u8 NS;
    u8 EW;
    u8 GPS_Status;
    u8 padding;
}esl_RFID_GPSOperation_t;


/**
 *  @brief RFID Lock parameter
 */
typedef struct
{
    esl_RFID_TagType_e    type;        /**< RFID type */
    esl_RFID_TagId_t      tagId;       /**< Tag info              */

	/* Structure for Lock Command */
	struct
	{
	    u8 Kill_mask;
	    u8 Access_mask;
	    u8 EPC_mask;
	    u8 TID_mask;
	    u8 User_mask;
	    u8 Kill_action;
	    u8 Access_action;
	    u8 EPC_action;
	    u8 TID_action;
	    u8 User_action;
	    u8 Flag;
    	u8 padding;
	}C1G2;

    /* ISO15693 MStar,  Valid, if Tag_Type = ESL_RFID_TYPE_ISO15693_MSTAR */
    struct
    {
        esl_RFID_Tag_Model_et    Tag_Model;      // In, Tag Model Name. Should be set if Tag_Type = ESL_RFID_TYPE_ISO15693_MSTAR
        esl_RFID_Cus_Category_et Cus_Category;   // In,  Cus_Category = CUS_EAS ==> EAS Lock
                                        //      Cus_Category = CUS_PWD ==> PWD Lock
                                        //      Others, Not Support
    }Custom;

    /* ISO15693,  Valid, if Tag_Type = ESL_RFID_TYPE_ISO15693 */
    struct
    {
        u8 Block_ID;
    	u8 padding[3];
    }Std_693;

} esl_RFID_LockParam_t;


typedef struct
{
    esl_RFID_MFCmdId_e	cmdId;
    esl_RFID_TagId_t	tagId;
    esl_RFID_MFKey_e	authKey;
    esl_RFID_MFKey_t	keyBuf;
    esl_RFID_MFStatus_e	rspStatus;
    s32					value;
    u8					blockIdx;
    u8					padding[3];
}esl_RFID_MFCommand_t;

#ifdef __SUPPORT_JSR257__
typedef enum {
    ESL_RFID_TARGET_RESERVED = 0,	//43A, 43B
    ESL_RFID_TARGET_NDEF = 0x0001,	//43A, 43B
	ESL_RFID_TARGET_RFID = 0x0002,	//43A, 43B
	ESL_RFID_TARGET_ISO14443_CARD = 0x0004,	//no support
	ESL_RFID_TARGET_VISUAL_TAG = 0x0008,	//no support

} esl_RFID_TargetType_e;

#define NDEF_RT_MASK_EMPTY          0x01
#define NDEF_RT_MASK_NFC_FORUM_RTD  0x02
#define NDEF_RT_MASK_MIME           0x04
#define NDEF_RT_MASK_URI            0x08
#define NDEF_RT_MASK_EXTERNAL_RTD   0x10
#define NDEF_RT_MASK_UNKNOWN        0x20
#define NDEF_RT_MASK_UNCHANGED      0x40

typedef enum {
	ESL_RFID_LISTEN_NDEF,
	ESL_RFID_LISTEN_TARGET
}esl_RFID_ListenType_e;

#define	URL_NUM_MAX	(4)
#define	UID_MAX_LEN	(10)
#define	MAPPING_MAX_LEN	(20)
#define	URL_MAX_LEN	(128)

typedef struct
{
	u16		targetType;

    char	UIDStr[UID_MAX_LEN*2+4];
    u8		UID_Hex[UID_MAX_LEN+2];
    char	mapping[MAPPING_MAX_LEN+4];
    char	url[URL_NUM_MAX][URL_MAX_LEN+4];
    u8		urlLen[URL_NUM_MAX];
	u8		UIDStrLen;
	u8		UID_Len;
	u8		padding[2];
} esl_RFID_TagProperties_t;

#define	NDEF_DATA_LEN (152)
typedef struct
{
	u8	data[NDEF_DATA_LEN];
	u16	dataSize;
    u8	detectMask;	//NDEF_RT_MASK_EMPTY
    u8	padding;
}esl_RFID_NDEFListener_t;

typedef struct
{
	esl_RFID_TagProperties_t	*tagArray;
	u16							tagNum;
}esl_RFID_TargetListener_t;

typedef struct
{
	esl_RFID_ListenType_e	type;

	union
	{
		esl_RFID_NDEFListener_t		NDEF;
		esl_RFID_TargetListener_t	target;
	}data;

}esl_RFID_Listener_t;

typedef struct
{
	u8	typeBuf[NDEF_DATA_LEN];
	u16	typeLen;
	u8	NDEFTypeMask;	//NDEF_RT_MASK_EMPTY
    u8  RecordIndex; //this index should maintine by Upper Layer , 0~6 used by JAVA Please notice.
}esl_RFID_AddNDEFListener_t;

typedef struct
{
	u8	typeBuf[NDEF_DATA_LEN];
    u16	typeLen;
	u8	NDEFTypeMask;	//NDEF_RT_MASK_EMPTY
    u8  RecordIndex; //this index should maintine by Upper Layer
}esl_RFID_RemoveNDEFListener_t;

typedef struct
{
	esl_RFID_TargetType_e	targetType;
}esl_RFID_AddTargetListener_t;

typedef struct
{
	esl_RFID_TargetType_e	targetType;
}esl_RFID_RemoveTargetListener_t;

typedef struct
{
	//cmd
	esl_RFID_TargetType_e	targetType;
	u8*	url;

	//return
	void* handle;

	u16	urlLen;
    u8 padding[2];
}esl_RFID_OpenConnection_t;

typedef struct
{
	void*	handle;
}esl_RFID_CloseConnection_t;

typedef struct
{
	void*	handle;
	u8*		data;
	u16		dataSize;
    u8 		padding[2];
}esl_RFID_WriteNDEF_t;

typedef struct
{
	//cmd
	void*	handle;

	//return
	u8		data[NDEF_DATA_LEN];
	u16		dataSize;
    u8 		padding[2];
}esl_RFID_ReadNDEF_t;

typedef struct
{
	void*	handle;
	u8*		data;
	u16		dataSize;
    u8 		padding[2];
}esl_RFID_ISO443Exchange_t;

typedef struct
{
	void*	handle;
	u8*		data;
	u16		dataSize;
    u8 		padding[2];
}esl_RFID_Transceive_t;
#endif	/* __SUPPORT_JSR257__ */

typedef struct
{
	esl_RFID_CmdReqType_et		CmdRegType;
	esl_RFID_Module_Type_et		ModuleType;

	union
	{
		esl_RFID_StartConfig_t	tOpen; //RFID Reader Config
		esl_RFID_ModuleInfo_t	tRfidModuleInfo;	//Yenchih note:: migrate temp, need remove
		esl_RFID_ReadParam_t	tRead;
		esl_RFID_WriteParam_t	tWrite;
		esl_RFID_SIMSwitch_t	tRfidSimSwitch; //Sim Switch Parameter
		esl_RFID_UpgradeParam_t	tRfidUpgradeParam;

#ifdef __BARCODE__
		esl_RFID_BarcodeParam_t tBarcodeParam;	//barcode reader
#endif	//__BARCODE__

		esl_RFID_GPSOperation_t tGPS;
        esl_RFID_LockParam_t tLock;
		esl_RFID_MFCommand_t			tMFCmdParam;

#ifdef __SUPPORT_JSR257__
		esl_RFID_AddNDEFListener_t		tAddNDEFListener;
		esl_RFID_RemoveNDEFListener_t	tRemoveNDEFListener;
		esl_RFID_AddTargetListener_t	tAddTargetListener;
		esl_RFID_RemoveTargetListener_t	tRemoveTargetListener;
		esl_RFID_OpenConnection_t		tOpenConnection;
		esl_RFID_CloseConnection_t		tCloseConnection;
		esl_RFID_WriteNDEF_t			tWriteNDEF;
		esl_RFID_ReadNDEF_t				tReadNDEF;
		esl_RFID_ISO443Exchange_t		tISO443Exchange;
		esl_RFID_Transceive_t			tTransceive;
		u16								bEnableAutoScan;
#endif	/* __SUPPORT_JSR257__ */
	} ReqParam;

} esl_RFID_driver_Req_t;


/**
 *  @brief RFID media file information structure
 */
typedef struct
{
	esl_RFID_CmdReqType_et		CmdRegType;	//for call back
	esl_RFID_Module_Type_et		ModuleType;	//for call back

	union
	{
		struct
		{
			u16                   	TagNum;       /**< Tag ID array size */
    		u8 						padding[2];
			esl_RFID_TagInfo_t   	*pTagInfo;     /**< Tag ID pointer array (Should need freed by AP layer) */
		}startInfo;

		esl_RFID_ReadParam_t    readParam;    /**< Read data */
		esl_RFID_WriteParam_t   writeParam;   /**< Write data */

		struct
		{
			u8						id[32];       /**< Reader ID */
			u8						FW_VERSION[12];  /**< Firmware Version */
			u16						idLen;        /**< Reader ID length in bytes */
    		u8 						padding[2];
		}readerInfo;

		esl_RFID_SIMSwitch_t	simSwitch;
		esl_RFID_UpgradeParam_t upgradeParam;

#ifdef __BARCODE__
		esl_RFID_BarcodeParam_t BarcodeParam;
#endif	//__BARCODE__

		esl_RFID_GPSOperation_t tGPS;
        esl_RFID_LockParam_t	lockParam;   /**< Write data */
		esl_RFID_MFCommand_t		MFCmdParam;

#ifdef __SUPPORT_JSR257__
		esl_RFID_Listener_t			listener;
		esl_RFID_OpenConnection_t	openConnection;
		esl_RFID_ReadNDEF_t			readNDEF;
		esl_RFID_ISO443Exchange_t	ISO443Exchange;
		esl_RFID_Transceive_t               Transceive;
#endif	/* __SUPPORT_JSR257__ */
	} param;
} esl_RFID_Info_t;

/**
 * @brief Call back function, MMI need to provide the function entity
 *
 * @param senderID     : Sender task id.
 * @param userValue    : Reference value for indicating different sender in same task or check msg response.
 * @param errCode      : The error code return by EMA task to know process success or fail.
 * @param pRfidInfo    : Query data return by EMA task.
 *
 * @return None
 */
typedef void (*esl_RFID_Cb)(u16 senderID, u32 userValue, esl_RFID_ErrCode_e errCode, esl_RFID_Info_t *pRfidInfo);

/**
 *  @brief Esl call back function structure definition
 */
typedef struct {
  u16           senderID;     /**< Task id of sender */
  u32           userValue;    /**< User vlue of sender for checking msg response */
  esl_RFID_Cb   pfnCb;        /**< Done call back function that called by EMA */
} esl_RFID_Cb_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

//#endif	//__RFID__

#endif /* __ESL_RFID_ITF_H__ */


