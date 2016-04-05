/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher for FRDM-K64F
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2004-2015 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions


#include "cmsis_os.h"
#include "board.h"
#include "Board_LED.h"
#include "Board_Buttons.h"
#include "rl_net.h"                     // Keil.MDK-Pro::Network:CORE
//#include "fsl_debug_console.h"          // Keil::Device:KSDK Utility:Debug Console


bool LEDrun;
bool MSGupdate;
char msg_text[64];

static void BlinkLed (void const *arg);
static void Message  (void const *arg);

osThreadDef(BlinkLed, osPriorityNormal, 1, 0);
osThreadDef(Message,  osPriorityNormal, 1, 0);


extern void Init_Thread(void);
extern void hardware_init (void);


void Delay(uint32_t dlyTicks)
{
    volatile uint32_t i = 0,j;
		for(j=0;j<dlyTicks;j++){
			//for (i = 0; i < 800000; ++i)
			for (i = 0; i < 80; ++i)
			{
					__asm("NOP"); /* delay */
			}
		}
}
void LCD_PInit(void)
{
	  PORTC->PCR[0]  = (1UL <<  8);                    
	PORTC->PCR[1]  = (1UL << 8);                    
	PORTC->PCR[2]  = (1UL <<  8);                    
	PORTC->PCR[3]  = (1UL <<  8);    

	PTC->PDDR =0x000f;
  
	
	PORTA->PCR[1]  = (1UL <<  8);       // R/W             
	PORTA->PCR[2]  = (1UL <<  8);      //  RS
	PORTB->PCR[9]  = (1UL <<  8);      //  Enable              

	PTB->PDDR |= (1UL <<  9);
	PTA->PDDR =0x0006;
	 
	
}


void lcdcmd(unsigned char cmdout)
{
			unsigned char i;
			i = cmdout>>4;
			PTB->PCOR = (1UL <<  9);		//  Enable low         
			PTC->PDOR = i;
		  PTA->PCOR = (1UL <<  2);   	//LCD_RS = 0 ;	//PORTA&=~(1<<rs);
		  PTA->PCOR = (1UL <<  1); //LCD_RW = 0 ;	//PORTA&=~(1<<rw);
			//Delay(100);
			PTB->PSOR = (1UL <<  9);		//  Enable high         
			Delay(1);  
			PTB->PCOR = (1UL <<  9);		//  Enable low         
			Delay(1);
			
			PTB->PCOR = (1UL <<  9);		//  Enable low         
			PTC->PDOR = cmdout;
		  PTA->PCOR = (1UL <<  2);   	//LCD_RS = 0 ;	//PORTA&=~(1<<rs);
		  PTA->PCOR = (1UL <<  1); //LCD_RW = 0 ;	//PORTA&=~(1<<rw);
			//Delay(200);
			PTB->PSOR = (1UL <<  9);		//  Enable high         
			Delay(1);  
			PTB->PCOR = (1UL <<  9);		//  Enable low         
			Delay(1);
		//LCD_STROBE ;
}


void lcdcmd1(unsigned char cmdout)
{
			unsigned char i;
		 
			PTB->PCOR = (1UL <<  9);		//  Enable low         
			PTC->PDOR = cmdout;
		  PTA->PCOR = (1UL <<  2);   	//LCD_RS = 0 ;	//PORTA&=~(1<<rs);
		  PTA->PCOR = (1UL <<  1); //LCD_RW = 0 ;	//PORTA&=~(1<<rw);
			//Delay(200);
			PTB->PSOR = (1UL <<  9);		//  Enable high         
			Delay(1);  
			PTB->PCOR = (1UL <<  9);		//  Enable low         
			Delay(1);
		//LCD_STROBE ;
}
void lcddata(unsigned char dataout)
{
			unsigned char i;
			i = dataout>>4;
	
			PTB->PCOR = (1UL <<  9);		//  Enable low         
			PTC->PDOR = i;
		  PTA->PSOR = (1UL <<  2);   	//LCD_RS = 1 ;	//PORTA&=~(1<<rs);
		  PTA->PCOR = (1UL <<  1); //LCD_RW = 0 ;	//PORTA&=~(1<<rw);
			//Delay(200);
			PTB->PSOR = (1UL <<  9);		//  Enable high         
			Delay(1);  
			PTB->PCOR = (1UL <<  9);		//  Enable low         
			Delay(1);
			PTB->PCOR = (1UL <<  9);		//  Enable low         
			PTC->PDOR = dataout;
		  PTA->PSOR = (1UL <<  2);   	//LCD_RS = 1 ;	//PORTA&=~(1<<rs);
		  PTA->PCOR = (1UL <<  1); //LCD_RW = 0 ;	//PORTA&=~(1<<rw);
			//Delay(200);
			PTB->PSOR = (1UL <<  9);		//  Enable high         
			Delay(1);  
			PTB->PCOR = (1UL <<  9);		//  Enable low         
			Delay(1);
		//LCD_STROBE ;
}


void LCD_Init(void)
{
			PTB->PCOR  = (1UL <<  2); 	// RS low
			PTB->PCOR = (1UL <<  9);		//  Enable low     
			Delay(50000); 
			Delay(2000); 
			//Delay(5000); 
			//Delay(5000);   
			//lcdcmd(0x28);
			//Delay(500);   
			lcdcmd1(0x02);//lcdcmd(0x28);
			Delay(500);   
			lcdcmd1(0x02);//lcdcmd(0x28);
			Delay(500);   
			lcdcmd1(0x08);
			Delay(500); 
			
		
			lcdcmd1(0x00);
			Delay(500); 
	    lcdcmd1(0x0e);
			Delay(500); 
			lcdcmd1(0x00);
			Delay(500);   
			lcdcmd1(0x01);
			Delay(1000); 
	
			lcdcmd1(0x00);
			Delay(500);  
			lcdcmd1(0x06);
			Delay(500);  
	
			lcdcmd1(0x08);
			Delay(500); 
			lcdcmd1(0x00);
			Delay(500);   
}

void dhcp_client_notify(uint32_t if_num, dhcpClientOption opt, const uint8_t *val, uint32_t len) {
		
  if (opt == dhcpClientIPaddress) {
    // IP address has changed
    sprintf (msg_text,"IP address: %s\n", ip4_ntoa (val));
    MSGupdate = true;
  }
}

/*----------------------------------------------------------------------------
  Thread 'Message': printf message handler
 *---------------------------------------------------------------------------*/

static void Message (void const *arg) {

  printf ("       MDK-MW       \n");
  printf (" HTTP Server example\n\n");

  printf ("Waiting for DHCP ...\n");
  fflush (stdout);
  MSGupdate = false;

  while(1) {
    if (MSGupdate == true) {
      printf ("%s\n", msg_text);
      MSGupdate = false;
    }
    osDelay (250);
  }
}

/*----------------------------------------------------------------------------
  Thread 'BlinkLed': Blink the LEDs on an eval board
 *---------------------------------------------------------------------------*/
static void BlinkLed (void const *arg) {
  const uint8_t led_val[] = { 1, 2, 3 };
  int cnt = 0;

  LEDrun = true;
  while(1) {
    // Every 100 ms
    if (LEDrun == true) {
      LED_SetOut (led_val[cnt]);
      if (++cnt >= sizeof(led_val)) {
        cnt = 0;
      }
    }
    osDelay (100);
  }
}

/*----------------------------------------------------------------------------
  Main function
 *----------------------------------------------------------------------------*/
unsigned char dummy_i;
int main (void) {
  int32_t i;
	osKernelInitialize(); // initialize CMSIS-RTOS
  hardware_init();                      /* Initialize hardware                */

  LED_Initialize();                     /* LED Initialization                 */
  Buttons_Initialize();                 /* Buttons Initialization             */
	LCD_PInit();
	LCD_Init();
	Init_Thread();
	net_initialize();
	dbg_uart_init();
  osThreadCreate (osThread(BlinkLed), NULL);
  osThreadCreate (osThread(Message),  NULL);
	osKernelStart(); // start thread execution 
	dummy_i=0x30;
  while (1) {                           /* Loop forever                       */
			net_main();
			osThreadYield();
                  /* Wait 1s                            */
      while (Buttons_GetState() & 1);   /* Wait while holding INT1 button     */
			osDelay(100);  
			lcddata(dummy_i++);
			if(dummy_i > 0x43)dummy_i=0x30;
			// debug_printf("%d \n",dummy_i);
    
  }
}
