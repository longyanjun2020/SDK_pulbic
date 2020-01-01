#!/bin/sh

# String filter tools, just keep need
# remove c standard function

cp -vf zlib_rom.sym zlib_rom_symbol.sym

sed -e '/__raise/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__aeabi_idiv/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__aeabi_idivmod/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__default_signal_handler/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__rt_raise/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_ttywrch/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__aeabi_idiv0/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__rt_div0/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_sys_exit/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__I_use_semihosting_swi/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__semihosting_swi_guard/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__aeabi_uidiv/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__aeabi_uidivmod/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/D extr_/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__decompress_flags/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__decompress_sizes/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/hw_memcpy128/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/DL_Get_Local_Device_Ref/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/DL_Get_Device_Ref/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/LMconfig_LM_Connected_As_Master/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/LMconfig_LM_Connected_As_Scatternet/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/Spi_Frame_Make/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_printf_pre_padding/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_printf_post_padding/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_printf_longlong_hex/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__0sprintf/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_printf_int_common/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_sputc/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_printf_char_common/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__printf/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_printf_outstr_char/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_printf_input_char/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym

sed -e '/__aeabi_memcpy/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__rt_memcpy/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym

sed -e '/HW_Get_Native_Clk_Avoid_Race/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/LMconfig_LM_Clear_Device_State/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/LMconfig_LM_Set_Device_State/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/HW_Get_Bt_Clk_Avoid_Race/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/HW_set_slave/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/SYSconfig_Is_Feature_Supported/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym

sed -e '/DL_Get_Rx_LT_Expected_Seqn/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/DL_Get_Rx_LT_Tx_Ack_Pending/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/DL_Get_Tx_LT_Previous_Arqn/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/DL_Get_Tx_LT_Seqn/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/DL_Get_Tx_LT_Tx_Ack_Pending/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/DL_Init_Rx_eSCO_Pending/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/DL_Set_LT_Tx_Ack_Pending/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/DL_Set_Rx_LT_Previous_Arqn/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/DL_Toggle_Rx_LT_Seqn/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/DL_Toggle_Tx_LT_Seqn/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/FHS_Set_Device_Class/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/HW_set_bd_addr/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/HW_set_rx_mode/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/HWhab_Set_Rx_Mode/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/LSLCASS_IS_FREQ_VALID/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/LSLCASS_SET_FREQ_UNUSED/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/LSLCASS_SET_FREQ_USED/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/LSLCacc_Get_SCO_CFG/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/LSLCass_Device_Update_Notification/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/LSLCass_Eval_Reuse/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/LSLCass_Fade_Distant_Channels/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_LSLCacc_Extract_ACL_Payload/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_LSLCacc_Extract_SCO_Payload/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_LSLChop_Get_X_Page_Inquiry/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_USLCsched_Get_Emergency_Poll_Activity/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/hw_memcpy8/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym

sed -e '/__aeabi_memcpy4/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__aeabi_memcpy8/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__rt_memcpy_w/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_memcpy_lastbytes/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__ARM_switch8/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__rt_switch8/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__ARM_call_via_r0/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__call_via_r0/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__ARM_call_via_r1/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__call_via_r1/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__ARM_call_via_r2/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__call_via_r2/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__ARM_call_via_r3/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__call_via_r3/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__ARM_call_via_r4/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__call_via_r4/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__ARM_call_via_r5/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__call_via_r5/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__ARM_call_via_r6/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__call_via_r6/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__ARM_call_via_r7/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__call_via_r7/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__ARM_ll_cmpu/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_ll_cmpu/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym

sed -e '/__aeabi_memclr/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/__rt_memclr_w/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym
sed -e '/_memset_w/d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym


#sed -e '//d' zlib_rom_symbol.sym > tmp2.sym; mv tmp2.sym zlib_rom_symbol.sym


