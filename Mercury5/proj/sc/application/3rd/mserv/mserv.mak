PATH_H = \
    $(PATH_audio)/pub \
    $(PATH_cc)/itf_open \
    $(PATH_core)/pub \
    $(PATH_cpu_mdl)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_esl)/pub \
    $(PATH_fc)/pub \
    $(PATH_fms)/pub \
    $(PATH_ip)/itf_open \
    $(PATH_keypad_mdl)/pub \
    $(PATH_mae)/inc \
    $(PATH_mae)/pub \
    $(PATH_mmmanager)/inc \
    $(PATH_mmmanager)/pub \
    $(PATH_mserv)/inc \
    $(PATH_mserv)/itf \
    $(PATH_MsWrapper)/pub \
    $(PATH_NCCBrowser_target)/inc \
    $(PATH_NCCMms_target)/inc \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/DataStruct \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/inc/ResMgr \
    $(PATH_ResMgr)/inc/SocketCore \
    $(PATH_ResMgr)/inc/SocketResMgr \
    $(PATH_ResMgr)/inc/Util \
    $(PATH_ResMgr)/pub \
    $(PATH_ril_itf)\
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
    $(PATH_sdk)/pub \
    $(PATH_sys)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_vfs)/pub \
    $(PATH_vml)/itf

MMI_PATH_H = 

#
#	Important :	This software is protected	by	Copyright and the	information
#					contained herein is confidential. Distribution,	reproduction
#					as	well as exploitation	and transmission of its	contents	is
#					not allowed	except if expressly permitted. Infringments
#					result in damage claims
#					Copyright Wavecom	S.A. (c)	$JustDate:$
#

# ****************************************************************************
# *  File	 :	$Workfile:$			$Revision:$
# *--------------------------------------------------------------------------*
# *  Scope	 :	  Description of the	librarie	to	generate							  *
# *																								  *
# *  Notes	 :	  to launch	the compilation of the current library,			  *
# *				  type from	output directory :										  *
# *						 make	-r	-f	..//gen.mak	TARGET=<target>					  *
# *																								  *
# *																								  *
# *																								  *
# *  Changes	 :																				  *
# *--------------------------------------------------------------------------*
# *  Version VSS	| Date			  | Author |	Modification					  *
# *--------------------------------------------------------------------------*
# *	$Log:$
#
# ****************************************************************************

#SCE_OPTIONS = -R -G -Cysc.cfg -N
#SCE_OPTIONS = -R -N

#------------------------------------------------------------------------------
#	Description	des variables propre	a la bibliothèque
#	Description	of	some variables	own to the librairie
#------------------------------------------------------------------------------
# Library module (lib) or Binary	module (bin)
PROCESS		= lib


#------------------------------------------------------------------------------
#	Liste	des fichiers sources	de	la	bibliothèque ou de l'éxecutable a générer
#	List of source	files	of	the library	or	executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST += ms_app.c
SRC_C_LIST += ms_evt_network.c
SRC_C_LIST += ms_evt_timer.c
SRC_C_LIST += ms_init.c
SRC_C_LIST += ms_pars.c
SRC_C_LIST += ms_task.c
SRC_C_LIST += sic_net.c
SRC_C_LIST += sic_net_msl.c
SRC_C_LIST += sic_net_net2msl.c
SRC_C_LIST += winsock.c
SRC_C_LIST += ms_file_p.c
SRC_C_LIST += ms_sdk.c
SRC_C_LIST += mms_pars.c
SRC_C_LIST += ms_socket_cmn.c
SRC_C_LIST += ms_socket_fsm.c
SRC_C_LIST += ms_socketmgr_init.c
SRC_C_LIST += ms_socketmgr_util.c
SRC_C_LIST += ms_prov.c
SRC_C_LIST += ms_socket_ind_hdlr.c
SRC_C_LIST += ms_socket_ind_itf.c
SRC_C_LIST += ms_socket_req_hdlr.c
SRC_C_LIST += ms_socket_req_itf.c
SRC_C_LIST += ms_socket_rsp_hdlr.c
SRC_C_LIST += ms_socket_rsp_itf.c
SRC_C_LIST += ms_socket_debug_history.c
SRC_C_LIST += ms_socket_traffic_checker.c
SRC_C_LIST += ms_socket_traffic_recorder.c
SRC_C_LIST += ms_socket_traffic_manager.c


#------------------------------------------------------------------------------
#  ABI checker file
#------------------------------------------------------------------------------
SRC_C_LIST += \
  abi_headers_mserv.c
