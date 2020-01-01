/**
 * @file mmi_mae_sm_defs.h
 *
 * This file defines the data structure used by state machine application
 *
 * @see mmi_mae_sm.h
 * @see mmi_mae_sm_defs.h
 *
 * @version $Id: mmi_mae_sm_defs.h 609 2009-04-10 15:49:02Z zinc.chen $
 */
#ifndef __MMI_MAE_SM_DEFS_H__
#define __MMI_MAE_SM_DEFS_H__
#include "mmi_mae_common_def.h"

/*-------------------------------------------------------------------------*/

#define cNone				((SM_ModeId_t)0xFF)	/**< Deprecated, use SM_MODE_NONE instead */

#define SM_MODE_NONE		((SM_ModeId_t)0xFF)	/**< Reserved mode number */
#define SM_MODE_DYNAMIC		((SM_ModeId_t)0xFE)	/**< To indicate the target mode is determinted at runtime */
#define SM_TRANS_NONE		((SM_TransId_t)0xFFFF)	/**< Reserved transition number */
/*-------------------------------------------------------------------------*/

typedef enum
{
    MODE_METHOD_ENTRY       = 0,
    MODE_METHOD_EXIT           ,
    MODE_METHOD_CONDITION      ,
    MODE_METHOD_ACTION         ,
    MODE_METHOD_GET_DEST
}SM_MethodType_e;

typedef enum
{
    TRANS_TYPE_INTERNAL			= 0,
    TRANS_TYPE_DEFAULT			,
    TRANS_TYPE_HISTORY			,
    TRANS_TYPE_DEEP
}SM_TransType_e;

typedef enum
{
    EXEC_MODE_ACTIVATE			= 0,
    EXEC_MODE_INACTIVATE		,
    EXEC_MODE_TRANSITION
}SM_ExecMode_e;

typedef u8  SM_ModeId_t;
typedef u16 SM_TransId_t;

typedef struct SM_t_ SM_t;
typedef s32 (*PfnGenericModeMethod)(void *app, SM_t *pSM, s32 actToken, s32 index);

/*-------------------------------------------------------------------------*/
#define SM_MODE_TRANSITION_MASK             0x03FF
#define SM_MODE_LEVEL_MASK                  0x3C00
#define SM_MODE_HASENTRY_MASK               0x4000
#define SM_MODE_HASEXIT_MASK                0x8000

/**
 * Macro for making a single record of SM_Mode_t
 */
/* deprecated, use MODE_MAKEREC instead */
#define MODE_makeRec(parent, defaultChild, level, modeMethod, hadEntry, hasExit, transitionNum) \
{(SM_ModeId_t)parent, (SM_ModeId_t)defaultChild, \
((u16)((transitionNum)& SM_MODE_TRANSITION_MASK) | \
(u16)((level) << 10) | \
(u16)((hadEntry) << 14) | \
(u16)((hasExit) << 15)), \
(GenericModeMethod)modeMethod}
#define MODE_MAKEREC(parent, defaultChild, level, modeMethod, hadEntry, hasExit, transitionNum) \
{(SM_ModeId_t)parent, (SM_ModeId_t)defaultChild, \
((u16)((transitionNum)& SM_MODE_TRANSITION_MASK) | \
(u16)((level) << 10) | \
(u16)((hadEntry) << 14) | \
(u16)((hasExit) << 15)), \
(PfnGenericModeMethod)modeMethod}

/**
 * Record for one node in mode tree.
 */
typedef struct
{
    SM_ModeId_t      nParent;         /**< Parent mode ID, cNone for Root mode */
    SM_ModeId_t      nDefaultChild;   /**< Default child ID, cNone if no  */
    u16         nBitfields;      /**< 0-9 number of transitions; 10-13 level; 14 hasEntry(0/1); 15 hasExit(0/1) */
    PfnGenericModeMethod pfnMethods;
}SM_Mode_t;

#define SM_TRANS_TYPE_MASK                  0x0003
#define SM_TRANS_HASACTION_MASK             0x0004
#define SM_TRANS_HASCONDITION_MASK          0x0008
#define SM_TRANS_SOURCEEQUALDEST_MASK       0x0010
#define SM_TRANS_TOANCESSOR_MASK            0x0020
#define SM_TRANS_TODESCENDANT_MASK          0x0040

/**
 * Macro for making a single record of SM_Transition_t
 */
/* deprecated, use TRANSITION_MAKEREC instead */
#define TRANSITION_makeRec(source, target, type, hasAction, toAncessor, toDescendant, sourceEqualDest, hasCondition) \
{(SM_ModeId_t)source, (SM_ModeId_t)target, \
((u16)((type)& SM_MODE_TRANSITION_MASK) | \
(u16)((hasAction) << 2) | \
(u16)((hasCondition) << 3) | \
(u16)((sourceEqualDest) << 4) | \
(u16)((toAncessor) << 5) | \
(u16)((toDescendant) << 6))}
#define TRANSITION_MAKEREC(source, target, type, hasAction, toAncessor, toDescendant, sourceEqualDest, hasCondition) \
{(SM_ModeId_t)source, (SM_ModeId_t)target, \
((u16)((type)& SM_MODE_TRANSITION_MASK) | \
(u16)((hasAction) << 2) | \
(u16)((hasCondition) << 3) | \
(u16)((sourceEqualDest) << 4) | \
(u16)((toAncessor) << 5) | \
(u16)((toDescendant) << 6))}

/**
 * Record for transitions
 */
typedef struct
{
    SM_ModeId_t  nSourceMode;
    SM_ModeId_t  nTargetMode;
    /**
     * 0-1 types(internal,default,history,deep);
     * 2 hasAction(0/1);
     * 3 hasCondition(0/1);
     * 4 sourceEqualDest(0/1);
     * 5 toAncestor(0/1);
     * 6 toDescendant(0/1);
     * 7-15 reserved
     */
    u16 nFlags;
}SM_Transition_t;

/**
 * Macro for making a single record of SM_EventDep_t
 */
/* deprecated, use EVENT_DEP_MAKEREC instead */
#define EVENT_DEP_makeRec(event, index) \
{(u32)event, (u16)index}
#define EVENT_DEP_MAKEREC(event, index) \
{(u32)event, (u16)index}

/**
 * Record for event->transitions (one to many)
 */
typedef struct
{
    u32 nEventID;		/**< event id */
    u16 nIndexEntry;		/**< index of first transitions for this event */
}SM_EventDep_t;


#define SM_TRANSFOREVENT_TRANS_MASK                  0x7FFF
#define SM_TRANSFOREVENT_ISMORE_MASK                 0x8000

/**
 * Macro for making a single record of SM_TransitionForEvent_t
 */
/* deprecated, use TRANS_FOR_EVENT_MAKEREC instead */
#define TRANS_FOR_EVENT_makeRec(trans, more) ((trans) | (more << 15))
#define TRANS_FOR_EVENT_MAKEREC(trans, more) ((trans) | (more << 15))

/**
 * Transition entry for Events
 * 0-14 Entry of transition;
 * 15 isMore, There are more transitions for this event;
 */
typedef u16 SM_TransitionForEvent_t;

//typedef struct T_SM_TRANSITION_FOR_EVENT_TAG
//{
//    u16 transID;    /* Entry of transition */
//    u8  isMore;     /* There are more transitions for this event */
//}
//SM_TransitionForEvent_t;

#define APP_ISPROCESSING_MASK                       0x01
#define APP_PROCESSING_MASK                         0xF0

#ifdef __SM_TRANSITION_HISTORY__

#define MAX_TRANS_HISTORY_COUNT						10
typedef struct
{
	u8				nTail;									/**< idx of history which pointer to the oldest transition (or empty node)*/
	SM_TransId_t	nTransHistory[MAX_TRANS_HISTORY_COUNT];	/**< Transition idx in array of transition */
	MAE_EventId		nEventHistory[MAX_TRANS_HISTORY_COUNT];	/**< event ID for each transition */
}SM_TransHistory_t;

#endif

/**
 * MAO(Mobile Applicatio Object)
 * This structure represents one state machine appliciation including
 * the structure of mode tree, the transitions, listened events,
 * the relationship between event and transitions and the working memory location.
 */
typedef struct
{
    void*       pSelf;										/**< pointer to real object instance */
    u16         nDependencyNumbers;							/**< Size of SM_EventDep_t array */
    u8          nModeNumbers;								/**< Number of modes */
    u8          nFlag;                                       /**< 0: isProcessing; 1-7 reserved */
    const SM_Mode_t*          pModeArray;					/**< Mode tree definitation array */
    const SM_Transition_t*    pTransitionArray;				/**< Transition definitation array */
    const SM_EventDep_t*     pEventDepArray;				/**< All listened events array */
    const SM_TransitionForEvent_t*  pTransForEventArray;	/**< Relationship between event and transition */
    SM_ModeId_t*              pLastActiveModeArray;				/**< Lastest active child for each mode, the array size shoulde be modeNumbers */
    SM_ModeId_t*              pCurrentMode;						/**< Current active leaf child */
#ifdef __SM_TRANSITION_HISTORY__
	SM_TransHistory_t	tTransHistory;					/**< Latest MAX_TRANS_HISTORY_COUNT transition executed */
#endif
}SM_Mao_t;

typedef struct
{
	MAE_EventId nId;			/**< event id */
	u32     nParam1;			/**< parameter for event */
	u32     nParam2;			/**< parameter for event */
}SM_Event_t;

struct SM_t_
{
	 SM_Event_t* pCurEvt;	/**< the event during processing */
};
/*-------------------------------------------------------------------------*/

#endif /* __MAE_SM_DEFS_H__ */
