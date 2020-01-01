#ifndef RVC_HEADER_H
#define RVC_HEADER_H

#define RVC_SLICE_MORE_DATA       0
#define RVC_SLICE_SOP             2                       //!< Start Of Picture
#define RVC_SLICE_SOSL            3                       //!< Start Of Slice
#define RVC_SLICE_EOP             4     // end of picture
#define RVC_SLICE_EOSL            5                       //!< End Of Sequence

int32 decode_rvc_i_slice(RVC_HANDLE *hp, struct RVDecoder *t, struct CRealVideoBs *pBitstream,
                         int32 mbstart, uint8 QP, uint32 *ulSkipModesLeft,
                         uint32 totalMBs,
                         int32 iRatio0, int32 iRatio1, 
                         RV_Boolean bFirstSlice
                         );
int32 ATTR_INST16 decode_rvc_pb_slice(RVC_HANDLE *hp, struct RVDecoder *t, struct CRealVideoBs *pBitstream,
                         int32 mbstart, uint8 QP, uint32 *ulSkipModesLeft,
                         uint32 totalMBs,
                         int32 iRatio0, int32 iRatio1, 
                         RV_Boolean bFirstSlice
                         );
#endif
