#----------------------------------------------------------------------
#	Description of some variables owned by the library
#----------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

# generate preprocess file (e.g. A.c --> A.o.pp)
# This option is for debugging in the local environment.
# Please do NOT commit $(moduel).mak with GEN_PREPROCESS=1
#GEN_PREPROCESS = 1

PATH_H = \
    $(PATH_audio_mdl)/pub \
    $(PATH_cc)/itf_open \
    $(PATH_fc)/pub \
    $(PATH_mserv)/inc \
    $(PATH_mserv)/itf \
    $(PATH_MsWrapper)/pub \
    $(PATH_ResMgr)/pub/ \
    $(PATH_ResMgr)/inc/ \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/DataStruct \
    $(PATH_ResMgr)/inc/HAL \
    $(PATH_ResMgr)/inc/ResMgr \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_SocketMgr)/inc/SocketCore \
    $(PATH_SocketMgr)/inc/SocketResMgr \
    $(PATH_ResMgr)/inc/Util \
    $(PATH_ResMgr)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
    $(PATH_sdk)/pub \
    $(PATH_sys)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_vml)/itf \
    $(PATH_cus_app)/inc \
    $(PATH_middleware)/esl/pub \
    $(PATH_middleware)/mmmanager/pub

MMI_PATH_H =

SRC_ASM_LIST =

REL_SRC_C_LIST = \
    CmdAdaptorCommon.c \
    SocketCmd.c \
    SocketCmdCtrlHandler.c \
    SocketCmdCusParams.c \
    SocketCmdFac.c \
    SocketCmdRspFac.c \
    SocketTaskStgr.c \
    SocketTaskStgrListener.c \
    SockMgrApPriorityTable.c \
    SockMgrBearer.c \
    SockMgrBearerConflictTable.c \
    SockMgrBearerDescriptor.c \
    SockMgrBearerFsm.c \
    SockMgrBearerItf.c \
    SockMgrBearerMgr.c \
    SockMgrComMedia.c \
    SockMgrComMediaDescriptor.c \
    SockMgrComMediaItf.c \
    SockMgrComMediaMgr.c \
    SockMgrComMediaSupportTable.c \
    SockMgrConflictMgr.c \
    SockMgrConnection.c \
    SockMgrConnectionFacItf.c \
    SockMgrConnectionFsm.c \
    SockMgrDataLink.c \
    SockMgrDataLinkFsm.c \
    SockMgrDataLinkItf.c \
    SockMgrDSPort.c \
    SockMgrFsm.c \
    SockMgrOSPort.c \
    SockMgrRes.c \
    SockMgrResCtrl.c \
    SockMgrSocketFsmItf.c \
    SockMgrSocket.c \
    SockMgrTrackPool.c \
    SockMgrUtilPort.c \
    VmlInd2SocketCmdPro.c \
    VmlMakeMsgCommon.c \
    VmlReq2SocketCmd.c \
    VmlRsp2SocketCmdRsp.c \
    DBL_Sock.c

PATH_C = \
    $(PATH_SocketMgr)/src/SocketCore \
    $(PATH_SocketMgr)/src/SocketResMgr \
    $(PATH_SocketMgr)/src/SocketUnitTest
