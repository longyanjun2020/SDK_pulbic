/**
 * @file mmi_rfid_receive.h
 *
 * $Id: mmi_rfid_receive.h 2009-11-12 austin.chou $
 */

#ifndef __MMI_RFID_RECEIVE_H__
#define __MMI_RFID_RECEIVE_H__

#include "mae_common_def.h"
#include "mmi_rfid_def.h"

#define OpRcvSystemFlag_Max		(2)
#define OpRcvRtnStr_Max			(126)
#define OpRcvBuf_Max				(65535)
#define BizFileAmout_Max        (500)


typedef struct
{
	RcvHeader_t	header;

	u16			code;
	MAE_WChar	str[OpRcvRtnStr_Max+1];

	RtnAction_e		rtnAction;
} OpRcvRtn_t;


typedef struct
{
	OpRcvRtn_t	rtnValue;

	u8	key[PORK_RANDOM_KEY_LEN];
} OpRcvGetRandomKey_t;

typedef struct
{
	OpRcvRtn_t	rtnValue;

	u8	newVer;
	u8	dateTime[PORK_DATETIME_MAX];
	u8	ver[2];
	u8	serverIp[PORK_SERVER_IP_MAX];
	u16	serverPort;
	u8	serverUrl[PORK_SERVER_URL_MAX+1];
	u8	commInterval;
	u8	bandType;
	u8	systemFlag[OpRcvSystemFlag_Max];

}OpRcvProfile_t;

typedef struct
{
	u8 FileType;
	u16 FileID;
	u16 FileIdx;

} Biz_FileName_st;


typedef struct
{
    u8  action;
    u8  filetype;
    u16  fileId;
	Biz_FileName_st BizFileName;
}UpdateBizfile_t;

typedef struct
{
	OpRcvRtn_t	rtnValue;

	u8	newVer;
    u8  verlength;
	u8	ver[BIZ_FILE_VER_MAX];
    u16  fileAmount;
    UpdateBizfile_t  FileContent[BizFileAmout_Max];
} OpRcvBizCheck_t;

typedef struct
{
	OpRcvRtn_t	rtnValue;

	u8	newVer;
    u16  fileLength;
    u8   *pfileData;
} OpRcvBizGet_t;


typedef struct
{
	OpRcvRtn_t	rtnValue;

	u8			dateTime[PORK_DATETIME_MAX];
	u8			allowFunc[PORK_ALLOW_FUNC_MAX];
	MAE_WChar	name[PORK_NAME_MAX+1];
} OpRcvBizLogin_t;

typedef struct
{
	OpRcvRtn_t	rtnValue;

	u16	currentPacket;
	u16	totalPacket;
    u16 newVer;
	u16 ObjIdx;
}OpRcvUpdate_t;

boolean	receive_parser(u8 *pData);
boolean	test_receive_parser(u8 *pData);
u16		receive_get_op(void);
MAE_Ret	receive_get_data(u16 op, void *pData, u16 size);
RtnAction_e	receive_get_action(void);
MAE_WChar*	receive_get_rtn_str(void);

#endif // #ifndef __MMI_RFID_RECEIVE_H__
