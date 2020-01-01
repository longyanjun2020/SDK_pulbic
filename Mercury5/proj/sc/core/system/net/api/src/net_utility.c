//
// net_utility.c: Utility functions used by network. Typically CGIs.
// used to be netapp2.c
//
#if 1
#include "ahc_menu.h"
#include "ahc_stream.h"
#include "ahc_display.h"    // CarDV - Aaron
#include "ahc_browser.h"
#include "ahc_modectl.h"
#include "MenuSetting.h"
#include "ledcontrol.h"

#include "amn_osal.h"
#include "amn_sysobjs.h"
#include "amn_event.h"
#include "rtkos_osl_ext.h"

#include "netapp.h"
#include "net_utility.h"
#include "net_serv.h"

#include "mmpf_scaler.h"
#include "mmpf_dsc.h"
#include "mmpf_exif.h"
#include "mmp_dsc_inc.h"
#include "mmpd_dsc.h"
#include "mmpf_fs_api.h"
#include "mmps_vidplay.h"
#endif

/*******************************************************************
 *
 * Miscellaneous for NETWORK
 *
 *******************************************************************/
//
extern MMP_ULONG m_ulJpegFileID;

#define MI_FILE_JPEG        0
#define MI_FILE_VIDEO       1
#define CUR_READ_INSIDE_STRUCT (1)

typedef struct MI_THUMBNAIL{
    char            file[64];
    int             type;
    int             width;
    int             height;
    int             bufsize;
    int             jsize;
    #define THUMBNAIL_FOUND(pmi) ((pmi)->jsize > 0)
#if CUR_READ_INSIDE_STRUCT
    int             cur_read;
#endif
    unsigned char   *jbuf;
} MI_THUMBNAIL;

#if CUR_READ_INSIDE_STRUCT
#define CUR_READ (pmi->cur_read)
#else
    int             cur_read;
#define CUR_READ cur_read
#endif
#define MAX_JPEG_SIZE       (70*1024)

#if 0
void ____Thumbnail_Generation____() {}
#endif

static int miDigThumbnailInJpg(char *filename, unsigned char **ppbuf, int bufsize, int *width, int *height);
static int miRebuildImageThumbnail(char *bJpgFileName, unsigned char *pBuf, int nBufSize, int *pnWidth, int *pnHeight);
static int miDigThumbnailInMov(char *filename, unsigned char **ppbuf, int bufsize, int *width, int *height);
static int miRebuildVideoThumbnail(char *movFileName, unsigned char *pbuf, int bufsize, int *width, int *height);

static int miIsValidThumbUiState(enum NS_MEDIA_TYPE ns_media_type)
{
    int ret;

    ret = ns_handle_event(NS_EVENT_QUERY_THUMB_STATE, (void*)ns_media_type);

    if (ret == NSE_CB_NOT_FOUND) {
        #ifdef NET_SYNC_PLAYBACK_MODE //move to later step
        if (ncgi_get_ui_state_id() != UI_NET_PLAYBACK_STATE) {
            printd(FG_YELLOW("Need to be in UI_NET_PLAYBACK_STATE")"\r\n");
            return 0;
        }
        #endif
    }
    else if (ANY_NS_ERR(ret)) {
        UartSendTrace("Invalid UI State err:%d\r\n", ret);
        return 0;
    }
    return 1;
}

//------------------------------------------------------------------------------
//  Function    : miOpenThumbnail
//  Description :
//------------------------------------------------------------------------------
/*
 * Give a filename and buf/size, return thumbnail of jpeg, width,height and size.
 * Caller has to free *pbuf by osal_free if *pbuf is NULL and bufize is 0.
 * @param[out] error error type of enum vhand_authen_spec_t
 */
MI_THUMBNAIL* miOpenThumbnail(char *filename, int *error)
{
    MI_THUMBNAIL        *pmi = NULL;
    char                *p = NULL;
    int                 (*DigThumbnailFunc)(char *filename, unsigned char **ppbuf, int bufsize, int *width, int *height) = NULL;
    int                 (*RebuildThumbnailFunc)(char *jpgFileName, unsigned char *pbuf, int bufsize, int *width, int *height) = NULL;
    enum NS_MEDIA_TYPE  media_type;
    int                 header_size = 0;

    *error = VHAND_ERR__ILLEGAL_URL_PARAM;

    pmi = NULL;

    // Check File Type
    p = strrchr(filename, '.');
    if (p == NULL) {
        return NULL;
    }

    pmi = (MI_THUMBNAIL*)osal_malloc(MAX_JPEG_SIZE);
    if (pmi == NULL) {
        *error = VHAND_ERR__INTERNAL;
        return NULL;
    }

    header_size = ALIGN32(sizeof(MI_THUMBNAIL));//align 32 is for hardware

    pmi->bufsize = MAX_JPEG_SIZE - header_size;
    pmi->jsize   = 0;
    pmi->jbuf    = (unsigned char*)pmi + header_size;

    strncpy(pmi->file, filename, sizeof(pmi->file));

    if (stricmp(p + 1, "JPG") == 0) {
        pmi->type = MI_FILE_JPEG;
        media_type = NS_MEDIA_JPEG;
        DigThumbnailFunc = miDigThumbnailInJpg;
        RebuildThumbnailFunc = miRebuildImageThumbnail;
    }
    else {
        pmi->type = MI_FILE_VIDEO;
        media_type = NS_MEDIA_MOV;
        DigThumbnailFunc = miDigThumbnailInMov;
        RebuildThumbnailFunc = miRebuildVideoThumbnail;
    }

    if(netapp_cap_lock(LOCK_CAPTURE, LOCK_CAPTURE_TIMEOUT) == 0)
    {
		if (DigThumbnailFunc) {
			pmi->jsize = DigThumbnailFunc(pmi->file, &pmi->jbuf, pmi->bufsize, &pmi->width, &pmi->height);
		}

		if (!THUMBNAIL_FOUND(pmi)) {
			// UI State Check
			if (miIsValidThumbUiState(media_type)) {
				// Create JPEG from JPEG
				pmi->jsize = RebuildThumbnailFunc(pmi->file, pmi->jbuf, pmi->bufsize, &pmi->width, &pmi->height);
			}
			else {
				*error = VHAND_ERR__OUT_OF_SERVICE;
			}
		}

		netapp_cap_lock(UNLOCK_CAPTURE, 0);
    }
    else
    {
    	*error = VHAND_ERR__INTERNAL;
    }


    CUR_READ = 0;

    if (THUMBNAIL_FOUND(pmi)) {
        *error = VHAND_OK__NO_CHECK_AUTH;
    }
    else {
        osal_free(pmi);
        pmi = NULL;
    }
    return pmi;
}

//------------------------------------------------------------------------------
//  Function    : miCloseThumbnail
//  Description :
//------------------------------------------------------------------------------
void miCloseThumbnail(MI_THUMBNAIL *handle)
{
    if (handle == NULL)
        return;
    osal_free(handle);
}

//------------------------------------------------------------------------------
//  Function    : _miRebuildImageThumbnail
//  Description :
//------------------------------------------------------------------------------
/* @brief Create a new JPEG thumbnail from JPEG File. It Decodes JPEG and Encodes into smaller JPEG.
 *
 * Give a filename and output a buffer of thumbnail
 *
 * @param[in] jpgFileName The file name of JPEG file.
 * @param[in,out] pbuf The output buffer of the JPEG.
 * @param[in] bufsize The size of the output JPEG buffer in bytes.
 * @param[out] width, height The resolution of the JPEG.
 * @param[in] type MI_FILE_JPEG Decode this JPEG file as source.
 *                 MI_FILE_VIDEO Use pbuf as JPEG source but use Video thumbnail resolution.
 * When pbuf is NULL return the thumbnail size and width/height
 * @warning This function requires extra buffer, a clean UI state for memory map, and fixed hardware image pipeline.
 *          Thus, it switches AHC mode inside! It also pauses streaming.
 *          If the project does not comply this behavior, it is better avoid using this function.
 *          e.g. The project need to get the thumbnail while video is previewing, then it does not comply.
 */
static int _miRebuildImageThumbnail(char *bJpgFileName, unsigned char *pbuf, int nBufSize, int *pnWidth, int *pnHeight, int type)
{
    MMP_DSC_JPEG_INFO   stJpegInfo;
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    MI_INFO             miInfo;
    unsigned short      w = 0, h = 0;
    AHC_MODE_ID         save;
    int                 ret = 0;

    if (miGetMediaInfo(bJpgFileName, &miInfo) == 0) {
        return 0;
    }

    save = AHC_GetAhcSysMode();
    if (AHC_MODE_IDLE != save) {
        ncam_set_streaming_mode(AHC_STREAM_PAUSE);
        AHC_SetMode(AHC_MODE_IDLE);
    }

    w = ALIGN_X(*pnWidth, 16);
    h = miInfo.height * (*pnWidth) / miInfo.width;
    h = ALIGN_X(h, 16);

    MEMSET0(&stJpegInfo);

    if (type == MI_FILE_JPEG)
    {
        strcpy(stJpegInfo.bJpegFileName, bJpgFileName);
        stJpegInfo.usJpegFileNameLength = strlen(bJpgFileName);
        stJpegInfo.ulJpegBufAddr        = 0;
        stJpegInfo.ulJpegBufSize        = 0;
        stJpegInfo.bDecVRThumb          = MMP_FALSE;
        stJpegInfo.bDecodeThumbnail     = MMP_TRUE;
        #if (DSC_SUPPORT_BASELINE_MP_FILE)
        stJpegInfo.bDecodeLargeThumb    = MMP_FALSE;
        #endif
        stJpegInfo.bValid               = MMP_FALSE;
        #if 1//(DSC_ENC_THUMBNAIL_OK == 0)
        stJpegInfo.bReEncodeThumb       = MMP_TRUE;
        #else
        stJpegInfo.bReEncodeThumb       = MMP_FALSE;
        #endif
    }
    else {
        #if 1
        UartSendTrace(BG_RED("VR Thumb ReBuild TBD")"\r\n");
        goto End_miCreateJPEGThumbnail;
        #else
        stJpegInfo.bDecodeThumbnail     = MMP_TRUE;
        #if (DSC_SUPPORT_BASELINE_MP_FILE)
        stJpegInfo.bDecodeLargeThumb    = MMP_FALSE;
        #endif
        stJpegInfo.bReEncodeThumb       = MMP_FALSE;

        if (!bufsize) {
            UartSendTrace(BG_RED("%s %d")"\r\n", __FUNCTION__, __LINE__);
            goto End_miCreateJPEGThumbnail;
        }
        else {
            UINT32 ulVRThumbJpgW = 0, ulVRThumbJpgH = 0;

            MMPS_3GPRECD_GetVRThumbResol(&ulVRThumbJpgW, &ulVRThumbJpgH);
            stJpegInfo.usJpegFileNameLength   = NULL;
            stJpegInfo.ulJpegBufAddr          = (MMP_ULONG)(pbuf);
            stJpegInfo.ulJpegBufSize          = bufsize;
            stJpegInfo.usPrimaryWidth         = ulVRThumbJpgW;
            stJpegInfo.usPrimaryHeight        = ulVRThumbJpgH;
        }
        #endif
    }

    eRetErr = MMPS_DSC_DecodeThumbnail(&stJpegInfo, w, h);

    if (eRetErr != MMP_ERR_NONE) {
        UartSendTrace(BG_RED("miRebuildImageThumbnail => DecodeThumbnail() Fail")"\r\n");
        goto End_miCreateJPEGThumbnail;
    }

    if (stJpegInfo.ulReEncodeThumbSize > nBufSize) {
        UartSendTrace(BG_RED("miRebuildImageThumbnail => JPEG Size [%d] Buf Size [%d]\r\n"),
               stJpegInfo.ulReEncodeThumbSize, nBufSize);
        goto End_miCreateJPEGThumbnail;
    }

    #if 0 // For debug
    MMPD_DSC_SetFileName("SD:\\001.jpg", strlen("SD:\\001.jpg"));
    MMPF_DSC_JpegDram2Card(stJpegInfo.ulReEncodeThumbAddr, stJpegInfo.ulReEncodeThumbSize, MMP_TRUE, MMP_TRUE);
    #endif

    if (pbuf && stJpegInfo.ulReEncodeThumbAddr) {
        memcpy(pbuf, (void*)stJpegInfo.ulReEncodeThumbAddr, stJpegInfo.ulReEncodeThumbSize);
        ret = (int)stJpegInfo.ulReEncodeThumbSize;
        UartSendTrace("miRebuildImageThumbnail Buf [%x] Thumb [%x] Sz [%d]\r\n",
                pbuf, stJpegInfo.ulReEncodeThumbAddr, ret);
    }

    if (pnWidth)
        *pnWidth  = w;
    if (pnHeight)
        *pnHeight = h;

End_miCreateJPEGThumbnail:

    eRetErr = MMPS_DSC_ExitThumbReEncodeMode(&stJpegInfo);

    if (AHC_MODE_IDLE != save) {
        AHC_SetMode(save);
        ncam_set_streaming_mode(AHC_STREAM_RESUME);
    }
    return ret;
}

//------------------------------------------------------------------------------
//  Function    : miRebuildImageThumbnail
//  Description :
//------------------------------------------------------------------------------
static int miRebuildImageThumbnail(char *bJpgFileName, unsigned char *pBuf, int nBufSize, int *pnWidth, int *pnHeight)
{
    *pnWidth  = NET_THUMBNAIL_WIDTH;
    *pnHeight = NET_THUMBNAIL_HEIGHT;
    return _miRebuildImageThumbnail(bJpgFileName, pBuf, nBufSize, pnWidth, pnHeight, MI_FILE_JPEG);
}

//------------------------------------------------------------------------------
//  Function    : miGetThumbnail
//  Description :
//------------------------------------------------------------------------------
/* @brief Claim the existing thumbnail data from handle.
 *
 * The handle must be successfully opened.
 *
 */
int miGetThumbnail(MI_THUMBNAIL *pmi, unsigned char **ppJpegBuf)
{
    if (!pmi)
        return 0;

    if (ppJpegBuf != NULL) {
        *ppJpegBuf = pmi->jbuf + CUR_READ;
        if ((pmi->jsize - CUR_READ) > 8192) {
            CUR_READ += 8192;
            return 8192;
        }
        return pmi->jsize - CUR_READ;
    }
    return pmi->jsize;
}

//------------------------------------------------------------------------------
//  Function    : miGetThumbnailSize
//  Description :
//------------------------------------------------------------------------------
int miGetThumbnailSize(MI_THUMBNAIL *handle)
{
    MI_THUMBNAIL *pmi;

    if (!handle)
        return 0;

    pmi = (MI_THUMBNAIL*)handle;
    return pmi->jsize;
}

//------------------------------------------------------------------------------
//  Function    : miGetThumbnailDimension
//  Description :
//------------------------------------------------------------------------------
int miGetThumbnailDimension(MI_THUMBNAIL *handle, int *pwidth, int *pheight)
{
    MI_THUMBNAIL *pmi;

    if (!handle)
        return 0;

    pmi = (MI_THUMBNAIL*)handle;
    *pwidth  = pmi->width;
    *pheight = pmi->height;
    return 1;
}

//------------------------------------------------------------------------------
//  Function    : miDigThumbnailInJpg
//  Description :
//------------------------------------------------------------------------------
/** @brief Extract/Dig JPEG thumbnail out from JPEG Image file
 *
 *  Extract JPEG thumbnail from JPEG file if there is any.
 *
 *  @note This function should be able to call without extra memory and could be used with any UI State.
 *  @warning This is not a thread-safe function because it uses common member variables in MMPF function.
 */
static int miDigThumbnailInJpg(char *bFileName, unsigned char **ppBuf, int nBufSize, int *pnWidth, int *pnHeight)
{
#if (DSC_ENC_THUMBNAIL_OK)
    MMP_ULONG           ulOffset = 0, ulSize = 0;
    unsigned int        ret = 0;
    MMP_ULONG           ulReadCnt = 0;
    MMP_DSC_JPEG_INFO   stJpegInfo;
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    unsigned char*      pBuf = *ppBuf;

    strcpy(stJpegInfo.bJpegFileName, bFileName);
    stJpegInfo.usJpegFileNameLength = strlen(bFileName);
    stJpegInfo.ulJpegBufAddr        = 0;
    stJpegInfo.ulJpegBufSize        = 0;
    stJpegInfo.bDecodeThumbnail     = MMP_TRUE;
    #if (DSC_SUPPORT_BASELINE_MP_FILE)
    stJpegInfo.bDecodeLargeThumb    = MMP_FALSE;
    #endif
    stJpegInfo.bValid               = MMP_FALSE;
    stJpegInfo.bReEncodeThumb       = MMP_FALSE;

    eRetErr = MMPS_DSC_GetJpegInfo(&stJpegInfo);
    if (eRetErr != MMP_ERR_NONE) {
        UartSendTrace("miDigThumbnailInJpg GetJpegInfo Fail\r\n");
        ulOffset = 0;
        ulSize   = 0;
        goto END_miDigJPEGThumbnail;
    }
    else {
        UartSendTrace("miDigThumbnailInJpg Thumb Ofst [%d] Sz [%d] WH [%d][%d]\r\n",
               stJpegInfo.ulThumbOffset, stJpegInfo.ulThumbSize,
               stJpegInfo.usThumbWidth, stJpegInfo.usThumbHeight);
    }

    ulOffset = stJpegInfo.ulThumbOffset;
    ulSize   = stJpegInfo.ulThumbSize;

    if (pnWidth != NULL && pnHeight != NULL) {
        *pnWidth  = (int)stJpegInfo.usThumbWidth;
        *pnHeight = (int)stJpegInfo.usThumbHeight;
    }

    if (pBuf) {

        if (nBufSize < ulSize) {
            UartSendTrace("miDigThumbnailInJpg Thumb Buffer Too Small [%d][%d]\r\n", nBufSize, ulSize);
            ret = -1;
            goto END_miDigJPEGThumbnail;
        }

        MMPS_DSC_AllocFileNameBuf();

        eRetErr = MMPD_DSC_OpenJpegFile(&stJpegInfo);

        if (eRetErr || m_ulJpegFileID == 0) {
            UartSendTrace("miDigThumbnailInJpg OpenJpegFile Fail [%x]\r\n", eRetErr);
            ret = -1;
            MMPS_DSC_FreeFileNameBuf();
            goto END_miDigJPEGThumbnail;
        }

        // Seek to thumbnail start position
        eRetErr = MMPF_FS_FSeek(m_ulJpegFileID, ulOffset, MMP_FS_FILE_BEGIN);

        // Flush all data in cache into physical memory
        osal_flush_dcache(pBuf,ulSize);

        eRetErr = MMPF_FS_FRead(m_ulJpegFileID, (unsigned char*)MsPA2VA(pBuf), ulSize, &ulReadCnt);

        if ((eRetErr != MMP_ERR_NONE) || (ulReadCnt != ulSize)) {
            UartSendTrace("[%s] miDigThumbnailInJpg Thumbnail Read Fail [%x] Buf [%x] Read [%d][%d]\n",
                    bFileName, eRetErr, pBuf, ulSize, ulReadCnt);
            ret = -1;
            MMPD_DSC_CloseJpegFile(&stJpegInfo);
            MMPS_DSC_FreeFileNameBuf();
            goto END_miDigJPEGThumbnail;
        }

        eRetErr = MMPD_DSC_CloseJpegFile(&stJpegInfo);

        MMPS_DSC_FreeFileNameBuf();

        // Make D-cache is invalid to
        // make sure CPU(Program) can read correct data that in physical memory.
        //osal_invalidate_dcache(((unsigned int)(pBuf)), ulSize);
    }

    // return thumbnail size
    ret = ulSize;

END_miDigJPEGThumbnail:
    return ret;
#else
    return 0;
#endif
}

//------------------------------------------------------------------------------
//  Function    : miDigThumbnailInMov
//  Description :
//------------------------------------------------------------------------------
static int miDigThumbnailInMov(char *bFileName, unsigned char **ppBuf, int nBufSize, int *pnWidth, int *pnHeight)
{
    MMP_ULONG jpg_size = 0;

    if (bFileName == NULL)
        return -1;

    // Not implemented, the existing video thumbnail resolution remains unknown.
    *pnWidth = 0;
    *pnHeight = 0;

    // Ignore return value because the size is always 0 when error.
    (void)MMPS_VIDPLAY_GetThumbnail(bFileName, strlen(bFileName), nBufSize, ppBuf, &jpg_size);
    UartSendTrace("VR jpg_size=%d\n",jpg_size);
    return jpg_size;
}

//------------------------------------------------------------------------------
//  Function    : miRebuildVideoThumbnail
//  Description : TBD
//------------------------------------------------------------------------------
/* @brief Create a new JPEG thumbnail from Video File. (Decode Video and Encode into JPEG)
 *
 * @param[in] movFileName The file name of the mov/mp4/3gp file.
 * @param[out] pbuf The output buffer of the JPEG.
 * @param[in] bufsize The size of the output JPEG buffer in bytes.
 * @param[out] width, height The resolution of the JPEG.
 * When pbuf is NULL return the thumbnail size and width/height
 * @warning This function requires extra buffer, a clean UI state for memory map, and fixed hardware image pipeline.
 *          Thus, it switches AHC mode inside! It also pauses streaming.
 *          If the project does not comply this behavior, it is better avoid using this function.
 *          e.g. The project need to get the thumbnail while video is previewing, then it does not comply.
 */
static int miRebuildVideoThumbnail(char *movFileName, unsigned char *pbuf, int bufsize, int *width, int *height)
{
    int         ret, size;
    MMP_UBYTE   *jpegBuf;
    AHC_MODE_ID save;
    MMP_UBYTE   ubLCDBKPowerOff = 0;            // CarDV - Aaron
    AHC_DISPLAY_OUTPUTPANEL     OutputDevice;   // CarDV - Aaron

    ret = -1;

    if (pbuf == NULL) {
        jpegBuf = (MMP_UBYTE*)osal_malloc(MAX_JPEG_SIZE);
        if (jpegBuf == NULL) {
            UartSendTrace(BG_RED("%s %d: ERROR at Memory Alloc\n"), __FUNCTION__, __LINE__);
            ret = -1;
            goto END_miGetVideoThumbnail;
        }
        size = MAX_JPEG_SIZE;
    }
    else {
        jpegBuf = pbuf;
        size = bufsize;
    }

    save = AHC_MODE_MAX;

    if (ncgi_get_ui_state_id() != UI_NET_PLAYBACK_STATE) {

        /// CarDV - Aaron +++
        // Read media files, LCD will be huaping.
        AHC_GetDisplayOutputDev(&OutputDevice);
        if(OutputDevice == AHC_DISPLAY_MAIN_LCD/*MMP_DISPLAY_SEL_MAIN_LCD*/)
        {
            ubLCDBKPowerOff = AHC_TRUE;
            LedCtrl_LcdBackLight(AHC_FALSE);
        }
        // CarDV - Aaron ---

        ncam_set_streaming_mode(AHC_STREAM_PAUSE);
        save = AHC_GetAhcSysMode();
        AHC_SetMode(AHC_MODE_IDLE);
    }
    // flush all data in cache into physical memory
    //osal_flush_dcache(jpegBuf,size);

    //ret = AHC_Thumb_GetJPEGFromVidFF((UINT8*)jpegBuf, size, movFileName, NET_THUMBNAIL_WIDTH, NET_THUMBNAIL_HEIGHT);
    if (save != AHC_MODE_MAX) {
        AHC_SetMode(save);
        ncam_set_streaming_mode(AHC_STREAM_RESUME);
    }

    if (ret < 0 || ret > size) {
        UartSendTrace(BG_RED("%s %d: ERROR File - %s\n"), __FUNCTION__, __LINE__, movFileName);
        ret = -1;
        goto END_miGetVideoThumbnail;
    }

    //osal_invalidate_dcache(((unsigned int)(jpegBuf) & ~(MEM_ALIGNMENT_HEAP - 1)) , size);

    *width  = NET_THUMBNAIL_WIDTH;
    *height = NET_THUMBNAIL_HEIGHT;

    if (pbuf == NULL) {
        if (jpegBuf)
            osal_free(jpegBuf);
    }

END_miGetVideoThumbnail:
    // CarDV - Aaron +++
    AHC_GetDisplayOutputDev(&OutputDevice);

    if (OutputDevice == AHC_DISPLAY_MAIN_LCD/*MMP_DISPLAY_SEL_MAIN_LCD*/)
    {
        if (ubLCDBKPowerOff) {
            if (!LedCtrl_GetBacklightStatus()) {
                LedCtrl_LcdBackLight(AHC_TRUE);
            }
        }
    }
    // CarDV - Aaron ---
    return ret;
}

#if 0
void ____SPS_PPS_Generation____() {}
#endif

//
typedef unsigned short JPEGTAG;
typedef struct {
    JPEGTAG         tag;
    unsigned short  size;
} JTAG_HEADER;
//
#define TAG_JPEG    0xffd8
#define TAG_APP1    0xffe1
#define TAG_SOF     0xffc0
#define TAG_QT      0xffdb
#define MAKE_JTAG_HEADER(jh, src)   jh.tag  = (*(src)     << 8) + (*(src + 1));\
                                    jh.size = (*(src + 2) << 8) + (*(src + 3));
//
#define ATOM(a, b, c, d)    ((a) + (b << 8) + (c << 16) + (d << 24))
#define ATOM_ftyp   ATOM('f','t','y','p')
#define ATOM_moov   ATOM('m','o','o','v')
#define ATOM_mvhd   ATOM('m','v','h','d')
#define ATOM_trak   ATOM('t','r','a','k')
#define ATOM_tkhd   ATOM('t','k','h','d')
#define ATOM_mdia   ATOM('m','d','i','a')
#define ATOM_minf   ATOM('m','i','n','f')
#define ATOM_stbl   ATOM('s','t','b','l')
#define ATOM_stsz   ATOM('s','t','s','z')
#define ATOM_udta   ATOM('u','d','t','a')
//#define   ATOM_PANA   ATOM('P','A','N','A')
//
typedef unsigned int    MP4ATOM;
typedef struct {
    unsigned int    size;
    MP4ATOM         atom;
} ATOM_HEADER;

typedef struct {
    OSAL_FILE*      fhdl;
    unsigned int    fpos;   // file position of read
    unsigned int    bpos;
    unsigned int    rpos;   // file position of data in buf
    char*           buf;
    char*			pfree;
    unsigned int    bufsize;
    ATOM_HEADER     ah;
} ACONTEXT;

#define MAKE_ATOM_HEADER(ah, src)   ah.size =  (*(src)     << 24) + \
                                               (*(src + 1) << 16) + \
                                               (*(src + 2) <<  8) + \
                                               (*(src + 3));  \
                                    ah.atom =  (*(src + 4)) + \
                                               (*(src + 5) <<  8) + \
                                               (*(src + 6) << 16) + \
                                               (*(src + 7) << 24);

#define MAKE_INT16(p)               (int)(*(p) << 8) + (int)(*(p + 1))
#define MAKE_INT32(p)               (int)(*(p) << 24)    + (int)(*(p + 1) << 16) + \
                                    (int)(*(p + 2) << 8) + (int)(*(p + 3))

ACONTEXT* InitAtomContext(ACONTEXT *atxt, OSAL_FILE *hdl);
void UninitAtomContext(ACONTEXT *atxt);
ATOM_HEADER* Reach_Sibling_Atom(ACONTEXT *atxt, MP4ATOM theAtom);
ATOM_HEADER *Find_AtomString(ACONTEXT *atxt, MP4ATOM *astr);

JTAG_HEADER *Find_JPEG_Tag(ACONTEXT *jtxt, JPEGTAG theTag)
{
    while (1) {
        JTAG_HEADER jh;

        MAKE_JTAG_HEADER(jh, jtxt->buf + (jtxt->bpos - jtxt->rpos));
        if (jh.size == 0) {
            UartSendTrace(BG_RED("%s %d UNRECOGNIZE FORMAT\n"), __FUNCTION__, __LINE__);
            return NULL;    // Unrecognize  Format
        }
        if (jh.tag == theTag) {
            memcpy(&jtxt->ah, &jh, sizeof(JTAG_HEADER));
            return (JTAG_HEADER*)&jtxt->ah;
        }
        // next sibling
        jtxt->bpos += (jh.size + sizeof(JPEGTAG));
        if (jtxt->bpos > jtxt->fpos - sizeof(JTAG_HEADER)) {
            unsigned int    rs;

            jtxt->rpos = jtxt->bpos & (~(512 - 1));
            if (osal_fseek(jtxt->fhdl, jtxt->rpos, MMP_FS_FILE_BEGIN) != 0) {
                break;
            }
            //osal_flush_dcache(jtxt->buf,jtxt->bufsize);
            if ((rs = osal_fread((void*)MsPA2VA(jtxt->buf), 1, jtxt->bufsize, jtxt->fhdl)) == 0) {
                break;
            }
            //osal_invalidate_dcache(((unsigned int)(jtxt->buf) & ~(MEM_ALIGNMENT_HEAP - 1)) , rs);
            osal_invalidate_dcache(((unsigned int)(jtxt->buf)) , rs);
            jtxt->fpos = jtxt->rpos + rs;
        } else if (jtxt->bpos < jtxt->rpos) {
            UartSendTrace(BG_RED("%s %d UNRECOGNIZE FORMAT\n"), __FUNCTION__, __LINE__);
            return NULL;
        }
    }
    return NULL;
}

//------------------------------------------------------------------------------
//  Function    : miGetJPGInfo
//  Description :
//------------------------------------------------------------------------------
int miGetJPGInfo(OSAL_FILE *hdl, MI_INFO *miInfo)
{
    ACONTEXT    context;
    int         ret = 0;

    if (InitAtomContext(&context, hdl) == NULL)
        goto ERR_miGetJPGInfo;

    context.bpos += sizeof(JPEGTAG);    // skip TAG_JPEG

    if (Find_JPEG_Tag(&context, TAG_SOF) == NULL)
        goto ERR_miGetJPGInfo;

    miInfo->width  = MAKE_INT16(context.buf + (context.bpos - context.rpos) + 0x7);
    miInfo->height = MAKE_INT16(context.buf + (context.bpos - context.rpos) + 0x5);
    miInfo->type   = 2; // Still Image

    ret = sizeof(MI_INFO);

ERR_miGetJPGInfo:
    UninitAtomContext(&context);
    return ret;
}

// frame rate = moov.mdia.stbl.stsz.samplecount /
//              (moov.trak.tkhd.duration / moov.mvhd.timescale)
int miGetMP4Info(OSAL_FILE *hdl, MI_INFO *miInfo)
{
    //#define   BUF_MP4SIZE     1024
    //#define   READ_MP4SIZE    1024
    //char          *buf;
    //size_t            rs;
    int             ret;
    //ATOM_HEADER       ah;
    ACONTEXT        context;
    MP4ATOM mvhdstr[] = {ATOM_moov, ATOM_mvhd, 0};
    MP4ATOM tkhdstr[] = {           ATOM_trak, ATOM_tkhd, 0};
    MP4ATOM stszstr[] = {                      ATOM_mdia, ATOM_minf, ATOM_stbl, ATOM_stsz, 0};
    ret = 0;
    // |<-------------------------->|
    // |<----->r<---b---->f<------->|
    //
    // init context
    if (InitAtomContext(&context, hdl) == NULL)
        goto ERR_miGetMP4Info;
    // moov.mvhd, get timescale, duration
    if (Find_AtomString(&context, mvhdstr) == NULL)
        goto ERR_miGetMP4Info;
    miInfo->timescale = MAKE_INT32(context.buf + (context.bpos - context.rpos) + 0x14);
    miInfo->duration  = MAKE_INT32(context.buf + (context.bpos - context.rpos) + 0x18);
    // moov.trak.tkhd, get width, height
    // *NOTE*: the first trak MUST BE vide
    if (Find_AtomString(&context, tkhdstr) == NULL)
        goto ERR_miGetMP4Info;
    miInfo->width  = MAKE_INT16(context.buf + (context.bpos - context.rpos) + 0x54);
    miInfo->height = MAKE_INT16(context.buf + (context.bpos - context.rpos) + 0x58);
    // moov.trak.mdia.minf.stbl.stsz, get sample counts
    if (Find_AtomString(&context, stszstr) == NULL)
        goto ERR_miGetMP4Info;
    miInfo->samplecount = MAKE_INT32(context.buf + (context.bpos - context.rpos) + 0x10);
    // It's MP4.
    miInfo->type = 1;   //MP4
    ret = sizeof(MI_INFO);

ERR_miGetMP4Info:
    UninitAtomContext(&context);
    return ret;
}
/*
 * Init ATON Context
 */
ACONTEXT* InitAtomContext(ACONTEXT *atxt, OSAL_FILE *hdl)
{
	#define NET_ATOME_ALIGN_BYTES (512)
    #define BUF_MP4SIZE     (1024)
    //#define   READ_MP4SIZE    1024
    size_t          rs;

    // init context
    atxt->buf = atxt->rpos = atxt->bpos = atxt->fpos = 0;
    atxt->fhdl = hdl;
    atxt->pfree  = osal_malloc(BUF_MP4SIZE + NET_ATOME_ALIGN_BYTES);
    atxt->bufsize = BUF_MP4SIZE;
    if (atxt->pfree == NULL) {
        return NULL;
    }
    atxt->buf = atxt->pfree + (NET_ATOME_ALIGN_BYTES - ((u32)atxt->pfree & (NET_ATOME_ALIGN_BYTES - 1)));
    osal_fseek(atxt->fhdl, atxt->rpos, MMP_FS_FILE_BEGIN);
    //osal_flush_dcache(atxt->buf,atxt->bufsize);
    if ((rs = osal_fread((void*)MsPA2VA(atxt->buf), 1, atxt->bufsize, atxt->fhdl)) == 0) {
        osal_free(atxt->pfree);
        return NULL;
    }
    //osal_invalidate_dcache(((unsigned int)(atxt->buf) & ~(MEM_ALIGNMENT_HEAP - 1)) , rs);
    osal_invalidate_dcache(((unsigned int)(atxt->buf)) , rs);
    atxt->fpos += rs;
    return atxt;
}
/*
 *
 */
void UninitAtomContext(ACONTEXT *atxt)
{
    if (atxt->pfree)
        osal_free(atxt->pfree);
}
/*
 *
 */
ATOM_HEADER* Reach_Sibling_Atom(ACONTEXT *atxt, MP4ATOM theAtom)
{
    while (1) {
        ATOM_HEADER ah;

        MAKE_ATOM_HEADER(ah, atxt->buf + (atxt->bpos - atxt->rpos));
        if (ah.size == 0) {
            UartSendTrace(BG_RED("%s %d UNRECOGNIZE FORMAT\n"), __FUNCTION__, __LINE__);
            return NULL;    // Unrecognize  Format
        }
        if (ah.atom == theAtom) {
            memcpy(&atxt->ah, &ah, sizeof(ATOM_HEADER));
            return &atxt->ah;
        }
        // next sibling
        atxt->bpos += ah.size;
        if (atxt->bpos > atxt->fpos - sizeof(ATOM_HEADER)) {
            unsigned int    rs;

            atxt->rpos = atxt->bpos & (~(512 - 1));
            if (osal_fseek(atxt->fhdl, atxt->rpos, MMP_FS_FILE_BEGIN) != 0) {
                break;
            }
            //osal_flush_dcache(atxt->buf,atxt->bufsize);
            if ((rs = osal_fread((void*)MsPA2VA(atxt->buf), 1, atxt->bufsize, atxt->fhdl)) == 0) {
                break;
            }
            //osal_invalidate_dcache(((unsigned int)(atxt->buf) & ~(MEM_ALIGNMENT_HEAP - 1)) , rs);
            osal_invalidate_dcache(((unsigned int)(atxt->buf)) , rs);
            atxt->fpos = atxt->rpos + rs;
        } else if (atxt->bpos < atxt->rpos) {
            UartSendTrace(BG_RED("%s %d UNRECOGNIZE FORMAT\n"), __FUNCTION__, __LINE__);
            return NULL;
        }
    }
    return NULL;
}
/*
 *
 */
ATOM_HEADER *Find_AtomString(ACONTEXT *atxt, MP4ATOM *astr)
{
    MP4ATOM *pato;

    if (astr == NULL) return NULL;
    pato = astr;
    while (Reach_Sibling_Atom(atxt, *pato) != NULL) {
        pato++;
        if (*pato == NULL)
            return &atxt->ah;
        // to offspring
        atxt->bpos += sizeof(ATOM_HEADER);
    }
    return NULL;
}
/*
 * handle is file handle
 * Get Media File Info
 */
int miGetMediaInfo(char *filename, MI_INFO *miInfo)
{
    OSAL_FILE *hdl;
    char      *p = NULL;
    int       ret = 0;

    p = strrchr(filename, '.');
    if (p == NULL)
        return ret;

    hdl = osal_fopen(filename, "rb");
    if (hdl == NULL)
        return ret;

    if (stricmp(p + 1, "JPG") == 0) {
        ret = miGetJPGInfo(hdl, miInfo);
    }
    else if (stricmp(p + 1, "MP4") == 0 ||
             stricmp(p + 1, "MOV") == 0) {
        ret = miGetMP4Info(hdl, miInfo);
    }

    osal_fclose(hdl);

    return ret;
}

/*******************************************************************
 * Miscellaneous for H.264 SPS/PPS Generation
 * Because MMP might not be on and the code and coupled with MMPF
 * Port a version here.
 *******************************************************************/
#if 0
void ____SPS_PPS_Generation____() {}
#endif

#define BASELINE_PROFILE (66)
#define MAIN_PROFILE     (77)
#define FREXT_HP         (100)      ///< YUV 4:2:0/8 "High"
#define SUPPORT_POC_TYPE_1 (0)

typedef struct _MI_H264_SPS_INFO {
    MMP_BOOL    Valid; // indicates the parameter set is valid

    MMP_ULONG   profile_idc;                                    // u(8)
    MMP_BOOL    constrained_set0_flag;                          // u(1)
    MMP_BOOL    constrained_set1_flag;                          // u(1)
    MMP_BOOL    constrained_set2_flag;                          // u(1)
    MMP_BOOL    constrained_set3_flag;                          // u(1)
    MMP_BOOL    constrained_set4_flag;                          // u(1)
    MMP_BOOL    constrained_set5_flag;                          // u(1)
    MMP_BOOL    constrained_set6_flag;                          // u(1)
    MMP_ULONG   level_idc;                                      // u(8)
    MMP_ULONG   seq_parameter_set_id;                           // ue(v)
    MMP_ULONG   chroma_format_idc;                              // ue(v)

    MMP_BOOL    seq_scaling_matrix_present_flag;                // u(1) => always 0
        //MMP_LONG   seq_scaling_list_present_flag[12];         // u(1)

    MMP_ULONG   bit_depth_luma_minus8;                          // ue(v)
    MMP_ULONG   bit_depth_chroma_minus8;                        // ue(v)
    MMP_ULONG   log2_max_frame_num_minus4;                      // ue(v)
    MMP_ULONG   pic_order_cnt_type;
    // if( pic_order_cnt_type == 0 )
    MMP_ULONG   log2_max_pic_order_cnt_lsb_minus4;              // ue(v)
    // else if( pic_order_cnt_type == 1 )
    #if (SUPPORT_POC_TYPE_1 == 1)
    MMP_BOOL delta_pic_order_always_zero_flag;                  // u(1)
    MMP_LONG    offset_for_non_ref_pic;                         // se(v)
    MMP_LONG    offset_for_top_to_bottom_field;                 // se(v)
    MMP_ULONG   num_ref_frames_in_pic_order_cnt_cycle;          // ue(v)
    // for( i = 0; i < num_ref_frames_in_pic_order_cnt_cycle; i++ )
    MMP_LONG    offset_for_ref_frame[MAX_REF_FRAME_IN_POC_CYCLE];   // se(v)
    #endif //(SUPPORT_POC_TYPE_1 == 1)
    MMP_ULONG   num_ref_frames;                                 // ue(v)
    MMP_BOOL    gaps_in_frame_num_value_allowed_flag;           // u(1)
    MMP_ULONG   pic_width_in_mbs_minus1;                        // ue(v)
    MMP_ULONG   pic_height_in_map_units_minus1;                 // ue(v)
    MMP_BOOL    frame_mbs_only_flag;                            // u(1)
    // if( !frame_mbs_only_flag )
    MMP_BOOL    mb_adaptive_frame_field_flag;                   // u(1)
    MMP_BOOL    direct_8x8_inference_flag;                      // u(1)
    MMP_BOOL    frame_cropping_flag;                            // u(1)
    MMP_ULONG   frame_cropping_rect_left_offset;                // ue(v)
    MMP_ULONG   frame_cropping_rect_right_offset;               // ue(v)
    MMP_ULONG   frame_cropping_rect_top_offset;                 // ue(v)
    MMP_ULONG   frame_cropping_rect_bottom_offset;              // ue(v)
    MMP_BOOL    vui_parameters_present_flag;                    // u(1)
    #if (SUPPORT_VUI_INFO)
        MMPF_H264ENC_VUI_INFO vui_seq_parameters;
    #endif
} MI_H264_SPS_INFO;
static MI_H264_SPS_INFO m_sps;

typedef struct _MMPF_H264ENC_BS_INFO {
    MMP_LONG byte_pos;          ///< current position in bitstream;
    MMP_LONG bits_to_go;        ///< current bit counter
    MMP_UBYTE byte_buf;         ///< current buffer for last written byte
    MMP_UBYTE *streamBuffer;    ///< actual buffer for written bytes
} MMPF_H264ENC_BS_INFO;

typedef enum _MMPF_H264ENC_NALU_TYPE {
    H264_NALU_TYPE_SLICE    = 1,
    H264_NALU_TYPE_DPA      = 2,
    H264_NALU_TYPE_DPB      = 3,
    H264_NALU_TYPE_DPC      = 4,
    H264_NALU_TYPE_IDR      = 5,
    H264_NALU_TYPE_SEI      = 6,
    H264_NALU_TYPE_SPS      = 7,
    H264_NALU_TYPE_PPS      = 8,
    H264_NALU_TYPE_AUD      = 9,
    H264_NALU_TYPE_EOSEQ    = 10,
    H264_NALU_TYPE_EOSTREAM = 11,
    H264_NALU_TYPE_FILL     = 12,
    H264_NALU_TYPE_SPSEXT   = 13,
    H264_NALU_TYPE_PREFIX   = 14,
    H264_NALU_TYPE_SUBSPS   = 15
} MMPF_H264ENC_NALU_TYPE;

typedef enum _MMPF_H264ENC_NAL_REF_IDC{
    H264_NALU_PRIORITY_HIGHEST     = 3,
    H264_NALU_PRIORITY_HIGH        = 2,
    H264_NALU_PRIORITY_LOW         = 1,
    H264_NALU_PRIORITY_DISPOSABLE  = 0
} MMPF_H264ENC_NAL_REF_IDC;

typedef struct _MMPF_H264ENC_NALU_INFO {
    MMPF_H264ENC_NALU_TYPE nal_unit_type;
    MMPF_H264ENC_NAL_REF_IDC nal_ref_idc;
    MMP_UBYTE   temporal_id;    ///< SVC extension
} MMPF_H264ENC_NALU_INFO;

typedef struct _MMPF_H264ENC_SYNTAX_ELEMENT {
    MMP_LONG    type;           //!< type of syntax element for data part.
    MMP_LONG    value1;         //!< numerical value of syntax element
    MMP_LONG    value2;         //!< for blocked symbols, e.g. run/level
    MMP_LONG    len;            //!< length of code
    MMP_LONG    inf;            //!< info part of UVLC code
    MMP_ULONG   bitpattern;     //!< UVLC bitpattern
    MMP_LONG    context;        //!< CABAC context

  //!< for mapping of syntaxElement to UVLC
  //void    (*mapping)(int value1, int value2, int* len_ptr, int* info_ptr);
} MMPF_H264ENC_SYNTAX_ELEMENT;

#define MAX_PARSET_BUF_SIZE     (256)
#define H264E_STARTCODE_LEN     (3)

static void sodb2rbsp(MMPF_H264ENC_BS_INFO *cur_bs)
{
    // check byte_aligned
#if 0//still generate 0x80 as HW does
    if (cur_bs->bits_to_go == 8)
        return;
#endif

    // check this: if bits_to_go is 0

    cur_bs->byte_buf    <<= 1;
    cur_bs->byte_buf    |= 1;
    cur_bs->bits_to_go--;
    cur_bs->byte_buf    <<= cur_bs->bits_to_go;
    cur_bs->streamBuffer[cur_bs->byte_pos++] = cur_bs->byte_buf;
    cur_bs->bits_to_go  = 8;
    cur_bs->byte_buf    = 0;
}

static int rbsp2ebsp(unsigned char *ebsp, unsigned char *rbsp, int rbsp_size)
{
    int i, ebsp_len, zero_count;

    ebsp_len = 0;
    zero_count = 0;
    for (i = 0; i < rbsp_size; i++) {
        if(zero_count == 2 && !(rbsp[i] & 0xFC)) {
            ebsp[ebsp_len] = 0x03;
            ebsp_len++;
            zero_count = 0;
        }
        ebsp[ebsp_len] = rbsp[i];

        zero_count = (rbsp[i])? 0: zero_count+1;
        ebsp_len++;
    }
    return ebsp_len;
}

static int rbsp2nalu(unsigned char *nalu_buf, unsigned char *rbsp, int rbsp_size,
                     MMPF_H264ENC_NALU_INFO *nalu_inf)
{
    int i;

#if 0
    // Write AnnexB NALU
    for (i = 0; i < (H264E_STARTCODE_LEN-1); i++) //always make 4 byte startcode
        nalu_buf[i] = 0x00;
    nalu_buf[i++] = 0x01;
#else
    i = 0;
#endif
    nalu_buf[i++] = (unsigned char)((nalu_inf->nal_ref_idc<<5)|nalu_inf->nal_unit_type);
    return i + rbsp2ebsp((nalu_buf+i), rbsp, rbsp_size);
}


static void write_uvlc(MMPF_H264ENC_SYNTAX_ELEMENT *se, MMPF_H264ENC_BS_INFO *currStream)
{
    unsigned int mask = 1 << (se->len - 1);
    int i;

    // Add the new bits to the bitstream.
    // Write out a byte if it is full
    if ( se->len < 33 )
    {
        for (i = 0; i < se->len; i++)
        {
            currStream->byte_buf <<= 1;

            if (se->bitpattern & mask)
                currStream->byte_buf |= 1;

            mask >>= 1;

            if ((--currStream->bits_to_go) == 0)
            {
                currStream->bits_to_go = 8;
                currStream->streamBuffer[currStream->byte_pos++] = currStream->byte_buf;
                currStream->byte_buf = 0;
            }
        }
    }
    else
    {
        // zeros
        for (i = 0; i < (se->len - 32); i++)
        {
            currStream->byte_buf <<= 1;

            if ((--currStream->bits_to_go) == 0)
            {
                currStream->bits_to_go = 8;
                currStream->streamBuffer[currStream->byte_pos++] = currStream->byte_buf;
                currStream->byte_buf = 0;
            }
        }
        // actual info
        mask = ((unsigned int)1) << 31;
        for (i = 0; i < 32; i++)
        {
            currStream->byte_buf <<= 1;

            if (se->bitpattern & mask)
                currStream->byte_buf |= 1;

            mask >>= 1;

            if ((--currStream->bits_to_go) == 0)
            {
                currStream->bits_to_go = 8;
                currStream->streamBuffer[currStream->byte_pos++] = currStream->byte_buf;
                currStream->byte_buf = 0;
            }
        }
    }
}

/** @brief Makes code word and passes it back
A code word has the following format: 0 0 0 ... 1 Xn ...X2 X1 X0.
NOTE this function is called with sym->inf > (1<<(sym->len/2)).  The upper bits of inf are junk
*/
static int symbol2uvlc(MMPF_H264ENC_SYNTAX_ELEMENT *sym)
{
    int suffix_len = sym->len >> 1;
    //assert (suffix_len < 32);
    suffix_len = (1 << suffix_len);
    sym->bitpattern = suffix_len | (sym->inf & (suffix_len - 1));
    return 0;
}

/** @brief mapping for ue(v) syntax elements
*/
static void ue_linfo(int ue, int dummy, int *len, int *info)
{
    int i, nn =(ue+1)>>1;

    for (i=0; i < 33 && nn != 0; i++)
    {
        nn >>= 1;
    }
    *len  = (i << 1) + 1;
    *info = ue + 1 - (1 << i);
}

/** @brief ue_v, writes an ue(v) syntax element, returns the length in bits
*/
static int ue_v (int value, MMPF_H264ENC_BS_INFO *bitstream)
{
    MMPF_H264ENC_SYNTAX_ELEMENT symbol, *sym=&symbol;
    sym->value1 = value;
    sym->value2 = 0;

    ue_linfo(sym->value1,sym->value2,&(sym->len),&(sym->inf));
    symbol2uvlc(sym);

    write_uvlc (sym, bitstream);

    return (sym->len);
}

/** @brief u_1, writes a flag (u(1) syntax element, returns the length in bits, always 1
*/
static int u_1 (int value, MMPF_H264ENC_BS_INFO *bitstream)
{
    MMPF_H264ENC_SYNTAX_ELEMENT symbol, *sym=&symbol;

    sym->bitpattern = value;
    sym->value1 = value;
    sym->len = 1;

    //assert (bitstream->streamBuffer != NULL);
    write_uvlc(sym, bitstream);

    return (sym->len);
}

/** @brief u_v, writes a n bit fixed length syntax element, returns the length in bits,
*/
static int u_v (int n, int value, MMPF_H264ENC_BS_INFO *bitstream)
{
    MMPF_H264ENC_SYNTAX_ELEMENT symbol, *sym=&symbol;

    sym->bitpattern = value;
    sym->value1 = value;
    sym->len = n;

    //assert (bitstream->streamBuffer != NULL);
    write_uvlc(sym, bitstream);

    return (sym->len);
}

static __inline MMP_ULONG idc_level(MI_H264_SPS_INFO* sps)
{
    struct IDC_LEVELS {
        MMP_ULONG MBperSec;
        MMP_USHORT level;
    } IDC_LEVELS[] = {
        {1485, 10},
        {3000, 11},
        {6000, 12},
        {11880, 20},
        {19800, 21},
        {20250, 22},
        {40500, 30},
        {108000, 31},
        {216000, 32},
        {245760, 41}
    };//must from low to high
    int i;
    MMP_ULONG MBperSec = (sps->pic_height_in_map_units_minus1 + 1) *
                         (sps->pic_width_in_mbs_minus1 + 1) * 30;

    for (i = 0; i < sizeof(IDC_LEVELS)/sizeof(IDC_LEVELS[0]); ++i) {
        if (MBperSec < IDC_LEVELS[i].MBperSec) {
            return (MMP_ULONG) IDC_LEVELS[i].level;
        }
    }
    return 0;
}

//idx is currently not used
MI_H264_SPS_INFO* miH264GetSpsInfo(int idx)
{
    return &m_sps;
}

void miH264InitSpsInfo(MI_H264_SPS_INFO* sps)
{
    MEMSET(sps, 0, sizeof(MI_H264_SPS_INFO));
    sps->profile_idc = BASELINE_PROFILE;
    sps->constrained_set0_flag = 0;
    sps->constrained_set1_flag = 0;
    sps->constrained_set2_flag = 0;
    sps->constrained_set3_flag = 0;
    sps->constrained_set4_flag = 0;
    sps->constrained_set5_flag = 0;
    sps->constrained_set6_flag = 0;
    sps->level_idc = 40;
    sps->seq_parameter_set_id = 0;
    sps->log2_max_frame_num_minus4 = 0;
    sps->pic_order_cnt_type = 0;
    sps->log2_max_pic_order_cnt_lsb_minus4 = 0;
    sps->num_ref_frames = 1;
    sps->pic_width_in_mbs_minus1 = 119;
    sps->pic_height_in_map_units_minus1 = 67;
    sps->frame_mbs_only_flag = 1;

    sps->vui_parameters_present_flag = 0;
}

void miH264ModifySpsInfo(MI_H264_SPS_INFO* sps, MMP_USHORT w, MMP_USHORT h)
{
    if ((h & 0x0F) != 0) {
        sps->frame_cropping_flag = 1;
        sps->frame_cropping_rect_bottom_offset = (0x10 - (h & 0x0F)) >> 1;
    }
    if ((w & 0x0F) != 0) {
        sps->frame_cropping_flag = 1;
        sps->frame_cropping_rect_right_offset = (0x10 - (w & 0x0F)) >> 1;
    }
    sps->pic_height_in_map_units_minus1 = ((h + 0xF)>> 4) - 1;
    sps->pic_width_in_mbs_minus1 = ((w + 0xF) >> 4) - 1;

    sps->level_idc = idc_level(sps);

    //sps->level_idc = 40;
    //printt("level_idc = %d\r\n", sps->level_idc);
}

//return total generated SPS length
int miH264GenerateSps (nalu_buf_t *nalu_buf, MI_H264_SPS_INFO *sps)
{
    MMPF_H264ENC_BS_INFO *bitstream, rbsp_inf;
    MMPF_H264ENC_NALU_INFO nalu_inf;
    MMP_ULONG   len = 0;
    MMP_UBYTE m_bH264ParsetBuf[MAX_PARSET_BUF_SIZE];
    int ret_len;

    //nalu_inf.buf = nalu_buf; // init nalu buf addr
    bitstream = &rbsp_inf;
    MEMSET0(&rbsp_inf);
    MEMSET0(m_bH264ParsetBuf);
    bitstream->streamBuffer = m_bH264ParsetBuf;
    bitstream->bits_to_go = 8;

    //len+=u_1  (0, bitstream);
    //len+=u_1  (sps->nal_ref_idc, bitstream);

    len+=u_v  (8, sps->profile_idc, bitstream);

    len+=u_1  (sps->constrained_set0_flag, bitstream);
    len+=u_1  (sps->constrained_set1_flag, bitstream);
    len+=u_1  (sps->constrained_set2_flag, bitstream);
    len+=u_1  (sps->constrained_set3_flag, bitstream);
    len+=u_1  (sps->constrained_set4_flag, bitstream);
    len+=u_1  (sps->constrained_set5_flag, bitstream);
    len+=u_1  (sps->constrained_set6_flag, bitstream);
    len+=u_1  (0, bitstream); //reserve_zero_bit
    //len+=u_v  (4, 0, bitstream);

    len+=u_v  (8, sps->level_idc, bitstream);

    len+=ue_v (sps->seq_parameter_set_id, bitstream);

    // Fidelity Range Extensions stuff
    if(sps->profile_idc == FREXT_HP) {
        len+=ue_v (sps->chroma_format_idc, bitstream);
        len+=ue_v (sps->bit_depth_luma_minus8, bitstream);
        len+=ue_v (sps->bit_depth_chroma_minus8, bitstream);
        len+=u_1  (0, bitstream);
        len+=u_1 (sps->seq_scaling_matrix_present_flag, bitstream);
    }

    len+=ue_v (sps->log2_max_frame_num_minus4, bitstream);
    len+=ue_v (sps->pic_order_cnt_type, bitstream);

    switch (sps->pic_order_cnt_type) {
    #if (SUPPORT_POC_TYPE_1 == 1)
    case 1:
        len+=u_1  (sps->delta_pic_order_always_zero_flag, bitstream);
        len+=se_v (sps->offset_for_non_ref_pic, bitstream);
        len+=se_v (sps->offset_for_top_to_bottom_field, bitstream);
        len+=ue_v (sps->num_ref_frames_in_pic_order_cnt_cycle, bitstream);
        for (i=0; i<sps->num_ref_frames_in_pic_order_cnt_cycle; i++)
            len+=se_v (sps->offset_for_ref_frame[i], bitstream);
        break;
    #endif
    case 2:
        break;
    case 0:
    default:
        len+=ue_v (sps->log2_max_pic_order_cnt_lsb_minus4, bitstream);
        break;
    }

    len+=ue_v (sps->num_ref_frames, bitstream);
    len+=u_1  (sps->gaps_in_frame_num_value_allowed_flag, bitstream);
    len+=ue_v (sps->pic_width_in_mbs_minus1, bitstream);
    len+=ue_v (sps->pic_height_in_map_units_minus1, bitstream);
    len+=u_1  (sps->frame_mbs_only_flag, bitstream);
    if (!sps->frame_mbs_only_flag) {
        len+=u_1  (sps->mb_adaptive_frame_field_flag, bitstream);
    }
    len+=u_1  (sps->direct_8x8_inference_flag, bitstream);

    len+=u_1  (sps->frame_cropping_flag, bitstream);
    if (sps->frame_cropping_flag) {
        len+=ue_v (sps->frame_cropping_rect_left_offset, bitstream);
        len+=ue_v (sps->frame_cropping_rect_right_offset, bitstream);
        len+=ue_v (sps->frame_cropping_rect_top_offset, bitstream);
        len+=ue_v (sps->frame_cropping_rect_bottom_offset, bitstream);
    }

    len+=u_1  (sps->vui_parameters_present_flag, bitstream);

    #if (SUPPORT_VUI_INFO)
    if (sps->vui_parameters_present_flag) {
        len += vui_parameter_generate(&(sps->vui_seq_parameters),
                bitstream);
    }
    #endif

    sodb2rbsp(bitstream); //byte aligned
    nalu_inf.nal_ref_idc   = H264_NALU_PRIORITY_HIGHEST;
    nalu_inf.nal_unit_type = H264_NALU_TYPE_SPS;
    ret_len = rbsp2nalu(nalu_buf->buf, bitstream->streamBuffer, bitstream->byte_pos, &nalu_inf);
    if (ret_len > nalu_buf->len) {
        printd(FG_RED("ERROR") " Insufficient NALU buffer size %d. SPS has been generated %d bytes and might have"
                " overwritten it.\r\n", nalu_buf->len, ret_len);
    }
    return ret_len;
}

int miH264GenerateSpsPpsNalu(nalu_buf_t * const sps_buf, nalu_buf_t *sps_pps_buf)
{
    unsigned char* ptr = sps_pps_buf->buf;
    unsigned char START_CODE[] = {0x00, 0x00, 0x00, 0x01};
    #define START_CODE_SIZE sizeof(START_CODE)
    unsigned char PPS[] = {0x68, 0xCE, 0x38, 0x80};
    #define PPS_SIZE sizeof(PPS)

    if (sps_pps_buf->len < sps_buf->len + START_CODE_SIZE * 2 + PPS_SIZE) {
        return -1;
    }

    MEMCPY(ptr, START_CODE, START_CODE_SIZE);
    ptr +=  START_CODE_SIZE;

    MEMCPY(ptr, sps_buf->buf, sps_buf->len);
    ptr += sps_buf->len;

    MEMCPY(ptr, START_CODE, START_CODE_SIZE);
    ptr +=  START_CODE_SIZE;

    MEMCPY(ptr, PPS, PPS_SIZE);
    ptr +=  PPS_SIZE;

    return ptr - sps_pps_buf->buf;
}



//
// Enum DCF File
#ifndef TEMP
#include "ahc_general.h"
#include "ahc_uf.h"
#include "fs_api.h"
#endif
//
// FILE Enum
//#include "fs_api.h"
typedef struct _FFINST {
    unsigned int    tot;
    unsigned int    idx;
    unsigned int    flen;
    int             fmt;    // AVI: 2, JPEG: 0
    int             rd;     // rd only:1, rw: 0
    int             new_file;    // 1: is a new file and wait for downloading
    void            *data;
    FS_FILETIME     ft;
} FFINST, *PFFINST;
static DCF_INFO _dcf_info;
static void copy_ffattr(PFFINST pffi, DCF_INFO *pinfo);
static FFINST   _ffi;

//int FindNextFile(PFFINST hinst, char *out, int bufsize, int *retsize, FFFILTER_FN* pfilter);

/*
 * check the input file is being written by recorder
 */
static int fileIsRecording(char* filename)
{
    if (AHC_GetAhcSysMode() == AHC_MODE_VIDEO_RECORD) {
        char    *fullname;

        fullname = (char*)AHC_VIDEO_GetCurPrmRecdFileName(AHC_TRUE);
        UartSendTrace("Current Recording file %s\r\n", fullname);
        return 0;
    }
    return 0;
}
/*
 * Currently Support DCF only, \DCIM\*
 */
PFFINST FindFirstFile(char *inout, int bufsize, int *retsize, FFFILTER_FN* pfilter)
{
//  AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *)"MP4,MOV,JPG,AVI");
//#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    // nothing!!
//#else
//  AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL);
//#endif
    if (pfilter == NULL)
        return NULL;

#if USE_THREAD_SAFE_DCF_API
    if (!AHC_UF_GetTotalFileCountByDB(pfilter->arg.db, &_ffi.tot))
#else
    if (!AHC_UF_GetAllDBTotalFileCount(&_ffi.tot))
#endif
    {
        return NULL;
    }
    if(_ffi.tot <= 0)
    {
        UartSendTrace("%s,DB=%d,count=%d!!!\r\n",__FUNCTION__,pfilter->arg.db,_ffi.tot);
        return NULL;
    }
    _ffi.idx = -1;
    _ffi.data = (void*)&_dcf_info;
    if (FindNextFile(&_ffi, inout, bufsize, retsize, pfilter) == 0)
        return NULL;
    return &_ffi;
}

int FindNextFile(PFFINST hinst, char *out, int bufsize, int *retsize, FFFILTER_FN* pfilter)
{
    unsigned char   type;
    int             len;
    PFFINST         pffi;
    int             idx;
    DCF_INFO        *pInfo;
#if USE_THREAD_SAFE_DCF_API
    AHC_BOOL ret = AHC_FALSE;
    UINT8 op;
#endif

    len = *retsize = 0;
    if (hinst == NULL || (pfilter == NULL)) {
        return 0;
    }
    pffi = (PFFINST)(hinst);
    idx  = pffi->idx;
    pffi->idx++;

__fnnext:
#if USE_THREAD_SAFE_DCF_API
    if (pfilter->arg.order == FF_BACKWARD) {
        if (pffi->idx == 0) {
            op = DCF_NODE_VISIT_NODETAIL;
        } else {
            op = DCF_NODE_VISIT_REWIND;
        }
    } else {
        if (pffi->idx == 0) {
            op = DCF_NODE_VISIT_NODEHEAD;
        } else {
            op = DCF_NODE_VISIT_FORWARD;
        }
    }

    if (pffi->data != NULL) {
        pInfo = (DCF_INFO*) pffi->data;
        ret = AHC_UF_GetFileInfoByVisitNode(pfilter->arg.db, pfilter->arg.cam, pInfo, op);
    }
    if (ret == AHC_FALSE) {
        pffi->idx = idx;
        return 0;
    }
#else
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    if (!AHC_UF_GetAllDBInfobyIndex(pffi->idx, &info)) {
        pffi->idx = idx;
        return 0;
    }
#else
{
    AHC_RTC_TIME    ftime;
    if (AHC_UF_GetFilePathNamebyIndex(pffi->idx, info.FileName) == AHC_FALSE) {
        pffi->idx = idx;
        return 0;
    }

#if (AHC_SHAREENC_SUPPORT) //dual encode case
    if (AHC_FALSE ==  AHC_UF_GetFileSizebyFullName(info.FileName, &info.uiFileSize)) {
        UartSendTrace("Unable to get file size\r\n");
        return 0;
    }
#else //fading code
    AHC_UF_GetFileSizebyIndex(pffi->idx, &info.uiFileSize);
#endif

    AHC_UF_GetFileTypebyIndex(pffi->idx, &info.FileType);
    AHC_UF_IsReadOnlybyIndex(pffi->idx, &info.bReadOnly);
    AHC_UF_GetFileTimebyIndex(pffi->idx, &ftime);
    info.uwYear = ftime.uwYear;
    info.uwMonth= ftime.uwMonth;
    info.uwDay  = ftime.uwDay;
    info.uwHour = ftime.uwHour;
    info.uwMinute=ftime.uwMinute;
    info.uwSecond=ftime.uwSecond;
}
#endif
#endif
    strncpy(out, pInfo->FilePath, bufsize);
    type = pInfo->FileType;
    if (pfilter) {
        if (pfilter->ffn) {
            if ((len = (pfilter->ffn)(hinst, out, (char*)(void*)(int)type, &(pfilter->arg))) == 0) {
                pffi->idx++;
                goto __fnnext;
            }
        }
        if (pfilter->arg.new_file != FF_ATTR_ANY && pInfo->bIsFileDownload != pfilter->arg.new_file) {
            pffi->idx++;
            goto __fnnext;
        }
    }
    len = strlen(out);
    // don't send writing file to remote to be deleted or downloaded
    if (fileIsRecording(out)) {
        pffi->idx++;
        goto __fnnext;
    }
    copy_ffattr(pffi, pInfo);
    *retsize = (len > bufsize - 1)? bufsize : len;
    return *retsize;
}

int FindFileAttr(PFFINST hinst, char *in, unsigned int* size, char** fmt, int *rd, FS_FILETIME *ft, int *new_file)
{
    PFFINST         pffi;

    if (!hinst)
        return 0;
    pffi  = (PFFINST)(hinst);
    *size = pffi->flen;
    switch (pffi->fmt) {
    case 0:
        *fmt = "jpeg";
        break;
    case 2:
        *fmt = "AVI";
        break;
    case 3:
        *fmt = "MOV";
        break;
    case 4:
        *fmt = "MP4";
        break;
    default:
        *fmt = "BAD";
    }
    *rd   = pffi->rd;
    *ft   = pffi->ft;
    *new_file  = pffi->new_file;
    return 1;
}

int FindFileGroup(PFFINST hinst, FILE_GRPINFO *pinf)
{
    PFFINST         pffi;
    DCF_INFO        *pif;

    if (!hinst) {
        return 0;
    }
    pffi = (PFFINST)(hinst);
    /*
    if (AHC_UF_GetDirFileKeybyIndex(pffi->idx, &pinf->dkey, &pinf->fkey) != AHC_TRUE) {
        UartSendTrace("ERROR:%s %d\n", __FUNCTION__, __LINE__);
        return 0;
    }
    */
    pif = (DCF_INFO*)pffi->data;
    pinf->dkey = pif->uwDirKey;
    pinf->fkey = pif->uwFileKey;
    #if (defined(DCF_GROUP_FUN) && DCF_GROUP_FUN != 0)
    if (AHC_UF_GetCurGrp(pinf->dkey, pinf->fkey, &pinf->grpid, &pinf->grpmo) != AHC_TRUE) {
        UartSendTrace("ERROR:%s %d\n", __FUNCTION__, __LINE__);
        return 0;
    }
    if (AHC_UF_GetGrpCurFileNum(pinf->dkey, pinf->fkey, pinf->grpid, &pinf->grpno) != AHC_TRUE) {
        UartSendTrace("ERROR:%s %d\n", __FUNCTION__, __LINE__);
        return 0;
    }
    if (AHC_UF_GetGrpTotalFileNum(pinf->dkey, pinf->grpid, &pinf->grpto) != AHC_TRUE) {
        UartSendTrace("ERROR:%s %d\n", __FUNCTION__, __LINE__);
        return 0;
    }
    #else
    //TBD
    #endif
    return 1;
}

int FindFileGetPosition(PFFINST hinst)
{
    PFFINST         pffi;

    if (!hinst)
        return 0;
    pffi = (PFFINST)(hinst);
    return pffi->idx;
}

/* FIXME To be reviewed. The target is to remove this define in case (1).
 * Use a temporary PSDATETIMEDCFDB structure here to implement backward from parameter.
 * It does not use DB lock and thus it is not tread-safe.
 * This function cooperates with the entire DIR command and might take up to seconds(?)
 * so it would be difficult to decide how to lock the DB.
 * Also it should use AHC_UF functions instead but which are not available now.*/
#define CR_DIR_BACKWARD_FROM (1)

/* FIXME To be reviewed. The target is to remove this define in case (1).
 * Also it should use AHC_UF functions instead but which are not available now.*/
#define CR_DIR_THREAD_SAFE_FROM (1)

PSDATETIMEFILE AIHC_DCFDT_GetParentNodeByIndex(PSDATETIMEDCFDB pDB, UINT uiIndex );
void *FindFileSetPosition(PFFINST hinst, int pos, FFFILTER_FN* pFilter)
{
    PFFINST         pffi;

    if (!hinst)
        return 0;
    pffi = (PFFINST)(hinst);
    if (pFilter == NULL)
        return NULL;
#if USE_THREAD_SAFE_DCF_API
    {
        PSDATETIMEDCFDB pDb;
        PSDATETIMEFILE node = NULL;
        #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
        pDb = AIHC_DCFDT_GetDbByType(pFilter->arg.db);
        if (pDb) {
        #if CR_DIR_BACKWARD_FROM
            if (pFilter->arg.order == FF_BACKWARD) {
                UINT32 cnt;
                cnt = pDb->ulTotalObjectNumByCam[pFilter->arg.cam];
                pos = cnt - pos - 1;
                osal_dprint(WARN, "Backward listing is not thread-safe. (to IDX %d)", pos);
            }
        #endif
        #if CR_DIR_THREAD_SAFE_FROM
            node = AIHC_DCFDT_GetParentNodeByIndex(pDb, pos);
        #endif
        }
        if (node) {
            pDb->psCurrParentNode = node;
        }
        #else
            #error Not supported
        #endif
    }
#endif
    pffi->idx = pos;
    return hinst;
}

static void copy_ffattr(PFFINST pffi, DCF_INFO *pinfo)
{
    pffi->flen = pinfo->uiFileSize;
    pffi->rd = (int)(pinfo->bReadOnly == AHC_TRUE)? 1 : 0;  // ??
    pffi->fmt  = pinfo->FileType;
    pffi->ft.Year     =  pinfo->uwYear;
    pffi->ft.Month    =  pinfo->uwMonth;
    pffi->ft.Day      =  pinfo->uwDay;
    pffi->ft.Hour     =  pinfo->uwHour;
    pffi->ft.Minute   =  pinfo->uwMinute;
    pffi->ft.Second   =  pinfo->uwSecond;
    pffi->new_file = pinfo->bIsFileDownload;
}

/*
*Just for old DCF rule
*if we want to delete rear file,
*we must transfer the rear path to the front path
*Because DCF will delete relvant rear and front files
*/
int GetFrontFilename(char* front)
{
    char *p,*n;

    if(0 == (p = strrchr(front, '.')))
        return 0;
    p--;
    if (!strncmp(p,  "R", 1)) {

        if( 0 == (n = strrchr(front, '\\')))
            return 0;
        n--;
        if (!strncmp(n,  "R", 1)) {
            memcpy(n,"F",1);
            memcpy(p,"F",1);
            return 1;
        }
    }
    return 0;

}

int wildstrcmp(char *s1, const char* ws2, int ws2len)
{
    if (*(ws2 + ws2len - 1) == '.') {
        return strncmp(s1, ws2, ws2len);
    }
    return strcmp(s1, ws2);
}

#define STATION_SERVICE_PORT 49132//43
#define STATION_SERVICE_VERSION 0x0f0a //2015/10

extern struct netif main_netdev;
static int  gSTAser_fd = -1;
static struct ammo_evmsg * gpSTAev = NULL;

//#define DBG_STA_SERV
static int station_handle_request(char * src,int revlen,char *pack)
{

    short reqtype;
    char *prestype,*presdata;
    int reslen;

    if(revlen < 4)
        return 0;

    if(*src != (STATION_SERVICE_VERSION >> 8) || *(src+1) != (STATION_SERVICE_VERSION & 0xff))
        return 0;

    #ifdef DBG_STA_SERV
    {
        int i ;
        for(i=0 ; i < revlen ; i++){
            UartSendTrace(FG_BLUE("0x%x "),*(src+i));
        }
        UartSendTrace(FG_BLUE("\n"));
    }
    #endif

    reslen      = 0;
    reqtype     = ntohs(*(uint16*)(src + 2));
    prestype    = pack + 2;
    presdata    = pack + 4;

    UartSendTrace("%s : reqtype=%x\n",__FUNCTION__,reqtype);

    switch(reqtype)
    {
        case 0x0001:
        {//request ip
            *(uint16*)prestype = htons(0x0101);
            *(uint32*)presdata = htonl(main_netdev.ip_addr.addr);
            UartSendTrace("ip = %x \n",main_netdev.ip_addr.addr);
            reslen = 8;
        }
        break;

        default:
        return 0;
    }

    *pack = STATION_SERVICE_VERSION >> 8;
    *(pack+1) = STATION_SERVICE_VERSION & 0xff;

    #ifdef DBG_STA_SERV
    {
        int i ;
        for(i=0 ; i < reslen ; i++){
            UartSendTrace(FG_RED("0x%x "),*(pack+i));
        }
        UartSendTrace(FG_RED("\n"));
    }
    #endif

    return reslen;

}

#define DISCOVER_STR "DISCOVER.CAMERA.IP"
static void station_service_requset(struct ammo_evmsg *m, void *d)
{
    socklen_t fromlen;
    int rev_len;
    struct sockaddr_in sockaddr;
    char rec_buf[128];

    fromlen = sizeof(struct sockaddr_in);
    if((rev_len = lwip_recvfrom(gSTAser_fd, rec_buf, sizeof(rec_buf), 0 , (struct sockaddr *)&sockaddr, &fromlen)) > 0)
    {
        int sendlen;
        //UartSendTrace("UDP receive data =%s,len=%d\n",rec_buf,rev_len);

        if (!strncasecmp(rec_buf,DISCOVER_STR,rev_len)) {
                ncgi_notify_uichange(NCGI_DEF_REASON);
        }

        if((sendlen = station_handle_request(rec_buf,rev_len,rec_buf)) != 0){
            int client_fd;
            struct sockaddr_in bind_sockaddr;
            int cnt;

            if((client_fd = lwip_socket( PF_INET, SOCK_DGRAM, 0 )) < 0)
                return;

            bind_sockaddr.sin_family      = AF_INET;
            bind_sockaddr.sin_addr.s_addr = 0;
            bind_sockaddr.sin_port        = 0;

            if( lwip_bind( client_fd, (struct sockaddr *)&bind_sockaddr, sizeof( sockaddr ) ) < 0 ) {
                osal_dprint(ERR, "fail to bind socket: %s",__FUNCTION__);
                lwip_close( client_fd );
            }

            #ifdef DBG_STA_SERV
            UartSendTrace("rec ip = %x port = %d\n",sockaddr.sin_addr.s_addr,sockaddr.sin_port);
            #endif

            cnt = lwip_sendto(client_fd, rec_buf, sendlen, 0, (struct sockaddr*)&sockaddr, fromlen);
            UNUSED_PARAMETER(cnt);
            lwip_close( client_fd );
        }
    }
}

/*
* Only for station Mode, listen to UDP port AIT_SERVICE_PORT
* to service request ,such as ip request ...
*/
void start_station_service(void)
{
    struct sockaddr_in sockaddr;

    if(gSTAser_fd != -1){
        UartSendTrace("%s : socket has exsited\n",__FUNCTION__);
        return;
    }

    if((gSTAser_fd = lwip_socket( PF_INET, SOCK_DGRAM, 0 )) < 0){
        return;
    }

    sockaddr.sin_family      = AF_INET;
    sockaddr.sin_addr.s_addr = IPADDR_ANY;//INADDR_BROADCAST;
    sockaddr.sin_port        = htons(STATION_SERVICE_PORT);

    if( lwip_bind( gSTAser_fd, (struct sockaddr *)&sockaddr, sizeof( sockaddr ) ) < 0 ) {
        osal_dprint(ERR, "fail to bind socket: %s", osal_strerror() );
        lwip_close( gSTAser_fd );
        return ;
    }

    //lwip_fcntl( gSTAser_fd, F_SETFL, O_NONBLOCK );

    gpSTAev = evmsg_new_FD( gSTAser_fd, 0, 0, station_service_requset, 0 );
}

void stop_station_service(void)
{

    if(gpSTAev){
        evmsg_remove(gpSTAev);
        gpSTAev = 0;
    }

    if(gSTAser_fd != -1){
        lwip_close(gSTAser_fd);
        gSTAser_fd = -1;
    }

}

/**
 *
 * @param[in,out] from Input string.
 * @param[out] to Output string. If this string pointer is NULL, then change `from` string.
 */
void ns_convert_fn_fs_to_web(char* from, char* to)
{
    size_t len;
    size_t i, j;

    len = strlen(from);
    if (to) {
        strncpy(to, from, len + 1);
    } else {
        to = from;
    }

    for (i = 0; i < len; ++i) {
        if ((to[i] == ':') && (to[i+1] == '\\')) {
            //dont' use strncpy(). the memory might be overlapped and the result will be undefined.
            for (j = i; j < len + 1; ++j) {
                to[j] = to[j+1];
            }
        }
        if (to[i] == ':' || (to [i] == '\\')) {
            to[i] = '/';
        }
    }
}
