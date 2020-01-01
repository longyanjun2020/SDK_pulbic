
#ifndef __ANGRYBIRD_LIB_INC__
#define __ANGRYBIRD_LIB_INC__

#define GROUND_P	50

#define INIT_X		(GROUND_P + 50)
#define INIT_Y		40

#define ANGRYBIRD_BIRD_SIZE				10


typedef enum
{
	PIG_TYPE= 0,
	WOOD_TYPE,
	ICE_TYPE,
	ROCK_TYPE,
	BALL_TYPE,
	BOX_TYPE,
	PLANE_TYPE,
} Type_e;

typedef enum
{
	SHAPE_TYPE_PIG_1 = 0,
	SHAPE_TYPE_PIG_2,
	SHAPE_TYPE_PIG_3,
	SHAPE_TYPE_PIG_4,
	SHAPE_TYPE_PIG_5,
	SHAPE_TYPE_PIG_6,
	SHAPE_TYPE_RED_BIRD,
	SHAPE_TYPE_YELLOW_BIRD,
	SHAPE_TYPE_BLACK_BIRD,
    SHAPE_TYPE_BLUE_BIRD,
	SHAPE_TYPE_WOOD,
	SHAPE_TYPE_ICE,
	SHAPE_TYPE_ROCK,
	SHAPE_TYPE_EXPLOSION,
	SHAPE_TYPE_POOF,
	SHAPE_TYPE_BALL,
	SHAPE_TYPE_BOX,
	SHAPE_TYPE_PLANE,
} ShapeType_e;

typedef enum
{
	COLLISION_TYPE_OTHER = 0,	
	COLLISION_TYPE_WOOD,
	COLLISION_TYPE_ICE,
	COLLISION_TYPE_ROCK,
	COLLISION_TYPE_BIRD,
	COLLISION_TYPE_BOMO,
	COLLISION_TYPE_PIG,
	COLLISION_TYPE_GROUND,
	COLLISION_TYPE_NULL,
}CollisionType_e;

enum
{
	ANGRYBIRD_MENU = 0,
	ANGRYBIRD_CLICK,
	ANGRYBIRD_FIRE,
	ANGRYBIRD_PIG,
	ANGRYBIRD_BREAKS,
}; 
typedef u8 eANGRYBIRD_SOUND;

//////////////////////////////////////////////////////////////////////////
// Angry Bird API 
//////////////////////////////////////////////////////////////////////////

void AngryBird_CreateWorld(void);

void AngryBird_UpdateFrame(void *pUserData, int nfps);

void AngryBird_Render(mgl_u32 nodeID, void *pUserData);

void AngryBird_Destroy(void);


void AngryBird_CreateBirds(mgl_u8 max_bird_num);

void AngryBird_Add_Bird(mgl_u8 idx, mgl_u32 bird_type);

void AngryBird_add_wood_block(cpFloat p_x, cpFloat p_y, cpFloat width, cpFloat height, cpFloat angle);

void AngryBird_add_ice_block(cpFloat p_x, cpFloat p_y, cpFloat width, cpFloat height, cpFloat angle);

void AngryBird_add_rock_block(cpFloat p_x, cpFloat p_y, cpFloat width, cpFloat height, cpFloat angle);

void AngryBird_add_Pigs(cpFloat p_x, cpFloat p_y, cpFloat Pigs_width, cpFloat Pigs_height);

void AngryBird_Add_Ball(float px, float py, float radius);

void AngryBird_Add_Box(float px, float py, float w, float h);
void AngryBird_Add_Plane(float px, float py, float w, float h);
//
//boolean AngryBird_Picking(void* pUserData);

void AngryBird_Check_TouchJoint(void);

float AngryBird_CheckMove(void *pUserData);

//boolean AngryBird_CheckBird(void);

boolean AngryBird_CheckStatus(void);

//boolean AngryBird_NextBird(void);

void AngryBird_SetBird(void *pUserData, u32 bird_type);

void AngryBird_ControlBird(void);

void AngryBird_Add_CollisionHandler(void *pUserData);

void AngryBird_PlayAudioOnce(void *pUser, eANGRYBIRD_SOUND audiotype);

#endif
