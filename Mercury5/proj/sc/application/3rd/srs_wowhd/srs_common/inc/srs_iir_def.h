/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SOS cascaded IIR filter types, constants
 *
 *	Author: Oscar Huang
 *	
 *	(RCS keywords below, do not edit)
 *  $Id$
 *  $Author$
 *  $Date$
********************************************************************************/
#ifndef __SRS_IIR_DEF_H__
#define __SRS_IIR_DEF_H__

#include "srs_typedefs.h"

typedef struct _SRSIirObj{int _;}*	SRSIirObj;

#define SRS_IIR_OBJ_SIZE(order)	(sizeof(_SRSIirObj_t) + sizeof(srs_int64)*(((order)+1)>>1)*2 + 16)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SRS Internal Use:
typedef struct
{
	int 		Enable;
	int			NumOfSections;	//Number of SOS.
	int			CoefWordLen;	//0: 16-bit coefficients, 1: 32-bit coefficients, see SRSFilterWl
	const void	*FilterCoefs;
} _SRSIirSettings_t;

typedef struct
{
	void	*FilterState;
} _SRSIirState_t;

typedef struct
{
	_SRSIirSettings_t		Settings;
	_SRSIirState_t			State;
} _SRSIirObj_t;


#endif //__SRS_IIR_DEF_H__
