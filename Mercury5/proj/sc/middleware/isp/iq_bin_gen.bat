Xml_Parser.exe 0
IqFileToBin.exe -x default_iqfile.xml
Iq_Bin_Gen.exe
move api_id.h inc\common\
move dbg_ae_param.h inc\common\
move dbg_awb_param.h inc\common\
move dbg_af_param.h inc\common\
move dbg_iq_param.h inc\common\
move dbg_cali_param.h inc\common\
move dbg_eis_param.h inc\common\
move dbg_gui_param.h inc\common\
move dbg_id.h inc\common\
move dbg_isp_operation_param.h inc\common\
move dbg_sensor_param.h inc\common\
move dbg_version_param.h inc\common\
move iq_bin.h inc\common\
move iq_reg_map.h inc\common\
move dbg_buf.h inc\common\