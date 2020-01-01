#ifndef INDCALENDAR_PUB_H
#define INDCALENDAR_PUB_H

#ifdef __INDIAN_CALENDAR__

#define INDIAN_FESTIVAL_NUM 32
#define INDIAN_STRING_MAX_LENTH 40

/*
 * When __INDIAN_CALENDAR_SECTION__ is set,
 * put the three big tables aFestivalIndex, aTithiStartTime and aSunriseTime
 * into a sldlm (static link dynamic load module) to save code size.
 */
#if defined(__TARGET__) && defined(__arm)
#define __INDIAN_CALENDAR_SECTION__ __attribute__((section(".indcalendar_buffer")))
#else
#define __INDIAN_CALENDAR_SECTION__
#endif

enum
{
    // indian
    MAUNI_AMAVAS,
    VASAN_PANCHAMI,
    MAHA_SHIVARATI,
    RANGWALU_HOLI,
    YAGADI,
    RAM_NAUMI,
    HANUMAN_JAYANTI,
    AKSHAYA_TRITIYA,
    BUDDHA_PURIMA,
    RAMDHAN_BEGINS,
    NAG_PANCHAMI,
    RAKSHA_BANDHAN,
    KRISHNA_JANMASHTAMI,
    GANESH_CHATURTHI,
    SARVAPITRU_AMAVASYA,
    NAVRATRI_STARTED,
    DUSSEHRA,
    DHAN_TERAS,
    DIWALI_LAKSHAMI,
    BHAIYA_DUJ,
    KARTIK_PURNIMA,
    // western
    REPUBLIC_DAY,
    VALENTINE,
    SOLAR_NEW_YEAR,
    GOOD_FRIDAY,
    INDEPENDENT_DAY,
    GANDHI,
    CHRISTMAS
};
typedef unsigned int Festival_Enum;



enum
{
    NOT_LEAP,
    LEAP_SECTION_1,
    LEAP_SECTION_2,
    LEAP_SECTION_3,
    LEAP_SECTION_4,
};
typedef unsigned int IndianCalendar_LeapType;
/*
western_to_indian, 
input :an western date offset nWestDateOffset
output : indian Tithi table's index
*/
void western_to_indian(unsigned int nWestDateOffset, int * TithiIndex);

/*
indian_to_western
input: indian date, leap type
output: 0~2 western dates ,  sunrise table's index
*/
void indian_to_western(int year,int month,int day, IndianCalendar_LeapType eLeapType, int *num, int *SunriseIndex1,int *SunriseIndex2);

/*
yearly_tithi
input: indian tithi(1~14, 15, 30), indian year(2068~)
output: western(sunrise) tables index, may multiple, 
(**ppOutputIndex) is an int array and (* pSizeofOutput) is the length
*/
void yearly_tithi(int year, unsigned int Tithi , int *pOutputIndex,  unsigned int * pSizeofOutput);

/*
Indian_tithi_index_to_date
input: nIndex of aTithiStartTime
output: Indian date and leap type pIsInLeapMonth
if Error return -1 
*/
int Indian_tithi_index_to_date(int nIndex, unsigned short* pYear,unsigned short* pMonth,unsigned short* pDay, IndianCalendar_LeapType *pIsInLeapMonth);


/*
the only api that can access aTithiStartTime
*/
static unsigned int Indian_get_tithi_start_time(unsigned int nIndex);
/*
the only api that can access aSunriseTime
*/
unsigned int Indian_get_sunrise_time(unsigned int nIndex);

int IsLeapMonth(unsigned int nYear,unsigned int nMonth);

unsigned short Festival_get_western_index(unsigned int nYear,Festival_Enum eFestival);

void sunrisetime_to_festival(unsigned int nOffset, unsigned int *pYear,unsigned int *nNum,Festival_Enum *pFestival);

    
#endif //__INDIAN_CALENDAR__
#endif /* MMI_CALENDARAPP_INDIAN_UTIL_H */

