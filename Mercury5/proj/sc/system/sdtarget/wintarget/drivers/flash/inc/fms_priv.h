/****************************************************************************/
/*  $Workfile::   fms_priv.h                                               */
/*--------------------------------------------------------------------------*/
/*  Scope   : Flash Memory Services                                         */
/*            Private header file for Core and Services                     */
/****************************************************************************/



#ifndef __FMS_PRIV_H__
#define __FMS_PRIV_H__


/****************************************************************************/
/* FATAL ERRORS                                                             */
/****************************************************************************/

typedef enum
{
   FMS_ERROR_UNKNOWN,
   FMS_ERROR_EEPROM_BROKEN,
   FMS_ERROR_EEPROM_CLEAR,
   FMS_ERROR_FLASH_UNKNOWN,
   FMS_ERROR_BAD_OBJECTFORMAT,
   FMS_ERROR_DEAD_DEVICE,
   FMS_ERROR_CODE_OBJECTSPACE_COLLISION,
   FMS_ERROR_CODE_CORRUPT
} fms_FatalError_e;

/****************************************************************************/
/* SERVICES MANAGEMENT                                                      */
/****************************************************************************/

typedef enum
{
   FMS_AREA_GSMSTACK = 0,
   FMS_AREA_OPENAT,
   FMS_AREA_EEPROM,
   FMS_AREA_OBJECTS,
   FMS_AREA_SPAREVOLUME,
   FMS_AREA_CUSTOM,
   FMS_AREA_JAVA,
   FMS_AREA_DOTA,
   FMS_AREA_SOUND,
   FMS_AREA_TRACES,
   FMS_AREA_XMODEM
} fms_Area_e;

#define FMS_AREA_MAXNUMBER 11

typedef struct
{
   u32 u32_StartAddr;
   u32 u32_Length;
} fms_AreaLocus_t;

typedef struct
{
   u32 u32_HighestCodeAddr;
   u32 u32_GsmCodeHighwater;
   fms_AreaLocus_t as_Areas[FMS_AREA_MAXNUMBER];
} fms_DeviceMemUsage_t;


/* Services management */
extern fms_DeviceMemUsage_t fms_s_MemUsage;

/* Is M18 MCP */
extern bool bfms_M18_setting;
/****************************************************************************/
/* ERASURE AND PROTECTION MODES                                             */
/****************************************************************************/

#define FMS_ERASE_NORMAL      1
#define FMS_ERASE_NO_SUSPEND  2 
#define FMS_ERASE_RESUME      4
#define FMS_ERASE_NO_CHECK_EMPTY 8


#define FMS_PROTECT_DEACTIVATE 1
#define FMS_PROTECT_ACTIVATE   2
#define FMS_PROTECT_LOCKDOWN   4
#define FMS_PROTECT_RANGE      8
#define FMS_PROTECT_DEACTIVATE_SPI 0x10
#define FMS_PROTECT_ACTIVATE_SPI   0x20

/****************************************************************************/
/* EXTENDED COMMANDS                                                        */
/****************************************************************************/


#define FMS_CMD_READ_SERIALNUMBER      1 /* Returns the device S/N                                          */
#define FMS_CMD_GET_FLASH_NAME         2 /* Returns the device part name                                    */
#define FMS_CMD_GET_DEVICE_SIZE        3 /* Returns the size of the device                                  */
#define FMS_CMD_DWL_SUSPENDERASE       4 /* Suspends an erase process                                       */
#define FMS_CMD_DWL_RESUMEERASE        5 /* Resumes a suspended erasure                                     */
#define FMS_CMD_GET_DEVICE_ID          6 /* Returns the manufacturer+device code                            */
#define FMS_CMD_PERMANENT_LOCK_STATUS  7 /* Returns FMS_OK if the permanent locking feature can be disabled */
#define FMS_CMD_PREVENT_PERMANENT_LOCK 8 /* Deactivates the permanent locking feature                       */
#define FMS_CMD_ACTIVATE_SYNCHRONOUS   9 /* Set the device in synchronous mode                              */
#define FMS_CMD_DEACTIVATE_SYNCHRONOUS 10 /* Exit the device from synchronous mode                          */
#define FMS_CMD_GET_SMALL_BLOCK_START_ADDR 11 /* Returns small sector start addr of device*/

/****************************************************************************/
/* FEATURES OF THE FLASH MEMORY DEVICE                                      */
/****************************************************************************/

#define FMS_FEATURE_SECTOR_PROTECTION       (1<<0)
#define FMS_FEATURE_MULTILEVELCELL          (1<<1)
#define FMS_FEATURE_PERMANENT_BLOCK_LOCKING (1<<2)
#define FMS_FEATURE_SYNCHRONOUS_MODE        (1<<3)

/****************************************************************************/
/* SHARED ROUTINES                                                          */
/****************************************************************************/

/****************************************************************************/
/* COMMON UTILITIES                                                         */
/****************************************************************************/

/****************************************************************************/
/*  Function: fms_AlreadyErasedSector                                       */
/*--------------------------------------------------------------------------*/
/*  Scope   : Checks whether a given sector is erased or not                */
/*                                                                          */
/*  Return    : (s32) TRUE or FALSE                                         */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   |  Address within the sector to check     */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_AlreadyErasedSector(u32 i__u32_Address);

/****************************************************************************/
/*  Function: fms_FatalException                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   : Initialisation fatal error handling                           */
/*                                                                          */
/*  Return    : n/a                                                         */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__e_ErrorCode    | X |   |   |  fms_FatalError_e code                  */
/*  i__sz_FmtString   | X |   |   |  String to dump in ERROR                */
/*  ...variadic       | X |   |   |  Parameters for ERROR                   */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
void fms_FatalException(fms_FatalError_e i__e_ErrorCode, ascii *i__sz_FmtString, ...);

/****************************************************************************/
/*  Function: fms_Panic                                                     */
/*--------------------------------------------------------------------------*/
/*  Scope   : Fatal error after initialisation phases                       */
/*                                                                          */
/*  Return    : void                                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__sz_Message     | X |   |   |  Error message                          */
/*                    |   |   |   |                                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
void fms_Panic(ascii *i__sz_Message, ...);

/****************************************************************************/
/* FEATURES RELATED                                                         */
/****************************************************************************/


/****************************************************************************/
/*  Function: fms_DeviceHasFeature                                          */
/*--------------------------------------------------------------------------*/
/*  Scope   : Returns TRUE if the device whose address is given             */
/*            has the specified feature                                     */
/*                                                                          */
/*  Return    : TRUE/FALSE                                                  */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   | Address of the device                   */
/*  i__u32_Feature    | X |   |   | Feature to check                        */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_DeviceHasFeature(u32 i__u32_Address, u32 i__u32_Feature);

/****************************************************************************/
/* GEOMETRY RELATED FUNCTIONS                                               */
/****************************************************************************/


/****************************************************************************/
/*  Function: fms_CoreAddressToEndBank                                      */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Gets the address of the end of the bank where the address    */
/*             given as a parameter lies                                    */
/*                                                                          */
/*  Return    :  (u32) Address or FMS_UNDEFINED                             */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* i__u32_Address     | X |   |   |                                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
u32 fms_CoreAddressToEndBank(u32 i__u32_Address);

/****************************************************************************/
/*  Function:  fms_SectorLowerBound                                         */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Return the address of the lower bound of the sector          */
/*             where the specified parameter address lies.                  */
/*                                                                          */
/*  Return    :  (s32) Address or FMS_OVERFLOW                              */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   |  Address to locate                      */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_SectorLowerBound(u32 i__u32_Address);

/****************************************************************************/
/*  Function:  fms_RegionLowerBound                                         */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Return the address of the lower bound of the region          */
/*             where the specified parameter address lies.                  */
/*                                                                          */
/*  Return    :  (s32) Address or FMS_UNDEFINED                              */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   |  Address to locate                      */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_RegionLowerBound(u32 i__u32_Address);

/****************************************************************************/
/*  Function: fms_NxtSectorLowerBound                                       */
/*--------------------------------------------------------------------------*/
/*  Scope   : Return the address of the sector following the one where      */
/*            the specified address lies.                                   */
/*                                                                          */
/*  Return    : Address or FMS_OVERFLOW                                     */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   |  Address to locate                      */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_NxtSectorLowerBound(u32 i__u32_Address);
/****************************************************************************/
/*  Function: fms_PreSectorLowerBound                                       */
/*--------------------------------------------------------------------------*/
/*  Scope   : Return the address of the sector following the one where      */
/*            the specified address lies.                                   */
/*                                                                          */
/*  Return    : Address or FMS_OVERFLOW                                     */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   |  Address to locate                      */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/

s32 fms_PreSectorLowerBound(u32 i__u32_Address);

/****************************************************************************/
/*  Function: fms_SizeOfSector                                              */
/*--------------------------------------------------------------------------*/
/*  Scope   : Returns the size of the sector where the specified address    */
/*            lies                                                          */
/*                                                                          */
/*  Return    :  (s32) Address or FMS_OVERFLOW                              */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   | Address to locate                       */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_SizeOfSector(u32 i__u32_Address);

/****************************************************************************/
/*  Function: fms_GetGeometryNumber                                         */
/*--------------------------------------------------------------------------*/
/*  Scope   : Returns the geometry identifier                               */
/*                                                                          */
/*  Return    : (s32) Geometry number                                       */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
s32 fms_GetGeometryNumber(void);

/****************************************************************************/
/* SERVICES RELATED FUNCTIONS                                               */
/****************************************************************************/


/****************************************************************************/
/*  Function: fms_AllocateArea                                              */
/*--------------------------------------------------------------------------*/
/*  Scope   : Allocates a memory area for a service or a code section       */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__e_ServiceArea  | X |   |   |  Service (see fms_s_MemUsage)           */
/*  i__u32_Address    | X |   |   |  Start address                          */
/*  i__u32_Length     | X |   |   |  Size                                   */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_AllocateArea(fms_Area_e i__e_ServiceArea, u32 i__u32_Address, u32 i__u32_Length);

/**
  * @brief Tests if a memory allocation (given origin and size) is allowed for an area
  *
  * @param i__e_ServiceArea Flash area to test
  * @param i__u32_Address Origin of the area
  * @param i__u32_Length Length of the area
  *
  * @return FMS_OK or error code
  */
s32 fms_TestAllocateArea(fms_Area_e i__e_ServiceArea, u32 i__u32_Address, u32 i__u32_Length);


/****************************************************************************/
/*  Function:  fms_RetrieveArea                                             */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Gets information about a specified service                   */
/*                                                                          */
/*  Return    : FMS_OK or FMS_UNDEFINED                                     */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* i__e_ServiceArea   | X |   |   |  Service Area                           */
/* o__pu32_StartAddr  |   | X |   |  Output pointer for start address       */
/* o__pu32_Length     |   | X |   |  Output pointer for length              */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_RetrieveArea(fms_Area_e i__e_ServiceArea, u32 *o__pu32_StartAddr, u32 *o__pu32_Length);


/****************************************************************************/
/*  Function: fms_DeallocateArea                                            */
/*--------------------------------------------------------------------------*/
/*  Scope   : Deallocates the memory space of a service                     */
/*                                                                          */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__e_ServiceArea  | X |   |   |  Service Area                           */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_DeallocateArea(fms_Area_e i__e_ServiceArea);

/****************************************************************************/
/*  Function: fms_DeallocateAll                                             */
/*--------------------------------------------------------------------------*/
/*  Scope   : Deallocates all areas                                         */
/*                                                                          */
/*  Return    : n/a                                                         */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void fms_DeallocateAll(void);

/****************************************************************************/
/*  Function: fms_MapPurgeArea                                              */
/*--------------------------------------------------------------------------*/
/*  Scope   : Erases the contents and deallocates an area                   */
/*                                                                          */
/*  Return    : (s32) FMS_OK or error code                                  */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__e_Area         | X |   |   |  Area to purge                          */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_MapPurgeArea(fms_Area_e i__e_Area);

/****************************************************************************/
/*  Function: fms_MapLaunchService                                          */
/*--------------------------------------------------------------------------*/
/*  Scope   : Launches the specified service                                */
/*                                                                          */
/*                                                                          */
/*  Return    : (s32) FMS_OK if the specified service has got allocated     */
/*                    memory.                                               */
/*                    FMS_UNDEFINED if the area is for code or is incorrect */
/*                    FMS_NOT_AVAILABLE if the service has no memory        */
/*                                                                          */
/*              Notice that FMS_OK does mean that the service has been      */
/*              correctly initialised                                       */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__e_Area         | X |   |   |  Area of the service to launch          */
/*                    |   |   |   |                                         */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_MapLaunchService(fms_Area_e i__e_Area);

/****************************************************************************/
/* FLASH COMMANDS                                                           */
/****************************************************************************/


/****************************************************************************/
/*  Function: fms_Write                                                     */
/*--------------------------------------------------------------------------*/
/*  Scope   : Low-level write function                                      */
/*                                                                          */
/*  Return    :  FMS_OK or error code                                       */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   |  Target address                         */
/*  i__u32_Size       | X |   |   |  Number of bytes to program             */
/*  i__p_Source       | X |   |   |  Source buffer                          */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_Write(u32 i__u32_Address, u32 i__u32_Size, const void *i__p_Source);

/****************************************************************************/
/*  Function: fms_Erase                                                     */
/*--------------------------------------------------------------------------*/
/*  Scope   : Flash device block erasure process                            */
/*                                                                          */
/*  Return    : FMS_OK or error code                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   |  Address of the sector to erase         */
/*  i__u32_Mode       | X |   |   |  Erasure mode                           */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_Erase(u32 i__u32_Address, u32 i__u32_Mode);

/****************************************************************************/
/*  Function: fms_SetProtect                                                */
/*--------------------------------------------------------------------------*/
/*  Scope   : Erase block protection modification utility                   */
/*                                                                          */
/*                                                                          */
/*  Return    : FMS_OK or error code                                        */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/*  i__u32_Address    | X |   |   |  Address of the sector to (un)protect   */
/*  i__u32_Mode       | X |   |   |  Protection mode to set                 */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_SetProtect(u32 i__u32_Address, u32 i__u32_Mode);

/****************************************************************************/
/*  Function: fms_ExtendedCmd                                               */
/*--------------------------------------------------------------------------*/
/*  Scope   : Multi-purposes function                                       */
/*                                                                          */
/*                                                                          */
/*  Return    : depends on the selected function                            */
/*                                                                          */
/*  Interface :                                                             */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* i__u32_FunctionCode| X |   |   |  Selected function                      */
/* i__u32_Address     | X |   |   |  Operating address                      */
/* io__p_Buffer       | X | X |   |  I/O buffer                             */
/*--------------------+---+---+---+-----------------------------------------*/
/****************************************************************************/
s32 fms_ExtendedCmd(u32 i__u32_FunctionCode, u32 i__u32_Address, void *io__p_Buffer);


/** 
 * @brief Modifies the value of a flash address for use by other SW components
 *
 * On some platforms, the flash device address used by FMS is specific
 * and does not match the one used outside FMS.\n
 * This function transforms an internal flash address into an address
 * that can be safely used outside.
 * 
 * @param[in,out] io_pp_PtrAddress Pointer to the value to modify
 */
void fms_TuneOutputPointer(void **io_pp_PtrAddress);

/****************************************************************************/
/*  Function: fms_GetRegionNum                                              */
/*--------------------------------------------------------------------------*/
/*  Scope   : Returns the number of regions of the main flash device        */
/*                                                                          */
/*  Return    : (u32) region num. 0 if error                                */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
u32 fms_GetRegionNum(void);

/****************************************************************************/
/*  Function: fms_GetRegionSectorNum                                        */
/*--------------------------------------------------------------------------*/
/*  Scope   : Returns the number of sectors of a region                     */
/*            of the main flash device                                      */
/*                                                                          */
/*  Return    : (u32) region num. 0 if error                                */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* u32Region          | X |   |   |  Selected function                      */
/****************************************************************************/
u32 fms_GetRegionSectorNum(u32 u32Region);

/****************************************************************************/
/*  Function: fms_GetRegionSectorSize                                       */
/*--------------------------------------------------------------------------*/
/*  Scope   : Returns the sector size of a region                           */
/*            of the main flash device                                      */
/*                                                                          */
/*  Return    : (u32) sector size. 0 if error                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  Variable Name     |IN |OUT|GLB|  Use                                    */
/*--------------------+---+---+---+-----------------------------------------*/
/* u32Region          | X |   |   |  Selected function                      */
/****************************************************************************/
u32 fms_GetRegionSectorSize(u32 u32Region);

void fms_m18_control_read(void * base_addr, int length, void* buf);
int fms_Memcmp(u8* source, u8* sector_base, u32 length);
void fms_Read(void* base_addr, u32 length, void** buff);
void fms_Memcpy(void * base_addr, u32 length, u8* buf);
void* fms_MemAllocate(u32 nSize);
void fms_MemRelease(void* buff);


#endif /* __FMS_PRIV_H__ not defined   */

