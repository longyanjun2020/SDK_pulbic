/**
 *  @file   mmi_mae_common_content.h
 *  @brief
 *  @version $Id: mmi_mae_common_content.h 1805 2009-09-21 12:56:09Z elvis.chen $
 */
#ifndef __MMI_MAE_COMMON_CONTENT_H__
#define __MMI_MAE_COMMON_CONTENT_H__
/*****************************************************************************
*!!! NOTICE !!!
* The followings are moved from mmi_common_content.h, for the purpose that
* MAE can not include any header file in app/srv/mmi_common level.
* This is just a temporary solution! It should be modified in the future!
******************************************************************************/
/*==============================================================================
                       INCLUDE FILES FOR MODULE
==============================================================================*/
enum MAEMIMEFilterID_e_
{
    MIMEFILTER_NONE				= 0xFF, // list all
    MIMEFILTER_PICTUREBASE		= 0,
    MIMEFILTER_RINGERBASE,      // music file that can be set as ringer.
    MIMEFILTER_MUSICBASE,       // all sound content
    MIMEFILTER_MP3BASE,
    MIMEFILTER_M3UBASE,
    MIMEFILTER_WAVBASE,
    MIMEFILTER_VIDEOBASE,
    MIMEFILTER_VOICEMEMOBASE,
    MIMEFILTER_EMUBASE,         // filter: all emulator game files
    MIMEFILTER_THEMEBASE,       // filter: all theme files
    MIMEFILTER_VCARDBASE,	    // filter: (*.vcf, *.phb)
    MIMEFILTER_MMSVIDEOBASE,
    MIMEFILTER_MMSMUSICBASE,
    MIMEFILTER_FMRECBASE,
#if defined (__USER_DEFINE_POWERONOFF_ANIM__) || defined (__USER_DEFINE_POWERONOFF_VIDEO__)
    MIMEFILTER_ONOFFDISPLAYBASE,    // Power on/off display
#endif
#ifdef __VIDEO_WALLPAPER__
    MIMEFILTER_WALLPAPERBASE,   //image and video can be set as wallpaper
#endif
    MIMEFILTER_MEDIATYPEMAX
};

//-------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------
/**************
* End of NOTICE
**************/
/*-------------------------------------------------------------------------*/
#endif /* __MAE_COMMON_CONTENT_H__ */
