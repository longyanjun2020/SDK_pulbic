/// **************************************************************************
/// \file fms_burst.h
/// \brief Burst mode configuration structure
///
///
///


#ifndef _fa5c5adecb9f4f58d14a2de63510b6eb_included_fms_burst_h
#define _fa5c5adecb9f4f58d14a2de63510b6eb_included_fms_burst_h

/** 
  * @brief Synchronous access configuration information
  *
  * This structure must be filled by fms_ConfigureBurstMode's caller.
  * \n
  * Notice that the burst mode frequency is not configured here.
  * All frequencies related issues must be dealt with before calling
  * fms_ConfigureBurstMode.
  */
typedef struct
{
    /**
      * @brief Set to TRUE to activate burst mode, to FALSE to deactivate
      */
    u8 u8_EnableSynchronousMode;

    /**
      * @brief Chip Select number to configure (presumably, 0)
      */
    u8 u8_ChipSelectNumber;

    /**
      * @brief CLKBURST cycles from address valid to data valid
      *
      * The interpretation of this parameter depends on the platform
      * and the flash device type. The smaller it is, 
      * the faster the accesses are.
      * 
      * @note The parameter is taken into account when activating and when
      * deactivating the synchronous mode.
      * \n
      * On Swift platforms (PCF5213), when deactivating the burst mode,
      * this is the number of cycles required to perform a read access
      * in asynchronous mode.
      */
    u8 u8_ClkBurstCyclesToData;

} fms_BurstConfig_t;

/** 
  * @brief Setup the synchronous access to flash memory 
  * 
  * @param i_ps_BurstCfg Synchronous mode configuration
  * @note The interrupts are masked during the execution of this function
  * @return FMS_OK if the operation is successful, FMS_BAD_FUNCTION if the device does not support burst mode
  */
s32 fms_ConfigureBurstMode(fms_BurstConfig_t *i_ps_BurstCfg);

#endif /* ! _fa5c5adecb9f4f58d14a2de63510b6eb_included_fms_burst_h */
