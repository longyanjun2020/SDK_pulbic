/******************************************************************************/
/* File    : sysmiscdrv.h                                                     */
/*----------------------------------------------------------------------------*/
/* Scope   : Misc. system driver header file                                  */
/*                                                                            */
/******************************************************************************/
#ifndef __SYSMISCDRV_H__
#define __SYSMISCDRV_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "sysdrvhdr.h"

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define SPI_TFRBITS(_bits_)     (_bits_ % 16)
#define SPI_SSLDST(_num_)       (_num_)
#define SPI_DUPLEX_HALF         0
#define SPI_DUPLEX_FULL         1
#define SPI_TFRMODE_CPU         0
#define SPI_TFRMODE_DMA         1
#define SPI_ROLE_MASTER         0
#define SPI_ROLE_SLAVE          1
#define SPI_RATE_LOW            0
#define SPI_RATE_MIDLOW         1
#define SPI_RATE_MIDHIGH        2
#define SPI_RATE_HIGH           3
#define SPI_CPOL_LOW            0
#define SPI_CPOL_HIGH           1
#define SPI_CPHA_LEAD           0
#define SPI_CPHA_TRAIL          1
#define SPI_SSLPOL_LOW          0
#define SPI_SSLPOL_HIGH         1


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
typedef struct BusSpiCfg_s
{
    u32 duplex      : 1 ;
    u32 tfrMode     : 1 ;
    u32 spiRole     : 1 ;
    u32 sslPol      : 1 ;
    u32 sslDst      : 2 ;
    u32 rate        : 2 ;
    u32 tfrBits     : 4 ;
    u32 cpol        : 1 ;
    u32 cpha        : 1 ;
} BusSpiCfg_t;


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
/* Timer Driver APIs */
void    MDrv_SysTimer_Init(void);
void    MDrv_SysTimer_Start(u16 msec);
void    MDrv_SysTimer_Stop(void);
bool    MDrv_isSysTimerExpire(void);
bool    MDrv_isWatchDogRst(void);
void    MDrv_StdaTimer_Start(void);
u32     MDrv_StdaTimer_Count(void);
void    MDrv_OSTick2_Init(u32 msec);
void    MDrv_OSTick2_Stop(void);

/* DBB SPI Bus Driver APIs */
bool    MDrv_DbbSPI_Init(BusSpiCfg_t cfgval);
void    MDrv_DbbSPI_Close(void);
bool    MDrv_DbbSPI_TransBegin(void);
bool    MDrv_DbbSPI_TransEnd(void);
bool    MDrv_DbbSPI_Write(const void *pdata, u16 u16count);
bool    MDrv_DbbSPI_Read(void *pdata, u16 u16count);

/* Paging SPI Bus Driver APIs */
bool    MDrv_PagingSPI_Init(BusSpiCfg_t cfgval);
void    MDrv_PagingSPI_Close(void);
bool    MDrv_PagingSPI_TransBegin(void);
bool    MDrv_PagingSPI_TransEnd(void);
bool    MDrv_PagingSPI_Write(const void *pdata, u16 u16count);
bool    MDrv_PagingSPI_Read(void *pdata, u16 u16count);

#endif /* __SYSMISCDRV_H__ */
