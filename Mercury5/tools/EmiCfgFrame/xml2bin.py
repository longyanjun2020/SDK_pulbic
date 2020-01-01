

import xml.dom.minidom as minidom
import struct
import optparse
import sys

ClkMappingTbl = ((u'EMI_CLK_26MHZ', '0'), 
                 (u'EMI_CLK_52MHZ', '1'), 
                 (u'EMI_CLK_78MHZ', '2'), 
                 (u'EMI_CLK_104MHZ', '3'), 
                 (u'EMI_CLK_130MHZ', '4'),
                 (u'EMI_CLK_156MHZ', '5'),
                 (u'EMI_CLK_128MHZ', '8'))


nOpModeMappingTbl = ((u'EMI_SINGLE', '0'), 
                     (u'EMI_PAGE', '1'), 
                     (u'EMI_BURST_WRITE', '2'), 
                     (u'EMI_BURST_READ', '4'), 
                     (u'EMI_BURST_RW', '6'))


nTypeMappingTbl = ((u'EMI_NOR', '0'),
                   (u'EMI_CELLULARRAM', '1'),
                   (u'EMI_COSMORAM', '2'),
                   (u'EMI_UtRAM', '3'),
                   (u'EMI_SRAM', '4'))


nPageSizeMappingTbl = ((u'EMI_PAGE_1WORD', '0'),
                       (u'EMI_PAGE_2WORDS', '1'),
                       (u'EMI_PAGE_4WORDS', '2'),
                       (u'EMI_PAGE_8WORDS', '3'),
                       (u'EMI_PAGE_16WORDS', '4'))


BurstSizeMappingTbl = ((u'EMI_NO_BOUNDARY', '0'),
                       (u'EMI_BURST_4WORDS', '1'),
                       (u'EMI_BURST_8WORDS', '2'),
                       (u'EMI_BURST_16WORDS', '3'),
                       (u'EMI_BURST_32WORDS', '4'),
                       (u'EMI_BURST_64WORDS', '5'),
                       (u'EMI_BURST_128WORDS', '6'),
                       (u'EMI_BURST_256WORDS', '7'))



SpiNorOpModeMappingTbl = ((u'SPINOR_SPI', '0'),
                          (u'SPINOR_QPI', '1'))


SpiNorFuncMappingTbl = ((u'SPINOR_FUNC_NORMAL', '0'),
                        (u'SPINOR_FUNC_CMD_BYPASS', '1'),
                        (u'SPINOR_FUNC_WRAP', '2'))


SpiNorBusClockMappingTbl = ((u'SPINOR_26MHz', '26'),
                            (u'SPINOR_48MHz', '48'),
                            (u'SPINOR_77MHz', '77'),
                            (u'SPINOR_89MHz', '89'),
                            (u'SPINOR_96MHz', '96'),
                            (u'SPINOR_128MHz', '128'))


SpiNorSuspendBitMappingTbl = ((u'WINBOND_SUSPEND_BIT', '0x80'),
                              (u'GIGADEVICE_SUSPEND_BIT', '0x80'),
                              (u'MACRONIX_SUSPEND_BIT', '0x08'),
                              (u'MICRON_SUSPEND_BIT', '0x40'),
                              (u'EON_SUSPEND_BIT', '0x04'))




def getTagValue(parent_tag_node, tag_name, index):
    
    tag_value = None
    
    tag_node = parent_tag_node.getElementsByTagName(tag_name)[index]
    node = tag_node.childNodes[0]

    if node.nodeType == node.TEXT_NODE:
        tag_value = node.nodeValue    

    return tag_value



def getLeafValues(parent_tag_node, leaf_tag_names, leaf_tag_values):

    for leaf_tag_name in leaf_tag_names:
        leaf_tag_values.append(getTagValue(parent_tag_node, leaf_tag_name, 0))
        
    return leaf_tag_values

def getSpiCmdData(spicmd_node):
    
    spicmd_leaf_tag_names = ['RSTA', 'RSTA1', 'RSTA2', 'RSTA3', 'RSTB', 'RSTB1', 'RSTB2', 'RSTB3', 'RSTC', 'RSTC1', 'RSTC2', 'RSTC3', 'RSTD', 'RSTD1', 'RSTD2', 'RSTD3', 'DUMMY1', 'DUMMY2']

    spicmd_data = []
    spicmd_data = getLeafValues(spicmd_node, spicmd_leaf_tag_names, spicmd_data)
    
    '''
    print 'spicmd_data : '
    print spicmd_data
    print "\n",  
    '''
    
    # write to binary file
    fmt_string = 'BBBBBBBBBBBBBBBBBB'
    
    RSTA = int(spicmd_data[0], 0)
    RSTA1 = int(spicmd_data[1], 0)
    RSTA2 = int(spicmd_data[2], 0)
    RSTA3 = int(spicmd_data[3], 0)
    RSTB = int(spicmd_data[4], 0)
    RSTB1 = int(spicmd_data[5], 0)
    RSTB2 = int(spicmd_data[6], 0)
    RSTB3 = int(spicmd_data[7], 0)
    RSTC = int(spicmd_data[8], 0)
    RSTC1 = int(spicmd_data[9], 0)
    RSTC2 = int(spicmd_data[10], 0)
    RSTC3 = int(spicmd_data[11], 0)
    RSTD = int(spicmd_data[12], 0)
    RSTD1 = int(spicmd_data[13], 0)
    RSTD2 = int(spicmd_data[14], 0)
    RSTD3 = int(spicmd_data[15], 0)
    DUMMY1 = int(spicmd_data[16], 0)
    DUMMY2 = int(spicmd_data[17], 0)
    
    hex_binary_string = struct.pack(fmt_string, RSTA, RSTA1, RSTA2, RSTA3, RSTB, RSTB1, RSTB2, RSTB3, RSTC, RSTC1, RSTC2, RSTC3, RSTD, RSTD1, RSTD2, RSTD3, DUMMY1, DUMMY2)
    output_file.write(hex_binary_string)

    hex_binary_string = struct.pack('B', 0)
    output_file.write(hex_binary_string)
    output_file.write(hex_binary_string)   

    hex_binary_string = struct.pack('I', 0)
    for x in range(43):
        output_file.write(hex_binary_string)    
                      
    return spicmd_data

def getIdentifierData(identifier_node):
    
    identifier_leaf_tag_names = ['nMagic', 'nDeviceFullId', 'nFlashName', 'nFeatures', 'nFlashType', 'nDeviceSecondID', 'nSecondIDMask']

    identifier_data = []
    identifier_data = getLeafValues(identifier_node, identifier_leaf_tag_names, identifier_data)
    
    '''
    print 'identifier_data : '
    print identifier_data
    print "\n",  
    '''
    
    # write to binary file
    fmt_string = 'II36sIIHH'
    
    nMagic = int(identifier_data[0], 0)
    nDeviceFullId = int(identifier_data[1], 0)
    nFlashName = str(identifier_data[2])
    nFeatures = int(identifier_data[3], 0)
    nFlashType = int(identifier_data[4], 0)
    nDeviceSecondID = int(identifier_data[5], 0)
    nSecondIDMask = int(identifier_data[6], 0)
    
    hex_binary_string = struct.pack(fmt_string, nMagic, nDeviceFullId, nFlashName, nFlashType, nFeatures, nDeviceSecondID, nSecondIDMask)
    output_file.write(hex_binary_string)
    
                      
    return identifier_data  
            


def getGeometryData(geometry_node):
    
    geometry_tag_names = ['nDeviceSize', 'nPad', 'nRegionNumber']
    geometry_data = []
    geometry_data = getLeafValues(geometry_node, geometry_tag_names, geometry_data)
    
    # write to binary file
    fmt_string = 'HBB'    
    
    nDeviceSize = int(geometry_data[0], 0)
    nPad = int(geometry_data[1], 0)
    nRegionNumber = int(geometry_data[2], 0)
    
    hex_binary_string = struct.pack(fmt_string, nDeviceSize, nPad, nRegionNumber)
    output_file.write(hex_binary_string)     
    
        
    # proceed nAsRegions[8]        
    as_region_number = int(geometry_data[2], 0)

    if as_region_number == 0:
        
        # if as_region_number == 0, then fill the remaining binary file space with 0x0000
        for i in range(8):
            
            fmt_string = 'HH'
            
            nShiftedSize = int('0x0000', 0)
            nNumber = int('0x0000', 0)
            
            hex_binary_string = struct.pack(fmt_string, nShiftedSize, nNumber)
            output_file.write(hex_binary_string) 
        
    else:
            
        for as_region_index in range(as_region_number):
    
            region_node = geometry_node.getElementsByTagName('nAsRegions')[as_region_index]
            
            as_region_tag_names = ['nShiftedSize', 'nNumber']        
            as_region_data = []
            as_region_data = getLeafValues(region_node, as_region_tag_names, as_region_data)        
            geometry_data.append(as_region_data)
            
            # write to binary file
            fmt_string = 'HH'
            
            nShiftedSize = int(as_region_data[0], 0)
            nNumber = int(as_region_data[1], 0)
            
            hex_binary_string = struct.pack(fmt_string, nShiftedSize, nNumber)
            output_file.write(hex_binary_string) 
            

    
        # if as_region_number < 8, then fill the remaining binary file space with 0x0000
        if as_region_number < 8:
            remaining_num = 8 - as_region_number
            for i in range(remaining_num):
                fmt_string = 'HH'
                nShiftedSize = int('0x0000', 0)
                nNumber = int('0x0000', 0)
                hex_binary_string = struct.pack(fmt_string, nShiftedSize, nNumber)
                output_file.write(hex_binary_string) 

    '''        
    print 'geometry_data : '
    print geometry_data
    print "\n",    
    '''

    return geometry_data



def getBankData(bank_node):

    bank_data = []
    
    # get nBankNumber value
    bank_data.append(getTagValue(bank_node, 'nBankNumber', 0))   

    # write to binary file
    fmt_string = 'I'    
    nBankNumber = int(bank_data[0], 0)    
    hex_binary_string = struct.pack(fmt_string, nBankNumber)
    output_file.write(hex_binary_string)        
    

    
    # proceed nBankAddresses[32]
    bank_addr_number = int(bank_data[0], 0)
    
    if bank_addr_number == 0:
        # if bank_addr_number == 0, then fill the remaining binary file space with 0x0000
        for i in range(32):
            fmt_string = 'H'
            nBankAddresses = int('0x0000', 0)
            hex_binary_string = struct.pack(fmt_string, nBankAddresses)
            output_file.write(hex_binary_string)         
    else:

        for bank_addr_index in range(bank_addr_number):
            nBankAddresses = getTagValue(bank_node, 'nBankAddresses', bank_addr_index)
            
            bank_data.append(nBankAddresses)
            
            # write to binary file
            fmt_string = 'H'
            hex_binary_string = struct.pack(fmt_string, int(nBankAddresses, 0))
            output_file.write(hex_binary_string)  
        
        # if bank_addr_number < 32, then fill the remaining binary file space with 0x0000
        if bank_addr_number < 32:
            remaining_num = 32 - bank_addr_number
            for i in range(remaining_num):
                fmt_string = 'H'
                nBankAddresses = int('0x0000', 0)
                hex_binary_string = struct.pack(fmt_string, nBankAddresses)
                output_file.write(hex_binary_string)         
        
    '''    
    print 'bank_data : '
    print bank_data
    print "\n",            
    '''
    
    return bank_data          
  
    
  
def getCommandSetsData(command_sets_node):

    command_sets_data = []
    
    nCommandSetsIndex = getTagValue(command_sets_node, 'nCommandSetsIndex', 0)    
    command_sets_data.append(nCommandSetsIndex)    
    # write to binary file
    fmt_string = 'B'
    hex_binary_string = struct.pack(fmt_string, int(nCommandSetsIndex, 0))
    output_file.write(hex_binary_string)

    
    command_sets_data.append(getTagValue(command_sets_node, 'ndummyArray', 0))
    # fill "u8 ndummyArray[3];" with 0x00
    for i in range(3):
        fmt_string = 'B'
        ndummyArray = int('0x00', 0)
        hex_binary_string = struct.pack(fmt_string, ndummyArray)
        output_file.write(hex_binary_string)     
    
    '''    
    print 'command_sets_data : '
    print command_sets_data
    print "\n",
    '''
    
    return command_sets_data
        


# proceed Psram_SWCmd[16]     
# proceed Nor_SWCmd[16] 
def getSWCmdData(sw_cmd_node):
    
    sw_cmd_data = []
  
    swcmd_number = len(sw_cmd_node.getElementsByTagName('swcmd'))
    
    if swcmd_number == 0:
        
        # if swcmd_number == 0, then fill the remaining binary file space with 0x0000
        for i in range(16):
            fmt_string = 'III'
            hex_binary_string = struct.pack(fmt_string, int('0x00000000', 0), int('0x00000000', 0), int('0x00000000', 0))
            output_file.write(hex_binary_string)          
        
    else:

        for swcmd_index in range(swcmd_number):
    
            swcmd_node = sw_cmd_node.getElementsByTagName('swcmd')[swcmd_index]
            
            swcmd_tag_names = ['addrh', 'addrl', 'wrdata']        
            swcmd_data = []
            swcmd_data = getLeafValues(swcmd_node, swcmd_tag_names, swcmd_data)        

            # check and convert 'NOUSE' & 'CRVALUE'
            for idx in range(3):
                if swcmd_data[idx] == u'NOUSE':
                    swcmd_data[idx] = '0xFFFFFFFF'
                elif swcmd_data[idx] == u'CRVALUE':
                    swcmd_data[idx] = '0xFFFFFFFE'
                else:
                    pass
            
            sw_cmd_data.append(swcmd_data)
            
            # write to binary file
            fmt_string = 'III'
            
            Addr_h = int(swcmd_data[0], 0)
            Addr_l = int(swcmd_data[1], 0)
            WrData = int(swcmd_data[2], 0)
            
            hex_binary_string = struct.pack(fmt_string, Addr_h, Addr_l, WrData)
            output_file.write(hex_binary_string)            
            
            
        # if swcmd_number < 16, then fill the remaining binary file space with 0x0000
        if swcmd_number < 16:
            remaining_num = 16 - swcmd_number
            for i in range(remaining_num):
                fmt_string = 'III'
                hex_binary_string = struct.pack(fmt_string, int('0x00000000', 0), int('0x00000000', 0), int('0x00000000', 0))
                output_file.write(hex_binary_string) 
                
    '''    
    print 'sw_cmd_data : '
    print sw_cmd_data
    print "\n",       
    '''    
        
    return sw_cmd_data
    
    
        
#emi_AdvancedConfig_t emiAdvanParams;
def getEmiAdvanParams(emi_params_node, emi_advan_params):
    
    emi_advan_params_tag_node = emi_params_node.getElementsByTagName('emi_AdvancedConfig_t')[0]
    emi_advan_params_tag_names = ['FineInBound', 'FineOutBound', 'smcCLK', 'CoarseInBound', 'CoarseOutBound', 
                                  'dmcCLK', 'OM', 'IL', 'LC', 'WaitPol', 
                                  'WaitConfig', 'DrivStrength', 'BurstWrap', 'BLength', 'PageMode', 
                                  'DeepPWD', 'PartialRefresh']

    emi_advan_params = getLeafValues(emi_advan_params_tag_node, emi_advan_params_tag_names, emi_advan_params)

    '''
    print 'emi_advan_params : '
    print emi_advan_params
    print "\n",
    '''
    
    
    # convert 'smcCLK' & 'dmcCLK' field value
    
    # emi_advan_params[2] : 'smcCLK'
    if nor_type == 'serial':
        emi_advan_params[2] = '1' #u'EMI_CLK_52MHZ'
    else:
        for mapping in ClkMappingTbl:
            if emi_advan_params[2] == mapping[0]:
                emi_advan_params[2] = mapping[1]
                break        

    # emi_advan_params[5] : 'dmcCLK'    
    for mapping in ClkMappingTbl:
        if emi_advan_params[5] == mapping[0]:
            emi_advan_params[5] = mapping[1]
            break

    # emi_advan_params[6] : 'OM'     
    if emi_advan_params[6] == u'NOUSE':
        emi_advan_params[6] = '0xFFFFFFFF'
    elif emi_advan_params[6] == u'CRVALUE':
        emi_advan_params[6] = '0xFFFFFFFE'
    else:
        pass
        
        
    # write to binary file    
    fmt_string = '19I'
    
    FineInBound = int(emi_advan_params[0], 0)
    FineOutBound = int(emi_advan_params[1], 0)
    smcCLK = int(emi_advan_params[2], 0)
    CoarseInBound = int(emi_advan_params[3], 0)
    CoarseOutBound = int(emi_advan_params[4], 0)
    dmcCLK = int(emi_advan_params[5], 0)
    OM = int(emi_advan_params[6], 0)
    IL = int(emi_advan_params[7], 0)
    LC = int(emi_advan_params[8], 0)
    WaitPol = int(emi_advan_params[9], 0)
    WaitConfig = int(emi_advan_params[10], 0)
    DrivStrength = int(emi_advan_params[11], 0)
    BurstWrap = int(emi_advan_params[12], 0)
    BLength = int(emi_advan_params[13], 0)
    PageMode = int(emi_advan_params[14], 0)
    DeepPWD = int(emi_advan_params[15], 0)
    PartialRefresh = int(emi_advan_params[16], 0)
    ndummy0 = int('0x00000000', 0)
    ndummy1 = int('0x00000000', 0)
    
    hex_binary_string = struct.pack(fmt_string, 
                                    FineInBound, FineOutBound, smcCLK, CoarseInBound, CoarseOutBound, 
                                    dmcCLK, OM, IL, LC, WaitPol, 
                                    WaitConfig, DrivStrength, BurstWrap, BLength, PageMode,
                                    DeepPWD, PartialRefresh, ndummy0, ndummy1)
    
    output_file.write(hex_binary_string)         
        
    '''
    print 'emi_advan_params : '
    print emi_advan_params
    print "\n",
    '''
    
    return emi_advan_params
    

def getParallelNorBasicParams(nor_basic_params_tag_node, nor_basic_params):
    
    nor_basic_params_tag_names = ['nOenToEnd', 'nSetupWr', 'nTurnAround', 'nPageAddAcct', 'nWenCycle',
                                  'nSetupRd', 'nWrCs', 'nRdCs', 'nOpMode', 'nType',
                                  'BurstReadWait', 'BurstWriteWait', 'nPageSize', 'BurstSize', 'nDriving']

    nor_basic_params = getLeafValues(nor_basic_params_tag_node, nor_basic_params_tag_names, nor_basic_params)
    
    
    # convert 'nOpMode', 'nType', 'BurstReadWait', 'BurstWriteWait', 'nPageSize', 'BurstSize' field value

    # nor_basic_params[8] : 'nOpMode'
    for mapping in nOpModeMappingTbl:
        if nor_basic_params[8] == mapping[0]:
            nor_basic_params[8] = mapping[1]
            break

        
    # nor_basic_params[9] : 'nType'    
    for mapping in nTypeMappingTbl:
        if nor_basic_params[9] == mapping[0]:
            nor_basic_params[9] = mapping[1]
            break    
    
    
    # nor_basic_params[12] : 'nPageSize'
    for mapping in nPageSizeMappingTbl:
        if nor_basic_params[12] == mapping[0]:
            nor_basic_params[12] = mapping[1]
            break                                
    
    
    # nor_basic_params[13] : 'BurstSize'
    for mapping in BurstSizeMappingTbl:
        if nor_basic_params[13] == mapping[0]:
            nor_basic_params[13] = mapping[1]
            break     

        
    # write to binary file    
    fmt_string = '17I'
    
    nOenToEnd = int(nor_basic_params[0], 0)
    nSetupWr = int(nor_basic_params[1], 0)
    nTurnAround = int(nor_basic_params[2], 0)
    nPageAddAcct = int(nor_basic_params[3], 0)
    nWenCycle = int(nor_basic_params[4], 0)
    nSetupRd = int(nor_basic_params[5], 0)
    nWrCs = int(nor_basic_params[6], 0)
    nRdCs = int(nor_basic_params[7], 0)
    nOpMode = int(nor_basic_params[8], 0)
    nType = int(nor_basic_params[9], 0)

    tmp_param_one = int(nor_basic_params[10].strip('(').strip(')').split('+')[0], 0)
    tmp_param_two = int(nor_basic_params[10].strip('(').strip(')').split('+')[1], 0)
    BurstReadWait = tmp_param_one + tmp_param_two

    tmp_param_one = int(nor_basic_params[11].strip('(').strip(')').split('+')[0], 0)
    tmp_param_two = int(nor_basic_params[11].strip('(').strip(')').split('+')[1], 0)
    BurstWriteWait = tmp_param_one + tmp_param_two

    nPageSize = int(nor_basic_params[12], 0)
    BurstSize = int(nor_basic_params[13], 0)
    nDriving = int(nor_basic_params[14], 0)
    ndummy0 = int('0x00000000', 0)
    ndummy1 = int('0x00000000', 0)
    
    hex_binary_string = struct.pack(fmt_string, 
                                    nOenToEnd, nSetupWr, nTurnAround, nPageAddAcct, nWenCycle,
                                    nSetupRd, nWrCs, nRdCs, nOpMode, nType,
                                    BurstReadWait, BurstWriteWait, nPageSize, BurstSize,
                                    nDriving, ndummy0, ndummy1)

    
    output_file.write(hex_binary_string) 
    
    

def getSpiNorBasicParams(nor_basic_params_tag_node, nor_basic_params):
    
    nor_basic_params_tag_names = ['eOpMode', 'eFunc', 'eBusClock', 'pSPIInit', 'pSPICmdByp',
                                  'nCMDStatus2', 'nCMDSuspend', 'nCMDResume', 'nSuspendBit', 'R_CSZ',
                                  'W_CSZ', 'nDriving', 'nDummyClock']

    nor_basic_params = getLeafValues(nor_basic_params_tag_node, nor_basic_params_tag_names, nor_basic_params)
    
    
    # convert 'eOpMode', 'eFunc', 'eBusClock', 'nSuspendBit' field value

    # nor_basic_params[0] : 'eOpMode'
    for mapping in SpiNorOpModeMappingTbl:
        if nor_basic_params[0] == mapping[0]:
            nor_basic_params[0] = mapping[1]
            break

        
    # nor_basic_params[1] : 'eFunc'    
    for mapping in SpiNorFuncMappingTbl:
        if nor_basic_params[1] == mapping[0]:
            nor_basic_params[1] = mapping[1]
            break    
    
    
    # nor_basic_params[2] : 'eBusClock'
    for mapping in SpiNorBusClockMappingTbl :
        if nor_basic_params[2] == mapping[0]:
            nor_basic_params[2] = mapping[1]
            break                                
    
    
    # nor_basic_params[8] : 'nSuspendBit'
    for mapping in SpiNorSuspendBitMappingTbl:
        if nor_basic_params[8] == mapping[0]:
            nor_basic_params[8] = mapping[1]
            break     

        
    # write to binary file    
    fmt_string = '17I'
    
    eOpMode = int(nor_basic_params[0], 0)
    eFunc = int(nor_basic_params[1], 0)
    eBusClock = int(nor_basic_params[2], 0)
    pSPIInit = int(nor_basic_params[3], 0)
    pSPICmdByp = int(nor_basic_params[4], 0)
    nCMDStatus2 = int(nor_basic_params[5], 0)
    nCMDSuspend = int(nor_basic_params[6], 0)
    nCMDResume = int(nor_basic_params[7], 0)
    nSuspendBit = int(nor_basic_params[8], 0)
    R_CSZ = int(nor_basic_params[9], 0)
    W_CSZ = int(nor_basic_params[10], 0)
    nDriving = int(nor_basic_params[11], 0)
    nDummyClk = int(nor_basic_params[12], 0)
    ndummy0 = int('0x00000000', 0)
    ndummy1 = int('0x00000000', 0)    

    # not in structure field, but for union size
    ndummy2 = int('0x00000000', 0)
    ndummy3 = int('0x00000000', 0)       
    
    hex_binary_string = struct.pack(fmt_string, 
                                    eOpMode, eFunc, eBusClock, pSPIInit, pSPICmdByp,
                                    nCMDStatus2, nCMDSuspend, nCMDResume, nSuspendBit, R_CSZ,
                                    W_CSZ, nDriving, nDummyClk, ndummy0, ndummy1, ndummy2, ndummy3)


    
    output_file.write(hex_binary_string) 
    
    


#emi_NorBasicConfig_t NorBasicParams;
def getNorBasicParams(emi_params_node, nor_basic_params):

    nor_basic_params_tag_node = emi_params_node.getElementsByTagName('emi_NorBasicConfig_t')[0]
    
    if nor_type == 'parallel':
        getParallelNorBasicParams(nor_basic_params_tag_node, nor_basic_params)
    else:
        getSpiNorBasicParams(nor_basic_params_tag_node, nor_basic_params)
   
    '''
    print 'nor_basic_params : '
    print nor_basic_params
    print "\n",        
    '''    

    return nor_basic_params


#emi_BasicConfig_t PsramBasicParams;
def getPsramBasicParams(emi_params_node, psram_basic_params):
    
    psram_basic_params_tag_node = emi_params_node.getElementsByTagName('PsramBasicParams')[0]
    psram_basic_params_tag_names = ['nOenToEnd', 'nSetupWr', 'nTurnAround', 'nPageAddAcct', 'nWenCycle',
                                  'nSetupRd', 'nWrCs', 'nRdCs', 'nOpMode', 'nType',
                                  'BurstReadWait', 'BurstWriteWait', 'nPageSize', 'BurstSize', 'nDriving']

    psram_basic_params = getLeafValues(psram_basic_params_tag_node, psram_basic_params_tag_names, psram_basic_params)
    
    
    # convert 'nOpMode', 'nType', 'BurstReadWait', 'BurstWriteWait', 'nPageSize', 'BurstSize' field value

    # nor_basic_params[8] : 'nOpMode'
    for mapping in nOpModeMappingTbl:
        if psram_basic_params[8] == mapping[0]:
            psram_basic_params[8] = mapping[1]
            break

        
    # nor_basic_params[9] : 'nType'    
    for mapping in nTypeMappingTbl:
        if psram_basic_params[9] == mapping[0]:
            psram_basic_params[9] = mapping[1]
            break    
    

    # nor_basic_params[12] : 'nPageSize'
    for mapping in nPageSizeMappingTbl:
        if psram_basic_params[12] == mapping[0]:
            psram_basic_params[12] = mapping[1]
            break                                
    
    
    # nor_basic_params[13] : 'BurstSize'
    for mapping in BurstSizeMappingTbl:
        if psram_basic_params[13] == mapping[0]:
            psram_basic_params[13] = mapping[1]
            break     

        
        
    # write to binary file    
    fmt_string = '17I'
    
    nOenToEnd = int(psram_basic_params[0], 0)
    nSetupWr = int(psram_basic_params[1], 0)
    nTurnAround = int(psram_basic_params[2], 0)
    nPageAddAcct = int(psram_basic_params[3], 0)
    nWenCycle = int(psram_basic_params[4], 0)
    nSetupRd = int(psram_basic_params[5], 0)
    nWrCs = int(psram_basic_params[6], 0)
    nRdCs = int(psram_basic_params[7], 0)
    nOpMode = int(psram_basic_params[8], 0)
    nType = int(psram_basic_params[9], 0)

    tmp_param_one = int(psram_basic_params[10].strip('(').strip(')').split('+')[0], 0)
    tmp_param_two = int(psram_basic_params[10].strip('(').strip(')').split('+')[1], 0)
    BurstReadWait = tmp_param_one + tmp_param_two

    tmp_param_one = int(psram_basic_params[11].strip('(').strip(')').split('+')[0], 0)
    tmp_param_two = int(psram_basic_params[11].strip('(').strip(')').split('+')[1], 0)
    BurstWriteWait = tmp_param_one + tmp_param_two

    nPageSize = int(psram_basic_params[12], 0)
    BurstSize = int(psram_basic_params[13], 0)
    nDriving = int(psram_basic_params[14], 0)
    ndummy0 = int('0x00000000', 0)
    ndummy1 = int('0x00000000', 0)
    
    hex_binary_string = struct.pack(fmt_string, 
                                    nOenToEnd, nSetupWr, nTurnAround, nPageAddAcct, nWenCycle,
                                    nSetupRd, nWrCs, nRdCs, nOpMode, nType,
                                    BurstReadWait, BurstWriteWait, nPageSize, BurstSize,
                                    nDriving, ndummy0, ndummy1)

    
    output_file.write(hex_binary_string)    
    
    '''
    print 'psram_basic_params : '
    print psram_basic_params
    print "\n",       
    '''   

    return psram_basic_params
    
#----------------------------------------------------------------------    

DEBUG_FLAG = False

mcp_config_list = []

nor_type = 'parallel'

if __name__ == "__main__":

    if DEBUG_FLAG == False:
    
        # parse command line to get input and output file name
        MSG_USAGE = "python xml2bin.py -i <input_file_name> -o <output_file_name>"
        parser = optparse.OptionParser(MSG_USAGE)
        
        parser.add_option("-i",
                          "--input_file_name",
                          type = "string",
                          dest = "inputFileName")
        
        parser.add_option("-o",
                          "--output_file_name",
                          type = "string",
                          dest = "outputFileName")

        parser.add_option("-s", 
                          "--skip_offset_header",
                          action="store_true", 
                          dest="skipOffset",
                          default=False) 
        
        
        options, args = parser.parse_args()    
       
        
        input_file_name = options.inputFileName
        output_file_name = options.outputFileName    
    
        
        
        try:
            input_file = open(input_file_name, 'r')
            output_file = open(output_file_name, 'wb')
        except:
            print "File Open Error!!"
    
    else:        
    
        input_file_name = 'sd_mini.xml' #'test_tmp.xml' #'save_all.xml' #  
        output_file = open('test.bin', 'wb')
    
    
    xml_dom = minidom.parse(input_file_name)

    if options.skipOffset == False:
        # write sizeof(emi_mcpConfig_t) to the beginning of binary file (reserved)
        offset = 0 # sizeof(emi_mcpConfig_t)
        hex_binary_string = struct.pack('I', offset)
        output_file.write(hex_binary_string)
        # write DIDR offset
        didr_offset = 52
        hex_binary_string = struct.pack('I', didr_offset)
        output_file.write(hex_binary_string)
        # write dummu
        dummy_header = 0
        hex_binary_string = struct.pack('I', dummy_header)
        output_file.write(hex_binary_string)
        # write dummu
        dummy_header = 0
        hex_binary_string = struct.pack('I', dummy_header)
        output_file.write(hex_binary_string)

    # assure that no flash name is repeated
    flash_names = []
    for mcp_node in xml_dom.getElementsByTagName('mcpConfig_t'):
        tag_node = mcp_node.getElementsByTagName('Identifier')[0]
        tag_value = getTagValue(tag_node, 'nFlashName', 0)
        
        if tag_value in flash_names:
            sys.exit("flash name " + str(tag_value) + " is repeated\n")
        else:
            flash_names.append(tag_value)
        
    
        
    for mcp_node in xml_dom.getElementsByTagName('mcpConfig_t'):

        mcp_config_data = []

        
        # set nor_type
        tag_node = mcp_node.getElementsByTagName('emi_params')[0]
        nor_basic_params_tag_node = tag_node.getElementsByTagName('emi_NorBasicConfig_t')[0]
        if len(nor_basic_params_tag_node.getElementsByTagName('pSPIInit')) == 0:
            nor_type = 'parallel'
        else:
            nor_type = 'serial'
        
        
        tag_node = mcp_node.getElementsByTagName('Identifier')[0]
        mcp_config_data.append(getIdentifierData(tag_node))
        nStartChar = tag_node.firstChild.nextSibling.data.find("CHIP_TYPE=") + len("CHIP_TYPE=")
        nEndChar = tag_node.firstChild.nextSibling.data.find(">")
        chip_type = tag_node.firstChild.nextSibling.data[nStartChar:nEndChar]
        
        tag_node = mcp_node.getElementsByTagName('Geometry')[0]
        mcp_config_data.append(getGeometryData(tag_node))    

        tag_node = mcp_node.getElementsByTagName('Bank')[0]
        mcp_config_data.append(getBankData(tag_node))
        
        tag_node = mcp_node.getElementsByTagName('CommandSets')[0]
        mcp_config_data.append(getCommandSetsData(tag_node))


        #get ndummy0 value
        ndummy0 = getTagValue(mcp_node, 'ndummy0', 0)
        mcp_config_data.append(ndummy0)
        # write ndummy0 value to binary file
        fmt_string = 'I'
        hex_binary_string = struct.pack(fmt_string, int(ndummy0, 0))
        output_file.write(hex_binary_string)         
        
        
        #get ndummy1 value
        ndummy1 = getTagValue(mcp_node, 'ndummy1', 0)
        mcp_config_data.append(ndummy1)
        # write ndummy0 value to binary file
        fmt_string = 'I'
        hex_binary_string = struct.pack(fmt_string, int(ndummy1, 0))
        output_file.write(hex_binary_string) 


        if nor_type == 'parallel':
            tag_node = mcp_node.getElementsByTagName('Psram_SWCmd')[0]        
            mcp_config_data.append(getSWCmdData(tag_node))        
        else:
            for x in range(48):
                hex_binary_string = struct.pack('I', 0)
                output_file.write(hex_binary_string)

        if nor_type == 'parallel':        
            tag_node = mcp_node.getElementsByTagName('Nor_SWCmd')[0]        
            mcp_config_data.append(getSWCmdData(tag_node)) 
        else:
            if chip_type == 'MSW8556x':
                tag_node = mcp_node.getElementsByTagName('emi_params')[0]
                spicmd_tag_node = tag_node.getElementsByTagName('emi_NorBasicConfig_t')[0]     
                mcp_config_data.append(getSpiCmdData(spicmd_tag_node))            
            else:
                for x in range(48):
                    hex_binary_string = struct.pack('I', 0)
                    output_file.write(hex_binary_string)
        
        tag_node = mcp_node.getElementsByTagName('emi_params')[0]        
        # proceed emi_AdvancedConfig_t
        if nor_type == 'parallel':
            emi_advan_params = []
            emi_advan_params = getEmiAdvanParams(tag_node, emi_advan_params)
            mcp_config_data.append(emi_advan_params)
        else:
            for x in range(19):
                hex_binary_string = struct.pack('I', 0)
                output_file.write(hex_binary_string)
    
        # proceed emi_NorBasicConfig_t
        nor_basic_params = []
        nor_basic_params = getNorBasicParams(tag_node, nor_basic_params)
        mcp_config_data.append(nor_basic_params)

        # proceed PsramBasicParams
        if nor_type == 'parallel':
            psram_basic_params = []
            psram_basic_params = getPsramBasicParams(tag_node, psram_basic_params)
            mcp_config_data.append(psram_basic_params)


        mcp_config_list.append(mcp_config_data)

    if options.skipOffset == False:
        if nor_type == 'parallel':
            offset = 768 # sizeof(emi_mcpConfig_t)
        else:
            offset = 700 # sizeof(emi_mcpConfig_t)
        hex_binary_string = struct.pack('I', offset)
        output_file.seek(0)
        output_file.write(hex_binary_string)
        
    if DEBUG_FLAG == False:        
        if input_file != None:
            input_file.close()
        if output_file != None:    
            output_file.close()
    else:
        output_file.close()

    
    
    '''    
    for index in range(0, len(mcp_config_list)):
        
        print "\nmcp_config No.%d" % index

        print "identifier data:"
        print mcp_config_list[index][0]

        print "geometry data:"
        print mcp_config_list[index][1]
        
        print "bank data:"
        print mcp_config_list[index][2]

        print "command_sets data:"
        print mcp_config_list[index][3]        
        
        print "ndummy0 data:"
        print mcp_config_list[index][4] 
        
        print "ndummy1 data:"
        print mcp_config_list[index][5] 
        
        print "psram swcmd data:"
        print mcp_config_list[index][6]
        
        print "nor swcmd data:"
        print mcp_config_list[index][7]        
        
        print "emi_params data:"
        print mcp_config_list[index][8]            
    '''        
        

        
        
        
