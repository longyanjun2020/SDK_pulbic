
// mstar hardware video encoder I/F (mhveif)

#ifndef _MHVE_IOS_H_
#define _MHVE_IOS_H_

typedef struct mhve_ios mhve_ios;
typedef struct mhve_reg mhve_reg;
typedef struct mhve_job mhve_job;

typedef int MfeIOsCBFunc(int);

struct mhve_ios {
    void    (*release)(void*);                 	//! Release this object.
    int     (*set_bank)(mhve_ios*, mhve_reg*);  //! Assign register base pointer.
    int     (*set_cbfunc)(mhve_ios*, void*);    //! register callback function.
    int     (*enc_fire)(mhve_ios*, mhve_job*);  //! Process and trigger encoder job.
    int     (*enc_poll)(mhve_ios*);             //! Polling encode-done.
    int     (*isr_func)(mhve_ios*, int);        //! Interrupt service routine.
    int     (*irq_mask)(mhve_ios*, int);        //! Masking irq.
    int     (*rst_module)(mhve_ios*, mhve_job*);//! Reset MFE module.
};

struct mhve_reg {
    int     i_id;   /* Register Table ID */
    void*   base;   /* Register Base Address */
    int     size;   /* Register Bank Size */
};

#define MHVEJOB_OKAY        0
#define MHVEJOB_ENC_DONE    0
#define MHVEJOB_BUF_FULL    1
#define MHVEJOB_ENC_FAIL   -1
#define MHVEJOB_TIME_OUT   -2

struct mhve_job {
    int     i_code;	/* Not Used */
    int     i_tick; /* Encode cycles */
    int     i_bits; /* Bit counts include pure bitstream and slice header only */
};

mhve_ios* MfeIosAcquire(char* tags);

#endif //_MHVE_IOS_H_
