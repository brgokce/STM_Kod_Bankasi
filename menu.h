/*
 * menu.h
 *
 *  Created on: Nov 26, 2020
 *      Author: Dell
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_


#include "stm32f1xx_hal.h"
#include"stdio.h"
#include"string.h"
#include "LCD16x2.h"
#include "main.h"
#include "dwt_stm32_delay.h"




//Function prototypes
//Timer0 initialization
void Timer0_init(void);
//Initial menu
void menu_Init(void);
//Inits ports for buttons and LED's
void ports_Init(void);
//long delay (1s)
void delay1s(void);
//Functions for each menu item

void func000(void);
void func100(void);
void func200(void);
void func300(void);
void func110(void);
void func120(void);
void func130(void);
void func210(void);
void func220(void);
void func230(void);
void func310(void);



//Timer0 overflow interrupt service routine
void call_menu_function(uint8_t const jump_index);
void menu_callback(uint16_t GPIO_Pin);
void call_main_menu(void);
void call_sub_menu(void);
void call_sub_sub_menu(void);
void menu_Init(void);
uint8_t MFIndex(uint8_t mn, uint8_t sb);
#endif /* INC_MENU_H_ */
