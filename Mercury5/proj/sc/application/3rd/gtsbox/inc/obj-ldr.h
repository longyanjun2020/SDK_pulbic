#ifndef __OBJ_LDR__H
#define __OBJ_LDR__H

struct object_loader_facility{
	/* mandary facility functions */
	void *(*malloc)(int size, void *user_data);
	void (*free)(void *ptr, void *user_data);
	/* read data from file at the give offset, a combination of seek and read */
	int (*read)(void *file_handle, long offset, void *buf, int size, void *user_data);
	/* resolve extern symbol */
	unsigned long (*resolve_symbol)(const char *name, void *user_data);
	
	/* executable memory allocation functions, for better memory manangement.
	   if set to NULL will fall back to basic malloc functions.
	   typical sinario:
	   malloc() will allocate memory from the end of a large memory block, 
	   which can later use as application program stack or heap, and 
	   alloc_exec_mem() will allocate memory from the beginning of the 
	   memory block.
	*/
	void *(*alloc_exec_mem)(int size, void *user_data);
	void (*free_exec_mem)(void *, void *user_data);	
};

/* load a object file using the given facility */
void *object_loader_load(void *file_handle, const struct object_loader_facility *facility, void *user_data);

/* get the address of a symbol(function name or global variable name) */
unsigned long object_loader_sym(void *handle, const char *name);

/* unload the object from memory. this function need not be called if
   the calling program can take care the object unloading itself.
 */
int object_loader_unload(void *handle);

/* free internal data structures, but the mmapped memory or the memory allocated
   by alloc_exec_mem() will not unmap or free. use object_loader_unload() to free
   the exe memory, or take care by the calling program itself.
*/
int object_loader_free(void *handle); 


#endif