/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  ParametricEQ types, constants
 *
 *	Author: Oscar Huang
 *	
 *	(RCS keywords below, do not edit)
 *  $Id: //srstech/srs_common/std_fxp/include/srs_parametriceq_def.h#2 $
 *  $Author: oscarh $
 *  $Date: 2011/02/14 $
********************************************************************************/
#ifndef __SRS_PARAMETRICEQ_DEF_H__
#define __SRS_PARAMETRICEQ_DEF_H__

#include "srs_typedefs.h"

typedef struct _SRSParametricEqObj{int _;}*	SRSParametricEqObj;

#define SRS_PARAMETRICEQ_OBJ_SIZE(nBands, filterWl)		(sizeof(_SRSParametricEqObj_t) + \
														sizeof(_SRSParametricEqBand_t)*(nBands) + \
														SRS_PEQ_STATE_WL(filterWl)*SRS_PEQ_BAND_ORDER*(nBands)+16)     /*Extra 16 bytes for alignment on boundary 8*/

#define SRS_PEQ_GAIN_IWL			4	//Integer word length of inpug gain, output gain and bypass gain

#define SRS_PEQ_BAND_ORDER	2	/*Assuming each band is implemented in a 2nd order IIR*/
/*Macros for computing PEQ core and obj size in bytes*/
#define SRS_PEQ_STATE_WL(filterWl)	((filterWl)==SRSFilter16? sizeof(srs_int32):sizeof(srs_int64))	//filter state word length in bytes


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SRS Internal Use:
typedef struct
{
	int						Enable;			/*enable/disable of the band*/
	const void					*FilterCoef;	//filter coefs of this band: b0, a1, b1, a2, b2, could be srs_int16 or sr_int32
} _SRSParametricEqBand_t;

typedef struct
{
	int							Enable;				//Master enable, 0: disabled, non-zero: enabled
	srs_int16					InputGain;			//I16.SRS_PEQ_GAIN_IWL
	srs_int16					OutputGain;			//I16.SRS_PEQ_GAIN_IWL
	srs_int16					BypassGain;			//I16.SRS_PEQ_GAIN_IWL		
	int							NumOfBands;			//the number of PEQ bands
	_SRSParametricEqBand_t		*Bands;				//PEQ bands
	const void					*FilterGain;		//Overall gain of the cascaded SOS PEQ filters.
} _SRSParametricEqSettings_t;

typedef struct
{
	void			*BandFiltersState;			//could be srs_int32 or srs_int64
} _SRSParametricEqState_t;

typedef struct
{
	_SRSParametricEqSettings_t	Settings;
	_SRSParametricEqState_t		State;
} _SRSParametricEqObj_t;

#endif //__SRS_PARAMETRICEQ_DEF_H__
