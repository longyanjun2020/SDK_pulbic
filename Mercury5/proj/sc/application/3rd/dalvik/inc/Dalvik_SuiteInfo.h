#ifndef __DALVIK_SUITEINFO_H_
#define __DALVIK_SUITEINFO_H_
#include "Dalvik_ams_info.h"


extern int DeocdeJARandGetIcon( u16* JARFilePath, u8* iconFileName, int* iconFileLen, u8* iconBuf );
extern int AddMIDletSuiteToDisk();
extern int Dalvik_AMS_free_suiteList();
extern int RemoveMIDletSuiteToDisk( int index );
extern int UpdateMIDletSuiteToDisk( int index );
extern int parse_Dalvik_SuiteInfo(int index, dalvik_suites_list** this_saved_mids_listfile_ptr);

#endif
