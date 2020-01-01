/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_pgl_physics_actor.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_PGL_PHYSICS_ACTOR_INC__
#define __MMI_PGL_PHYSICS_ACTOR_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_pgl_utility_types.h"
#include "mmi_pgl_resource_texmgr.h"
#include "chipmunk_private.h"

/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/
#define PGL_ACTOR_NULL                  0
#define PGL_ACTOR_FIX                   1
#define PGL_COSHANDLER_NULL             0
#define PGL_CONSTRAINT_NULL             0

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/

enum
{
    ePGL_SHAPE_SEGMENT = 0,
    ePGL_SHAPE_TRIANGLE,
    ePGL_SHAPE_CIRCLE,
    ePGL_SHAPE_RECT,
    ePGL_SHAPE_POLYGON,
    ePGL_SHAPE_SPRITE,
    ePGL_SHAPE_CIRCLE_SPRITE,
} ;
typedef pgl_u16 ePgl_Shape_Type;

enum
{
	ePGL_CONSTRAINT_PINJOINT = 0,
	ePGL_CONSTRAINT_SLIDEJOINT,
	ePGL_CONSTRAINT_PIVOTJOINT,
	ePGL_CONSTRAINT_GROOVEJOINT,
	ePGL_CONSTRAINT_DAMPEDSPRING,
	ePGL_CONSTRAINT_DAMPEDROTARYSPRING,
	ePGL_CONSTRAINT_ROTARYLIMITJOINT,
	ePGL_CONSTRAINT_RATCHETJOINT,
	ePGL_CONSTRAINT_GEARJOINT,
	ePGL_CONSTRAINT_SIMPLEMOTOR
};
typedef pgl_u16 ePgl_ConstraintType;
typedef pgl_u16 ePgl_Actor_Name;


/*User-Defined Collision type of input-Actor*/
typedef pgl_s32 hActor;
typedef pgl_s32 hConstraint;
typedef pgl_s32 hActorCosHandler;
typedef void (*FPPglActorCollisionFunc)(hActor hActorA, hActor hActorB, pgl_void *pUserData);
typedef void (*FPPglActorTouchPressCBFunc)(hActor hActorNode, pgl_void *pUserData);
typedef void (*FPPglActorTouchMoveCBFunc)(hActor hActorNode, pgl_u32 Touches_x, pgl_u32 Touches_y, pgl_void *pUserData);
typedef void (*FPPglActorTouchReleaseCBFunc)(hActor hActorNode, pgl_void *pUserData);
typedef struct PglActorTouchesCBFunc_tag
{
    FPPglActorTouchPressCBFunc       fpTouchPressfunCb;
    FPPglActorTouchMoveCBFunc        fpTouchMovefunCb;
    FPPglActorTouchReleaseCBFunc     fpTouchReleasefunCb;
    pgl_void					     *pUserData;
}PglActorTouchesCBFunc_t;

/* define geometry of physics shape */

/** PglSegment_t;

*
* @brief    a:             Start position of Physics Segment actor.
*           b:             End position  of Physics Segment actor.
*
*/
typedef struct pglSegment_tag
{
	Vertex2D a;
	Vertex2D b;
}PglSegment_t;

/** PglCircle_t;

*
* @brief    radius:              radius of Physics Circle actor.
*
*/
typedef struct pglCircle_tag
{
	pgl_float radius;
}PglCircle_t;

/** PglRect_t
*
* @brief    width:              Width of Physics Rect actor.
*           height:             Height of Physics Rect actor.
*
*/
typedef struct pglRect_tag
{
	pgl_float width;
	pgl_float height;
}PglRect_t;

/** PglPolygon_t
*
* @brief    width:              Width of Physics Polygon actor.
*           height:             Height of Physics Polygon actor.
*           nShape_Num:         Shape num of Physics Polygon actor.
*           pVertexNumArray:    Pointer to Vertex Num Array of Physics Polygon actor.
*           pVertsDataArray:    Pointer to Vertex Data Array of Physics Polygon actor.
*
*/
typedef struct pglPolygon_tag
{
	pgl_float   width;
	pgl_float   height;
    pgl_u8      nShape_Num;
    pgl_u8      *pVertexNumArray;
    Vertex2D    *pVertsDataArray;
}PglPolygon_t;

/** PglTriangle_t
*
* @brief    width:              Width of Physics Triangle actor.
*           height:             Height of Physics Triangle actor.
*
*/
typedef struct pglTriangle_tag
{
	pgl_float width;
	pgl_float height;
}PglTriangle_t;

/** PglSprite_t
*
* @brief    width:              Width of Physics Sprite actor.
*           height:             Height of Physics Sprite actor.
*           curFragment:        Current Frame idx of Physics Sprite actor.
*           fragmentStep:       User-defined frame step of Physics Sprite actor.
*           spriteLoopCycle:    User-defined repeat cycle index of Physics Sprite actor.
*
*/
typedef struct pglSprite_tag
{
	pgl_float width;
	pgl_float height;
    pgl_u8  curFragment;
    pgl_u32 fragmentStep;       //PGL_SPRITE_FIX_FRAME : Fix current frame!
    pgl_u32 spriteLoopCycle;    //PGL_SPRITE_INFINITY_LOOP : Infinity loop!
}PglSprite_t;

/** pglCircleSprite_tag
*
* @brief    radius:              radius of Physics Circle actor.
*           curFragment:        Current Frame idx of Physics Sprite actor.
*           fragmentStep:       User-defined frame step of Physics Sprite actor.
*           spriteLoopCycle:    User-defined repeat cycle index of Physics Sprite actor.
*
*/
typedef struct pglCircleSprite_tag
{
	pgl_float radius;
    pgl_u8  curFragment;
    pgl_u32 fragmentStep;       //PGL_SPRITE_FIX_FRAME : Fix current frame!
    pgl_u32 spriteLoopCycle;    //PGL_SPRITE_INFINITY_LOOP : Infinity loop!
}pglCircleSprite_t;

/** pglActorInfo
*
* @brief    engineID:           Engine HandleID of Physics actor.
*           sceneID:            Scene HandleID of Physics actor.
*           actorType:          Actor name of Physics actor.
*           shapeType:          shape type of Physics actor.
*           p:                  Position of Physics actor.
*           v:                  Velocity of Physics actor.
*           angle:              Angle of Physics actor.
*           friction:           Friction of Physics actor.
*           restitution:        Restitution of Physics actor.
*           mass:               Mass of Physics actor.
*           depth:              Z depth of Physics actor.
*           bNoRotate:          Physics actor is rotation or not.
*           angularVelocity:    angularVelocity of Physics actor.
*           resID:              Texture res hangleID of Physics actor.
*           color:              Color of Physics actor.
*           pData:              Pointer to userData of Physics actor.
*           touchesCBFunc:      The Touch call back functiom table of Physics actor..
*           segment:            Settings for Physics segmentactor.
*           circle:             Settings for Physics circle actor.
*           rect:               Settings for Physics rect actor.
*           sprite:             Settings for Physics sprite actor.
*           triangle:           Settings for Physics triangle actor.
*           polygon:            Settings for Physics polygon actor.
*
*/
typedef struct pglActorInfo_tag
{
    EngineHandleID      engineID;
    SceneHandleID       sceneID;
    ePgl_Actor_Name     actorType;
    ePgl_Shape_Type     shapeType;
    Vertex2D p;
    Vertex2D v;
    pgl_float angle;
	pgl_float friction;
	pgl_float restitution;
    pgl_float mass;
    pgl_float depth;
    pgl_boolean bNoRotate;
    pgl_float angularVelocity;              //Auto-Self rotation...
    hTexRes resID;
    Color4f  color;
    pgl_void *pData;
    PglActorTouchesCBFunc_t touchesCBFunc;
    union
    {
        PglSegment_t  segment;                /* for segment line */
        PglCircle_t   circle;                 /* for circle */
        PglRect_t     rect;                   /* for rectangle */
        PglSprite_t   sprite;                 /* for Animation Rect sprite with texture */
        pglCircleSprite_t   circleSprite;                 /* for Animation Rect sprite with texture */
        PglTriangle_t triangle;               /* for triangle */
        PglPolygon_t  polygon;                /* for Polygon*/
    }uActorInfos;
}pglActorInfo;

/* define PivotJoint structure */
typedef struct pglPivotJointInfo_tag
{
	Vertex2D pivot;
}PglPivotJoint_t;

/* define SlideJoint structure */
typedef struct pglSlideJointInfo_tag
{
	Vertex2D anchr_a;
    Vertex2D anchr_b;
    pgl_float min, max;
}PglSlideJoint_t;

/* define PinJoint structure */
typedef struct pglPinJointInfo_tag
{
	Vertex2D anchr_a;
    Vertex2D anchr_b;
}PglPinJoint_t;

/* define GrooveJoint structure */
typedef struct pglGrooveJointInfo_tag
{
	Vertex2D groove_a_1;
    Vertex2D groove_a_2;
    Vertex2D anchr_b;
}PglGrooveJoint_t;

/* define DampedSpringJoint structure */
typedef struct pglDampedSpringJointInfo_tag
{
    Vertex2D anchr_a;
    Vertex2D anchr_b;
    pgl_float restLength;
    pgl_float stiffness;
    pgl_float damping;
}PglDampedSpringJoint_t;

/* define DampedSpringJoint structure */
typedef struct pglDampedRotarySpringJointInfo_tag
{
    pgl_float restAngle;
    pgl_float stiffness;
    pgl_float damping;
}PglDampedRotarySpringJoint_t;

/* define RotaryLimitJoint structure */
typedef struct pglRotaryLimitJointInfo_tag
{
    pgl_float min_angle;
    pgl_float max_angle;
}PglRotaryLimitJoint_t;

/* define RatchetJoint structure */
typedef struct PglRatchetJoint_tInfo_tag
{
    pgl_float phase;
    pgl_float ratchet;
}PglRatchetJoint_t;

/* define GearJoint structure */
typedef struct pglGearJointInfo_tag
{
    pgl_float phase;
    pgl_float ratio;
}PglGearJoint_t;

/* define GearJoint structure */
typedef struct PglSimpleMotorJointInfo_tag
{
    pgl_float rate;
}PglSimpleMotorJoint_t;



/** pglConstraintInfo
*
* @brief    eConstraintType:    Constraint type of Physics joint.
*           Actor_a:            Physics actor A handleID.
*           Actor_b:            Physics actor B handleID.
*           pinj:               Settings for Physics pin joint.
*           slidej:             Settings for Physics slide joint.
*           pivotj:             Settings for Physics pivot joint.
*           groovej:            Settings for Physics groove joint.
*           dspringj:           Settings for Physics damped spring joint.
*           drspringj:          Settings for Physics damped rotary spring joint.
*           rlimitj:            Settings for Physics rotary limit joint.
*           ratchetj:           Settings for Physics ratchet joint.
*           gearj:              Settings for Physics gear joint.
*           simplemotorj:       Settings for Physics simple motor joint.
*
*/
typedef struct pglConstraintInfo_tag
{
	ePgl_ConstraintType eConstraintType;
    hActor Actor_a;
    hActor Actor_b;
	union
	{
        PglPinJoint_t pinj;
        PglSlideJoint_t slidej;
        PglPivotJoint_t pivotj;
        PglGrooveJoint_t groovej;
        PglDampedSpringJoint_t dspringj;
        PglDampedRotarySpringJoint_t drspringj;
        PglRotaryLimitJoint_t rlimitj;
        PglRatchetJoint_t ratchetj;
        PglGearJoint_t gearj;
        PglSimpleMotorJoint_t simplemotorj;
	}uJointInfos;
}pglConstraintInfo;

/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
/*Physics Collision Handlers APIs*/
hActorCosHandler pgl_Physics_ActorCollisionHandler_Create(EngineHandleID engineID, ePgl_Actor_Name CTypeA, ePgl_Actor_Name CTypeB,
         FPPglActorCollisionFunc fpActorCollBeginFunc, FPPglActorCollisionFunc fpActorCollSeparateFunc, pgl_void *pUserData);
pgl_void pgl_Physics_CollisionHandler_Destroy(EngineHandleID engineID, hActorCosHandler handler);

/*Physics Actor APIs*/

/** pgl_Physics_Actor_Add
* @brief      Add a physics Actor into PGL game engine space.
*
* @param[in]  pActorInfo        Pointer to physics actor parameters to be used for creating a physics actor.
*
* @retval     hActor            return physics actor handleID.
*
*/
hActor pgl_Physics_Actor_Add(pglActorInfo *pActorInfo);

/** pgl_Physics_Actor_Destroy
* @brief      Destroy a Physics Actor from PGL game engine space.
*
* @param[in]  hAct              Physics actor handleID.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_Destroy(hActor hAct);

/** pgl_Physics_Actor_ModifySpriteInfos
* @brief      Modify sprite infos of Physics Actor that is Sprite.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  curFragment       Current Frame idx of Physics Sprite actor.
* @param[in]  fragmentStep      User-defined frame step of Physics Sprite actor.
* @param[in]  spriteLoopCycle   User-defined repeat cycle index of Physics Sprite actor.
*
* @retval     ePgl_RetCode      return ePGL_RET_SUCCESS if Physics actor resID is modified successfully.
*
*/
ePgl_RetCode pgl_Physics_Actor_ModifySpriteInfos(hActor hAct, pgl_u8 curFragment, pgl_u32 fragmentStep, pgl_u32 spriteLoopCycle);

/** pgl_Physics_Actor_ModifyTexResID
* @brief      Modify texture res handleID of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  TexReID           Texture resource handleID.
*
* @retval     ePgl_RetCode      return ePGL_RET_SUCCESS if Physics actor resID is modified successfully.
*
*/
ePgl_RetCode pgl_Physics_Actor_ModifyTexResID(hActor hAct,hTexRes TexReID);

/** pgl_Physics_Actor_ModifyActorName
* @brief      Modify name{collision_type} of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  name              Physics actor collision name.
*
* @retval     ePgl_RetCode      return ePGL_RET_SUCCESS if Physics actor collision name is modified successfully.
*
*/
ePgl_RetCode pgl_Physics_Actor_ModifyActorName(hActor hAct,ePgl_Actor_Name name);

/** pgl_Physics_Actor_GetData
* @brief      Get userData of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
*
* @retval     pgl_void*         Pointer to userData.
*
*/
pgl_void* pgl_Physics_Actor_GetData(hActor hAct);

/** pgl_Physics_Actor_SetFixedPosition
* @brief      Fix position of Physics Actor under PGL space with gravity.
*
* @param[in]  hAct              Physics actor handleID.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_SetFixedPosition(hActor hAct);

/** pgl_Physics_Actor_RemoveFixedPosition
* @brief      Cancel fix-position of Physics Actor under PGL space with gravity.
*
* @param[in]  hAct              Physics actor handleID.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_RemoveFixedPosition(hActor hAct);

/** pgl_Physics_Actor_ApplyForce
* @brief      Apply force effect onto Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  force             Force power value.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_ApplyForce(hActor hAct, Vertex2D force);

/** pgl_Physics_Actor_ApplyTorque
* @brief      Apply torque effect onto Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  torque            Torque power value.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_ApplyTorque(hActor hAct, pgl_float torque);

/** pgl_Physics_Actor_ApplyImpulse
* @brief      Apply impulse effect onto Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  impulse           Impulse power value.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_ApplyImpulse(hActor hAct, Vertex2D impulse);

/** pgl_Physics_Actor_ApplyAngular
* @brief      Apply angular effect onto Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  angularVelocity   Angular power value.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_ApplyAngular(hActor hAct, pgl_float angularVelocity);

/** pgl_Physics_Actor_ApplyExplosionImpulse
* @brief      Apply explosion impulse effect onto Physics Actor.
*
* @param[in]  hExplosionAct     Physics explosion actor handleID.
* @param[in]  hForcedAct        Physics forced actor handleID.
* @param[in]  impulse_weight    Explosion impulse power value.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_ApplyExplosionImpulse(hActor hExplosionAct, hActor hForcedAct, pgl_float impulse_weight);

/** pgl_Physics_Actor_ResetForce
* @brief      Remove all forces of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_ResetForce(hActor hAct);

/** pgl_Physics_Actor_SetPosition
* @brief      Set Position of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  pos               New position.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_SetPosition(hActor hAct,Vertex2D pos);

/** pgl_Physics_Actor_SetTouchMove
* @brief      Move Physics actor based on touch move infos.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  nTSx              Touch X position.
* @param[in]  nTSy              Touch Y position.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_SetTouchMove(hActor hAct, pgl_u32 nTSx, pgl_u32 nTSy);

/** pgl_Physics_Actor_SetRotation
* @brief      Set Rotation of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  rotation          Rotation angle.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_SetRotation(hActor hAct,pgl_float rotation);

/** pgl_Physics_Actor_SetColor
* @brief      Set color of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  r                 Red Channel.
* @param[in]  g                 Green Channel.
* @param[in]  b                 Blue Channel.
* @param[in]  a                 AlphaChannel.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_SetColor(hActor hAct, pgl_float r, pgl_float g, pgl_float b, pgl_float a);

/** pgl_Physics_Actor_ChangeTex
* @brief      Set Current texture frame idx of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  index             Frame index.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_ChangeTex(hActor hAct, pgl_u8 index);

/** pgl_Physics_Actor_SetStatus
* @brief      Set status of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  status            status of Physics actor.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_SetStatus(hActor hAct, pgl_s32 status);

/** pgl_Physics_Actor_GetStatus
* @brief      Get status of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
*
* @retval     pgl_s32           return status of Physics actor.
*
*/
pgl_s32 pgl_Physics_Actor_GetStatus(hActor hAct);

/** pgl_Physics_Actor_GetPosition
* @brief      Get position of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  pPos              Pointer to position for reading.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_GetPosition(hActor hAct, Vertex2D *pPos);

/** pgl_Physics_Actor_GetAngular
* @brief      Get AngularVelocity of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
*
* @retval     pgl_float         Angular Velocity.
*
*/
pgl_float pgl_Physics_Actor_GetAngular(hActor hAct);

/** pgl_Physics_Actor_GetRotation
* @brief      Get Rotation Angle of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
*
* @retval     pgl_float         Rotation Angle.
*
*/
pgl_float pgl_Physics_Actor_GetRotation(hActor hAct);

/** pgl_Physics_Actor_GetVelocity
* @brief      Get Velocity of Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  pPos              Pointer to Velocity for reading.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_GetVelocity(hActor hAct, Vertex2D *pVelocity);

/** pgl_Physics_Actor_SetVelocity
* @brief      Set Velocity ofq Physics Actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  velocity          New velocity for setting.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_SetVelocity(hActor hAct, Vertex2D velocity);

//Anim.............
typedef pgl_void (*FPPglActorDelayCBFunc)(hActor hActorNode, pgl_void *pUserData);

/** pgl_Physics_Actor_Delay
* @brief      Apply Physics action of Gui actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  duration          Animation time.
* @param[in]  fpDelayCBFunc     The delay call back function .
* @param[in]  pUserData         Pointer to userData.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_Delay(hActor hAct, pgl_s32 duration, FPPglActorDelayCBFunc fpDelayCBFunc, pgl_void *pUserData);

/** pgl_Physics_Actor_MoveTo
* @brief      Apply MoveTo action of Gui actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  newPosition       The last animation position of Physics actor.
* @param[in]  duration          Animation time.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_MoveTo(hActor hAct, Vertex2D newPosition, pgl_s32 duration);

/** pgl_Physics_Actor_RotateTo
* @brief      Apply RotateTo action of Gui actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  newRotation       The last animation rotation angle of Physics actor.
* @param[in]  duration          Animation time.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_RotateTo(hActor hAct, pgl_float newRotation, pgl_s32 duration);

/** pgl_Physics_Actor_JumpTo
* @brief      Apply JumpTo action of Gui actor.
*
* @param[in]  hAct              Physics actor handleID.
* @param[in]  jumpheight        The last animation height of Physics actor.
* @param[in]  duration          Animation time.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_JumpTo(hActor hAct, Vertex2D jumpheight, pgl_s32 duration);

/** pgl_Physics_Actor_Remove_Action
* @brief      Remove action of Physics actor.
*
* @param[in]  hActor          Physics actor handleID.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Actor_Remove_Action(hActor hActor);


/*Physics Constraint APIs*/
/** pgl_Physics_Constraint_Visible
* @brief      Visible constraint line of PGL engine space.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  lineWidth         Line width of constraint joint.
* @param[in]  r                 Red Channel.
* @param[in]  g                 Green Channel.
* @param[in]  b                 Blue Channel.
* @param[in]  a                 AlphaChannel.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Constraint_Visible(EngineHandleID engineID, pgl_u8 lineWidth, pgl_float r, pgl_float g, pgl_float b, pgl_float a);

/** pgl_Physics_Constraint_Invisible
* @brief      Invisible constraint line of PGL engine space.
*
* @param[in]  engineID          PGL Engine HandleID.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Constraint_Invisible(EngineHandleID engineID);

/** pgl_Physics_Constraint_Create
* @brief      Create a Physics constraint joint into PGL game engine space.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  pConstraintInfo   Pointer to constraint parameters to be used for creating a physics joint.
*
* @retval     hConstraint       return Constraint handleID.
*
*/
hConstraint pgl_Physics_Constraint_Create(EngineHandleID engineID, pglConstraintInfo *pConstraintInfo);

/** pgl_Physics_Constraint_Create
* @brief      Destroy a Physics constraint joint from PGL game engine space.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  hcos              Constraint handleID.
*
* @retval     None.
*
*/
pgl_void pgl_Physics_Constraint_Destroy(EngineHandleID engineID, hConstraint hcos);
pgl_void pgl_Physics_Space_Clear(EngineHandleID engineID);

#endif

