#ifndef __MMI_COMMON_SIM_H__
#define __MMI_COMMON_SIM_H__


#define DUAL_MASTER		(0)
#define DUAL_SLAVE	        (1)
#ifdef __QUAD_SIM_DUAL_STANDBY__
#define PS_MASTER          (0)
#define PS_SLAVE           (1)
#define PS_SLAVE1          (2)
#define PS_SLAVE2          (3)

#define DUAL_SIM (2)
#define THRD_SIM (3)
#define QUAD_SIM (4)
#endif

typedef enum
{
	COMMON_SIM_CARD_UNKNOW	= 0,				//Not receive SIM indication yet.
	COMMON_SIM_CARD_NOSIM,					//no SIM inserted for both single mode and DUO mode.
	COMMON_SIM_CARD_SINGLE,					//SIM inserted and activated for single SIM mode.
	COMMON_SIM_CARD_SINGLE_INACTIVE,				//SIM inserted and inactivated for single SIM mode.
	COMMON_SIM_CARD_SINGLE_MASTER,			//Master SIM inserted and activated for DUO mode. Slave SIM is not inserted.
	COMMON_SIM_CARD_SINGLE_MASTER_INACTIVE,		//Master SIM inserted and inactivated for DUO mode. Slave SIM is not inserted.
	COMMON_SIM_CARD_SINGLE_SLAVE,			//Slave SIM inserted and activated for DUO mode. Master SIM is not inserted.
	COMMON_SIM_CARD_SINGLE_SLAVE_INACTIVE,			//Slave SIM inserted and inactivated for DUO mode. Master SIM is not inserted.
	COMMON_SIM_CARD_DUAL_MASTER,			//Master SIM activated only for DUO mode. Both Master and Slave SIM are inserted.
	COMMON_SIM_CARD_DUAL_SLAVE,				//Slave SIM activated only for DUO mode. Both Master and Slave SIM are inserted.
	COMMON_SIM_CARD_DUAL_BOTH_ACTIVE,		//Both Master and Slave SIM are inserted and activated for DUO mode.
	COMMON_SIM_CARD_DUAL_BOTH_INACTIVE	//Both Master and Slave SIM are inserted and inactivated for DUO mode.
} COMMON_SIM_CARD_STATUS_e;

#endif /* __MMI_COMMON_SIM_H__ */
