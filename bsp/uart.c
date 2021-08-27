/*
 * @FileName:	uart.c
 * @Author: JL KKB zj
 * @Version: V1.0.0
 * @Date: 2021-08-11 15:45:19
 * @LastEditTime: 2021-08-20 18:02:38
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \kboot\bsp\uart.c
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
#include "uart.h"

static void open(void * dev_obj);
static int8_t write(void * dev_obj,void * data);
static int8_t read(void * dev_obj,void * data);
static void close(void * dev_obj);

/**
  * uart1 : tx pa9    rx pa10
  */

static UART_T G_UART_GROUP[UART_GROUP_NUM] = 
{
	UART1,
	{
		{//tx pa9
			PA9,
			0
		},
		{//rx pa10
			PA10,
			0
		},
		
	},
	RCC_APB2Periph_USART1,
	USART1,
	{
		9600,
		USART_WordLength_8b,
		USART_StopBits_1,
		USART_Parity_No,
		USART_Mode_Tx | USART_Mode_Rx,
		USART_HardwareFlowControl_None,
	}
};

/**
  * @brief  init uart .
  * @param  dev_obj.
  * @retval None
  */
void uart_init(void *dev_obj)
{
	((UART_OPR_T *)dev_obj)->open = open;
	((UART_OPR_T *)dev_obj)->write = write;
	((UART_OPR_T *)dev_obj)->read = read;
	((UART_OPR_T *)dev_obj)->close = close;
}

/**
  * @brief  init the device .
  * @param  device obj.
  * @retval None
  */
static void open(void * dev_obj)
{
	UART_PIN_NAME_T  pin_name = TX;
	GPIO_OPR_T kgpio;
	
	 /* open the clock */
	RCC_APB2PeriphClockCmd(G_UART_GROUP[(uint32_t)dev_obj].uart_clock,ENABLE);
	 /* init uart pins*/
	gpio_init(&kgpio);
	for(;pin_name <= RX;pin_name++)
	{
		kgpio.open(&(G_UART_GROUP[(uint32_t)dev_obj].uart_gpio[pin_name].pin));
	}
 	/* init uart*/
	USART_Init(G_UART_GROUP[(uint32_t)dev_obj].uart_x,&G_UART_GROUP[(uint32_t)dev_obj].uart_arg);
	USART_Cmd(G_UART_GROUP[(uint32_t)dev_obj].uart_x,ENABLE);
}

/**
  * @brief  write the device .
  * @param  device obj.
  * @retval opr state
  */
static int8_t write(void * dev_obj,void * data)
{
	int8_t result_state = 0;
	
	USART_ClearFlag(G_UART_GROUP[(uint32_t)dev_obj].uart_x,USART_FLAG_TC);
	USART_SendData(G_UART_GROUP[(uint32_t)dev_obj].uart_x,*((uint16_t *)data));
	while(!USART_GetFlagStatus(G_UART_GROUP[(uint32_t)dev_obj].uart_x,USART_FLAG_TC));
	result_state = 1;

	return result_state;
}

/**
  * @brief  read the device .
  * @param  device obj.
  * @retval opr state
  */
static int8_t read(void * dev_obj,void * data)
{
	int8_t result_state = 0;

	

	return result_state;
}

/**
  * @brief  close the device .
  * @param  device obj.
  * @retval None
  */
static void close(void * dev_obj)
{

}
