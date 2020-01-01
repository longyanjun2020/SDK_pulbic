
#ifndef SWVENC_2DDMA_PFRAME_H
#define SWVENC_2DDMA_PFRAME_H

#define CURRENT_MB_SIZE 256
#define SEARCH_WINDOW_SIZE (48*48)
#define UV_MB_SIZE 64
#define QMEM_SIZE 3000
#define DCT_ALIGN 0xF
#define LAST_MB 999999
typedef struct Pframe_QMEM_t {
    int dctbuf_addr[6];
    uint8* fmebuf_addr[3];
    uint8* Curblock_addr[6];
    uint8* UV_Refblock_addr[2];
    uint8* Rec_addr[6];
    int ref_offset;
    
} PFRAME_QMEM_t;


#define UV_REC_BLOCK ((uint8*)(QM_MEM +2*UV_MB_SIZE + 2*2*64+2*24*10))


#endif /* SWVENC_2DDMA_PFRAME_H */
