/*
   Static bit counter
 */
#ifndef __STAT_BITS_H
#define __STAT_BITS_H

#include "psy_const.h"
#include "interface.h"

Word16 countStaticBitdemand(PSY_OUT_CHANNEL psyOutChannel[MAX_CHANNELS],
                            Word16 nChannels);

#endif /* __STAT_BITS_H */
