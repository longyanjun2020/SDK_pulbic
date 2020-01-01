
/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_vampiregame_gamescene_maps.h
*
*
* HISTORY
*      2012.02.22       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_VAMPIREGAME_GAMESCENE_MAP__
#define __MMI_VAMPIREGAME_GAMESCENE_MAP__


/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/

typedef struct
{
    eVAMPIRE_ACTOR_TYPE ActorType;
    pgl_float pos_x, pos_y;
    pgl_float size_w, size_h;
    pgl_float angle;
}Vampire_LevelInfo_t;


typedef struct
{
	pgl_u8 actorIDX_a, actorIDX_b;
}Vampire_ConstraintInfo_t;

typedef struct
{
    Vampire_LevelInfo_t *plevel;
	pgl_u16	ActorNum;
    Vampire_ConstraintInfo_t *pConstraint;
    pgl_u16	ConstraintNum;
}Vampire_AllLevels;
////// Level 1
static Vampire_LevelInfo_t Vampire_Level1[] =
{
    {eVAMPIRE_ACTOR_GOODVAMPIRE,	220.000000f,    98.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_HUMAN,	        100.000000f,	224.000000f,	40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GIRL,	        220.000000f,	224.000000f,	40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        176.000000f,	136.000000f,	128.000000f,	36.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        56.000000f,     230.000000f,    71.000000f,     230.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        71.000000f,     231.000000f,    90.000000f,     265.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        89.000000f,     265.000000f,    392.000000f,    266.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        391.000000f,    266.000000f,    409.000000f,    231.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        409.000000f,    230.000000f,    424.000000f,    230.000000f,    0.000000f},
};

////// Level 2
static Vampire_LevelInfo_t Vampire_Level2[] =
{
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    220.000000f,    42.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_HUMAN,	        220.000000f,    224.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        173.000000f,    82.000000f,	    128.000000f,    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        141.000000f,    82.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        300.000000f,    82.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_CLERGYMAN,	    220.000000f,    128.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        56.000000f,     230.000000f,    71.000000f,     230.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        71.000000f,     231.000000f,    90.000000f,     265.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        89.000000f,     265.000000f,    392.000000f,    266.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        391.000000f,    266.000000f,    409.000000f,    231.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        409.000000f,    230.000000f,    424.000000f,    230.000000f,    0.000000f},
};
static Vampire_ConstraintInfo_t Vampire_Constaint2[] =
{
    {3, 5},
    {4, 5},
};

////// Level 3
static Vampire_LevelInfo_t Vampire_Level3[] =
{
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    293.000000f,    123.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GIRL,	        297.000000f,    225.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        259.000000f,    50.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        334.000000f,    50.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GARLIC,	        269.000000f,    176.000000f,    16.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GARLIC,	        306.000000f,    177.000000f,    16.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GARLIC,	        343.000000f,    178.000000f,    16.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        282.000000f,    265.000000f,    392.000000f,    266.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        391.000000f,    266.000000f,    409.000000f,    231.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        409.000000f,    230.000000f,    424.000000f,    230.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        55.999981f,    196.000015f,     280.999969f,    265.000000f,    0.000000f},
};
static Vampire_ConstraintInfo_t Vampire_Constaint3[] =
{
    {3, 0},
    {2, 0},
};


////// Level 4
static Vampire_LevelInfo_t Vampire_Level4[] =
{
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    347.000000f,    112.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_HUMAN,	        98.000000f,	    97.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        133.000000f,    113.000000f,    32.000000f,	    32.000000f,	    14.826500f},
    {eVAMPIRE_ACTOR_BOX,	        318.000000f,    129.000000f,    32.000000f,	    32.000000f,	    -14.743600f},
    {eVAMPIRE_ACTOR_GARLIC,	        231.000000f,    164.000000f,    16.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        156.000000f,    266.000000f,    320.000000f,    266.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        322.000031f,    267.000000f,    425.000031f,    179.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        56.999989f,     214.000000f,    158.000000f,    267.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        62.999985f,     122.000008f,    194.000000f,    160.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        282.999969f,    178.000000f,    418.999969f,    139.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        187.000000f,    178.000000f,    196.000000f,    160.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        284.000000f,    198.000000f,    282.000000f,    179.000000f,    0.000000f},
};

////// Level 5
static Vampire_LevelInfo_t Vampire_Level5[] =
{
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    349.000000f,    51.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        360.154053f,    150.458527f,    52.000000f,	    12.000000f,	    -5.102170f},
    {eVAMPIRE_ACTOR_GIRL,	        85.000000f,	    38.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_WHEEL,	        126.000000f,    41.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_WHEEL,	        162.000000f,    43.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_WHEEL,	        198.000000f,    45.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_WHEEL,	        234.000000f,    46.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_CLERGYMAN,	    272.000000f,    47.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        58.000080f,     221.000015f,    332.000122f,    253.000015f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        23.999996f,     151.000000f,    57.000000f,     221.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        90.999969f,     170.000000f,    354.999969f,    153.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        55.999954f,     76.000000f,     392.999969f,    93.000000f,     0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        284.000000f,    198.000000f,    282.000000f,    179.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        441.000000f,    127.999992f,    462.000000f,    79.999992f,     0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        416.000000f,    148.000000f,    440.000000f,    129.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        413.000000f,    238.000000f,    465.000000f,    201.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        401.000000f,    283.000000f,    414.000000f,    237.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        367.000000f,    300.000000f,    401.000000f,    282.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        333.000000f,    289.000000f,    333.000000f,    254.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        332.999969f,    289.000000f,    367.999969f,    300.000000f,    0.000000f},
};


////// Level 6
static Vampire_LevelInfo_t Vampire_Level6[] =
{
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    49.000000f,	    37.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_HUMAN,	        409.000000f,    208.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_CLERGYMAN,	    281.000000f,    208.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        189.000000f,    48.000000f,	    128.000000f,    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        342.000000f,    46.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_ROCK,	        327.000000f,    107.000000f,    64.000000f,	    32.000000f,	    90.000000f},
    {eVAMPIRE_ACTOR_BOX_STEP,	    210.000000f,    87.000000f,	    100.000000f,    45.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        51.000000f,	    77.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        191.000076f,    249.000000f,    453.000122f,    249.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        66.999992f,     161.000015f,    191.000000f,    250.000015f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        2.999990f,      160.000000f,    65.999992f,     161.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        453.000000f,    251.000000f,    461.000000f,    212.000015f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        461.000000f,    211.000000f,    479.000000f,    211.000000f,    0.000000f},
};
static Vampire_ConstraintInfo_t Vampire_Constaint6[] =
{
    {3, 6},
    {4, 5},
};

////// Level 7
static Vampire_LevelInfo_t Vampire_Level7[] =
{
    {eVAMPIRE_ACTOR_GIRL,	        185.000000f,    261.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        171.000000f,    80.000000f,	    128.000000f,    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    264.000000f,    133.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BADVAMPIRE,	    168.000000f,    132.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        143.000000f,    219.000000f,    48.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_ROCK,	        148.000000f,    234.000000f,    36.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        21.000000f,     170.000015f,    72.000000f,     268.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        2.999990f,      160.000000f,    65.999992f,     161.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        411.000000f,    259.000000f,    444.000000f,    152.000031f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        71.999992f,     270.000000f,    191.000000f,    302.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        191.999985f,    303.000000f,    286.000000f,    302.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        411.000000f,    261.000000f,    284.000000f,    302.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        -203.000000f,   -52.000000f,    -202.000000f,   -52.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        249.999985f,    168.000015f,    357.000000f,    203.000015f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        124.999992f,    219.000015f,    248.999985f,    167.000015f,    0.000000f},
};

static Vampire_ConstraintInfo_t Vampire_Constaint7[] =
{
    {1, 2},
    {4, 5},
    {1, 3},
};


////// Level 8
static Vampire_LevelInfo_t Vampire_Level8[] =
{
    {eVAMPIRE_ACTOR_GARLIC,	        176.000000f,    187.000000f,    16.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        231.000000f,    70.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    228.000000f,    31.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GIRL,	        348.000000f,    120.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_HUMAN,	        109.000000f,    120.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        68.000000f,	    70.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        306.000000f,    70.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        396.000000f,    70.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_CLERGYMAN,	    229.000000f,    125.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GARLIC,	        304.000000f,    184.000000f,    16.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        155.000000f,    70.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        20.000000f,     219.000015f,    37.000000f,     293.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        37.999989f,     293.000000f,    142.000000f,    311.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        233.000015f,    268.000000f,    144.000000f,    313.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        -203.000000f,   -52.000000f,    -202.000000f,   -52.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        269.000000f,    271.000000f,    357.000000f,    313.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        444.000000f,    295.000031f,    462.000000f,    218.000031f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        442.000000f,    295.000000f,    355.000000f,    313.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        268.000000f,    217.000000f,    268.000000f,    271.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        232.000000f,    216.000000f,    232.000000f,    270.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        267.000000f,    218.000000f,    231.999985f,    218.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        269.000000f,    166.000000f,    227.000000f,    166.000000f,    0.000000f},
};
static Vampire_ConstraintInfo_t Vampire_Constaint8[] =
{
    {7, 3},
    {6, 3},
    {10, 4},
    {5, 4},
};


////// Level 9
static Vampire_LevelInfo_t Vampire_Level9[] =
{
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    83.000000f,	    58.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_HUMAN,	        218.000000f,    165.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        117.000000f,    73.000000f,	    32.000000f,	    32.000000f,	    10.437500f},
    {eVAMPIRE_ACTOR_CLERGYMAN,	    150.000000f,    73.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        114.000000f,    207.000000f,    256.000000f,    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_ROCK,	        125.000000f,    175.000000f,    64.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_ROCK,	        289.000000f,    175.000000f,    64.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        18.000000f,     213.000015f,    37.000000f,     310.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        36.999962f,     309.000031f,    400.000000f,    289.000031f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        -203.000000f,   -52.000000f,    -202.000000f,   -52.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        446.000000f,    253.000076f,    463.000000f,    74.000069f,     0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        445.000000f,    252.999985f,    400.000000f,    290.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        54.999969f,     88.999901f,     374.000000f,    159.999893f,    0.000000f},
};



////// Level 10
static Vampire_LevelInfo_t Vampire_Level10[] =
{
    {eVAMPIRE_ACTOR_GIRL,	        405.000000f,    130.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    70.000000f,	    130.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BADVAMPIRE,	    313.000000f,    130.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_CLERGYMAN,	    189.000000f,    130.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        32.000000f,	    45.000000f,     32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        117.000000f,    45.000000f,     32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        149.000000f,    45.000000f,     32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        437.000000f,    45.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        235.000000f,    45.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        286.000000f,    45.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        343.000000f,    45.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        375.000000f,    45.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GARLIC,	        78.000000f,	    207.000000f,    16.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GARLIC,	        35.000000f,     157.000000f,    16.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GARLIC,	        129.000000f,    192.000000f,    16.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        55.000000f,     214.000015f,    73.000000f,     284.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        410.000000f,    284.000000f,    427.000000f,    213.000015f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        72.999992f,     283.000000f,    142.000000f,    301.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        411.000000f,    284.000000f,    347.000000f,    300.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        -203.000000f,   -52.000000f,    -202.000000f,   -52.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        141.999985f,    301.000000f,    248.999985f,    313.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        248.999985f,    313.000000f,    346.999969f,    300.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        38.000000f,     214.000000f,    54.000000f,    214.000000f,     0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        428.000000f,    214.000000f,    444.000000f,    214.000000f,    0.000000f},
};
static Vampire_ConstraintInfo_t Vampire_Constaint10[] =
{
    {7, 0},
    {11, 0},
    {10, 2},
    {9, 2},
    {8, 3},
    {6, 3},
    {5, 1},
    {4, 1},
};

////// Level 11
static Vampire_LevelInfo_t Vampire_Level11[] =
{
    {eVAMPIRE_ACTOR_HUMAN,	        109.000000f,    206.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    228.000000f,    155.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        176.000000f,    80.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        371.000000f,    80.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GARLIC,	        184.000000f,    208.000000f,    16.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GARLIC,	        183.000000f,    174.000000f,    16.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GIRL,	        170.000000f,    37.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GIRL,	        318.000000f,    218.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        302.000000f,    80.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_WHEEL,	        361.000000f,    32.000000f,	    54.000000f,	    54.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        150.000000f,    201.000000f,    16.000000f,	    64.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        17.000000f,     159.000015f,    36.000000f,     284.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        409.000031f,    281.999969f,    462.000031f,    178.000031f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        37.999989f,     284.000000f,    88.000000f,     310.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        408.000031f,    283.999969f,    244.000031f,    310.999969f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        -203.000000f,   -52.000000f,    -202.000000f,    -52.000000f,   0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        87.999992f,     311.000000f,    243.999985f,    311.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        107.000000f,    248.000000f,    141.999985f,    248.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        2.000000f,      160.000000f,    18.000000f,     160.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        462.000000f,    178.000000f,    478.000000f,    178.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        230.000000f,    195.000000f,    265.000000f,    195.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        320.000000f,    258.000000f,    355.000000f,    258.000000f,    0.000000f},
};
static Vampire_ConstraintInfo_t Vampire_Constaint11[] =
{
    {8, 9},
};

////// Level 12
static Vampire_LevelInfo_t Vampire_Level12[] =
{
    {eVAMPIRE_ACTOR_GIRL,	        71.000000f,	    170.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    387.000000f,    83.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        375.000000f,    124.000000f,    64.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_ROCK,	        135.000000f,    40.000000f,	    64.000000f,	    16.000000f,	    90.000000f},
    {eVAMPIRE_ACTOR_GARLIC,	        281.000000f,    192.000000f,    16.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_HUMAN,	        267.000000f,    83.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        255.000000f,    124.000000f,    64.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        40.000000f,	    108.000000f,    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        115.000000f,    108.000000f,    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        151.000000f,    84.000000f,	    32.000000f,	    16.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        179.000000f,    227.000015f,    179.000000f,    265.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        419.000000f,    191.999985f,    446.000000f,    126.000023f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        419.000061f,    193.999985f,    181.000046f,    227.999985f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        -203.000000f,   -52.000000f,    -202.000000f,   -52.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        150.999985f,    266.000000f,    179.999985f,    266.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        127.000000f,    231.000000f,    151.000000f,    231.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        446.000000f,    125.000000f,    462.000000f,    125.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        320.000000f,    124.000000f,    374.999969f,    124.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        151.000000f,    230.000015f,    151.000000f,    268.000000f,    0.000000f},
};
static Vampire_ConstraintInfo_t Vampire_Constaint12[] =
{
    {8, 0},
    {7, 0},
};



////// Level 13
static Vampire_LevelInfo_t Vampire_Level13[] =
{
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    232.000000f,    11.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        220.000000f,    53.000000f,	    64.000000f,	    8.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_HUMAN,	        46.000000f,	    56.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        221.000000f,    105.000000f,    64.000000f,	    8.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        91.000000f,	    80.000000f,	    32.000000f,	    32.000000f,	    20.924500f},
    {eVAMPIRE_ACTOR_GIRL,	        388.000000f,    75.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        355.000000f,    96.000000f,	    32.000000f,	    32.000000f,	    -18.970400f},
    {eVAMPIRE_ACTOR_CLERGYMAN,	    232.000000f,    63.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        134.238815f,    212.510101f,    128.480957f,    8.000000f,	    19.025600f},
    {eVAMPIRE_ACTOR_BOX,	        152.238815f,    161.510101f,    120.000000f,    8.000000f,	    19.025600f},
    {eVAMPIRE_ACTOR_BOX,	        268.238800f,    222.510101f,    90.000000f,	    8.000000f,	    -17.644600f},
    {eVAMPIRE_ACTOR_BOX,	        274.507721f,    165.467926f,    60.000000f,	    8.000000f,	    -24.915100f},
    {eVAMPIRE_ACTOR_SEGEMNT,        101.000000f,    298.999939f,    155.000015f,    136.000046f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        393.000031f,    274.000000f,    278.000031f,    299.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        -203.000000f,   -52.000000f,    -202.000000f,   -52.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        101.999962f,    300.000000f,    204.999954f,    300.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        242.000000f,    246.000000f,    261.000000f,    246.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        393.000000f,    274.999969f,    331.999969f,    149.000046f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        154.999985f,    134.999985f,    42.999950f,     91.000008f,     0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        279.000000f,    300.000000f,    261.000000f,    246.000015f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        431.999969f,    110.000023f,    331.999939f,    148.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        242.000000f,    246.000031f,    206.999985f,    299.000000f,    0.000000f},

};



////// Level 14
static Vampire_LevelInfo_t Vampire_Level14[] =
{
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    86.000000f,	    32.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_HUMAN,	        80.000000f,	    259.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        225.000000f,    269.000000f,    48.000000f,	    12.000000f,	    10.885500f},
    {eVAMPIRE_ACTOR_BOX,	        125.000000f,    59.000000f,	    16.000000f,	    16.000000f,	    14.036200f},
    {eVAMPIRE_ACTOR_GIRL,	        406.000000f,    38.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        324.000000f,    93.000000f,	    64.000000f,	    12.000000f,	    -6.842770f},
    {eVAMPIRE_ACTOR_CLERGYMAN,	    331.000000f,    49.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        226.000000f,    205.000000f,    48.000000f,	    12.000000f,	    -17.102699f},
    {eVAMPIRE_ACTOR_BOX,	        225.000000f,    139.000000f,    48.000000f,	    12.000000f,	    10.885500f},
    {eVAMPIRE_ACTOR_BOX,	        395.000000f,    66.000000f,	    16.000000f,	    16.000000f,	    -6.911230f},
    {eVAMPIRE_ACTOR_BOX,	        95.000000f,    124.000000f,    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        171.000000f,    124.000000f,    32.000000f,	    32.000000f,     0.000000f},
    {eVAMPIRE_ACTOR_GIRL,	        130.000000f,    188.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        318.000000f,    79.000000f,	    16.000000f,	    16.000000f,	    -6.911230f},
    {eVAMPIRE_ACTOR_SEGEMNT,        44.000000f,     277.999969f,    10.999990f,     221.000015f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        455.000031f,    276.000000f,    417.000031f,    302.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        -203.000000f,   -52.000000f,    -202.000000f,   -52.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        90.999969f,     300.000000f,    168.999969f,    300.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        339.000000f,    301.000000f,    417.000000f,    301.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        454.000000f,    275.000000f,    453.000000f,    198.000031f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        221.999969f,    97.999992f,     80.999939f,     71.000008f,     0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        338.000000f,    301.000000f,    276.999969f,    274.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        453.000000f,    80.000000f,     391.999969f,    89.000000f,     0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        222.000000f,    265.000031f,    170.999985f,    299.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        319.000000f,    97.000000f,     276.999969f,    106.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        91.000000f,     301.000000f,    45.999981f,     282.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        277.000000f,    211.999985f,    276.000000f,    107.000038f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        222.000000f,    143.000000f,    222.000000f,    98.000023f,     0.000000f},
};
static Vampire_ConstraintInfo_t Vampire_Constaint14[] =
{
    {11, 12},
    {10, 12},
};


////// Level 15
static Vampire_LevelInfo_t Vampire_Level15[] =
{
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    128.000000f,    117.000000f,    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        161.000000f,    155.000000f,    16.000000f,	    16.000000f,	    32.275600f},
    {eVAMPIRE_ACTOR_HUMAN,	        417.000000f,    78.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_CLERGYMAN,	    72.000000f,	    77.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        407.000000f,    114.000000f,    16.000000f,	    16.000000f,	    -21.447701f},
    {eVAMPIRE_ACTOR_BOX,	        172.000000f,    23.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        237.000000f,    23.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_CLERGYMAN,	    275.000000f,    68.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GIRL,	        15.000000f,	    39.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	        102.000000f,    116.000000f,    16.000000f,	    16.000000f,	    32.275600f},
    {eVAMPIRE_ACTOR_BOX,	        49.000000f,	    79.000000f,	    16.000000f,	    16.000000f,	    32.275600f},
    {eVAMPIRE_ACTOR_WHEEL,	        190.000000f,    52.000000f,	    70.000000f,	    70.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        185.999985f,    185.999954f,    0.999940f,      62.000031f,     0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        462.000031f,    276.000000f,    417.000031f,    304.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        -203.000000f,   -52.000000f,    -202.000000f,   -52.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        282.000000f,    108.000000f,    308.000000f,    108.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        170.000000f,    311.000000f,    326.000000f,    311.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        18.999990f,     285.000000f,    17.999990f,     249.000015f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        418.000000f,    305.000000f,    343.999969f,    292.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        328.000000f,    311.000000f,    275.999969f,    267.000031f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        344.000000f,    290.999969f,    276.999969f,    248.999954f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        213.000000f,    267.000031f,    168.999985f,    311.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        469.000031f,    107.999969f,    311.999939f,    186.999969f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        65.000000f,     303.000000f,    19.999981f,     284.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        282.000000f,    134.000000f,    282.000000f,    108.000008f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        184.000031f,    188.999969f,    16.999941f,     249.999969f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        452.000000f,    246.999985f,    312.999939f,    187.000015f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        214.000015f,    249.999985f,    143.999969f,    292.999969f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        144.000015f,    292.000000f,    64.999969f,     302.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,        462.000000f,    274.999969f,    452.000000f,    246.999969f,    0.000000f},
};
static Vampire_ConstraintInfo_t Vampire_Constaint15[] =
{
    {6, 11},
    {5, 11},
};

////// Level 16
static Vampire_LevelInfo_t Vampire_Level16[] =
{
    {eVAMPIRE_ACTOR_GOODVAMPIRE,    400.000000f,    50.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_HUMAN,	    119.000000f,        87.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	    382.000000f,        77.000000f,	    16.000000f,	    16.000000f,	    -8.130100f},
    {eVAMPIRE_ACTOR_BOX,	    92.000000f,	        43.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	    157.000000f,	    43.000000f,	    32.000000f,	    32.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_GIRL,	    13.000000f,	        83.000000f,	    40.000000f,	    40.000000f,	    0.000000f},
    {eVAMPIRE_ACTOR_BOX,	    50.000000f,	        119.000000f,    16.000000f,	    16.000000f,	    23.428699f},
    {eVAMPIRE_ACTOR_CONCAVEWHEEL,   143.000000f,    133.000000f,    128.000000f,    128.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,    103.999992f,        157.999985f,    11.999970f,     121.000008f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,    466.000000f,        151.342667f,    417.000000f,    304.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,    -203.000000f,       -52.000000f,    -202.000000f,   -52.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,    417.999969f,        305.000000f,    257.999939f,    281.000000f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,    480.000031f,        79.999992f,     311.999939f,    111.999992f,    0.000000f},
    {eVAMPIRE_ACTOR_SEGEMNT,    464.000000f,        151.999985f,    446.000000f,    108.000008f,    0.000000f},
};
static Vampire_ConstraintInfo_t Vampire_Constaint16[] =
{
    {4, 1},
    {3, 1},
};


static Vampire_AllLevels Vampire_Levels[] =
{
	{Vampire_Level1, sizeof(Vampire_Level1)/sizeof(Vampire_LevelInfo_t), NULL, 0 },
	{Vampire_Level2, sizeof(Vampire_Level2)/sizeof(Vampire_LevelInfo_t), Vampire_Constaint2,  sizeof(Vampire_Constaint2)/sizeof(Vampire_ConstraintInfo_t)},
	{Vampire_Level3, sizeof(Vampire_Level3)/sizeof(Vampire_LevelInfo_t), Vampire_Constaint3,  sizeof(Vampire_Constaint3)/sizeof(Vampire_ConstraintInfo_t) },
	{Vampire_Level4, sizeof(Vampire_Level4)/sizeof(Vampire_LevelInfo_t), NULL, 0 },
    {Vampire_Level5, sizeof(Vampire_Level5)/sizeof(Vampire_LevelInfo_t), NULL, 0 },
    {Vampire_Level6, sizeof(Vampire_Level6)/sizeof(Vampire_LevelInfo_t), Vampire_Constaint6,  sizeof(Vampire_Constaint6)/sizeof(Vampire_ConstraintInfo_t) },
    {Vampire_Level7, sizeof(Vampire_Level7)/sizeof(Vampire_LevelInfo_t), Vampire_Constaint7,  sizeof(Vampire_Constaint7)/sizeof(Vampire_ConstraintInfo_t) },
    {Vampire_Level8, sizeof(Vampire_Level8)/sizeof(Vampire_LevelInfo_t), Vampire_Constaint8,  sizeof(Vampire_Constaint8)/sizeof(Vampire_ConstraintInfo_t) },
    {Vampire_Level9, sizeof(Vampire_Level9)/sizeof(Vampire_LevelInfo_t), NULL, 0 },
    {Vampire_Level10, sizeof(Vampire_Level10)/sizeof(Vampire_LevelInfo_t), Vampire_Constaint10,  sizeof(Vampire_Constaint10)/sizeof(Vampire_ConstraintInfo_t) },
    {Vampire_Level11, sizeof(Vampire_Level11)/sizeof(Vampire_LevelInfo_t), Vampire_Constaint11,  sizeof(Vampire_Constaint11)/sizeof(Vampire_ConstraintInfo_t) },
    {Vampire_Level12, sizeof(Vampire_Level12)/sizeof(Vampire_LevelInfo_t), Vampire_Constaint12,  sizeof(Vampire_Constaint12)/sizeof(Vampire_ConstraintInfo_t) },
    {Vampire_Level13, sizeof(Vampire_Level13)/sizeof(Vampire_LevelInfo_t), NULL, 0 },
    {Vampire_Level14, sizeof(Vampire_Level14)/sizeof(Vampire_LevelInfo_t), Vampire_Constaint14,  sizeof(Vampire_Constaint14)/sizeof(Vampire_ConstraintInfo_t) },
    {Vampire_Level15, sizeof(Vampire_Level15)/sizeof(Vampire_LevelInfo_t), Vampire_Constaint15,  sizeof(Vampire_Constaint15)/sizeof(Vampire_ConstraintInfo_t) },
    {Vampire_Level16, sizeof(Vampire_Level16)/sizeof(Vampire_LevelInfo_t), Vampire_Constaint16,  sizeof(Vampire_Constaint16)/sizeof(Vampire_ConstraintInfo_t) },

};



/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/

#endif //__MMI_VAMPIREGAME_GAMESCENE_MAP__
