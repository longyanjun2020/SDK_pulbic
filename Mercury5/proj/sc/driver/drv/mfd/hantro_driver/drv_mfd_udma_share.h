/* Linear memory area descriptor */
    typedef struct MEMMAP
    {
        u8  *miuPointer;
        u32 miuAddress;
        u32 size;
    } MEMMAP_t;

void M4VD_MMAPInit(unsigned char* handle_buffer, int handle_buffer_size);
i32  M4VD_MMAPMalloc(u32 size, MEMMAP_t * info);