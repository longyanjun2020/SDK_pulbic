#ifndef __R2_GDB_H__
#define __R2_GDB_H__

typedef enum {
	GDB_R0, GDB_R1, GDB_R2, GDB_R3, GDB_R4, GDB_R5, GDB_R6, GDB_R7,
	GDB_R8, GDB_R9, GDB_R10, GDB_R11, GDB_R12, GDB_R13, GDB_R14, GDB_R15,
	GDB_R16, GDB_R17, GDB_R18, GDB_R19, GDB_R20, GDB_R21, GDB_R22, GDB_R23,
	GDB_R24, GDB_R25, GDB_R26, GDB_R27, GDB_R28, GDB_R29, GDB_R30, GDB_R31,
	GDB_PC, GDB_SR, GDB_ESR, GDB_EPCR, GDB_EEAR
} gdb_register_id_t;

#define MAX_GDB_GPR 37

/* gdb signal values */
#define GDB_SIGHUP		1
#define GDB_SIGINT		2
#define GDB_SIGQUIT		3
#define GDB_SIGILL		4
#define GDB_SIGTRAP		5
#define GDB_SIGABRT		6
#define GDB_SIGIOT		6
#define GDB_SIGBUS		7
#define GDB_SIGFPE		8
#define GDB_SIGKILL		9
#define GDB_SIGUSR1		10
#define GDB_SIGSEGV		11
#define GDB_SIGUSR2		12
#define GDB_SIGPIPE		13
#define GDB_SIGALRM		14
#define GDB_SIGTERM		15
#define GDB_SIGSTKFLT		16
#define GDB_SIGCHLD		17
#define GDB_SIGCONT		18
#define GDB_SIGSTOP		19
#define GDB_SIGTSTP		20
#define GDB_SIGTTIN		21
#define GDB_SIGTTOU		22
#define GDB_SIGURG		23
#define GDB_SIGXCPU		24
#define GDB_SIGXFSZ		25
#define GDB_SIGVTALRM		26
#define GDB_SIGPROF		27
#define GDB_SIGWINCH		28
#define GDB_SIGIO		29

extern int gdbt_peek_register_file(int id, unsigned long *val);
extern int gdbt_poke_register_file(int id, unsigned long val);
extern void gdbt_step(unsigned long addr);
extern void gdbt_continue(unsigned long addr);
extern void gdbt_kill(void);
extern void gdbt_detach(void);
extern void gdbt_invalidate_icache(unsigned long start, unsigned long len);
extern void gdbt_flush_dcache(unsigned long start, unsigned long len);
extern char gdbt_putc(char c);
extern char gdbt_getc(void);
extern void gdb_handle_exception(int sig);

#endif //__R2_GDB_H__
