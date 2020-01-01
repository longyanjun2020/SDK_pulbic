/*
   Band/Line energy calculations
 */
#ifndef _BAND_NRG_H
#define _BAND_NRG_H

#include "ffr.h"
#include "intrinsics.h"


void CalcBandEnergy(const Word32 *mdctSpectrum,
                    const Word16 *bandOffset,
                    const Word16  numBands,
                    Word32       *bandEnergy,
                    Word32       *bandEnergySum);



#endif
