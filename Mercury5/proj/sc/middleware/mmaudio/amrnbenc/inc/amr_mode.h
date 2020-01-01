#ifndef _AMR_MODE_H
#define _AMR_MODE_H

/*
 * definition of modes for amr codec
 */
enum Mode { MR475 = 0,
            MR515,
            MR59,
            MR67,
            MR74,
            MR795,
            MR102,
            MR122,
            MRDTX,
            N_MODES     /* number of (SPC) modes, for amr decode */
};

#endif  // _AMR_MODE_H
