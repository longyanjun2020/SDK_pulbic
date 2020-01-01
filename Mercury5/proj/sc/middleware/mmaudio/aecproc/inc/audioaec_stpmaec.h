//
// #############################################################################
//
//                  <<< MSTAR SEMICONDUCTOR CONFIDENTIAL >>>
//
//    The information contained in this file is the property of MSTAR
//    SEMICONDUCTOR.  Except as specifically authorized in writing by
//    MSTAR SEMICONDUCTOR, the user of this file shall keep information
//    contained herein confidential and shall protect same in whole or in part
//    from disclosure and dissemination to third parties and use for internal
//    evaluation, operation or maintenance purposes within MSTAR SEMICONDUCTOR
//    only. Without prior written consent of MSTAR SEMICONDUCTOR, you may not
//    reproduce, represent, or download through any means, the information
//    contained herein in any way or in any form for a purpose other that the
//    use for internal evaluation, operation or maintenance within
//    MSTAR SEMICONDUCTOR.
//
//              (c) STEPMIND S.A.         2002-2006
//              (c) MSTAR SEMICONDUCTOR   2006-2010
//
//                          All Rights Reserved
//
// #############################################################################


// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
//  Module      :   Acoustic Echo Cancellation  (AEC)
//
//  File        :   STPMAEC.H
//
//  Description :   (test bench for) the AEC implementation, perhaps using the
//                  Win32 sound utilities for real-time assessment of the
//                  actual performances of the proposed scheme
//
//  Author      :   JL Dornstetter
//
//  Date        :   December 5, 2005
//
//  Reader      :   S.Gosne, please...
//
//  Evolutions  :   highly volatile (in construction)
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef __STPMAEC_H__
#define __STPMAEC_H__

/* ===== *
 * compiler options
 * ===== */

#ifndef TU
#define TU      0
#endif

#if defined(TU) && TU > 0
/* Kill next line to pass DropZone-TEST */
/*#include "ccure.h"*/
#else
#include "audioaec_ccstubs.h"
#endif

#define  TYPES_LAYOUT_WANTED

#include "audioaec_echosuppr.h"

// ============================================================================(
//                                   DEFINE
// =============================================================================
//
//  the AEC library itself doens't offer a lot of tuning, its unit test does
//  allow numerous knobs & spies...
#if defined(TU) && TU > 0

//  select the 'everything can be changed' option
# define  DESIGN_SETTINGS     TRUE

#else   //  !(defined(TU) && TU > 0)

//  we CCP_MESSAGE some details
# define CC_WARNING_REGARDING_WEIRD_OPTIONS  ON

//  retail code, remove most of the additional design fat
# define  DESIGN_SETTINGS     FALSE

#endif  //  defined(TU) && TU > 0


//  ------- 'semi-public', ECHO_CANCELLER_t::event() first argument  ---------
//  ------- i.e. monitoring hook events
//
#define AEC_EVT_OVFLCONV_MAX          (-2)    //  same as below but can't fix since
//  internal block floating point dynamic
//  is exhausted (would require <convShift>
//  dropping to 0 or even negative...)
//  May happen e.g. with zero reference

#define AEC_EVT_SCALE_IR_DOWN_FAILURE (-1)    //  all gains reached max, sorry...
//  highly unlikely (never seen) but
//  tested for code integrity

#define AEC_EVT_OVFLCONV                0     //  overflow within IR convolution
#define AEC_EVT_SCALE_IR_DOWN_1         1     //  IR shrunk, boosted input
#define AEC_EVT_SCALE_IR_DOWN_2         2     //  IR shrunk, boosted post-conv gain
#define AEC_EVT_SCALE_IR_UP             3     //  IR zoom-in since too small
#define AEC_EVT_HOWLING                 4     //  self-reset (divergence control)
//
//  Note  : the four events 0-3 happen on a regular basis when the environment
//  is learned and/or when it changes, and are part of the expected/normal flow
//  of the code. Only the last one represents an unexpected nuisance, and has a
//  small associated audio 'glitch'. The 'error' negative values are rarely seen
//  the -2 can happen with 'all-zero' reference, the other -1 remains unobserved

//  ------ AEC 'private' definitions, some shared between 'C' and 'ASM' ------
//  internal cooking / tweaking
//
//  controls whether the core routines accurately report saturation events
//  (actual bit-exactness is always enforced for the reference code, this one
//   is only used for the PC version, FALSE <=> faster code)
#define DEF_BIT_EXACT   TRUE

//  this switch controls whether we keep Impulse Response in 16 bits rather
//  than the 'comfortable' 32
#define TIGHT_STORAGE   TRUE    //  FALSE : 32 
//  TRUE  : 16
//  the comfortable option is qualified as of 2006, June 20
//  the 'tight' option is under robustness assessment, there is virtually no
//  breathing room left on each of these essential fields. Believed reliable
//  after lots  of fine tuning as of August 8

//  this switch controls the inclusion of reference source code for
//  the often called countLeadingZeros() utility. If you are absolutely
//  sure that your target machine does not offer any fast way to compute
//  such a thing, you may change this definition to OFF so as to emit the
//  miserably slow code found at the beginning of STPMAEC.C, but this is
//  really not recommended since any 'real CPU' offers a fast instruction
//  for this task, and we urge you to actually use it and provide the desired
//  fast routine whenever possible
//
#define CPU_SPECIFIC_CLZ32    (COMPILER!=MSVISUAL)   //  states that such an efficient function
//  is actually available to the linker

//  design fat-elimination : we want the cake and eat it i.e. keep the
//  flexibility of investigating what happens yet not add useless instructions
//  in the retail code. This is independant from the usual DEBUG settings, the
//  resulting algorithm becomes 'polymorphic at run-time' when defined, and has
//  a slower implementation :
//
#if !defined(__ASM)
# if !defined(DESIGN_SETTINGS) || DESIGN_SETTINGS != (DESIGN_SETTINGS*DESIGN_SETTINGS)
#   error "the DESIGN_SETTINGS symbol must be #define'd as TRUE or FALSE"
# endif
#else
# define  DESIGN_SETTINGS     FALSE  
#endif

//  The only run-time variable in the retail code is the IR depth parameter, all
//  other become hard-wired constants ...
#if DESIGN_SETTINGS

//  expand debug statement
# define DESIGN_SPECIFIC(text)  text

//  ... that are made dynamic during design fine-tuning conditions :
//  alias toward static integers in STPMAEC.C
# define  AEC_BKGND_CLEANUP SHIFT1            //  our last debug hint
# define  AEC_ORDER         aecOrder          //  tied to
# define  AEC_SMOOTH        aecSmooth         //    sliders

# define  SHIFT1            tuneInt1          //      for
# define  SHIFT2            tuneInt2          //        evaluation
# define  SHIFT3            tuneInt3          //          purposes
extern  uint  aecOrder,aecSmooth;           //  all declared in the test
extern  int   tuneInt1,tuneInt2,tuneInt3;   //  part of STPMAEC.C

//  integer overflow detection routines (detect : yes, 'fix' : no)
# define  mul32(x,y,i)     _mul32((S32)(x),(S32)(y),i,FILE_LINE)
S32     _mul32(S32 x,S32 y,int id,U32 fileLine);

# define  add32(x,y,i)      _add32((S32)(x),(S32)(y),i,FILE_LINE)
S32     _add32(S32 x,S32 y,int id,U32 fileLine);

# define  sub32(x,y,i)      _sub32((S32)(x),(S32)(y),i,FILE_LINE)
S32     _sub32(S32 x,S32 y,int id,U32 fileLine);

//  for spies Id's, currently Win32 specific...
/* Kill next line to pass DropZone-TEST */
/*# include "rsrc/resource.h"*/

#else //  !DESIGN_SETTINGS

//  i.e. the retail code
//
//  do not expand debug statements
# define DESIGN_SPECIFIC(text)

//  we are opinionated, aren't we ?
# define  AEC_BKGND_CLEANUP DEF_AEC_BKGND_CLEANUP //  all
# define  AEC_ORDER         DEF_AEC_ORDER         //  our
# define  AEC_SMOOTH        DEF_AEC_SMOOTH        //    default

//  too late for knit picking, fast zero-condom instructions wanted :
# define  mul32(x,y,i)      (((S32)(x))*((S32)(y)))
# define  add32(x,y,i)      (((S32)(x))+((S32)(y)))
# define  sub32(x,y,i)      (((S32)(x))-((S32)(y)))
//  type cast sometimes needed, else S16 * S16 => S16, not S32 ...

#endif  //  DESIGN_SETTINGS

//  these are design / compile-time constants
#define   AEC_AES_MAX_LATENCY      96   //  (fat) arrays behind this one
#define   AEC_AES_MAX_BKGND_N0  16384   //  boundary test only

//  magic 'howling threshold', reset decided when <spikes> over 1024
//  Note: <spikes> adds ratios of samples post versus pre-cancellation that
//        are above 4, so (exponential) divergence gets caught within a few
//        samples when not dealing with high local/mixed levels
#define   AEC_HOWLING_THRESHOLD 1024u

//  i.e. the retail code : we are opinionated, aren't we ? These are
//  close to best values, the AEC_ORDER and AEC_SMOOTH macros expand
//  as compile-time constants in the retail code to these values
#define   DEF_AEC_ORDER          4u           //  reasonable LPC order
#define   DEF_AEC_SMOOTH        10u           //   9  <=>  512 samples =  64 ms
//  10  <=> 1024 samples = 128 ms
#define   DEF_AEC_BKGND_CLEANUP 12u           //  12  <=> 4096 samples = 512 ms

#define   DEF_SHIFT1  DEF_AEC_BKGND_CLEANUP   //  maintenance period ~= 1/4 sec

//  these are reasonable default values to start from
#define   DEF_AES_LATENCY         64
#define   DEF_AES_ATTACK         256
#define   DEF_AES_DECAY           20
#define   DEF_AES_HOLD           600
#define   DEF_AES_ALPHA          512
#define   DEF_AES_BETA           384
#define   DEF_AES_BKGNDNOISE     128

#define AEONR2_SIM
#ifndef AEONR2_SIM

//  32 bit for the IR estimate is a small overkill. The main rationale for switching
//  to 16 bit is memory footprint but even more that on ARM you can use single-cycle
//  SMLA<x><y> substitutes to the standard two-cycles MLA instruction. Additional
//  benefit is that you can then put more loop un-rolling data in register cache, a
//  rare case where you can both have the cake and eat it.
#if TIGHT_STORAGE

//  how many samples are processed within one cycle
//  => batching factor, higher values improve overhead
//  We can afford quite high value here since the assembly-coded routines
//  packs pairs of coefficients / samples in one 32 bit register
# define  AEC_STRIDE_C      6                 //  these values are the larget possible
# define  AEC_STRIDE_U      10                //  (the ARM register count permitting)
# define  AEC_MULTIPLE      30                //  manually set to their least common
//  multiple in order not to pull intLcm()
//  into the final link
#else   //  !TIGHT_STORAGE

//  with large coefficients, we can only put one sample per register and use
//  the MUL/MLA core instructions through regular 'C' code, which limits our
//  ability to put a large number of fetched data in 'registers cache'
# define  AEC_STRIDE_C      4                 //  this is the best we can do
# define  AEC_STRIDE_U      4                 //  with every variable 32 bits wide
# define  AEC_MULTIPLE      4                 //  incredible...

#endif  //  TIGHT_STORAGE

#else

#define AEC_STRIDE_C    4
#define AEC_STRIDE_U    8
#define AEC_MULTIPLE    8

#ifndef __AEONR2__

typedef __int64         S64;

#define AEON_AMAC_ENABLE()

#else

typedef long long       S64;

#define AMACR_KEEP     16   // keep
#define AMACR_CLR       8   // clear
#define AMACR_RND       4   // round
#define AMACR_SAT       2   // saturate
#define AMACR_SHR       1   // shift

#define AEON_AMAC_ENABLE() { int val=1; asm volatile("b.mtspr1 %0,0x280D"::"r"(val)); }

#endif

#endif//AEONR2_SIM

//  We tried several implementation of the LPC enhancement, only two survived
//  the various tests. One is symmetrical since it whitens the reference signal
//  twice the 'minimum phase' way, it then has a delay of L samples where <L>
//  is the LPC prediction order. The doubly-whitened reference (DWR) is kept in
//  addition to the orignal, the regular Widrow update is performed using the
//  DWR and the current residual. In the non-delayed version, we use simple
//  whitening on both the reference and the residual signal, using this pair
//  of signals for the Widrow update cycle. Pros & cons :
//
//    DELAYED seems to have less 'hiss' than the other one (?)
//
//    !DELAYED has a slightly smaller memory footprint, looks more robust
//
#define   DELAYED          FALSE  //  FALSE TRUE
//  this is a significant algorithmic tweak, see STPMAEC.C for the details


//  ASM routines refer to these values which we check within aecBoot()
#if DELAYED
# define  sizeOf_CELL_t       20
#else
# define  sizeOf_CELL_t       16
#endif  // DELAYED

#define cellOffset_rho         0
#define cellOffset_w2          4
#define cellOffset_refMem      8


//  ECHO_CANCELLER_t layout
#define aecOffset_ir           8
#define aecOffset_whiteStride 16
#define aecOffset_irDepth     20
#define aecOffset_dampedSets  22


//  the rest is not assembler-friendly, so :
#if !defined(__ASM)
// =============================================================================
//                                   TYPES
// =============================================================================
//
#define CC_RTTSIG_ECHO_CANCELLER_t                                 0xB5845E79
dbgStronglyTyped(ECHO_CANCELLER_t);
typedef struct ECHO_CANCELLER_s  ECHO_CANCELLER_t;

//  type / dynamic range for internal variables
typedef   S16                 WHITE_TYPE_t;   //  quite comfortable, could be packed
//  into 8 bits provided that some further
//  re-alignment housekeeping code. Not
//  provided because this would go against
//  16 bit speedup available on ARM, but
//  a viable option would memory footprint
//  prove essential, not speed

#if TIGHT_STORAGE
typedef S16               IR_TYPE_t;        //  extremely tight, no room for mis-scaling
#else   //  !TIGHT_STORAGE
typedef S32               IR_TYPE_t;        //  ample margin (helps dynamic range)
#endif  //  TIGHT_STORAGE


//  ----------------------------------------------------------------------------
//
//  Name    : AEC_REPORT_t
//
//  Purpose : a simple set of counters that provide some hint reagrding what
//            happened in the life of an EAC object
//
//  Usage   : embeeded within ECHO_CANCELLER_t, returned by aecGetReport()
//
typedef struct AEC_REPORT_s
{
    U32           ovflClean;    //  the echo substraction went out of the 16 bit range
    U16           ovflConv;     //  counts aecFastRefIrConvolve() returning TRUE
    U16           satUpdate;    //  counts aecFastIrUpdate()        "         "
    U16           undflIr;      //  counts the number of times we decided to
    //  zoom-in the IR internal representation since it
    //  was too small/tiny
    U16           howling;      //  counts the number of 'self-reset' sad events
}AEC_REPORT_t;


//  ----------------------------------------------------------------------------
//  The internals aren't needed, they are put here because our GUI test code
//  needs to cheat / access everything, so it has to access the 'private' members
//  The only legitimate #defin'ition for TYPES_LAYOUT_WANTED is within the
//  STPMAEC.C implementation itself, in addition to the test / cheat code
#if defined(TYPES_LAYOUT_WANTED)
//  ----------------------------------------------------------------------------
//
//  Name    : CELL_t
//
//  Purpose : this gather all the data pertaining to one cell of our double
//            whitener, which has one 'active' learning branch named <ref> and
//            one passive path named <residual>. The LPC engine is driven by
//            its upper <ref> branch, it performs whitening using the same
//            coefficients on its other path
//
//  Inside  : the update logic for one cell, depicted as follows
//
//                             +
//                in1  -->------S-->- out1
//                         \   /-
//                          \ /                   <S> : the 'Sum' operation
//                        R  X
//                          / \                   <R> : the <ro> reflection
//              o-----o    /   \-                       coefficient
//              | in2 |-->------S-->- out2
//              o-----o        +
//
//            is based on simple algebra : <in2> here is <refMem> and one
//            can observe that in the ideal world
//
//                 out2*in1 + out1*in2       2*in1*in2
//            D =  ------------------- = -----------------  -  <ro>
//                  in1*in1 + in2*in2    in1*in1 + in2*in2
//
//            Our update equation for maintaining the <ro> estimate not too
//            far from the wanted correlation coefficient (the expectation of
//            the first ratio in the above right-hand-side) is to set
//
//                        out2*in1 + out1*in2
//              <ro>  +=  -------------------
//                               2^d
//
//            where the number <d> in the denominator is such that it is roughly
//            greater by the wanted memory factor than the power sum :
//
//               (in1*in1 + in2*in2).2^m <= 2^d < (in1*in1 + in2*in2).2^(m+1)
//
//            This calls for the approximate log in base 2, a fast function on
//            the ARM machnine thanks to the CLZ instruction. Here the 2^m
//            number is roughly a memory forgetting factor that we set to the
//            value 256 (about 32 ms @ 8Ks/s)
//
typedef struct CELL_s
{
    S32     rho;        //  the actual reflection coefficient, in S0.31 format

    U32     w2;         //  smoothed guestimate of the current cell's input power

    S32     refMem;     //  the memory cell for the training / master path
    S32     locMem;     //    "         "   for the cleaned local passive / slave path
    S32     echoMem;    //    "         "   for the echo estimate
# if DELAYED
    S32     resMem;   //  ditto for the doubly whitened passive / slave path
# endif
}CELL_t;


//  ----------------------------------------------------------------------------
//
//  Name    : AES_t
//
//  Purpose : state variables for the NLP / AES function
//
#if !defined(_USE_NEW_AES_)

#define AEC_AES_QUEUE   64

typedef struct AES_s
{
    S32           lpFilterSum,lpFilterMem[4];
    uint          lpIndex;
    U32           indexDist, queueDist [AEC_AES_QUEUE];
    U32           maDistSum, maDistMem [AEC_AES_MAX_LATENCY];
    U32           maLocalSum,maLocalMem[AEC_AES_MAX_LATENCY];
    U32           maEchoSum, maEchoMem [AEC_AES_MAX_LATENCY];
    U32           bkgndNoise;
    S32           nsTest;
    uint          maIndex,latency;
    S16           clean[AEC_AES_MAX_LATENCY];
    uint          clIndex;
    S32           alpha,beta;
    S32           clipSum,bottomVal;
    int           timer,ramp,boost,attack,decay,hold;
    U8            aesEnable;    //  global NLP/AES flag
}AES_t;

#endif
//  ----------------------------------------------------------------------------
//
//  Name    : ECHO_CANCELLER_t
//
//  Purpose : gather all nasty details required to make an AEC work
//
struct ECHO_CANCELLER_s
{
    //  The code below doesn't have hard-wired parameters, variable-length arrays
    //  are at stake here : we store pointers and ask the caller to allocate the
    //  object with enough room, we compute adequate positioning once in aecInit()
    //
    //  Note that many buffers are over-dimensioned by the batching factor
    //  AEC_STRIDE in order to allow 'early new values writes', which helps the
    //  register allocation on ARM / RISC, helping register starvation avoidance...
    //
    //  This extra padding is not necessarily used by reference routines, which are
    //  left as part of the source code for future changes and your information, the
    //  dimensions e.g. aecSizeOf() and aecInit() are determined by the actual
    //  worst case i.e. the retail code with obscure unrolled loops...
    //
    S16          *ref;          //  the past reference (distant signal) samples
    //  circular with count <irDepth> + AEC_STRIDE_C

    uint          refStride;    //  index of the current stride within the above
    //  <ref> buffer where we gather a new batch of
    //  incoming samples, always a multiple of the
    //  AEC_STRIDE_C batch figure, and always within
    //  [0,<irDepth>] including bounds

    IR_TYPE_t    *ir;           //  the impulse response estimate, count <irDepth>
    //  type is S32 (regular) or S16 (TIGHT_STORAGE)

    WHITE_TYPE_t *white;        //  [doubly-]whitened reference, circular with
    //  count <irDepth> + AEC_STRIDE_U

    uint          whiteStride;  //  similar to <refStride> but with respect to
    //  the <white> circular buffer with AEC_STRIDE_U
    //  as granularity

    U16           irDepth;      //  constructor parameter, we manage to round it so
    //  that it becomes a multiple of both AEC_STRIDE_C
    //  and AEC_STRIDE_U

    U16           dampedSets;   //  the number of different damping factors
    //  used within aecFastIrUpdate(). This is
    //  used by the ARM assembly routine to perform
    //  dynamic stack allocation a la alloca()
    //  Actual value stored here relates to the
    //  number D of distincts sets as follows :
    //
    //  D = (15+irDepth/AEC_STRIDE_U)/16
    //                           (10)
    //  dampedSets  = D*sizeOf(S16)*AEC_STRIDE_U
    //
    //  in other words, it is the memory footprint
    //  of the complete (i.e. including the original)
    //  damped coefficient sets in  S16 packed format
    //  and its order of magnitude is given by
    //
    //    <irDepth> / 8

    U16           allocSlots;   //  we put here within aecInit() the number of
    //  AEC_MULTIPLE for which room was allocated

    //  --- end of struct members that are accessed by low-level ASM routines
    //  --- and therefore conveniently put at the beginning of the structure

    S16           spikes;       //  anti-howling parameter
    //  -- when 'calm', += roughly the over-ratio
    //  when the 'cleaned' signal is way bigger that
    //  the original, a KISS yet efficient logic

    U16           refBacklog;   //  small index between 0 and AEC_STRIDE_C - 1
    U16           deltaBacklog; //  same, but between 0 and AEC_STRIDE_U - 1
    //  both used during the batch accumulation
    //  respective 'idle' periods

# if  DELAYED                 //  lag re-alignment variables
    U8            lagIndex;     //  position within the <residue> above buffer


    S16          *residue;      //  a small buffer to compensate for the doubly
    //  whitened signal lag due to LPC backward delay
    //  circular with count AEC_ORDER, only useful
    //  with the DELAYED alternate method
# endif //  DELAYED

    //  scaling dirty variables...
    uint          splRank;      //  smart startup convergence acceleration

    U8            smooth;       //  gradually increased from 0 to AEC_SMOOTH with
    //  profile log2(splRank)

    U8            refShift;     //  reference signal '>>r' derating before storage
    //  within <ref> array. Stays in [0,15] range

    U8            convShift;    //  output of aecFastRefIrConvolve() '>>g' derating
    //  for the echo calculation. Guaranteed to remain
    //  in the [1,31] range

    U8            useLpc;       //  simple flag that controls the method to be used
    //  within the echo canceller. Currently FALSE except
    //  under some investigation exercise

    uint          watts;        //  running sum of distant dB's, a weird way to
    //  lower the <eps> below toward its bottom value

    uint          threshold;    //  this enables a fake division using a couple
    //  comparisons instead of a costly '/'

    S16           bottomEps;    //  the final vlaue of the step parameter
    //  resonnable range looks like
    //  [4096,16384]  for the standard LPC option
    //  [512,2048]   for the alternate non-LPC case

    S16           eps;          //  the current value for the step parameter, starts
    //  from high values, lowered as more distant signal
    //  is fed into the engine

    //  'lazyness' control, which provides a run-time trade-off between convergence
    //  speed and CPU burden. This uses a rather smart scheme that selects the most
    //  significant subset of the IR updates and only performs the most important
    //  update cycles. The algorithm is detailed within aecWorkload()
    //
    U32           medianPoint;  //  the current selection threshold

    U8            incrDelta;    //  we add (incrDelta * medianPoint) >> shiftDelta
    //  when we perform some 1.25 ms IR update. Value 0
    //  means that we always perform the update (100% busy)

    U8            decrDelta;    //  we substract (decrDelta * medianPoint) >> shiftDelta
    //  when skipping an IR update

    U8            shiftDelta;   //  the shift factor in the above equations, which
    //  governs the memory of the scheme

    //  scaling is definitely a delicate matter, max-hold logic proved both
    //  fast and robust, the code gimmick being always the same, these are
    //  all squared values :
    U32           peakDist;     //  distant residual peak, the normal denominator
    //  for the normalisation process

    U32           peakMix;      //  the original mixed signal, used for the
    //  'howling' (aka divergence) detection

    U32           peakLoc;      //  the reference-whitened mixture, used as a
    //  'soft-decision' DTD substitute, the cross-
    //  whitening trick improves its sensitivity
#if defined(_USE_NEW_AES_)
    echosuppr_t   echosuppr;
#else
    AES_t         aesState;     //  NLP post-processing variables
#endif
    //  monitoring callback and counters
    void        (*event)
        (
        int               event,    //  one of the above AEC_EVT_xxx
        ECHO_CANCELLER_t *thisOne   //  this object
        );

    AEC_REPORT_t  counters;     //  a few counters to be sampled whenever the
    //  owner see fit...

    DBG_RUN_TIME_TYPE           //  late in the stucture whenever possible

    S16           mixBuf[AEC_STRIDE_C]; //  mixed signal accumulated here during
    //  the 'just store' period, index is
    //  the <refBacklog> member

    S16           deltas[AEC_STRIDE_U]; //  the small set of d0,d1,d2...d9 that
    //  will be used for the batch update
    //  of the <ir> vector, index is the
    //  <deltaBacklog> member

    CELL_t        lpCells[1];   //  [1] dim is dumb here, actually the
    //  AEC_ORDER stages state variables

    //  ----  buffers actually located hereafter :  ----
    //  ----            ref[]                       ----
    //  ----            ir[]                        ----
    //  ----            white[]                     ----
    //  ----            residue[]                   ----
};  //  ECHO_CANCELLER_t

#endif // defined(TYPES_LAYOUT_WANTED)


// =============================================================================
//                              (debug) DATA
// =============================================================================
//
#if DESIGN_SETTINGS
//  watching some vanilla counters helps human correlation between audio
//  glitches and their root cause, rather volatile assignment
extern int sat1,sat2,spy1,spy2,spy3,spy4,spy5,spy6,spy7,spy8,spy9,spy10;
#endif  //  DESIGN_SETTINGS


// )===========================================================================(
//                                SERVICES
// =============================================================================
//
START_PROTO


//  ----------------------------------------------------------------------------
//
//  Name    : aecSizeOf
//
//  Purpose : return the required object size in bytes for an echo canceller
//            with the specified echo cancellation window, keeps the actual
//            genetics opaque and makes this package agnostic w.r.t. the actual
//            memory allocation engine.
//
//  Args    : <irDepth> : the desired 8 Ks/s echo cancellation depth as
//                        expressed in samples.
//
//  Return  : the object size to be allocated and passed to aecInit()
//
//  Inside  : the returned value varies somewhat with debug and DELAYED options
//            but the bottom line is that the returned value is roughly equal to
//
//              memory footprint ~= 256 + 6 x irDepth
//
//            in the retail version i.e. with TIGHT_STORAGE set to TRUE.
//
//            It is wise not to use values for <irDepth> that approach the
//            size of your data cache since there are other hidden parts of
//            the memory working set e.g. the temporary stack array within
//            the ASM aecFastIrUpdate() routine, which amounts to another
//            <irDepth> / 8 so that you definitely need some margin here.
//
//            For example, setting <irDepth> to 1020 (i.e. 127.5 ms) results
//            in 'visiting' the frenetic way at least 6.6 kb of memory, not
//            including the caller's stack/locals area. The value 1200 which
//            corresponds to 150 ms of echo capability is probably the ultimate
//            value that does not result in catastrophic 8 kb data cache misses.
//
//            The code footprint is around 2.5 kb and should not be a severe
//            issue on a 'normal ARM-9E' having a separate 8 kb code cache.
//
PUBLIC  int  aecSizeOf(uint irDepth);


//  ----------------------------------------------------------------------------
//
//  Name    : aecInit
//
//  Purpose : initial setup for an ECHO_CANCELLER_t object
//
//  Usage   : see above aecSizeOf(). It is legal to aecInit() the same object
//            more than once
//
//  Args    : <aec>           : the object to initialize, it must satisfy the
//                              usual memory alignment constraints and offer 
//                              write access on aecSizeOf(aecWindowSize) bytes
//
//            <aecWindowSize> : the Impulse Response (IR) length, which must be
//                              less or equal to the value used to determine the
//                              required footprint
//
//            <eps>           : a dirty parameter with imprecise semantics that
//                              trades convergence speed (the higher, the fastest)
//                              against accuracy / echo cancellation depth as
//                              well as amount of non-linear artifacts (the
//                              smaller, the deepest / most accurate / less
//                              annoying intermod-like audio nuisance)
//
//                              Values above 10000 lead to audible acoustic
//                              pain, values below 1000 to noticeably slow
//                              re-convergence when the acoustic echo conditions
//                              actually change. Recommended value for the time
//                              being is about 4000.
//
//                              Note : this is not really desirable to have this
//                              parameter assigned here. It may prove desirable in
//                              future versions to have this stuff automatically
//                              adjusted according to the currently estimated ERL
//                              rather than hard-wired to this asymptotic value.
//                              The reason for not having this in this first
//                              release is that we had already enough intricately
//                              coupled feedback mechanisms, adding one more
//                              would have made the overall testing process even
//                              more complicated.
//
//            <aesEnable>     : a simple flag that activates (if TRUE) the
//                              built-in Acoustic Echo Suppression, aka NLP
//                              in the popular ITU-related jargon. What is done
//                              here is just to attenuate in a smart way the
//                              cleaned-up local signal when the distant seems
//                              active and the local seems not.
//
//  Return  : the returned <bytesBag> with the correct type and the same
//            physical address e.g. you can 'forget' <bytesBag> and free() the
//            returned beast
//
//  Inside  : the memory allocation is up to the caller, this makes this call
//            independant of the actual allocation engine.
//
#define aecInit(a,d,e)      _aecInit(a,d,e,FILE_LINE)
#define aecInit_(a,d,e)     _aecInit(a,d,e,_fileLine_)
#define _aecInit(a,d,e,fl)  __aecInit(a,d,e _FL(fl))

PUBLIC  ECHO_CANCELLER_t *__aecInit(void *bytesBag,uint irDepth,
                                    int eps _cp_fileLine_);


//  ----------------------------------------------------------------------------
//
//  Name    : aecReset
//
//  Purpose : make the target object forget anything from its past life
//
//  Usage   : to be called when it is known that the audio environment has
//            changed from the AEC standpoint e.g. the speaker path was just
//            switched on etc...
//
PUBLIC void aecReset(ECHO_CANCELLER_t *aec);


//  ----------------------------------------------------------------------------
//
//  Name    : aesConfigure
//
//  Purpose : commit new settings for the NLP part of the AEC
//
//            roughly speaking, an instantaneous 'local talking' decision is
//            based on a formula like
//
//              |local|  >    alpha . |echo estimate|
//                          + beta  . |reference|
//                          + backgroundLevel
//
//            and the three numbers <alpha>, <beta> and <backgroundLevel> are
//            set by this call. The |magnitude| values are obtained via a moving
//            average process over some <latency> period, the instantaneous
//            decisions being then integrated with distinct <attack> and <decay>
//            rates, with a kind of <hold> timer when reaching a convincing
//            local talk state
//
//  Args    : <aec>         : the device pointer
//
//            <enable>      : a simple BOOL flag with the obvious semantics
//                            all arguments below ignored when FALSE
//
//            <latency>     : a value in the [16 .. DEF_AES_MAX_LATENCY (96)]
//                            range, units being 8 kHz samples (125 mics)
//
//            <alpha>       : numbers in the [16..16384] range that controls
//            <beta>        : the relative local / distant levels for which the
//                            AES will hesitate / stay near 50% gain. Ratio
//                            is in absolute amplitude (not power) with the
//                            neutral point (i.e. equal powers) set at 1024.
//
//                            <alpha> weights the estimated echo magnitude and
//                            <beta> weights the reference magnitude, both of
//                            which are considered 'distant', although the first
//                            term scales with the IR level while the second
//                            does not. Selecting 2048 instead of 1024 will raise
//                            the equilibrium point from |local| ~= |distant| to
//                            |local| ~= 2*|distant|, opening the AES gate
//                            at |local| signal levels that are 6 dB higher
//                            compared to the reference 1024 case.
//
//            <bkgndNoise>  : a number in the [1..16384] range, acts as an
//                            absolute magnitude below which local signals are
//                            not considered useful speech: high values will
//                            prevent AES to open the gate for small signals
//                            with the risk of cutting low level utterances
//                            (benefit being that the AES reduction factor
//                             will remain small in more creepy conditions)
//
//            <attack>      : integrator's charge rate, add this amount to
//                            a [0,65535] clipped sum each time we believe the
//                            local signal is bigger than the distant signal.
//                            Legal range is [1..8192], reasonable value seems
//                            around 200 to 300.
//
//            <decay>       : integrator's leak, subtract this amount to the
//                            said sum each time we believe the distant signal
//                            dominates the local one. Legal range [1..512],
//                            numbers like 10 to 30 seem fine.
//
//            <hold>        : a timer in 8 kHz samples count is started when
//                            the clipped sum reaches its max 65535, leak being
//                            then disabled for this number of samples. Legal
//                            range is [0..4000]. A value of 0 is allowed and
//                            disables this weird feature. Decent values are
//                            something around 600 to 800 <=> 100 ms.
//
//            <minGain>     : a number in [0..256] with a logarithmic shape
//                            that represents the bottom value for the AES
//                            attenuation factor. 16 units represent 6 dB of
//                            dynamic range and 0 corresponds to complete shut
//                            off for the return signal. The maximal attenuation
//                            of the AES is given below for some values
//
//                              <minGain>    max AES attenuation
//                                256              -6 dB
//                                240             -12 dB
//                                224             -18 dB
//                                208             -24 dB
//                                192             -30 dB
//                                 .                .
//                                128             -54 dB
//                                 .                .
//                                 0             -Inf dB
//
//  Return  : TRUE iff all parameters were found in their legal range. When
//            returning FALSE, the AES is indeed disabled as a (wanted) side
//            effect of the error detection checks
//
//  Inside  : when <enable> is FALSE, the AEC has almost zero latency (the
//            actual latency may be non-zero if optimized ASM routines use
//            batching i.e. AEC_STRIDE_C > 1 but this is not a structural
//            attribute of the device per se). When <enable> is TRUE, the
//            output latency is increased by the <latency> value, which is not
//            required to bear any special relationship with respect to the
//            convolution batching factor AEC_STRIDE_C.
//
PUBLIC BOOL aesConfigure( ECHO_CANCELLER_t   *aec,
                         BOOL                enable,
                         int                 latency,
                         int                 alpha,
                         int                 beta,
                         int                 bkgndNoise,
                         int                 attack,
                         int                 decay,
                         int                 hold,
                         int                 minGain);

//  ----------------------------------------------------------------------------
//
//  Name    : aecWorkload
//
//  Purpose : control the CPU burden / convergence speed trade-off of the AEC
//
//  Args    : <busyControl> : a value within [0,255] with the following meaning
//
//              0   : complete freeze of the current IR estimate
//            255   : normal behaviour, the IR estimate is refined according to
//                    all of the available samples
//
//            other : the average CPU consumption devoted to the IR update is
//                    rougly equal to a fraction X = N / 255 of what it normally
//                    should be. The AEC uses a clever selection method aiming
//                    at the determination of the most significant fraction X of
//                    the IR updates that should actually be performed
//
//            <memory> : a value in milliseconds that specifies the typical
//                    period of time among which the outcome of the selection
//                    process should ressemble the specified workload factor.
//
//                    Setting this to a large value makes the actual CPU load
//                    be what you want it to be on average ***over this
//                    specified long period*** : don't be surprised if the
//                    cycles consumption remains equal to the maximum during
//                    three seconds if you passed 8191 as <memory>...
//
//                    The routine returns FALSE beyond the already too large
//                    value of 8191 or below the ludicrously small 20
//
//  Usage   : general purpose, aecInit() performs a call to aecWorkload(255)
//
//  Return  : TRUE iff the parameters were reasonable
//
//  Inside  : the selection process works as follows. Suppose, for the sake of
//            the explanation, that we have <busyControl> = 128, in other words
//            we target an average 50 % duty cycle for the IR update burden.
//
//            The ARM CPU cycles consumption for a window of L taps is rougly
//            equal, on a per-125 us sample basis, to the following number
//
//              #ARM cycles / sample ~= 500 + 3 x L
//
//            The 3 cycles per {tap x sample} is dispatched inside the AEC code
//            as follows:
//
//              3   =   1.23    +   1.75
//
//            where 1.23 is the time needed to actually compute the estimated
//            echo via aecFastRefIrConvolve(), and 1.75 is what we spend on
//            average updating the IR estimate.
//
//            What <busyControl> changes is the above '1.75' load factor. You
//            cannot save anything on the fixed cost (the above '500') nor on
//            the 1.23 x L convolution part. The table below gives the total
//            CPU burden (also as a fraction of its maximum value) for some
//            values of the parameters :
//
//        +--------------------------------------------------------------------
//        | L (taps/ms)|    240/30        480/60       810/101      1020/128
//        |\---------\ +-------------------------------------------------------
//        |busyControl\|       ARM - MIPS ( % of the max / first line)
//        +------------+- - - - - - - - - - - - - - - - - - - - - - - - - - - -
//        |   256      | 9.8 (100 %)   15.5 (100 %)  23.4 (100 %)  28.5 (100 %)
//        |            |
//        |   192      | 8.9 (91.4%)   13.8 (89.2%)  20.6 (87.9%)  24.9 (87.5%)
//        |            |
//        |   128      | 8.1 (82.8%)   12.2 (78.4%)  17.8 (75.8%)  21.3 (74.9%)
//        |            |
//        |    64      | 7.2 (74.2%)   10.5 (67.5%)  14.9 (63.7%)  17.8 (62.4%)
//        |            |
//        |     0      | 6.4 (65.6%)    8.8 (56.7%)  12.1 (51.6%)  14.2 (49.9%)
//        +------------+-------------------------------------------------------
//
//            It is of course not recommended to stay at <busyControl> = 0 for
//            a long period of time except if you know that things are in
//            rather severe trouble...
//
//            Experiments seem to indicate that little degradation in the actual
//            convergence time occurs for <busyControl> above 50%, and that it
//            remains perfectly decent down to 25%, the real degradation starting
//            to manifest itself below this level
//
PUBLIC BOOL aecWorkload(ECHO_CANCELLER_t *aec,uint busyControl,uint memory);


//  ----------------------------------------------------------------------------
//
//  Name    : aecEchoSubstract
//
//  Purpose : process a single couple of incoming samples
//
//            given reference samples named <refSample> and mixed signal
//            samples <mixedSample>, update the ECHO_CANCELLER_t state according
//            to the rules as specified below and return the <clean>ed signal
//
//  Args    : <clean>       : OUT, the mixed signal minus the (removed ?)
//                            guestimated echo. This return array must have at
//                            least AEC_STRIDE positions with write access rights
//
//            <aec>         : IN/OUT, the master AEC object
//
//            <refSample>   : IN, the distant signal that fuels the loudspeaker
//                            eventually producing an echo
//
//            <mixedSample> : IN, the local / microphone signal which is
//                            supposedly the sum of the local speaker's voice
//                            plus some to-be-cancelled echo due to the
//                            <refSample> stream flowing through the loudspeaker
//                            back into the microphone through the reverberating
//                            environment
//
//                            =>  these two IN streams must be synchronous i.e.
//                                they should be time-aligned : in the limit case
//                                of the loudspeaker set back-to-back with the
//                                microphone, we expect <mixedSample> to be
//                                directly proportional to <refSample>
//
//            <audio>       : dev DESIGN_SETTINGS only, provides debug feedback
//                            for 12 distinct points within the processing chain
//                            (see below for index assignments)
//
//  Return  : an integer between 0 and AEC_STRIDE_C inclusive, telling how many
//            echo-cancelled samples were delivered to the <clean> output array
//            For regular batching strategies, the return pattern is periodic
//            e.g. 0,0,0,4,0,0,0,4 etc... but the exact behaviour isn't
//            specified by this interface, leaving such degree of freedom, at
//            the cost of a small latency, allows some internal batching
//            optimizations
//
//  Usage   : this is the main user-level call, present on the nominal audio
//            signal path, you must live with the AEC_STRIDE_C output latency
//            which proved necessary in order to get the most of the ARM-E core
//
//  Inside  : the state update comprises the following sub-steps, which are
//            performed in small batches that are done 'asynchronously' i.e.
//            a 'stride' of a few simlar operations are done in a single call
//            to a dedicated optimized routine
//
//            (a)   compute the estimated echo using the current value of the IR
//                  and the current + past values of the reference signal
//
//            (a')  substract it to the current mixed signal to get the residual
//                  i.e. 'echo-cleaned' useful result
//
//            (b)   use the current residual and the current + past reference
//                  signal to add a small update to the <delta> IR member of the
//                  ECHO_CANCELLER_t state
//
//            When performing a batch of (a) and (a') above, the returned value
//            is non-zero. The (b) operation is sometimes (rarely) replaced by
//            a routine maintenance pass through the IR estimate aiming at the
//            monitoring of 'underflow' and the implementation of some dirty
//            'return-to-zero' policy that helps keeping accumulated rounding
//            noise ending in 'uncontrolled' hidden vectors in the null-space of
//            the overall feedback system in control. Such a rare maintenance
//            step would be the ideal place where to perform regularized LMS
//            since at the end of the day such a thing amounts to a rather
//            trivial first order memory a la 'estimatedIr *= (1-epsilon)'
//            but with painfully small <epsilon> so that the right way to do
//            such things is to perform the said step once every N samples but
//            with N times a greater <epsilon>, for a roughly equivalent result
//
#define aecEchoSubstract(c,a,r,m,e)     _aecEchoSubstract(c,a,r,m,e,FILE_LINE)

#if DESIGN_SETTINGS
//  pass additional arguments
# define _aecEchoSubstract(c,a,r,m,e,fl) __aecEchoSubstract(c,a,r,m,e _FL(fl))
PUBLIC int  __aecEchoSubstract(S16               clean[AEC_STRIDE_C],
                               ECHO_CANCELLER_t *aec,
                               S16               refSample,
                               S16               mixedSample,
                               S16               audio[12*AEC_STRIDE_C]
//  12.N+0 : echo
//  12.N+1 : cleaned signal before AES
//  12.N+2 : doubly white distant (DELAYED only, else same as [2])
//  12.N+3 : simply white distant ([1] a copy of this one #if !DELAYED)
//  12.N+4 : white local
//  12.N+5 : peak whitened distant
//  12.N+6 : peak whitened residual
//  12.N+7 : AES attenuation ratio
//  12.N+[8..11] : future extensions
_cp_fileLine_);
#else //  !DESIGN_SETTINGS
//  no secondary <audio> return
# define _aecEchoSubstract(c,a,r,m,e,fl) __aecEchoSubstract(c,a,r,m _FL(fl))
PUBLIC int  __aecEchoSubstract(S16               clean[AEC_STRIDE_C],
                               ECHO_CANCELLER_t *aec,
                               S16               refSample,
                               S16               mixedSample
                               _cp_fileLine_);

#endif  //  DESIGN_SETTINGS

/***************************************************************************
* Name    : aecClipRefPcm()
* Purpose : clip reference pcm for analog saturation
* Args    : <refSample> : pointer of reference pcm need clipping
*           <clipLevel> : level of reference clipping
*           <lenSample> : sample count need to process
***************************************************************************/

PUBLIC void aecClipRefPcm(S16*    refSample,
                          S16     clipLevel,
                          S32     lenSample);

//  ----------------------------------------------------------------------------
//
//  Name    : aecGetReport
//
//  Purpose : make simplistic counters available to the owner of an AEC
//
//  Usage   : general purpose, AEC_REPORT_t is public whereas the internals
//            of ECHO_CANCELLER_t are better kept opaque
//
PUBLIC  AEC_REPORT_t *aecGetReport(ECHO_CANCELLER_t *aec);


//  ----------------------------------------------------------------------------
//
//  Name    : aecResize
//
//  Purpose : 'on-the-fly' change of the echo cancellation IR depth.
//
//  Usage   : This call is available at any time, it only involves a moderate
//            memory moving burden and does not imply any significant audio
//            'glitch'. If the depth is increased, audio continuity is 'perfect'
//            and if it is shortened, the discontinuity is tolerable provided
//            that the 'cut' part of the impulse response did not have too much
//            weight w.r.t. the remaining part, the residual echo being
//            immediately increased due to the instantaneously shortened IR.
//
//  Return  : -1 if you attempt to resize it to a value smaller than the
//            absolute minimum of AEC_MULTIPLE or beyond the allocated size as
//            determined during aecInit(), else the new number of active taps
//            which is rounded down to a multiple of AEC_MULTIPLE
//
//            Would -1 be returned, no change to the target object's state
//            is performed, you may have to inspect the <irDepth> member in
//            order to retrieve the actual current size
//
PUBLIC int aecResize(ECHO_CANCELLER_t *aec,uint newSize);


//  ----------------------------------------------------------------------------
//
//  Name    : aecBoot
//
//  Purpose : the usual 'call-once' routine
//
#if (defined (CCF_REG)) || (COMPILER == GHS && DBGF_ASSRT)
# define  aecBoot()     _aecBoot(FILE_LINE)
# define  _aecBoot(fl)  __aecBoot(_VFL(fl))
PUBLIC  void          __aecBoot(_p_fileLine_);
#else
# define  aecBoot()     VACUUM(0)
#endif  //  CCF_REG || (COMPILER == GHS && DBGF_ASSRT)

END_PROTO

#endif // !defined(__ASM)

#endif  //  __STPMAEC_H__
// ****************************************************************************)
//
//  End of file STPMAEC.H
//
