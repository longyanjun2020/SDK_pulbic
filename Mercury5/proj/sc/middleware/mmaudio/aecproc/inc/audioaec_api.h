
#ifndef _AUDIOAEC_API_H_
#define _AUDIOAEC_API_H_

#define AUDIO_AEC_BLOCK     32

typedef struct echo_canceller_config_t
{
    /* Adaptive Filtering Settings */
    int     adp_filter_fir_depth;     /* default : adp_filter_fir_depth       240   */
    int     adp_filter_lim_step_size; /* default : adp_filter_lim_step_size   5000  */
    /* Echo Suppressor Settings */    
    int     echo_suppr_enable;        /* default : echo_suppr_enable          1     */
    int     echo_suppr_latency;       /* default : echo_suppr_latency         64    */
    int     echo_suppr_alpha;         /* default : echo_suppr_alpha           512   */
    int     echo_suppr_beta;          /* default : echo_suppr_beta            384   */
    int     echo_suppr_bkgn_noise;    /* default : echo_suppr_bkgn_noise      128   */
    int     echo_suppr_attack;        /* default : echo_suppr_attack          256   */
    int     echo_suppr_decay;         /* default : echo_suppr_decay           20    */
    int     echo_suppr_hold;          /* default : echo_suppr_hold            600   */
    int     echo_suppr_min_gain;      /* default : echo_suppr_min_gain        0     */
    /* Ref. Signal Clipping Level */
    int     ref_signal_clip_level;
}
echo_canceller_config_t;

extern void*
mstaraec_initiailise(
    void*   buffer,
    int *   length,
    void*   configure);

extern int
mstaraec_configure(
    void*   canceller,
    void*   configure);

extern int
mstaraec_process(
    void*   canceller,
    short*  mixed_pcm,
    short*  reference);

#endif//_MSFAEC_API_H_
