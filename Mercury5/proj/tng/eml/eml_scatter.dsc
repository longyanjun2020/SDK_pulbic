LR_1 0x0 PI
{
	ER_RO +0 
	{
		* (+RO)
	}

	ER_RO2 +0 
	{
	    * (elm_mapper_head, +FIRST)
	    * (elm_mapper_rodata)
		* (elm_mapper_code, +LAST)
	}

	ER_RW 0x0 PI
	{
		* (+RW)
	}

	ER_ZI +0 
	{
		* (+ZI)
	}
	
	ER_ZI2 +0
	{
		* (elm_mapper_rwdata)
	    * (elm_mapper_zidata)
	}
}
