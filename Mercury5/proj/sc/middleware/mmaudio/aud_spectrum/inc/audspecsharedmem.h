#ifndef AUDSPECSHAREDMEM_H
#define AUDSPECSHAREDMEM_H

// --- compile option ----

// --- paramters ---------
#define REG_NUM 5

// index of ring-buffer register
#define HDR_ADDR 0
#define CONSUMER_FLAG 1
#define PRODUCER_FLAG 2
#define PREAD 3
#define PWRITE 4

#define rreg(reg,index,val) {unsigned int* preg = reg[index]; val = *preg;}
#define wreg(reg,index,val) {unsigned int* preg = reg[index]; *preg = val;}

typedef struct STRUC_AUDSPEC_RBUF_PACKET_S {
	long long pts;
	char data[32];
} STRUC_AUDSPEC_RBUF_PACKET;

/* address of this B2-M3 shared structure
*  will be sent to M3 by command. M3 only
*  changes the following three members:
*
*  1. unsigned int u32Write_Index;            // write index
*  2. unsigned int u32Consumber_Flag;         //data is validate
*  3. unsigned int u32Producer_Flag;
*/
typedef struct STRUC_AUDSPEC_SHAREDMEM_REGISTER_S{
    // B2 access
    unsigned int u32Read_Index;             // read index
    unsigned int padding1[7];               // 32bytes aligned

    // M3 access
    unsigned int u32Write_Index;            // write index
    unsigned int padding2[7];               // 32bytes aligned

    unsigned char* u32RingBaseMMIAddr;      //BB base address
    unsigned char* u32RingBaseM3Addr;       //M3 base address , BB don't care
    unsigned int u32ringbufsize;            // total size ( head+data )
    unsigned int u32ringbufblocksize;       // data block size
    unsigned int u32ringinit;               //buff is init ( BB set )
    unsigned int u32Consumer_Flag;         //data is validate
    unsigned int u32Producer_Flag;
    unsigned int padding4[1];               // 32bytes aligned

} STRUC_AUDSPEC_SHAREDMEM_REGISTER;

typedef struct STRUC_AUDSPEC_RBUF_HEADER_S {
    STRUC_AUDSPEC_SHAREDMEM_REGISTER* shared_mem_reg_s;
    unsigned int* reg_addr[5];      // shared ring-buffer registers
    char* pkt_list_addr;            // begin of data packet ring-buffer = begin of shared memory+sizeof(STRUC_AUDSPEC_SHAREDMEM_REGISTER)
    unsigned int max_packet_size;   // (sizeof(shared memory)-24)/sizeof(data packet)
} STRUC_AUDSPEC_RBUF_HEADER;

#ifdef __cplusplus
extern "C"{
#endif

int WriteData_AudSpectrum(STRUC_AUDSPEC_RBUF_HEADER *hdr,
                           STRUC_AUDSPEC_RBUF_PACKET *pkt);
int ReadData_AudSpectrum(STRUC_AUDSPEC_RBUF_HEADER *hdr,
                          STRUC_AUDSPEC_RBUF_PACKET *pkt);
void EnableReadRbuf_AudSpectrum(STRUC_AUDSPEC_RBUF_HEADER* hdr);
void DisableReadRbuf_AudSpectrum(STRUC_AUDSPEC_RBUF_HEADER* hdr);
void EnableWriteRbuf_AudSpectrum(STRUC_AUDSPEC_RBUF_HEADER* hdr);
void DisableWriteRbuf_AudSpectrum(STRUC_AUDSPEC_RBUF_HEADER* hdr);

#ifdef __cplusplus
}
#endif

#endif
