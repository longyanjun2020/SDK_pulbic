#ifndef __NEMOMP_PUSH_CONN_H__
#define __NEMOMP_PUSH_CONN_H__

// 20090119: Changed
typedef struct nm_push_entry_t
{
    struct nm_push_entry_t *next;

    nm_int32 portNo;
    nm_bool available;  // 20090112: Added 
    nm_char *connection;
    nm_char *midlet;
    nm_char *filter;
    nm_char *storagename;
    nm_int32 midletid; // 20090112: Added
} nm_push_entry;

extern nm_push_entry *gpPushList;

extern nm_int32 nemomp_push_open(void);
extern void nemomp_push_set_unavailable(nm_char *storge); // 20090112: Addded
extern nm_push_entry *nemomp_push_check(nm_int32 port);
extern nm_int32 nemomp_push_save(void);
extern nm_char *nemomp_push_findsuite(nm_char *storge, nm_bool available); // 20090112: Changed
extern nm_int32 nemomp_push_add(nm_char *str);
extern nm_int32 nemomp_push_remove(nm_char *str, nm_char *storge);
extern void nemomp_push_deletesuite(nm_char *storge);
extern nm_char *nemomp_push_findconn(nm_char *str);
extern void nemomp_push_free(void);

#endif /* __NEMOMP_PUSH_CONN_H__ */
