/****************************************************************************/
/*  File    : GSMSYST.HC                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   : General definition of the GSM constants                       */
/*            Some of them are compilation flag dependant                   */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Changes    :                                                            */
/*--------------------------------------------------------------------------*/
/*   Date   | Author | Err  |  Modification                                 */
/*----------+--------+------+-----------------------------------------------*/
/* 09/01/97 | pfa    |      |  creation                                     */
/* 04/03/98 | aja    |      |  Ajout bande PCS 1900                         */
/* 09/04/99 | aja,rma|      |  Ajout des paramˆtres de config de bearers    */
/* 04/05/99 |  FCO   |      |  modem 14.4Kbit/s : BEARER_CFG_DATA_144KB     */
/* 22/09/99 |  FCO   |      |  User Rate BEARER_CFG_DATA_600NT supported    */
/*----------+--------+------+-----------------------------------------------*/
/****************************************************************************/
/*
$LogWavecom: G:\projet\gsm\pvcsarch\archives\fc\com\gsmsyst.hc-arc $
 * --------------------------------------------------------------------------
 *  Date     | Author | Revision       | Description
 * ----------+--------+----------------+-------------------------------------
 *  23.04.03 | apa    | 3.2            | Resolution tracker 9721 : bad defin
 *           |        |                | e using TCH_AMR  flag in CC  Resolu
 *           |        |                | tion for 9721: Add some defines in 
 *           |        |                | gsmsyst.hc in order to compile with
 *           |        |                |  __TCH_AMR__ flag                  
 * ----------+--------+----------------+-------------------------------------
 *  02.10.02 | ddo    | 3.1            | Merge tf v19+ with rev 1.7         
 * ----------+--------+----------------+-------------------------------------
 *  02.10.02 | ddo    | 3.0            | integration dev tf V19             
 * ----------+--------+----------------+-------------------------------------
*/

#ifndef GSMSYST_HC
#define GSMSYST_HC

/*
**-------------------------------------------------  
** Definition of flags to be used for compilation   
**-------------------------------------------------   
   

   Band : 
           __850__     GSM      850 MHz
           __P900__    primary  900 Mhz
           __E900__    Extended 900 Mhz
           __DCS1800__ DCS     1800 Mhz
           __PCS1900__ PCS     1900 Mhz

   Traces :
           __DIAGNOSE__                   enables traces code

   Phase :
           __PHASE1__                     for Phase 1
           __PHASE2__                     for Phase 2


*/


  /*-----------------------------------------------------------**
  **                                                           **
  ** Band and frequency list defintions      (TS-05.05)        **
  **                                                           **
  **-----------------------------------------------------------**
  ** Band                     Arfcn         Reduced            **
  **-----------------------------------------------------------**
  **  850    [128..251]            Ofst = 127                  **
  **-----------------------------------------------------------**
  **                                                           **
  **                           128             1               **
  **                           129             2               **
  **                           ...           ...               **
  **                           251           124               **
  **                                                           **
  **-----------------------------------------------------------**
  ** P_900    [1..124]              Ofst = 0                   **
  **-----------------------------------------------------------**
  **                                                           **
  **                            1              1               **
  **                            2              2               **
  **                           ...           ...               **
  **                           124           124               **
  **                                                           **
  **                                                           **
  **-----------------------------------------------------------**
  ** E_900    [975..1023][0..124]    Ofst = 974                **
  **-----------------------------------------------------------**
  **                                                           **
  **                           975             1               **
  **                           976             2               **
  **                           ...            ..               **
  **                          1023            49               **
  **                             0            50               **
  **                             1            51               **
  **                           ...           ...               **
  **                           124           174               **
  **                                                           **
  **-----------------------------------------------------------**
  ** DCS1800  [512..885]             Ofst = 511                **
  **-----------------------------------------------------------**
  **                                                           **
  **                           512             1               **
  **                           ...           ...               **
  **                                                           **
  **                           885           374               **
  **                                                           **
  **-----------------------------------------------------------**
  ** PCS1900  [512..810]             Ofst = 511                **
  **-----------------------------------------------------------**
  **                                                           **
  **                           512             1               **
  **                           ...           ...               **
  **                                                           **
  **                           810           299               **
  **                                                           **
  **-----------------------------------------------------------**

  */

/* Bands supported */
#define         BAND_GSM_P900             0x01        
#define         BAND_GSM_E900             0x02
#define         BAND_DCS_1800             0x04
#define         BAND_PCS_1900             0x08
/* modif OVC GSM850 */
#define 	BAND_GSM_850		  0x10
/*08/11/06 modified for quad band{*/
#ifdef __QUAD_BAND_SUPPORT__
#define         BAND_QUAD                 0x40
#endif

/*
** Maximum number of frequencies
*/
#define PH_NBMAX_P900_FREQ   124  
#define PH_NBMAX_E900_FREQ   174  
#define PH_NBMAX_1800_FREQ   374  
#define PH_NBMAX_1900_FREQ   299  
/* modif OVC GSM850 */
#define PH_NBMAX_850_FREQ    124 


/* modif OVC GSM850 */
/** nombre de frequence dans chaque bande */
/* NbFreqBand[RR_BAND_GSM] */
#define NBFREQ_850   124  /* 128->251 */
#define NBFREQ_900   124  /* 1->124 */
/* NbFreqBand[RR_BAND_DCS] */
#define NBFREQ_E900    49  /* 975->1023 (partie haute de la bande E900) */
#define NBFREQ_1800   374  /* 512->885 */
#define NBFREQ_1900   299  /* 512->810 */

/** offset de frequence dans chaque bande */
#define FREQ_OFST_850        127 /*= 128-1 */
#define FREQ_OFST_900        0	 /*= 1-1*/
#define FREQ_OFST_E900       974 /*= 975-1 (partie haute de la bande E900) */
#define FREQ_OFST_1800       511 /*= 512-1 */
#define FREQ_OFST_1900       511 /*= 512-1 */


/*
** Ofsets defintions for conversion
** Arfcn [0..1023] to Arfcn [1..374]
*/
 
#define P900_FREQ_OFST         0
#define E900_FREQ_OFST       974
#define DCS_FREQ_OFST        511
#define PCS_FREQ_OFST        511

/*08/11/06 modified for quad band{*/
#ifdef __QUAD_BAND_SUPPORT__
#define PH_NBMAX_MTBD_FREQ   (548+124+299)  
#else
#define PH_NBMAX_MTBD_FREQ   548
// 548=NBFREQ_900+NBFREQ_E900+1+NBFREQ_1800, where "+1" indicates the band 0 of E900
#endif

/* 
** We use a compilation flag to define the Band 
*/
#define PH_NBMAX_FREQ    PH_NBMAX_MTBD_FREQ


  /*-----------------------------------------------------------**
  **                                                           **
  ** BEARER CONFIG PARAMETERS                                  **
  **                                                           **
  **-----------------------------------------------------------**/

#define BEARER_CFG_EFR           0x0001
#define BEARER_CFG_HALF_RATE     0x0002
#define BEARER_CFG_DATA_24KB     0x0004
#define BEARER_CFG_DATA_48KB     0x0008
#define BEARER_CFG_DATA_96KB     0x0010
#define BEARER_CFG_ALTERN        0x0020
#define BEARER_CFG_DATA_ON       0x0040
#define BEARER_CFG_FAX_ON        0x0080
#define BEARER_CFG_DATA_144KB    0x0100
#define BEARER_CFG_FAX_CLASS_2   0x0200              
#define BEARER_CFG_FAX_ECM       0x0400       
#define BEARER_CFG_DATA_V42_BIS  0x0800 
#define BEARER_CFG_DATA_V42      0x1000
#define BEARER_CFG_DATA_600NT    0x2000  /* UR < 600 bits/s Non Transparent supported */
#define BEARER_CFG_AMR_FR        0x4000
#define BEARER_CFG_AMR_HR        0x8000
#define BEARER_CFG_DATA_HR       0x200000

#endif
