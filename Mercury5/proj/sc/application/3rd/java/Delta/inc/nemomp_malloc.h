#ifndef _NEMOMP_MALLOC_H
#define _NEMOMP_MALLOC_H

#include "DualMemPool.h"
  

#if 1

#define nemomp_malloc(x) platform_malloc((x), __FILE__, __LINE__)
#define nemomp_free(y) platform_free((y), __FILE__, __LINE__)
#define nemomp_calloc platform_strdup

#endif

extern void *platform_malloc(int size, char* filename, int lineno);
extern void platform_free(void* ptr, char* filename, int lineno);
extern char *platform_strdup(char *string, int length);




typedef struct nemomp_allocated_ptr_struct_t
{
	int handle;
	int size;
	struct nemomp_allocated_ptr_struct_t *next;

} nemomp_allocated_ptr_struct;

typedef nemomp_allocated_ptr_struct *nemomp_allocated_ptr;

extern nemomp_allocated_ptr nemomp_allocated_ptr_head;

extern int nemomp_add_ptr(int fd,int size);
extern int nemomp_remove_ptr(int fd);
extern void nemomp_list_ptr(void);
extern int nemomp_get_ptr_count(void);
extern void nemomp_force_close_all_ptr(void);
extern int nemomp_get_ptr_size(int ptr);


#endif /* _NEMOMP_MALLOC_H */

