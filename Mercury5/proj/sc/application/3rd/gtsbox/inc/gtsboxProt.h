#ifndef __GTSBOX_PORT_H__
#define __GTSBOX_PORT_H__

#include "PixtelDataTypes.h"

void gtsbox_force_quit(void);
BOOL gtsbox_is_actived(void);

//for box only
void gtsbox_enter_app_fullscreen(void);
void gtsbox_leave_current_screen(void);
#endif
