
#include "nemomp.h"

typedef struct nm_properites_setting_struct_t
{
    nm_char *key;
    nm_char *value;
} nm_properites_setting_struct;

extern nm_int32 nemomp_get_java_properites_count(void);

extern nm_properites_setting_struct* nemomp_get_java_properites(void);