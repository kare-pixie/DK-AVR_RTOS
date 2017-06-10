/*
********************************************************************************
* File        	: APP2.C
* By          	: FunFun Yoo (funfun.yoo@gmail.com)
*
* Description 	: Example for Task Test
********************************************************************************
*/

#include "includes.h"

/** ----- AVR init -----**/

//#define CPU_CLOCK_HZ		16000000    // "os_cfg.h" defined   

#define CPU_CLOCK       16000000

#define BAUD_RATE       19200
#define BAUD_RATE_L     (CPU_CLOCK / (16l * BAUD_RATE)) - 1
#define BAUD_RATE_H     ((CPU_CLOCK / (16l * BAUD_RATE)) - 1) >> 8

#define BS              0x08    // ASCII : Back Space
#define CR              0x0D    // ASCII : Carriage Return (Enter key)

#define UART_RX_BUFLEN  128

void uart_send_byte(unsigned char byte)
{
    while (!(UCSR1A & (1 << UDRE1)));
    UDR1 = byte;
}

void uart_send_string(unsigned char *str, unsigned char len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        if (!(*(str + i)))
	    break;
	
	uart_send_byte(*(str + i));
    }
}

void uart_init()
{
    // Baud rate : 19200
    UBRR1L = (unsigned char)BAUD_RATE_L;
    UBRR1H = (unsigned char)BAUD_RATE_H;
    // 8-N-1 : Data 8-bit, No parity, 1 Stop bit
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10) | (0 << UPM11) | (0 << UPM10) | (0 << USBS1);
    UCSR1B = (0 << UCSZ12) | (1 << TXEN1) | (1 << RXEN1);
}



/** ----- uC/OS-II init ----- **/

/* default stack size : 128 bytes */
#define TASK_STK_SIZE  OS_TASK_DEF_STK_SIZE	
#define N_TASKS		2	/* number of tasks */

typedef	void (*task_func)(void *); 

OS_STK task_stack[N_TASKS][TASK_STK_SIZE];	/* task stack  */
OS_STK task_start_stk[TASK_STK_SIZE];		/* the 1st task stack */
char task_data[N_TASKS];

/* task function */
void task1(void *data);
void task2(void *data);

task_func task_list[N_TASKS] = {task1, task2};


void task1(void *data)
{   
    while(1) 
    {	
	uart_send_string("task1\r\n", 7);
        OSTimeDly(400);		
    }
}
         
void task2(void *data)
{   

    while(1) 
    {
	uart_send_string("task2\r\n", 7);
        OSTimeDly(200);		
    }
}   


/* the 1st task */
void task_start(void *data)
{
    INT8U i;

    /* Time/Counter0 init */
    OS_ENTER_CRITICAL();
    TCCR0B = (0 << WGM02) | (0 << CS02) | (1 << CS01) | (1 << CS00) ;
    TCCR0A =             (0 << WGM01) | (0 << WGM00);
    TIMSK0 = (1 << TOIE0);    // Overflow Interrupt
    TCNT0 = 256 - (CPU_CLOCK_HZ / OS_TICKS_PER_SEC / 64);    // 1msec
    OS_EXIT_CRITICAL();
           
    /* creating tasks of N_TASKS */	  	
    for(i = 0; i < N_TASKS; i++) 
    {    
        task_data[i] = '0' + i;
        OSTaskCreate((void (*)(void *)) task_list[i], 
                              (void *)&task_data[i], 
                              (void *)&task_stack[i][TASK_STK_SIZE - 1], 
                              (INT8U)(i+1));               
    }	
    	
    while(1) 
    { 
	uart_send_string("task start\r\n", 12);
        //OSTimeDlyHMSM(0, 0, 1, 0);
        OSTimeDly(1000);		
    }
}



int main(void)
{
    /** ----- AVR init ----- **/
    uart_init(); 

    /** ----- RTOS init ----- **/
    OSInit();

    OSTaskCreate(task_start, (void *)0, (void *)&task_start_stk[TASK_STK_SIZE - 1], 0);

    OSStart();

    return 0;
}

