PATH_H = \
    $(PATH_cpu_mdl)/pub \
    $(PATH_dynldr)/pub \
    $(PATH_fc)/pub \
    $(PATH_i18n)/inc \
    $(PATH_mserv)/inc \
    $(PATH_NCCBrowser_target)/inc \
    $(PATH_NCCBrowser_target)/src \
    $(PATH_NCCMms_target)/inc \
    $(PATH_sdk)/inc \
	$(PATH_sdk)/pub \
    $(PATH_sys)/pub \
    $(PATH_trc)/pub \
    $(PATH_zlib)/inc

MMI_PATH_H =
#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

#GEN_PREPROCESS = 1

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

PATH_C =\
	$(PATH_NCCBrowser_target)/src \
	$(PATH_NCCMms_target)/src

# for core
SRC_C_LIST = \
	alg_init.c	\
	asn1.c	\
	bn_add.c	\
	bn_c.c	\
	bn_ctx.c	\
	bn_div.c	\
	bn_exp.c	\
	bn_lib.c	\
	bn_mod.c	\
	bn_mont.c	\
	bn_mul.c	\
	bn_shift.c	\
	bn_spr.c	\
	bn_word.c	\
	cache_addfile.c	\
	cache_api.c	\
	cache_deletefile.c	\
	cache_innerapi.c	\
	cache_search.c	\
	cbc_cksm.c	\
	cert_certificate.c	\
	cert_crl.c	\
	cert_dlist.c	\
	cert_infor.c	\
	cert_mgi.c	\
	cert_setconvert.c	\
	cert_store.c	\
	cert_verify.c	\
	cfg_bookmark.c	\
	cfg_history.c	\
	cfg_mmanage.c	\
	cfg_protocolsetting.c	\
	cfg_storageread.c	\
	cfg_storagewrite.c	\
	cfg_viewsetting.c	\
	des_enc.c	\
	dlm.c	\
	enc_enc.c	\
	enc_encode.c	\
	enc_get.c	\
	enc_md.c	\
	hmac.c	\
	html_encoding.c	\
	html_io.c	\
	html_memory.c	\
	html_other.c	\
	html_parser.c	\
	html_parserapi.c	\
	html_parserinternals.c	\
	html_parserpool.c	\
	iflayer.c	\
	iflayer_context.c	\
	iflayer_dlbgsound.c	\
	iflayer_dlddparser.c	\
	iflayer_dlErrorPage.c	\
	iflayer_dlimg.c	\
	iflayer_dljs.c	\
	iflayer_dlmainnew.c	\
	iflayer_dlpage.c	\
	iflayer_encodeadd.c	\
	iflayer_htmlfile.c	\
	iflayer_zip.c	\
	layout_field.c	\
	layout_main.c	\
	layout_tableex2.c	\
	layout_text.c	\
	md2_for_wap.c	\
	md5_for_wap.c	\
	multipart_api.c	\
	multipart_encodepack.c	\
	multipart_encodeunpack.c	\
	multipart_innerapi.c	\
	multipart_textpack.c	\
	multipart_textunpack.c	\
	ncbc_enc.c	\
	ncc_browser_cfg.c	\
	nccport_browser_agent.c	\
	nccport_browser_cert.c	\
	nccport_browser_mem.c	\
	nccport_browser_misc.c	\
	nccport_browser_net.c	\
	nccport_browser_pclient.c	\
	nccport_whttp_tls.c	\
	p_encry.c	\
	p_key.c	\
	parser_html.c	\
	parser_xml.c	\
	rand_llib.c	\
	rc4_enc.c	\
	rsa_eay.c	\
	rsa_lib.c	\
	sa_attrtable.c	\
	sa_esmpclient.c	\
	sa_maparea.c	\
	sa_marquee.c	\
	sa_mcollect.c	\
	sa_mmanage.c	\
	sa_parser.c	\
	sa_picto.c	\
	sa_sax.c	\
	sa_stack.c	\
	sa_tagattrlists.c	\
	sa_urlhstack.c	\
	sa_schema.c	\
	set_key.c	\
	sha_for_wap.c	\
	svc_parser.c	\
	tls_client.c	\
	tls_fsm.c	\
	tls_handshake.c	\
	tls_iface.c	\
	tls_record.c	\
	whttp_auth.c	\
	whttp_cookie.c	\
	whttp_nano.c	\
	whttp_socket.c	\
	wmlconv_checkinputformat.c	\
	wmlconv_fromwbxml.c	\
	wmlconv_output.c	\
	wmlconv_tagattrs.c	\
	wmlconv_tohtml.c	\
	wmlconv_totemplate.c	\
	wmlconv_var.c	\
	x509.c	\
	x509_obj.c	\
	nccxmlparse.c	\
	nccxmlrole.c	\
	nccxmltok.c	\

#delete original {MMI_}PATH_H
CFLAGS +=\
	-DHAVE_MEMMOVE	\
	-DNCC_WHTTP	\
	-DNCC_MULTIPART	\
	-DNCC_BROWSER_XML	\
	-DNCC_BROWSER_CACHE	\
	-DNCC_BROWSER_ZLIB	\
	-DNCC_WITH_CONSMS	\
	-DMMS_UTF8_CHARSET	\
	-DMMS_DUAL_SIM_SUPPORT	\
	-DI18N_LATIN1_SUPPORT	\
	-DI18N_UTF8_UTF16_SUPPORT	\
	-DNCC_MMSNET_TIMER_DRIVER	\
	-DUAPP_MMS_WHTTP	\
	-DMEM_USING_TESTING	\
	-DMEM_TESTING_IN_EMMI \
	-DSUPPORT_FONT_MODE_DYNAMIC	\
	-D__FEATURE_VECTOR_FONT__	\
	-DSET_VECTOR_FONT_SIZE_BY_LIB	\
	-DNCC_EXTENDED_FILE_SUPPORT

ifeq ($(filter __WAP_MMI_OTA_PROV__, $(PP_OPT_COMMON)), __WAP_MMI_OTA_PROV__)
CFLAGS +=\
	-DUAPP_PUSH_PROV
endif

ifeq ($(filter __WLAN__ ,$(PP_OPT_COMMON)),__WLAN__)
CFLAGS += -DNCC_WAP_SUPPORT_WIFI
endif

ifeq ($(COMPILER_VERSION), RVCTV22)
C_OPTIONS += --diag_suppress 1,9,42,47,66,68,111,117,120,144,152,161,167,170,174,175,177,186,188,191,192,223,236,260,513,514,546,550,767,815,940,991,1215,1293,1294,1295,1296,2874
endif
