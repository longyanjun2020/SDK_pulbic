#ifndef IQUANT_H
#define IQUANT_H

void iquant1(short *psblock, int quantizer, const uint8 *qmatrix);
void ATTR_INST16 iquant2(short *psblock, int quantizer);

#endif // IQUANT_H
