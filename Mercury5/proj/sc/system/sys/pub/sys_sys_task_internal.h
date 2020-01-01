/** @file sys_sys_task_internal.h
 * @author Piazza.Lo
 * @date 04/28/2011
 *
 * Define task structure
 */

#ifdef TASK_DEF

  // WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
  // If you had or remove any task in the array below, do not forget to
  // modify accordingly the TASK ID constants in osdefs.hc
  // WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING

  /*  Name   ,  EntryPoint , Priority ,  StackSize    , arm exception el */
#ifndef __HWL_TINY__
#ifndef __WIRTI_USE__
#ifndef __MSTAR_DUAL_SIM__
TASK_DEF( IDLE   ,  idle_Task    ,        0 ,  IDLE_STACK_SIZE  ,  _HWL   )
#if !defined(__3G__)
TASK_DEF( SS     ,  ss_Task      ,       18 ,  SS_STACK_SIZE    ,  _L3SS  )
TASK_DEF( SMS    ,  sm_Task      ,       19 ,  SM_STACK_SIZE    ,  _L3SM  )
TASK_DEF( CC     ,  cc_Task      ,       20 ,  CC_STACK_SIZE    ,  _L3CC  )
TASK_DEF( SIM    ,  sim_Task     ,       21 ,  SIM_STACK_SIZE   ,  _SIM   )
TASK_DEF( MM     ,  mm_Task      ,       22 ,  MM_STACK_SIZE    ,  _L3MM  )
TASK_DEF( RR     ,  rr_Task      ,       29 ,  RR_STACK_SIZE    ,  _L3RR  )
TASK_DEF( DL     ,  Dl_Task      ,       30 ,  DL_STACK_SIZE    ,  _LAPD  )
TASK_DEF( MSR    ,  msr2_Task    ,       31 ,  MSR_STACK_SIZE   ,  _MSR   )
TASK_DEF( DAT    ,  dat_Task     ,       32 ,  DAT_STACK_SIZE   ,  _DATA  )
TASK_DEF( SPV    ,  spv2_Task    ,       33 ,  SPV_STACK_SIZE   ,  _SPV   )
#ifndef __NO_HACTIM_TASK__
TASK_DEF( HAC    ,  hac2_Task    ,       34 ,  HAC_STACK_SIZE   ,  _HAC   )
#else
TASK_DEF( HAC    ,  null_Task	   , 	     34 ,  NULL_STACK_SIZE  ,  _HAC   )
#endif // __NO_HACTIM_TASK__
#endif // __3G__
TASK_DEF( V24    ,  v24_Task     ,       14 ,  V24_STACK_SIZE   ,  _HWL   )
#if !defined(__3G__)
TASK_DEF( IP     ,  ip_Task      ,       12 ,  IP_STACK_SIZE    ,  _DATA  )
#endif
TASK_DEF( BATT   ,  bat_Task     ,       16 ,  BATT_STACK_SIZE  ,  _HWL   )
TASK_DEF( ABB    ,  abb_Task     ,       15 ,  ABB_STACK_SIZE   ,  _HWL   )
  /*
   ** Customer tasks
   ** 2 higher priorities then MDL are reserved for customer Task => prio 11 & prio 10
   */
TASK_DEF( MDL    ,  mdl_Task     ,       9 ,   MDL_STACK_SIZE   ,  _MDL   )
#if !defined(__3G__)
  /*
   ** GPRS tasks
   ** Task order MUST be consistent with gosdefs.hc
   */
TASK_DEF( PPS    ,  pps_Task     ,       17 ,  PPS_STACK_SIZE   ,  _DATA  )
TASK_DEF( SM     ,  smg_Task     ,       23 ,  SM_STACK_SIZE    ,  _L3SMG )
TASK_DEF( SNDCP  ,  sn_Task      ,       25 ,  SND_STACK_SIZE   ,  _SNDCP )
TASK_DEF( LLC    ,  ll_Task      ,       26 ,  LLC_STACK_SIZE   ,  _LLC   )
TASK_DEF( RLD    ,  rld_Task     ,       27 ,  RLD_STACK_SIZE   ,  _RLD   )
TASK_DEF( RLU    ,  rlu_Task     ,       28 ,  RLU_STACK_SIZE   ,  _RLU   )
#endif //__3G__
TASK_DEF( PM     ,  MdlPmTask    ,       35 ,  PM_STACK_SIZE    ,  _IOB   )
#else // __MSTAR_DUAL_SIM__
#ifndef __MSTAR_DUAL_SIM_REDUCE_CODE__
TASK_DEF( IDLE   ,  idle_Task    ,        0 ,  IDLE_STACK_SIZE  ,  _HWL   )
#if !defined(__3G__)
TASK_DEF( SS     ,  ss_Task      ,       21 ,  SS_STACK_SIZE    ,  _L3SS  )
TASK_DEF( SMS    ,  sm_Task      ,       23 ,  SM_STACK_SIZE    ,  _L3SM  )
TASK_DEF( CC     ,  cc_Task      ,       25 ,  CC_STACK_SIZE    ,  _L3CC  )
TASK_DEF( SIM    ,  sim_Task     ,       27 ,  SIM_STACK_SIZE   ,  _SIM   )
TASK_DEF( MM     ,  mm_Task      ,       29 ,  MM_STACK_SIZE    ,  _L3MM  )
TASK_DEF( RR     ,  rr_Task      ,       41 ,  RR_STACK_SIZE    ,  _L3RR  )
TASK_DEF( DL     ,  Dl_Task      ,       43 ,  DL_STACK_SIZE    ,  _LAPD  )
TASK_DEF( MSR    ,  msr2_Task    ,       45 ,  MSR_STACK_SIZE   ,  _MSR   )
TASK_DEF( DAT    ,  dat_Task     ,       47 ,  DAT_STACK_SIZE   ,  _DATA  )
TASK_DEF( SPV    ,  spv2_Task    ,       49 ,  SPV_STACK_SIZE   ,  _SPV   )
#ifndef __NO_HACTIM_TASK__
TASK_DEF( HAC    ,  hac2_Task    ,       52 ,  HAC_STACK_SIZE   ,  _HAC   )
#else
  /* Since the task ID defined in osdefs.hc is mapping   */
  /* to the tasks in cus_InitTask[]. The purpose of this */
  /* null task is to make sure the task Id will not be   */
  /* shifted by the __NO_HACTIM_TASK__ */
TASK_DEF( HAC    ,  null_Task    , 	     52 ,  NULL_STACK_SIZE  ,  _HAC   )
#endif // __NO_HACTIM_TASK__
#endif // __3G__
TASK_DEF( V24    ,  v24_Task     ,       14 ,  V24_STACK_SIZE   ,  _HWL   )
#if !defined(__3G__)
TASK_DEF( IP     ,  ip_Task      ,       12 ,  IP_STACK_SIZE    ,  _DATA  )
#endif //__3G__
TASK_DEF( BATT   ,  bat_Task     ,       16 ,  BATT_STACK_SIZE  ,  _HWL   )
TASK_DEF( ABB    ,  abb_Task     ,       15 ,  ABB_STACK_SIZE   ,  _HWL   )
TASK_DEF( MDL    ,  mdl_Task     ,        9 ,  MDL_STACK_SIZE   ,  _MDL   )
#if !defined(__3G__)
TASK_DEF( PPS    ,  pps_Task     ,       19 ,  PPS_STACK_SIZE   ,  _DATA  )
TASK_DEF( SM     ,  smg_Task     ,       31 ,  SMG_STACK_SIZE   , _L3SMG  )
TASK_DEF( SNDCP  ,  sn_Task      ,       33 ,  SND_STACK_SIZE   ,  _SNDCP )
TASK_DEF( LLC    ,  ll_Task      ,       35 ,  LLC_STACK_SIZE   ,  _LLC   )
TASK_DEF( RLD    ,  rld_Task     ,       37 ,  RLD_STACK_SIZE   ,  _RLD   )
TASK_DEF( RLU    ,  rlu_Task     ,       39 ,  RLU_STACK_SIZE   ,  _RLU   )
TASK_DEF( CC2    ,  cc_Task_2    ,       24 ,  CC2_STACK_SIZE   ,  _L3CC2 )
TASK_DEF( SS2    ,  ss_Task_2    ,       20 ,  SS2_STACK_SIZE   ,  _L3SS2 )
TASK_DEF( SMS2   ,  sm_Task_2    ,       22 ,  SM2_STACK_SIZE   ,  _L3SM2 )
TASK_DEF( MM2    ,  mm_Task_2    ,       28 ,  MM2_STACK_SIZE   ,  _L3MM2 )
TASK_DEF( RR2    ,  rr_Task_2    ,       40 ,  RR2_STACK_SIZE   ,  _L3RR2 )
TASK_DEF( DL2    ,  Dl_Task_2    ,       42 ,  DL2_STACK_SIZE   ,  _LAPD2 )
TASK_DEF( SPV2   ,  spv2_Task_2  ,       48 ,  SPV2_STACK_SIZE  ,  _SPV2  )
TASK_DEF( MSR2   ,  msr2_Task_2  ,       44 ,  MSR2_STACK_SIZE  ,  _MSR2  )
TASK_DEF( SM2    ,  smg_Task_2   ,       30 ,  SMG2_STACK_SIZE  ,  _L3SMG2)
TASK_DEF( SNDCP2 ,  sn_Task_2    ,       32 ,  SND2_STACK_SIZE  ,  _SNDCP2)
TASK_DEF( LLC2   ,  ll_Task_2    ,       34 ,  LLC2_STACK_SIZE  ,  _LLC2  )
TASK_DEF( RLD2   ,  rld_Task_2   ,       36 ,  RLD2_STACK_SIZE  ,  _RLD2  )
TASK_DEF( RLU2   ,  rlu_Task_2   ,       38 ,  RLU2_STACK_SIZE  ,  _RLU2  )
TASK_DEF( MDL2   ,  mdl_Task_2   ,        8 ,  MDL2_STACK_SIZE  ,  _MDL2  )
TASK_DEF( CE     ,  ce_Task      ,       50 ,  CE_STACK_SIZE    ,  _CE    )
TASK_DEF( PPS2   ,  pps_Task_2   ,       18 ,  PPS2_STACK_SIZE  ,  _DATA  )
TASK_DEF( IP2    ,  ip_Task_2    ,       11 ,  IP2_STACK_SIZE   ,  _DATA  )
#endif // __3G__
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
#if !defined(__3G__)
TASK_DEF( SIM2   ,  sim_Task_2   ,       26 ,  SIM2_STACK_SIZE  ,  _SIM2  )
#endif // __3G__
#endif
TASK_DEF( PM     ,  MdlPmTask    ,       54 ,  PM_STACK_SIZE    ,  _IOB   )
TASK_DEF( DSR    ,  dsr_Task     ,       53 ,  DSR_STACK_SIZE   ,  _SYS   )
TASK_DEF( TIMER  ,  timer_Task   ,       51 ,  TIMER_STACK_SIZE ,  _RTK   )
#else
  /* Task 0 must be IDLE task */
TASK_DEF( IDLE   ,  idle_Task    ,        0 , IDLE_STACK_SIZE   ,  _HWL   )
#if !defined(__3G__)
TASK_DEF( CE     ,  ce_Task      ,       50 , CE_STACK_SIZE     ,  _CE    )
  /* Stack task ID should be arranged according to its module ID. */
TASK_DEF( CC     ,  cc_Task      ,       25 , CC_STACK_SIZE     ,  _L3CC  )
TASK_DEF( CC2    ,  cc_Task_2    ,       24 , CC2_STACK_SIZE    ,  _L3CC2 )
TASK_DEF( SS     ,  ss_Task      ,       21 , SS_STACK_SIZE     ,  _L3SS  )
TASK_DEF( SS2    ,  ss_Task_2    ,       20 , SS2_STACK_SIZE    ,  _L3SS2 )
TASK_DEF( SMS    ,  sm_Task      ,       23 , SM_STACK_SIZE     ,  _L3SM  )
TASK_DEF( SMS2   ,  sm_Task_2    ,       22 , SM2_STACK_SIZE    ,  _L3SM2 )
TASK_DEF( MM     ,  mm_Task      ,       29 , MM_STACK_SIZE     ,  _L3MM  )
TASK_DEF( MM2    ,  mm_Task_2    ,       28 , MM2_STACK_SIZE    ,  _L3MM2 )
TASK_DEF( RR     ,  rr_Task      ,       41 , RR_STACK_SIZE     ,  _L3RR  )
TASK_DEF( RR2    ,  rr_Task_2    ,       40 , RR2_STACK_SIZE    ,  _L3RR2 )
TASK_DEF( DL     ,  Dl_Task      ,       43 , DL_STACK_SIZE     ,  _LAPD  )
TASK_DEF( DL2    ,  Dl_Task_2    ,       42 , DL2_STACK_SIZE    ,  _LAPD2 )
TASK_DEF( SPV    ,  spv2_Task    ,       49 , SPV_STACK_SIZE    ,  _SPV   )
TASK_DEF( SPV2   ,  spv2_Task_2  ,       48 , SPV2_STACK_SIZE   ,  _SPV2  )
TASK_DEF( MSR    ,  msr2_Task    ,       45 , MSR_STACK_SIZE    ,  _MSR   )
TASK_DEF( MSR2   ,  msr2_Task_2  ,       44 , MSR2_STACK_SIZE   ,  _MSR2  )
TASK_DEF( SM     ,  smg_Task     ,       31 , SMG_STACK_SIZE    ,  _L3SMG )
TASK_DEF( SM2    ,  smg_Task_2   ,       30 , SMG2_STACK_SIZE   ,  _L3SMG2)
TASK_DEF( SNDCP  ,  sn_Task      ,       33 , SND_STACK_SIZE    ,  _SNDCP )
TASK_DEF( SNDCP2 ,  sn_Task_2    ,       32 , SND2_STACK_SIZE   ,  _SNDCP2)
TASK_DEF( LLC    ,  ll_Task      ,       35 , LLC_STACK_SIZE    ,  _LLC   )
TASK_DEF( LLC2   ,  ll_Task_2    ,       34 , LLC2_STACK_SIZE   ,  _LLC2  )
TASK_DEF( RLD    ,  rld_Task     ,       37 , RLD_STACK_SIZE    ,  _RLD   )
TASK_DEF( RLD2   ,  rld_Task_2   ,       36 , RLD2_STACK_SIZE   ,  _RLD2  )
TASK_DEF( RLU    ,  rlu_Task     ,       39 , RLU_STACK_SIZE    ,  _RLU   )
TASK_DEF( RLU2   ,  rlu_Task_2   ,       38 , RLU2_STACK_SIZE   ,  _RLU2  )
#endif
TASK_DEF( MDL    ,  mdl_Task     ,        9 , MDL_STACK_SIZE    ,  _MDL   )
#if !defined(__3G__)
TASK_DEF( MDL2   ,  mdl_Task_2   ,        8 , MDL2_STACK_SIZE   ,  _MDL2  )
TASK_DEF( SIM    ,  sim_Task     ,       27 , SIM_STACK_SIZE    ,  _SIM   )
#ifdef __MSTAR_DUAL_SIM_SIM_DUO__
TASK_DEF( SIM2   ,  sim_Task_2   ,       26 , SIM2_STACK_SIZE   ,  _SIM2  )
#endif
TASK_DEF( IP     ,  ip_Task      ,       12 , IP_STACK_SIZE     ,  _DATA  )
TASK_DEF( IP2    ,  ip_Task_2    ,       11 , IP2_STACK_SIZE    ,  _DATA  )
TASK_DEF( PPS    ,  pps_Task     ,       19 , PPS_STACK_SIZE    ,  _DATA  )
TASK_DEF( DAT    ,  dat_Task     ,       47 , DAT_STACK_SIZE    ,  _DATA  )
#endif
#ifndef __NO_HACTIM_TASK__
TASK_DEF( HAC    ,  hac2_Task    ,       52 ,  HAC_STACK_SIZE   ,  _HAC   )
#else
  /* Since the task ID defined in osdefs.hc is mapping   */
  /* to the tasks in cus_InitTask[]. The purpose of this */
  /* null task is to make sure the task Id will not be   */
  /* shifted by the __NO_HACTIM_TASK__ */
TASK_DEF( HAC    ,  null_Task    , 	     52 ,  NULL_STACK_SIZE  ,  _HAC   )
#endif
TASK_DEF( V24    ,  v24_Task     ,       14 , V24_STACK_SIZE    ,  _HWL   )
TASK_DEF( BATT   ,  bat_Task     ,       16 , BATT_STACK_SIZE   ,  _HWL   )
TASK_DEF( ABB    ,  abb_Task     ,       15 , ABB_STACK_SIZE    ,  _HWL   )
TASK_DEF( PM     ,  MdlPmTask    ,       54 ,  PM_STACK_SIZE    ,  _IOB   )
TASK_DEF( DSR    ,  dsr_Task     ,       53 ,  DSR_STACK_SIZE   ,  _SYS   )
TASK_DEF( MDL_EXT, mdl_Task_ext  ,		 7	, MDL_EXT_STACK_SIZE,  _MDL   )    /* use MDL trace group since it is not used by anyone */
TASK_DEF( TIMER  ,  timer_Task   ,       51 ,  TIMER_STACK_SIZE ,  _RTK   )
#endif
#endif // __MSTAR_DUAL_SIM__

#else // __WIRTI_USE__
TASK_DEF( WIRTI  ,  wirti_task   ,       33 ,  IDLE_STACK_SIZE  ,  _HWL   )
#endif
#else // __HWL_TINY__
TASK_DEF( IDLE   ,  idle_Task    ,        0 ,  IDLE_STACK_SIZE  ,  _HWL   )
#if !defined(__3G__)
TASK_DEF( SPV    ,  spv2_Task    ,       33 ,  SPV_STACK_SIZE   ,  _SPV   )     // Necessary for V24 serial link
#endif
TASK_DEF( V24    ,  v24_Task     ,       14 ,  V24_STACK_SIZE   ,  _HWL   )     // Serial link
#endif

#endif // TASK_DEF

