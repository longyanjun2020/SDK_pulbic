/**
 * @file mmi_rfid_upload.h
 *
 * $Id: mmi_rfid_upload.h 2009-11-19 austin.chou $
 */

#ifndef __MMI_RFID_UPLOAD_H__
#define __MMI_RFID_UPLOAD_H__

#include "mae_common_def.h"
#include "mmi_rfid_def.h"

#define OpUploadFrameCount_Max	(55)
#define OpUploadBuf_Max			(65535)
#define OpUploadLen_Min			(12)	//at least one frame
#define OpUploadUHF_Max			(UHF_EPC_LEN+UHF_TID_LEN)
#define OpUploadCellRssi_Max		(9)
#define OpUploadCellRssiArray_Max	(50)
#define OpCardData_Len			(20)


typedef struct
{
	u8	*handsetVer;
	u16	handsetVerLen;
	u8	profileVer[2];
} OpUploadProfile_t;

typedef struct
{
    u8  verlength;
	u8	ver[BIZ_FILE_VER_MAX];
} OpUploadBizCheck_t;

typedef struct
{
    u8  verlength;
	u8	ver[BIZ_FILE_VER_MAX];
	Biz_FileName_st BizFileName;
} OpUploadBizGet_t;

typedef struct
{
	u8	CardEPC[UHF_EPC_LEN];
	u8	CardTID[UHF_TID_LEN];
	u8	manNumber[PORK_MAN_NUMBER_MAX];
	u8	manPassWd[PORK_MAN_PASSWD_MAX];
} OpUploadLogin_t;

typedef struct
{
    u16      op;
    u16     Snddatalen;
    u16     frameamount;
    u8*      Sndbuf;

    u16     Rcvdatalen;
    u8*      Rcvbuf;

    u8		okDialog;
} OpUploadBizServerComm_t;


typedef struct
{
	u8		op;
	u16		BizTableIdx;
    u8      packetinfo[PORK_PACKET_INFO_LEN];
    boolean  bHaveDataSetFlag;
    u16     BizDataSetIdx;
} OpUploadBizUpdate_t;


extern OpUploadBizServerComm_t	*UploadBizServerComm;
extern boolean         bSaveToDataTable;
extern boolean         bNeedParseResult;

u16	upload_get_buf_len(void);
u8*	upload_get_buf_ptr(void);

void	op_register_req(void *pData);
void	op_get_random_key_req(void *pData);
void	op_login_req(void *pData);
void	op_profile_req(void *pData);
void	op_biz_check_req(void *pData);
void	op_biz_get_req(void *pData);
void 	op_biz_server_comm_req(void *pData);

//for test service
void	test_op_general_rsp(u16 op);
void	test_op_random_key_rsp(u16 op);
void	test_op_profile_rsp(u16 op);
void	test_op_biz_check_rsp(u16 op);
void	test_op_biz_get_rsp(u16 op);


#endif // #ifndef __MMI_RFID_UPLOAD_H__
