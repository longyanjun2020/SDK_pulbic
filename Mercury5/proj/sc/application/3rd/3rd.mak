
#
#	Important :	This software is protected by Copyright and the information
#	            contained herein is confidential. Distribution, reproduction
#	            as well as exploitation and transmission of its	contents is
#	            not allowed except if expressly permitted. Infringments
#	            result in damage claims.
#
#	            Copyright (c) 2009 MStar

# ****************************************************************************

PRODUCT_SC_3RD = \
  utility\
  ms_conv\
  i18n\
  i18n_cus\
  zlib

ifeq ($(filter __WAP__ ,$(PP_OPT_COMMON)),__WAP__)
PRODUCT_SC_3RD += wap
endif

ifeq ($(filter __SDK_API__ ,$(PP_OPT_COMMON)),__SDK_API__)
PRODUCT_SC_3RD += sdk
endif

ifeq ($(filter __MSERVICES__ ,$(PP_OPT_COMMON)),__MSERVICES__)
PRODUCT_SC_3RD += mserv
endif

ifeq ($(filter __HTTP_STREAMING__ ,$(PP_OPT_COMMON)),__HTTP_STREAMING__)
PRODUCT_SC_3RD += http
endif

ifeq ($(filter __RTSP_STREAMING__ ,$(PP_OPT_COMMON)),__RTSP_STREAMING__)
PRODUCT_SC_3RD += rtsp
endif

ifeq ($(filter __INDIAN_CALENDAR__ ,$(PP_OPT_COMMON)),__INDIAN_CALENDAR__)
PRODUCT_SC_3RD += IndCalendar
endif

ifeq ($(filter __ENABLE_POLARSSL__ ,$(PP_OPT_COMMON)),__ENABLE_POLARSSL__)
PRODUCT_SC_3RD += ssl
endif

# for DM2
ifeq ($(filter ENABLE_DM2 ,$(PP_OPT_COMMON)),ENABLE_DM2)
PRODUCT_SC_3RD += dm2
endif

ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)),__EMAIL_MMI__)
PRODUCT_SC_3RD += \
  email
endif

ifeq ($(filter __NCCQQ_MMI__ ,$(PP_OPT_COMMON)), __NCCQQ_MMI__)
PRODUCT_SC_3RD += qq
endif

ifeq ($(filter __APP_MMI_TUDOU__ ,$(PP_OPT_COMMON)), __APP_MMI_TUDOU__)
PRODUCT_SC_3RD += tudou
endif

ifeq ($(filter __SDK_MMI_VENDOR_ENTRY__, $(PP_OPT_COMMON)), __SDK_MMI_VENDOR_ENTRY__)
PRODUCT_SC_3RD += vendor
endif

ifeq ($(filter __MAP_CORE__, $(PP_OPT_COMMON)), __MAP_CORE__)
PRODUCT_SC_3RD += map
endif

#expat has duplicated in WAP library
ifeq ($(filter __MAP__, $(PP_OPT_COMMON)), __MAP__)
ifneq ($(filter __WAP_MMI_CDWAP__, $(PP_OPT_COMMON)), __WAP_MMI_CDWAP__)
PRODUCT_SC_3RD += expat
endif
endif

# 3RD group source code
PATH_ime = $(PATH_3rd)/ime
PATH_handwriting = $(PATH_3rd)/handwriting
PATH_sinovoice = $(PATH_3rd)/handwriting/sinovoice
PATH_vendor = $(PATH_3rd)/vendor
PATH_mserv = $(PATH_3rd)/mserv
PATH_utility = $(PATH_3rd)/utility
PATH_ms_conv = $(PATH_3rd)/utility
PATH_sdk = $(PATH_3rd)/sdk
PATH_wap = $(PATH_3rd)/wap
PATH_math_hwfp = $(PATH_3rd)/r2_math
ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)),__EMAIL_MMI__)
PATH_email = $(PATH_3rd)/email
endif

ifeq ($(filter __NCCQQ_MMI__ ,$(PP_OPT_COMMON)), __NCCQQ_MMI__)
PATH_qq          = $(PATH_3rd)/qq
endif

ifeq ($(filter __APP_MMI_TUDOU__ ,$(PP_OPT_COMMON)), __APP_MMI_TUDOU__)
PATH_tudou          = $(PATH_3rd)/tudou
endif

PATH_map = $(PATH_3rd)/map
PATH_expat = $(PATH_utility)/expat
PATH_http = $(PATH_3rd)/http
PATH_i18n = $(PATH_utility)/i18n
PATH_i18n_cus = $(PATH_utility)/i18n
PATH_zlib = $(PATH_utility)/zlib
PATH_dm2  = $(PATH_3rd)/dm2
PATH_srs_wowhd_3rd = $(PATH_3rd)/srs_wowhd
ifeq ($(filter __ETRUMP__ ,$(PP_OPT_COMMON)),__ETRUMP__)
PATH_etrump = $(PATH_3rd)/etrump
endif

ifeq ($(filter __RTSP_STREAMING__ ,$(PP_OPT_COMMON)),__RTSP_STREAMING__)
PATH_rtsp = $(PATH_3rd)/rtsp
endif

ifeq ($(filter __INDIAN_CALENDAR__ ,$(PP_OPT_COMMON)),__INDIAN_CALENDAR__)
PATH_IndCalendar = $(PATH_3rd)/IndCalendar
endif

ifeq ($(filter __ENABLE_POLARSSL__ ,$(PP_OPT_COMMON)),__ENABLE_POLARSSL__)
PATH_ssl  = $(PATH_3rd)/ssl
endif

# 3RD group source code
PATH_C +=\
    $(PATH_vendor)/src\
    $(PATH_mserv)/src\
    $(PATH_utility)/src\
    $(PATH_sdk)/src\
    $(PATH_wap)/src\
    $(PATH_http)/src\
    $(PATH_zlib)/src

ifeq ($(filter __RTSP_STREAMING__ ,$(PP_OPT_COMMON)),__RTSP_STREAMING__)
PATH_C +=\
    $(PATH_rtsp)/src
endif

ifeq ($(filter __INDIAN_CALENDAR__ ,$(PP_OPT_COMMON)),__INDIAN_CALENDAR__)
PATH_C +=\
    $(PATH_IndCalendar)/src
endif

ifeq ($(filter __ENABLE_POLARSSL__ ,$(PP_OPT_COMMON)),__ENABLE_POLARSSL__)
PATH_C +=\
	$(PATH_ssl)/library
endif

ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)),__EMAIL_MMI__)
PATH_C +=\
    $(PATH_email)/src
endif

ifeq ($(filter __NCCQQ_MMI__ ,$(PP_OPT_COMMON)), __NCCQQ_MMI__)
PATH_C += $(PATH_qq)/src
endif

ifeq ($(filter __APP_MMI_TUDOU__ ,$(PP_OPT_COMMON)), __APP_MMI_TUDOU__)
PATH_C += $(PATH_tudou)/src
endif

PATH_H +=\
    $(PATH_handwriting)/sinovoice/inc\
    $(PATH_vendor)/inc\
    $(PATH_vendor)/itf\
    $(PATH_mserv)/inc\
    $(PATH_mserv)/itf\
    $(PATH_NCCMms_target)/inc\
    $(PATH_NCCBrowser_target)/inc\
    $(PATH_utility)/inc\
    $(PATH_utility)/itf\
    $(PATH_sdk)/inc\
    $(PATH_sdk)/pub\
    $(PATH_wap)/inc\
    $(PATH_wap)/itf\
    $(PATH_http)/inc\
    $(PATH_zlib)/inc\
    $(PATH_i18n)/inc\
    $(PATH_avp)/pub

ifeq ($(filter __RTSP_STREAMING__ ,$(PP_OPT_COMMON)),__RTSP_STREAMING__)
PATH_H +=\
    $(PATH_rtsp)/inc
endif

ifeq ($(filter __ENABLE_POLARSSL__ ,$(PP_OPT_COMMON)),__ENABLE_POLARSSL__)
PATH_H +=\
    $(PATH_ssl)/include
endif

ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)),__EMAIL_MMI__)
PATH_H +=\
    $(PATH_NCCEmail_target)/inc\
    $(PATH_email)/inc\
    $(PATH_email)/itf\
    $(PATH_SrvWrapper)/pub\
    $(PATH_mmicomn)/cfg\
    $(PATH_mmi_res)\
    $(PATH_build)\
    $(PATH_FileMgr)/pub\
    $(PATH_srv)/pub\
    $(PATH_customer_define_folder)/pub\
    $(PATH_mmi_res)/resourcelib
endif

ifeq ($(filter __NCCQQ_MMI__ ,$(PP_OPT_COMMON)), __NCCQQ_MMI__)
PATH_H +=\
    $(PATH_application)/mms/inc\
    $(PATH_qq)/inc\
    $(PATH_qq)/itf\
    $(PATH_build)
endif

PATH_EXT_LIB +=\
    $(PATH_handwriting)/sinovoice/lib\
    $(PATH_vendor)/lib\
    $(PATH_app)/EmuApp/lib\
    $(PATH_bluetooth)/lib\
    $(PATH_mserv)/lib\
    $(PATH_wap)/lib\
    $(PATH_math_hwfp)/lib\
    $(PATH_utility)/lib\
    $(PATH_core_lib_algorithm)/adas\
    $(PATH_core_lib_algorithm)/mdtc\
    $(PATH_core_lib_algorithm)/edog\
    $(PATH_core_system_vid_play)/inc\
    $(PATH_vendor_speech)/inc\
    $(PATH_LibSourceInc_wifi_WiFi-RTL8189_lib)\
    $(PATH_LibSourceInc_wifi_WiFi-BCM-SDIO_lib)\
    $(PATH_LibSourceInc_wifi_WiFi-ATBM6022_lib)\
    $(PATH_core_lib)/sdk_lib

ifeq ($(filter __EMAIL_MMI__ ,$(PP_OPT_COMMON)),__EMAIL_MMI__)
PATH_EXT_LIB +=\
    $(PATH_email)/lib
endif

ifeq ($(filter __ETRUMP__ ,$(PP_OPT_COMMON)),__ETRUMP__)
PATH_EXT_LIB +=\
    $(PATH_etrump)/lib
endif

ifeq ($(filter __NCCQQ_MMI__ ,$(PP_OPT_COMMON)), __NCCQQ_MMI__)
PATH_EXT_LIB += $(PATH_qq)/lib
endif



ifeq ($(filter __ATV__ ,$(PP_OPT_COMMON)),__ATV__)
PATH_EXT_LIB +=\
    $(PATH_atv)/lib
endif

# for DM2
ifeq ($(filter ENABLE_DM2 ,$(PP_OPT_COMMON)),ENABLE_DM2)
PATH_C +=\
    $(PATH_dm2)/src
PATH_H +=\
	$(PATH_dm2)/inc
PATH_EXT_LIB +=\
	$(PATH_dm2)/lib
endif

# for srs wowhd
ifeq ($(filter ENABLE_SRSWOWHD ,$(PP_OPT_COMMON)),ENABLE_SRSWOWHD)
PATH_H +=\
    $(PATH_srs_wowhd_3rd)/srs_common/inc\
    $(PATH_srs_wowhd_3rd)/srs_sa_trubass/inc\
    $(PATH_srs_wowhd_3rd)/srs_srs3d/inc\
    $(PATH_srs_wowhd_3rd)/srs_wowhd/inc

PATH_EXT_LIB +=\
    $(PATH_srs_wowhd_3rd)/srs_common/lib\
    $(PATH_srs_wowhd_3rd)/srs_sa_trubass/lib\
    $(PATH_srs_wowhd_3rd)/srs_srs3d/lib\
	$(PATH_srs_wowhd_3rd)/srs_wowhd/lib
endif
ifeq ($(filter __MMI_SCRIPT_EASY__, $(PP_OPT_COMMON)), __MMI_SCRIPT_EASY__)
PATH_EXT_LIB +=\
    $(PATH_ime)/kmx/lib
endif

# for IME CSTAR
ifeq ($(filter __IME_MMI_CSTAR__, $(PP_OPT_COMMON)), __IME_MMI_CSTAR__)
PRODUCT_SC_3RD += ime
PATH_C +=\
    $(PATH_ime)/kmx/src
PATH_EXT_LIB +=\
    $(PATH_ime)/kmx/lib
endif

# for IME MY
ifeq ($(filter __IME_MMI_MY__, $(PP_OPT_COMMON)), __IME_MMI_MY__)
PRODUCT_SC_3RD += ime
PATH_C +=\
    $(PATH_ime)/my/src
PATH_H +=\
    $(PATH_ime)/my/inc\
    $(PATH_ime)/my/itf
PATH_EXT_LIB +=\
    $(PATH_ime)/my/lib
endif

# for IME SG
ifeq ($(filter __IME_MMI_SG__ ,$(PP_OPT_COMMON)),__IME_MMI_SG__)
PRODUCT_SC_3RD += ime
PATH_C +=\
    $(PATH_ime)/sg/src
PATH_H +=\
    $(PATH_ime)/sg/inc\
    $(PATH_ime)/sg/itf
PATH_EXT_LIB +=\
    $(PATH_ime)/sg/lib
endif

# for IME ZI
ifeq ($(filter __IME_MMI_ZI__, $(PP_OPT_COMMON)), __IME_MMI_ZI__)
PRODUCT_SC_3RD += ime
PATH_C +=\
    $(PATH_ime)/zi8/src
PATH_H +=\
	$(PATH_ime)/zi8/inc\
    $(PATH_ime)/zi8/itf
PATH_EXT_LIB +=\
	$(PATH_ime)/zi8/lib
endif

# for JAVA
ifeq ($(filter __JAVA_MMI__, $(PP_OPT_COMMON)), __JAVA_MMI__)
PATH_java = $(PATH_3rd)/java
ifneq ($(filter __DALVIK__ ,$(PP_OPT_COMMON)),__DALVIK__)
PATH_java_common = $(PATH_3rd)/java/common

PATH_C +=\
	  $(PATH_java_common)/src

PATH_H +=\
	  $(PATH_java_common)/inc

else
PATH_java_common = $(PATH_3rd)/dalvik
PATH_H +=\
	  $(PATH_mgl)/megl/inc
endif

# for NCC 3rd JAVA porting layer
ifeq ($(filter __NCC_3RD_JAVA_PORTING_LAYER__ ,$(PP_OPT_COMMON)),__NCC_3RD_JAVA_PORTING_LAYER__)

PRODUCT_SC_3RD += nccjpl

PATH_nccjpl   = $(PATH_3rd)/java/nccjpl

PATH_C +=	  $(PATH_nccjpl)/src

PATH_H +=\
	  $(PATH_nccjpl)/inc\
	  $(PATH_nccjpl)/itf \
      ${PATH_build}

ifeq ($(filter __NCC_3RD_JAVA_PORTING_LAYER_S__ ,$(PP_OPT_COMMON)),__NCC_3RD_JAVA_PORTING_LAYER_S__)
PATH_EXT_LIB +=    $(PATH_nccjpl)/lib_sj
endif
ifeq ($(filter __NCC_3RD_JAVA_PORTING_LAYER_M__ ,$(PP_OPT_COMMON)),__NCC_3RD_JAVA_PORTING_LAYER_M__)
PATH_EXT_LIB +=    $(PATH_nccjpl)/lib_mj
endif
endif

# for JAVA Delta
ifeq ($(filter __JAVA_DELTA__, $(PP_OPT_COMMON)), __JAVA_DELTA__)
ifneq ($(filter __DALVIK__ ,$(PP_OPT_COMMON)),__DALVIK__)
PRODUCT_SC_3RD += \
	Delta\
	Delta_cus

PATH_Delta = $(PATH_3rd)/java/Delta
PATH_Delta_cus = $(PATH_Delta)

PATH_C +=\
	  $(PATH_Delta)/src

PATH_H +=\
	  $(PATH_Delta)/inc\
	  $(PATH_Delta)/itf

PATH_EXT_LIB +=\
    $(PATH_Delta)/lib

endif
endif

# for JAVA Oakmont
ifeq ($(filter __JAVA_OAKMONT__, $(PP_OPT_COMMON)), __JAVA_OAKMONT__)

PRODUCT_SC_3RD += Oakmont

PATH_Oakmont = $(PATH_3rd)/java/Oakmont

PATH_C +=\
	  $(PATH_Oakmont)/src\
	  $(PATH_Oakmont)/src/jsc\
	  $(PATH_Oakmont)/src/ksc\
	  $(PATH_Oakmont)/src/data

PATH_H +=\
	  $(PATH_Oakmont)/inc\
	  $(PATH_Oakmont)/itf


# CLDC-HI version       ifeq ($(filter __JAVA_OAKMONT_SUP_CLDC_HI__, $(PP_OPT_COMMON)), __JAVA_OAKMONT_SUP_CLDC_HI__)

# CLDC version

ifeq ($(filter __JAVA_OAKMONT_SCOPE_JAP0__, $(PP_OPT_COMMON)), __JAVA_OAKMONT_SCOPE_JAP0__)
PATH_EXT_LIB +=\
    $(PATH_Oakmont)/lib/target/jap0
endif

ifeq ($(filter __JAVA_OAKMONT_SCOPE_JTWI__, $(PP_OPT_COMMON)), __JAVA_OAKMONT_SCOPE_JTWI__)
PATH_EXT_LIB +=\
    $(PATH_Oakmont)/lib/target/jtwi
endif

ifeq ($(filter __JAVA_OAKMONT_SCOPE_JAP1_HI__, $(PP_OPT_COMMON)), __JAVA_OAKMONT_SCOPE_JAP1_HI__)
PATH_EXT_LIB +=\
    $(PATH_Oakmont)/lib/target/jap1_hi
endif

#ifeq ($(filter __JAVA_OAKMONT_SCOPE_JTWI_184__, $(PP_OPT_COMMON)), __JAVA_OAKMONT_SCOPE_JTWI_184__)
#PATH_EXT_LIB +=\
#    $(PATH_Oakmont)/lib/target/jtwi_184
#endif


ifeq ($(filter __JAVA_OAKMONT_SCOPE_JAP2__, $(PP_OPT_COMMON)), __JAVA_OAKMONT_SCOPE_JAP2__)
PATH_EXT_LIB +=\
    $(PATH_Oakmont)/lib/target/jap2
endif

#JAP2C for developement
ifeq ($(filter __JAVA_OAKMONT_SCOPE_JAP2C__, $(PP_OPT_COMMON)), __JAVA_OAKMONT_SCOPE_JAP2C__)
PATH_EXT_LIB +=\
    $(PATH_Oakmont)/lib/target/jap2c
endif

endif # __JAVA_OAKMONT__
endif # __JAVA__


# for Fake vendor
ifeq ($(filter __FAKE_VENDOR__, $(PP_OPT_COMMON)), __FAKE_VENDOR__)

PRODUCT_SC_3RD += fakevendor

PATH_fakevendor = $(PATH_3rd)/fakevendor

PATH_C +=\
    $(PATH_fakevendor)/src

PATH_H +=\
    $(PATH_fakevendor)/inc\
    $(PATH_fakevendor)/itf

PATH_EXT_LIB +=\
    $(PATH_fakevendor)/lib

endif

### for video telephony
ifeq ($(filter __VT_3G324M__ ,$(PP_OPT_COMMON)),__VT_3G324M__)

PATH_3g324m = $(PATH_3rd)/3g324m

PATH_H +=\
    $(PATH_3g324m)/include/3g324m\
    $(PATH_3g324m)/include/asn1\
    $(PATH_3g324m)/include/common\
    $(PATH_3g324m)/include/h245\
    $(PATH_3g324m)/include/h323addons

PATH_EXT_LIB  +=\
    $(PATH_3g324m)/lib

endif

# for __TENCENT_MCARE__ QQ test
ifeq ($(filter __TENCENT_MCARE__ ,$(PP_OPT_COMMON)),__TENCENT_MCARE__)
ifeq ($(filter __TENCENT_MCARE_QXIN__ ,$(PP_OPT_COMMON)),__TENCENT_MCARE_QXIN__)
# v31

PRODUCT_SC_3RD += tencentmcare

PATH_tencentmcare = $(PATH_3rd)/tencentmcare_qxin

PATH_EXT_LIB +=\
    $(PATH_tencentmcare)/lib

else
# v30
PRODUCT_SC_3RD += tencentmcare

PATH_tencentmcare = $(PATH_3rd)/tencentmcare

PATH_EXT_LIB +=\
    $(PATH_tencentmcare)/lib
endif

endif

# for MGL
ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
ifeq ($(filter __FEATURE_MGLS__ ,$(PP_OPT_COMMON)),__FEATURE_MGLS__)

PATH_EXT_LIB +=\
$(PATH_mgl)/lib

endif
endif

# for SwitchMainmenu and Screen effect
PATH_EXT_LIB +=\
$(PATH_widget)/lib

# for Skyengine
ifeq ($(filter __SKYENGINE__, $(PP_OPT_COMMON)), __SKYENGINE__)

PRODUCT_SC_3RD += skyengine

PATH_skyengine = $(PATH_3rd)/skyengine

PATH_C +=\
    $(PATH_skyengine)/src

PATH_H +=\
    $(PATH_skyengine)/inc

PATH_EXT_LIB +=\
    $(PATH_skyengine)/lib

endif

# for ZMOL
ifeq ($(filter __ZMOL__ ,$(PP_OPT_COMMON)),__ZMOL__)

PRODUCT_SC_3RD += zmol

PATH_zmol  = $(PATH_3rd)/zmol

PATH_C +=\
    $(PATH_zmol)/interface

PATH_H +=\
    $(PATH_zmol)/include

PATH_H +=\
    $(PATH_zmol)/interface

PATH_EXT_LIB +=\
    $(PATH_zmol)/lib

endif

ifeq ($(filter __ZYUE_ENGINE__ ,$(PP_OPT_COMMON)),__ZYUE_ENGINE__)
    PRODUCT_SC_3RD +=\
	zhangyue
    PATH_zhangyue  = $(PATH_3rd)/zhangyue
    PATH_C +=\
	$(PATH_zhangyue)/src
    PATH_H +=\
	$(PATH_zhangyue)/inc
    PATH_EXT_LIB +=\
	$(PATH_zhangyue)/lib
endif

ifeq ($(filter __MMI_GTSBOX__ ,$(PP_OPT_COMMON)),__MMI_GTSBOX__)

PRODUCT_SC_3RD += gtsbox

PATH_gtsbox = $(PATH_3rd)/gtsbox

PATH_C +=\
		$(PATH_gtsbox)/src

PATH_H +=\
		$(PATH_gtsbox)/inc

PATH_EXT_LIB +=\
		$(PATH_gtsbox)/lib

endif

ifeq ($(filter __SXMENGINE__, $(PP_OPT_COMMON)), __SXMENGINE__)

PRODUCT_SC_3RD += sxmengine

PATH_sxmengine = $(PATH_3rd)/sxmengine

PATH_C +=\
    $(PATH_sxmengine)/src

PATH_H +=\
    $(PATH_sxmengine)/inc

PATH_EXT_LIB +=\
    $(PATH_sxmengine)/lib

endif

ifeq ($(filter __SRE__, $(PP_OPT_COMMON)), __SRE__)

PRODUCT_SC_3RD += sre

PATH_sre = $(PATH_3rd)/sre

PATH_C +=\
    $(PATH_sre)/src

PATH_H +=\
    $(PATH_sre)/inc

PATH_EXT_LIB +=\
    $(PATH_sre)/lib

endif

ifeq ($(filter __TTS__, $(PP_OPT_COMMON)), __TTS__)

PRODUCT_SC_3RD += tts

PATH_tts = $(PATH_3rd)/tts

PATH_C +=\
    $(PATH_tts)/src

PATH_H +=\
    $(PATH_tts)/inc

PATH_EXT_LIB +=\
    $(PATH_tts)/lib

endif

ifeq ($(filter __USER_LEVEL_PTHREAD__ ,$(PP_OPT_COMMON)),__USER_LEVEL_PTHREAD__)

PATH_pthread  = $(PATH_3rd)/pthread

PATH_EXT_LIB  +=\
    $(PATH_pthread)/lib
endif

# for dalvik
ifeq ($(filter __DALVIK__ ,$(PP_OPT_COMMON)),__DALVIK__)

PRODUCT_SC_3RD += \
	dalvik

PATH_dalvik    = $(PATH_3rd)/dalvik

PATH_C +=\
	  $(PATH_dalvik)/src

PATH_H +=\
	  $(PATH_dalvik)/inc

PATH_EXT_LIB +=\
    $(PATH_dalvik)/lib

endif

#for Kmx TT
ifeq ($(filter __MMI_KMX_TT__, $(PP_OPT_COMMON)), __MMI_KMX_TT__)

PRODUCT_SC_3RD += kmxtt

PATH_kmxtt = $(PATH_3rd)/kmxtt

PATH_EXT_LIB +=\
    $(PATH_kmxtt)/lib

endif

ifeq ($(filter __MAP_MMI_GPS_PLUGIN_LIB__, $(PP_OPT_COMMON)), __MAP_MMI_GPS_PLUGIN_LIB__)

PATH_gplug = $(PATH_3rd)/map/core

PATH_EXT_LIB +=\
    $(PATH_gplug)/lib

endif

ifneq ($(filter __ENABLE_SLDLM_SXMENGINE__ __ENABLE_SLDLM_ZYUEENGINE__ __ENABLE_SLDLM_ZMOLENGINE__ __ENABLE_SLDLM_SKYENGINE__ __ENABLE_SLDLM_TENCENT_MCARE__ __ENABLE_SLDLM_JAVA_OAKMONT__, $(PP_OPT_COMMON)),)
PATH_H +=\
	$(PATH_sys)/itf\
    $(PATH_sys)/pub
endif
