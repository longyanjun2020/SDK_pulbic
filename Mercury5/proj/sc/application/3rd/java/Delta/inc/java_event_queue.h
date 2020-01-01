#ifndef __JAVA_EVENT_QUEUE_H__
#define __JAVA_EVENT_QUEUE_H__ 

#include "ven_os.h"
#include "ven_dbg.h"
#include "java_head.h"
#include "nemomp.h"
 
 typedef struct listnode
  {
  	int KeyCode;
    int KeyState;
  	struct listnode *nextptr; 	
  } java_key_LISTNODE;
    
    
  typedef struct queue
  {
  	java_key_LISTNODE *frontptr;
  	java_key_LISTNODE *rearptr;
  } *java_key_QUEUE;


  typedef struct touch_listnode
  {
  	int x;
    int y;
	int state;
  	struct listnode *nextptr; 	
  } java_touch_LISTNODE;
    
    
  typedef struct touch_queue
  {
  	java_touch_LISTNODE *frontptr;
  	java_touch_LISTNODE *rearptr;
  } *java_touch_QUEUE;
  
  
  java_key_QUEUE java_key_queue_create(void);
  void java_key_queue_destroy( java_key_QUEUE qptr );
  void java_key_enqueue(java_key_QUEUE q,int KeyCode,int KeyState);
  void java_key_dequeue(java_key_QUEUE q,int* KeyCode, int* KeyState); 
  #define java_key_queue_empty(qptr) ((qptr)->frontptr == NULL )   


  java_touch_QUEUE java_touch_queue_create(void);
  void java_touch_queue_destroy( java_touch_QUEUE qptr );
  void java_touch_enqueue(java_touch_QUEUE q,int x,  int y, int state);
  void java_touch_dequeue(java_touch_QUEUE q,int* x, int* y, int* state);
  
  
#endif
