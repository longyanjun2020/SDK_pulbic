#ifndef __MMI_MAE_THMMGR_H__
#define __MMI_MAE_THMMGR_H__

#ifdef __RS_USE_SCRIPT__

#define LoadRC(apid, wid) (wid##_t *) &t##wid

#else

typedef struct {
    u16 nThmId;
    u32 nThmName;
}ThmInfo_t;

void ThmMgrInit(void);
u16 ThmGetThemesNum(void);
MAE_Ret ThmGetThemesID(u32 *pId, u16 nNum);
MAERet_t ThmChangeThm(u32 nThmNameId);
u32 ThmChangeThmEx(u32 nThmNameId);
u16 ThmGetRotation(void);
boolean ThmSetRotation(u16 nRotation);
boolean ThmIsThmSupported(u16 nRotation,u16 nAPResId);
u16 ThmGetDefaultRotation(void);

void* LoadRCFromCUS(u16 apid, u16 wndid);

#define LoadRC(apid, wid) LoadRCFromCUS(apid,wid)

#endif

#define ThmDefault  0
#define THM_LANDSCAPE 90
#define THM_PORTRAIT 0

#endif
