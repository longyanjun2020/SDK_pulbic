#ifndef DVK_PERMISSION_H
#define DVK_PERMISSION_H

#include "java_ams.h"

#define DALVIK_PERMISSION_FILE_EXT  L".bin"

//for installer
int generate_default_permission_file( unsigned short* MIdletname );

// for MIDlet
int getNativeSettingValue(char* permissionName);

// for MIDlet
int setNativeSettingValue(char* permissionName, int value);

// for Java MMI
int nemomp_ams_getPermission_req(int index,java_permission_setting *java_per_set);

// for Java MMI
int nemomp_ams_setPermission_req(int index, java_permission_setting *ps);



#endif