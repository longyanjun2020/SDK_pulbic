#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib


#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

# c file list
SRC_C_LIST = \
	Font_19_West.c\
	Font_20_French.c\
	Font_20_German.c\
	Font_20_Italian.c\
	Font_20_Latvian.c\
	Font_20_Polish.c\
	Font_20_Portuguese.c\
	Font_20_Romanian.c\
	Font_20_Russian.c\
	Font_20_Slovak.c\
	Font_20_Spanish.c\
	Font_20_Ukraninian.c\
	Font_20_West.c\
	Font_24_English.c\
	Font_24_Japanese.c\
	Font_24_Korean.c\
	Font_24_SChinese.c\
	Font_24_TChinese.c\
	LargeCzechOSDStringsPool.c\
	LargeEnglishOSDStringsPool.c\
	LargeFrenchOSDStringsPool.c\
	LargeGermanOSDStringsPool.c\
	LargeItalianOSDStringsPool.c\
	LargeJapaneseOSDStringsPool.c\
	LargeKoreanOSDStringsPool.c\
	LargeLatvianOSDStringsPool.c\
	LargePolishOSDStringsPool.c\
	LargePortugueseOSDStringsPool.c\
	LargeRomanianOSDStringsPool.c\
	LargeRussianOSDStringsPool.c\
	LargeSChineseOSDStringsPool.c\
	LargeSlovakOSDStringsPool.c\
	LargeSpanishOSDStringsPool.c\
	LargeTChineseOSDStringsPool.c\
	LargeUkraninianOSDStringsPool.c\
	F28B_ASCII.c\
	Font_16_English.c\
	Font_16_French.c\
	Font_16_German.c\
	Font_16_Italian.c\
	Font_16_Japanese.c\
	Font_16_Korean.c\
	Font_16_Latvian.c\
	Font_16_Polish.c\
	Font_16_Portuguese.c\
	Font_16_Romanian.c\
	Font_16_Russian.c\
	Font_16_SChinese.c\
	Font_16_Slovak.c\
	Font_16_Spanish.c\
	Font_16_TChinese.c\
	Font_16_Ukraninian.c\
	Font_16_West.c\
	CzechOSDStringsPool.c\
	EnglishOSDStringsPool.c\
	FrenchOSDStringsPool.c\
	GermanOSDStringsPool.c\
	ItalianOSDStringsPool.c\
	JapaneseOSDStringsPool.c\
	KoreanOSDStringsPool.c\
	LatvianOSDStringsPool.c\
	PolishOSDStringsPool.c\
	PortugueseOSDStringsPool.c\
	RomanianOSDStringsPool.c\
	RussianOSDStringsPool.c\
	SChineseOSDStringsPool.c\
	SlovakOSDStringsPool.c\
	SpanishOSDStringsPool.c\
	TChineseOSDStringsPool.c\
	UkraninianOSDStringsPool.c\
	
PATH_H +=\
  $(PATH_core_lib_gui_inc_Core)\
  $(PATH_core_lib_gui_inc_Config)\
  $(PATH_project_Dvr_CarDV_SDK_OSDIcon)/inc\

PATH_C +=\
	$(PATH_project_Dvr_CarDV_SDK_OSDString)/Font/\
	$(PATH_project_Dvr_CarDV_SDK_OSDString)/Font/FontLarge/\
	$(PATH_project_Dvr_CarDV_SDK_OSDString)/OSDStringsPool/\

