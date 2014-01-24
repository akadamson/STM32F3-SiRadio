/*
 * drv_pwm.c
 *
 *  Created on: Jan 19, 2014
 *      Author: aadamson
 */

#include "board.h"

void pwmTim3_Channel4Init(void)
{
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    //uint16_t Channel2Pulse = 0;

    /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */
    //Channel2Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);

    /* Channel 1, 2, 3 and 4 Configuration in PWM mode */
    TIM_OCInitStructure.TIM_OCMode          = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState     = TIM_OutputState_Enable;
    //TIM_OCInitStructure.TIM_OutputNState  = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_Pulse           = 0;
    TIM_OCInitStructure.TIM_OCPolarity      = TIM_OCPolarity_High;
    //TIM_OCInitStructure.TIM_OCNPolarity   = TIM_OCNPolarity_High;
    //TIM_OCInitStructure.TIM_OCIdleState   = TIM_OCIdleState_Set;
    //TIM_OCInitStructure.TIM_OCNIdleState  = TIM_OCIdleState_Reset;

    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM3, ENABLE);
}

void setPWM_dutycycle(uint16_t channel, uint16_t dutycycle)
{
    if (channel == 1)
    {
        TIM3->CCR1 = dutycycle;
    }
    else if (channel == 2)
    {
        TIM3->CCR2 = dutycycle;
    }
    else if (channel == 3)
    {
        TIM3->CCR3 = dutycycle;
    }
    else
    {
        TIM3->CCR4 = dutycycle;
    }
}
