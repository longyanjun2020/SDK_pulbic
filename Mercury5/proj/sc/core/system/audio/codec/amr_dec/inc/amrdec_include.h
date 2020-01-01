#ifndef AMRDEC_INCLUDE
#define AMRDEC_INCLUDE

#define MAX_PRM_SIZE    57     /* max. num. of params                      */
#define MAX_SERIAL_SIZE 244    /* max. num. of serial bits                 */

#define AMR_L_FRAME      160       /* Frame size                               */
#define EHF_MASK 0x0008        /* encoder homing frame pattern             */

/*
*****************************************************************************
*                         DEFINITION OF DATA TYPES
*****************************************************************************
* Note: The order of the TX and RX_Type identifiers has been chosen in
*       the way below to be compatible to an earlier version of the
*       AMR-NB C reference program.                                   
*****************************************************************************
*/

enum RXFrameType { RX_SPEECH_GOOD = 0,
                   RX_SPEECH_DEGRADED,
                   RX_ONSET,
                   RX_SPEECH_BAD,
                   RX_SID_FIRST,
                   RX_SID_UPDATE,
                   RX_SID_BAD,
                   RX_NO_DATA,
                   RX_N_FRAMETYPES     /* number of frame types */
};


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


#endif
