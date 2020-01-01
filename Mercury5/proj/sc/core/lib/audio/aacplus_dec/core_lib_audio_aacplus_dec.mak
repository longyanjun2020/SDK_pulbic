#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_lib_audio_aacplus_dec)/src\
    $(PATH_core_lib_audio_aacplus_dec)/src/sbrdec\
    $(PATH_core_lib_audio_aacplus_dec)/src/ffrlib\
	$(PATH_core_lib_audio_aacplus_dec)/src/aacdec\
	$(PATH_core_lib_audio_aacplus_dec)/src/bitbuf\
	
ifeq ($(OSTYPE), linux)
PATH_H +=\
    $(PATH_core_lib_audio_aacplus_dec)/inc\
    $(PATH_core_system_audio_control)/inc\
    $(PATH_core_lib_audio)/aac_inc\

else	    
PATH_H +=\
    $(PATH_core_lib_audio_aacplus_dec)/inc\
    $(PATH_core_system_audio_control)/inc\
    $(PATH_core_lib_audio)/aac_inc\
    /usr/include\
    
endif
	
#-------------------------------------------------------------------------------
#	List of bitbuf directory
#-------------------------------------------------------------------------------

SRC_C_LIST +=\
	aacplus_bitbuffer.c
	
#-------------------------------------------------------------------------------
#	List of ffrlib directory
#-------------------------------------------------------------------------------

SRC_C_LIST +=\
	dsp_fft32x32s.c\
	aac_transcendent.c\
	aacplus_vector.c\
	
#-------------------------------------------------------------------------------
#	List of sbrdec directory
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
	aacpluscheck.c\
	env_calc.c\
	env_dec.c\
	env_extr.c\
	freq_sca.c\
	hybrid.c\
	lpp_tran.c\
	ps_bitdec.c\
	ps_dec.c\
	qmf_dec.c\
	sbr_crc.c\
	sbr_dec.c\
	sbr_ram.c\
	sbr_rom.c\
	sbrdecoder.c\
		
#-------------------------------------------------------------------------------
#	List of aacdec directory
#-------------------------------------------------------------------------------

SRC_C_LIST +=\
	aacdecoder_ram.c\
	aacdecoder_rom.c\
	aacdecoder.c\
	aacplus_basicop2.c\
	aacplus_bitstream.c\
	aacplus_block.c\
	aacplus_channel.c\
	aacplus_channelinfo.c\
	aacplus_conceal.c\
	aacplus_pns.c\
	aacplus_streaminfo.c\
	aacplus_tns.c\
	datastream.c\
	ic_predict.c\
	imdct.c\
	longblock.c\
	aacplus_oper_32b.c\
	pulsedata.c\
	shortblock.c\
	stereo.c\
	
SRC_ASM_LIST +=\
	aacplus_lib.S\
	aacplib.S
	