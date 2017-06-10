/*
********************************************************************************
* File        	: TEST.C
*
* last modified by FUNFUN.YOO 2017.06.02
********************************************************************************
*/

#include "includes.h"

/*
********************************************************************************
********************************************************************************
*/

#define DDR_LED1	DDRC
#define PORT_LED1	PORTC
#define PIN_LED1	PINC

#define DDR_LED2	DDRD
#define PORT_LED2	PORTD
#define PIN_LED2	PIND

OS_STK task_start_stk[OS_TASK_DEF_STK_SIZE];
OS_STK task_led_stk[OS_TASK_DEF_STK_SIZE];
OS_STK task_fnd_stk[OS_TASK_DEF_STK_SIZE];

void task_start(void *data);
void task_led1(void *data);
void task_led2(void *data);

int main(void)
{
	OSInit();
	
	OSTaskCreate(task_start, (void *)0, (void *)&task_start_stk[OS_TASK_DEF_STK_SIZE - 1], 0);
	
	OSStart();
	
	return 0;
}

void task_start(void *data)
{
	// Timer/Counter0 Overflow
	OS_ENTER_CRITICAL();
        TCCR0B = (0 << WGM02) | (0 << CS02) | (1 << CS01) | (1 << CS00) ;
        TCCR0A =             (0 << WGM01) | (0 << WGM00);	
	TIMSK0 = (1 << TOIE0);
	TCNT0 = 256 - (CPU_CLOCK_HZ / OS_TICKS_PER_SEC / 64);
	OS_EXIT_CRITICAL();
	
	OSTaskCreate(task_led1, (void *)0, (void *)&task_led_stk[OS_TASK_DEF_STK_SIZE - 1], 1);
	OSTaskCreate(task_led2, (void *)0, (void *)&task_fnd_stk[OS_TASK_DEF_STK_SIZE - 1], 2);
	
	for (;;)
	{
		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}

void task_led1(void *data)
{
	INT8U led1_status = (1 << PORT7);
	
	DDR_LED1 |= (1 << PORT7);
	
	for (;;)
	{
		// LED toggle 
		led1_status = ~led1_status;
		PORT_LED1 = led1_status;
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
}

void task_led2(void *data)
{
	INT8U led2_status = (1 << PORT7);
	
	DDR_LED2 |= (1 << PORT7);
	
	for (;;)
	{
		// LED toggle 
		led2_status = ~led2_status;
		PORT_LED2 = led2_status;
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
}


