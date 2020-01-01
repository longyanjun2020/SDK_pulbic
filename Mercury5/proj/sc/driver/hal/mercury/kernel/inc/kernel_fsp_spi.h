/***************************************************************************
 *  kernel_fsp_spi.h
 *--------------------------------------------------------------------------
 *  Scope: FSP(Flash Self Programming) related definitions
 *
 ****************************************************************************/

#ifndef __KERNEL_FSP_SPI_H__
#define __KERNEL_FSP_SPI_H__

#include "stdcomp.h"
#include "cpu_mem_map.hc"

/****************************************************************************/
/*        FSP registers                                                     */
/****************************************************************************/
typedef struct Fsp_Write
{
    u32 reg_fsp_wd 					:16;
    u32 							:16;
} Fsp_Write_Data_t;

typedef struct Fsp_Read
{
    u32 reg_fsp_rd  				:16;
	u32 							:16;
} Fsp_Read_Data_t;

typedef struct KeFspSpi_s
{
    //0x0[rw] ~ 0x4[rw]
    Fsp_Write_Data_t tFsp_WriteData[5];
    //0x5[rw] ~ 0x9[rw]
    Fsp_Read_Data_t  tFsp_ReadData [5];
    //0xa[rw] how many bytes will be transmitted in nth command
    u32 reg_fsp_wbf_size0           :4;     //first command 1~10 bytes
    u32 reg_fsp_wbf_size1           :4;     //second command 1~9 bytes
    u32 reg_fsp_wbf_size2           :4;     //third command 1~8 bytes
    u32                             :20;
    //0xb[rw] how many bytes will be received in nth command
    u32 reg_fsp_rbf_size0           :4;     //first command 0~10 bytes
    u32 reg_fsp_rbf_size1           :4;     //second command 0~10 bytes
    u32 reg_fsp_rbf_size2           :4;     //third command 0~10 bytes
    u32                             :20;
    //0xc[rw]
    u32 reg_fsp_en                  :1;     //Enable FSP [0]:Disable [1]:Enable
    u32 reg_fsp_reset               :1;     //Enable reset [0]:Reset [1]: Not Reset
    u32 reg_fsp_interrupt           :1;     //Enable FSP interrupt [0]:Disable [1]:Enable
    u32 reg_fsp_auto_chk_err_flg    :1;     //Enable auto check error flag
    u32                             :4;
    u32 reg_fsp_flash_rdy_bit       :3;     //Which bit is flash ready bit
    u32 reg_fsp_rdsr_cmd            :2;     //Which command is RDSR
    u32 reg_fsp_auto_check_en       :1;     //Enable auto check flash status
    u32 reg_fsp_third_cmd_en        :1;
    u32 reg_fsp_second_cmd_en       :1;
    u32                             :16;
    //0xd[w]
    u32 reg_fsp_trigger             :1;     //Start flash self-programming
    u32                             :31;
    //0xe[r]
    u32 reg_fsp_done_flg            :1;     //Busy status, HW sets to one when self-programming is completed
                                            //1: Self-programming done or interrupt pending
                                            //0: Self-programming busy or interrupt not pending
    u32 reg_fsp_auto_chk_err        :1;     //Reserved.
    u32                             :30;
    //0xf[w]
    u32 reg_fsp_done_flg_clear      :1;     //SW needs to set this bit to clear done flag or interrupt.
    u32                             :31;
    //0x10[rw] ~ 0x14[rw]
    Fsp_Write_Data_t tFsp_WriteData1[5];
    //0x15[rw]
    u32 reg_fsp_ctrl2               :8;     //[0] : fsp_quad_mode
    u32 reg_fsp_ctrl3               :8;     //[0] : outside_trig_en_0
                                            //[1] : outside_trig_en_1
                                            //[2] : outside_trig_en_2
                                            //[3] : outside_trig_en_3
                                            //[4] : outside_trig_en_4
                                            //[5] : outside_trig_en_5
                                            //[6] : outside_trig_en_6
                                            //[7] : outside_trig_en_7
    u32                             :16;
	//0x16[rw]
	u32 reg_fsp_ctrl4               :8;
	u32 reg_spare_0                 :8;
	u32                             :16;
	//0x17[rw]
	u32 reg_spare_1                 :16;
	u32                             :16;
	//0x18[rw]
	u32 reg_fsp_wbf_size_outside    :12;
	u32                             :20;
	//0x19[rw]
	u32 reg_fsp_wbf_replaced        :8;
	u32 reg_fsp_wbf_mode            :4;
	u32 reg_fsp_wbf_outside_en      :1;
	u32 reg_fsp_wbf_outside_tx_timeout_en :1;
	u32 reg_fsp_wbf_src             :2;
	u32                             :16;
	//0x1a[r]
	u32 reg_fsp_wbf_outside_cnt     :12;
	u32                             :20;
	//0x1b[rw]
	u32 reg_fsp_wbf_outside_tx_timeout_max :16;
	u32                             :16;
	//0x1c[r]
	u32 reg_fsp_wbf_outside_tx_timeout_cnt :16;
	u32                             :16;
	//0x1d[r]
	u32 reg_fsp_debug_info0         :16;
	u32                             :16;
	//0x1e[r]
	u32 reg_fsp_debug_info1         :16;
	u32                             :16;
	//0x1f[r]
	u32 reg_fsp_debug_info2         :16;
	u32                             :16;
} KeFspSpi_t;

extern volatile KeFspSpi_t* const g_ptKeFspSpi;

#endif // __KERNEL_FSP_SPI_H__
                                                 
