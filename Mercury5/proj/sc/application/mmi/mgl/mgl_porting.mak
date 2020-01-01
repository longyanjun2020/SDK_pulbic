#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST += \
	mgl_porting.c	

MMI_PATH_H += \
	$(PATH_gss)/pub \
	$(PATH_mmicomn)/inc\
	$(PATH_widget)/inc\
	$(PATH_srv)/inc \
  $(PATH_srv)/pub \
  $(PATH_mae)/pub \
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
	$(PATH_mgl)/mPorting/inc

PATH_C =\
	$(PATH_mgl)/mPorting/src

CFLAGS += \
    --no_debug
    
