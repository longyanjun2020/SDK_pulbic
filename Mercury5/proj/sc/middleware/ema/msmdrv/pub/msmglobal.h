#if !defined(__MSMGLOBAL_H__)
#define __MSMGLOBAL_H__

//#define __HOSTSIM__         /* Target Platform (Win32) */
//#define __B1BOX__           /* Target Platform (B1BOX+DTP) */
#define __ON_EMA__          /* Target Platform (B1+EMA+XMMI) */

#if defined (__ON_EMA__)
    #include "vm_types.ht"
    #include "sys_rtk_vmrtkho.h"
    #include "vm_stdio.ho"
    #include "sys_vm_dbg.ho"
    #include "sys_traces.ho"
    #include "cus_os.hc"
    #ifndef __B1BOX__
        #include "ema.h"
    #else
        #include "mmpse.h"
    #endif /* __B1BOX__ */
#endif

/** @defgroup ConstructionFlags Construction Flags
    @ingroup msmGlobal
    @brief Use these flags to control the library builds
    @{
*/
#define USE_FPGA_HIF                    /* Use this for FPGA testing (legacy) */
#define USE_HIF_VER03_HW                /* Use the new HIF architecture */
#define USE_BIN_OFFSET32                /* Use the new Config binary format */
#define USE_LOCK                        /* Use HIF Lock */
#define USE_MASK                        /* Use Software Interrupt Mask */
#define USE_HIF_VER03_WORKAROUND        /* Use HIF workaround */
#define USE_HIF_VER03_PATCH_1           /* Use the HIF patch #1 */
#define USE_DIRECT_MEMORY_WRITE         /* Use the Dierct channel to memory of Montage (write) */
#define USE_DIRECT_STREAMS              /* Use the Direct path to send out streams data */
#define USE_DIRECT_FRAME_BUFFER         /* Use the Direct path to fill Montage-inside frame buffer */
#define USE_DIRECT_USB_WRITE            /* Use the Direct path to send out USB data */
#define USE_DIRECT_DISPLAY_WRITE        /* Use the Direct path to send out DISPLAY data */
#define USE_DIRECT_SHUTTER              /* Use the Direct path to send out Shutter Sound */
#define USE_DIRECT_TRACE_WRITE          /* Use the Direct path to send out Trace data */
#define USE_DIRECT_ERROR_RETURN         /* Use the error return for DIRECT path */
#define USE_DIRECT_URGENT               /* Use the Direct write handler in ISR routine */
#define USE_URGENT_READ                 /* Use the Emergency read */
#define USE_URGENT_WRITE                /* Use the Emergency write */
#define USE_FIXED_POOL                  /* Use the fixed pool allocation */
#define USE_LCM_FIRE_INT                /* Use the fire interrupt method to set Lcm */
#define USE_CUSTOM_ERROR_PROC           /* Use the custom fatal error handler */
#define USE_INT_FIRE_LOCK               /* Use the acquring lock to fire interrupt to Montage */
#define USE_ACTIVE_CHAN_LIST            /* Use the active list of command channels */
#define USE_MIU1_RESET_PATCH            /* Use the Ned's path for MIU1 reset at boot time */
#define USE_MIDI_ASSISTS                /* Use the M2-assisted MIDI playback */
#define USE_ASSERT                      /* Use the ASSERT macro to detect unexpeceted confition */
#define USE_P4_FIRMWARE_ID              /* Use the Perforce change-list number as firmware ID */
#define USE_DEV_CHANNEL_BUFFER          /* Use the device channel buffer, private use only */
#define USE_REVISED_DIRECT_DISPLAY      /* Use the revised transfer format to send out DISPLAY data */
#define USE_SECTION_DISCARD             /* Use the discard_b flag to drop section from download process */
#define USE_SYSTEM_PARAMETER_REQUEST    /* Use the "System Parameter Request" notification */
#define USE_DYNAMIC_PACKAGE             /* Use the dynamic package download */
#define USE_EMI_WAIT                    /* Use the EMI init/check waiting option */
#define USE_EMI_POLL                    /* Use the EMI check polling option */
#define USE_SHM_DOWNLOAD_CODE           /* Use the memcpy to download code based on shared memory architecture */
#define USE_DIRECT_FILE_WRITE           /* Use the Direct path to send out FILE data */
#define USE_SHM_COMMAND_PROTOCOL        /* Use the shared memory command protocol */
#define USE_DIRECT_JPEG_WRITE           /* Use the Direct path to send out JPEG bitstream */
//#define USE_VIRGO2_RFID                 /* Use the Virgo2 RFID */
//#define USE_ANTARES_RFID                /* Use the Antares RFID */
#define USE_SENSOR_TABLE_PACKAGE        /* Use the sensor table solution */
#define USE_SENSOR2_TABLE_PACKAGE       /* Use the sensor2 table solution */
#define USE_DISPLAY_TABLE_PACKAGE       /* Use the display table solution */
//#define USE_DIRECT_JPEG_ENCODE      	/* Use the Direct path to send out RGB bitstream for JPEG encode */
#define USE_DIRECT_EMU_WRITE            /* Use the Direct path to send out EMU bitstream */
#define USE_NON_INTERRUPT_POLLING       /* Use the polling instead of interrupt to receive ACCEPT_CMD_READY */
//#define USE_API_RAM_PACKAGE             /* Use the low-level API software solution */
#define USE_EBI_BUS_DUMMY_WRITE         /* Use the dummy write to flush EBI bus between and after context switch */

#if defined(__NAND__)
#define USE_TYPE_A_FIRMWARE_PACKAGE     /* Use the TYPE-A software solution */
//#define USE_OBSOLETE_TYPE_A_ARCHIT      /* Don't use the TYPE-C-like software architecture in TYPE-A */
#define USE_SYSTEM_RESOURCE_SIGNAL      /* Poll SYSTEM_RESOURCE_READY instead of ACCEPT_CMD_READY in non-interrupt polling mode */
#else
#define USE_TYPE_C_FIRMWARE_PACKAGE     /* Use the TYPE-C software solution */
//#define USE_SYSTEM_RESOURCE_SIGNAL      /* Poll SYSTEM_RESOURCE_READY instead of ACCEPT_CMD_READY in non-interrupt polling mode */
#endif

#define USE_DYNAMIC_CHANNEL_MALLOC      /* Allocate channel resource dynamically from pre-allocated memory space */
#define USE_DYNAMIC_CHANNEL_FREE        /* Release channel resource dynamically according to command ID */
#define USE_RO_TABLE_PACKAGE            /* Use the Read-Only table solution */
#define USE_DIRECT_DISK_INFO_WRITE      /* Use the Direct path to send out Disk Info bitstream */
//#define USE_HARDCODED_SHM_PARAM_BUFFER  /* Use the hardcoded shared parameter buffer address */
#define USE_CONFIGURABLE_CHIP_SELECT    /* Use the configurable CS0(default)/CS1 for LCM control */
#define USE_BOOT_OFFSET_AUTOCONFIG      /* Use the boot EMI offset auto-configuration */
//#define USE_NO_SPACE_EXCEPTION_ASSERT   /* Trigger assert, if no enough HIF space, even when exception occurrs */
#define USE_BYPASS_SWITCH_PROCEDURE     /* Use the procedure of switching between HIF bypass and bridge mode */
#define USE_AF_INSIDE_SENSOR_TABLE      /* Use the solution of sensor + auto-focus table (Need extra 12KB space) */
#define USE_SD_PWRCTRL_CONFIG           /* Control SD card power from MMP */
#define USE_SD_DETECT_CONFIG            /* Use the product-specific SD card detection */
#define USE_SD_DRVINIT_CONFIG           /* Config to skip SD driver init procedure */
//#define USE_OBSOLETE_RTK_SYSTEM_CALL    /* Use the obsolete RTK system call */
#define USE_POWER_CLOCK_CHECK           /* Check if there is any abnormal power/clock setting */
//#define USE_SENSOR_DEPENDENT_FIRMWARE   /* Use the obsolete architecture (firmware + default sensor driver) */
#define USE_SHARED_FIFO_QUEUE           /* Use the lock based FIFO queue */
#define USE_PRODUCT_FEATURE_SWITCH
#define USE_SD_PAD_CARD_PWR_CONFIG      /* Indicate whether SD pad power and card power are the same source */
#define USE_HARDCODE_ADDR_FORMULA       /* Hardcode address translation formula to speed up FIFO queue operations */
#define USE_MMP_TMT_TRACE_BUFFER        /* Redirect MMP debug message to TMT */
#define USE_SYSTEM_BOOTING_FLAG         /* Indicate whether system is booting up */
#define USE_UART_OUTPUT_PATH_CONFIG     /* Config MMP UART output to MTX0 (default) or MTX1 */
//#define IDENTIFY_CHIPID_FROM_MMP        /* Identify the chip ID by reading MMP registers */

/* Debug Message Control */
#define SUPPRESS_USB_CDC_TRACE          /* Suppress the USB CDC message to avoid TMT trace overflow */
//#define ENABLE_PACKET_READ_TRACE        /* Enable the packet read debug message */
//#define ENABLE_NOTIFY_CB_LIST_TRACE     /* Print notification callback list */
//#define ENABLE_FIFO_QUEUE_TRACE         /* Enable the Tx/Rx FIFO queue debug message */
#define FIX_PCLINT_WARNINGS

/* Candidate */
#if 0
#define USE_BIN_LEN32                   /* Use the new Config binray format */
#define USE_URGENT_DISPLAY_READ         /* Use the Emergency read on Display Data */
#define USE_DESTROY_DRIVER_ASSERT       /* Do Assertion in Destroy Driver */
#define USE_DESTROY_DRIVER_PROTECT      /* Do protection in Destroy Driver */
#define USE_DYNAMIC_BACKTRACE_BUFFER
#define USE_MAX_CHANNEL_ALLOCATE        /* Use the maximum channel resource */
#define USE_URGENT_USB_READ             /* Use the Emergency read on USB */
#define USE_URGENT_USB_WRITE            /* Use the Emergency write on USB */
#define USE_URGENT_USB_ONV24PAL         /* Use the USB OnWrite ISR context */
#define USE_MCP_2MB_DRAM_INIT           /* Use the MCP 2MB DRAM init setting */
#define USE_CIRCULAR_BACKTRACE          /* Use the circular backtrace buffer */
#define USE_FORCE_TO_DEBUG_MODE         /* Use the debug mode on trigger of assertion */
#define USE_SIMUL_USB_TXRX_INT          /* Use the new USB architecture (simulating TX/RX interrupt) */
#define USE_H263_RAM_PACKAGE            /* Use the H.263 software solution */
#define USE_RMVB_RAM_PACKAGE            /* Use the RMVB software solution */
#endif


/* Debugging-purpose only */
//#define USE_PROFILER                    /* Use the profiler inside */
//#define USE_FORCE_TO_DEBUG_MODE         /* Use the debug mode on trigger of assertion */
#if 0
#define USE_DEBUG_UART                  /* Use the debug printf port (UART1, 115200,8,N,One) */
#define USE_FN_COUNTER                  /* Use the FN counter */
    #ifdef USE_DEBUG_UART
        #undef USE_PROFILER
    #endif
#endif


/* Reserved */
#if 0
#define USE_PROFLER                     /* Use the profiler */
#define USE_IMMEDIATE_PROC              /* Use the immediate handler in command interface */
#define USE_DEBUG_UART                  /* Use the debug printf port (UART1, 115200,8,N,One) */
#define USE_FN_COUNTER                  /* Use the FN counter */
#define USE_DIRECT_RESTRICT             /* Use the deault handler with regarding DIRECT request */
#define USE_ENGINE_CLOCK_OVERRIDE       /* Use the override default engine clock */
#define USE_BOOT_CHECK                  /* Use the Boot Checker (debugging-purpose only) */
#define USE_DRAM_VERIFIER               /* Use DRAM read/write check at initialization */
#define USE_EXHAUST_READ                /* Use the exhaust HIF read */
#define USE_FIRMWARE_VERIFIER           /* Use the integrity check of M2 firmware */
#define USE_CMD_INT_BIT6                /* Use the bit6 for MCU interrupt */
#define USE_DIRECT_SYNC                 /* Use the Direct channel in sync way */
#define USE_HIF_VER03_PATCH_2           /* Use the HIF patch #2 */
#define USE_MEMORY_DOWNLOAD             /* Use memory mode download */
#define USE_HARDCODE_CONFIG             /* Use the default configs which are hard-coded inside */
#define USE_EXTERNAL_LOCK               /* Use the external lock as HIF Lock (B1 platform? Confirmed by Paul Chin) */
#define USE_PARMS_STREAMS               /* Use the Parameter path to send out streams data */
#define USE_DATA_STREAMS                /* Use the Data path to send out streams data */
#define USE_PARMS_STREAMS               /* Use the Parameter path to send out streams data */
#define USE_READ_CHECKSUM               /* Use the read checksum check */
#define USE_CMD_INSPECTER               /* Use the inspector while sending command */
#define USE_INT_FIRE_CONFIRM            /* Use the fire interrupt confirmation */
#define USE_DRAM_PREFETCH               /* Use the DRAM prefetch setting */
#endif

#if defined(__ON_EMA__)
    #define USE_MEMORY_DOWNLOAD         /* Use memory mode download */
    #define USE_HARDCODE_CONFIG         /* Use the default configs which are hard-coded inside */
    #define USE_CMD_LOGGER              /* Use the Pauli's command logger */
    /*#define USE_EXTERNAL_LOCK*/       /* Use the external lock as HIF Lock (B1 platform? Confirmed by Paul Chin) */

    /* Init-Package Size */
    #if defined(USE_TYPE_C_FIRMWARE_PACKAGE)
    #define MSM_FIRMWARE_BYTES                      4096        /* 4 KB */
    #elif defined(USE_TYPE_A_FIRMWARE_PACKAGE)
      #ifndef USE_OBSOLETE_TYPE_A_ARCHIT
      #define MSM_FIRMWARE_BYTES                    4096        /* 4 KB */
      #else
      #define MSM_FIRMWARE_BYTES                    655360      /* 640 KB */
      #endif
    #else
    #define MSM_FIRMWARE_BYTES                      389120      /* 380 KB */
    #endif

    #define MSM_H263_FIRMWARE_BYTES                 542720      /* 530 KB */
    #define MSM_RMVB_FIRMWARE_BYTES                 542720      /* 530 KB */
    #define MSM_IPTV_FIRMWARE_BYTES                 276480      /* 270 KB */
    #define MSM_API_FIRMWARE_BYTES                  389120      /* 380 KB */

    /* Type-C Code/Data Size, Offset */
    #ifdef __CMMB_DRV__
    #define MSM_TYPE_C_FIRMWARE_BYTES               1536000     /* 1500 KB */
    #else
    #define MSM_TYPE_C_FIRMWARE_BYTES               1017856     /* 994 KB */
    #endif

    #define MSM_TYPE_C_RAM_BYTES                    813056      /* 794 KB */

    #define MSM_TYPE_C_FIRMWARE_OFFSET              0x800000

    /* Type-A Code/Data Size, Offset */
    #define MSM_TYPE_A_FIRMWARE_BYTES               0x280000    /* 2560 KB */
    #define MSM_TYPE_A_RAM_BYTES                    0x200000    /* 2048 KB */

    /* Run-Package Size */
    #ifdef  USE_DYNAMIC_PACKAGE

      #if defined(USE_TYPE_C_FIRMWARE_PACKAGE)
      #define MSM_PACKAGE_BYTES                     262144      /* 256 KB */
      #elif defined(USE_TYPE_A_FIRMWARE_PACKAGE)
        #ifndef USE_OBSOLETE_TYPE_A_ARCHIT
        #define MSM_PACKAGE_BYTES                   262144      /* 256 KB */
        #else
        #define MSM_PACKAGE_BYTES                   870400      /* 850 KB */
        #endif
      #else
        #if defined(USE_IPTV_RAM_PACKAGE)
        #define MSM_PACKAGE_BYTES                   972800      /* 950 KB */
        #else
        #define MSM_PACKAGE_BYTES                   870400      /* 850 KB */
        #endif
      #endif

      /* Sensor Table Size */
      #ifdef  USE_SENSOR_TABLE_PACKAGE
        #ifdef USE_AF_INSIDE_SENSOR_TABLE
        #define MSM_SENSOR_TABLE_BYTES              22528       /* 22 KB */
        #else
        #define MSM_SENSOR_TABLE_BYTES              10240       /* 10 KB */
        #endif
      #endif

      /* Sensor2 Table Size */
      #ifdef  USE_SENSOR2_TABLE_PACKAGE
        #ifdef USE_AF_INSIDE_SENSOR_TABLE
        #define MSM_SENSOR2_TABLE_BYTES             22528       /* 22 KB */
        #else
        #define MSM_SENSOR2_TABLE_BYTES             10240       /* 10 KB */
        #endif
      #endif

      /* Display Table Size */
      #ifdef  USE_DISPLAY_TABLE_PACKAGE
        #define MSM_DISPLAY_TABLE_BYTES             3072        /* 3 KB */
      #endif
    #endif

    /* Use Read-Only table solution */
    #if defined(USE_TYPE_C_FIRMWARE_PACKAGE) || \
       (defined(USE_TYPE_A_FIRMWARE_PACKAGE) && !defined(USE_OBSOLETE_TYPE_A_ARCHIT))
        #undef  USE_MIDI_ASSISTS

        #ifdef USE_RO_TABLE_PACKAGE
        #undef  USE_SENSOR_TABLE_PACKAGE
        #undef  USE_SENSOR2_TABLE_PACKAGE
        #endif

        #ifdef __MULTIPLE_SENSOR_TABLE_DETECTION__
        #undef  USE_SENSOR_TABLE_PACKAGE
        #undef  USE_SENSOR2_TABLE_PACKAGE
        #undef  USE_RO_TABLE_PACKAGE
        #endif
    #endif

    /* Redefine for special cases */
    #if defined(__MMCFG_2__) /* TypeC Burst */
        /* Type-C Code Size */
        #undef  MSM_TYPE_C_FIRMWARE_BYTES
        #define MSM_TYPE_C_FIRMWARE_BYTES           1413120     /* 1380 KB */
        /* Run-Package Size */
        #undef  MSM_PACKAGE_BYTES
        #define MSM_PACKAGE_BYTES                   129024      /* 126 KB */
    #endif

    #if defined(__MMCFG_DIPPER__)  /* TypeA GPS */
        /* Type-A Data Size */
        #undef  MSM_TYPE_A_RAM_BYTES
        #define MSM_TYPE_A_RAM_BYTES                2621440     /* 2560 KB */
    #endif

    #if defined(__WLAN_DRV__) /* TypeA WIFI */
        /* Type-A Data Size */
        #undef  MSM_TYPE_A_FIRMWARE_BYTES
        #define MSM_TYPE_A_FIRMWARE_BYTES           0x1C0000     /* 1792 KB */
        #undef  MSM_TYPE_A_RAM_BYTES
        #define MSM_TYPE_A_RAM_BYTES                0x230000     /* 2240 KB */
    #endif

    /* B3 doesn't need M3 code section */
        /* Type-A/C Code Section */
        #undef  MSM_TYPE_C_FIRMWARE_BYTES
        #define MSM_TYPE_C_FIRMWARE_BYTES           2
        #undef  MSM_TYPE_A_FIRMWARE_BYTES
        #define MSM_TYPE_A_FIRMWARE_BYTES           2

    /* Debugging */
    #ifdef  USE_BOOT_CHECK
        //#define USE_EFUSE_CHECKER       /* Use e-fuse check at initialization */
        #define USE_DRAM_VERIFIER       /* Use DRAM read/write check at initialization */
    #endif

    /* Assert */
    #define MSM_WARN(x)     CUS_ASSERT(x)
    #define MSM_ASSERT(x)   CUS_ASSERT(x)
    #ifdef USE_FORCE_TO_DEBUG_MODE      /* Force to use debug Mode */
        #undef  MSM_ASSERT
        #define MSM_ASSERT(x)   \
                if (!(x)) \
                { \
                    dbgStrOut(TRUE, "File(line): %s(%d)", __FILE__, __LINE__); \
                    MSM_DEBUG_MODE(); \
                }
    #endif
    #ifndef USE_ASSERT
        #undef  MSM_ASSERT
        #define MSM_ASSERT(x)   (void)(x)
    #endif
#endif

#if !defined(USE_FPGA_HIF) || defined(USE_MIPSSIM)
    #if _MSC_VER == 1200 /* VC 6*/ || _MSC_VER == 1310 /* DotNet 2003 */
    #define USE_CMODEL_HIF
    #pragma message ("msmDrvLib: USE_CMODEL_HIF build.")
    #endif
#endif

#if defined(__HOSTSIM__)
    #if _MSC_VER == 1200 /* VC 6*/ || _MSC_VER == 1310 /* DotNet 2003 */
    #include "assert.h"
    #define MSM_ASSERT(x)  assert(x)
    #endif
#endif


#if defined(__B1BOX__)
    #ifdef USE_CMD_LOGGER
    #undef USE_CMD_LOGGER
    #endif

	/* Firmware Size */
    #undef  MSM_FIRMWARE_BYTES
    #define MSM_FIRMWARE_BYTES    		1048576    /* 1 MB */

	/* Packeage Size */
    #ifdef  USE_DYNAMIC_PACKAGE
        #undef  MSM_PACKAGE_BYTES
        #define MSM_PACKAGE_BYTES       655360     /* 640 KB */
    #endif
#endif


/** @} */

/** @defgroup BasicSizedTypes Basic Sized Types
    @ingroup msmGlobal
    @brief Use these flags to control the basic type defines
    @{
*/
typedef unsigned short  Boolean;

#if !defined(TRUE)
#define TRUE            (1)
#endif

#if !defined(FALSE)
#define FALSE           (0)
#endif

#if !defined(NULL)
#define NULL            (0)
#endif

#if !defined(MAX)
#define MAX(a,b)        (((a) > (b)) ? (a) : (b))
#endif

#if !defined(MIN)
#define MIN(a,b)        (((a) < (b)) ? (a) : (b))
#endif
/** @} */

#endif /* __MSMGLOBAL_H__ */
