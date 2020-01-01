/**
 * @file mmi_rfid_def.h
 *
 * $Id: mmi_rfid_def.h 2009-11-26 austin.chou $
 */

#ifndef __MMI_RFID_DEF_H__
#define __MMI_RFID_DEF_H__

#include "ven_sdk.h"
#include "mae_common_def.h"
#include "mmi_common_custom.h"
#include "mmi_mmsrv.h"
#include "winsocket.h"
#include "vm_e2p_stack.ho"

//#define __MMI_PORK_TEST_H__

//#define PORK_NO_ENCRYPT

#define TAG_MAX_ID_SIZE		(10)
#define TAG_MAX_BLOCK_SIZE	(120)
#define HF_UID_LEN			(8)
#define UHF_EPC_LEN			(12)
#define UHF_TID_LEN			(8)

#define PORK_READER_TEST_MAX		(10000)

#define PORK_CHECK_C1G2_CARD_TYPE
#define PORK_BGUPLOAD_CHECK_MIN	(5)	// 5 min
#define PORK_WAIT_KEY_LOGOUT_TIME	(600000)	// 10 min
#define PORK_BUF_MAX				(32000)
#define PORK_SCAN_TAG_MAX			(100)
#define PORK_CONFIG_STRING_LEN		(2000)
#define PORK_SUPPLIER_STRING_LEN	(25000)
#define PORK_SUPPLIER_RAI_MAX		(5)
#define PORK_SUPPLIER_ITEM_MAX		(100)	// 5*100 = 500
#define PORK_LIST_DATA_ID_LEN		(8)
#define PORK_BANDID_BUF_MAX			(16000)
#define PORK_RANDOM_KEY_LEN     		(16)
#define PORK_ERRORLIST_STRING_LEN	(17500)
#define PORK_ERRORLIST_MAX_NUM		(1000)
#define PORK_TXT_RECORD_MAX_LEN	(250)
#define PORK_MAX_ID_SIZE				(10)
#define PORK_BAND_LEN 				(12)
#define PORK_FRAME_MAX 				(256)
#define PORK_N_TAG_TO_ADD_RSSI		(10)
#define PORK_NAME_MAX				(50)
#define PORK_NAME_MAX_PEDIGREE		(100)
#define PORK_INSECT_CODE_LEN		(4)
#define PORK_TRACE_DATA_MAX		(512)
#define PORK_PEDIGREE_FORMAT_MAX	(36)
#define UPLOAD_HANDSET_VER_LEN		(14)
#define PORK_DATETIME_MAX			(6)
#define PORK_SERVER_IP_MAX			(4)
#define PORK_TEL_NUM_MAX			(20)
#define PORK_SERVER_URL_MAX			(100)

#define PORK_ALLOW_FUNC_MAX		(2)
#define PORK_EMERGENCY_MAX			(10)
#define PORK_MAN_NUMBER_MAX		(4)
#define PORK_MAN_PASSWD_MAX		(4)
#define PORK_FRAME_LEN				(29000)	//0xFFFF-2
#define PORK_PEDIGREE_STR_LEN		(25)
#define PORK_WEIGHT_DISPLAY_MAX    (7)
#define PORK_WEIGHT_DECIMAL_MAX   (3)
#define PORK_WEIGHT_INTEGER_MAX   (3)
#define PORK_PACKET_INFO_LEN        (6)

#define HF_CARD_TYPE_LEN          4
#define PORK_USERNAME_MAX         12
#define PORK_COMPANY_MAX          12

#define BIZ_HEADER_LEN              (2)
#define BIZ_CRC_LEN                 (2)
#define BIZ_FRAME_LEN               (2)
#define BIZ_DATATYPE_LEN            (2)

#define BIZ_READER_ID_LEN			(16)
#define BIZ_FILE_VER_MAX            (64)

#define U08_TO_U16HI(value)         (  ((u16)value)<<8      )
#define U08_TO_U16LO(value)         (  ((u16)value)&0x00FF  )
#define U8_TO_U16(high, low)         (U08_TO_U16HI(high)|U08_TO_U16LO(low))

typedef enum
{
	CARD_TYPE_UHF               = 0,
	CARD_TYPE_HF                = 1,
	CARD_TYPE_HF_MSTAR			= 2,
}CardType_et;

typedef enum
{
    MMI_CRC_ISO_14443A = 0,
    MMI_CRC_ISO_14443B,
    MMI_CRC_ISO_15693,
    MMI_CRC_ISO_18092_106,
    MMI_CRC_ISO_18092_248,
    MMI_CRC_EPC_C1G2,
    MMI_CRC_HWIF,
    MMI_CRC_HWIF_SDIO,
    MMI_CRC_TYPE_MAX
}MmiCRCType_e;

enum
{
	OP_REGISTER = 0xff01,
	OP_GET_RANDOM_KEY = 0xff02,
	OP_PROFILE	= 0xff03,
	OP_BIZ_CHECK = 0xff04,
	OP_BIZ_GET = 0xff05,

	OP_LOGIN = 0xff06,
	OP_NULL = 0x0000,
};

enum
{

    DATA_CELL_RSSI= 50008,

	DATA_READER_ID = 65024,
	DATA_OP_ID = 65025,
	DATA_RANDOM_KEY = 65026,
	DATA_HANDSET_VER = 65027,
	DATA_PROFILE_REQ = 65028,
	DATA_PROFILE_RSP = 65029,
	DATA_BIZ_VER = 65030,
	DATA_BIZ_HAS_NEW_VER = 65031,

	DATA_BIZ_FILE_ID = 65032,
	DATA_BIZ_FILE_ID_UPDATE = 65033,
    DATA_BIZ_FILE_ID_DELETE = 65034,
	DATA_BIZ_FILE_CONTENT =65035,
	DATA_SYSTEM_TIME = 65036,
	DATA_CARD_EPC = 65037,
	DATA_CARD_TID= 65038,
	DATA_MAN_ID = 65039,
	DATA_MAN_PASSWD = 65040,
	DATA_MAN_NAME = 65041,
	DATA_MAN_COMPANY= 65042,
    DATA_OP_TIME =65046,


	DATA_SERVER_STR = 65534,
	DATA_SERVER_CODE = 65535,
};

enum
{
    BIZ_FILE_UPDATE = 0,
    BIZ_FILE_DELETE = 1,
};

typedef struct
{
	u8	ver[2];
	u8	releaseDate[PORK_DATETIME_MAX];
	u8	lastUpdateDate[PORK_DATETIME_MAX];
	u8	serverUrl[PORK_SERVER_URL_MAX+1];
	u8	smsTel[PORK_TEL_NUM_MAX+1];
	u16	smsMaxLen;
	u8	commInterval;
	u8	bandType;
	u8	emergencyTelCount;
	u8	emergencyTel[PORK_EMERGENCY_MAX][PORK_TEL_NUM_MAX+1];
	u8	backupIp[PORK_SERVER_IP_MAX];
}PorkConfig_t;

#define	CARD_TYPE_LEN		(2)
#define	CARD_NUMBER_LEN		(4)
#define	CARD_PASSWD_LEN		(4)
#define	CARD_STATUS_LEN		(2)
#define	CARD_CHECK_LEN		(2)
#define	CARD_PRESERVE_LEN	(10)
#define	CARD_TOTAL_LEN		(24)

typedef union
{
	u8	byte[CARD_TOTAL_LEN];

	struct
	{
		u8	type[CARD_TYPE_LEN];
		u8	number_BCD[CARD_NUMBER_LEN];
		u8	passwd_BCD[CARD_PASSWD_LEN];
		u8	status[CARD_STATUS_LEN];
		u8	check[CARD_CHECK_LEN];
		u8	preserve[CARD_PRESERVE_LEN];
	}data;
}PorkLoginCard_t;

#define	TAG_TYPE_LEN			(2)
#define	TAG_OPERATE_LEN		(2)
#define	TAG_PRESERVE_1_LEN		(2)
#define	TAG_CHECK_LEN			(2)
#define	TAG_PRESERVE_2_LEN		(8)
#define	TAG_TOTAL_LEN			(24)

typedef union
{
	u8	byte[TAG_TOTAL_LEN];

	struct
	{
		u8	type[TAG_TYPE_LEN];
		u8	pigSourceStart[TAG_OPERATE_LEN];
		u8	preserve1[TAG_PRESERVE_1_LEN];
		u8	inspectCode[PORK_INSECT_CODE_LEN];
		u8	porkSellStart[TAG_OPERATE_LEN];
		u8	porkSellEnd[TAG_OPERATE_LEN];
		u8	check[TAG_CHECK_LEN];
		u8	preserve[TAG_PRESERVE_2_LEN];
	}data;
}PorkTag_t;

// Upload Request Type
enum
{
	MSG_NO_ENCRYPT =0x00,
	MSG_NORMAL = 0x01,
};

typedef struct
{
	u16	nLen;
	//u16	mechineId;
	u8	imei[VM_IMEI_SIZE];
	u8	version;
	u8	messageId;
	u8	nSmsAmount;
	u8	smsId;
	u16	op;
	u16	nFrameAmount;
} RcvHeader_t;
#define	RcvHeader_t_size	(19)	//alignment issue

typedef struct
{
	u16		nLen;
	u16		type;
	u8		data[PORK_FRAME_LEN];
} RcvFrame_t;

enum
{
	RTN_OK,
	RTN_FAIL,
	RTN_KEY,
	RTN_REGISTER,
	RTN_RESEND,
	RTN_BK_TRACE_OK,
	RTN_RSSI_LEARN,
	RTN_RSSI_FAIL_NO_BLOCK,
	RTN_RSSI_FAIL_BLOCK,
	RTN_UNDEFINE,
	RTN_CRC_ERROR,
	RTN_NULL
};
typedef u8 RtnAction_e;

typedef struct
{
	boolean		bUploadComplete;

	MAE_WChar	loginUserName[PORK_NAME_MAX+1];
	u8			loginManNumber[PORK_MAN_NUMBER_MAX];
	u8			pswdFromLogin[PORK_MAN_PASSWD_MAX];
	u8			loginCardData[UHF_EPC_LEN+UHF_TID_LEN];	//UHF 20 bytes, HF 8 bytes
	u8			loginCardDataLen;	// 20 or 8
	boolean		bLoginUpdated;

	u8		ipFromDns[MAX_IP_LENGTH];
	boolean	bBackUploadEnable;
	boolean	bIdleScreenFlag;
	boolean	bLogoutEnable;

	u8		readerId[BIZ_READER_ID_LEN];				//RFID Reader Id
	boolean	bRkeyReady;
	u8		pRKey[PORK_RANDOM_KEY_LEN];         /**< 128-bit Random Key */
	s32		idleTime;
	u8		key_from_imei[BIZ_READER_ID_LEN];	//gen key from imei

}PorkGlobe_t;

typedef struct
{
    CardType_et	CardType;
	u8		CardEPC[UHF_EPC_LEN];
	u8		CardTID[UHF_TID_LEN];
	u8	    ManNumber[PORK_MAN_NUMBER_MAX];
	u8		Password[PORK_MAN_PASSWD_MAX];
    u16*     pServerCode;
    u16*     pNetCode;
	MAE_WChar ** pUserName;
	MAE_WChar ** pUserCompany;

}BizGlobe_t;

//Encrypt parameter
#define ENCRYPT_ERRORCODE_MD5_DECRYPT		(0xFF01)
#define ENCRYPT_ERRORCODE_UNKNOWN_KEYLEN	(0xFF02)
#define ENCRYPT_ERRORCODE_INIT_FAIL			(0xFF03)
#define ENCRYPT_ERRORCODE_UNKNOWN_TYPE		(0xFF04)

#define MD5_BLOCK_LENGTH                64
#define MD5_DIGEST_LENGTH               16

#define AES_MAXKEYBITS  (256)
#define AES_MAXKEYBYTES (AES_MAXKEYBITS/8)
/* for 256-bit keys, fewer for less */
#define AES_MAXROUNDS   14

typedef struct MD5Context
{
    u32	state[4];                     /* state */
    u64	count;                        /* number of bits, mod 2^64 */
    u8	buffer[MD5_BLOCK_LENGTH];      /* input buffer */
} MD5_CTX_RFID;

/*  The structure for key information */
typedef struct
{
    u8      enc_only;               /* context contains only encrypt schedule */
    u8      KNr;                     /* key-length-dependent number of rounds */
    u32     ek[4*(AES_MAXROUNDS + 1)];      /* encrypt key schedule */
    u32     dk[4*(AES_MAXROUNDS + 1)];      /* decrypt key schedule */
} rijndael_ctx;

typedef enum
{
    RFID_CRYPTO_ENCRYPTION = 0, /**< Encryption */
    RFID_CRYPTO_DECRYPTION,     /**< Decryption */
}RfidCrypto_e;

typedef enum
{
    RFID_CRYPTO_MD5 = 0,        /**< MD5 */
    RFID_CRYPTO_AES,            /**< AES */
    RFID_CRYPTO_UNKNOWN         /**< Unknown type */
}RfidCryptoType_e;

typedef enum
{
	RFID_KEY_128_BIT = 128,	/**< 128-bit */
	RFID_KEY_192_BIT = 192,	/**< 192-bit */
	RFID_KEY_256_BIT = 256,	/**< 256-bit */
	RFID_KEY_UNKNOWN = 0	/**< Unknown lenght */
}RfidKeyLength_e;

typedef struct
{
	RfidCrypto_e		crypto;	//encryption decryption
	RfidCryptoType_e	type;         /**< Crypto type */
	RfidKeyLength_e		keyLen;       /**< Key length */
	u8	*pKey;         /**< Key */
	u16	length;       /**< memory write length (= buffer length) */
	u8	*pBuff;        /**< Buffer for data encrypt */
}RfidEncryptParam_t;


#endif // #ifndef __MMI_RFID_DEF_H__
