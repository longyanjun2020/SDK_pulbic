#ifndef AGCAPI_H
#define AGCAPI_H

void            MMPF_AGC_SetEnable(MMP_BOOL enable);
MMP_BOOL        MMPF_AGC_IsEnable(void);
void            Init_AGConfigs(void);
MMP_LONG        AGC_Proc(void);
void            AGC_SetAUDIOParameter(MMP_SHORT MaxDB, MMP_SHORT MinDB, MMP_SHORT target_level,MMP_SHORT hold_time);
//void            AGC_dbg_printf(int x, char* y);
#endif /* AGCAPI_H*/

