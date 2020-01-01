PATH_H = \
    $(PATH_audio)/pub \
    $(PATH_avp)/pub \
    $(PATH_bluetooth)/pub \
    $(PATH_bsp_mn)/pub \
    $(PATH_cc)/itf_open \
    $(PATH_core)/pub \
    $(PATH_cpu_mdl)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_esl)/pub \
    $(PATH_fc)/pub \
    $(PATH_FileMgr)/inc \
    $(PATH_FileMgr)/pub \
    $(PATH_gpd_mdl)/pub \
    $(PATH_gss)/pub \
    $(PATH_hal)/kernel/inc \
    $(PATH_hopper)/inc \
    $(PATH_hopper)/pub \
    $(PATH_image_codec)/pub \
    $(PATH_keypad_mdl)/pub \
    $(PATH_mae)/pub \
    $(PATH_mmaudio)/pub \
    $(PATH_mmicomn)/inc \
    $(PATH_mmmanager)/inc \
    $(PATH_mmmanager)/pub \
    $(PATH_mserv)/inc \
    $(PATH_mserv)/itf \
    $(PATH_MsWrapper)/pub \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/DataStruct \
    $(PATH_ResMgr)/inc/DBL \
    $(PATH_ResMgr)/inc/HAL \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/inc/ResMgr \
    $(PATH_SocketMgr)/inc/SocketCore \
    $(PATH_SocketMgr)/inc/SocketResMgr \
    $(PATH_ResMgr)/inc/Util \
    $(PATH_ResMgr)/pub \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
    $(PATH_sdk)/pub \
    $(PATH_srv)/pub \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_tscr)/pub \
    $(PATH_tscr_mdl)/pub \
    $(PATH_ucs2)/pub \
    $(PATH_vfs)/pub \
    $(PATH_drm_vfs)/pub \
    $(PATH_vml)/itf

MMI_PATH_H =

#
#   Important : This software is protected by Copyright and the information
#               contained herein is confidential. Distribution, reproduction
#               as well as exploitation and transmission of its contents is
#               not allowed except if expressly permitted. Infringments
#               result in damage claims
#               Copyright Wavecom   S.A. (c)    $JustDate:$
#

# ****************************************************************************
# *  File    :  $Workfile:$         $Revision:$
# *--------------------------------------------------------------------------*
# *  Scope   :    Description of the librarie to generate                    *
# *                                                                          *
# *  Notes   :    to launch the compilation of the current library,          *
# *               type from output directory :                               *
# *                      make   -r  -f  ..//gen.mak TARGET=<target>          *
# *                                                                          *
# *                                                                          *
# *                                                                          *
# *  Changes     :                                                           *
# *--------------------------------------------------------------------------*
# *  Version VSS    | Date            | Author |    Modification             *
# *--------------------------------------------------------------------------*
# * $Log:$
#
# ****************************************************************************



#------------------------------------------------------------------------------
#   Description of some variables own to the librairie
#------------------------------------------------------------------------------
# Library module (lib) or Binary    module (bin)
PROCESS     = lib


#------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#------------------------------------------------------------------------------
REL_SRC_C_LIST += \
    ABL_Tv.c \
    ABL_Aud.c \
    ABL_Cam.c \
    ABL_Common.c \
    ABL_Ctrl.c \
    ABL_Device.c \
    ABL_Fmr.c   \
    ABL_Gps.c \
    ABL_Gss.c \
    ABL_RFID.c \
    ABL_Usb.c \
    ABL_Vdo.c \
    ABL_VdoChat.c \
    ABL_Vfs.c \
    ABL_Vtm.c \
    ABL_WiFi.c \
    ABL_CusParms.c \
    DataStructFactory.c \
    DList.c \
    GenericStrategier.c \
    QueueStrategier.c \
    StackStrategier.c \
    DBL_Tv.c \
    DBL_Aud.c \
    DBL_Cam.c \
    DBL_Common.c \
    DBL_Fmr.c \
    DBL_Gss.c \
    DBL_Gps.c \
    DBL_Usb.c \
    DBL_Vdo.c \
    DBL_VdoChat.c \
    DBL_Vfs.c \
    DBL_Vtm.c \
    HAL_AudResCtrl.c \
    HAL_Main.c \
    HAL_MmpResCtrl.c \
    TvFsm.c \
    AudioDevCtrlFsm.c \
    AudioFsm.c \
    CameraDevCtrlFsm.c \
    AudioA2DPFsm.c \
    CameraFsm.c \
    CodecDevCtrlFsm.c \
    CodecFsm.c \
    FmRadioFsm.c \
    FmRadioDevCtrlFsm.c \
    GpsFsm.c \
    MediaAppClientMgr.c \
    MediaAppStgr.c \
    MediaCmd.c \
    MediaCmdFac.c \
    MediaCmdListener.c \
    MediaCtrlHandler.c \
    MediaFsm.c \
    MediaMmpCapability.c \
    MediaPriorityCtrl.c \
    MediaRspFac.c \
    MediaTaskClientMgr.c \
    MediaTaskStgr.c \
    MediaUtil.c \
    PseduoDevResCtrl.c \
    UsbDevCtrlFsm.c \
    UsbFsm.c \
    VfsFsm.c \
    VideoDevCtrlFsm.c \
    VideoFsm.c \
    VideoChatFsm.c \
    VtmFsm.c \
    CmdMgrStgr_CtrlHandler.c \
    CmdMgrStgr_EvtHandler.c \
    ResMgr_AppListener.c \
    ResMgr_AppIdConfig.c \
    ResMgr_AppStgr.c \
    ResMgr_AsyncStgr.c \
    ResMgr_Cmd.c \
    ResMgr_CmdMgr.c \
    ResMgr_CmdMgrFac.c \
    ResMgr_CmdMgrStgr.c \
    ResMgr_Common.c \
    ResMgr_DevMediator.c \
    ResMgr_EvtFac.c \
    ResMgr_Task.c \
    ResMgr_TaskStgr.c \
    ResMgr_CtrlHandler.c \
    TaskStgr_CmdHandler.c \
    TaskStgr_DevMediator.c \
    TaskStgr_RspHandler.c \
    BitStream.c \
    GenEvtHdlr.c \
    GenEvtHdlrUtil.c \
    GenResCtrl.c \
    Listener.c \
    Mediator.c \
    ObjArray.c \
    StateMachine.c \
    AudioRecFsm.c \
            srv_filemgr_async.c \
            srv_filemgr_sync.c \
            srv_filemgr_util.c \
            srv_filemgr_exec.c \
            srv_filemgr_register_path.c \
            srv_filemgr_mark.c \
            srv_filemgr_fstream.c \
            srv_mmi_filemgr.c \
            srv_fs_test_case.c \
            RingBuffer.c \
            srv_hopper_task.c \
            srv_mmi_hopper.c \
            Simu_Aud.c \
            Simu_Cam.c \
            Simu_Cmn.c \
            Simu_Fmr.c \
            Simu_Gps.c \
            Simu_Gss.c \
            Simu_Tv.c \
            Simu_Usb.c \
            Simu_Vdo.c \
            Simu_VdoChat.c \
            Simu_Vfs.c \
            Simu_Vtm.c

SRC_ASM_LIST =


#ABI(Application Binary Interface) check
SRC_C_LIST += abi_headers_ResMgr.c
