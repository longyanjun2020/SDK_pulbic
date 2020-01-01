
/**
 * @file
 * Map browser attribute to css  attribute
 */


#ifndef _DBA_CSSPRPTMAP_H_
#define _DBA_CSSPRPTMAP_H_

#include <wap_config.h>
#ifdef   DB_USING_CSS

#include <css_property.h>
#include <css_parser.h>

#define DBA_CSS_PRDisplay            PRDisplay            /*0  display */
#define DBA_CSS_PRHeight             PRHeight             /*1  height  */
#define DBA_CSS_PRWidth              PRWidth              /*2  width   */
#define DBA_CSS_PRMarginTop          PRMarginTop          /*3  margin-top */
#define DBA_CSS_PRMarginRight        PRMarginRight        /*4  margin-right */
#define DBA_CSS_PRMarginBottom       PRMarginBottom       /*5  margin-bottom */
#define DBA_CSS_PRMarginLeft         PRMarginLeft         /*6  margin-left */
#define DBA_CSS_PRPaddingTop         PRPaddingTop         /*7  padding-top */
#define DBA_CSS_PRPaddingRight       PRPaddingRight       /*8  padding-right */
#define DBA_CSS_PRPaddingBottom      PRPaddingBottom      /*9  padding-bottom */
#define DBA_CSS_PRPaddingLeft        PRPaddingLeft        /*10 padding-left */
#define DBA_CSS_PRBorderTopWidth     PRBorderTopWidth     /*11 border-top-width */
#define DBA_CSS_PRBorderRightWidth   PRBorderRightWidth   /*12 border-right-width */
#define DBA_CSS_PRBorderBottomWidth  PRBorderBottomWidth  /*13 border-bottom-width */
#define DBA_CSS_PRBorderLeftWidth    PRBorderLeftWidth    /*14 border-left-width */
#define DBA_CSS_PRBorderTopColor     PRBorderTopColor     /*15 border-top-color */
#define DBA_CSS_PRBorderRightColor   PRBorderRightColor   /*16 border-right-color */
#define DBA_CSS_PRBorderBottomColor  PRBorderBottomColor  /*17 border-bottom-color */
#define DBA_CSS_PRBorderLeftColor    PRBorderLeftColor    /*18 border-left-color */
#define DBA_CSS_PRBorderTopStyle     PRBorderTopStyle     /*19 border-top-style */
#define DBA_CSS_PRBorderRightStyle   PRBorderRightStyle   /*20 border-right-style */
#define DBA_CSS_PRBorderBottomStyle  PRBorderBottomStyle  /*21 border-bottom-style */
#define DBA_CSS_PRBorderLeftStyle    PRBorderLeftStyle    /*22 border-left-style */
#define DBA_CSS_PRSize               PRSize               /*23 font-size */
#define DBA_CSS_PRStyle              PRStyle              /*24 font-style */
#define DBA_CSS_PRWeight             PRWeight             /*25 font-weight */
#define DBA_CSS_PRFont               PRFont               /*26 font-family */
#define DBA_CSS_PRUnderline          PRUnderline          /*27 text-decoration */
#define DBA_CSS_PRIndent             PRIndent             /*28 text-indent */
#define DBA_CSS_PRLineSpacing        PRLineSpacing        /*29 line-height */
#define DBA_CSS_PRAdjust             PRAdjust             /*30 text-align */
#define DBA_CSS_PRDirection          PRDirection          /*31 direction */
#define DBA_CSS_PRUnicodeBidi        PRUnicodeBidi        /*32 unicode-bidi */
#define DBA_CSS_PRBackground         PRBackground         /*33 background-color */
#define DBA_CSS_PRForeground         PRForeground         /*34 foreground-color */
#define DBA_CSS_PRBackgroundPicture  PRBackgroundPicture  /*35 background-image */
#define DBA_CSS_PRPictureMode        PRPictureMode        /*36 background-repeat */
#define DBA_CSS_PRPageBefore         PRPageBefore         /*37 page-break-before */
#define DBA_CSS_PRPageAfter          PRPageAfter          /*38 page-break-after */
#define DBA_CSS_PRPageInside         PRPageInside         /*39 page-break-inside */
#define DBA_CSS_PRAttachMode         PRAttachMode         /*40 background-attachment */
#define DBA_CSS_PRPositionMode       PRPositionMode       /*41 background-position */

#define DBA_CSS_PRListtype           PRListtype           /*42 list-style-type */
#define DBA_CSS_PRListimage          PRListimage          /*43 list-style-image */
#define DBA_CSS_PRListposition       PRListposition       /*44 list-style-position */
#define DBA_CSS_PRListstyle          PRListstyle          /*45 list-style */
#define DBA_CSS_PRBlank              PRBlank              /*46 white-space */
#define DBA_CSS_PRClear              PRClear              /*47 clear */
#define DBA_CSS_PRFloat              PRFloat              /*48 float */
#define DBA_CSS_PRVerticalalign      PRVerticalalign      /*49 vertical-align */
#define DBA_CSS_PRTexttransform      PRTexttransform      /*50 text-transform */
#define DBA_CSS_PRLetterspacing      PRLetterspacing      /*51 letter-spacing */
#define DBA_CSS_PRWordspacing        PRWordspacing        /*52 word-spacing */
#define DBA_CSS_PRVariant            PRVariant            /*53 font-variant */



/* values for rules PRBorder*Style */
#define DBA_CSS_STYLE_BORDERNONE    STYLE_BORDERNONE      /*1*/
#define DBA_CSS_STYLE_BORDERHIDDEN  STYLE_BORDERHIDDEN    /*2*/
#define DBA_CSS_STYLE_BORDERDOTTED  STYLE_BORDERDOTTED    /*3*/
#define DBA_CSS_STYLE_BORDERDASHED  STYLE_BORDERDASHED    /*4*/
#define DBA_CSS_STYLE_BORDERSOLID   STYLE_BORDERSOLID     /*5*/
#define DBA_CSS_STYLE_BORDERDOUBLE  STYLE_BORDERDOUBLE    /*6*/
#define DBA_CSS_STYLE_BORDERGROOVE  STYLE_BORDERGROOVE    /*7*/
#define DBA_CSS_STYLE_BORDERRIDGE   STYLE_BORDERRIDGE     /*8*/
#define DBA_CSS_STYLE_BORDERINSET   STYLE_BORDERINSET     /*9*/
#define DBA_CSS_STYLE_BORDEROUTSET  STYLE_BORDEROUTSET    /*10*/

/* values for rule PRStyle */
#define DBA_CSS_STYLE_FONT_NORMAL   STYLE_FONT_NORMAL     /*1*/
#define DBA_CSS_STYLE_FONT_ITALICS  STYLE_FONT_ITALICS    /*2*/
#define DBA_CSS_STYLE_FONT_OBLIQUE  STYLE_FONT_OBLIQUE    /*3*/



/* values for rule PRFont */
#define DBA_CSS_STYLE_FONT_TIMES     STYLE_FONT_TIMES     /*1*/
#define DBA_CSS_STYLE_FONT_HELVETICA STYLE_FONT_HELVETICA /*2*/
#define DBA_CSS_STYLE_FONT_COURIER   STYLE_FONT_COURIER   /*3*/

/* values for rule PRUnderline----textdecoration*/
#define DBA_CSS_STYLE_NOUNDERLINE   STYLE_NOUNDERLINE     /*1*/
#define DBA_CSS_STYLE_UNDERLINE     STYLE_UNDERLINE       /*2*/
#define DBA_CSS_STYLE_OVERLINE      STYLE_OVERLINE        /*3*/
#define DBA_CSS_STYLE_CROSSOUT      STYLE_CROSSOUT        /*4*/

/* values for rule PRAdjust */
#define DBA_CSS_STYLE_ADJUSTLEFT           STYLE_ADJUSTLEFT          /*1*/
#define DBA_CSS_STYLE_ADJUSTRIGHT          STYLE_ADJUSTRIGHT         /*2*/
#define DBA_CSS_STYLE_ADJUSTCENTERED       STYLE_ADJUSTCENTERED      /*3*/
#define DBA_CSS_STYLE_ADJUSTJUSTIFY        STYLE_ADJUSTJUSTIFY       /*4*/
#define DBA_CSS_STYLE_ADJUSTLEFTWITHDOTS   STYLE_ADJUSTLEFTWITHDOTS  /*5*/

/* values for rule PRDirection */
#define DBA_CSS_STYLE_LEFTTORIGHT          STYLE_LEFTTORIGHT         /*1*/
#define DBA_CSS_STYLE_RIGHTTOLEFT          STYLE_RIGHTTOLEFT         /*2*/

/* values for rule PRUnicodeBidi */
#define DBA_CSS_STYLE_BIDINORMAL           STYLE_BIDINORMAL          /*1*/
#define DBA_CSS_STYLE_BIDIEMBED            STYLE_BIDIEMBED           /*2*/
#define DBA_CSS_STYLE_BIDIOVERRIDE         STYLE_BIDIOVERRIDE        /*3*/

/* values for rule PRDisplay */
#define DBA_CSS_STYLE_DISPLAYNONE          STYLE_DISPLAYNONE         /*0*/
#define DBA_CSS_STYLE_DISPLAYUNDEFINED     STYLE_DISPLAYUNDEFINED    /*1*/
#define DBA_CSS_STYLE_DISPLAYINLINE        STYLE_DISPLAYINLINE       /*2*/
#define DBA_CSS_STYLE_DISPLAYBLOCK         STYLE_DISPLAYBLOCK        /*3*/
#define DBA_CSS_STYLE_DISPLAYLISTITEM      STYLE_DISPLAYLISTITEM     /*4*/
#define DBA_CSS_STYLE_DISPLAYRUNIN         STYLE_DISPLAYRUNIN        /*5*/
#define DBA_CSS_STYLE_DISPLAYCOMPACT       STYLE_DISPLAYCOMPACT      /*6*/
#define DBA_CSS_STYLE_DISPLAYMARKER        STYLE_DISPLAYMARKER       /*7*/

/* value for PRForeground --foreground color: RGB */

/* value for PRBackground----background color transparent */
#define DBA_CSS_STYLE_BACKGROUNDCOLOR_TRANS  STYLE_BACKGROUNDCOLOR_TRANS   /*1*/

/* value for PRPictureMode-----background repeat */
#define DBA_CSS_STYLE_REALSIZE            STYLE_REALSIZE             /*1*/
#define DBA_CSS_STYLE_SCALE               STYLE_SCALE                /*2*/
#define DBA_CSS_STYLE_REPEAT              STYLE_REPEAT               /*3*/
#define DBA_CSS_STYLE_VREPEAT             STYLE_VREPEAT              /*4*/
#define DBA_CSS_STYLE_HREPEAT             STYLE_HREPEAT              /*5*/

/* value for PRAttachMode----background attachment */
#define DBA_CSS_STYLE_SCROLL              STYLE_SCROLL               /*1*/
#define DBA_CSS_STYLE_FIXED               STYLE_FIXED                /*2*/

/* value for PRPositionMode-----background position */
#define DBA_CSS_STYLE_LEFT                STYLE_LEFT                 /*1*/
#define DBA_CSS_STYLE_RIGHT               STYLE_RIGHT                /*2*/
#define DBA_CSS_STYLE_CENTER              STYLE_CENTER               /*3*/
#define DBA_CSS_STYLE_TOP                 STYLE_TOP                  /*4*/
#define DBA_CSS_STYLE_BOTTOM              STYLE_BOTTOM               /*5*/

/* value for PRPageBefore,PRPageAfer,PRPageInside-----
pagebreakbefore pagebreakafter pagebreakinside */
#define DBA_CSS_STYLE_AUTO                STYLE_AUTO                 /*0*/
#define DBA_CSS_STYLE_ALWAYS              STYLE_ALWAYS               /*1*/
#define DBA_CSS_STYLE_AVOID               STYLE_AVOID                /*2*/
#define DBA_CSS_STYLE_PAGELEFT            STYLE_PAGELEFT             /*3*/
#define DBA_CSS_STYLE_PAGERIGHT           STYLE_PAGERIGHT            /*4*/
#define DBA_CSS_STYLE_INHERIT             STYLE_INHERIT              /*5*/


/* CSS category */
#define DBA_CSS_INLINE_SYTLE              CSS_INLINE_SYTLE           /*0  inline CSS <p style="color:red"> */
#define DBA_CSS_DOCUMENT_STYLE            CSS_DOCUMENT_STYLE         /*1  a <style> element in the document */
#define DBA_CSS_EXTERNAL_STYLE            CSS_EXTERNAL_STYLE         /*2  an external CSS */

/* HTML query type */
#define DBA_CSS_TAG_SINGLE               TAG_SINGLE                  /*0  <p> example */
#define DBA_CSS_TAG_STYLE                TAG_STYLE                   /*1  <p style="color:red"> example */
#define DBA_CSS_TAG_ID                   TAG_ID                      /*2  <p ID=id1> example */
#define DBA_CSS_TAG_CLASS                TAG_CLASS                   /*3  <p CLASS=class1> example */
#define DBA_CSS_TAG_MULTIPLE_DEFINE      TAG_MULTIPLE_DEFINE         /*4  mix of the above*/
#define DBA_CSS_TAG_COMBINE              TAG_COMBINE                 /*5  P EM {color:red} */

/* pseudo class and element */
#define DBA_CSS_PSEUDO_FIRSTCHILD        PSEUDO_FIRSTCHILD           /*1*/
#define DBA_CSS_PSEUDO_LINK              PSEUDO_LINK                 /*2*/
#define DBA_CSS_PSEUDO_VISITED           PSEUDO_VISITED              /*3*/
#define DBA_CSS_PSEUDO_HOVER             PSEUDO_HOVER                /*4*/
#define DBA_CSS_PSEUDO_ACTIVE            PSEUDO_ACTIVE               /*5*/
#define DBA_CSS_PSEUDO_FOCUS             PSEUDO_FOCUS                /*6*/
#define DBA_CSS_PSEUDO_LANG              PSEUDO_LANG                 /*7*/
#define DBA_CSS_PSEUDO_FIRSTLINE         PSEUDO_FIRSTLINE            /*8*/
#define DBA_CSS_PSEUDO_FIRSTLETTER       PSEUDO_FIRSTLETTER          /*9*/
#define DBA_CSS_PSEUDO_BEFORE            PSEUDO_BEFORE               /*10*/
#define DBA_CSS_PSEUDO_AFTER             PSEUDO_AFTER                /*11*/

/* Units */
#define DBA_CSS_STYLE_UNIT_INVALID        STYLE_UNIT_INVALID        /*0 invalid unit : for parsing   */
#define DBA_CSS_STYLE_UNIT_REL            STYLE_UNIT_REL            /*1 relative : e.g. to font size */
#define DBA_CSS_STYLE_UNIT_PT             STYLE_UNIT_PT             /*2 typo points : 1/72 inches    */
#define DBA_CSS_STYLE_UNIT_PC             STYLE_UNIT_PC             /*3 typo points : 1/6 inches     */
#define DBA_CSS_STYLE_UNIT_IN             STYLE_UNIT_IN             /*4 inches                       */
#define DBA_CSS_STYLE_UNIT_CM             STYLE_UNIT_CM             /*5 centimeters                  */
#define DBA_CSS_STYLE_UNIT_MM             STYLE_UNIT_MM             /*6 millimeters                  */
#define DBA_CSS_STYLE_UNIT_EM             STYLE_UNIT_EM             /*7 defined / size of M char     */
#define DBA_CSS_STYLE_UNIT_PX             STYLE_UNIT_PX             /*8 defined in pixel, bad :-(    */
#define DBA_CSS_STYLE_UNIT_PERCENT        STYLE_UNIT_PERCENT        /*9 a relative size in percent   */
#define DBA_CSS_STYLE_UNIT_XHEIGHT        STYLE_UNIT_XHEIGHT        /*10 defined / size of x char     */

#endif  /*DB_USING_CSS*/
#endif /*_DBA_CSSPRPTMAP_H_*/
