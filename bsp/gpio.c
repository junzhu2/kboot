/*
 * @FileName:	gpio.c
 * @Author: JL KKB zj
 * @Version: V1.0.0
 * @Date: 2021-08-11 15:45:19
 * @LastEditTime: 2021-08-27 16:16:01
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \kboot\bsp\gpio.c
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
#include "bsp.h"
#include "gpio.h"


static void open(void * dev_obj,void *handle);
static int8_t write(void * handle,void * data);
static int8_t read(void * handle,void * data);
static void close(void * handle);

/**
  * @brief  init gpio .
  * @param  dev_obj.
  * @retval None
  */
void gpio_opr_init(void *dev_obj_opr)
{
	((GPIO_OPR_T *)dev_obj_opr)->open = open;
	((GPIO_OPR_T *)dev_obj_opr)->write = write;
	((GPIO_OPR_T *)dev_obj_opr)->read = read;
	((GPIO_OPR_T *)dev_obj_opr)->close = close;
}

/**
  * @brief  init the device .
  * @param  device obj.
  * @retval None
  */
static void open(void * dev_obj,void *handle)
{
	/*
		BSP_BASE_T --> GPIO_T 
	*/
	BSP_BASE_T *bsp_base = (BSP_BASE_T *)dev_obj;
	GPIO_INFO_T *gpio_info = (GPIO_INFO_T *)handle;
	uint8_t pin_flag = 0;

	for(pin_flag = 0;pin_flag < bsp_base->dev_pin_num;pin_flag++)
	{
		gpio_info->gpio_clock = GPIO_RCC_CLOCK(bsp_base->dev_pins[pin_flag].pin/GPIO_GROUP_NUM);
		gpio_info->gpiox = GPIO_GROUP(bsp_base->dev_pins[pin_flag].pin/GPIO_GROUP_NUM);
		
		gpio_info->gpio_arg.GPIO_Pin = GPIO_PIN(bsp_base->dev_pins[pin_flag].pin%GPIO_GROUP_NUM);
		gpio_info->gpio_arg.GPIO_Speed = GPIO_Speed_MAX;

		switch(bsp_base->dev_type&0x03)
		{
			case PIN_OUT:
#if defined (STM32F40_41xxx)
				gpio_info->gpio_arg.GPIO_Mode = GPIO_Mode_OUT;
#endif	
			break;
			case PIN_OD:
#if defined (STM32F40_41xxx)
				gpio_info->gpio_arg.GPIO_Mode = GPIO_Mode_OUT;
				gpio_info->gpio_arg.GPIO_OType = GPIO_OType_OD;
#elif defined (STM32F10X_XL) || (STM32F10X_MD)
				gpio_info->gpio_arg.GPIO_Mode = GPIO_Mode_Out_OD;
#endif	
			break;
			case PIN_PP:
#if defined (STM32F40_41xxx)
				gpio_info->gpio_arg.GPIO_Mode = GPIO_Mode_OUT;
				gpio_info->gpio_arg.GPIO_OType = GPIO_OType_PP;
#elif defined (STM32F10X_XL) || (STM32F10X_MD)
				gpio_info->gpio_arg.GPIO_Mode = GPIO_Mode_Out_PP;
#endif	
			break;
			case PIN_INPUT:
#if defined (STM32F40_41xxx)
				gpio_info->gpio_arg.GPIO_Mode = GPIO_Mode_IN;
#endif	
			break;
		}

		switch(bsp_base->dev_type&0xC0)
		{
			case PIN_UP:
#if defined (STM32F40_41xxx)
				gpio_info->gpio_arg.GPIO_PuPd = GPIO_PuPd_UP;
#elif defined (STM32F10X_XL) || (STM32F10X_MD)
				gpio_info->gpio_arg.GPIO_Mode = GPIO_Mode_IPU;
#endif	
			break;
			case PIN_DOWN:
#if defined (STM32F40_41xxx)
				gpio_info->gpio_arg.GPIO_PuPd = GPIO_PuPd_DOWN;
#elif defined (STM32F10X_XL) || (STM32F10X_MD)
				gpio_info->gpio_arg.GPIO_Mode = GPIO_Mode_IPD;
#endif	
			break;
		}

		/* open the clock */
		GPIO_RCC_PeriphClockEnable(gpio_info->gpio_clock);
		/* init gpio*/
		GPIO_Init(gpio_info->gpiox,&gpio_info->gpio_arg);
	}
}

/**
  * @brief  write the device .
  * @param  device obj.
  * @retval opr state
  */
static int8_t write(void * handle,void * data)
{
	GPIO_INFO_T *gpio_obj = &(((GPIO_HANDLE_T *)handle)->gpio_info);
	BitAction gpio_opr =  (BitAction)((uint32_t)(data));
	int8_t result_state = 0;

	if(GPIO_MODE_IS(gpio_obj->gpio_arg.GPIO_Mode) == GPIO_OUT)
	{
		GPIO_WriteBit(gpio_obj->gpiox,gpio_obj->gpio_arg.GPIO_Pin,gpio_opr);
		result_state = 0;
	}
	else
	{
		result_state = -1;
	}

	return result_state;
}

/**
  * @brief  read the device .
  * @param  device obj.
  * @retval opr state
  */
static int8_t read(void * handle,void * data)
{
	GPIO_INFO_T *gpio_obj = &(((GPIO_HANDLE_T *)handle)->gpio_info);
	int8_t result_state = 0;

	if(GPIO_MODE_IS(gpio_obj->gpio_arg.GPIO_Mode) == GPIO_IN )
	{
		result_state =  GPIO_ReadInputDataBit(gpio_obj->gpiox,gpio_obj->gpio_arg.GPIO_Pin);
		*(uint8_t *)data = result_state;
	}
	else if(GPIO_MODE_IS(gpio_obj->gpio_arg.GPIO_Mode) == GPIO_OUT )
	{
		result_state =  GPIO_ReadOutputDataBit(gpio_obj->gpiox,gpio_obj->gpio_arg.GPIO_Pin);
		*(uint8_t *)data = result_state;
	}
	else
	{
		result_state = -1;
	}

	return result_state;
}

/**
  * @brief  close the device .
  * @param  device obj.
  * @retval None
  */
static void close(void * handle)
{

}
