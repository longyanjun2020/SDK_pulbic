#ifndef __EML_MAIN_INTF_H__
#define __EML_MAIN_INTF_H__

#ifdef DPM_PARAM

#define DPM_NAME eml_main

#undef __EML_MAIN_INTF_H__
#else // DPM_PARAM

#ifndef INIT_JMPTBL

void (*p_EML_Itf_GetInfo)(unsigned int *, unsigned int *, unsigned int *);
void (*p_EML_Itf_GetSramInfo)(void *);
void (*p_EML_Itf_InitInterface)(void *);
void (*p_EML_Itf_Input)(unsigned long );
void (*p_EML_Itf_Notify)(void *);
void (*p_EML_Itf_Stop)(unsigned int, unsigned char *);

#define EML_Itf_GetInfo (*p_EML_Itf_GetInfo)
#define EML_Itf_GetSramInfo (*p_EML_Itf_GetSramInfo)
#define EML_Itf_InitInterface (*p_EML_Itf_InitInterface)
#define EML_Itf_Input (*p_EML_Itf_Input)
#define EML_Itf_Notify (*p_EML_Itf_Notify)
#define EML_Itf_Stop (*p_EML_Itf_Stop)

#else // INIT_JMPTBL

extern void (*p_EML_Itf_GetInfo)(unsigned int *, unsigned int *, unsigned int *);
extern void (*p_EML_Itf_GetSramInfo)(void *);
extern void (*p_EML_Itf_InitInterface)(void *);
extern void (*p_EML_Itf_Input)(unsigned long );
extern void (*p_EML_Itf_Notify)(void *);
extern void (*p_EML_Itf_Stop)(unsigned int, unsigned char *);

p_EML_Itf_GetInfo           = (void *)*(tmpJmpTbl + 0);
p_EML_Itf_GetSramInfo       = (void *)*(tmpJmpTbl + 1);
p_EML_Itf_InitInterface     = (void *)*(tmpJmpTbl + 2);
p_EML_Itf_Input             = (void *)*(tmpJmpTbl + 3);
p_EML_Itf_Notify            = (void *)*(tmpJmpTbl + 4);
p_EML_Itf_Stop              = (void *)*(tmpJmpTbl + 5);

#endif // INIT_JMPTBL

#endif // DPM_PARAM

#endif // __EML_MAIN_INTF_H__
