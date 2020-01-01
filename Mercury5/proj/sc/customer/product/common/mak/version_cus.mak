#-------------------------------------------------------------------------------
# Define customer's version information for compilation
# PPPPP.CUS.CHIPNAME.STACK.YYTWyyww.MM.NNnn.Rxxxxx.HW.MMDDhhmm
#
# PPPPP: Platform name; ¡Õ¡× 5 characters  ex. PBB or XMMI
# CUS: Customer ID; ¡Õ¡× 3 characters  ex. MST or SZ
# CHIPNAME: Base Band Chip Name; 3 characters + 4 digits ex. MSW8528, MSW8529
# STACK: Protocol Stack; <= 4 characters ex. GPRS, EDGE, or 3G
# YYTWyyww: YYT is the platform feature set; = 2 digits + 1 characters ex. 09A or 09B
#            Wyyww is the branch created date; = 5 characters ex. W0908 means 2009 week 08
# MM: Major release; ¡× 2 digits
#   Changes in the major number indicate a significant change in the code base such as production 
#       release or season release and/or end-user functionality. 
#   ex. 00: before production
# NNXx: Minor release; ¡× 4 characters
#   Changes in the minor number indicate a subversion release between two major release
#   NN: 2digits, subversion release sequence number, the number starts from 00
#   X: 1 character, a branch release of a subversion release, in the sequence, 0, a, b, c, d, ¡K
#   x: 1 character, a brach release of a branch release, in the sequence, 0, a, b, c, d, ¡K
#       ex. 6800: a subversion release
#          68a0: base on 6800 to patch some bugs fixed or features added
#          68b0: base on 68a0 to patch some bugs fixed or features added
#          68ba: base on 68b0 to patch some bugs fixed or features added, this is for internal release only
#          68c0: base on 68b0 to patch some bugs fixed or features added, not guarantee 68ba included
# HW: hardware version; ¡× 2 digits  ex. 01
# MMDDhhmm : 8 digits, indicate the build load date and time
#
# If we have a software release for M700, its version will look like  
# M700D.MST.MSW8528.GPRS.09AW0908.01.00b0.02.02191215
#
# It means M700D platform/ MSTAR customer/ MSW8528 B.B Chip/ GPRS stack / 09AW0908 platform information /01 major 
# release / 00 minor release b0patch / M700 v1 hardware / build load at 05/19 10:30
#-------------------------------------------------------------------------------


PRODUCT_ID_CUS=EMMI
CUST_ID_CUS=MST

#Filter "_" char in CHIP_TYPE --- start
UNDERLINE:=_
EMPTY:=
CHIPNAME_CUS=$(subst $(UNDERLINE),$(EMPTY),$(CHIP_TYPE))
#Filter "_" char in CHIP_TYPE --- end

YYTWyyww_CUS=10AW1021
STACK_CUS=GPRS
SW_MAJ_VER_CUS=02
SW_MIN_VER_CUS=0404M2
HW_VER_CUS=0a
SRT=.

VERSION_CUS=$(PRODUCT_ID_CUS)$(SRT)$(CUST_ID_CUS)$(SRT)$(CHIPNAME_CUS)$(SRT)$(STACK_CUS)$(SRT)$(YYTWyyww_CUS)$(SRT)$(SW_MAJ_VER_CUS)$(SRT)$(SW_MIN_VER_CUS)$(SRT)$(HW_VER_CUS)$(SRT)
