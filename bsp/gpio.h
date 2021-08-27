/*
 * @FileName: gpio.h
 * @Author: JL KKB zj
 * @Version: V1.0.0
 * @Date: 2021-08-11 15:45:19
 * @LastEditTime: 2021-08-27 16:20:30
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \kboot\bsp\gpio.h
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
#ifndef _GPIO_H
#define _GPIO_H

#define G_GPIO extern

/* Includes ------------------------------------------------------------------*/
#if defined (STM32F40_41xxx)
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#elif defined (STM32F10X_XL) || (STM32F10X_MD)
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#endif

/** @addtogroup KBOOT
  * @{
  */

/** @addtogroup BSP
  * @{
  */

 /** @addtogroup GPIO
  * @{
  */

/** @defgroup GPIO_Exported_Types
  * @{
  */
/** 
  * @brief  GPIO Init structure definition  
  */
typedef enum  
{
  PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
  PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
  PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
  PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
  PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,
  PF0,PF1,PF2,PF3,PF4,PF5,PF6,PF7,PF8,PF9,PF10,PF11,PF12,PF13,PF14,PF15,
  PG0,PG1,PG2,PG3,PG4,PG5,PG6,PG7,PG8,PG9,PG10,PG11,PG12,PG13,PG14,PG15,
}GPIO_PIN_NAME_T;

/** 
  * @brief  GPIO dir definition  
  */
typedef enum  
{
  GPIO_IN,GPIO_OUT
}GPIO_DIR_T;

/** 
  * @brief  GPIO pin info structure definition  
  */
typedef struct  
{
  GPIO_PIN_NAME_T  pin;     /*!< led pin */
  BitAction effe_level;		  /*!< Effective level */
}GPIO_PIN_T;

/** 
  * @brief  GPIO info structure definition  
  */
typedef struct  
{
	uint32_t gpio_clock;				/*!< RCC clock */
	GPIO_TypeDef* gpiox;				/*!< GPIO group */
	GPIO_InitTypeDef  gpio_arg;	/*!< GPIO config */
}GPIO_INFO_T;

/** 
  * @brief  GPIO opr structure definition  
  */
typedef struct  
{
	void (*open)(void * dev_obj,void *handle);				      /*!< device init */
	int8_t (*write)(void * handle,void *data);	/*!< device write */
	int8_t (*read)(void * handle,void *data);	/*!< device read */
	void (*close)(void * handle);				      /*!< device close */
}GPIO_OPR_T;

/** 
  * @brief  GPIO handle structure definition  
  */
typedef struct  
{
	GPIO_INFO_T gpio_info;    /*!< gpio info */
  GPIO_OPR_T  gpio_opr;     /*!< gpio opr */
}GPIO_HANDLE_T;

/**
  * @}
  */

/** @defgroup GPIO_Exported_Constants
  * @{
  */
#define GPIO_GROUP_NUM 16
#define GPIO_GROUP(x)  (GPIO_TypeDef*)(APB2PERIPH_BASE + (0x0800+0x400*(x)))
#define GPIO_PIN(x) GPIO_Pin_0<<(x)
#if defined (STM32F40_41xxx)
#define GPIO_RCC_CLOCK(x) RCC_AHB1Periph_GPIOA<<(x)
#define GPIO_RCC_PeriphClockEnable(gpio_clock) RCC_AHB1PeriphClockCmd(gpio_clock,ENABLE)
#define GPIO_MODE_IS(mode) ((mode) == GPIO_Mode_OUT)?GPIO_OUT:(((mode) == GPIO_Mode_IN)?GPIO_IN:-1)
#define GPIO_Speed_MAX GPIO_Speed_100MHz
#elif defined (STM32F10X_XL) || (STM32F10X_MD)
#define GPIO_RCC_CLOCK(x) RCC_APB2Periph_GPIOA<<(x)
#define GPIO_RCC_PeriphClockEnable(gpio_clock) RCC_APB2PeriphClockCmd(gpio_clock,ENABLE)
#define GPIO_MODE_IS(mode) ((mode) == GPIO_Mode_Out_OD ||  (mode) == GPIO_Mode_Out_PP)?GPIO_OUT:\
(((mode) == GPIO_Mode_IPU ||  (mode) == GPIO_Mode_IPD)?GPIO_IN:-1) 
#define GPIO_Speed_MAX GPIO_Speed_50MHz
#endif

 /**
  * @}
  */

/** @defgroup GPIO_Exported_Functions
  * @{
  */
G_GPIO void gpio_opr_init(void *dev_obj_opr);
/**
  * @}
  */
#endif/* __GPIO_H */
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

