;///////////////////////////////////////////////////////////////////////; 
;/                                                                     /; 
;/                       COPYRIGHT VMTS FRANCE                      /; 
;/                                                                     /; 
;///////////////////////////////////////////////////////////////////////; 
;/                                                                     /; 
;/     The ownership and copyright of this document belong to          /; 
;/     VMTS FRANCE and it must not be disclosed, copied,            /; 
;/  altered or used without the written permission of VMTS FRANCE.  /; 
;/                                                                     /; 
;///////////////////////////////////////////////////////////////////////; 
;/                                                                     /; 
;/ Asic          : V2751                                               /; 
;/ File name     : arm_copro_s.asm                                          /; 
;/ Author        : Vincent Moret-bosch                                 /; 
;/ Purpose       : Function that could not be written in C code.       /; 
;/ hierarchy     :                                                     /; 
;/                                                                     /; 
;/ Notes         :                                                     /; 
;/ Synthetisable : NA                                                  /; 
;/                                                                     /; 
;///////////////////////////////////////////////////////////////////////; 
;/ Notes:                                                              /; 
;/                                                                     /; 
;/                                                                     /;
;/                                                                     /;
;/                                                                     /; 
;///////////////////////////////////////////////////////////////////////; 
 
 AREA Common_s, CODE, READONLY
    EXPORT cp15_write_reg7_test_clean_invalidate_dcache
    EXPORT cp15_write_reg7_test_clean_dcache  
    CODE32

;;void __cp15_write_reg7_test_clean_invalidate_dcache(void)
;; used to invalidate Dcache correctly

cp15_write_reg7_test_clean_invalidate_dcache PROC
;; following code from ARM DDI0198B (ARM926EJS Rev0) spec page 2-23
tci_loop
   MRC p15,0,r15,c7,c14,3 ;test clean and invalidate
   BNE tci_loop
   BX lr
   ENDP

cp15_write_reg7_test_clean_dcache PROC
;; following code from ARM DDI0198B (ARM926EJS Rev0) spec page 2-23
tc_loop
   MRC p15,0,r15,c7,c10,3 ;test clean
   BNE tc_loop
   BX lr
   ENDP

   END



