#ifndef CTX_H
#define CTX_H

#define NUM_BLOCK_TYPES 6

// IDX = 0~11, CTX276: 12
// I MB (8 ctx), P MB (10 ctx), B MB (12 ctx)
// CTX276: (1 ctx)
#define NUM_MB_TYPE_CTX       (12+1) // change to (12+2) due to dual operation
// IDX = 13~16
// I MB (0 ctx), P MB (3 ctx), B MB (4 ctx)
#define NUM_B8_TYPE_CTX       (4+1) //4 // change to 5 due to dual operation
// IDX = 17~30
// I MB (0 ctx), P/B MB (14 ctx)
#define NUM_MV_RES_CTX        14 //10
// IDX = 31~34
// I MB (4 ctx), P/B MB (4 ctx), fixed model for all types of slices
#define NUM_DELTA_QP_CTX       4
// IDX = 35~36
// I MB (2 ctx), P/B MB (2 ctx), fixed model for all types of slices
#define NUM_IPR_CTX    2
// IDX = 37~40
// I MB (4 ctx), P/B MB (4 ctx), fixed model for all types of slices
#define NUM_CIPR_CTX   4



// IDX = 290~295
// I MB (0 ctx), P/B MB (6 ctx)
#define NUM_REF_NO_CTX         6
// IDX = 296~298
// I MB (3 ctx), P/B MB (3 ctx)
#define NUM_MB_AFF_CTX         /*4*/ 3 // change to 4 due to dual operation
// IDX = 299~301
// I MB (3 ctx), P/B MB (3 ctx)
#define NUM_TRANSFORM_SIZE_CTX /*4*/ 3 // change to 4 due to dual operation

// IDX = 275~286
// I MB (12 ctx), P/B MB (12 ctx)
#define NUM_CBP_CTX   12 //4

// category: 0(4), 1(4), 2(4), 3(4), 4(4)
// I MB (4 ctx), P/B MB (4 ctx)
#define NUM_BCBP_CTX   4

// category: 0(5), 1(5), 2(5), 3(5), 4(5), 5(5)
// I MB (5+5+5+5+5+5=30 ctx), P/B MB (5+5+5+5+5+5 ctx)
#define NUM_ONE_CTX    6 //5  // change to 6 due to dual operation

// category: 0(5), 1(5), 2(5), 3(4), 4(5), 5(5)
// I MB (5+5+5+4+5+5=29 ctx), P/B MB (5+5+5+4+5+5 ctx)
#define NUM_ABS_CTX    6 //5  // change to 6 due to dual operation

// category: 0(15), 1(14), 2(15), 3(3), 4(14), 5(15)
// I MB (15+14+15+3+14+15=76 ctx), P/B MB (15+14+15+3+14+15 ctx)
#define NUM_MAP_CTX   16 //15 // change to 16 due to dual operation

// category: 0(15), 1(14), 2(15), 3(3), 4(14), 5(9)
// I MB (15+14+15+3+14+9=70 ctx), P/B MB (15+14+15+3+14+9 ctx)
#define NUM_LAST_CTX  16 //15 // change to 16 due to dual operation

// BCBP  category: 0(4):  41~44,  1(4): 115~118, 2(4): 185~188, 3(4):259~262,         4(4): 308~311
// ONE   category: 0(5):  45~49,  1(5): 119~123, 2(5): 189~193, 3(5):263~267,         4(5): 312~316, 5(5): 378~382
// ABS   category: 0(5):  50~54,  1(5): 124~128, 2(5): 194~198, 3(4):268~271,         4(5): 317~321, 5(5): 383~387
// MAP   category: 0(15): 55~69,  1(14):129~142, 2(15):199~213, 3(3+12):272~274(286), 4(14):322~335, 5(15):388~402
// LAST  category: 0(15): 70~84,  1(14):143~156, 2(15):214~228, 3(3+12):287~289(301), 4(14):336~349, 5(9): 403~411
// FMAP  category: 0(15): 85~99,  1(14):157~170, 2(15):229~243, 3(3):302~304,         4(14):350~363, 5(15):412~426
// FLAST category: 0(15):100~114, 1(14):171~184, 2(15):244~258, 3(3):305~307,         4(14):364~377, 5(9): 427~435


// field map 76

// field last 70

#define MB_TYPE_CTX_OFFSET 0
#define B8_TYPE_CTX_OFFSET (MB_TYPE_CTX_OFFSET+NUM_MB_TYPE_CTX)

#define MV_RES_CTX_OFFSET 0 //NUM_REF_NO_CTX

#define DELTA_QP_CTX_OFFSET 0
#define IPR_CTX_OFFSET  (DELTA_QP_CTX_OFFSET+NUM_DELTA_QP_CTX)
#define CIPR_CTX_OFFSET (IPR_CTX_OFFSET+NUM_IPR_CTX)

#define BCBP_CTX_OFFSET 0
#define ONE_CTX_OFFSET  (BCBP_CTX_OFFSET+NUM_BCBP_CTX)
#define ABS_CTX_OFFSET  (ONE_CTX_OFFSET+NUM_ONE_CTX)
#define MAP_CTX_OFFSET  (ABS_CTX_OFFSET+NUM_ABS_CTX)
#define LAST_CTX_OFFSET (MAP_CTX_OFFSET+NUM_MAP_CTX)
#define FLD_MAP_CTX_OFFSET  (LAST_CTX_OFFSET+NUM_LAST_CTX)
#define FLD_LAST_CTX_OFFSET (FLD_MAP_CTX_OFFSET+NUM_MAP_CTX)

#define CBP_CTX_OFFSET  (MAP_CTX_OFFSET+3)
#define REF_NO_CTX_OFFSET (LAST_CTX_OFFSET+3)
#define MB_AFF_CTX_OFFSET (REF_NO_CTX_OFFSET+NUM_REF_NO_CTX)
#define MB_TRANSFORM_SIZE_CTX_OFFSET (MB_AFF_CTX_OFFSET+NUM_MB_AFF_CTX)

#define USE_CTX_276

//! struct for context management
typedef struct
{
	unsigned char state;         // index into state-table CP
	unsigned char MPS;           // Least Probable Symbol 0/1 CP
} BiContextType;

typedef BiContextType * BiContextTypePtr;


typedef struct
{
    // motion contexts
//#ifdef USE_CTX_276
    //BiContextType mb_type_contexts [NUM_MB_TYPE_CTX+2];
    BiContextType mb_type_b8_type_contexts[NUM_MB_TYPE_CTX+NUM_B8_TYPE_CTX];
//#else
    //BiContextType mb_type_contexts [NUM_MB_TYPE_CTX];
//    BiContextType mb_type_b8_type_contexts[NUM_MB_TYPE_CTX+NUM_B8_TYPE_CTX];
//#endif
    //BiContextType b8_type_contexts [NUM_B8_TYPE_CTX];
    // 2erin, remove the following redundant variable
//#ifdef USE_CTX_276
    BiContextType _b8_type_contexts [2];
//#else
//    BiContextType _b8_type_contexts [4];
//#endif
#define ref_no_contexts one_abs_map_last_contexts[CHROMA_DC][REF_NO_CTX_OFFSET]
    //BiContextType ref_no_contexts  [NUM_REF_NO_CTX];
    BiContextType mv_res_contexts[NUM_MV_RES_CTX];
    //BiContextType refidx_mvres_contexts[NUM_REF_NO_CTX+NUM_MV_RES_CTX];
    //BiContextType delta_qp_contexts[NUM_DELTA_QP_CTX];
    // high profile
#define transform_size_contexts one_abs_map_last_contexts[CHROMA_DC][MB_TRANSFORM_SIZE_CTX_OFFSET]
    //BiContextType transform_size_contexts [NUM_TRANSFORM_SIZE_CTX];
    // mbaff
#define mb_aff_contexts one_abs_map_last_contexts[CHROMA_DC][MB_AFF_CTX_OFFSET]
    //BiContextType mb_aff_contexts  [NUM_MB_AFF_CTX];

    // texture contexts
    //BiContextType  ipr_contexts [NUM_IPR_CTX];
    //BiContextType  cipr_contexts[NUM_CIPR_CTX];
    //BiContextType  ipr_cipr_contexts[NUM_IPR_CTX+NUM_CIPR_CTX];
    //  0~3: delta_qp
    //  4~5: ipr
    //  6~9: cipr
    BiContextType  delta_qp_ipr_cipr_contexts[NUM_DELTA_QP_CTX+NUM_IPR_CTX+NUM_CIPR_CTX];
#define cbp_contexts one_abs_map_last_contexts[CHROMA_DC][CBP_CTX_OFFSET]
    //BiContextType  cbp_contexts [NUM_CBP_CTX];
    //BiContextType  bcbp_contexts[NUM_BLOCK_TYPES-1][NUM_BCBP_CTX]; // 8x8 does not have bit_cbp
    //BiContextType  map_contexts [NUM_BLOCK_TYPES][NUM_MAP_CTX];
    //BiContextType  last_contexts[NUM_BLOCK_TYPES][NUM_LAST_CTX];
    //BiContextType  one_contexts [NUM_BLOCK_TYPES][NUM_ONE_CTX];
    //BiContextType  abs_contexts [NUM_BLOCK_TYPES][NUM_ABS_CTX];
    //  0~15: frame significant
    // 16~31: frame last_significant
    // 32~47: field significant
    // 48~63: field last_significant
    //BiContextType  map_last_contexts[NUM_BLOCK_TYPES][(NUM_MAP_CTX+NUM_LAST_CTX)*2];
    //  0~ 5: one
    //  6~11: abs
    // 12~27: frame significant
    // 28~43: frame last_significant
    // 44~59: field significant
    // 60~75: field last_significant
    BiContextType  one_abs_map_last_contexts[NUM_BLOCK_TYPES][NUM_BCBP_CTX+NUM_ONE_CTX+NUM_ABS_CTX+(NUM_MAP_CTX+NUM_LAST_CTX)*2];
    // field coding
    //BiContextType  fld_map_contexts [NUM_BLOCK_TYPES][NUM_MAP_CTX];
    //BiContextType  fld_last_contexts[NUM_BLOCK_TYPES][NUM_LAST_CTX];

} MotionTextureInfoContexts;

#endif
