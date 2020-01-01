/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SRS SRS3D types, constants
 *
 *	Author: Zesen Zhuang
 *
 *  RCS keywords:
 *	$Id: //srstech/srs_srs3d/std_fxp/include/srs_srs3d_def.h#3 $
 *  $Author: oscarh $
 *  $Date: 2011/02/14 $
 *
********************************************************************************/

#ifndef __SRS_SRS3D_DEF_H__
#define __SRS_SRS3D_DEF_H__

#include "srs_typedefs.h"


#define SRS_SRS3D_GAIN_IWL	1
#define SRS_SRS3D_CTRL_IWL	1

typedef struct _SRSSrs3dObj{int _;}	* SRSSrs3dObj;

#define SRS_SRS3D_OBJ_SIZE					(sizeof(_SRSSrs3dObj_t)+8)
#define SRS_SRS3D_WORKSPACE_SIZE(blksize)	(sizeof(srs_int32)*(blksize)*4+8)

/****** SRS 3D Modes ******/
typedef enum
{
	SRSSrs3dMono,
	SRSSrs3dSingleSpeaker,
	SRSSrs3dStereo,
	SRSSrs3dExtreme
//	SRSSrs3dModeSize
} SRSSrs3dMode;

////////////////////////////////////////////////////////////////////////////////////////
//SRS Internal Use:
typedef struct
{
	int							Enable;				//enable, 0: disabled, non-zero: enabled
	srs_int16					InputGain;			//refined?
	srs_int16					OutputGain;			//refined?
	srs_int16					BypassGain;			//refined?

	int							HighBitRate;
	srs_int16					SpaceCtrl;
	srs_int16					CenterCtrl;
	int							Headphone;
	SRSSrs3dMode				Mode;

	srs_int16					NormGain;


	const srs_int16				*InitFilterCoefPtr;
	int							InitFilterIwl;
	const srs_int16				*InitFilterCoefPtrArry[4];
	int							InitFilterIwlArry[4];

	const srs_int16				*FinalFilterCoefPtr;
	const srs_int16				*SingleAllPassFilterCoefPtr;
	const srs_int16				*SingleFirstFilterCoefPtr;
	const srs_int16				*SingleSecondFilterCoefPtr;
	const srs_int16				*SingleThirdFilterCoefPtr;


} _SRSSrs3dSettings_t;


typedef struct
{
	/* Storage for the SRS3D filter state variables */
	srs_int32					InitFilterState[2];						/* Length:	2 */
	srs_int32					FinalFilterState[1];					/* Length:	1 */
	srs_int32					SingleAllPassFilterState[1];			/* Length:	1 */	// single speaker

	srs_int32					PhaseShiftFilterState[6];

} _SRSSrs3dState_t;


typedef struct
{
	_SRSSrs3dSettings_t		Settings;
	_SRSSrs3dState_t		State;
} _SRSSrs3dObj_t;

#endif //__SRS_SRS3D_DEF_H__
