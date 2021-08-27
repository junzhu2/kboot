/*
 * @FileName: led.h
 * @Author: JL KKB zj
 * @Version: V1.0.0
 * @Date: 2021-08-11 15:45:19
 * @LastEditTime: 2021-08-27 16:17:36
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \kboot\periph\led.h
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
#ifndef _LED_H
#define _LED_H

#define G_LED extern

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"
#include "string.h"

/** @addtogroup KBOOT
  * @{
  */

/** @addtogroup PERIPH
  * @{
  */

 /** @addtogroup LED
  * @{
  */

/** @defgroup LED_Exported_Types
  * @{
  */
/** 
  * @brief  LED name  
  */
typedef uint32_t * LED_NAME_T;
typedef uint32_t * LED_ACTION_T;

/** 
  * @brief  LED state level  
  */
typedef enum  
{
	LV0,LV1,LV2,LV3,LV4
}LED_STATE_T;

/** 
  * @brief  LED Init structure definition  
  */
typedef struct  
{
  BSP_BASE_T  	  led_bsp;			/*!< led bsp */
	LED_NAME_T	    led_name;			/*!< led name */
	LED_STATE_T     led_state;	  /*!< led current state */
}LED_INFO_T;


/** 
  * @brief  LED opr structure definition  
  */
typedef struct  
{
	void  (*open)(void * dev_obj,void *handle); /*!< device open */
	int8_t (*write)(void * hanled,void *data);	/*!< device write */
	int8_t (*read)(void * hanled,void *data);	/*!< device read */
	void (*close)(void * hanled);				      /*!< device close */
}LED_OPR_T;

/** 
  * @brief  LED handle structure definition  
  */
typedef struct  
{
  LED_INFO_T    led_info; /*!< LED info */
	GPIO_HANDLE_T gh;       /*!< LED PIN handle */
  LED_OPR_T     led_opr;  /*!< LED opr */
}LED_HANDLE_T;

/**
  * @}
  */

/** @defgroup LED_Exported_Constants
  * @{
  */
#define LED_GROUP_NUM 1

/** 
  * @brief  LED name  
  */
#define LED1 (uint32_t *)0


/** 
  * @brief  LED  opr 
  */

#define OFF (uint32_t *)0
#define ON	OFF+1
 /**
  * @}
  */

/** @defgroup LED_Exported_Functions
  * @{
  */
G_LED void led_opr_init(void *dev_obj);
/**
  * @}
  */
#endif/* __LED_H */
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



