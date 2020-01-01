#ifndef __CUTROPE_INC__
#define __CUTROPE_INC__

#include "mmi_baseapplet.h"
#include "mae_widgetbase.h"
#include "mgl_Core_Types.h"

#include "chipmunk_private.h"

#define CUTROPE_SLICE_VARIOUS_COLOR_SPEED			2.0f		//Various color speed of comet.
#define CUTROPE_SLICE_LENGTH_THREAD				10		
#define CUTROPE_SLICE_LENGTH_THREAD_DELTA			0.8f/(float)CUTROPE_SLICE_LENGTH_THREAD

#define TIMER_INTERVAL 25
#define EN_TIME 1
#define EN_AUDIO 1
#define EN_RECORD 1
#define STAGE_NUM 36

#define CUTROPE_SLICE_POWER       2.5f
#define GETSTAR_STEP 40

#define CROPE_NODE_MAX      30
#define CROPE_ROPE_MAX      10
#define CROPE_HANDLER_MAX   10
#define CROPE_ERROR         0xffff
#define CROPE_NULL          0x1000

typedef mgl_s16 hCRope;
typedef mgl_s16 hCRopeNode;
typedef mgl_s16 hCRopeCosHandler;

enum
{
    eCROPE_NODE_COLLISION = 0,
    eCROPE_NODE_NO_COLLISION,
} ;
typedef mgl_u16 eCROPE_NODE_COLLISION_STATUS;

enum
{
    eCROPE_LAYER_NO_COLLISION = 0,
    eCROPE_LAYER_COLLISION,
    eCROPE_LAYER_FORCE,
} ;
typedef mgl_u16 eCROPE_LAYER_TYPE;

enum
{
    eTEXID_BALL = 0,
    eTEXID_RANGE1,
    eTEXID_RANGE2,
    eTEXID_BALLWithBUBBLE1,
    eTEXID_BALLWithBUBBLE2,
    eTEXID_BALLWithBUBBLE3,
    eTEXID_FIXSWITCH,
    eTEXID_GOAL1,
    eTEXID_GOAL2,
    eTEXID_GOAL3,
    eTEXID_GOAL4,
    eTEXID_GOAL5,
    eTEXID_GOAL6,
    eTEXID_GOAL7,
    eTEXID_GOAL8,
    eTEXID_GOAL9,
    eTEXID_BUBBLE,
    eTEXID_FORCE,
    eTEXID_FORCE1,
    eTEXID_STAR,
    eTEXID_TOTALSTAR,
    eTEXID_BG,
    eTEXID_THORN,
    eTEXID_SCORE0,
    eTEXID_SCORE1,
    eTEXID_SLICE,
    eTEXID_PLAY,
    eTEXID_PLAY_PRESS,
    eTEXID_SOUND,
    eTEXID_SOUNDCLOSE,
    eTEXID_PAUSE,
    eTEXID_AGAIN,
    eTEXID_AGAIN_PRESS,
    eTEXID_MENU,
    eTEXID_MENU_PRESS,
    eTEXID_RATE0,
    eTEXID_RATE1,
    eTEXID_RATE2,
    eTEXID_RATE3,
    eTEXID_PREVIOUS,
    eTEXID_PREVIOUS_PRESS,
    eTEXID_NEXT,
    eTEXID_NEXT_PRESS,
    eTEXID_IDLE_BG,
    eTEXID_BG_2,
    eTEXID_BG_3,
    eTEXID_BG_4,
    eTEXID_TIME,
    eTEXID_NUMBER0,
    eTEXID_NUMBER1,
    eTEXID_NUMBER2,
    eTEXID_NUMBER3,
    eTEXID_NUMBER4,
    eTEXID_NUMBER5,
    eTEXID_NUMBER6,
    eTEXID_NUMBER7,
    eTEXID_NUMBER8,
    eTEXID_NUMBER9,
    eTEXID_COLON,
    eTEXID_DASH,
    eTEXID_SLASH,
    eTEXID_STAGE_LOCK,
    eTEXID_STAGE_BG,
    eTEXID_STAGE1,
    eTEXID_STAGE2,
    eTEXID_STAGE3,
    eTEXID_STAGE4,
    eTEXID_STAGE5,
    eTEXID_STAGE6,
    eTEXID_STAGE7,
    eTEXID_STAGE8,
    eTEXID_STAGE9,
    eTEXID_STOPSCREEN,
    eTEXID_OPTIONMENU,
    eTEXID_HELPBUTTON,
    eTEXID_HELPBUTTON_PRESS,
    eTEXID_HELP,
    eTEXID_THEME1,
    eTEXID_THEME2,
    eTEXID_THEME3,
    eTEXID_THEME4,
    eTEXID_TOTAL,
    eTEXID_COMP1,
    eTEXID_COMP2,
    eTEXID_THEMELOCK,
    eTEXID_STONE,
    eTEXID_RANGE1_L,
    eTEXID_RANGE2_L,
    eTEXID_RESUME,
    eTEXID_RESUME_PRESS,
} ;
typedef mgl_u16 eCROPE_TEXTYPE;

enum
{
    eCROPE_COLLISION_TYPE_NULL,
	eCROPE_COLLISION_TYPE_FIXED,
	eCROPE_COLLISION_TYPE_RANGE,
	eCROPE_COLLISION_TYPE_WALL,
	eCROPE_COLLISION_TYPE_THORN,
    eCROPE_COLLISION_TYPE_STAR,
    eCROPE_COLLISION_TYPE_CPBALL,
    eCROPE_COLLISION_TYPE_BUBBLE,
    eCROPE_COLLISION_TYPE_FORCE,
	eCROPE_COLLISION_TYPE_GOAL,
    eCROPE_COLLISION_TYPE_MAX,
};
typedef mgl_u16 eCROPE_COLLISION_TYPE;

enum
{
	eCROPE_NODE_TYPE_NULL = 0,
    eCROPE_NODE_TYPE_FIXED,
    eCROPE_NODE_TYPE_RANGE,
    eCROPE_NODE_TYPE_WALL,
    eCROPE_NODE_TYPE_THORN,
    eCROPE_NODE_TYPE_STAR,
	eCROPE_NODE_TYPE_CPBALL,
    eCROPE_NODE_TYPE_CPBALLWithBUBBLE,
	eCROPE_NODE_TYPE_BUBBLE,
	eCROPE_NODE_TYPE_FORCE,
    eCROPE_NODE_TYPE_GOAL,
};
typedef mgl_u16 eCROPE_NODE_TYPE;

typedef struct CRopebody_tag
{
    mgl_boolean         isActive;
	hCRope              hRopeIDX;
    hCRopeNode          hNodeA;
    hCRopeNode          hNodeB;   
    cpBody              **cpbodyList;
    mgl_u16             Segment;
    cpVect p;
}CRopebody;

typedef struct CPBallNodeInfo_tag
{
    cpFloat mass;    
    cpFloat radius;      
}CPBallNodeInfo;

typedef struct BubbleNodeInfo_tag
{
    cpFloat mass;    
    cpFloat radius;
}BubbleNodeInfo;

typedef struct ForceNodeInfo_tag
{     
    cpFloat mass;    
    cpFloat size;
    Vertex2D ForceDir;
}ForceNodeInfo;

typedef struct StarNodeInfo_tag
{     
    cpFloat mass;    
    cpFloat radius;
}StarNodeInfo;

typedef struct FixedNodeInfo_tag
{     
    cpFloat mass;    
    cpFloat size;
}FixedNodeInfo, GoalNodeInfo;

typedef struct RangeNodeInfo_tag
{     
    cpFloat mass;    
    cpFloat size;
    cpFloat RopeLength;
}RangeNodeInfo;

typedef struct WallNodeInfo_tag
{     
    cpFloat mass;    
    cpFloat sizeW;
    cpFloat sizeH;
}WallNodeInfo;

typedef struct ThornNodeInfo_tag
{     
    cpFloat mass;    
    cpFloat size;
}ThornNodeInfo;

typedef struct CRopeNodeData_tag
{
	eCROPE_NODE_TYPE        NodeType;
    Vertex2D                NodePos;
    mgl_u32                 NodeTexID;
    mgl_boolean             NoddeFixed;
    union{
        CPBallNodeInfo          CPBallNodeParam;
        BubbleNodeInfo          BubbleNodeParam;
        ForceNodeInfo           ForceNodeParam;
        StarNodeInfo            StarNodeParam;
        FixedNodeInfo           FixedNodeParm;
        RangeNodeInfo           RangeNodeParm;
        WallNodeInfo            WallNodeParm;
        ThornNodeInfo            ThornNodeParam;
        GoalNodeInfo            GoalNodeParm;
    }NodeParam;
}CRopeNodeData;

typedef void (*CRopeCollisionFunc)(void *pThis, hCRopeNode hCRpoeA, hCRopeNode hCRpoeB);

typedef struct CRopeCosHandler_tag
{
	mgl_boolean             isActive;
    hCRopeCosHandler        hCosHandler;
    eCROPE_COLLISION_TYPE       a;
    eCROPE_COLLISION_TYPE       b;
    CRopeCollisionFunc      CollisionFunc;
    void *pThis;
}CRopeCosHandler;

typedef struct CRopeNodebody_tag
{
	mgl_boolean     isActive;
    mgl_boolean     isFixed;
    hCRopeNode      hNode;
    cpBody          *pNodebody;
    cpShape         *pNodeShape;
    cpConstraint    *pFixedConstraint;
    eCROPE_NODE_TYPE  eNodeType;
    cpVect          ForceDirect;
}CRopeNodebody;

typedef struct
{
	APPLET_BASE_ELEMENTS;
	boolean	bTouched;
   
	u16     u16SceneHandleId;
	s16     s16TextureHandleId;
	s16     s16TSType;
	u32     nodeID[3];
	s32		nTS_CurrentX, nTS_CurrentY;

    boolean	    bSlice;
    Vertex3D	    f_SlicePos;
    Vertex3D	    Slices[CUTROPE_SLICE_LENGTH_THREAD];
    Vertex3D	    p_LineCoords[CUTROPE_SLICE_LENGTH_THREAD];
    Color4f		    p_LineColors[CUTROPE_SLICE_LENGTH_THREAD];
    Vertex3D  	    p_SliceVertice[CUTROPE_SLICE_LENGTH_THREAD<<1];
    Vertex2D  	    p_SliceTex[CUTROPE_SLICE_LENGTH_THREAD<<1];

	boolean bSuspendMode;
	boolean bDraw;

#ifndef __G3D_MMI__
	IWidget *pBgImgWdg;
        mgl_u32 lastBG;
#endif
    mgl_u16 sg_demoidx;
    mgl_boolean sg_bwin;
    mgl_boolean sg_breload;
    mgl_boolean sg_bthorn;

    mgl_float sg_RopeNodeSize;
    mgl_float sg_RopeNodeRopeLength;
    mgl_float sg_ForceDirX;
    mgl_float sg_ForceDirY;
    mgl_float themeX[4];
    mgl_float themeY[4];
    mgl_float themeXTarget;
    u32 themeXPress;
    u32 themeXOriginalPress;
    boolean sg_bDeepColor;

    boolean sg_drawItem;

    int Ball_x_dir;
    int Ball_y_dir;
    mgl_float Ball_x;
    mgl_float Ball_y;
    mgl_float Ball_y_up_threshold;

    int sg_totalStar;
    int GetStar_num;
    mgl_float GetStar_x[3];
    mgl_float GetStar_shift_x[3];
    mgl_float GetStar_y[3];
    mgl_float GetStar_shift_y[3];
    int GetStar_step[3];

#if EN_TIME
    int sg_BaseTime;
    int sg_SuspendTime;
    int sg_SuspendBaseTime;
#endif

    int sg_EatCount;
    int sg_NormalCount;
    int sg_StarCount;
    int sg_BubbleCount;

    boolean sg_NoEat;
    mgl_u16 sg_starscore;
    boolean sg_bPlayPress;
    boolean sg_bHelpPress;
    boolean sg_bSound;
    boolean sg_bPausePress;
    boolean sg_bAgainPress;
    boolean sg_bMenuPress;
    int sg_Time;
    boolean sg_bNextPress;
    boolean sg_bResumePress;
    boolean sg_bPreviousPress;
    u8 sg_StageScore[STAGE_NUM];
    int sg_StageBase;


    cpSpace *sg_CRopeSpace;
    cpBody *sg_CRopeStaticBody;
    cpConstraint *sg_CRopeTouchJoint;
    CRopeNodebody sg_Nodebody[CROPE_NODE_MAX];
    CRopebody sg_Ropebody[CROPE_ROPE_MAX];
    CRopeCosHandler sg_CosHandler[CROPE_HANDLER_MAX];
    cpVect sg_Cut_S, sg_Cut_E;
    cpVect sg_BallPos;
    hCRopeNode sg_GoalNode;
    hCRopeNode sg_BallNode;
    hCRopeNode sg_ForceNode;
}CutRopeApp_t;

typedef struct CRopeDrawData_tag
{
	mgl_u32     nodeID;
    CutRopeApp_t *pThis;
}CRopeDrawData;



MAE_Ret CutRopeWdg_Ctor(CutRopeApp_t *pThis);
MAE_Ret CutRopeWdg_Dtor(CutRopeApp_t *pThis);
void CutRopeWdg_Draw(CutRopeApp_t *pWdg);
boolean CutRopeWdg_DefHandleEvent(CutRopeApp_t *pWdg, MAE_EventId evt, u32 P1, u32 P2);

#endif
