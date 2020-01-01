/*
   MDCT Transform
 */
#include "ffr.h"
#include "ffr.h"
                  
void mdct(Word32 *dctdata,
          const Word32 *trigData,
          const Word32 *sineWindow,
          Word32 n,
          Word32 ld_n
          );

void Transform_Real(Word16 *mdctDelayBuffer,
                    Word16 *timeSignal,
                    Word16 chIncrement,     /*! channel increment */
                    Word32 *realOut,
                    Word16 *mdctScale,
                    Word16 windowSequence
                    );


extern void Window_Filter1(Word16 *ptr1, 
                           Word16 *ptr2,
                           Word32 *ptr3, 
                           const Word32 *win_ptr,
                           Word16 minSf,
                           Word32 len);
                                
extern void Window_Filter2(Word16 *ptr1, 
                           Word16 *ptr2,
                           Word32 *ptr3, 
                           const Word32 *win_ptr,
                           Word16 minSf,
                           Word32 len);    
                           
extern void Short_Window_Filter(Word16 *ptr1, 
                                Word16 *ptr2,
                                Word32 *ptr3, 
                                const Word32 *win_ptr,
                                Word16 minSf,
                                Word32 len);                                                            
