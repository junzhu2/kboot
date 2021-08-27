/*
 * @FileName: BSP.h
 * @Author: JL KKB zj
 * @Version: V1.0.0
 * @Date: 2021-08-11 15:45:19
 * @LastEditTime: 2021-08-20 18:39:16
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \kboot\periph\BSP.h
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
#ifndef _BSP_H
#define _BSP_H

#define G_BSP extern

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/** @addtogroup KBOOT
  * @{
  */

/** @addtogroup PERIPH
  * @{
  */

 /** @addtogroup BSP
  * @{
  */

/** @defgroup BSP_Exported_Types
  * @{
  */
 
/** 
  * @brief  LED name  
  */
#define BSP_PIN_NUM_MAX 1


/** 
  * @brief  BSP type  
  * 00000000
  * 0-3bit  description properties

    0,1bit:out-driver
                1bit: od 
                      0:dis 1:en
                1bit: pp 
                      0:dis 1:en
    2,3bit:
                3bit: up 
                      0:dis 1:en
                4bit: down 
                      0:dis 1:en

    4-7bit:device type
            0000:PIN_DEV
                      PIN_OD    0001  0x01
                      PIN_PP    0010  0x02
                      PIN_UP    0100  0x04
                      PIN_DOWN  1000  0x08
            0001:UART_DEV
            0002:IIC_DEV
            0003:SPI_DEV
  */
typedef enum  
{
	PIN_DEV = 0x00, 
          PIN_OUT = 0x00,PIN_OD = 0x01,PIN_PP = 0x02,PIN_INPUT = 0x03,
          PIN_UP = 0x04, PIN_DOWN = 0x08,
  UART_DEV = 0x10,
  IIC_DEV = 0x20,
  SPI_DEV = 0x30,
}BSP_TYPE_T;


/** 
  * @brief  LED Init structure definition  
  */
typedef struct  
{
	BSP_TYPE_T	dev_type;			              /*!< device type */
	GPIO_PIN_T  dev_pins[BSP_PIN_NUM_MAX];  /*!< device pin */
  uint8_t     dev_pin_num;                /*!< device pin num */
  // uint8_t     _RESERVE_[3];
}BSP_BASE_T;

 /**
  * @}
  */

/** @defgroup BSP_Exported_Functions
  * @{
  */


/**
  * @}
  */
#endif/* __BSP_H */
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



