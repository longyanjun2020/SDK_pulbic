        .text

//****************************************************************************
//
//      File             : AMR_RAM.s
//      Purpose          : Speech codec variable
//                       :  (encoder, decoder, and postfilter)
//
//****************************************************************************
        .balign   4
ArgStack:        .space   16
VarStack:        .space   60
AzTemp:          .space   20

TempBuffer:      .space   480


        .end
