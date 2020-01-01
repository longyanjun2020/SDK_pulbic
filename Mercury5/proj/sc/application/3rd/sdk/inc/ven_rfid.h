/**
* @file ven_rfid.h
*
* This file defines the RFID related interface for vendor useage
* 
*
* @version $Id: ven_rfid.h  2011-06-22 05:24:37Z Bruce.Wu $
*
*/




#ifndef __VEN_RFID_H_
#define __VEN_RFID_H_


#include "ven_sdk.h"


#ifdef __RFID_SDK_SUPPORT__

    #include "srv_resmgr_mmlrfid_types.h"
    #include "ABL_RFID.h"

#endif//  __RFID_SDK_SUPPORT__


typedef enum
{
	VEN_RFID_OPEN_CMD,
	VEN_RFID_CLOSE_CMD,
	VEN_RFID_READ_CMD,
	VEN_RFID_WRITE_CMD,
	VEN_RFID_GET_READER_INFO_CMD,
	VEN_RFID_UPGRADE_CMD,
	VEN_RFID_SIM_SWITCH_CMD,
	VEN_RFID_BIZCOMMAND_CMD,

#ifdef __BARCODE__
	VEN_BARCODE_READ_CMD,
#endif	//__BARCODE__

	VEN_RFID_GPS_OPERATION,
	VEN_RFID_LOCK_TAG_CMD,

//#ifdef __SUPPORT_JSR257__
	VEN_RFID_INIT_CMD,//JSR257 only
	VEN_RFID_MF_CMD,
	VEN_RFID_ADD_NDEF_LISTENER_CMD,
	VEN_RFID_REMOVE_NDEF_LISTENER_CMD,
	VEN_RFID_ADD_TARGET_LISTENER_CMD,
	VEN_RFID_REMOVE_TARGET_LISTENER_CMD,
	VEN_RFID_OPEN_CONNECTION_CMD,
	VEN_RFID_CLOSE_CONNECTION_CMD,
	VEN_RFID_WRITE_NDEF_CMD,
	VEN_RFID_READ_NDEF_CMD,
	VEN_RFID_ISO443_EXCHANGE_DATA_CMD,
	VEN_RFID_TRANSCEIVE_CMD,
//#endif	//__SUPPORT_JSR257__

	VEN_RFID_CMD_MAX
} ven_RFID_CmdReqType_et;
/**
 *  @brief RFID error code
 */
//typedef enum {
//    ESL_RFID_OK,                /**< Function complete successfully */
//    ESL_RFID_FAIL,              /**< Function common error          */
//    ESL_RFID_PARAM_ERROR,       /**< The input parameter is wrong   */
//    ESL_RFID_MEM_ALLOC_ERROR,   /**< Can't allocate memory from OS  */
//    ESL_RFID_REJECT,            /**< Request reject because of other function's confliction */
//    ESL_RFID_ABORT,             /**< Request abort because of incorrect sequence            */
//    ESL_RFID_TIMEOUT            /**< Request no response timeout,this error is returned by call back function  */
//} esl_RFID_ErrCode_e;

/**
 *  @brief RFID Module type
 */
typedef enum
{
	VEN_MSR3110,
	VEN_MSR3320,
	VEN_MSR3330,

#ifdef __BARCODE__
	VEN_BARCODE_MODULE, //barcode reader
#endif	//__BARCODE__

	VEN_NO_SPECIFIED,
} ven_RFID_Module_Type_et;

/**
 *  @brief RFID type
 */
typedef enum {
    VEN_RFID_TYPE_ALL = 0,          /**< All supported tags */
    VEN_RFID_TYPE_ISO15693,         /**< ISO15693 type */
    VEN_RFID_TYPE_C1G2,             /**< C1G2 type     */
    VEN_RFID_TYPE_ISO15693_MSTAR,   /**< ISO15693 MStar proprietary */
    VEN_RFID_TYPE_C1G2_MSTAR,       /**< C1G2 MStar proprietary */
    VEN_RFID_TYPE_ISO14443A,        /**< ISO14443A type */
    VEN_RFID_TYPE_ISO14443A_MF4K,        /**< ISO14443A MF4K type */
    VEN_RFID_TYPE_ISO14443A_MF1K,        /**< ISO14443A MF1K type */
    VEN_RFID_TYPE_ISO14443A_UL,         /**< ISO14443A MF_UL type */
    VEN_RFID_TYPE_ISO14443_4A,        /**< ISO14443_4A type */
    VEN_RFID_TYPE_ISO14443A_TOPAZ,  /**< ISO14443A TOPAZ/JEWEL */
    VEN_RFID_TYPE_ISO14443B,        /**< ISO14443B type */
    VEN_RFID_TYPE_ISO14443B_AT88RF04C,        /**< ISO14443B ATMEL  AT88RF04C*/
    VEN_RFID_TYPE_ISO14443B_AT88SC0808CRF,        /**< ISO14443B ATMEL  AT88SC0808CRF*/
    VEN_RFID_TYPE_ISO14443B_AT88SC1616CRF,        /**< ISO14443B ATMEL  AT88SC1616CRF*/
    VEN_RFID_TYPE_ISO14443B_AT88SC3216CRF,        /**< ISO14443B ATMEL  AT88SC3216CRF*/
    VEN_RFID_TYPE_ISO14443B_AT88SC6416CRF,        /**< ISO14443B ATMEL  AT88SC6416CRF*/
    VEN_RFID_TYPE_ST14443B,         /**< ST14443B type  (Boli Add)*/
    VEN_RFID_TYPE_ISO14443_4B,        /**< ISO14443_4B type */
    VEN_RFID_TYPE_UNKNOWN,           /**< Unknown media type */
    VEN_RFID_TYPE_TOTAL
} ven_RFID_TagType_e;

/**
 *  @brief RFID memory type
 */
typedef enum {
    VEN_RFID_MEM_TYPE_RESERVED = 0, /**< reserved */
    VEN_RFID_MEM_TYPE_EPC,          /**< EPC type  */
    VEN_RFID_MEM_TYPE_TID,          /**< TID type  */
    VEN_RFID_MEM_TYPE_USER,         /**< USER type */
    VEN_RFID_MEM_TYPE_UNKNOWN       /**< Unknown media type */
} ven_RFID_MemType_e;

/**
 *  @brief RFID scan type
 */
typedef enum {
    VEN_RFID_SCAN_ONCE = 0,         /**< Once Scan   */
    VEN_RFID_SCAN_REPEAT,           /**< Repeat Scan */
    VEN_RFID_SCAN_UNKNOWN           /**< Unknown mode */
} ven_RFID_ScanMode_e;

/**
 *  @brief RFID block size
 */
typedef enum {
    VEN_RFID_BLOCK_2_BYTE = 0,      /**< 2-byte block */
    VEN_RFID_BLOCK_4_BYTE,          /**< 4-byte block  */
    VEN_RFID_BLOCK_16_BYTE,          /**< 16-byte block  */
    VEN_RFID_BLOCK_UNKNOWN          /**< Unknown block */
} ven_RFID_BlockSize_e;


/**
 *  @brief RFID SIM Switch choice
 */
typedef enum {
    VEN_RFID_SIM2_CTRL_BY_PHONE = 0,
    VEN_RFID_SIM2_CTRL_BY_RFID_MODULE,

	VEN_RFID_SIM2_CTRL_MAX,
} ven_SIM_Switch_e;

typedef enum {
    VEN_RFID_GET_SIMSWITCH,
	VEN_RFID_SET_SIMSWITCH,
} ven_SIM_Switch_Action_e;

/**
 *  @brief RFID Upgrade firmware operation
 */
typedef enum {
    VEN_RFID_UPGRADE_FW_PRE_CONDITION = 0,
    VEN_RFID_UPGRADE_FW_SECTOR_ERASE,
    VEN_RFID_UPGRADE_FW_WRITE,
    VEN_RFID_UPGRADE_FW_POST_CONDITION,
    VEN_RFID_UPGRADE_FW_SPEED_OPTIMIZE,
} ven_Upgrade_Firmware_OP_e;

typedef enum {
	VEN_RFID_WRITE_PWD_CMD		= 0,
	VEN_RFID_LOCK_PWD_CMD		= 1
}ven_RFID_CmdId_e;

typedef enum {
	VEN_GPS_GETPOS		= 0,
}ven_GPS_Operation_e;

/**
 *  @brief Mstar Tag Model ID
 */
typedef enum
{
    VEN_RFID_TAG_MSR3200 = 0,            /* MStar Lyra Series */
    VEN_RFID_TAG_MSR3260,                /* MStar Pavo Series */
    VEN_RFID_TAG_UNKNOWN,                /* UNKNOWN */
    VEN_RFID_TAG_MODEL_MAX               /*  */
} ven_RFID_Tag_Model_et;

/**
 *  @brief RFID MStar ISO15693 Custom Command Category
 */
typedef enum
{
    VEN_RFID_CUS_EAS = 0,            /* EAS Related Operation */
    VEN_RFID_CUS_SECURED_RW,         /* Secured Read / Write */
    VEN_RFID_CUS_PWD,                /* Password Setting */
    VEN_RFID_CUS_MAX                 /*  */
} ven_RFID_Cus_Category_et;


typedef enum {
	VEN_RFID_MF_CMD_AUTH			= 0,
	VEN_RFID_MF_CMD_INCREMENT	= 1,
	VEN_RFID_MF_CMD_DECREMENT	= 2,
	VEN_RFID_MF_CMD_TRANSFER	= 3,
	VEN_RFID_MF_CMD_RESTORE		= 4
}ven_RFID_MFCmdId_e;

typedef enum {
	VEN_RFID_MF_KEYA				= 0,
	VEN_RFID_MF_KEYB				= 1
}ven_RFID_MFKey_e;

typedef enum {
    // Search Tag
    VEN_MF_ST_ONE_TAG_FOUND = 0,
    VEN_MF_ST_TAG_NOT_MF_CLASSIC,
    VEN_MF_ST_NO_TAG_FOUND,
    VEN_MF_ST_MORE_THAN_ONE_TAG_FOUND,

    // Authentication
    VEN_MF_AU_OK,
    VEN_MF_AU_NO_TAG_TIMEOUT_FOR_RB,
    VEN_MF_AU_FAIL_TIMEOUT_FOR_TOKENBA,
    VEN_MF_AU_FAIL_WRONG_TOKENBA,
    VEN_MF_AU_OTHER_THAN_KEYA_KEYB,

    // Write
    VEN_MF_WR_OK,
    VEN_MF_WR_NO_TAG_TIMEOUT_FOR_1ST_ACK,
    VEN_MF_WR_FAIL_1ST_NACK_NOT_ALLOW,
    VEN_MF_WR_FAIL_1ST_NACK_TRANSMISSION_ERROR,
    VEN_MF_WR_FAIL_TIMEOUT_FOR_2ND_ACK,
    VEN_MF_WR_FAIL_2ND_NACK_NOT_ALLOW,
    VEN_MF_WR_FAIL_2ND_NACK_TRANSMISSION_ERROR,

    // Read
    VEN_MF_RD_OK,
    VEN_MF_RD_NO_TAG_TIMEOUT,
    VEN_MF_RD_FAIL_GOT_ACK,
    VEN_MF_RD_FAIL_NACK_NOT_ALLOW,
    VEN_MF_RD_FAIL_NACK_TRANSMISSION_ERROR,
    VEN_MF_RD_FAIL_WRONG_LENGTH,
    VEN_MF_RD_FAIL_WRONG_PARITY,
    VEN_MF_RD_FAIL_WRONG_CRC,

    // Increment/Decrement/Restore/Transfer (Value OP)
    VEN_MF_VP_OK,
    VEN_MF_VP_NO_TAG_TIMEOUT_FOR_1ST_ACK,
    VEN_MF_VP_FAIL_1ST_NACK_NOT_ALLOW,
    VEN_MF_VP_FAIL_1ST_NACK_TRANSMISSION_ERROR,

    // Halt
    VEN_MF_HT_OK,

    VEN_MF_UNEXPECTED_STATUS
}ven_RFID_MFStatus_e;




/**
 *  @brief RFID tag ID
 */
typedef struct {
    u8  uid[12];                    /**< Tag UID      */
} ven_RFID_TagId_t;

typedef struct
{
    u8  pwd[8];
} ven_RFID_Pwd_t;

typedef struct {
    u8  key[8];
}ven_RFID_MFKey_t;

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
} ven_RFID_Date_t;

/**
 *  @brief RFID tag info
 */
typedef struct {
    ven_RFID_TagType_e       type;        /**< Tag type     */
    bool                  killed;      /**< Is this tag killed */
    u8                    tagIdLen;    /**< Tag UID length */
    ven_RFID_TagId_t      tagId;       /**< Tag UID      */
    u16                   blockNum;    /**< Block number */
    ven_RFID_BlockSize_e  blockSize;   /**< Block size in byte */
    u8                    S43A_SAK;
    u16                   S43A_ATQA;
    u8                    AT43B_APP3;  /**<For ATMEL 43B use> */
    u8                    S43B_Param;    /**< For ATMEL 43B use > */
    u8                    block[16];    /**< For Data save >*/
} ven_RFID_TagInfo_t;

/**
 *  @brief RFID start parameters
 */
typedef struct {
    ven_RFID_TagType_e      type;         /**< RFID type            */
    ven_RFID_ScanMode_e  scanMode;     /**< Scan mode            */
    u32                  repeatTime;   /**< repeat scanning time (ms) (only for repeat scan)    */
    ven_RFID_Date_t      currDate;     /**< Current date         */
    bool                 retKilledTag; /*<< Return killed expired tags (0:No 1:Yes) */
    u16                  maxIdSize;    /**< Max number of Tag ID */
    ven_RFID_TagInfo_t  *pTagInfo;     /**< Tag ID pointer arry  */
} ven_RFID_StartConfig_t;

/**
 *  @brief RFID Read parameter
 */
typedef struct {
    ven_RFID_TagType_e      type;        /**< RFID type */
    ven_RFID_TagId_t      	tagId;       /**< Tag UID              */
    ven_RFID_MemType_e    	memType;     /**< memory type          */
    ven_RFID_BlockSize_e  	blockSize;   /**< block size in byte   */
    u16                   	memAddr;     /**< memory address,block ID       */
    u16                   	length;      /**< memory read length (= buffer length) */
    u8                   	*pBuff;       /**< Buffer for data read */
    u8                    	S43B_Param;
    u8						padding[3];

    /* ISO15693 MStar,  Valid, if Tag_Type = ESL_RFID_TYPE_ISO15693_MSTAR */
    struct
    {
        ven_RFID_Tag_Model_et    Tag_Model;      // In, Tag Model Name. Should be set if Tag_Type = ESL_RFID_TYPE_ISO15693_MSTAR
        ven_RFID_Cus_Category_et Cus_Category;   		// In,  Cus_Category = CUS_EAS ==> EAS Read
                                        		//      Cus_Category = CUS_SECURED_RW ==> Secured Read
                                        		//      Others, Not Support
        ven_RFID_Pwd_t PWD;                      // In, Password. If Cus_Category = CUS_SECURED_RW or CUS_PWD, PWD[8] should be set properly
    }Custom;

} ven_RFID_ReadParam_t;

/**
 *  @brief RFID Write parameter
 */
typedef struct {
    ven_RFID_TagType_e    type;        /**< RFID type */
    ven_RFID_TagId_t      tagId;       /**< Tag info              */
    ven_RFID_MemType_e    memType;     /**< memory type           */
    ven_RFID_BlockSize_e  blockSize;   /**< block size in byte    */

    u16                   memAddr;     /**< memory address,block ID        */
    u16                   length;      /**< memory write length (= buffer length) */
    u8                   *pBuff;       /**< Buffer for data write */

    u8                    S43B_Param;      /**< for ATMEL 43B > */
    u8						padding[3];

    /* ISO15693 MStar,  Valid, if Tag_Type = ESL_RFID_TYPE_ISO15693_MSTAR */
    struct
    {
        ven_RFID_Tag_Model_et    Tag_Model;      // In, Tag Model Name. Should be set if Tag_Type = ESL_RFID_TYPE_ISO15693_MSTAR
        ven_RFID_Cus_Category_et Cus_Category;   // In,  Cus_Category = CUS_EAS ==> EAS Write
			                                     //      Cus_Category = CUS_SECURED_RW ==> Secured Write
			                                     //      Others, Not Support
        ven_RFID_Pwd_t PWD;                      // In, Password. If Cus_Category = CUS_SECURED_RW or CUS_PWD, PWD[8] should be set properly
    }Custom;

} ven_RFID_WriteParam_t;


/**
 *  @brief RFID SIM switch parameter
 */
typedef struct {
	ven_SIM_Switch_Action_e Action;			/**< Set or Get SimSwitch*/
    ven_SIM_Switch_e    CtrlOwner;         /**< SIM2 is control by which one */
} ven_RFID_SIMSwitch_t;

/**
 *  @brief RFID media file information structure
 */
typedef struct {
    ven_RFID_Module_Type_et    ModuleType;         /**< RFIDModuleType */
} ven_RFID_ModuleInfo_t;

/**
 *  @brief RFID Upgrade firmware parameter
 */
typedef struct {
    ven_RFID_Module_Type_et          ModuleType;        /**< RFIDModuleType */
    ven_Upgrade_Firmware_OP_e    UpgradeOP;         /**< UpgradeOP */
    u32                          TargetAddr;        /**< Target address */
    u8                           *pData;
    u16                          Step;              /**< Upgrade step progress*/
    u8                           DataLen;           /**< Data length for upgrade */
    u8							 padding;
} ven_RFID_UpgradeParam_t;

typedef struct
{
	u16                   idLen;        /**< Reader ID length in bytes */
	u8                    id[32];       /**< Reader ID */
	u8                    FW_VERSION[11];  /**< Firmware Version */
}ven_RFID_GetReaderInfo_t;


#define	BARCODE_MAX_BYTE	(52)

typedef struct
{
	u8	readData[BARCODE_MAX_BYTE];	//read data
	u16	readLen;
    u8 	padding[2];
}ven_RFID_BarcodeParam_t;

#define	GPS_LONGITUDE_LEN	(20)
#define	GPS_LATITUDE_LEN	(20)
#define	GPS_SAT_COUNT_MAX	(12)
#define	GPS_HORIZON_MAX		(12)

typedef struct
{
	ven_GPS_Operation_e Op;
    u8 Longitude[GPS_LONGITUDE_LEN];
    u8 Latitude[GPS_LONGITUDE_LEN];
    u8 Satellite_Count[GPS_SAT_COUNT_MAX];
    u8 Horizontal_Precision[GPS_HORIZON_MAX];
    u8 NS;
    u8 EW;
    u8 GPS_Status;
    u8 padding;
}ven_RFID_GPSOperation_t;


/**
 *  @brief RFID Lock parameter
 */
typedef struct
{
    ven_RFID_TagType_e    type;        /**< RFID type */
    ven_RFID_TagId_t      tagId;       /**< Tag info              */

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
        ven_RFID_Tag_Model_et    Tag_Model;      // In, Tag Model Name. Should be set if Tag_Type = ESL_RFID_TYPE_ISO15693_MSTAR
        ven_RFID_Cus_Category_et Cus_Category;   // In,  Cus_Category = CUS_EAS ==> EAS Lock
                                        //      Cus_Category = CUS_PWD ==> PWD Lock
                                        //      Others, Not Support
    }Custom;

    /* ISO15693,  Valid, if Tag_Type = ESL_RFID_TYPE_ISO15693 */
    struct
    {
        u8 Block_ID;
    	u8 padding[3];
    }Std_693;

} ven_RFID_LockParam_t;



typedef enum {
    VEN_RFID_RET_OK,                /**< Function complete successfully */
    VEN_RFID_RET_FAIL,              /**< Function common error          */
    VEN_RFID_RET_PARAM_ERROR,       /**< The input parameter is wrong   */
    VEN_RFID_RET_MEM_ALLOC_ERROR,   /**< Can't allocate memory from OS  */
    VEN_RFID_RET_REJECT,            /**< Request reject because of other function's confliction */
    VEN_RFID_RET_ABORT,             /**< Request abort because of incorrect sequence            */    
    VEN_RFID_RET_TIMEOUT,            /**< Request no response timeout,this error is returned by call back function  */  
    //VEN_RFID_RET_REQUEST_CAT_ERROR,
    VEN_RFID_RET_RECORD_INDEX_USED,    
    VEN_RFID_RET_OUT_OF_CAPACITY,	    /**< Out of Tag Memory Capacity */
    VEN_RFID_RET_UNKNOWN_ERROR = 0xEEEE,
    VEN_RFID_RET_NOT_SUPPORT = 0xEEFF,

} ven_rfid_ret_e;



typedef struct
{
    ven_RFID_MFCmdId_e	cmdId;
    ven_RFID_TagId_t	tagId;
    ven_RFID_MFKey_e	authKey;
    ven_RFID_MFKey_t	keyBuf;
    ven_RFID_MFStatus_e	rspStatus;
    s32					value;
    u8					blockIdx;
    u8					padding[3];
}ven_RFID_MFCommand_t;

typedef enum {
    VEN_RFID_TARGET_RESERVED = 0,	//43A, 43B
    VEN_RFID_TARGET_NDEF = 0x0001,	//43A, 43B
	VEN_RFID_TARGET_RFID = 0x0002,	//43A, 43B
	VEN_RFID_TARGET_ISO14443_CARD = 0x0004,	//no support
	VEN_RFID_TARGET_VISUAL_TAG = 0x0008,	//no support

} ven_RFID_TargetType_e;

//NDEF_RT_MASK_EMPTY NDEF_RT_MASK_NFC_FORUM_RTD should the same as Esl_rfid_itf.h
#define NDEF_RT_MASK_EMPTY          0x01
#define NDEF_RT_MASK_NFC_FORUM_RTD  0x02
#define NDEF_RT_MASK_MIME           0x04
#define NDEF_RT_MASK_URI            0x08
#define NDEF_RT_MASK_EXTERNAL_RTD   0x10
#define NDEF_RT_MASK_UNKNOWN        0x20
#define NDEF_RT_MASK_UNCHANGED      0x40

typedef enum {
	VEN_RFID_LISTEN_NDEF,
	VEN_RFID_LISTEN_TARGET
}ven_RFID_ListenType_e;

#define	URL_NUM_MAX	(4)
#define	UID_MAX_LEN	(10)
#define	MAPPING_MAX_LEN	(20)
#define	URL_MAX_LEN	(128)

typedef struct
{
	u16     targetType;

    char	UIDStr[UID_MAX_LEN*2+4];
    u8		UID_Hex[UID_MAX_LEN+2];
    char	mapping[MAPPING_MAX_LEN+4];
    char	url[URL_NUM_MAX][URL_MAX_LEN+4];
    u8		urlLen[URL_NUM_MAX];
	u8		UIDStrLen;
	u8		UID_Len;
	u8		padding[2];
} ven_RFID_TagProperties_t;

#define	NDEF_DATA_LEN (152)
typedef struct
{
	u8	data[NDEF_DATA_LEN];
	u16	dataSize;
    u8	detectMask;	//NDEF_RT_MASK_EMPTY
    u8	padding;
}ven_RFID_NDEFListener_t;

typedef struct
{
	ven_RFID_TagProperties_t	*tagArray;
	u16							tagNum;
}ven_RFID_TargetListener_t;

typedef struct
{
	ven_RFID_ListenType_e	type;

	union
	{
		ven_RFID_NDEFListener_t		NDEF;
		ven_RFID_TargetListener_t	target;
	}data;

}ven_RFID_Listener_t;

typedef struct
{
	u8	typeBuf[NDEF_DATA_LEN];
	u16	typeLen;
	u8	NDEFTypeMask;	//NDEF_RT_MASK_EMPTY
    u8  RecordIndex; //this index should maintine by Upper Layer , 0~6 used by JAVA Please notice.
}ven_RFID_AddNDEFListener_t;

typedef struct
{
	u8	typeBuf[NDEF_DATA_LEN];
    u16	typeLen;
	u8	NDEFTypeMask;	//NDEF_RT_MASK_EMPTY
    u8  RecordIndex; //this index should maintine by Upper Layer
}ven_RFID_RemoveNDEFListener_t;

typedef struct
{
	ven_RFID_TargetType_e	targetType;
}ven_RFID_AddTargetListener_t;

typedef struct
{
	ven_RFID_TargetType_e	targetType;
}ven_RFID_RemoveTargetListener_t;

typedef struct
{
	//cmd
	ven_RFID_TargetType_e	targetType;
	u8*	url;

	//return
	void* handle;

	u16	urlLen;
    u8 padding[2];
}ven_RFID_OpenConnection_t;

typedef struct
{
	void*	handle;
}ven_RFID_CloseConnection_t;

typedef struct
{
	void*	handle;
	u8*		data;
	u16		dataSize;
    u8 		padding[2];
}ven_RFID_WriteNDEF_t;

typedef struct
{
	//cmd
	void*	handle;

	//return
	u8		data[NDEF_DATA_LEN];
	u16		dataSize;
    u8 		padding[2];
}ven_RFID_ReadNDEF_t;

typedef struct
{
	void*	handle;
	u8*		data;
	u16		dataSize;
    u8 		padding[2];
}ven_RFID_ISO443Exchange_t;

typedef struct
{
	void*	handle;
	u8*		data;
	u16		dataSize;
    u8 		padding[2];
}ven_RFID_Transceive_t;



typedef struct
{
	ven_RFID_CmdReqType_et		CmdRegType;
	ven_RFID_Module_Type_et		ModuleType;	/* Use to decide open which interface(SPI or Uart), if CmdReq no related to module,
												choose ESL_NO_SPECIFIED will open none of SPI or Uart*/
	union
	{
		ven_RFID_StartConfig_t	tOpen; //RFID Reader Config
		ven_RFID_ModuleInfo_t	tRfidModuleInfo;	//Yenchih note:: migrate temp, need remove
		ven_RFID_ReadParam_t	tRead;
		ven_RFID_WriteParam_t	tWrite;
		ven_RFID_SIMSwitch_t	tRfidSimSwitch; //Sim Switch Parameter
		ven_RFID_UpgradeParam_t	tRfidUpgradeParam;

#ifdef __BARCODE__
		ven_RFID_BarcodeParam_t tBarcodeParam;	//barcode reader
#endif	//__BARCODE__

		ven_RFID_GPSOperation_t tGPS;
        ven_RFID_LockParam_t tLock;
		ven_RFID_MFCommand_t			tMFCmdParam;

//#ifdef __SUPPORT_JSR257__
		ven_RFID_AddNDEFListener_t		tAddNDEFListener;
		ven_RFID_RemoveNDEFListener_t	tRemoveNDEFListener;
		ven_RFID_AddTargetListener_t	tAddTargetListener;
		ven_RFID_RemoveTargetListener_t	tRemoveTargetListener;
		ven_RFID_OpenConnection_t		tOpenConnection;
		ven_RFID_CloseConnection_t		tCloseConnection;
		ven_RFID_WriteNDEF_t			tWriteNDEF;
		ven_RFID_ReadNDEF_t				tReadNDEF;
		ven_RFID_ISO443Exchange_t		tISO443Exchange;
		ven_RFID_Transceive_t			tTransceive;
//#endif	/* __SUPPORT_JSR257__ */
	} ReqParam;

} ven_RFID_driver_Req_t;


/**
 *  @brief RFID media file information structure
 */
typedef struct
{
	ven_RFID_CmdReqType_et		CmdRegType;	//for call back
	ven_RFID_Module_Type_et		ModuleType;	//for call back

	union
	{
		struct
		{
			u16                   	TagNum;       /**< Tag ID array size */
    		u8 						padding[2];
			ven_RFID_TagInfo_t   	*pTagInfo;     /**< Tag ID pointer array (Should need freed by AP layer) */
		}startInfo;

		ven_RFID_ReadParam_t    	readParam;    /**< Read data */
		ven_RFID_WriteParam_t   	writeParam;   /**< Write data */

		struct
		{
			u8						id[32];       /**< Reader ID */
			u8						FW_VERSION[12];  /**< Firmware Version */
			u16						idLen;        /**< Reader ID length in bytes */
    		u8 						padding[2];
		}readerInfo;

		ven_RFID_SIMSwitch_t	simSwitch;
		ven_RFID_UpgradeParam_t upgradeParam;

#ifdef __BARCODE__
		ven_RFID_BarcodeParam_t BarcodeParam;
#endif	//__BARCODE__

		ven_RFID_GPSOperation_t tGPS;
        ven_RFID_LockParam_t	lockParam;   /**< Write data */
		ven_RFID_MFCommand_t		MFCmdParam;

//#ifdef __SUPPORT_JSR257__

		ven_RFID_Listener_t			listener;
		ven_RFID_OpenConnection_t	openConnection;
		ven_RFID_ReadNDEF_t			readNDEF;
		ven_RFID_ISO443Exchange_t	ISO443Exchange;
		ven_RFID_Transceive_t       Transceive;
//#endif	/* __SUPPORT_JSR257__ */
	} param;
} ven_RFID_Info_t;

#if 0
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

#endif


//typedef u32 ven_rfid_ret_t;




/**
 *  ven_rfid_send_cmd
 *
 *  @brief  RFID
 *
 *  @param  *pNFCReq           [in]Param of NFC usage.
 *  @param  *ptVenReq            [in]Request data.
 *
 *
 *  @retval  VEN_RFID_RET_OK if success
 *            if failed
 *            if input parameter is invalid
 *
 *  @note
 *
 *
 */

ven_rfid_ret_e ven_rfid_send_cmd(/*IRFIDREADER *pIRfidReader, void *pUserData,*/ ven_RFID_driver_Req_t *pNFCReq,ven_req_data_t *ptVenReq);

typedef struct
{
    ven_rfid_ret_e  retCode;
    ven_RFID_Info_t *pRfidInfo;
} ven_rfid_cmd_rsp_t;




/**
 *  ven_rfid_register_listener
 *
 *  @brief  RFID
 *
 *  @param  *ptVenReq            [in]Request data.
 *
 *
 *  @retval  VEN_RFID_RET_OK if success
 *            if failed
 *            if input parameter is invalid
 *
 *  @note
 *              this command just need to call once.
 *              After that, you still need to call ESL_RFID_ADD_TARGET_LISTENER_CMD to Active Target Listener
 *              After that, you still need to call ESL_RFID_ADD_NDEF_LISTENER_CMD to Active NDEF Listener
 *
 */

ven_rfid_ret_e ven_rfid_register_listener(ven_req_data_t *ptVenReq);

//typedef ven_rfid_cmd_rsp_t ven_rfid_listener_rsp_t;
typedef struct
{
    //ven_rfid_ret_e  retCode;
    ven_RFID_Info_t *pRfidInfo;
} ven_rfid_listener_rsp_t;



/**
 *  ven_rfid_deregister_listener
 *
 *  @brief  RFID 
 *
 *  @param  *ptVenReq            [in]Request data.
 *
 *
 *  @retval  VEN_RFID_RET_OK if success
 *            if failed
 *            if input parameter is invalid
 *
 *  @note 
 *              this command just need to call once. 
 *              After that, you still need to call ESL_RFID_ADD_TARGET_LISTENER_CMD to Active Target Listener
 *              After that, you still need to call ESL_RFID_ADD_NDEF_LISTENER_CMD to Active NDEF Listener
 * 
 */

ven_rfid_ret_e ven_rfid_deregister_listener(ven_req_data_t *ptVenReq);

// TODO:: Callback not finish

#endif//__VEN_RFID_H_



