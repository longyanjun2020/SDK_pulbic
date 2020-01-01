
/**
 * @file cps_public.h
 * NCC mms composer public encode macros
 *
 * Helper routines of the NCC mms composer
 */

#ifndef __CPS_PUBLIC_H__
#define __CPS_PUBLIC_H__

#include <ncc_types.h>
#include <nccmms_cps.h>
#include <cps_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/** smil document macros  */
#define CPS_SMIL_SIZE                                        0x2800    /**< smil document's size  */
#define CPS_MAX_TYPE_LEN                                     0x32    /**< max media type string's len  */
#define CPS_MAX_DURATION                                     0x1D4C0    /**<120 second  */

/**  smil content type define */
#define COMPOSER_SMIL_TYPE                                   "application/smil"    /**<smil type*/

/**media type*/
#define COMPOSER_MEDIAREF                                    0x0        /**<ref*/
#define COMPOSER_MEDIAVIDEO                                  0x1    /**<video*/
#define COMPOSER_MEDIAIMAGE                                  0x2    /**<image*/
#define COMPOSER_MEDIAAUDIO                                  0x3    /**<audio*/
#define COMPOSER_MEDIATEXT                                   0x4    /**<text*/

/*========================================================
 *      API defines
 *========================================================*/
/**
 * \param    pCpsNewMM    the point of the newmm
 * \return    <ul>
 *                <li> COMPOSER_SUCCESS     if success
 *                <li> COMPOSER_PARAMETER_ERROR if fail
 * \sa    ComposerInitSlideStruct()
 */
int32_t ComposerNewMMStruct(T_CPS_NewMM * pCpsNewMM);

/**
 * Judge whether to check MM Content
 * \param CPSHandle     composer handle
 * \param MediaType     pointer of a media type
 * \param MediaSize     size of media
 * \param warningmode       warningmode
 * \return <ul>
 *      <li> COMPOSER_SUCCESS       if success
 *      <li> COMPOSER_PARAMETER_ERROR   if invalid parameter
 *      <li> check result       other case
 *     </ul>
 */
int32_t ComposerCheckCreateMode(MMS_Handle CPSHandle, int8_t * MediaType,
                                uint32_t MediaSize, int32_t warningmode);

int32_t ComposerCheckRegion(const T_MMS_ScreenSize * pscreen,
                            const MMS_BasicRegion * ptxtregion);

int32_t ComposerCalImagRegionByTxtRegion(const T_MMS_ScreenSize * pscreen,
                                         const MMS_BasicRegion * ptxtregion,
                                         MMS_BasicRegion * pimgregion);

int32_t ComposerGetTxtAndImgRegion(const T_MMS_HANDLE * hMMS,
                                   MMS_BasicRegion * ptxtregion,
                                   MMS_BasicRegion * pimgregion,
                                   int32_t tactic);

int32_t ComposerProcessBasicAtt(T_MMS_Parser_BasicStructure * pFrom,
                                MMS_Composer_BasicStructure * pTo);

int32_t ComposerAmendRegion(T_MMS_HANDLE * hMMS);

int32_t ComposerProcessCurSlideText(T_MMS_HANDLE * CPSHandle,
                                    T_MMS_HANDLE * ParHandle,
                                    MMS_BasicRegion * txtregion);

int32_t ComposerProcessCurSlideAudio(T_MMS_HANDLE * CPSHandle,
                                     T_MMS_HANDLE * ParHandle);

int32_t ComposerProcessCurSlideImage(T_MMS_HANDLE * CPSHandle,
                                     T_MMS_HANDLE * ParHandle,
                                     MMS_BasicRegion * imgregion);

int32_t ComposerProcessCurSlideVideo(T_MMS_HANDLE * CPSHandle,
                                     T_MMS_HANDLE * ParHandle,
                                     MMS_BasicRegion * imgregion);

int32_t ComposerProcessCurMMAttach(T_MMS_HANDLE * CPSHandle,
                                   T_MMS_HANDLE * ParHandle);

int32_t ComposerProcessCurSlide(T_MMS_HANDLE * CPSHandle,
                                T_MMS_HANDLE * ParHandle,
                                MMS_BasicRegion * txtregion,
                                MMS_BasicRegion * imgregion);

int32_t ComposerFillStructWithCurMM(T_MMS_HANDLE * CPSHandle, uint8_t * pdu,
                                    int32_t length, MMS_BasicRegion * txtregion,
                                    int32_t tactic);


/* static function declare  */
void ComposerMakeFileName(int8_t * Buf, uint32_t index, int8_t *name, int8_t * Type);

/**
 * Init current mm's slide struct
 * \param    *pSlide    the point of the slide
 *
 * \return    NONE
 */
void ComposerInitSlideStruct(T_CPS_SlideStruct * pSlide);

/**
 * Copy the slide struct info from one to another
 * \param    *pFrom    the point of the source
 * \param    *pTo    the point of the
 * \return <ul>
 *      <li> None
 *     </ul>
 */
void ComposerCopySlideStruct(T_CPS_SlideStruct * pFrom,
                             T_CPS_SlideStruct * pTo);

/**
 * Judge whether  current slide is last or not
 * \param    *pCPSMM    the point of the current mms
 * \return    <ul>
 *                <li> TRUE     if success
 *                <li> FALSE        if failed
 *            </ul>
 */
int32_t ComposerCurIsTheLastSlide(T_CPS_NewMM * CPSMM);

/**
 * Free the media resource add in the new mms
 * \param    *pCpsNewMM    the point of the new mm
 * \param HandMMS       handle
 * \return <ul>
 *      <li> None
 *     </ul>
 */
void ComposerEmptyNewMMStruct(T_CPS_NewMM * pCpsNewMM);

/**
 * Fill the current mm's struct with current Ref
 * \param    *hMMS        the point of the current mms
 * \param    *Ref            the point of the Ref
 * \param    MediaType    Media Type
 * \param    index    the number of the slide
 * \return    <ul>
 *                <li>when successful,return#COMPOSER_SUCCESS
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_INPUT_PARAM_ERROR
 *                        <li>#COMPOSER_OVERSIZE
 *                        <li>#COMPOSER_UNKNOWN_ERROR
 *                        <li>#COMPOSER_DRMRESTRICTED
 *                    </ul>
 *            </ul>
 * \sa    NCCMms_par_smilParserEntry() ComposerHandleCurParVideo()    ComposerHandleCurParImage()    ComposerHandleCurParAudio()
 */
int32_t ComposerFillStructWithCurRef(T_MMS_HANDLE * hMMS,
                                     T_SMIL_RefStruct * Ref, uint8_t index,
                                     uint8_t typeindex);

/**
 * Create smil document with cur mm
 * \param    *hMMS        the handle of the hMMS
 * \return    <ul>
 *                <li> pointer of the pdu       if success
 *                <li> NULL             if failed
 *            </ul>
 */
int8_t *ComposerCreateSmil(T_MMS_HANDLE * hMMS);

/**
 * Check whether the mm's size is oversize or not
 * \param    *hMMS        the point of the mm
 * \param    *MeidaSize    the size of the media
 * \return    <ul>
 *                <li> #COMPOSER_MEDIASIZERIGHT if success
 *                <li>when fail,return
 *                    <ul>
 *                        <li>#COMPOSER_PARAMETER_ERROR
 *                        <li>#COMPOSER_OVERSIZE
 *                    </ul>
 *            </ul>
 */
int8_t ComposerCheckMMSize(T_MMS_HANDLE * hMMS, int32_t MediaSize);

/**
 * Combine resources into a link of structure
 * \param    *hMMS        the point of the mm
 * \return    <ul>
 *                <li> a structure      if success
 *                <li> #NULL            if failed
 *            </ul>
 */
T_MMS_Content_Union *ComposerRes2StructLink(T_MMS_HANDLE * hMMS);

/**
 * Check if error in the new mm struct
 * \param    *CpsNewMM        the point of the cur mm
 * \return    <ul>
 *                <li> #TRUE        if success
 *                <li> #FALSE       if failed
 *            </ul>
 */
int32_t ComposerCheckNewMMStruct(T_CPS_NewMM * CpsNewMM);

/**
 * Create smil head with cur mm
 * \param    *hMMS        the point of the cur mm
 * \param    *pSmilDoc    the point of the smil doc
 * \param    *pSmilLen    the length of the smil doc
 * \return    <ul>
 *                <li> #COMPOSER_CREATESMIL_SUCCESS if success
 *                <li> #NULL                if failed
 *            </ul>
 */
int8_t ComposerCreateSmilHead(T_MMS_HANDLE * hMMS, int8_t * pSmilDoc,
                              uint32_t * pSmilLen);

/**
 * Create smil body with cur mm
 * \param    *hMMS        the point of the cur mm
 * \param    *pSmilDoc    the point of the smil doc
 * \param    *pSmilLen    the length of the smil doc
 * \return    <ul>
 *                <li> #COMPOSER_CREATESMIL_SUCCESS if success
 *                <li> #NULL                if failed
 *            </ul>
 */
int8_t ComposerCreateSmilBody(T_MMS_HANDLE * hMMS, int8_t * pSmilDoc,
                              uint32_t * pSmilLen);

/**
 * Init the parse module
 * \param *pbasicstruct
 * \return <ul>
 *      <li> None
 *     </ul>
 */
void ComposerClearBasicAtt(MMS_Composer_BasicStructure * pbasicstruct);

#ifdef __cplusplus
}
#endif

#endif /* __CPS_PUBLIC_H__ */
