#ifndef ONCE_INFRA_DIAG_H
#define ONCE_INFRA_DIAG_H
////////////////////////////////////////////////////////////////////////////////
///@file infra_diag.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_system.h>
#include <pkgconf_infra.h>
#include <infra_type.h>
#include <stdarg.h>

//---------------------------------------------------------------------------
//Diagnostic routines  

//Initialize, call before any others
externC void diag_init(void);         
//Write single char to output   
externC void diag_write_char(char c);    
//Write zero terminated string 
externC void diag_write_string(const char *psz); 
//Write decimal value   
externC void diag_write_dec( efat_int32 n);       
typedef int __printf_fun(const char *fmt, ...);
externC void diag_vdump_buf_with_offset(__printf_fun *pf, efat_uint8 *p, EFAT_ADDRWORD s, efat_uint8 *base);
externC void diag_dump_buf_with_offset(efat_uint8 *p, EFAT_ADDRWORD s, efat_uint8 *base);
externC void diag_dump_buf_with_offset_32bit(efat_uint32 *p, EFAT_ADDRWORD s, efat_uint32 *base);
externC void diag_dump_buf_with_offset_16bit(efat_uint16 *p, EFAT_ADDRWORD s, efat_uint16 *base);
//Write hexadecimal value 
externC void diag_write_hex( efat_uint32 n);   
externC void diag_dump_buf(void *buf, EFAT_ADDRWORD len);
externC void diag_dump_buf_32bit(void *buf, EFAT_ADDRWORD len);
externC void diag_dump_buf_16bit(void *buf, EFAT_ADDRWORD len);
//Formatted print   
externC int  efat_dialog( const char *fmt, ... );     
externC void diag_printf_enable( void );
externC void diag_printf_disable( void );
//Formatted print for backtrace
externC int  diag_printf_trc(int type, const char *fmt, ...);    
#ifdef  CFG_BACKTRACE_SD
#define BACKTRACE_BUF_START     (HWR_HAL_MIPS_MSTAR_CFGVARS_START + HWR_HAL_MIPS_MSTAR_CFGVARS_SIZE)
//Formatted backtrace (log to backtrace buffer)
externC int  diag_backtrace(efat_uint8 level, int type, ... );    
//Formatted backtrace (force log to backtrace buffer)
externC int  diag_backtrace_SD(efat_uint8 level, int type, ... );    
//Record FS dir entry retry
externC void diag_backtrace_dentry_retry(void); 
//Record FS dir entry error
externC void diag_backtrace_dentry_err(void);        
externC void diag_backtrace_boot_status(unsigned char mode,unsigned int status);
externC void show_backtrace_boot_status(void);


typedef enum
{
    SD_POWER_STATUS     = 0x0,
    NAND_POWER_STATUS   = 0x2,
    CARD_STATUS         = 0x3,
    CARD_OPERATING_W    = 0x4,
    CARD_OPERATING_R    = 0x5,
    HW_SEM_ERROR        = 0x6,
    CARD_CORRUPT        = 0x7,
}CARD_BTR;
//bit   0: power status (00/01/10/11: unknow/power on/power off/unknow)
//bit   2: reserve
//bit   3: card status
//bit   4: writing    (0/1=X/in use)
//bit   5: reading    (0/1=X/in use)
//bit   6: HW sem     (1: error)
//bit   7: card corrupt
externC void diag_backtrace_sd_status(CARD_BTR operation, unsigned char status);//Record SD status 

typedef enum
{
    BOOT_STATUS_OR = 0,
    BOOT_STATUS_SET = 1,
} BOOT_STATUS_MODE;


typedef enum
{   //BS = Boot Status
    BS_EFAT_USER_START   = 0x1,
    BS_SM_START         = 0x2,
    BS_SM_DRVINIT       = 0x4,
    BS_BEFORE_CMD_READY = 0x8,
    BS_DONE_CMD_READY   = 0x10,
    BS_TRC_BUF_READY    = 0x20,
} BOOT_STATUS;

#endif

externC void diag_init_putc(void (*putc)(char c, void **param));
externC int  diag_snprintf(char *buf, size_t len, const char *fmt, ...);
externC int  diag_sprintf(char *buf, const char *fmt, ...);
externC int  diag_vprintf(const char *fmt, va_list ap);
externC int  diag_vsprintf(char *buf, const char *fmt, va_list ap);


//---------------------------------------------------------------------------
//Internal Diagnostic MACROS                                                
#define DIAG_DEVICE_END_SYNC()
#define DIAG_DEVICE_START_SYNC()

//---------------------------------------------------------------------------
#endif //ONCE_INFRA_DIAG_H 

