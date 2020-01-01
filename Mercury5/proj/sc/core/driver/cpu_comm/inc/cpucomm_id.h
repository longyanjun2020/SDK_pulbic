#ifndef __CPU_COMM_ID_H__
#define __CPU_COMM_ID_H__

typedef enum _CPU_COMM_ID {
    CPU_COMM_ID_SYSFLAG         = 0,
    CPU_COMM_ID_MDTC            = 1,    /* Motion Detection RequestID */
    CPU_COMM_ID_ADAS            = 2,

    // this is the end of ID enumeration
    CPUCOMM_ID_MAX_NUM          = 3,

    // illegal ID
    CPU_COMM_ID_ILLEGAL         = 0xFE,
    // to mark that the CPU B is not READY
    CPU_COMM_ID_CPU_B_NOT_READY = 0xFF
} CPU_COMM_ID;

#endif // __CPU_COMM_ID_H__

