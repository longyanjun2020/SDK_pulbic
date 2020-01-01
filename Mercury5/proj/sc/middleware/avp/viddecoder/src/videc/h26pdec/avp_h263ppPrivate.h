#ifndef H263PP_PRIVATE_H
#define H263PP_PRIVATE_H

#ifdef SUPPORT_H263PP

/* pb frame type */
#define PB_FRAMES                       1
#define IM_PB_FRAMES                    2

#define MODE_INTER                      0
#define MODE_INTER_Q                    1
#define MODE_INTER4V                    2
#define MODE_INTRA                      3
#define MODE_INTRA_Q                    4
#define MODE_INTER4V_Q                  5

/* Intra Mode for Advanced Intra Coding mode */
#define INTRA_MODE_DC                   0
#define INTRA_MODE_VERT_AC              2
#define INTRA_MODE_HORI_AC              3

extern const uchar MQ_chroma_QP_table[32];

#endif
#endif // H263PP_PRIVATE_H
