
#ifndef KJAVA_SYS_EXT_CERT_HEADER
#define KJAVA_SYS_EXT_CERT_HEADER

#ifdef __cplusplus
extern "C"{
#endif

#define EXT_MAX_CERT_CHAIN_DEPTH    9

typedef struct EXT_CA_info_
{
    const unsigned char *cert_data;
    int cert_data_len;
} EXT_CA_INFO;

int getCertStoreSize(void);

void getCertFromStore(int id, unsigned char **cert, int *len);

#ifdef __cplusplus
}
#endif

#endif /* KJAVA_EXT_HEADER */
