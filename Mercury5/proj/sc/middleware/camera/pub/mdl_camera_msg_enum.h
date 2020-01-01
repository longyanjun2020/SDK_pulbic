#ifndef __MDL_CAMERA_MSG_ENUM_H__
#define __MDL_CAMERA_MSG_ENUM_H__

#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif

typedef enum MdlCameraMsgType
{
#include "mdl_camera_message_define__.hi"
} MdlCameraMsgType_e;

#endif

