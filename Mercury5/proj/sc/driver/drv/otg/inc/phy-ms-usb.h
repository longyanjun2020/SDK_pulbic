#ifndef _PHY_MS_USB_H_
#define _PHY_MS_USB_H_

#define UTMIBaseAddress  	0x1F000000+(0x2200*2)
#define otgRegAddress     	0x1F000000+(0x2600*2)
#define USBCBaseAddress 	0x1F000000+(0x2400*2)
#define UHCBaseAddress		0x1F000000+(0x2500*2)

#define DRC_IN16(r)       *((U16 volatile*)(r))
#define DRC_OUT16(r,d)    (*((U16 volatile*)(r)) = (U16)d)
#define DRC_IN8(r)       *((U8 volatile *)(r))
#define DRC_OUT8(r,d)    (*((U8 volatile*)(r)) = (U8)d)

#define USB_REG_WRITE16(r,v)    (DRC_OUT16(otgRegAddress + (r),(v)))
#define USB_REG_READ16(r)    (DRC_IN16(otgRegAddress + (r)))
#define UTMI_REG_WRITE8(r,v)   (DRC_OUT8(UTMIBaseAddress + (r),(v)))
#define UTMI_REG_WRITE16(r,v)  (DRC_OUT16(UTMIBaseAddress + (r),(v)))
#define UTMI_REG_READ8(r)      (DRC_IN8(UTMIBaseAddress + (r)))
#define UTMI_REG_READ16(r)     (DRC_IN16(UTMIBaseAddress + (r)))

#define USBC_REG_WRITE16(r,v)  (DRC_OUT16(USBCBaseAddress + (r),(v)))
#define USBC_REG_READ16(r)     (DRC_IN16(USBCBaseAddress + (r)))
#define UHC_REG_READ16(r)     (DRC_IN16(UHCBaseAddress + (r)))
#define UHC_REG_WRITE16(r,v)  (DRC_OUT16(UHCBaseAddress + (r),(v)))

//--[EHCI Reg]----------------
#define EHC_CMD        (0x10<<1)
#define ASY_EN         (1<<5)
#define PSCH_EN        (1<<4)
#define RUN_STOP       (1<<0)
#define EHC_CMD_INT_THRC    (0x12<<1)
#define EHC_STATUS     (0x14<<1)

#define HC_HALTED      (1<<12)
#define EHC_INTR       (0x18<<1)
#define EHC_BMCS       (0x40<<1)
#define VBUS_OFF       (1<<4)
#define INT_POLARITY   (1<<3)


//--[USBC Reg]----------------
/* RST_CTRL */
#define  OTG_XIU         (1<<6)
#define  UHC_XIU         (1<<5)
#define  REG_SUSPEND     (1<<3)
#define  OTG_RST         (1<<2)
#define  UHC_RST         (1<<1)
#define  USB_RST         (1<<0)


/* PORT_CTRL */
#define  IDPULLUP_CTRL   (1<<4)
#define  PORTCTRL_OTG    (1<<1)
#define  PORTCTRL_UHC    (1<<0)



#define  ID_CHG_INTEN    (1<<3)
#define  ID_CHG_STS      (1<<3)
#define  IDDIG           (1<<3)


#define rst_ctrl	0x00*2
#define port_ctrl 	0x02*2
#define intr_en		0x04*2
#define intr_status	0x06*2
#define utmi_signal	0x08*2

#define M_REG_INTRTXE      0x06*2
#define M_REG_INTRRXE      0x08*2
#define M_REG_INTRUSB      0x0A*2 /* 8 bit */
#define	M_POWER_SOFTCONN    0x4000 // at address 1

#define _USB_HS_CUR_DRIVE_DM_ALLWAYS_HIGH_PATCH

#define BIT0	0x1
#define BIT1	0x2
#define BIT2	0x4
#define BIT3	0x8
#define BIT4	0x10
#define BIT5	0x20
#define BIT6	0x40
#define BIT7	0x80
#define BIT8	0x100
#define BIT9	0x200
#define BIT10	0x400
#define BIT11	0x800
#define BIT12	0x1000
#define BIT13	0x2000
#define BIT14	0x4000
#define BIT15	0x8000

#endif
