    INCLUDE v2751.i

        PRESERVE8
        
        AREA    abort_handlers, CODE


;****************************************************************************
;* Function: __AbortData
;****************************************************************************
;* This function should not be called directly
;*
;* This is the Abort Data exception handler
;****************************************************************************
__AbortData     FUNCTION
        EXPORT  __AbortData
        B       __AbortData                   ; endless while loop

        ENDFUNC

;****************************************************************************
;* Function: __AbortPrefetch
;****************************************************************************
;* This function should not be called directly
;*
;* This is the Abort Prefetch exception handler
;****************************************************************************
__AbortPrefetch FUNCTION
        EXPORT  __AbortPrefetch
        B       __AbortPrefetch               ; endless while loop

        ENDFUNC
        
;****************************************************************************
;* Function: __Undef
;****************************************************************************
;* This function should not be called directly
;*
;* This is the Undefined Instruction exception handler
;****************************************************************************
__Undef         FUNCTION
        EXPORT  __Undef
        B       __Undef                  ; endless while loop

        ENDFUNC

        END



     END
