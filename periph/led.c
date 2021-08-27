/*
 * @FileName:	gpio.c
 * @Author: JL KKB zj
 * @Version: V1.0.0
 * @Date: 2021-08-11 15:45:19
 * @LastEditTime: 2021-08-27 15:45:51
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
#include "led.h"

static void open(void * dev_obj,void *handle);
static int8_t write(void * hanled,void * data);
static int8_t read(void * hanled,void * data);
static void close(void * hanled);

/**
  * led1 : pc13
  */
static LED_INFO_T G_LED_INFO_GROUP[LED_GROUP_NUM] = 
{
  {
    {
      (PIN_DEV | PIN_OUT | PIN_PP),
      {
        {PC13,0},
      },
      1,
    },
    LED1,
    LV0/*default:off*/
  }
};

/**
  * @brief  init led .
  * @param  dev_obj.
  * @retval None
  */
void led_opr_init(void *dev_obj_opr)
{
	((LED_OPR_T *)dev_obj_opr)->open = open;
	((LED_OPR_T *)dev_obj_opr)->write = write;
	((LED_OPR_T *)dev_obj_opr)->read = read;
	((LED_OPR_T *)dev_obj_opr)->close = close;
}

/**
  * @brief  init the device .
  * @param  device obj.
  * @retval device handle.
  */
static void open(void * dev_obj,void *handle)
{
	LED_HANDLE_T *lh = (LED_HANDLE_T *)handle;

  memcpy(&lh->led_info,&G_LED_INFO_GROUP[(uint32_t)dev_obj],sizeof(LED_INFO_T));
  gpio_opr_init(&lh->gh.gpio_opr);
  lh->gh.gpio_opr.open(&(lh->led_info.led_bsp),&(lh->gh.gpio_info));
	/*default:close the led*/
	write(lh,OFF);

}

/**
  * @brief  write the device .
  * @param  device obj.
  * @retval opr state
  */
static int8_t write(void * handle,void * data)
{
  LED_HANDLE_T *lh = (LED_HANDLE_T *)handle;
	int8_t result_state = 0;
	uint32_t *opr;
	
	if(!lh->led_info.led_bsp.dev_pins[0].effe_level)
	{
		opr = (uint32_t *)(!(uint32_t)((uint32_t *)(data)));
	}
	else 
	{
		opr = (uint32_t *)(data);
	}
	result_state = lh->gh.gpio_opr.write(&(lh->gh),opr);

	return result_state;
}

/**
  * @brief  read the device .
  * @param  device obj.
  * @retval opr state
  */
static int8_t read(void * handle,void * data)
{
  LED_HANDLE_T *lh = (LED_HANDLE_T *)handle;
	int8_t result_state = 0;

	result_state = lh->gh.gpio_opr.read(&lh->gh,data);
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

