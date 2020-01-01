#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_lib_audio_aac_enc)/src\
    
ifeq ($(OSTYPE), linux)
PATH_H +=\
    $(PATH_core_lib_audio)/aac_inc\
    $(PATH_core_lib_audio_aac_enc)/inc\
    $(PATH_core_system_audio_control)/inc\

else
PATH_H +=\
    $(PATH_core_lib_audio)/aac_inc\
    $(PATH_core_lib_audio_aac_enc)/inc\
    $(PATH_core_system_audio_control)/inc\
    /usr/include\

endif

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
    aac_ram.c\
    aac_rom.c\
    aac_rom1.c\
    aacenc.c\
    adj_thr.c\
    band_nrg.c\
    basicop2.c\
    bit_cnt.c\
    bitbuffer.c\
    bitenc.c\
    block_switch.c\
    channel_map.c\
    dyn_bits.c\
    fft.c\
    grp_data.c\
    interface.c\
    intrinsics.c\
    line_pe.c\
    oper_32b.c\
    optimize.c\
    pre_echo_control.c\
    psy_configuration.c\
    psy_main.c\
    qc_main.c\
    quantize.c\
    sf_estim.c\
    spreading.c\
    stat_bits.c\
    tns.c\
    tns_param.c\
    transcendent.c\
    transcendent_enc.c\
    transform.c\
    vector.c\
        
SRC_ASM_LIST +=\
    aaclib.S