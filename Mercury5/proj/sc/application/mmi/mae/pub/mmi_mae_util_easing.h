/**
* @file mmi_mae_util_easing.h
*
* @version $Id$
*/
#ifndef __MMI_MAE_UTIL_EASING_H__
#define __MMI_MAE_UTIL_EASING_H__
/***** LINEAR ****/
float MAE_Linear_EaseNone(float t,float b , float c, float d);
float MAE_Linear_EaseIn(float t,float b , float c, float d);
float MAE_Linear_EaseOut(float t,float b , float c, float d);
float MAE_Linear_EaseInOut(float t,float b , float c, float d);

/***** SINE ****/
float MAE_Sine_EaseIn(float t,float b , float c, float d);
float MAE_Sine_EaseOut(float t,float b , float c, float d);
float MAE_Sine_EaseInOut(float t,float b , float c, float d);

/**** Quint ****/
float MAE_Quint_EaseIn(float t,float b , float c, float d);
float MAE_Quint_EaseOut(float t,float b , float c, float d);
float MAE_Quint_EaseInOut(float t,float b , float c, float d);

/**** Quart ****/
float MAE_Quart_EaseIn(float t,float b , float c, float d);
float MAE_Quart_EaseOut(float t,float b , float c, float d);
float MAE_Quart_EaseInOut(float t,float b , float c, float d);

/**** Quad ****/
float MAE_Quad_EaseIn(float t,float b , float c, float d);
float MAE_Quad_EaseOut(float t,float b , float c, float d);
float MAE_Quad_EaseInOut(float t,float b , float c, float d);
float MAE_Quad_EaseInTrans(float t,float b,float c,float d);

/**** Expo ****/
float MAE_Expo_EaseIn(float t,float b , float c, float d);
float MAE_Expo_EaseOut(float t,float b , float c, float d);
float MAE_Expo_EaseInOut(float t,float b , float c, float d);

/****  Elastic ****/
float MAE_Elastic_EaseIn(float t,float b , float c, float d);
float MAE_Elastic_EaseOut(float t,float b , float c, float d);
float MAE_Elastic_EaseInOut(float t,float b , float c, float d);

/****  Cubic ****/
float MAE_Cubic_EaseIn(float t,float b , float c, float d);
float MAE_Cubic_EaseOut(float t,float b , float c, float d);
float MAE_Cubic_EaseInOut(float t,float b , float c, float d);

/*** Circ ***/
float MAE_Circ_EaseIn(float t,float b , float c, float d);
float MAE_Circ_EaseOut(float t,float b , float c, float d);
float MAE_Circ_EaseInOut(float t,float b , float c, float d);

/****  Bounce ****/
float MAE_Bounce_EaseIn(float t,float b , float c, float d);
float MAE_Bounce_EaseOut(float t,float b , float c, float d);
float MAE_Bounce_EaseInOut(float t,float b , float c, float d);
int MAE_Bounce_IEaseOut(int t, int b, int c, int d);

/**** Back *****/
float MAE_Back_EaseIn(float t,float b , float c, float d);
float MAE_Back_EaseOut(float t,float b , float c, float d);
float MAE_Back_EaseInOut(float t,float b , float c, float d);
int MAE_Back_IEaseIn(int t, int b, int c, int d, int fx_s);
int MAE_Back_IEaseOut(int t, int b, int c, int d, int fx_s);
int MAE_Back_IEaseInOut(int t, int b, int c, int d, int fx_s);

typedef float(*MAE_EaseFunc_t)(float t,float b , float c, float d);  

#ifdef __MAE_UTIL_EASING_C__
MAE_EaseFunc_t mae_EaseFuncTbl[] =
{
    MAE_Linear_EaseNone,
    MAE_Linear_EaseIn,
    MAE_Linear_EaseOut,
    MAE_Linear_EaseInOut,
    MAE_Sine_EaseIn,
    MAE_Sine_EaseOut,
    MAE_Sine_EaseInOut,
    MAE_Quint_EaseIn,
    MAE_Quint_EaseOut,
    MAE_Quint_EaseInOut,
    MAE_Quart_EaseIn,
    MAE_Quart_EaseOut,
    MAE_Quart_EaseInOut,
    MAE_Quad_EaseIn,
    MAE_Quad_EaseOut,
    MAE_Quad_EaseInOut,
    MAE_Expo_EaseIn,
    MAE_Expo_EaseOut,
    MAE_Expo_EaseInOut,
    MAE_Elastic_EaseIn,
    MAE_Elastic_EaseOut,
    MAE_Elastic_EaseInOut,
    MAE_Cubic_EaseIn,
    MAE_Cubic_EaseOut,
    MAE_Cubic_EaseInOut,
    MAE_Circ_EaseIn,
    MAE_Circ_EaseOut,
    MAE_Circ_EaseInOut,
    MAE_Bounce_EaseIn,
    MAE_Bounce_EaseOut,
    MAE_Bounce_EaseInOut,
    MAE_Back_EaseIn,
    MAE_Back_EaseOut,
    MAE_Back_EaseInOut
};

#else

extern MAE_EaseFunc_t mae_EaseFuncTbl[];
#endif /* __MAE_UTIL_EASING_C__ */
#endif // __MAE_UTIL_EASING_H__
