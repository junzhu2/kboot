/*
 * @FileName:	main.c
 * @Author: JL KKB zj
 * @Version: V1.0.0
 * @Date: 2021-08-11 15:45:19
 * @LastEditTime: 2021-08-27 16:46:04
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \kboot\user\main.c
 * ******************************************************************************
  * @attention
  *
  * This is an embedded real-time operating system. The system is designed, 
  * developed and maintained by JL's team. You are welcome to criticize and 
  * make corrections and work together for the growth of this open source system. 
  * We encourage and support you to apply this system to various embedded platforms 
  * and application scenarios. I hope it can be the same as the growth of the second 
  * FreeRTOS.
  *
  * <h2><center>&copy; COPYRIGHT 2021 xRTOS-k</center></h2>
  ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "led.h"
#include "uart.h"


int main(void)
{
	LED_HANDLE_T kled;

	led_opr_init(&kled.led_opr);

	kled.led_opr.open(LED1,&kled);
    
	while(1)
	{
		kled.led_opr.write(&kled,ON);
        
	}

}
