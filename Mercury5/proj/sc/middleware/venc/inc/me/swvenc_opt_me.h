
#ifndef OPT_ME_H
#define OPT_ME_H  

//2009/10/19
// If not defined, use original MVFAST diamond pattern.
#define HEXAGONAL_SEARCH
	
// Jumpout if the SAD reduction after one round does not exceed a predefined threshold
//#define EJO_ROUND   
#ifdef EJO_ROUND
    #define REDUCED_SAD_THR  64
#endif

//2009/10/27 for fit Qmem size
//#define SMALL_WINDOW_SIZE
#ifdef SMALL_WINDOW_SIZE
	#define SR_MAX_X	15	
	#define SR_MIN_X	-15	
	#define SR_MAX_Y	10
	#define SR_MIN_Y	-11
#else
	#define SR_MAX_X	15	
	#define SR_MIN_X	-15	
	#define SR_MAX_Y	15
	#define SR_MIN_Y	-15
#endif

#endif  // OPT_ME_H
