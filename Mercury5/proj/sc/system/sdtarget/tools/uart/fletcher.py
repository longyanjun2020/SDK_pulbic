import zlib
import struct

def checksum(iStr):
	"""
	Returns a tuple with the two bytes
	of the fletcher checksum of iStr
	"""
	a=0
	b=0
	for x in iStr:
		a = a + ord(x)
		if a>255:
			a = a - 255
		b = b + a
		if b>255:
			b = b - 255
	return  (255 - ((a+b)%255), b)

def readAndPad(iFile, iSize):
	"""
	Reads iSize bytes from iFile, returns the resulting string.
	Pads the result to match an exact size of iSize bytes.
	Returns a null string when EOF is reached.
	"""
	a = iFile.read(iSize)
	if len(a) == iSize:
		return a
	if len(a) == 0:
		return ''
	a = a + '\0'*(iSize - len(a))
	return a

def slicefile(iFileName, iSize, iHeaderStr):
	"""
	Returns strings with hex-ed of iHeaderStr+chunks of iSize bytes
	from iFileName. iFileName is padded with zeros to get a round
	number of iSize-sized frames.
	"""
	fp = file(iFileName, "rb")
	retlist = []
	a = readAndPad(fp, iSize)
	while len(a) > 0:
		listitem = str()
		a = iHeaderStr+a
		fcks = checksum(a)
		for x in a:
			listitem = listitem + "%02X " % ord(x)
		listitem = listitem + "%02X %02X" % fcks
		retlist.append(listitem)
		# Next chunk
		a = readAndPad(fp, iSize)
	fp.close()
	return retlist

def lastframe(iFileName, iSize):
	"""
	Computes the Adler checksum of the file iFileName, 
	as if it had been downloaded by iSize-sized frames,
	padded with zeros when necessary.
	"""
	fp = file(iFileName, "rb")
	adlerchksum = long(1)
	a = readAndPad(fp, iSize)
	while len(a) > 0:
		adlerchksum = zlib.adler32(a, adlerchksum)
		a = readAndPad(fp, iSize)
	fp.close()
	packedadlerchksum = struct.pack("<L", adlerchksum)
	retstr = ''
	for x in '\x04'+packedadlerchksum:
		retstr = retstr + "%02X " % ord(x)
	retstr = retstr + "%02X %02X" % checksum('\x04'+packedadlerchksum)
	return retstr

	
