
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
PATH_H +=\
	  $(PATH_mmicomn)/inc\
	  $(PATH_widget)/inc\
	  $(PATH_Oakmont)/inc\
	  $(PATH_Oakmont)/inc/aci\
	  $(PATH_Oakmont)/inc/jblend\
	  $(PATH_Oakmont)/inc/jblend/extlib\
	  $(PATH_Oakmont)/inc/jblend/gui/common\
	  $(PATH_Oakmont)/inc/jblend/gui/inner\
	  $(PATH_Oakmont)/inc/jblend/gui/user\
	  $(PATH_Oakmont)/inc/ksi

# kjava_sys_ext_cert.c: used by SSL for retrieving certificates (stored in device)

REL_SRC_C_LIST += \
  kjava_sys_ext_cert.c\
  kjava_sys_data_content.c\
  jap_task_main.c\
  jap_task_kve.c\
  jap_ven.c\
  jap_msg.c\
  jap_media.c\
  jap_ams.c\
  jap_net.c\
  jap_util.c\
  jap_strtbl.c\
  JgurToolKit.c\
  JgurDateField.c\
  JkCommConnection.c\
  JkGenericConnection.c\
  JkLocationCoordinates.c\
  JkLocationLandmarkStore.c\
  JkLocationOrientation.c\
  JkLocationProvider.c\
  JkMediaControl.c\
  JkMediaCustomProtocol.c\
  JkMediaMIDIDrv.c\
  JkMediaStream.c\
  JkMediaTone.c\
  JkPIM.c\
  JkServerSocket.c\
  JkSoftkey.c\
  JkUDP.c\
  JKWirelessMessaging.c\
  JkCpuCache.c\
  JkVmTimer.c\
  JkHeap.c\
  JkSatsaProtocol.c\
  midiControl.c\
  amrControl.c\
  toneControl.c\
  audioCapture.c\
  waveStreamControl.c\
  MMAPImidiControl.c\
  fileStream.c\
  mp3StreamControl.c\
  kjava_sys.c\
  kjava_sys_core.c\
  kjava_sys_device.c\
  kjava_sys_ext.c\
  kjava_sys_fs.c\
  kjava_sys_fs_adv.c\
  kjava_sys_fs_dev.c\
  kjava_sys_gfx.c\
  kjava_sys_http.c\
  kjava_sys_log_out.c\
  kjava_sys_pe.c\
  kjava_sys_push.c\
  kjava_sys_serial.c\
  kjava_sys_sock.c\
  java_ams.c\
  java_ams_pars.c\
  JkContactless.c

#------------------------------------------------------------------------------
#  ABI checker file
#------------------------------------------------------------------------------
REL_SRC_C_LIST += \
  abi_headers_java.c
	  

