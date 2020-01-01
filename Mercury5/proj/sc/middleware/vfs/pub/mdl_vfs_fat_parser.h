/**
 *
 * @file    mdl_vfs_fat_parser.h
 *
 * @brief
 *
 * @author  Xavier
 * @version $Id: vfs_fat_parser.h 15206 2008-10-16 06:52:18Z xavier.fan $
 *
 */
#ifndef __MDL_VFS_FAT_PARSER_H__
#define __MDL_VFS_FAT_PARSER_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "mdl_vfs_fat.ho"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __VFS_FAT_PARSER__
#define DefExtern
#else
#define DefExtern extern
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/
void  VfsParser(void *pReceivedMsg);
void  VfsTaskInit(void);
s32   fat_abort_async_write_req(u32 sessionID);
s32   fat_abort_async_read_req(u32 sessionID);
s32   fat_abort_async_copy_req(u32 sessionID);
s32   fat_abort_async_move_req(u32 sessionID);
s32   fat_abort_async_format_req(u32 sessionID);
s32   fat_abort_async_chksum_req(u32 sessionID);
s32   fat_abort_async_get_file_num_req(u32 sessionID);
s32   fat_abort_async_delete_req(u32 sessionID);
s32   fat_abort_async_chkdsk_req(u32 sessionID);

s32   fat_pause_async_format_req(u32 sessionID);
s32   fat_pause_async_chkdsk_req(u32 sessionID);

s32   fat_resume_async_format_req(u32 sessionID);
s32   fat_resume_async_chkdsk_req(u32 sessionID);

s32   fat_send_async_write_req(u32 fileRef, u8 * pData, u32 dataSize, VFS_NotifyCb_t* pNotifyCb);
s32   fat_send_async_read_req(u32 fileRef, u8 * pBuffer, u32 bufferSize, VFS_NotifyCb_t* pNotifyCb);
s32   fat_send_async_copy_req(u16* pSrcPath, u16* pDstPath, VFS_NotifyCb_t* pNotifyCb);
s32   fat_send_async_move_req(u16* pSrcPath, u16* pDstPath, VFS_NotifyCb_t* pNotifyCb);
s32   fat_send_async_format_req(u32 volumdId, VFS_NotifyCb_t* pNotifyCb);
s32   fat_send_async_delete_req(u16* pPath, bool isFolder, VFS_PartialListFilter_t * pFilter, bool isKeepFolder, bool isRecursive, bool isForceDelete, VFS_NotifyCb_t* pNotifyCb);
s32   fat_send_async_force_format_req(u32 volumdId, VFS_NotifyCb_t* pNotifyCb);
s32   fat_ready_to_flush_rai(void);
s32   fat_send_async_chksum_req(u16* pPath, u32 chksumLen, VFS_IgnorePath_t* pIgnorePath, u32 flag, VFS_NotifyCb_t* pNotifyCb);
s32   fat_send_async_get_file_num_req(u16 * pPathName, VFS_PartialListFilter_t* pFilter, u32 startFileNum, u32 * pStartFileNum, VFS_PartialListFileInfo_t* pFileInfoArray, VFS_NotifyCb_t* pNotifyCb);
s32   fat_send_async_chkdsk_req(u32 volumeId, VFS_ChkdskOp_e op, VFS_NotifyCb_t * pNotifyCb);

s32   fat_ready_to_flush_rai(void);

// async delete utility
s32   fat_async_delete_all_req(u16 * pathName, u32 MailBoxId, u32 filterFunc, u32 cb);
s32   fat_async_delete_all_abort(u32 sessionId);

void fat_assign_sd_trace_lost_info_ind_req(vm_msg_t * msgPtr);
void fat_assign_sd_trace_info_ind_req(vm_msg_t * msgPtr);

#endif //#ifndef __MDL_VFS_FAT_PARSER_H__
