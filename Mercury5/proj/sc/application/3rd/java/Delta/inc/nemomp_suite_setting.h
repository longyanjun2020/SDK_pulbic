#ifndef __NEMOMP_SUITE_SETTING_H__
#define __NEMOMP_SUITE_SETTING_H__

typedef struct nm_suite_setting_t
{
    /*00*/nm_char permission_http;
    /*01*/nm_char permission_https;
    /*02*/nm_char permission_ssl;
    /*03*/nm_char permission_tcp;
    /*04*/nm_char permission_tcp_server;
    /*05*/nm_char permission_udp;
    /*06*/nm_char permission_udp_server;
    /*07*/nm_char permission_comm;
    /*08 X*/nm_char permission_push;
#ifdef __JAVA_JSR211_CHAPI__
    /*09 X*/nm_char permission_chapi; // 20090218: Added for JSR-211 CHAPI
#endif /* __JAVA_JSR211_CHAPI__ */
    /*X+1*/nm_char permission_sms_server;
    /*X+2*/nm_char permission_sms_send;
    /*X+3*/nm_char permission_sms_receive;
    /*X+4*/nm_char permission_cbs_server;
    /*X+5*/nm_char permission_cbs_receive;
    /*X+6*/nm_char permission_mms_server;
    /*X+7*/nm_char permission_mms_send;
    /*X+8*/nm_char permission_mms_receive;
    /*X+9*/nm_char permission_mma_record;
    /*X+10*/nm_char permission_mma_snap_shot;
    /*X+11*/nm_char permission_file_read;
    /*X+12*/nm_char permission_file_write;
    /*X+13*/nm_char permission_contact_list_read;
    /*X+14*/nm_char permission_contact_list_write;
    /*X+15*/nm_char permission_event_list_read;
    /*X+16*/nm_char permission_event_list_write;
    /*X+17*/nm_char permission_todo_list_read;
    /*X+18*/nm_char permission_todo_list_write;
} nm_suite_setting;

typedef struct nm_group_setting_t
{
    nm_char group_permission_network;
    nm_char group_permission_multimedia;
    nm_char group_permission_messaging;
    nm_char group_permission_autostart;
    nm_char group_permission_localconnect;
    nm_char group_permission_dataread;
    nm_char group_permission_datawrite;
	
} nm_group_setting;

typedef enum
{
    PERMISSION_NEVER = 0x00,
    PERMISSION_ALLOW = 0x01,
    PERMISSION_BLANKET_GRANTED = 0x02,
    PERMISSION_BLANKET = 0x04,
    PERMISSION_SESSION = 0x08,
    PERMISSION_ONE_SHOT = 0x10,
    PERMISSION_DENY_SESSION = 0x20,
    PERMISSION_DENY = 0x40,
    PERMISSION_USER_DENIED = 0x80
} suite_setting_enum;

extern nm_suite_setting running_suite_setting;
extern nm_suite_setting running_suite_max_setting;

#endif /* __NEMOMP_SUITE_SETTING_H__ */
