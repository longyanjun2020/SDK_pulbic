               		IMPORT |Image$$ROM$$Base|
        		IMPORT |Image$$ROM$$Limit|
             		IMPORT |Image$$XRAM$$Base|


             	             	
        		GBLS	Image__RO__Base 
Image__RO__Base		SETS	"|Image$$$$ROM$$$$Base|"

			GBLS	Image__RO__Limit 
Image__RO__Limit	SETS	"|Image$$$$ROM$$$$Limit|"

			GBLS	Image__RAM__Base 
Image__RAM__Base	SETS	"|Image$$$$XRAM$$$$Base|"
	


	
			GBLS	Image__RW__Limit 
Image__RW__Limit	SETS	"|Image$$$$XRAM$$$$ZI$$$$Limit|"	




			END