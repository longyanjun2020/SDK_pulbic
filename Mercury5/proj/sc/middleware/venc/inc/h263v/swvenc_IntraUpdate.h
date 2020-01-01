#ifndef _SWVENC_INTRA_UPDATE_H_
#define _SWVENC_INTRA_UPDATE_H_

#include "swvenc_deftypes.h"
#include "swvenc_udma_share.h"

// "in": For encoding the current frame.
// "out": The result of encoding current frame.
typedef struct {
    unsigned char intra:1;  // [in,out] in: This MB must be intra-coded; out: This MB is intra-coded.
    unsigned char motion:1; // [out] This MB is regarded as motion area.
    unsigned char inter_count;	// For FIR usage
} INTRA_UPDATE_MB_MAP;

typedef struct _IntraUpdateContext {
	// Input from caller
	int nTotalMb;
    int nWidthInMb;
        // Intra Refresh switches
	unsigned char bFIR;		// H.263 Forced Updating
	unsigned char bCIR;		// Cyclic intra updating
	unsigned char bAIR;		// Adaptive Intra-Refresh. Must be FALSE if bCIR is FALSE
	int nCIRDuration;       // Number of inter frame before performing row-by-row MB intra-updating.
	int nAIRCount;          // Number of MB's to be intra-updated in one inter frame

    // Private derived
    unsigned char bIntraUpdateEnabled;
        // Buffer
    INTRA_UPDATE_MB_MAP *pMbMap;	// Size: Mb-count.
	    // Intra update constants
	int nFIRThreshold;
	int nAIRThreshold;
	    // Internal counter
    int nCIRInterFrameCount;   // For CIF
	int nCIRIndex, nCIRMbY;  // MB index: The last-handled MB.
	int nAIRIndex;  // MB index: The last-handled MB.
} IntraUpdateContext;

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief
 *  Initialize IntraUpdate module.
 *  The caller must set following public members of IntraUpdateContext:
 *    bFIR, bAIR, bCIR, nAIRCount, nCIRDuration.
 *
 * \param[in] irctx IntraUpdateContext instance pointer.
 * \param[in] nWidthInMb Image width in the unit of MB.
 * \param[in] nHeightInMb Image height in the unit of MB.
 * \return E_TRUE if success.
 * \sa
 * \note
 * \warning
 */
Bool IntraUpdate_Init(IntraUpdateContext* irctx, int nWidthInMb, int nHeightInMb);

/*!
 * \brief
 *  For normal I- or P-frame: After encoding each MB, must call this API once to update status.
 *
 * \param[in] irctx IntraUpdateContext instance pointer.
 * \param[in] index The MB index inside one frame.
 * \param[in] is_inter 1 if INTER-coding; 0 if INTRA-coding.
 * \param[in] sad The SAD value when INTER-coding is used; when INTRA-coding, this value won't be used.
 * \return
 * \sa
 * \note
 * \warning
 */
void IntraUpdate_MbUpdate(IntraUpdateContext* irctx, int index, int is_inter, int SAD);

/*!
 * \brief
 *  For Dummy-P frame: After encoding each MB, must call this API once to update status.
 *
 * \param[in] irctx IntraUpdateContext instance pointer.
 * \param[in] index The MB index inside one frame.
 * \return
 * \sa
 * \note
 * \warning
 */
void IntraUpdate_MbUpdateDummy(IntraUpdateContext* irctx, int index);

/*!
 * \brief
 *  For normal P-frame: Each MB must call once to Check if forced-intra-coding was requested.
 *
 * \param[in] irctx IntraUpdateContext instance pointer.
 * \param[in] index The MB index inside one frame.
 * \return 1 if intra-coding is requested by the IntraUpdate algorithm(s).
 * \sa
 * \note
 * \warning
 */
int IntraUpdate_MBGet(IntraUpdateContext* irctx, int index);

/*!
 * \brief
 *  For each frame encoded (I-, P- or dummy-P-frame), must call this API once to form intra-coding MB map for the next frame.
 *
 * \param[in] irctx IntraUpdateContext instance pointer.
 * \param[out]
 * \return
 * \sa
 * \note
 * \warning
 */
void IntraUpdate_Frame(IntraUpdateContext* irctx, int is_intra_frame);

#ifdef __cplusplus
}
#endif


#endif //_SWVENC_INTRA_UPDATE_H_
