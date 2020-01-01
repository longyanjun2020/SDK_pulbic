/**
 * @file rtsp_msg_parser.h
 *
 * @brief This file defines the app state control related message parsers
 *
 */
#ifndef __RTSP_MSG_PARSER_H__
#define __RTSP_MSG_PARSER_H__


void RtspProcessDownloadOpenReq(vm_msg_t *pMessage);
void RtspProcessDownloadCloseReq(vm_msg_t *pMessage);
void RtspProcessDownloadInitReq(vm_msg_t *pMessage);
void RtspProcessDownloadUninitReq(vm_msg_t *pMessage);
void RtspProcessDownloadPlayReq(vm_msg_t *pMessage);
void RtspProcessDownloadStopReq(vm_msg_t *pMessage);
void RtspProcessDownloadPauseReq(vm_msg_t *pMessage);
void RtspProcessDownloadResumeReq(vm_msg_t *pMessage);
void RtspProcessDownloadSeekReq(vm_msg_t *pMessage);
void RtspProcessDownloadDataRsp(vm_msg_t *pMessage);

#endif /* __RTSP_MSG_PARSER_H__ */

