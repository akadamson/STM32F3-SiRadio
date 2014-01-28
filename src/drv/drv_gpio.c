/*
 * drv_gpio.c
 *
 *  Created on: Jan 20, 2014
 *      Author: aadamson
 */

#include "board.h"

void gpioInit(void)
{
#ifdef DEBUG_TIMING
    GPIO_InitTypeDef GPIO_InitStructure;

    /* TIM3_CH2_CLK Clocks enable */
    RCC_AHBPeriphClockCmd(TIM2D_GPIO_CLK, ENABLE);

    /* TIM3_CH2_PORT Configuration: Channel 1, 2, 3 and 4 as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin     = TIM2D_PIN;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;

    GPIO_Init(TIM2D_GPIO_PORT, &GPIO_InitStructure);
#endif
}
