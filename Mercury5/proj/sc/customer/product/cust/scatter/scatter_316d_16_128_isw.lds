OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(start)

/* Base Address RAM Memory Table 10-Mbyte on-chip RAM */
/* Total RAM available 10112K */
MEMORY {
    ROM0L (rwx)   : ORIGIN = 0x14000000, LENGTH = 0x1000000  /* NOR(16MB) H'00000000 to H'10000000 */
    RAM0L (rwx)   : ORIGIN = 0x20000000, LENGTH = 0x8000000  /* DDR(128MB) H'20000000 to H'28000000 */
}

PROGRAM_STACK_SIZE    = 0x8000; 	/* Application stack                  */
IRQ_STACK_SIZE	      = 0x2000;     /* IRQ mode stack                     */
FIQ_STACK_SIZE	      = 0x2000;     /* FRQ mode stack                     */
SVC_STACK_SIZE	      = 0x2000;     /* SVC mode stack                     */
ABT_STACK_SIZE	      = 0x2000;     /* ABT mode stack                     */
BACKTRACE_STACK_SIZE  = 0x800;      /* Backtrace stack                    */
UND_STACK_SIZE        = 0x100;      /* UND mode stack                     */
BOOT_STACK_SIZE       = 0x300;      /* BOOT stack                         */
TTB_SIZE              = 0x8000;     /* Level-1 Translation Table for MMU  */

/* The relocated vector table MUST be aligned on 32-byte boundary.      */
/* Please refer for more details to section                             */
/* B4.1.156 VBAR, Vector Base Address Register, Security Extensions,    */
/* ARM Architecture Reference Manual ARMv7-A and ARMv7-R edition        */
MIRRORED_VECTOR_TABLE = 0x20008000; /* VECTOR_MIRROR_TABLE located here */
MIRRORED_VECTOR_TABLE_OFFSET = 0x8000; /* VECTOR_MIRROR_TABLE located here */
ROM_BOOT_SIZE = 0x60000;

SECTIONS
{
	ROM_BOOT :
	{
    Image$$ROM_BOOT$$Base = .;
    .  += ROM_BOOT_SIZE;
    .	= ALIGN(0x4);
    Image$$ROM_BOOT$$Limit = .;
	} >ROM0L AT>ROM0L

	XRAM (NOLOAD):
	{
		Image$$XRAM$$Base = .;
		*(.mmu_table_16)
		.	= ALIGN(0x4);
	} >RAM0L

    .mvt MIRRORED_VECTOR_TABLE :
    {
    	Image$$ROM$$Base = .;
	     mvt_start = .;
	     *start.o (.text)
	     . = ALIGN(0x4);
	     mvt_end = .;
    } >RAM0L

    .text :
    {
      *(.text*)
      *(.RoCodeOnBoot)
      *(.gnu.warning)
      *(.gnu.linkonce.t.*)
      . = ALIGN(0x4);
      Image$$ROM$$Limit = .;
    } >RAM0L

    .rodata :
    {
    		Image$$ROM_DATA$$Base = .;
		    _srodata = .;
		    *(.rodata*)
		    *(.RoDataOnBoot)
		    .	= ALIGN(0x4);
		    _erodata = .;
    } >RAM0L

    .CODE_RESET :
    {
        _sCODE_RESET = .;
        *(.CODE_RESET)
        _eCODE_RESET = .;
        Image$$ROM_DATA$$Limit = .;
    } >RAM0L

	#if defined(__BOOT_UNCOMPRESS__) || defined(__COMPRESS_SELECTED_BIN__)
		// this is used to story binary size
		// DO NOT REMOVE IT !!!
		BIN_END :
		{
		  Load$$BIN_END$$Base = Image$$ROM_BOOT$$Base;
			*(bin_end)
		} >RAM0L
	#endif



	IRAM_SECTION0 :
	{
	  *(sys_HwWdtDebug)
	  .   = ALIGN(0x4);
	} >RAM0L

        //Mercury5. Merged from Mv2.
        MODULE_INIT :
        {
            Image$$MODULE_INIT$$Base = .;
            KEEP (*(initcall1))
            KEEP (*(initcall2))
            KEEP (*(initcall3))
            KEEP (*(initcall4))
            KEEP (*(initcall5))
            KEEP (*(initcall6))
            Image$$MODULE_INIT$$Limit = .;
            .   = ALIGN(0x4);
        } >RAM0L
        NETCGI_INIT :
        {
            Image$$NETCGI_INIT$$Base = .;
            KEEP (*(netcgi_init))
            Image$$NETCGI_INIT$$Limit = .;
            .   = ALIGN(0x4);
        } >RAM0L
        NETNODE_INIT :
        {
            Image$$NETNODE_INIT$$Base = .;
            KEEP (*(netnode_init))
            Image$$NETNODE_INIT$$Limit = .;
            .   = ALIGN(0x4);
        } >RAM0L
        

	XRAM0 :
	{
		Image$$XRAM0$$Base = .;
		*(kernel_memory_critical)
		*(kernel_memory_critical.rwdata)
		*(rtk_critical)
		*(rtk_critical_2)
		*(rtk_critical_2.rwdata)
		*(.RoDataOnFsp)
		.	= ALIGN(0x4);
	} >RAM0L


    .data :
    {
        _sdata = .;
        *(.data*)
        *(.igot.plt)
        *(.dqmem)
        .   = ALIGN(0x4);
		_data = .;
		_edata = .;
    } >RAM0L

    .DATA_RESET :
    {
        *(.DATA_RESET)
        .   = ALIGN(0x4);
    } >RAM0L

    RW_STATICBOOT :
    {
        *(STATICBOOT)
        .	= ALIGN(0x4);
    } >RAM0L

	DEBUG_AREA :
	{
	    *(DebugArea)
        *(SysNonZI)
        *(DrvNonZI)
        *(.rm_Struct)
        *(clkgen_data)
	    .	= ALIGN(0x4);
	} >RAM0L

    .bss :
    {
         _bss = .;
         PROVIDE(__bss_start__ = .);
         *(.bss*)
         *(COMMON)
         .   = ALIGN(0x4);
         PROVIDE(__bss_end__ = .);
         _ebss = .;
         _end = .;
         PROVIDE(end = .);
    } >RAM0L

    .BSS_RESET :
    {
        .   = ALIGN(0x4);
        PROVIDE (__start_BSS_RESET = .);
        *(.BSS_RESET)
        PROVIDE (__stop_BSS_RESET = .);
        .   = ALIGN(0x4);
    } >RAM0L

/*    .program_stack : ALIGN(0x8000)
    {
        program_stack_start = .;
        .  += PROGRAM_STACK_SIZE;
        .   = ALIGN(0x4);
        program_stack_end = .;
    } >RAM0L
*/

    .fiq_stack :
    {
    fiq_stack_start = .;
    FiqStack = fiq_stack_start;
    .  += FIQ_STACK_SIZE;
    .	= ALIGN(0x4);
    fiq_stack_end = .;
    FiqStackStart = fiq_stack_end;
    } >RAM0L

    .irq_stack :
    {
    irq_stack_start = .;
    IrqStack = irq_stack_start;
    .  += IRQ_STACK_SIZE;
    .	= ALIGN(0x4);
    irq_stack_end = .;
    IrqStackStart = irq_stack_end;
    } >RAM0L

    .abt_stack :
    {
    abt_stack_start = .;
    AbtStack = abt_stack_start;
    .  += ABT_STACK_SIZE;
    .	= ALIGN(0x4);
    abt_stack_end = .;
    AbtStackStart = abt_stack_end;
    } >RAM0L

    .backtrace_stack :
    {
    backtrace_stack_start = .;
    BacktraceStack = backtrace_stack_start;
    .  += BACKTRACE_STACK_SIZE;
    .	= ALIGN(0x4);
    backtrace_stack_end = .;
    BacktraceStackStart = backtrace_stack_end;
    } >RAM0L

    .und_stack :
    {
    und_stack_start = .;
    UndefStack = und_stack_start;
    .  += UND_STACK_SIZE;
    .	= ALIGN(0x4);
    und_stack_end = .;
    UndefStackStart = und_stack_end;
    } >RAM0L

    .boot_stack :
    {
    boot_stack_start = .;
    BootStack = boot_stack_start;
    .  += BOOT_STACK_SIZE;
    .	= ALIGN(0x4);
    boot_stack_end = .;
    BootStackStart = boot_stack_end;
    } >RAM0L

    .svc_stack :
    {
    PROVIDE(svc_stack_start = .);
    SupStack = svc_stack_start;
    .  += SVC_STACK_SIZE;
    .	= ALIGN(0x4);
    svc_stack_end = .;
    SupStackStart = svc_stack_end;
    } >RAM0L

    /* L1 translation table must be aligned to 16KB Boundary!           */
    /* Please refer to Cortex-A Series Version: 4.0 Programmer’s Guide, */
    /* section 9.4 First level address translation                      */
/*    .ttb_mmu1 : ALIGN(0x4000)
    {
        ttb_mmu1_base = .;
        .  += TTB_SIZE;
        .   = ALIGN(0x4);
        ttb_mmu1_end = .;
    } >RAM0L
*/
   // Image$$Heap_Start$Base = .;
    Image$$HEAP_START$$Base = .;
    Image$$HEAP_START$$Limit = 0x28000000;
}
