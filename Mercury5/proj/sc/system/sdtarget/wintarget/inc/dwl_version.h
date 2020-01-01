/****************************************************************************/
/*  $Workfile::xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx$ */
/*--------------------------------------------------------------------------*/
/*  Scope   :                                                               */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/****************************************************************************/



#ifndef __DWL_VERSION_H__
#define __DWL_VERSION_H__

#ifdef __DWL_VERSION_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

/*
  * 3.5.6.25: Support of uploading factory image after download
  */
/* this version number send to DwlWin to check if compatible */
#define DWL_VERSION_NUMBER { 3, 5, 6, 24 }

INTERFACE u32 touch_version_vars(void);
INTERFACE void print_version_string(void);

#endif /* ! __DWL_VERSION_H__   */

