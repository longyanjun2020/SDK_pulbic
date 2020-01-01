# Library module (lib) or Binary module (bin)
PROCESS = lib

#Varaible description:
#  SRC_C_LIST:
#    the source files of this library
#  PATH_C:
#    the directory that contains all the source files
#  PATH_H:
#    the directory that contains all the header files
#
#PATH_H should contain only
#  (1) the public and private header directories of this library,
#     usually called {priv, inc, src}, and
#  (2) public header directories of other libraries,
#     called pub (or inc, if pub is not present)
#
#Other related variable:
#  PATH_AutotestApp:
#  the directory that contains the file AutotestApp.mak.
#  The build process needs this variable to find the makefile
#  and compile AutotestApp.lib.
#  Related files:
#  //EMMI/mainline/proj/sc/customer/product/common/mak/paths.mak
#  //EMMI/mainline/proj/sc/customer/product/common/mak/lib_paths.mak
#  //EMMI/mainline/proj/sc/customer/product/common/mak/paths_pub.mak
#
#If you run into a problem related to trace id, please edit
#  //EMMI/mainline/proj/tng/remtrace/remtraceID
#  to enlarge the range of the trace id for this library.

#MMI_PATH_H is deprecated, keep it for the purpose of compatibility
MMI_PATH_H = 







SRC_C_LIST = \
    mmi_autotestapp.c

PATH_C = $(PATH_AutotestApp)/src






ifeq ($(call FIND_COMPILER_OPTION, __COMPONENT_BASE_CONFIGURATION__), TRUE)
PATH_H += $(PATH_cust_drv)/keypad/inc
else
PATH_H += $(PATH_cust_drv)/inc
endif

ifeq ($(filter __NCC_3RD_JAVA_PORTING_LAYER__ ,$(PP_OPT_COMMON)),__NCC_3RD_JAVA_PORTING_LAYER__)
PATH_H +=\
	$(PATH_java)/nccjpl/inc
endif

ifeq ($(filter __JAVA_MMI__ ,$(PP_OPT_COMMON)),__JAVA_MMI__)
PATH_H += \
    $(PATH_JavaAmsApp)/inc \
    $(PATH_JavaFactoryApp)/inc \
    $(PATH_java_common)/inc
endif

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
PATH_H += \
    $(PATH_mgl)/mAnimation/inc\
    $(PATH_mgl)/mCore/inc\
    $(PATH_mgl)/mEffect/inc\
    $(PATH_mgl)/mEgl/inc\
    $(PATH_mgl)/mFont/inc\
    $(PATH_mgl)/mScene/inc\
    $(PATH_mgl)/mTexture/inc\
    $(PATH_mgl)/mUtility/inc
endif

ifeq ($(filter __SXMENGINE__ ,$(PP_OPT_COMMON)),__SXMENGINE__)
PATH_H += $(PATH_sxmengine)/inc
endif

ifeq ($(filter __TTS__ ,$(PP_OPT_COMMON)),__TTS__)
PATH_H += $(PATH_tts)/inc
endif

ifeq ($(filter __ATV_CMMB__ ,$(PP_OPT_COMMON)), __ATV_CMMB__)
PATH_H += $(PATH_zlib)/inc
endif


