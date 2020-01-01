#ifndef NALUCOMMON_H
#define NALUCOMMON_H

#define NALU_TYPE_SLICE   1
#define NALU_TYPE_DPA     2
#define NALU_TYPE_DPB     3
#define NALU_TYPE_DPC     4
#define NALU_TYPE_IDR     5
#define NALU_TYPE_SEI     6
#define NALU_TYPE_SPS     7
#define NALU_TYPE_PPS     8
#define NALU_TYPE_AUD     9
#define NALU_TYPE_EOSEQ   10
#define NALU_TYPE_EOSTREAM 11
#define NALU_TYPE_FILLER  12
// high profile
#define NALU_TYPE_SPS_EXT 13

#define NALU_PRIORITY_HIGHEST     3
#define NALU_PRIORITY_HIGH        2
#define NALU_PRIRITY_LOW          1
#define NALU_PRIORITY_DISPOSABLE  0


typedef struct
{
    uint8 nal_unit_type;            //! NALU_TYPE_xxxx
    uint2 nal_reference_idc;        //! NALU_PRIORITY_xxxx
    uint16 _align;
    //uint16 startcodeprefix_len;      //! 4 for parameter sets and first slice in picture, 3 for everything else (suggested)
    //uint32 max_size;            //! Nal Unit Buffer size
    //int forbidden_bit;            //! should be always FALSE
    uchar *buf;                    //! conjtains the first byte followed by the EBSP
    uint32 len;                 //! Length of the NAL unit (Excluding the start code, which does not belong to the NALU)
} NALU_t;


//NALU_t * AllocNALU(uchar *decbuf,int *size,int decbuf_size);
//void FreeNALU(NALU_t *n);

#endif
