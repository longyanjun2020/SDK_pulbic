PATH_H = \
    $(PATH_audio)/itf_open \
    $(PATH_audio)/pub \
    $(PATH_batt)/pub \
    $(PATH_battery)/pub \
    $(PATH_bluetooth)/pub \
    $(PATH_build) \
    $(PATH_bus)/inc \
    $(PATH_bus)/pub \
    $(PATH_core)/pub \
    $(PATH_cpu_mdl)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_CusDefine)/pub \
    $(PATH_cust_mmi)/inc \
    $(PATH_esl)/pub \
    $(PATH_fc)/pub \
    $(PATH_FileMgr)/pub \
    $(PATH_flash)/pub \
    $(PATH_fms)/itf \
    $(PATH_fms)/itf_open \
    $(PATH_fms)/pub \
    $(PATH_gpd_mdl)/pub \
    $(PATH_gss)/pub \
    $(PATH_hal)/audio/inc \
    $(PATH_hal)/io/pub \
    $(PATH_hal)/jpe/inc \
    $(PATH_hal)/kernel/inc \
    $(PATH_hal)/pm/inc \
    $(PATH_hwlaud)/inc \
    $(PATH_i18n)/inc \
    $(PATH_image_codec)/pub \
    $(PATH_io)/pub \
    $(PATH_mae)/pub \
    $(PATH_mae)/src \
    $(PATH_mmi_res) \
    $(PATH_mmi_res)/resourceLib \
    $(PATH_mmicomn)/cfg \
    $(PATH_mmicomn)/inc \
    $(PATH_mmicomn)/res \
    $(PATH_mmmanager)/inc \
    $(PATH_mmmanager)/pub \
    $(PATH_model)/pub \
    $(PATH_mserv)/inc \
    $(PATH_MsWrapper)/pub \
    $(PATH_NCCBrowser_target)/inc \
    $(PATH_NCCEmail_target)/inc \
    $(PATH_NCCMms_target)/inc \
    $(PATH_pm)/inc \
    $(PATH_pm_mdl)/inc \
    $(PATH_pgl)/pDispatcher/inc \
    $(PATH_pgl)/pEngine/inc \
    $(PATH_pgl)/pGui/inc \
    $(PATH_pgl)/pPhysics/inc \
    $(PATH_pgl)/pResource/inc \
    $(PATH_pgl)/pUtility/inc \
    $(PATH_pgl)/pub \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/HAL \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/inc/Util \
    $(PATH_ResMgr)/pub \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
    $(PATH_sdk)/pub \
    $(PATH_srv)/pub \
    $(PATH_SrvWrapper)/pub \
    $(PATH_storage)/pub \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_tscr)/pub \
    $(PATH_utility)/inc \
    $(PATH_vfs)/pub \
    $(PATH_drm_util)/pub \
    $(PATH_wap)/itf \
    $(PATH_widget)/inc \
    $(PATH_widget)/inc/priv \
    $(PATH_widget)/pub \
    $(PATH_pgl)/mChipmunk/inc \
    $(PATH_fc)/pub \
    $(PATH_mae)/pub \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_mgl)/pub
    
MMI_PATH_H = 
#------------------------------------------------------------------------------
#   Description of some variables owned by the library
#------------------------------------------------------------------------------


# Library module (lib) or Binary module (bin)
PROCESS     = lib

#------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST = \
    cpConstraint.c \
	cpDampedRotarySpring.c \
	cpDampedSpring.c \
	cpGearJoint.c \
	cpGrooveJoint.c \
	cpPinJoint.c \
	cpPivotJoint.c \
	cpRatchetJoint.c \
	cpRotaryLimitJoint.c \
	cpSimpleMotor.c \
	cpSlideJoint.c \
	chipmunk.c \
	cpArbiter.c \
	cpArray.c \
	cpBB.c \
	cpBBTree.c \
	cpBody.c \
	cpCollision.c \
	cpHashSet.c \
	cpPolyShape.c \
	cpShape.c \
	cpSpace.c \
	cpSpaceComponent.c \
	cpSpaceHash.c \
	cpSpaceQuery.c \
	cpSpaceStep.c \
	cpSpatialIndex.c \
	cpSweep1D.c \
	cpVect.c \
    pgl_Dispatcher_Keypad.c \
    pgl_Dispatcher_Touch.c \
    pgl_Dispatcher_GSensor.c \
    pgl_Engine_Action.c \
    pgl_Engine_Core.c \
    pgl_Engine_Scene.c \
    pgl_Gui_Actor.c \
    pgl_Gui_Render.c \
    pgl_Physics_Actor.c \
    pgl_Physics_Render.c \
    pgl_Resource_TexMgr.c \
    pgl_Utility_Container.c

PATH_C =\
    $(PATH_pgl)/mChipmunk/src\
    $(PATH_pgl)/mChipmunk/src/constraints\
    $(PATH_pgl)/pDispatcher/src\
    $(PATH_pgl)/pEngine/src\
    $(PATH_pgl)/pGui/src\
    $(PATH_pgl)/pPhysics/src\
    $(PATH_pgl)/pResource/src\
    $(PATH_pgl)/pUtility/src
    
ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
MMI_PATH_H +=\
    $(PATH_mae)/inc\
    $(PATH_mmicomn)/inc\
    $(PATH_widget)/inc\
    $(PATH_srv)/CodecSrv/inc \
    $(PATH_srv)/inc \
    $(PATH_srv)/pub \
    $(PATH_pgl)/mChipmunk/inc\
    $(PATH_mgl)/mAnimation/inc\
    $(PATH_mgl)/mCore/inc\
    $(PATH_mgl)/mEffect/inc\
    $(PATH_mgl)/mEgl/inc\
    $(PATH_mgl)/mFont/inc\
    $(PATH_mgl)/mScene/inc\
    $(PATH_mgl)/mTexture/inc\
    $(PATH_mgl)/mUtility/inc\
    $(PATH_pgl)/pDispatcher/inc \
    $(PATH_pgl)/pEngine/inc \
    $(PATH_pgl)/pGui/inc \
    $(PATH_pgl)/pPhysics/inc \
    $(PATH_pgl)/pResource/inc \
    $(PATH_pgl)/pUtility/inc \
    $(PATH_pgl)/pub
    
endif

#ABI(Application Binary Interface) check
SRC_C_LIST += abi_headers_pgl.c
