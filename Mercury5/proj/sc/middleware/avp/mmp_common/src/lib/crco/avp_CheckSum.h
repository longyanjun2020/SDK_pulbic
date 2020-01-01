#ifndef CHECKSUM_H
#define CHECKSUM_H

typedef unsigned long adler_ctx;

void InitCheckSum(adler_ctx *ctx);
void UpdateCheckSum(adler_ctx *ctx, unsigned char *ptr, int len);

void crco_add_frame(adler_ctx *ctx,
                    unsigned char *y, unsigned char *u, unsigned char *v,
                    int width, int height,
                    int stride_y, int stride_uv, 
                    int active_x, int active_y
                    );

#endif
