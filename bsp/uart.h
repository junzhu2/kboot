/*
 * @FileName: uart.h
 * @Author: JL KKB zj
 * @Version: V1.0.0
 * @Date: 2021-08-11 15:45:19
 * @LastEditTime: 2021-08-20 18:39:36
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \kboot\bsp\uart.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _UART_H
#define _UART_H

#define G_UART extern

/* Includes ------------------------------------------------------------------*/
#if defined (STM32F40_41xxx)
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#elif defined (STM32F10X_XL) || (STM32F10X_MD)
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#endif

/** @addtogroup KBOOT
  * @{
  */

/** @addtogroup BSP
  * @{
  */

 /** @addtogroup UART
  * @{
  */

/** @defgroup UART_Exported_Types
  * @{
  */
/** 
  * @brief  UART pin name definition  
  */
typedef enum  
{
	TX,RX
}UART_PIN_NAME_T;

/** 
  * @brief  UART dev name definition  
  */
typedef enum  
{
	UART1,UART2
}UART_NAME_T;

/** 
  * @brief  UART Init structure definition  
  */

typedef struct  
{
	UART_NAME_T	      uart_name;        /*!< uart name */
  GPIO_PIN_T      	uart_gpio[RX+1];  /*!< uart pins */
  uint32_t          uart_clock;       /*!< RCC clock */
  USART_TypeDef*    uart_x;           /*!< uart x */
  USART_InitTypeDef uart_arg;         /*!< uart config */
}UART_T;


/** 
  * @brief  UART opr structure definition  
  */
typedef struct  
{
	void (*open)(void * dev_obj);				        /*!< device init */
	int8_t (*write)(void * dev_obj,void *data);	/*!< device write */
	int8_t (*read)(void * dev_obj,void *data);	/*!< device read */
	void (*close)(void * dev_obj);				      /*!< device close */
}UART_OPR_T;

/**
  * @}
  */

/** @defgroup UART_Exported_Constants
  * @{
  */
#define UART_GROUP_NUM 1

 /**
  * @}
  */

/** @defgroup UART_Exported_Functions
  * @{
  */
G_UART void uart_init(void *dev_obj);
/**
  * @}
  */
#endif/* __UART_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2021 xRTOS-k *****END OF FILE****/

