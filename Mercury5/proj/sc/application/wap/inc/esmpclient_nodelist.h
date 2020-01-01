
#ifndef __ESMPCLIENT_NODELIST_H__
#define __ESMPCLIENT_NODELIST_H__
#include <uapps/wap/wap_struct.h>

#ifdef __cplusplus
extern "C" {
#endif

struct __cjs_optiions_private_data__ {
    T_DB_FieldNodePtr pField; /** options' parent select */
    T_DB_OptionNodePtr pFirstOption; /** possible first option pointer*/
    T_DB_OptionNodeIdx iFirstOption; /** iFirstOption for pFirstOption */
    T_DB_FieldNodeIdx iField; /** options' parent select */
};
typedef struct __cjs_optiions_private_data__ cjsOptsPriData;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESMPCLIENT_NODELIST_H__ */
