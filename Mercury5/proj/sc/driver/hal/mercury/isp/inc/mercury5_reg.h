#ifndef MERCURY5_REG_H
#define MERCURY5_REG_H

#include "mercury5_reg_isp0.h"
#include "mercury5_reg_isp1.h"
#include "mercury5_reg_isp2.h"
#include "mercury5_reg_isp3.h"
#include "mercury5_reg_isp4.h"
#include "mercury5_reg_isp5.h"
#include "mercury5_reg_isp6.h"
#include "mercury5_reg_isp7.h"
#include "mercury5_reg_isp8.h"
#include "mercury5_reg_isp9.h"
#include "mercury5_reg_isp10.h"
#include "mercury5_reg_isp11.h"
#include "mercury5_reg_isp12.h"
#include "mercury5_reg_vif.h"
#include "mercury5_reg_isp_dmag.h"
#include "mercury5_reg_isp_miu2sram.h"

#define reg_addr(base,field)  (((short*)base)+offset_of_##field)
#define reg_addrB(base,field)  (((char*)base)+field*2+((field%2==0)?(0):(-1)))
#define reg_addrW(base,field)  (((short*)base)+field)

#endif
