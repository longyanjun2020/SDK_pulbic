import sys, os, struct, ctypes, argparse

def ERROR(x): print "!!ERROR!! "+x

def ERROR(x,exception): 
    print "!!ERROR!! "+x
    print "    => ", exception

def WARNING(x): print "!!WARNING!! "+x   

class E2PRecord:
    pass


def FMS_E2P_COMPUTE_CKSUM(offset,length):
    WordOffset=ctypes.c_ushort(offset).value
    Length=ctypes.c_ushort(length).value
    return ((WordOffset & 0xFF) ^ (WordOffset >> 8) ^ (Length & 0xFF) ^ (Length >> 8))

def genE2PRecordHeaderBytes(r,db):
#typedef struct
#{
#   u16 b14_address:14;
#   u16 b_isBeingCreatedBit:1;
#   u16 b_isNotDeletedBit:1;
#   u16 u16_length;
#   u8 u8_checksum_h;
#   u8 u8_checksum_d;
#} fms_E2pSoftRecHeader_t;

    bs=struct.pack("HHBB",(r.offset & 0xBFFF),r.size,FMS_E2P_COMPUTE_CKSUM(r.offset, r.size),reduce(lambda x,y:x^y,map(ord,db)) )
    bs+=('\x00'*(r.size&0x1))
    return bs

def toHexString(bs):
    return " ".join("{:02X}".format(ord(c)) for c in bs)

def genE2PRecordDataBytes(r):
    try:
        for line in r.rawData.splitlines():
            tokens=line.split(" ")
            dataType=tokens[-1]
            dataBytes=""
            packString=""
            if dataType == "%u8":
                for tok in tokens[:-1]: dataBytes+=(struct.pack("<B",int(tok,0)))
            elif dataType == "%s8":
                for tok in tokens[:-1]: dataBytes+=(struct.pack("<b",int(tok,0)))
            elif dataType == "%u16":
                for tok in tokens[:-1]: dataBytes+=(struct.pack("<H",int(tok,0)))
            elif dataType == "%s16":
                for tok in tokens[:-1]: dataBytes+=(struct.pack("<h",int(tok,0)))
            elif dataType == "%u32":
                for tok in tokens[:-1]: dataBytes+=(struct.pack("<I",int(tok,0)))
            elif dataType == "%s32":
                for tok in tokens[:-1]: dataBytes+=(struct.pack("<i",int(tok,0)))
            elif dataType == "%ascii":
                for tok in tokens[:-1]: dataBytes+=tok
            else :
                ERROR('Unknown dataType: '+dataType+' for '+r.itemName+' in '+r.file)
                break;
    except Exception as err:
        print ''
#        ERROR('Exception when converting E2P value for '+r.itemName+' in '+r.file,err)
    if len(dataBytes) < r.size: 
#        WARNING('Padding '+str(r.size-len(dataBytes))+'*0x00 for '+r.itemName+' in '+r.file)
        dataBytes+= ('\x00'*(r.size-len(dataBytes)))
    return dataBytes;


def parseE2PFile(E2PFile):
    recordList=[]
    record=None
    for line in open(E2PFile):
        line=line.strip()
        if len(line)==0: continue
        if line[0] == 'W':
            if record is not None:
                recordList.append(record)
                record=None
            tokens=line.split(" ")
            record=E2PRecord()
            record.rawData=""
            record.file=E2PFile
            record.itemName=tokens[0][1:]
            record.offset=int(tokens[1])
            record.size=int(tokens[2])
            record.subFields=int(tokens[3])
            record.defString=line
        else:
            record.rawData+=(line+"\n")
    if record is not None:
        recordList.append(record)
        record=None
    return recordList

def getE2PRecordInfo(r):
    info = ( 'ItemName: '+r.itemName + '\n'
            'Offset: '+str(r.offset)+ '\n'
            'Size: '+str(r.size)+ '\n'
            'SubFields: '+str(r.subFields)+ '\n'
            'File: '+r.file+ '\n'
            'DefString: '+r.defString+ '\n'
            '[RawData]\n'+r.rawData+ '\n'
           )
    return info



def main():
    parser = argparse.ArgumentParser(description='Generate E2P bin for NOR_FLASH')
    parser.add_argument("--e2p", help="E2P file list")
    parser.add_argument("--out", help="output binary file")
    parser.add_argument("--mode", help="output binary file",default="factory")

    args=parser.parse_args()

    print 'mode: '+args.mode

    out=open(args.out,'w')

    for fn in args.e2p.split(' '):
        print '\n<<<< '+fn
        recordList=parseE2PFile(fn)

        for r in recordList :
            db=genE2PRecordDataBytes(r)
            hb=genE2PRecordHeaderBytes(r,db)
            if args.mode == 'factory':
                if out.tell()>r.offset:
#                    WARNING('Over writing E2P record for '+r.itemName+' in '+r.file+' at '+str(r.offset))
                    out.seek(r.offset,0)
                else:
                    out.write('\x00'*(r.offset-out.tell()))
            else:
                out.write(hb)

            out.write(db)
            out.seek(0,2)

    if args.mode=="factory":
        if out.tell() < 0x2000:
            out.write('\x00'*(0x2000-out.tell()))
        out.seek(0x1FFE,0)
        out.write('\x7f\xff')

    out.close()
    print '>>>> '+args.out

if __name__ == "__main__":
    main()