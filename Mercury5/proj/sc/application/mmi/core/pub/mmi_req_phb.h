
/**
 * @file    mmi_req_phb.h
 * @brief   The file handles all the PHB request function to RIL
 * @author  ryb.chen@mstarsemi.com
 * 
 * @version $Id: mmi_req_phb.h 12789 2008-07-24 07:04:32Z christoph.kuo $
 */
 
#ifndef __MMI_REQ_PHB_H__
#define __MMI_REQ_PHB_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_phbsrv_def.h"
#include "api_mrl_phb.h"

#define MMI_PHB_REQ_FDN_PIN2_LEN 8 // TBD

typedef enum
{
	MMI_PHB_REQ_TON_NPI_INTERNATIONAL	= 145,
	MMI_PHB_REQ_TON_NPI_NATIONAL		= 129
} MMI_PHB_REQ_TON_NPI_e;

typedef enum
{
	MMI_PHB_REQ_INIT_MODE_ENABLE	= 0,			/* normal initialization (default value) */
	MMI_PHB_REQ_INIT_MODE_DISABLE	= 1				/* no phonebook initialization */
} MMI_PHB_REQ_Init_Mode_e;

typedef enum
{
	MMI_PHB_REQ_VM_NUM_MODE_DISABLE	= 0,			/* disable the voice mail number (default value) => use SIM. */
	MMI_PHB_REQ_VM_NUM_MODE_ENABLE	= 1				/* enable the voice mail number => use phone. */
} MMI_PHB_REQ_VM_Num_Mode_e;

typedef enum
{
	MMI_PHB_REQ_EXTENDED_MODE_DISABLE	= 0,		/* select the SIM contacts (default mode) */
	MMI_PHB_REQ_EXTENDED_MODE_ENABLE	= 1			/* select the extended contacts for phonebook entries */
} MMI_PHB_REQ_Extended_Mode_e;

typedef enum
{
	MMI_PHB_REQ_FDN_MODE_DEACTIVATE	= 0,	/* SIM Fixed Dialing Numbers memory feature de-activated */
	MMI_PHB_REQ_FDN_MODE_ACTIVATE	= 1		/* SIM Fixed Dialing Numbers memory feature activated */
} MMI_PHB_REQ_FDN_Mode_e;

typedef struct
{
	u32							u32CheckValue;		/* Use to check the confirm is yours or not. */
	MmiPhbBookType_e			s32PhbBookType;		/* Phonebook storage type. Support SM, FD, ON, EN and SN. */
} MMI_PHB_REQ_QueryStorageStatusReq_t;


typedef struct
{
	u32							u32CheckValue;		/* Use to check the confirm is yours or not. */
	MmiPhbResult_e			s32PhbResult;		/* Result code */
	MmiPhbBookType_e			s32PhbBookType;		/* Storage type */
	u16							u16Used;			/* used locations in selected memory */
	u16							u16Total;			/* total number of locations in selected memory */
	u16							u16FirstIdx;		/* First location in memory storage. */
	u16							u16LastIdx;			/* Last location in memory storage. */
    u16                         u16Gloextnum;         /* total number of global ext num in selected memory */
    u16                         u16Gloextnumused;     /* used number of global  ext num in selected memory */    
    u16                         u16Locextnum;         /* total number of local ext num in selected memory */
    u16                         u16Locextnumused;     /* used number of local ext num in selected memory */
#ifdef __3G_RIL_MMI__
    u16                         u16Gloemailnum;       /* total number of global email num in selected memory */
    u16                         u16Gloemailnumused;   /* used number of global email num in selected memory */
    u16                         u16Locemailnum;       /* total number of local email num in selected memory */
    u16                         u16Locemailnumused;   /* used number of local email num in selected memory */
	u16							u16FirstGldx;	/*first location in group memory storage(grouping information alpha string EF), this field value will be set 0x00 when not return value.*/
	u16							u16LastGldx;	/*last location in group memory storage(grouping information alpha string EF), this field value will be set 0x00 when not return value*/
	u16							u16FirstNldx;	/*first location in name memory storage(additional number alpha string EF), this field value will be set 0x00 when not return value*/
	u16							u16LastNldx;	/*last location in name memory storage(additional number alpha string EF), this field value will be set 0x00 when not return value*/ 
#endif // #ifdef __3G_RIL_MMI__
	u8							u8NumLen;			/* max length of field <au8Num> */
	u8							u8NameLen;			/* max length of field <au8Name> */
#ifdef __3G_RIL_MMI__
	u8							u8GroupLen;		/*indicates max length of group name, this field value will be set 0x00 when not return value.*/ 
	u8							u8SecondLen;	/*max length of second text field, this field value will be set 0x00 when not return value.*/ 
	u8							u8MailLen;		/*max length of mail (field<au8Mail>), this field value will be set 0x00 when not return value.*/ 
	u8							u8AgroupLen; 	/*max length of additional group name, this field value will be set 0x00 when not return value.*/
	u8							u8AnameLen;	/*max length of additional name, this field value will be set 0x00 when not return value.*/ 
	u8							u8AGroupNum;	/*number of additional groups which can be read/written in one record entry, this field value will be set 0x00 when not return value*/
	u8							u8ANumNum;	/*number of additional numbers which can be read/written in one record entry, this field value will be set 0x00 when not return value*/ 
	u8							u8AEmailNum;	/*number of additional email which can be read/written in one record entry, this field value will be set 0x00 when not return value.*/ 
	u8							u8ANameNum;	/*number of additional name which can be read/written in one record entry, this field value will be set 0x00 when not return value*/ 
#endif // #ifdef __3G_RIL_MMI__
} MMI_PHB_REQ_QueryStorageStatusCnf_t;


typedef struct
{
	u32							u32CheckValue;		/* Use to check the confirm is yours or not. */
	MmiPhbBookType_e			s32PhbBookType;		/* Phonebook storage type. Support SM, FD, ON, EN and SN. */
#ifdef __3G_RIL_MMI__
	u16							u16Index;		/* first location (or range of locations) where to read phonebook entry */
#else //#ifdef __3G_RIL_MMI__
	u16							u16FirstEntry;		/* first location (or range of locations) where to read phonebook entry */
	u16							u16LastEntry;		/* last location (or range of locations) where to read phonebook entry */
#endif // #ifdef __3G_RIL_MMI__
} MMI_PHB_REQ_ReadEntryReq_t;


typedef struct
{
	u32						u32CheckValue;					/* Use to check the confirm is yours or not. */
	MmiPhbResult_e		s32PhbResult;					/* Result code */
	MmiPhbBookType_e		s32PhbBookType;					/* Phonebook storage type. Support SM, FD, ON, EN and SN. */
	u16						u16Idx;							/* phonebook index */
#ifdef __3G_RIL_MMI__
	u16					au16GroupId[MRL_PHB_GROUPID_NUM];/*group name index, this field value will be set 0xffff when not return value or no use.*/ 
	u16					au16NameId[MRL_PHB_NAMEID_NUM];/*additional name index, this field value will be set 0xffff when not return value or no use.*/
	u8					au8Num[MRL_PHB_NUMBER_NUM][MMI_PHB_NUMBER_LEN] ;/* storage format is ASCII format.First element of this field is phone number, and other elements are additional  phone number. The element value will be padded 0x00 when not return value or no use */
	MMI_PHB_REQ_TON_NPI_e	s32Type[MRL_PHB_NUMBER_NUM];						/* TON/NPI */
	u8					au8Name[MRL_PHB_NAME_NUM][MRL_PHB_NAME_LEN_MAX] ;/* indicates name ,second name and additional name. The storage format is ASCII or UCS2 format and end with 0xFF. First element of this field is name ,second element is second name and other elements are additional name. The second name store in second name entry EF. Additional name store in additional number alpha string EF. The element value will be padded 0xff when not return value or no use. */
	MMI_PHB_USIM_HIDDEN_MODE_E s32hidden; /*indicates the information of record entry to need hidden or not*/
	MMI_PHB_REQ_MAIL_t  stMail[MRL_PHB_MAIL_NUM];/*is to store length and pointer of mail string. The storage format of mail string is ASCII or UCS2 format. The element value will be padded 0x00 when not return value or no use. When this field value is not equal zero, MMI must release the allocated memory*/
	MMI_PHB_REQ_GROUP_t   stGroup[MRL_PHB_GROUP_NUM]; /* is to store length and pointer of group string. The storage format of group string is ASCII or UCS2 format. First group string does not set group name index. 2~10 group string need set group name index in au16GropId[9]. The element value will be padded 0x00 when not return value or no use */
#else //#ifdef __3G_RIL_MMI__
	u8						au8Num[MMI_PHB_NUMBER_LEN];		/* phone number in ASCII format, end with 0xFF. */
	MMI_PHB_REQ_TON_NPI_e	s32Type;						/* TON/NPI */
	u8						au8Name[MRL_PHB_NAME_LEN_MAX];		/* name associated with the phone number in ASCII or UCS2 format, 
															   end with 0xFF. */
#endif // #ifdef __3G_RIL_MMI__
} MMI_PHB_REQ_ReadEntryCnf_t;


typedef struct
{
	u32						u32CheckValue;					/* Use to check the confirm is yours or not. */
	MmiPhbBookType_e		s32PhbBookType;					/* Phonebook storage type. Support SM, FD, and ON. */
	u16						u16Idx;							/* location in memory storage, range of possible values depending on 
															   the capacity of the phonebook memory */
#ifdef __3G_RIL_MMI__
	u16					au16OldGroupId[MRL_PHB_GROUPID_NUM];/*group name index to delete, this field value will be set 0xffff when not return value or no use.*/ 
	u16					au16OldNameId[MRL_PHB_NAMEID_NUM];/*additional name index to delete, this field value will be set 0xffff when not return value or no use.*/
	u16					au16NewGroupId[MRL_PHB_GROUPID_NUM];/*group name index, this field value will be set 0xffff when not return value or no use.*/ 
	u16					au16NewNameId[MRL_PHB_NAMEID_NUM];/*additional name index, this field value will be set 0xffff when not return value or no use.*/
	u8					au8Num[MRL_PHB_NUMBER_NUM][MMI_PHB_NUMBER_LEN] ;/* storage format is ASCII format.First element of this field is phone number, and other elements are additional  phone number. The element value will be padded 0x00 when not return value or no use */
	MMI_PHB_REQ_TON_NPI_e	s32Type[MRL_PHB_NUMBER_NUM];						/* TON/NPI */
	u8					au8Name[MRL_PHB_NAME_NUM][MRL_PHB_NAME_LEN_MAX] ;/* indicates name ,second name and additional name. The storage format is ASCII or UCS2 format and end with 0xFF. First element of this field is name ,second element is second name and other elements are additional name. The second name store in second name entry EF. Additional name store in additional number alpha string EF. The element value will be padded 0xff when not return value or no use. */
	MMI_PHB_USIM_HIDDEN_MODE_E s32hidden; /*indicates the information of record entry to need hidden or not*/
	MMI_PHB_REQ_MAIL_t  stMail[MRL_PHB_MAIL_NUM];/*is to store length and pointer of mail string. The storage format of mail string is ASCII or UCS2 format. The element value will be padded 0x00 when not return value or no use. When this field value is not equal zero, MMI must release the allocated memory*/
	MMI_PHB_REQ_GROUP_t   stGroup[MRL_PHB_GROUP_NUM]; /* is to store length and pointer of group string. The storage format of group string is ASCII or UCS2 format. First group string does not set group name index. 2~10 group string need set group name index in au16GropId[9]. The element value will be padded 0x00 when not return value or no use */
#else //#ifdef __3G_RIL_MMI__							
	u8						au8Num[MMI_PHB_NUMBER_LEN];		/* phone number in ASCII format. This field is necessary. */
	MMI_PHB_REQ_TON_NPI_e	s32Type;						/* TON/NPI */
	u8						au8Name[MRL_PHB_NAME_LEN_MAX];		/* associated contact name in ASCII or UCS2 format, end with 0xFF. 
															   If this field is not necessary, fills it with 0xFF. */
#endif //#ifdef __3G_RIL_MMI__
} MMI_PHB_REQ_WriteEntryReq_t;


typedef struct
{
	u32							u32CheckValue;		/* Use to check the confirm is yours or not. */
	MmiPhbResult_e			s32PhbResult;		/* Result code */
} MMI_PHB_REQ_WriteEntryCnf_t;


typedef struct
{
	u32							u32CheckValue;		/* Use to check the confirm is yours or not. */
	MmiPhbBookType_e			s32PhbBookType;		/* Phonebook storage type. Support SM, FD, and ON. */
	u16							u16Idx;				/* location in memory storage, range of possible values depending on 
													   the capacity of the phonebook memory */
} MMI_PHB_REQ_DeleteEntryReq_t;


typedef struct
{
	u32							u32CheckValue;		/* Use to check the confirm is yours or not. */
	MmiPhbResult_e			s32PhbResult;		/* Result code */
} MMI_PHB_REQ_DeleteEntryCnf_t;


typedef struct
{
	u32							u32CheckValue;		/* Use to check the confirm is yours or not. */
	MmiPhbBookType_e			s32PhbBookType;		/* Phonebook storage type. Support SM, FD, and ON. */
} MMI_PHB_REQ_DeleteAllEntryReq_t;


typedef struct
{
	u32							u32CheckValue;		/* Use to check the confirm is yours or not. */
	MmiPhbResult_e			s32PhbResult;		/* Result code */
} MMI_PHB_REQ_DeleteAllEntryCnf_t;


typedef struct
{
	u32							u32CheckValue;		/* Use to check the confirm is yours or not. */
	MMI_PHB_REQ_Init_Mode_e		s32InitMode;		/* phonebook initialization mode (for next boot) */
} MMI_PHB_REQ_AvoidInitReq_t;


typedef struct
{
	u32							u32CheckValue;		/* Use to check the confirm is yours or not. */
	MmiPhbResult_e			s32PhbResult;		/* Result code */
} MMI_PHB_REQ_AvoidInitCnf_t;


typedef struct
{
	u32							u32CheckValue;					/* Use to check the confirm is yours or not. */
	MMI_PHB_REQ_VM_Num_Mode_e	s32VMNumMode;					/* voice mail number mode */
	u8							au8Num[MMI_PHB_NUMBER_LEN];		/* phone number in ASCII format. 
																   If this field is not necessary, fills it with 0xFF. */
	MMI_PHB_REQ_TON_NPI_e		s32Type;						/* TON/NPI */
} MMI_PHB_REQ_SetVoiceMailNumberReq_t;


typedef struct
{
	u32							u32CheckValue;		/* Use to check the confirm is yours or not. */
	MmiPhbResult_e			s32PhbResult;		/* Result code */
} MMI_PHB_REQ_SetVoiceMailNumberCnf_t;


typedef struct
{
	u32								u32CheckValue;		/* Use to check the confirm is yours or not. */
	MMI_PHB_REQ_Extended_Mode_e		s32ExtendedMode;	/* extended contact mode */
} MMI_PHB_REQ_SetExtendedModeReq_t;


typedef struct
{
	u32								u32CheckValue;		/* Use to check the confirm is yours or not. */
	MmiPhbResult_e				s32PhbResult;		/* Result code */
} MMI_PHB_REQ_SetExtendedModeCnf_t;


typedef struct
{
	boolean							bIsADNChange;		/* Indicate that the SIM entries have change or not. */
} MMI_PHB_REQ_SimEntryReadyInd_t;


typedef struct
{
	MMI_PHB_REQ_FDN_Mode_e		s32FDNMode;			/* FDN mode */
	u8							au8Pin2Code[MMI_PHB_REQ_FDN_PIN2_LEN+1];
} MMI_PHB_REQ_SetFDNModeReq_t;


typedef struct
{
	MmiPhbResult_e				s32PhbResult;		/* Result code */
} MMI_PHB_REQ_SetFDNModeCnf_t;


typedef struct
{
	u32							padding;
} MMI_PHB_REQ_FdnAdnSwapReadyInd_t;

typedef struct
{
	u8         ADNChecksum[VM_MRL_PHB_CHECKSUM_LEN+1];
#ifdef __3G_RIL_MMI__
	u8 	u16pbid[VM_MRL_PHBID_LEN+1];
    u16 u16puid;
	u16 u16cc;
    u8 u8forceflag;
#endif // __3G_RIL_MMI__
} MMI_PHB_REQ_ChecksumInd_t;

#ifdef __3G_RIL_MMI__
#define MMI_PHB_REQ_HIDDEN_LEN MRL_PHB_HIDDEN_LEN

typedef enum
{
	MMI_PHB_REQ_HIDDEN_KEY_MODE_VERIFY	= MRL_PHB_HIDDEN_VERIFY,	/* SIM Fixed Dialing Numbers memory feature de-activated */
	MMI_PHB_REQ_HIDDEN_KEY_MODE_UPDATE	= MRL_PHB_HIDDEN_UPDATE,		/* SIM Fixed Dialing Numbers memory feature activated */
} MMI_PHB_REQ_HIDDEN_KEY_Mode_e;

typedef struct
{
	u32 							u32CheckValue;		/* Use to check the confirm is yours or not. */
	MMI_PHB_REQ_HIDDEN_KEY_Mode_e	eMode;       /* indicates access mode  */
	ascii			                s8Hidden[MRL_PHB_HIDDEN_LEN+1];/*  is to store key to compare for hidden phonebook entry. The length is four to eight digits number. No use digits number must set 0x00. */
	ascii                       	s8Newhidden[MRL_PHB_HIDDEN_LEN+1];  /* New Hidden Key value. The length is four to eight digits number. No use digits number must set 0x00. */
} MMI_PHB_REQ_HiddenKey_t;

typedef struct
{
    u32							u32CheckValue;		/* Use to check the confirm is yours or not. */
	MmiPhbBookType_e			ePhbType;			/* Phonebook storage type. Support SM, FD, ON, EN and SN. */
	u16							u16Gindex;	        /* location where to read group information entry */
} MMI_PHB_REQ_ReadGroupEntry_t;

typedef struct
{
	u32					u32CheckValue;					/* Use to check the confirm is yours or not. */
	MmiPhbBookType_e	ePhbType;						/* Phonebook storage type. Support SM, FD, and ON. */
	u16					u16Gindex;							/* location in memory storage, range of possible values depending on the capacity of the phonebook memory */
	u32	u32datalen;		/*  length of data that is referred by  u8data pointer. */
	u8	data[1];			/* data, the length is variance according the u32datalen */
} MMI_PHB_REQ_WriteGroupEntry_t;
#endif 

/*
	Function
*/

MmiPhbReturn_e MMI_PHB_REQ_QueryPhbStatusReq					(const MMI_PHB_REQ_QueryStorageStatusReq_t	*ptReq, u8 u8DualID);
MmiPhbReturn_e MMI_PHB_REQ_ReadOneContactByPhysicalIdxReq		(const MMI_PHB_REQ_ReadEntryReq_t			*ptReq, u8 u8DualID);
MmiPhbReturn_e MMI_PHB_REQ_WriteOneContactByPhysicalIdxReq	(const MMI_PHB_REQ_WriteEntryReq_t			*ptReq, u8 u8DualID);
MmiPhbReturn_e MMI_PHB_REQ_DeleteOneContactByPhysicalIdxReq	(const MMI_PHB_REQ_DeleteEntryReq_t			*ptReq, u8 u8DualID);
MmiPhbReturn_e MMI_PHB_REQ_DeleteAllContactReq				(const MMI_PHB_REQ_DeleteAllEntryReq_t		*ptReq, u8 u8DualID);
MmiPhbReturn_e MMI_PHB_REQ_SetFDNModeReq(const MMI_PHB_REQ_SetFDNModeReq_t *ptReq, u8 u8DualID);
#ifdef __3G_RIL_MMI__
MmiPhbReturn_e MMI_PHB_REQ_HiddenKeyReq(const MMI_PHB_REQ_HiddenKey_t *ptReq, u8 u8DualID);
MmiPhbReturn_e MMI_PHB_REQ_ReadGroupEntryReq(const MMI_PHB_REQ_ReadGroupEntry_t *ptReq, u8 u8DualID);
MmiPhbReturn_e MMI_PHB_REQ_WriteGroupEntryReq(const MMI_PHB_REQ_WriteGroupEntry_t *ptReq, u8 u8DualID);
MmiPhbReturn_e MMI_PHB_REQ_CleanSimCacheReq(u8 u8DualID);
MmiPhbReturn_e MMI_PHB_REQ_ecc_req(u8 DualID);
#endif //#ifdef __3G_RIL_MMI__
#endif /* __MMI_REQ_PHB_H__ */

