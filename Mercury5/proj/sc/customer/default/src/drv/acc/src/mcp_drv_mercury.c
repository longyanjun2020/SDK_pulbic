#include "mcp_drv_pub_types.h"
#include "sys_sys_bootinit.h"
#if defined(__arm) && !defined(__GNUC__)
#pragma arm section rodata = ".RoDataOnBoot"
#endif
//  #include "drv_flash_lowl_ht_pub.h"
//  #include "drv_flash_lowl_ho_pub.h"
//  #include "drv_flash_lowl_id.h"

/****************************************************************************/
/* FLASH IDENTIFICATION FOR DOWNLOADER OR PROD. FUNCTIONS                   */
/****************************************************************************/
#if defined(__DEVICE_INFO__)

#define FLASH_IDENTIFIER(MANUFACTURER,DEVICECODE,PRODID,NAME) {FLASH_DEVID(MANUFACTURER, DEVICECODE), NAME, PRODID}

#else

#if defined ( __DOWNLOADER__)
#define FLASH_IDENTIFIER(MANUFACTURER,DEVICECODE,PRODID,NAME) {FLASH_DEVID(MANUFACTURER, DEVICECODE), NAME}
#else //__DOWNLOADER__
#define FLASH_IDENTIFIER(MANUFACTURER,DEVICECODE,PRODID,NAME) {FLASH_DEVID(MANUFACTURER, DEVICECODE), PRODID}
#endif /* __DOWNLOADER__ */

#endif

/****************************************************************************/
/* FLASH DEVICES DESCRIPTORS                                                */
/****************************************************************************/

/*Dummy  descristors and functions pointers , This region must fully maps to following region*/

DrvFlashErrCode_n dummy(u32 nAddress, u32 nMode)
{
    return 0;
}

/*** GENERAL COMMAND SET ***/
#if defined (FLASH_S_GENERAL_COMMANDSET)    //SPI NOR
static const FlashActionsDescriptor_t fms_s_GENERAL_CommandSetS =
{
    DrvFlashProgram,
    DrvFlashErase,
    DrvFlashSetProtect,
    dummy,
    DrvFlashBufferProgram,
};
#endif

#if defined (FLASH_S_1BANKS128)
static const FlashMonoBank_t fms_s_1Bank128 =
{
    1,
    {
        0x1FFF /* Containing last address of the bank divided by 0x1000 */
    }
};
#endif
#if defined (FLASH_S_1BANKS64)
static const FlashMonoBank_t fms_s_1Bank64 =
{
    1,
    {
        0x07FF /* Containing last address of the bank divided by 0x1000 */
    }
};
#endif
#if defined (GEO_TOP_128MBITS_64KWORDS)
static const FlashOneRegionGeometry_t Geometry_Top_128Mbits_64kWords =
{
    0x100,         /* Device Size/0x10000 = 16Mbytes/0x10000 = 2^24/0x10000 = 0x100*/
    0,             /* ignored */
    1,             /* Number of regions */
    {
        {
            16,    /* 64KWord = 128Kbytes Sector size = 2^n */
            256    /* Number of sectors */
        }
    }
};
#endif
#if defined (GEO_TOP_256MBITS_64KWORDS)
static const FlashOneRegionGeometry_t Geometry_Top_256Mbits_64kWords =
{
    0x200,         /* Device Size/0x10000 = 32Mbytes/0x10000 = 2^25/0x10000 = 0x200*/
    0,             /* ignored */
    1,             /* Number of regions */
    {
        {
            16,    /* 64KWord = 128Kbytes Sector size = 2^n */
            256    /* Number of sectors */
        }
    }
};
#endif
#if defined (GEO_TOP_64MBITS_32KWORDS)
static const FlashOneRegionGeometry_t Geometry_Top_64Mbits_32kWords =
{
    0x080,         /* Device Size/0x10000 = 16Mbytes/0x10000 = 2^24/0x10000 = 0x100*/
    0,             /* ignored */
    1,             /* Number of regions */
    {
        {
            15,    /* 32KWord = 64Kbytes Sector size = 2^n */
            256    /* Number of sectors */
        }
    }
};
#endif
#if defined (GEO_TOP_16MBITS_4KWORDS)
static const FlashOneRegionGeometry_t Geometry_Top_16Mbits_4kWords =
{
    0x20,         /* Device Size/0x10000 = 16Mbytes/0x10000 = 2^24/0x10000 = 0x100*/
    0,             /* ignored */
    1,             /* Number of regions */
    {
        {
            13,    /* 4KWord = 8Kbytes Sector size = 2^n */
            256    /* Number of sectors */
        }
    }
};
#endif


/****************************************************************************/
/* FLASH DEVICES DESCRIPTORS                                                */
/****************************************************************************/

const FlashConstDeviceDescriptor_t fms_cas_Descriptors[] =
{
    /* 128Mib */
    {
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_MACRONIX, FLASH_DEVICE_MACRONIX_MX25L25645G),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_256Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    /* 128Mib */
    {
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_MACRONIX, FLASH_DEVICE_MACRONIX_MX25L12805D),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_MACRONIX, FLASH_DEVICE_MACRONIX_MX25L6455E),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_ST, FLASH_DEVICE_MICRON_N25Q128),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_ST, FLASH_DEVICE_ST_STM25P32),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_EONSI, FLASH_DEVICE_EN25QH18),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_WINBOND, FLASH_DEVICE_W25Q128),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_WINBOND, FLASH_DEVICE_W25Q64),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_WINBOND, FLASH_DEVICE_W25X64),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_WINBOND, FLASH_DEVICE_W25X80),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_WINBOND, FLASH_DEVICE_W25Q80),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_ATMEL, FLASH_DEVICE_ATMEL_AT25DF321A),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_ATMEL, FLASH_DEVICE_ATMEL_AT25DF321),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_EONSI, FLASH_DEVICE_EON_EN25B64B),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_EONSI, FLASH_DEVICE_EON_EN25Q64),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_EONSI, FLASH_DEVICE_EON_EN25Q128),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_EONSI, FLASH_DEVICE_EON_EN25F80),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_SPANSION, FLASH_DEVICE_SPANSION_S25FL128P),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_SPANSION, FLASH_DEVICE_SPANSION_S25FL064P),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_GIGADEVICE, FLASH_DEVICE_GD25Q64),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_GIGADEVICE, FLASH_DEVICE_GD25Q128),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_128Mbits_64kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {   //* 2M *//FLASH_IC_MX25L1606E,  MID_MXIC,   0x20,   0x15,
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_MACRONIX, FLASH_DEVICE_MX25L1606E),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_16Mbits_4kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank128,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_MACRONIX, FLASH_DEVICE_MACRONIX_MX25L6405D),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_64Mbits_32kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank64,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_ST, FLASH_DEVICE_XMD_PP69720G),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_64Mbits_32kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank64,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },

	{
		/* T.B.D */
		/* Identifier  */ FLASH_DEVID(FLASH_JEDEC_ESEE, FLASH_DEVICE_ESEE25Q64F),
		/* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
		/* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_64Mbits_32kWords,
		/* Banks	   */ (FlashBanksDescriptor_t*)&fms_s_1Bank64,
		/* Actions set */ &fms_s_GENERAL_CommandSetS
	},


    {
        /* T.B.D */
        /* Identifier  */ FLASH_DEVID(FLASH_JEDEC_XTX, FLASH_DEVICE_XT25F64B),
        /* Features    */ FLASH_FEATURE_SECTOR_PROTECTION,
        /* Geometry    */ (FlashDeviceGeometry_t*)&Geometry_Top_64Mbits_32kWords,
        /* Banks       */ (FlashBanksDescriptor_t*)&fms_s_1Bank64,
        /* Actions set */ &fms_s_GENERAL_CommandSetS
    },
    {NULL},
};

const FlashIdentifier_t fms_cas_Identifiers[] =
{
    FLASH_IDENTIFIER(FLASH_JEDEC_MACRONIX, FLASH_DEVICE_MACRONIX_MX25L25645G, 0, "MXIC_MX25L25655F"),
    FLASH_IDENTIFIER(FLASH_JEDEC_MACRONIX, FLASH_DEVICE_MACRONIX_MX25L12805D, 0, "MXIC_MX25L12805D"),
    FLASH_IDENTIFIER(FLASH_JEDEC_MACRONIX, FLASH_DEVICE_MACRONIX_MX25L6455E, 0, "MXIC_MX25L6455E"),
    FLASH_IDENTIFIER(FLASH_JEDEC_ST, FLASH_DEVICE_MICRON_N25Q128, 0, "N25Q128"),
    FLASH_IDENTIFIER(FLASH_JEDEC_ST, FLASH_DEVICE_ST_STM25P32, 0, "STM25P32"),
    FLASH_IDENTIFIER(FLASH_JEDEC_ST, FLASH_DEVICE_XMD_PP69720G, 0, "PP69720G"),
    FLASH_IDENTIFIER(FLASH_JEDEC_EONSI, FLASH_DEVICE_EN25QH18, 0, "EN25QH18"),
    FLASH_IDENTIFIER(FLASH_JEDEC_WINBOND, FLASH_DEVICE_W25Q128, 0, "W25Q128"),
    FLASH_IDENTIFIER(FLASH_JEDEC_WINBOND, FLASH_DEVICE_W25Q64, 0, "W25Q64"),
    FLASH_IDENTIFIER(FLASH_JEDEC_WINBOND, FLASH_DEVICE_W25X64, 0, "W25X64"),
    FLASH_IDENTIFIER(FLASH_JEDEC_WINBOND, FLASH_DEVICE_W25X80, 0, "W25X80"),
    FLASH_IDENTIFIER(FLASH_JEDEC_WINBOND, FLASH_DEVICE_W25Q80, 0, "W25Q80"),
    FLASH_IDENTIFIER(FLASH_JEDEC_ATMEL, FLASH_DEVICE_ATMEL_AT25DF321A, 0, "AT25DF321A"),
    FLASH_IDENTIFIER(FLASH_JEDEC_ATMEL, FLASH_DEVICE_ATMEL_AT25DF321, 0, "AT25DF32"),
    FLASH_IDENTIFIER(FLASH_JEDEC_EONSI, FLASH_DEVICE_EON_EN25B64B, 0, "EN25B64B"),
    FLASH_IDENTIFIER(FLASH_JEDEC_EONSI, FLASH_DEVICE_EON_EN25Q64, 0, "EN25Q64"),
    FLASH_IDENTIFIER(FLASH_JEDEC_EONSI, FLASH_DEVICE_EON_EN25Q128, 0, "EN25Q128"),
    FLASH_IDENTIFIER(FLASH_JEDEC_EONSI, FLASH_DEVICE_EON_EN25F80, 0, "EN25F80"),
    FLASH_IDENTIFIER(FLASH_JEDEC_SPANSION, FLASH_DEVICE_SPANSION_S25FL128P, 0, "S25FL128P"),
    FLASH_IDENTIFIER(FLASH_JEDEC_SPANSION, FLASH_DEVICE_SPANSION_S25FL064P, 0, "S25FL064P"),
    FLASH_IDENTIFIER(FLASH_JEDEC_GIGADEVICE, FLASH_DEVICE_GD25Q64, 0, "GD25Q64"),
    FLASH_IDENTIFIER(FLASH_JEDEC_GIGADEVICE, FLASH_DEVICE_GD25Q128, 0, "GD25Q128"),
    FLASH_IDENTIFIER(FLASH_JEDEC_MACRONIX, FLASH_DEVICE_MACRONIX_MX25L1606E, 0, "MXIC_MX25L1606E"),
    FLASH_IDENTIFIER(FLASH_JEDEC_MACRONIX, FLASH_DEVICE_MACRONIX_MX25L6405D, 0, "MX25L6405D"),

    FLASH_IDENTIFIER(FLASH_JEDEC_ESEE, FLASH_DEVICE_ESEE25Q64F, 0, "ESEE25Q64F"),   
    FLASH_IDENTIFIER(FLASH_JEDEC_XTX,  FLASH_DEVICE_XT25F64B, 0, "XT25F64B"),
    {NULL},
};

#if defined (__MCP_COMMAND_STYLE__)

s32 DrvFlashProgram(u32 i__u32_Address, u32 i__u32_Data);
s32 DrvFlashBufferProgram(u32 i__u32_Address, u16 *i__u16_Data);
s32 DrvFlashSetProtect(u32 i__u32_Address, u32 i__u32_Mode);
s32 DrvFlashErase(u32 i__u32_Address, u32 i__u32_Mode);
#endif

