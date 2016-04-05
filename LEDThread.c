
#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include "Board_LED.h"                  // ::Board Support:LED
#include "Board_Accelerometer.h"        // ::Board Support:Accelerometer
#include "Board_Magnetometer.h"         // ::Board Support:Magnetometer


ACCELEROMETER_STATE g_accel;
MAGNETOMETER_STATE g_magneto;
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
void Thread (void const *argument);                             // thread function
osThreadId tid_Thread;                                          // thread id
osThreadDef (Thread, osPriorityNormal, 1, 0);                   // thread object

static const uint8_t LED_Table[] = {
  0x01, /* Green=On,  Red=Off, Blue=Off */
  0x02, /* Green=Off, Red=On,  Blue=Off */
  0x04, /* Green=Off, Red=Off, Blue=On  */
  0x03, /* Green=On,  Red=On,  Blue=Off */
  0x05, /* Green=On,  Red=Off, Blue=On  */
  0x06, /* Green=Off, Red=On,  Blue=On  */
  0x07, /* Green=On,  Red=On,  Blue=On  */
  0x00  /* Green=Off, Red=Off, Blue=Off */
};


int Init_Thread (void) {

  tid_Thread = osThreadCreate (osThread(Thread), NULL);
  if (!tid_Thread) return(-1);
  
  return(0);
}

void Thread (void const *argument) {
int32_t i;
		Accelerometer_Initialize();
Magnetometer_Initialize();
  while (1) {
    ; // Insert thread code here...
		for (i = 0; i < sizeof(LED_Table); i++) {
			LED_SetOut(LED_Table[i]);         /* Set LED Outputs                    */
      osDelay(100);        
			Accelerometer_GetState (&g_accel);
		Magnetometer_GetState (&g_magneto); 
    osThreadYield ();                                           // suspend thread
		}
  }
}
