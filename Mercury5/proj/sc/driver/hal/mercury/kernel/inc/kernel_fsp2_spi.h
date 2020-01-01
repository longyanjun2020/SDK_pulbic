/***************************************************************************
 *  kernel_fsp2_spi.h
 *--------------------------------------------------------------------------
 *  Scope: FSP2(Flash Self Programming) related definitions
 *
 ****************************************************************************/

#ifndef __KERNEL_FSP2_SPI_H__
#define __KERNEL_FSP2_SPI_H__

#include "stdcomp.h"
#include "cpu_mem_map.hc"

/****************************************************************************/
/*        FSP registers                                                     */
/****************************************************************************/
typedef struct Fsp2_Write
{
    u32 reg_fsp2_wd 					:16;
    u32 							:16;
} Fsp2_Write_Data_t;

typedef struct Fsp2_Read
{
    u32 reg_fsp2_rd  				:16;
	u32 							:16;
} Fsp2_Read_Data_t;

typedef struct KeFsp2Spi_s
{
    //0x40[rw] ~ 0x47[rw]
    Fsp2_Write_Data_t tFsp2_WriteData2[8];
    //0x48[rw]
    u32                             :32;
    //0x49[rw]
    u32                             :32;
    //0x4a[rw]
    u32                             :32;
    //0x4b[rw]
    u32                             :32;
    //0x4c[rw]
    u32                             :32;
    //0x4d[rw]
    u32                             :32;
    //0x4e[rw]
    u32                             :32;
    //0x4f[rw]
    u32                             :32;

    //0x50[rw]
    u32 reg_replaced_wd_num          :6;     //Write data number of byte to be replaced
    u32                              :1;
    u32 reg_replaced_en              :1;     //Replaced function enable
    u32 reg_replaced_wd_1            :8;     //Write data buffe to change to 128-256Mb
    u32                             :16;
    //0x51[rw]
    u32 reg_replaced_wd_2            :8;     //Write data buffe to change to 256-384Mb
    u32 reg_replaced_wd_3            :8;     //Write data buffe to change to 384-512Mb
    u32                             :16;
    //0x52[rw]
    u32                             :32;
    //0x53[rw]
    u32                             :32;
    //0x54[rw]
    u32                             :32;
    //0x55[rw]
    u32                             :32;
    //0x56[rw]
    u32                             :32;
    //0x57[rw]
    u32                             :32;
    //0x58[rw]
    u32                             :32;
    //0x59[rw]
    u32                             :32;
    //0x5a[rw]
    u32                             :32;
    //0x5b[rw]
    u32                             :32;
    //0x5c[rw]
    u32                             :32;
    //0x5d[rw]
    u32                             :32;
    //0x5e[rw]
    u32                             :32;
    //0x5f[rw]
    u32                             :32;

    //0x60[rw] ~ 0x64[rw]
    Fsp2_Write_Data_t tFsp2_WriteData[5];
    //0x65[rw] ~ 0x69[rw]
    Fsp2_Read_Data_t  tFsp2_ReadData [5];
    //0x6a[rw] how many bytes will be transmitted in nth command, Max size is 15Byte, Min. size is 1Byte
    u32 reg_fsp2_wbf_size0           :4;
    u32 reg_fsp2_wbf_size1           :4;
    u32 reg_fsp2_wbf_size2           :4;
    u32 reg_fsp2_wbf_size3           :4;
    u32                             :16;
    //0x6b[rw] how many bytes will be received in nth command, Max size is 10Byte, Min. size is 0Byte
    u32 reg_fsp2_rbf_size0           :4;
    u32 reg_fsp2_rbf_size1           :4;
    u32 reg_fsp2_rbf_size2           :4;
    u32 reg_fsp2_rbf_size3           :4;
    u32                             :16;
    //0x6c[rw]
    u32 reg_fsp2_en                  :1;     //Enable FSP [0]:Disable [1]:Enable
    u32 reg_fsp2_reset               :1;     //Enable reset [0]:Reset [1]: Not Reset
    u32 reg_fsp2_interrupt           :1;     //Enable FSP interrupt [0]:Disable [1]:Enable
    u32 reg_fsp2_auto_chk_err_flg    :1;     //Enable auto check error flag
    u32                             :4;
    u32 reg_fsp2_flash_rdy_bit       :3;     //Which bit is flash ready bit
    u32 reg_fsp2_rdsr_cmd            :2;     //Which command is RDSR
    u32 reg_fsp2_auto_check_en       :1;     //Enable auto check flash status
    u32 reg_fsp2_third_cmd_en        :1;
    u32 reg_fsp2_second_cmd_en       :1;
    u32                             :16;
    //0x6d[w]
    u32 reg_fsp2_trigger             :1;     //Start flash self-programming
    u32                             :31;
    //0x6e[r]
    u32 reg_fsp2_done_flg            :1;     //Busy status, HW sets to one when self-programming is completed
                                             //1: Self-programming done or interrupt pending
                                             //0: Self-programming busy or interrupt not pending
    u32 reg_fsp2_auto_chk_err        :1;     //Reserved.
    u32                             :30;
    //0x6f[w]
    u32 reg_fsp2_done_flg_clear      :1;     //SW needs to set this bit to clear done flag or interrupt.
    u32                             :31;
    //0x70[rw] ~ 0x74[rw]
    Fsp2_Write_Data_t tFsp2_WriteData1[5];
    //0x75[rw]
    u32 reg_fsp2_ctrl2               :8;     //[0] : fsp_quad_mode
    u32 reg_fsp2_ctrl3               :8;     //[0] : outside_trig_en_0
                                             //[1] : outside_trig_en_1
                                             //[2] : outside_trig_en_2
                                             //[3] : outside_trig_en_3
                                             //[4] : outside_trig_en_4
                                             //[5] : outside_trig_en_5
                                             //[6] : outside_trig_en_6
                                             //[7] : outside_trig_en_7
    u32                              :16;
    //0x76[rw]
    u32 reg_fsp2_ctrl4               :8;     //[0] : outside_trig_en_8
                                             //[1] : outside_trig_en_9
                                             //[2] : outside_trig_en_a
                                             //[3] : outside_trig_en_b
                                             //[4] : outside_trig_en_c
                                             //[5] : outside_trig_en_d
                                             //[6] : outside_trig_en_e
                                             //[7] : outside_trig_en_f
    u32 reg_spare_0                 :8;      //Bit[0] : outside_trig_en_for_clk_spi
                                             //Bit[1] : use_new_setting
    u32                             :16;
    //0x77[rw]
    u32 reg_spare_1                 :16;
    u32                             :16;
    //0x78[rw] how many bytes will be transmitted in nth command, Max size is 15Byte, Min. size is 1Byte
    u32 reg_fsp2_wbf_size4           :4;
    u32 reg_fsp2_wbf_size5           :4;
    u32 reg_fsp2_wbf_size6           :4;
    u32 reg_fsp2_wbf_size7           :4;
    u32                             :16;
    //0x79[rw] how many bytes will be received in nth command, Max size is 10Byte, Min. size is 0Byte
    u32 reg_fsp2_rbf_size4           :4;
    u32 reg_fsp2_rbf_size5           :4;
    u32 reg_fsp2_rbf_size6           :4;
    u32 reg_fsp2_rbf_size7           :4;
    u32                             :16;
    //0x7a[rw]
    u32 reg_new_cmd_enable           :7;    //new command enable. Valid if use_new_setting = 1
                                            //Bit [0] : Enable 2nd command
                                            //Bit [1] : Enable 3rd command
                                            //Bit [2] : Enable 4th command
                                            //Bit [3] : Enable 5th command
                                            //Bit [4] : Enable 6th command
                                            //Bit [5] : Enable 7th command
                                            //Bit [6] : Enable 8th command 
    u32                              :25;
    //0x7b[rw]
    u32 reg_new_auto_check           :8;    //new auto check setting. Valid if use_new_setting = 1
                                            //Bit [2:0] : Indicate which bit is flash ready bit
                                            //Bit [5:3] : which command is RDSR
                                            //000: First command
                                            //001: Second command
                                            //010: Third command
                                            //011: Fourth command
                                            //100: Fifth command
                                            //101: Sixth command
                                            //Bit [7] : Enable auto check flash status
                                            //0: Disable
                                            //1: Enable 
    u32                              :24;
} KeFsp2Spi_t;

extern volatile KeFsp2Spi_t* const g_ptKeFsp2Spi;

#endif // __KERNEL_FSP_SPI_H__
                                                 
