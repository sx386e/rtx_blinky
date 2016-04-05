
#include "cmsis_os.h"                                           // CMSIS RTOS header file

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
void Thread1 (void const *argument);                             // thread function
osThreadId tid_Thread1;                                          // thread id
osThreadDef (Thread1, osPriorityNormal, 1, 0);                   // thread object

int Init_Thread1 (void) {

  tid_Thread1 = osThreadCreate (osThread(Thread1), NULL);
  if (!tid_Thread1) return(-1);
  
  return(0);
}

void Thread1 (void const *argument) {

  while (1) {
    ; // Insert thread code here...
    osThreadYield ();                                           // suspend thread
  }
}
