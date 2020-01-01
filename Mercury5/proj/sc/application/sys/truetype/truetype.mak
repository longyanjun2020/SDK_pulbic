#------------------------------------------------------------------------------
#   List of source  files   of  the library or  executable to generate
#------------------------------------------------------------------------------
SRC_C_LIST =    \
	smooth.c\
	truetype.c\
	sfnt.c\
	ftstream.c\
	ftsystem.c\
	fttrigon.c\
	ftutil.c\
	ftadvanc.c\
	ftapi.c\
	ftcalc.c\
	ftgloadr.c\
	ftinit.c\
	ftobjs.c\
	ftoutln.c\
	ftcache.c\
	ftglyph.c\
	ftbitmap.c\
	ftotval.c\
	otvalid.c\
	otvbase.c\
	otvcommn.c\
	otvgdef.c\
	otvgpos.c\
	otvgsub.c\
	otvjstf.c\
	otvmath.c\
	otvmod.c

PATH_H += \
	$(PATH_truetype)/freetype2/inc\
	$(PATH_truetype)/freetype2/src/base\
	$(PATH_truetype)/freetype2/src/sfnt\
	$(PATH_truetype)/freetype2/src/smooth\
	$(PATH_truetype)/freetype2/src/truetype\
	$(PATH_truetype)/freetype2/src/cache\
	$(PATH_truetype)/freetype2/src/otvalid
	
PATH_C +=\
	$(PATH_truetype)/freetype2/src/base\
	$(PATH_truetype)/freetype2/src/sfnt\
	$(PATH_truetype)/freetype2/src/smooth\
	$(PATH_truetype)/freetype2/src/truetype\
	$(PATH_truetype)/freetype2/src/cache\
	$(PATH_truetype)/freetype2/src/otvalid
