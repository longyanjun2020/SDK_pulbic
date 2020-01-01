/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2010 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Effect_ParticleSystem.h
 *
 *
 * HISTORY
 *      2010.11.11       Pioneer Huang         Initial Version
 *      
 *                                          
 *----------------------------------------------------------------------------- 
 */

#ifndef __M_EFFECT_PARTICLESYSTEM_H__
#define __M_EFFECT_PARTICLESYSTEM_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_Common.h"
#include "mgl_Texture_ImgMgr.h"
#include "mgl_Core_Types.h"

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#define MAX_PARTICLESYSTEM_COUNT 5
#define NOT_FOUND_PARTICLESYSTEM -1
#define BAD_PARAM_PARTICLESYSTEM -2


/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
enum
{
    PS_EFFECT_EMIT_GUN_SHOOT = 0,
    PS_EFFECT_EMIT_FOUNTAIN,
    PS_EFFECT_EMIT_FLAME,
    PS_EFFECT_EMIT_FLAME_CIRCLE,
    PS_EFFECT_EMIT_FLAME_GALAXY,
    PS_EFFECT_EMIT_FLAME_FIRWORK,
    PS_EFFECT_EMIT_BUTTERFLY_FIRWORK,
    PS_EFFECT_EMIT_VARIOUS_CIRLCE_COMET,
    PS_EFFECT_EMIT_CIRLCE_COMET,
    PS_EFFECT_EMIT_SMOKE,
    PS_EFFECT_EMIT_GHOST,
    PS_EFFECT_EMIT_SATRFIELD,
    PS_EFFECT_EMIT_CIRCLE_SATRFIELD,
    PS_EFFECT_NOEMIT_RAND,
    PS_EFFECT_NOEMIT_SNOW,    
    PS_EFFECT_EMIT_MAX,
    PS_EFFECT_LIVEWALLPAPER_SNOW,      /* custom1 */
    PS_EFFECT_LIVEWALLPAPER_FIRE,           /* custom2 */
    /* user add */
};
typedef mgl_u16 PS_EFFECTTYPE;

enum
{
	PS_NOEMIT =  0x0,
	PS_EMIT,
};
typedef mgl_u16 PS_EMITMODE;

typedef struct ParticlesInfo_tag
{  
    mgl_float       	    p_fSize;
    Vertex3D	    p_glvLocation; 
    Vertex3D	    p_glvVelocity;   
    Vertex3D	    p_glvAcceleration;
    Color4f		    p_glcColor;  

    mgl_u16 	    index;                             /* don't modify */
    mgl_void              *pUserData;
}ParticlesInfo;

typedef struct ParticleSystemInfo_tag
{        
    mgl_float   ps_fLife;                          /* input normalize value 0~1 */
    mgl_float   ps_fLifeVar;                   /* input normalize value 0~1 */
    
    mgl_float   ps_fSpeed;                           /* time */
    Vertex3D   ps_vEmitLocation;	    
    mgl_u16    ps_uEmitType;                      /* ¦³µL¼Q¼L */

    mgl_u16     ps_uParticleNum;          /* don't modify */
    mgl_u16     ps_uParticleEffect;         /* don't modify */
	
    mgl_void    *pUserData;
}ParticleSystemInfo;

typedef mgl_boolean (*InitCB)(ParticleSystemInfo *pPSInfo);
typedef mgl_void (*UpdateOneParticleCB)(ParticleSystemInfo *pPSInfo, ParticlesInfo *pOneParticle);
typedef mgl_boolean (*RebornOneParticleCB)(ParticleSystemInfo *pPSInfo, ParticlesInfo *pOneParticle);
typedef mgl_void (*UpdeateEmitMotionCB)(ParticleSystemInfo *pPSInfo);

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
mgl_boolean mgl_Effect_RenderParticleSystem(mgl_u16 psID, T_TEXTURE_ATTR_PTR pTexAttri, mgl_float TexAlpha);
mgl_void mgl_Effect_ReleaseParticleSystem(mgl_u16 psID);
mgl_s16 mgl_Effect_CreateParticleSystem(mgl_u16 u16ParticleNum, mgl_u16 ParticleEffect, InitCB pfn_Init, UpdateOneParticleCB pfn_updateOneParticle, RebornOneParticleCB pfn_rebornOneParticle, UpdeateEmitMotionCB pfn_updateEmitMotion);

#endif /* __M_EFFECT_PARTICLESYSTEM_H__ */
