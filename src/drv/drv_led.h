/*
 * drv_led.h
 *
 *  Created on: Jan 19, 2014
 *      Author: aadamson
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Exported_Types
  * @{
  */
typedef enum
{
    LED0 = 0,
}
Led_TypeDef;

/** @addtogroup LED
  * @{
  */
#define LEDn                             1

#ifdef DISCOVERY
#define LED0_PIN                         GPIO_Pin_9
#define LED0_GPIO_PORT                   GPIOE
#define LED0_GPIO_CLK                    RCC_AHBPeriph_GPIOE
#else
#define LED0_PIN                         GPIO_Pin_2
#define LED0_GPIO_PORT                   GPIOA
#define LED0_GPIO_CLK                    RCC_AHBPeriph_GPIOA
#endif
/** @defgroup Exported_Functions
  * @{
  */
void ledInit(Led_TypeDef Led);
void ledON(Led_TypeDef Led);
void ledOFF(Led_TypeDef Led);
void ledToggle(Led_TypeDef Led);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif
