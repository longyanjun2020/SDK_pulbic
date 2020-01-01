
#ifndef __TLS_HMAC_H__
#define __TLS_HMAC_H__

#ifdef  __cplusplus
extern "C"{
#endif

#include <alg_enc.h>

#define ALG_HMAC_MAX_MD_CBLOCK	64

typedef struct
{
        uint8_t key[ALG_HMAC_MAX_MD_CBLOCK];
	T_ALG_Md *md;
	T_ALG_MdCtx md_ctx;
	T_ALG_MdCtx i_ctx;
	T_ALG_MdCtx o_ctx;
	uint32_t key_length;
} T_ALG_HmacCtx;

void algHMACCTXInit(T_ALG_HmacCtx *ctx);
void algHMACInitEx(T_ALG_HmacCtx *ctx, const void *key, int32_t len,uint32_t mdid);
void algHMACUpdate(T_ALG_HmacCtx *ctx, const uint8_t *data, int32_t len);
void algHMACFinal(T_ALG_HmacCtx *ctx, uint8_t *md, uint32_t *len);
void algHMACCTXCleanup(T_ALG_HmacCtx *ctx);

#ifdef _cplusplus
}
#endif

#endif
