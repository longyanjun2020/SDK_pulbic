/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name     : start.S
* Version       : 0.01
* Device(s)     : Aragon - RZ/A1H
* Tool-Chain    : DS-5 Ver 5.13
*                 ARM Complier
*               :
* H/W Platform  : Aragon CPU Board
* Description   : This is the code to be executed on the target
                  The copyright string signifies the end of the Vector table
*                 Note boot strap sequence is as follows:
*
*                 start->reset_handler->PowerON_Reset()->main()
*
*                 start - first code to be executed on the target
                  start jumps to reset_handler the asm startup routine
*                 reset_handler jumps to PowerON_Reset() C entry point
*                 PowerON_Reset() calls main() C User code entry point
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 18.06.2013 0.01
*******************************************************************************/

    .text
    .code 32

    .global start
    .func   start

start:
    LDR pc, =reset_handler                                            /* Reset Vector */
    LDR pc, =__Undef
    LDR pc, =__SoftInt
    LDR pc, =__AbortPrefetch
    LDR pc, =__AbortData
    LDR pc, =reserved_handler
    LDR pc, =__IrqISR
    LDR pc, =__FiqISR
    .string "Copyright (C) 2013 Renesas Electronics Corporation. All rights reserved."
    .align 5
    .end
