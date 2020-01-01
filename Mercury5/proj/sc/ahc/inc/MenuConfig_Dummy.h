#ifndef _MENU_CONFIG_DUMMY_H_
#define _MENU_CONFIG_DUMMY_H_

/////////////////////////////////////////////////////////////
/* OSD Drawing On/Off */

#ifndef OSD_SHOW_LDWS_LANE_LINE
#define OSD_SHOW_LDWS_LANE_LINE                     (LDWS_SUPPORT & 1)
#endif

#ifndef OSD_SHOW_LDWS_ALARM
#define OSD_SHOW_LDWS_ALARM                         (LDWS_SUPPORT & 1)
#endif

#ifndef OSD_SHOW_FCWS_RESULT
#define OSD_SHOW_FCWS_RESULT                        (FCWS_SUPPORT & 1)
#endif

#ifndef OSD_SHOW_BATLOW_WARNING
#define OSD_SHOW_BATLOW_WARNING						        (0)
#endif

#ifndef MENU_MEDIA_EN
#define MENU_MEDIA_EN                                       (0)
#endif

#ifndef MENU_SINGLE_EN
#define MENU_SINGLE_EN                                      (0)
#endif

#ifndef SHOW_HDMI_DIR_ICON
#define SHOW_HDMI_DIR_ICON                                  (0)
#endif

#endif//_MENU_CONFIG_DUMMY_H_
