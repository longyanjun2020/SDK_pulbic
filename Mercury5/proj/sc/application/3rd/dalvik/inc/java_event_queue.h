#ifndef __JAVA_EVENT_QUEUE_H__
#define __JAVA_EVENT_QUEUE_H__ 

#include "ven_os.h"
#include "ven_dbg.h"


 
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
  
typedef struct SimpleElem {
    void (*fp)(int, int, void *);
    int arg0;
    int arg1;
    void *argp;
} SimpleElem, MsgElem, JElem;

typedef struct {
    unsigned int capacity;
    unsigned int size;
    unsigned int head;
    unsigned int tail;
    SimpleElem queue[0];
} SimpleQueue, MsgQueue, JQueue;

SimpleQueue *SimpleQueue_create(unsigned int capacity, void *(*malloc_f)(unsigned int));
void SimpleQueue_release(SimpleQueue *q, void (*free_f)(void *));
void SimpleQueue_enqueue(SimpleQueue *q, SimpleElem e);
SimpleElem SimpleQueue_dequeue(SimpleQueue *q);

void MsgQueue_create(unsigned int capacity);
void MsgQueue_release();
int MsgQueue_enqueue(void (*f)(int, int, void *), int a, int b, void *p);
int MsgQueue_dequeue();
void MsgQueue_reset();
  
void JEvent_create(unsigned int capacity);
void JEvent_destroy();
int JEvent_post(void (*f)(int, int, void *), int a, int b, void *p);
int JEvent_wait();
#endif
