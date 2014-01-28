/*
 * drv_gpio.h
 *
 *  Created on: Jan 20, 2014
 *      Author: aadamson
 */

#pragma once

#ifdef DEBUG_TIMING
#define TIM2D_PIN                         GPIO_Pin_3
#define TIM2D_GPIO_PORT                   GPIOA
#define TIM2D_GPIO_CLK                    RCC_AHBPeriph_GPIOA
#endif

void gpioInit(void);
