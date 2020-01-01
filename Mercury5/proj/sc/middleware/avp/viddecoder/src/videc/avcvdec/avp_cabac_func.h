#ifndef CABAC_FUNC_H
#define CABAC_FUNC_H

#include <assert.h>
#include "avp_cabac.h"

#define CountZeroBitsInRange(range, bits) \
{ \
    bits = CLSAME(range, 0) - (32-9); \
}

static uint32 biari_decode_symbol_eq_prob(DecodingEnvironment *de_cabac, PBUF *RESTRICT pbuf)
{
    uint32 bit;
    uint32 value = de_cabac->a.Dvalue;
    uint32 range = de_cabac->a.Drange;

    value = value << 1 | (pbuf->bits >> 31);

    BITS_CACHE_FLUSH(pbuf->bits, pbuf->len, 1);

    bit = value >= range;
    if (bit) {
        value -= range;
    }

    de_cabac->a.Dvalue = value;
    return bit;
}

static unsigned int unary_bin_max_decode(DecodingEnvironment *de_cabac,
                                         BiContextTypePtr ctx,
                                         unsigned int max_symbol,
                                         PBUF *RESTRICT pbuf)
{
    unsigned int l;
    unsigned int symbol;

    symbol = biari_decode_symbol(de_cabac, ctx, pbuf);

    if ((symbol == 0) OR (max_symbol==1))
        return symbol;
    else {
        symbol=0;
        do {
            l = biari_decode_symbol(de_cabac, ctx, pbuf);
            symbol++;
        } while ((l != 0) AND (symbol<max_symbol-1));
        symbol += ((l != 0) AND (symbol==max_symbol-1));
        return symbol;
    }
}

static unsigned int unary_bin_decode_i_v2(DecodingEnvironment *de_cabac, BiContextTypePtr ctx,
                                          PBUF *RESTRICT pbuf)
{
    unsigned int l;
    unsigned int symbol;

    symbol = 1;
    do {
        l = biari_decode_symbol(de_cabac, ctx, pbuf);
        symbol++;
    } while (l != 0);

    return symbol;
}

static unsigned int biari_decode_final_i_v2(DecodingEnvironment *de_cabac, PBUF* RESTRICT pbuf)
{
    uint32 value = de_cabac->a.Dvalue;
    uint32 range = de_cabac->a.Drange - 2;
    uint32 range_value = PACK16LSB(range, value);
    int ret;
    ret = value>=range;

    if ((range<256) & (!ret))
    {
        assert(range>=128);
        range_value = (range_value << 1) | (pbuf->bits >> 31);
        BITS_CACHE_FLUSH(pbuf->bits, pbuf->len, 1);
    }

    if (!ret)
        de_cabac->cmp = range_value;

    return ret;
}
#endif /* CABAC_FUNC_H */
