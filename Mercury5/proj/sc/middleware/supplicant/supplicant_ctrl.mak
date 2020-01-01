#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C += $(PATH_supplicant)/src

ifeq ($(filter __GPS_DUALSTAR_DRV__ ,$(PP_OPT_COMMON)),__GPS_DUALSTAR_DRV__)
PATH_H += $(PATH_gps)/pub
endif

#PP_OPT_COMMON += __AEON_R2__
PP_OPT_COMMON += __ARM_RDK__
ifeq (RVCTV22,$(COMPILER_VERSION))
C_OPTIONS += --gnu
endif

PP_OPT_COMMON += OK_TO_RUN_PRODUCTION
PP_OPT_COMMON += OS_NO_C_LIB_DEFINES
PP_OPT_COMMON += CONFIG_CTRL_IFACE
PP_OPT_COMMON += CONFIG_DRIVER_AQUARIUS
PP_OPT_COMMON += INTERNAL_SHA1
PP_OPT_COMMON += INTERNAL_AES
PP_OPT_COMMON += INTERNAL_MD5
PP_OPT_COMMON += WAPI_WAIAKM
PP_OPT_COMMON += WAPI_PSK
PP_OPT_COMMON += INTERNAL_X509
PP_OPT_COMMON += CONFIG_INTERNAL_X509
PP_OPT_COMMON += PKCS12_FUNC
PP_OPT_COMMON += INTERNAL_SHA256
PP_OPT_COMMON += NEED_SHA256
PP_OPT_COMMON += SVN_REV=4491

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
PATH_C += \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/wpa_supplicant \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/common \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/crypto \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/drivers \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/eap_common \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/eap_peer \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/eap_server \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/eapol_supp \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/l2_packet \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/rsn_supp \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/tls \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/utils\
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/wapi\
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/ec


PATH_H += \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/wpa_supplicant \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/common \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/crypto \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/drivers \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/eap_common \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/eap_peer \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/eap_server \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/eapol_supp \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/l2_packet \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/rsn_supp \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/tls \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/utils \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/wps \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/wapi \
            $(PATH_supplicant)/lib/Supplicant_XOS_WAPI/src/ec



SRC_C_LIST =\
  supp_aes.c\
  supp_base64.c\
  supp_scan_helpers.c\
  supp_wpa_supplicant.c\
  supp_events.c\
  supp_blacklist.c\
  supp_wpas_glue.c\
  supp_scan.c\
  supp_main.c\
  supp_driver_aqu.c\
  supp_drivers.c\
  supp_cert.c\
  supp_l2_packet_rtk.c
  