#ifndef PARSETCOMMON_H
#define PARSETCOMMON_H

#define MAXIMUMPARSETRBSPSIZE   1500
#define MAXIMUMPARSETNALUSIZE   1500

// changed from 60000 to 6
#define SIZEslice_group_id      (sizeof (int) * 6)    // should be sufficient for HUGE pictures, need one int per MB in a picture

#ifdef AVC_USE_MIN_SPS_PPS
#define MAXSPS  4
#define MAXPPS  128//128
#else
#define MAXSPS  32
#define MAXPPS  256//128
#endif

#define MAXIMUMVALUEOFcpb_cnt   32
typedef struct
{
    unsigned  cpb_cnt;                                        // ue(v)
    unsigned  bit_rate_scale;                                 // u(4)
    unsigned  cpb_size_scale;                                 // u(4)
    unsigned  bit_rate_value [MAXIMUMVALUEOFcpb_cnt];         // ue(v)
    unsigned  cpb_size_value[MAXIMUMVALUEOFcpb_cnt];          // ue(v)
    unsigned  vbr_cbr_flag[MAXIMUMVALUEOFcpb_cnt];            // u(1)
    unsigned  initial_cpb_removal_delay_length_minus1;        // u(5)
    unsigned  cpb_removal_delay_length_minus1;                // u(5)
    unsigned  dpb_output_delay_length_minus1;                 // u(5)
    unsigned  time_offset_length;                             // u(5)
} hrd_parameters_t;


typedef struct
{
    uint1   aspect_ratio_info_present_flag;                 // u(1)
    uint8   aspect_ratio_idc;                               // u(8)
    uint16  sar_width;                                      // u(16)
    uint16  sar_height;                                     // u(16)
    uint1   overscan_info_present_flag;                     // u(1)
    uint1   overscan_appropriate_flag;                      // u(1)
    uint1   video_signal_type_present_flag;                 // u(1)
    uint3   video_format;                                   // u(3)
    uint1   video_full_range_flag;                          // u(1)
    uint1   colour_description_present_flag;                // u(1)
    uint8   colour_primaries;                               // u(8)
    uint8   transfer_characteristics;                       // u(8)
    uint8   matrix_coefficients;                            // u(8)
    uint1   chroma_location_info_present_flag;              // u(1)
    uint3   chroma_location_top_field;                      // ue(v)
    uint3   chroma_location_bot_field;                      // ue(v)
    uint1   timing_info_present_flag;                       // u(1)
    uint32  num_units_in_tick;                              // u(32)
    uint32  time_scale;                                     // u(32)
    uint1   fixed_frame_rate_flag;                          // u(1)
    uint1   nal_hrd_parameters_present_flag;                // u(1)
    hrd_parameters_t nal_hrd_parameters;                      // hrd_paramters_t
    uint1   vcl_hrd_parameters_present_flag;                // u(1)
    hrd_parameters_t vcl_hrd_parameters;                      // hrd_paramters_t
    // if ((nal_hrd_parameters_present_flag || (vcl_hrd_parameters_present_flag))
    uint1   low_delay_hrd_flag;                             // u(1)
    uint1   bitstream_restriction_flag;                     // u(1)
    uint1   motion_vectors_over_pic_boundaries_flag;        // u(1)
    uint5   max_bytes_per_pic_denom;                        // ue(v)
    uint5   max_bits_per_mb_denom;                          // ue(v)
    uint5   log2_max_mv_length_vertical;                    // ue(v)
    uint5   log2_max_mv_length_horizontal;                  // ue(v)
    unsigned  max_dec_frame_reordering;                       // ue(v)
    unsigned  max_dec_frame_buffering;                        // ue(v)
} vui_seq_parameters_t;


#define MAXnum_slice_groups_minus1  8
typedef struct
{
    uint1   Valid;                  // indicates the parameter set is valid
    uint8   pic_parameter_set_id;                           // ue(v)
    uint5   seq_parameter_set_id;                           // ue(v)
    uint1   pic_order_present_flag;                         // u(1)
    uint1   deblocking_filter_control_present_flag;         // u(1)
    uint1   redundant_pic_cnt_present_flag;                 // u(1)
    uint6   pic_init_qp;                                    // se(v)
    uint1   constrained_intra_pred_flag;                    // u(1)
    int5    chroma_qp_index_offset[2];                      // se(v)
    uint8   num_ref_idx_active[2];

#ifdef SUPPORT_AVCMP
    uint1   entropy_coding_mode_flag;                       // u(1)
    uint1   weighted_pred_flag;                             // u(1)
    uint2   weighted_bipred_idc;                            // u(2)
#endif

#ifdef SUPPORT_AVC2
    uint1   transform_8x8_mode_flag;                        // u(1)
    uint8   scalingList4x4[6][16];
    uint8   scalingList8x8[2][64];
#endif

#ifdef SUPPORT_AVCEP
    uint6   pic_init_qs;                                    // se(v)
    uint3   num_slice_groups_minus1;                        // ue(v)
    uint3   slice_group_map_type;                           // ue(v)
    uint32  run_length_minus1[MAXnum_slice_groups_minus1];  // ue(v)
    uint32  top_left[MAXnum_slice_groups_minus1];           // ue(v)
    uint32  bottom_right[MAXnum_slice_groups_minus1];       // ue(v)
    uint1   slice_group_change_direction_flag;              // u(1)
    uint32  slice_group_change_rate_minus1;                 // ue(v)
    uint32  num_slice_group_map_units_minus1;               // ue(v)
    uint3   slice_group_id[MAX_MBR];                        // complete MBAmap u(v)
#endif
} pic_parameter_set_rbsp_t;

#define MAX_NUM_REF_FRAMES_IN_PIC_ORDER_CNT_CYCLE  256
typedef struct
{
    uint5   log2_max_frame_num;                                         // ue(v)
    uint2   pic_order_cnt_type;                                         // ue(v)
    uint1   delta_pic_order_always_zero_flag;                           // u(1)
    uint1   frame_mbs_only_flag;                                        // u(1)
    uint5   log2_max_pic_order_cnt_lsb;                                 // ue(v)
    uint5   num_ref_frames;                                             // ue(v)
    uint1   gaps_in_frame_num_value_allowed_flag;                       // u(1)
    uint8   pic_width_in_mbs;                                           // ue(v)
    uint8   pic_height_in_map_units;                                    // ue(v)
    uint1   mb_adaptive_frame_field_flag;                               // u(1)
    uint1   direct_8x8_inference_flag;                                  // u(1)
    uint1   vui_parameters_present_flag;                                // u(1)
    int32   offset_for_non_ref_pic;                                     // se(v)
    int32   offset_for_top_to_bottom_field;                             // se(v)
    uint16  frame_cropping_rect_left_offset;                            // ue(v)
    uint16  frame_cropping_rect_right_offset;                           // ue(v)
    uint16  frame_cropping_rect_top_offset;                             // ue(v)
    uint16  frame_cropping_rect_bottom_offset;                          // ue(v)
    uint1   frame_cropping_flag;                                        // u(1)

    // syntax elements
    uint8  profile_idc;                                      // u(8)
    uint1  constrained_set0_flag;                            // u(1)
    uint1  constrained_set1_flag;                            // u(1)
    uint1  constrained_set2_flag;                            // u(1)
    uint8  level_idc;                                        // u(8)
    uint5  seq_parameter_set_id;                             // ue(v)
    uint8  num_ref_frames_in_pic_order_cnt_cycle;                            // ue(v)
    int32  offset_for_ref_frame[MAX_NUM_REF_FRAMES_IN_PIC_ORDER_CNT_CYCLE];   // se(v)
#ifdef SUPPORT_AVC2
    uint2  chroma_format_idc;                                           // ue(v)
    uint1  seq_scaling_maxtrix_present_flag;
    uint8  scalingList4x4[6][16];
    uint8  scalingList8x8[2][64];
#endif
    // temporarily remove vui
    //vui_seq_parameters_t vui_seq_parameters;                  // vui_seq_parameters_t

    uint1   Valid;                                                    // indicates the parameter set is valid
} seq_parameter_set_rbsp_t;

#endif
