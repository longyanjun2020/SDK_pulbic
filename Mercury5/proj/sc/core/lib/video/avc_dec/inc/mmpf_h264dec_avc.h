
#ifndef _MMPF_VIDDEC_AVC_H_
#define _MMPF_VIDDEC_AVC_H_

#include "mmpf_typedef.h"
#include "avc_api.h"
#define MAXnum_ref_frames_in_pic_order_cnt_cycle	256
#define MAXnum_slice_groups_minus1					8

#define MAX_MB_WIDTH    (2304/16)
#define MAX_MB_HEIGHT   (1296/16)

#define MAX_SPS_NUM     1
#define MAX_PPS_NUM     1

// H264 Profile IDC
#define BASELINE_PROFILE        (66)
#define MAIN_PROFILE            (77)

// FREXT Profile IDC
#define FREXT_HP                (100)      ///< YUV 4:2:0/8 "High"
#define FREXT_Hi10P             (110)      ///< YUV 4:2:0/10 "High 10"
#define FREXT_Hi422             (122)      ///< YUV 4:2:2/10 "High 4:2:2"
#define FREXT_Hi444             (244)      ///< YUV 4:4:4/12 "High 4:4:4"

#define NALU_TYPE_SLICE    1
#define NALU_TYPE_DPA      2
#define NALU_TYPE_DPB      3
#define NALU_TYPE_DPC      4
#define NALU_TYPE_IDR      5
#define NALU_TYPE_SEI      6
#define NALU_TYPE_SPS      7
#define NALU_TYPE_PPS      8
#define NALU_TYPE_AUD      9
#define NALU_TYPE_EOSEQ    10
#define NALU_TYPE_EOSTREAM 11
#define NALU_TYPE_FILL     12

/**
 * @brief The structure for NAL unit
 */
typedef struct 
{
	MMP_LONG forbidden_bit;			///< forbidden bit
	MMP_LONG nal_unit_type;			///< NALU TYPE
	MMP_LONG nal_reference_idc;		///< NALU PRIORITY
	MMP_LONG payload;				///< the length of payload buffer
	MMP_UBYTE *payload_buf;	        ///< the payload buffer
} NALU_t;


/**
 * @brief The structure for Sequence Parameter Set
 */
typedef struct 
{   
    MMP_LONG	offset_for_non_ref_pic;				// se(v)
	MMP_LONG	offset_for_top_to_bottom_field;		// se(v)
	MMP_SHORT	offset_for_ref_frame[MAXnum_ref_frames_in_pic_order_cnt_cycle];   // se(v)
	
    MMP_USHORT	mb_width;							// ue(v)
	MMP_USHORT	mb_height;							// ue(v)

    MMP_SHORT	cropping_left;						// ue(v)
	MMP_SHORT	cropping_right;						// ue(v)
	MMP_SHORT	cropping_top;						// ue(v)
	MMP_SHORT	cropping_bottom;					// ue(v)

    MMP_BYTE	sps_id;                             // ue(v)
    MMP_BYTE	log2_max_frame_num;					// ue(v)
    MMP_BYTE	log2_max_poc_lsb;					// ue(v)
    MMP_BYTE	num_ref_frames_in_poc_cycle;		// ue(v)
    MMP_BYTE	num_ref_frames;						// ue(v)

    MMP_BYTE	profile_idc;						// u(8)
	MMP_BYTE	level_idc;							// u(8)
	MMP_BYTE	poc_type;
	MMP_BYTE	is_delta_pic_order_always_zero;		// u(1)
	MMP_BYTE	gaps_in_frame_num_value_allowed;	// u(1)
	MMP_BYTE	is_frame_mbs_only;					// u(1)
	MMP_BYTE	direct8x8_inference;				// u(1)
	MMP_BYTE	frame_cropping_flag;				// u(1)
    
    MMP_BYTE    chroma_format_idc;                  // ue(v)
    MMP_BYTE    residual_colour_transform_flag;     // u(1)
    MMP_BYTE    bit_depth_luma_minus8;              // ue(v)
    MMP_BYTE    bit_depth_chroma_minus8;            // ue(v)
    MMP_BYTE    qpprime_y_zero_transform_bypass_flag; // u(1)
    MMP_BYTE    seq_scaling_matrix_present_flag;    // u(1)
    MMP_BYTE    seq_scaling_list_present_flag[8];   // u(1)
    MMP_BYTE    scaling_list[8][64];
    MMP_BYTE    mb_adaptive_frame_field;            // u(1)
} Sequence_Parameter_Set_t;

/**
 * @brief The structure for Picture Parameter Set
 */
typedef struct 
{
	//FMO stuff
	MMP_SHORT		slice_group_change_rate;                    // ue(v)
	MMP_SHORT		num_slice_group_int_map_units;              // ue(v)
	//end of FMO

    MMP_SHORT		pps_id;                                     // ue(v)
	MMP_SHORT		num_slice_groups;                           // ue(v)
    MMP_SHORT		*slice_group_id;                            // complete MBAmap u(v)

    MMP_BYTE		sps_id;                                     // ue(v)
    MMP_BYTE		slice_group_map_type;                       // ue(v)
	MMP_BYTE		num_ref_idx_l0_active;                      // ue(v)
	MMP_BYTE		num_ref_idx_l1_active;                      // ue(v)
	
	MMP_BYTE		pic_init_qp;                                // se(v)
	MMP_BYTE		pic_init_qs;                                // se(v)
	MMP_BYTE		chroma_qp_index_offset;                     // se(v)

    MMP_BYTE		is_cabac_mode;                              // u(1)
	MMP_BYTE		is_pic_order_present;                       // u(1)
    MMP_BYTE		is_slice_group_change_direction;            // u(1)
	MMP_BYTE		is_deblocking_filter_control;               // u(1)
	MMP_BYTE		is_constrained_intra_pred;                  // u(1)
	MMP_BYTE		is_redundant_pic_cnt;                       // u(1)
	MMP_BYTE        is_weighted_pred;                           // u(1)
	MMP_BYTE        weighted_bipred_idc;                        // u(1)
	// P_V3
	MMP_BYTE        transform_8x8_mode_flag;                    // u(1)
	MMP_BYTE        pic_scaling_matrix_present_flag;            // u(1)
	MMP_BYTE        pic_scaling_list_present_flag[8];           // u(1)
	MMP_BYTE        scaling_list[8][64];
	MMP_BYTE        second_chroma_qp_index_offset;              // se(v)

    MMP_SHORT		run_length[MAXnum_slice_groups_minus1];     // ue(v)
	MMP_SHORT		top_left[MAXnum_slice_groups_minus1];       // ue(v)
	MMP_SHORT		bottom_right[MAXnum_slice_groups_minus1];   // ue(v)
} Picture_Parameter_Set_t;

/**
 * @brief The main structure in our AVC decoder
 */
typedef struct {
    NALU_t	     nal;
    MMP_ULONG    width;				        ///< image width for luma
	MMP_ULONG    height;				    ///< image height for luma
    MMP_UBYTE    mb_width;	                ///< image width in MBs
	MMP_UBYTE    mb_height;			        ///< image height in MBs
    MMP_LONG     num_ref_frames;		    ///< number of reference frames
	MMP_LONG     max_frame_num;             ///< maximun frame number
    //MMP_LONG     slice_num;                 ///< total slice numbers
	MMP_LONG     frame_rate;
   	MMP_LONG     num_units_in_tick;
	MMP_LONG     time_scale;
	MMP_ULONG    fixed_frame_rate_flag;
	MMP_ULONG    pic_struct_present_flag;
    Sequence_Parameter_Set_t	*sps;		///< point to sps_array[sps_id]
    /*
	 * brief bitstream
	 */
    MMP_ULONG *tail;
	MMP_ULONG *start;
    MMP_ULONG bufA;
    MMP_ULONG bufB;
    MMP_ULONG initpos;
    MMP_ULONG buf_length;
	MMP_ULONG bitpos;				        ///< to record the bit position in the register
    MMP_ULONG bits_count;
    MMP_ULONG eof;
    MMP_ULONG golomb_zeros;

    /*
	 * Header
	 */
	Sequence_Parameter_Set_t	sps_array[MAX_SPS_NUM];
	///< Sequence Parameter Set array, max size is 256
    
    MMP_ULONG     current_mem_addr;
    MMP_ULONG     end_mem_addr;
} AVC_DEC;

#endif //#ifndef _MMPF_VIDDEC_AVC_H_
