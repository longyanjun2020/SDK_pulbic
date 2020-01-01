#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST += \
	mgl_Animation_loader.c\
	mgl_MD2_loader.c\
	mgl_3DS_loader.c\
	mgl_Core_Matrix.c\
	mgl_Core_Rendering.c\
	mgl_Core_Shape.c\
	mgl_Core_Transform.c\
	mgl_Core_Types.c\
	mgl_Effect_Stencil.c\
	mgl_Effect_BezierSurface.c\
        mgl_Effect_ClothModeling.c\
	mgl_Effect_WaterWave.c\
	mgl_Effect_FishEye.c\
	mgl_Effect_BumpMapping.c\
        mgl_Effect_Magnify.c\
	mgl_Effect_ParticleSystem.c\
	mgl_Egl.c\
	mgl_FontMgr.c\
	mgl_Scene_Camera.c\
	mgl_Scene_Environment.c\
	mgl_Scene_Light.c\
	mgl_Scene_NodeMgr.c\
	mgl_Texture_ImgMgr.c\
	mgl_Utility_file.c\
	mgl_Utility_hash.c\
	mgl_Utility_list.c\
	mgl_Utility_mm.c\
	mgl_Utility_sort.c\
	mgl_Utility_unicode.c

MMI_PATH_H += \
	$(PATH_mmicomn)/inc\
	$(PATH_widget)/inc\
	$(PATH_srv)/CodecSrv/inc \
	$(PATH_srv)/inc \
  $(PATH_srv)/pub \
	$(PATH_srv)/ShortcutsSrv/inc \
	$(PATH_mae)/src\
	$(PATH_mgl)/mAnimation/inc\
	$(PATH_mgl)/mCore/inc\
	$(PATH_mgl)/mEffect/inc\
	$(PATH_mgl)/mEgl/inc\
	$(PATH_mgl)/mFont/inc\
	$(PATH_mgl)/mScene/inc\
	$(PATH_mgl)/mTexture/inc\
	$(PATH_mgl)/mUtility/inc\
        $(PATH_mgl)/mParticle/inc\
        $(PATH_mgl)/mPorting/inc\
	$(PATH_mgl)/pub

PATH_C =\
	$(PATH_mgl)/mAnimation/src\
	$(PATH_mgl)/mCore/src\
	$(PATH_mgl)/mEffect/src\
	$(PATH_mgl)/mEgl/src\
	$(PATH_mgl)/mFont/src\
	$(PATH_mgl)/mScene/src\
	$(PATH_mgl)/mTexture/src\
	$(PATH_mgl)/mUtility/src\
        $(PATH_mgl)/mParticle/src\

#ABI(Application Binary Interface) check
SRC_C_LIST += abi_headers_mgl.c
