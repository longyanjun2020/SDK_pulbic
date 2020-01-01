/******************************************************************************/
/*  $Workfile::   fletcher_cks.h                                            $ */
/*----------------------------------------------------------------------------*/
/*  Scope   :                                                                 */
/*                                                                            */
/*  Contents:                                                                 */
/*                                                                            */
/******************************************************************************/

#ifndef _FLETCHER_CKS_H_
#define _FLETCHER_CKS_H_

void    FletcherCheckSum_Raz(void);
void    FletcherCheckSum_ByteUpdate(unsigned short i_u16_Value);
int     FletcherCheckSum_Test(void);
void    FletcherCheckSum_Calc(unsigned char *checkA, unsigned char *checkB,
                              unsigned char *data, unsigned long len);

unsigned short ComputeFletcher16Checksum(u8 *data, u32 size);

#endif /* !_FLETCHER_CKS_H_ */
