#ifndef __KERNEL_SIM_H__
#define __KERNEL_SIM_H__

/************************************************/
/* SIM: Subscriber Identity Module Interface    */
/************************************************/	

typedef struct OSim_s {
  u32           Control;        //0x0
  u32           IrqMask;        //0x4
  u32           Status;         //0x8
  u32           StatusClear;    //0xC
  u32           RawStatus;      //0x10
  u32           RxTx;           //0x14
  u32           TxCounter;      //0x18
  u32           RxCounter;      //0x1C
  u32           DmaCounter;     //0x20
  u32           WaitingTime;    //0x24
  u32           EtuClockSpeed;  //0x28
  u32           XWI;            //0x2C
  u32           NAD;            //0x30
  u32           PCB;            //0x34
  u32           EGT;            //0x38
  u32           BWTRE;          //0x3C
  u32           TPWR;           //0x40
  u32           TA;             //0x44
  u32           TB;             //0x48 
  u32           TC1;            //0x4C
  u32           TC2;            //0x50
  u32           SleepState;     //0x54 (BigBlue2 new added)
  u32           EcoFtr;     //0x58  (BigBlue3 newly added)
  u32           Debug;          //0x5C (BigBlue5 newly added)
  u32           Pad1;           //0x60
  u32           Pad2;           //0x64
  u32           DebugLdma;      //0x68 (BigBlue5 newly added)
  u32           DebugLdma_2;     //0x6C (BigBlue5 newly added)
  u32           Upsizer;        //0x70 (BigBlue5 newly added)
} OSim_t;

extern volatile OSim_t * const g_ptOSim1;
extern volatile OSim_t * const g_ptOSim2;

#endif /*__KERNEL_SIM_H__*/
