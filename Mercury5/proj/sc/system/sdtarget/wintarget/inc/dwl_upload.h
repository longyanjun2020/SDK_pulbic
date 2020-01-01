/****************************************************************************/
/*  $Workfile::xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx$ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Target downloader                                            */
/*             Memory upload function                                       */
/****************************************************************************/

#ifndef _4143bc5a002868fbfb3732fd975d8193_included_dwl_upload_h
#define _4143bc5a002868fbfb3732fd975d8193_included_dwl_upload_h

#ifdef __PASSIVE_DOWNLOAD__
s32 dwl_NorUpload(dwl_BinaryDescriptor_t *);
#else
s32 dwl_NorUpload(void);
#endif
s32 dwl_NandUpload(void);

#ifdef __PASSIVE_DOWNLOAD__
s32 dwl_Upload(u32, u32);
#else
s32 dwl_Upload(void);
#endif

#endif /* ! _4143bc5a002868fbfb3732fd975d8193_included_dwl_upload_h   */
