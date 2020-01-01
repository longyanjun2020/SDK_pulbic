#!/bin/csh

set OS_TYPE=`uname -o`

switch ($OS_TYPE)

  case GNU/Linux:
       ############################################
       # RVCT2.2 [Build 616] Environment Settings #
       ############################################
       echo " "
       echo "  Set License for RVCT 2.2 (build 616) environment ..."
       echo " "
       setenv      LM_LICENSE_FILE /tools/asic-bb/licenses/licenses_arm.dat
       echo "      LM_LICENSE_FILE path => $LM_LICENSE_FILE"
    
       echo " "
       echo "  Loading RVCT 2.2 (Build 616) for Linux environment with use_rvct ..."
       echo " "
    
       # ADS home directory:
       setenv ARMHOME /software/tools/delivery/arm/rvct/v2.2_576/linux/RVCT/Programs/2.2/503/linux-pentium
       setenv ARMLIB /software/tools/delivery/arm/rvct/v2.2_576/linux/RVCT/Data/2.2/503/lib
       setenv ARMINC /software/tools/delivery/arm/rvct/v2.2_576/linux/RVCT/Data/2.2/503//include/unix
       setenv ARMSD_DRIVER_DIR $ARMHOME 
       setenv ARMDLL $ARMHOME 
       setenv ARMCONF $ARMHOME 
       #setenv WUHOME /tools/asic-bb/arm/ads/1.2b848/windu
       #setenv HHHOME /tools/asic-bb/arm/ads/1.2b848/windu/bin.linux_i32/hyperhelp

       if ( $?LD_LIBRARY_PATH == 0 )
       then
            setenv LD_LIBRARY_PATH /usr/dt/lib
       else
            setenv LD_LIBRARY_PATH /usr/dt/lib:${LD_LIBRARY_PATH}
       endif
       
       if ( ${LD_LIBRARY_PATH} !~ */usr/openwin/lib* )
       then
            setenv LD_LIBRARY_PATH /usr/openwin/lib:${LD_LIBRARY_PATH}
       endif
       
       setenv LD_LIBRARY_PATH ${ARMHOME}/windu/lib.linux_i32:${LD_LIBRARY_PATH}
       
       setenv LD_LIBRARY_PATH ${ARMHOME}/linux/bin:${LD_LIBRARY_PATH}
       
       setenv LD_LIBRARY_PATH /usr/lib:${LD_LIBRARY_PATH}
   
       echo "      ARMHOME exported for RVCT 2.2 (build 616) !"
       echo "      ARMHOME path => $ARMHOME"
       echo " "
       echo "  RVCT 2.2 (build 616) environment loaded."
       echo " "
       breaksw
  
  default:
       ############################################
       # RVCT2.2 [Build 616] Environment Settings #
       ############################################
       echo " "
       echo "  Set License for RVCT 2.2 (build 616) environment ..."
       echo " "
       setenv      LM_LICENSE_FILE $ARMROOT\\Licenses\\license.dat
       echo "      LM_LICENSE_FILE path => $LM_LICENSE_FILE"
   
       echo " "
       echo "  Loading RVCT 2.2 (Build 616) for Cygwin environment with use_rvct ..."
       echo " "
   
       # RVCT home directory:
       # Reconfigure current 'ARMHOME'  environment variable set on windows for RVCT compiler 
       if ( $?$BCKUP_ARMHOME_ADS == 0 )
       then
            setenv BCKUP_ARMHOME_ADS=$ARMHOME
       endif
       setenv ARMHOME $RVCT22BIN
   
       # Reconfigure current 'ARMLIB'   environment variable set on windows for RVCT compiler 
       setenv ARMLIB $RVCT22LIB
   
       # Reconfigure current 'ARMINC'   environment variable set on windows for RVCT compiler 
       setenv ARMINC $RVCT22INC
   
       # Set current 'ARMSD_DRIVER_DIR' environment variable set on windows for RVCT compiler 
       setenv ARMSD_DRIVER_DIR
   
       # Reconfigure current 'ARMDLL'   environment variable set on windows for RVCT compiler 
       setenv ARMDLL $ARMHOME
   
       # Reconfigure current 'ARMCONF'  environment variable set on windows for RVCT compiler 
       setenv ARMCONF $ARMHOME
   
       #setenv WUHOME
       #setenv HHHOME
   
       echo "      ARMROOT exported for RVCT 2.2 (build 616) !"
       echo "      ARMROOT path => $ARMROOT"
       echo " "
       echo "  RVCT 2.2 (build 616) environment loaded."
       echo " "
       breaksw

endsw
