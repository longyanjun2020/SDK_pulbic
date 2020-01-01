#ifndef __MMI_COMMON_OFF_TYPE_H__
#define __MMI_COMMON_OFF_TYPE_H__

/*
 * OffApp's Data type/defintion that other libraries need 
 * */
typedef enum
{
  PowerOffType_Normal = 0,      /* Power off by long press END key.             */
  PowerOffType_Auto,            /* Power off by auto power off alarm expired.   */
  PowerOffType_PowerOffMenu,    /* Show power off menu.                         */
  PowerOffType_SwitchDualMode,  /* Switch dual mode                             */
  PowerOffType_LowBattery,      /* Power off by low battery.                    */
  PowerOffType_ATCommand,       /* Power off by AT command.                     */
  PowerOffType_FactoryMode      /* Power off by master restore in factory mode. */
}PowerOffType_e;

#endif //__MMI_COMMON_OFF_TYPE_H__
