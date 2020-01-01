#
# 
#
.SILENT:

all:  	b2

b1:
	make -f Makefile_b1

b2: 
	make -f Makefile_b2
clean:	
	make -f Makefile_b2 clean

dep:	
	make -f Makefile_b2 dep
	
genlib:
	make -f Makefile_b2 genlib
cus:
	make -f Makefile_b2_cus
cus_clean:
	make -f Makefile_b2_cus clean
cleanlib:
	make -f Makefile_b2_cus cleanlib

e2p_on_rai:
	make -f Makefile_e2p_on_rai

