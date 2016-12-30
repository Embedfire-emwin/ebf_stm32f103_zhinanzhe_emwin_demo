/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                     ST Microelectronics STM32
*                                              on the
*
*                                     Micrium uC-Eval-STM32F107
*                                         Evaluation Board
*
* Filename      : includes.h
* Version       : V1.00
* Programmer(s) : EHS
*                 DC
*********************************************************************************************************
*/

#ifndef  INCLUDES_PRESENT
#define  INCLUDES_PRESENT


/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/

#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>


/*
*********************************************************************************************************
*                                              LIBRARIES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_def.h>
#include  <lib_ascii.h>
#include  <lib_math.h>
#include  <lib_mem.h>
#include  <lib_str.h>


/*
*********************************************************************************************************
*                                              APP / BSP
*********************************************************************************************************
*/
#include  "..\User\bsp\bsp.h"
#include  "..\User\bsp\led\bsp_led.h"  
#include  "..\User\bsp\usart\bsp_usart1.h"
#include  "..\User\bsp\lcd\bsp_ili9341_lcd.h"
#include  "..\User\bsp\lcd\bsp_xpt2046_lcd.h"
#include  "ff.h"
#include  "app_cfg.h"
#include  "app.h"
/*
*********************************************************************************************************
*                                                 OS
*********************************************************************************************************
*/

#include  <os.h>	
#include "os_type.h"
#include "os_cfg_app.h"
/*
*********************************************************************************************************
*                                                 ST
*********************************************************************************************************
*/

#include  <stm32f10x.h>

/*
*********************************************************************************************************
*                                                 emWin
*********************************************************************************************************
*/
#include "GUI.H"
#include "DIALOG.h"


/*
*********************************************************************************************************
*                                            INCLUDES END
*********************************************************************************************************
*/


#endif

