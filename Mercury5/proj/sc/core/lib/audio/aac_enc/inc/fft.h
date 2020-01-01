/*
    Complex FFT Analysis/Synthesis
 */
#ifndef __FFT_H
#define __FFT_H

/*!< Size of the fft twiddle table, <br>
     The table can be used in other algorithmic sections
     sin k*pi/(LSI_FFT_TWIDDLE_TABLE_SIZE*2) k=0..LSI_FFT_TWIDDLE_TABLE_SIZE
*/
#define LSI_LD_FFT_TWIDDLE_TABLE_SIZE 9
#define LSI_FFT_TWIDDLE_TABLE_SIZE (1<<LSI_LD_FFT_TWIDDLE_TABLE_SIZE)

/* twiddle tables */
#if 0
extern const Word16 fftTwiddleTable[LSI_FFT_TWIDDLE_TABLE_SIZE+1];
#else
extern const Word32 fftTwiddleTable[LSI_FFT_TWIDDLE_TABLE_SIZE/2+1];
#endif

void cfft32(Word32 *x, Word16 size, Word16 isign, Word8 scale);

#endif
