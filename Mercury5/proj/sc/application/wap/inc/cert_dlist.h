
#ifndef __CERT_DLIST_H__
#define __CERT_DLIST_H__

#include <ncc_types.h>
#include <bnst.h>
#include <alg_module.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------    Function Declaration   ------------------------*/
extern T_SSL_Node * sslLstFirst(const T_SSL_List *pList);
extern T_SSL_Node * sslLstLast(const T_SSL_List *pList);
extern T_SSL_Node * sslLstNext(const T_SSL_Node *pNode);
extern T_SSL_Node * sslLstPre(const T_SSL_Node *pNode);
extern int32_t  sslLstCount(const T_SSL_List *pList);
extern int32_t  sslLstFind (const T_SSL_List *pList,const T_SSL_Node *pNode);
extern int32_t  sslLstAdd (T_SSL_List *pList, T_SSL_Node *pNode);
extern int32_t  sslLstDelete (T_SSL_List *pList,const T_SSL_Node *pNode);
extern void     sslLstInit (T_SSL_List *pList);
extern int32_t  sslLstInsert (T_SSL_List *pList, T_SSL_Node *pPrev, T_SSL_Node *pNode);
extern T_SSL_Node * sslLstGetFirst (T_SSL_List *pList);

#ifdef __cplusplus
}
#endif

#endif/* __CERT_DLIST_H__ */

