/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                          (c) Copyright 1992-2002, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
* File : uCOS_II.C
* By   : Jean J. Labrosse
*********************************************************************************************************
*/

#define  OS_GLOBALS                           /* Declare GLOBAL variables                              */
#include "includes.h"


#define  OS_MASTER_FILE                       /* Prevent the following files from including includes.h */
// --------------------------------------------
// FUNFUN.YOO 2017.06.02.
//#include "\software\ucos-ii\source\os_core.c"
//#include "\software\ucos-ii\source\os_flag.c"
//#include "\software\ucos-ii\source\os_mbox.c"
//#include "\software\ucos-ii\source\os_mem.c"
//#include "\software\ucos-ii\source\os_mutex.c"
//#include "\software\ucos-ii\source\os_q.c"
//#include "\software\ucos-ii\source\os_sem.c"
//#include "\software\ucos-ii\source\os_task.c"
//#include "\software\ucos-ii\source\os_time.c"
// --------------------------------------------

#include "/home/funfun/DK-AVR_RTOS/CORE_SRC/os_core.c"
#include "/home/funfun/DK-AVR_RTOS/CORE_SRC/os_flag.c"
#include "/home/funfun/DK-AVR_RTOS/CORE_SRC/os_mbox.c"
#include "/home/funfun/DK-AVR_RTOS/CORE_SRC/os_mem.c"
#include "/home/funfun/DK-AVR_RTOS/CORE_SRC/os_mutex.c"
#include "/home/funfun/DK-AVR_RTOS/CORE_SRC/os_q.c"
#include "/home/funfun/DK-AVR_RTOS/CORE_SRC/os_sem.c"
#include "/home/funfun/DK-AVR_RTOS/CORE_SRC/os_task.c"
#include "/home/funfun/DK-AVR_RTOS/CORE_SRC/os_time.c"
