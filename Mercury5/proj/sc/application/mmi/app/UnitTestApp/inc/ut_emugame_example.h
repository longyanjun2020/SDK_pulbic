/* ut_emugame_example.h */
#ifndef __UT_EMUGAME_EXAMPLE_H__
#define __UT_EMUGAME_EXAMPLE_H__

#include "ut_def.h"
#include "mmi_layout.h" /* For MAIN_LCD_WIDTH, MAIN_LCD_HEIGHT */

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetEmugame_Example(void);
int NumEmugame_Example(void);
void ReleaseEmugame_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif /*__UT_EMUGAME_EXAMPLE_H__ */