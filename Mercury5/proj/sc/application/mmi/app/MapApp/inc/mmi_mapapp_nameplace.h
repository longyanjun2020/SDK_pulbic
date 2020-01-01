#ifndef _NAMEPLACE_H
#define _NAMEPLACE_H

#include "fw_std.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef MVOID (*T_NP_DRAWNAME_FUNC_PTR)(PU16 sName, pVertex_st ptVertex, S32 iTextRotation);//, S32 iTextCenPosX, S32 iTextCenPosY);
typedef MBOOL (*T_NP_CHECK_POSITION_FUNC_PTR)(S32 iX, S32 iY);


MVOID nplInitNamePlace(MVOID);

MVOID nplEndNamePlace(MVOID);

MVOID nplResetNamePlace(MVOID);

MBOOL nplFindName(PU16 sName);

MVOID nplAddName(PU16 sName, pVertex_st ptVertex, S32 iTextRotation);//, S32 iTextCenPosX, S32 iTextCenPosY);

MVOID nplDrawName(T_NP_DRAWNAME_FUNC_PTR pfnDrawNameCB);

MVOID nplClipNamePlaceData(T_NP_CHECK_POSITION_FUNC_PTR pfnCheckPos);

#ifdef  __cplusplus
}
#endif

#endif
