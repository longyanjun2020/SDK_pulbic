#ifndef _MMPF_SARADC_H_
#define _MMPF_SARADC_H_

#define OP_MASK                         (0x03)

#define WRITE_OP                        (0x00)
#define READ_OP                         (0x01)

#define SARADC_SET_MACRO_BIT_SHIFT      (2)
#define SARADC_MACRO_ADDR_SET_VAL       (0)
#define POLLING_MODE                    (1)
#define SARADC_DEFAULT_CR               (3)

#define HIGH_BYTE(a)                    ((a>>8) & 0x00FF)
#define LOW_BYTE(a)                     (a & 0x00FF)

typedef struct _MMPF_SARADC_DATA 
{
  MMP_USHORT    data;
  MMP_USHORT    chan;
} MMPF_SARADC_DATA;

typedef enum _MMPF_SARADC_DELAY_CLOCK
{
    /*nomal mode delay clocks*/
    D_1_DIV_FS                = 0x00, 
    D_2_DIV_FS                = 0x10,
    D_4_DIV_FS                = 0x20,
    D_8_DIV_FS                = 0x30,
    D_16_DIV_FS               = 0x40,
    D_32_DIV_FS               = 0x50,
    D_48_DIV_FS               = 0x60,
    D_64_DIV_FS               = 0x70,
    D_96_DIV_FS               = 0x80,
    D_128_DIV_FS              = 0x90,
    D_160_DIV_FS              = 0xA0,
    D_192_DIV_FS              = 0xB0,
    D_224_DIV_FS              = 0xC0,
    D_256_DIV_FS              = 0xD0,
    D_288_DIV_FS              = 0xE0,
    /*fast mode: no delay clock*/
    FAST_MODE                 = 0xF0
}   MMPF_SARADC_DELAY_CLOCK;

/*Maximum FS=48kHz=768kHz/16;*/
typedef enum _MMPF_SARADC_MEA_RATE
{
    /* CR values only for NORMAL mode*/
    FS_DIV_512              = 0, 
    FS_DIV_400              = 1,
    FS_DIV_312              = 2,
    FS_DIV_256              = 3,
    /* Fast CR rate only for FAST mode*/
    FS_DIV_6                = 0, 
    FS_DIV_4                = 1,
    FS_DIV_2                = 2,
    FS                      = 3
}   MMPF_SARADC_MEA_RATE;

typedef struct _MMPF_SARADC_ATTR
{
   MMP_BOOL             TPWait;
} MMPF_SARADC_ATTR;

MMP_ERR     MMPF_SARADC_InitDeviceID(void);
MMP_ERR     MMPF_SARADC_Init(MMPF_SARADC_ATTR *saradc_attri);
MMP_ERR     MMPF_SARADC_PowerDown(void);
MMP_ERR     MMPF_SARADC_ReadShort(MMP_UBYTE addr_aligned, MMP_USHORT *readata);
MMP_ERR     MMPF_SARADC_WriteShort(MMP_UBYTE addr_aligned, MMP_USHORT write_data);
MMP_ERR     MMPF_SARADC_WriteByte(MMP_UBYTE addr_aligned, MMP_UBYTE write_data);
MMP_ERR     MMPF_SARADC_ReadByte(MMP_UBYTE addr_aligned, MMP_UBYTE *readata);
MMP_ERR     MMPF_SARADC_SetDelClk(MMPF_SARADC_DELAY_CLOCK DEL);
MMP_ERR     MMPF_SARADC_SetCR(MMPF_SARADC_MEA_RATE CR);
MMP_ERR     MMPF_SARADC_EnableTPWait(MMP_BOOL TPWaitenable);
MMP_ERR     MMPF_SARADC_SetChannel(MMP_SHORT channel);
MMP_ERR     MMPF_SARADC_SetMode(MMP_SHORT mode);
MMP_ERR     MMPF_SARADC_SetFastRead(void);
MMP_ERR     MMPF_SARADC_HandShake_Read(void);
MMP_ERR     MMPF_SARADC_SetPoll(void);
MMP_ERR     MMPF_SARADC_StartADC(void);
MMP_ERR     MMPF_SARADC_GetData(MMP_USHORT *value, MMP_USHORT channel);
MMP_ERR     MMPF_SARADC_SetMeasMode(MMPF_SARADC_DELAY_CLOCK DEL, MMPF_SARADC_MEA_RATE CR, MMP_BOOL TPWaitenable);

#endif
