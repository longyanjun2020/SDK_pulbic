;----------------------------------------------------------------------------
;Nom du Fichier : rtk1_swit.asm
;Description    : Fonctions assembleurs de changement de context 
;Date Cr‚ation  : 20/11/1994
;----------------------------------------------------------------------------
;


.MODEL  LARGE

 EXTRN  _RtkExceptionRoutine:FAR
 EXTRN  _RTK_MASKINT:BYTE
 EXTRN  _RTK_UNDERINT:WORD

.CODE

; RTK1_ACTIVATE_TASK (u16 FAR *CsNouvelleTache,u16 FAR *CsAncienneTache
; => Cette proc‚dure effectue les actions suivantes:
;    - Sauvegarde du contexte CurrentTask
;    - Restauration du contexte rtkTaskNumber
;    - Activation de la tƒche rtkTaskNumber
;

PUBLIC _RTK1_ACTIVATE_TASK
	_RTK1_ACTIVATE_TASK PROC FAR

		PUSH    BP
		MOV   BP,SP
		PUSHF

		PUSH    AX             ; Check if under interrupt ?
		MOV     AX, seg _RTK_UNDERINT
		MOV     ES, AX
		MOV     AX, ES:_RTK_UNDERINT
		CMP     AX,0
		JNE     RESTORE_AX

		PUSH    BX              ; The AX reg is already saved
		PUSH    CX
		PUSH    DX
		PUSH    SI
		PUSH    DI

		JMP     BASCULE

RESTORE_AX:
		POP     AX


; -------------  Save context of current task -------------

BASCULE:
		PUSH    AX
		MOV     AX, seg _RTK_UNDERINT
		MOV     ES, AX
		MOV     BX, ES:_RTK_UNDERINT
		POP     AX
		PUSH    DS
		MOV     SI,[BP+6]              ; get SI of Current task
		MOV     DS,[BP+8]         ; get DS of Current task

		POP     AX
		MOV     [SI],AX                 ; save DS
		MOV     [SI+2],ES      ; save ES

		MOV     [SI+4],SS               ; save SS
		MOV     [SI+6],SP       ; save SP

		MOV     [SI+10],BX

			 MOV     DI,[SI+12]     ; get the si of addr stackovf
			 MOV     AX,[DI]
			 CMP     AL,55H           ; Valeur test end of stack
;                        JNE   STACK_OVF


; -------------- Restore context of Next task ------------------

		MOV   SI,[BP+10]         ; get SI of Next task
		MOV   DS,[BP+12]               ; get DS of Next task

		MOV   SP,[SI+6]         ; Restore SP
		MOV   SS,[SI+4]      ; Restore SS

		MOV   AX,[SI+8]               ; get indication if first starting code (CS)
		CMP   AX,0H
		JE              EXIT           ; this is not a new starting code task

; ----- This is the first time we enter this task --

		MOV     ES,[SI+2]               ; Restore ES

		PUSH    [SI+8]                  ; Push cs of next task
		PUSH    [SI+10]                 ; Push ip of next task

		MOV     AX,0
		MOV     [SI+8],AX               ; update not first starting code

		MOV     DS,[SI]                 ; Restore DS

		PUSHF
		POP     AX
		AND     AX,0300H                  ;  enable int.
		PUSH    AX
		POPF


		RET                                             ; the ret is quicker then jmp

; ----- This is the not the first time we enter this task --
EXIT:

		MOV     AX,[SI+10]     ; Test if was under interruption
		CMP     AX,0
		JNE     RETT

		MOV     ES,[SI+2]               ; Restore ES
		MOV     DS,[SI]                 ; Restore DS

		POP     DI
		POP     SI
		POP     DX
		POP     CX
		POP     BX
		POP     AX

RETT:
		POPF                 ; we are not interruptible because Flag int is 0
		POP     BP             ; we do not need to restore ES,DS because they are
		RET                  ; saved on the interrupt handler epilog

STACK_OVF:

			 MOV     AX,0AFH
			 CALL _RtkExceptionRoutine       ;  call exeption


_RTK1_ACTIVATE_TASK ENDP


;
; RTK1_ACTIVATE_FIRST_TASK (u16 FAR *CsTache)
;
PUBLIC _RTK1_ACTIVATE_FIRST_TASK
	_RTK1_ACTIVATE_FIRST_TASK PROC FAR

		PUSH    BP
		MOV     BP,SP

		MOV     SI,[BP+6]       ; get SI of Current task
		MOV     DS,[BP+8]       ; get DS of Current task

		MOV     SP,[SI+6]         ; Set SP
		MOV     SS,[SI+4]         ; Set SS
		MOV     ES,[SI+2]         ; Set ES

		PUSH    [SI+8]          ; set CS
		PUSH    [SI+10]         ; set IP

		MOV     AX,0
		MOV     [SI+8],AX               ; update not first starting code

		MOV     DS,[SI]          ; Set DS

		PUSHF
		POP     AX
		AND     AX,0300H                  ;  enable int.
		PUSH    AX
		POPF

		RET                                             ; the ret is quicker then jmp

_RTK1_ACTIVATE_FIRST_TASK ENDP


END
END
END
END
END
END
END
END
END
END
END
END
END
END
END
END
END
END
END
END
END
END
END
END
END
