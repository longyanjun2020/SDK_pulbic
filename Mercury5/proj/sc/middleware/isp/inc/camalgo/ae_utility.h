/*
 * ae_utility.h
 *
 *  Created on:
 *      Author:
 */

#define INT_MAX_POINT (16)

typedef struct
{
    unsigned short u2NumOfPoints;
    int i4Y[INT_MAX_POINT];
    int i4X[INT_MAX_POINT];
} INTP_LUT;

int Interp(int X1, int X2, int Y1, int Y2, int XX);
int Interp_LUT(INTP_LUT strLUT, int XX);
int compare(const void *a, const void *b);
