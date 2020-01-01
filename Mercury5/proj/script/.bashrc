
#-----------------------------------------------------------
# Default variables for G1 Build System
#-----------------------------------------------------------
export G1_VER=e00_011MFCMUX.g1
export G1_SCRIPT=$HOME/$G1_VER/script
export PATH=$G1_SCRIPT:$PATH

alias use_ads='source $G1_SCRIPT/ads.sh'
alias use_rvct='source $G1_SCRIPT/rvct.sh'

#uncomment to select RVDS2.2 compiler
use_rvct

#uncomment to select ADS1.2 compiler
#use_ads
