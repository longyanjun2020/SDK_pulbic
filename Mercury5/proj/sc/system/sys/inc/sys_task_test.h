
#if defined(__SYS_TIME_SLICE_TEST__)

#include "sys_sys_isw_uart.h"

void test1_Task(void)
{
	volatile int i=0;
	UartSendTrace("in task1\n");
	while (1)
	{
		if(i++>30000)
		{
			//UartSendTrace("task1\n");
			send_msg("!!task1\n");
		    i=0;
		}
	}
}

void test2_Task(void)
{
	volatile int i=0;
	UartSendTrace("in task2\n");
	while (1)
	{

		if(i++>30000)
		{
			//UartSendTrace("task2\n");
			send_msg("!!task2\n");
		    i=0;
		}
	}
}




#endif