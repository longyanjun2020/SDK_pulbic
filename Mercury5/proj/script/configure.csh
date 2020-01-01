#!/bin/csh

set OS_TYPE=`uname -o`

switch ($OS_TYPE)
  case GNU/Linux:
#      setenv SCRIPT_DIR /software/tools/delivery/script
       setenv SCRIPT_DIR /software/int/adc/tools/script
       breaksw

  case Cygwin:
#      setenv SCRIPT_DIR //Lnx-ds02/software/tools/delivery/script
       setenv SCRIPT_DIR //Lnx-ds02/software/int/adc/tools/script
       breaksw

endsw

# aliases for SGT
alias use_ads 'source $SCRIPT_DIR/ads.csh'
alias use_rvct 'source $SCRIPT_DIR/rvct.csh'

switch (`uname`)

  case Linux:
       echo " Type use_ads  to load ADS  1.2 environment"
       echo " Type use_rvct to load RVCT 2.2 environment"
       echo " "
       echo " "
       breaksw

  case Cygwin:
       # Load compiler variable by default
       if ( $?$ARMROOT != 0 )
       then
          if ( $?$ARMHOME != 0 )
          then
             echo " Type use_ads  to load ADS  1.2 environment"
             echo " Type use_rvct to load RVCT 2.2 environment"
             echo " "
             echo " "
             echo " ==============================================="
             echo "  Set ADS 1.2 as default ARM Compiler path      "
             echo " ==============================================="
             echo " "
             echo " load ADS 1.2 compiler by default ..."
             echo " "
             use_ads
          else
             echo " Type use_rvct to load RVCT 2.2 environment"
             echo " "
             echo " "
             echo " ==============================================="
             echo "  Set RVCT 2.2 as default ARM Compiler path     "
             echo " ==============================================="
             echo " "
             echo " load RVCT 2.2 compiler by default ..."
             echo " "
             use_rvct
          endif
       else
          if ( $?$ARMHOME != 0 )
          then
             echo " Type use_ads  to load ADS  1.2 environment"
             echo " "
             echo " "
             echo " ==============================================="
             echo "  Set ADS 1.2 as default ARM Compiler path      "
             echo " ==============================================="
             echo " "
             echo " load ADS 1.2 compiler by default ..."
             echo " "
             use_ads
          else
             echo " "
             echo " No ARM compiler detected !!!!!!!!!!"
             echo " "
          endif
       endif
       breaksw

endsw