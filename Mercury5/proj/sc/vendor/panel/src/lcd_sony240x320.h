//==============================================================================
//
//  File        : lcd_sony240x320.h
//  Description : SONY 240x320 LCD Panel Initiali Data File
//  Author      : Jerry Tsao
//  Revision    : 1.0
//
//==============================================================================

#ifndef _LCD_SONY240x320_H_
#define _LCD_SONY240x320_H_

void LcdSony240x320InitSeq(void)
{
    LCD_WAIT(1);
      
    // ============ CR On =============
    LCD_CMD(0x0504, 0x0707);    // CLKCNF = 0x0707
    LCD_CMD(0x0000, 0x0001);    // SYS.CRON = 1
    LCD_CMD(0x0500, 0x0001);    // SYSCTL.CRON = 1
    
    LCD_WAIT(1);
    
    // ============ PLL On =============
    LCD_CMD(0x0506, 0x000B);    // CLKDIV.PLLON = 1
    
    LCD_WAIT(1);
        
    LCD_CMD(0x0500, 0x0201);    // SYSCTL.MCLKON = 1
    LCD_CMD(0x0007, 0x0001);    // DISP1.HD1 = 0 / HD0 = 1, sleep off status

    LCD_CMD(0x0100, 0x0002);    // POW1.HSLP = 1, display on operation

    LCD_WAIT(100);
    
    LCD_CMD(0x0007, 0x0003);    // DISP1.HD1 = 1 / HD0 = 1, active status

    // Vertical mirror
	#ifdef LCD_ROTATE_180
    LCD_CMD(0x0200,    219);    // start x = 219
    LCD_CMD(0x0201,    319);    // start y = 319
    LCD_CMD(0x0003, 0x0000);    // default 0x0030h    
                                // [5:4] 00 : x-, y-
                                //       01 : x+, y-
                                //       10 : x-, y+
                                //       11 : x+, y+
                                // [  3]  0 : horizontal
                                //        1 : vertical
	#else
    LCD_CMD(0x0200,      0);    // start x = 0
    LCD_CMD(0x0201,      0);    // start y = 0
    LCD_CMD(0x0003, 0x0030);    // default 0x0030h    
	#endif
}

#endif //_LCD_SONY240x320_H_