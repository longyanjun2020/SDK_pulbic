/* INTRUSB, INTRUSBE */
#define M_INTR_VBUSERROR    0x80   /* only valid when A device */
#define M_INTR_SESSREQ      0x40   /* only valid when A device */
#define M_INTR_DISCONNECT   0x20
#define M_INTR_CONNECT      0x10   /* only valid in Host mode */
#define M_INTR_SOF          0x08
#define M_INTR_RESET        0x04
#define M_INTR_BABBLE       0x04
#define M_INTR_RESUME       0x02
#define M_INTR_SUSPEND      0x01   /* only valid in Peripheral mode */


void USB_EP0_Clear_sst(void);
