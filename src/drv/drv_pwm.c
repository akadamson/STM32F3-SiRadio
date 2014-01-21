/*
 * drv_pwm.c
 *
 *  Created on: Jan 19, 2014
 *      Author: aadamson
 */

#include "board.h"
//Sin table values
uint16_t sin_table[] =
{
    127, 130, 133, 136, 139, 143, 146, 149, 152, 155, 158, 161, 164, 167, 170, 173, 176, 178,
    181, 184, 187, 190, 192, 195, 198, 200, 203, 205, 208, 210, 212, 215, 217, 219, 221, 223,
    225, 227, 229, 231, 233, 234, 236, 238, 239, 240, 242, 243, 244, 245, 247, 248, 249, 249,
    250, 251, 252, 252, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 253, 253, 253, 252,
    252, 251, 250, 249, 249, 248, 247, 245, 244, 243, 242, 240, 239, 238, 236, 234, 233, 231,
    229, 227, 225, 223, 221, 219, 217, 215, 212, 210, 208, 205, 203, 200, 198, 195, 192, 190,
    187, 184, 181, 178, 176, 173, 170, 167, 164, 161, 158, 155, 152, 149, 146, 143, 139, 136,
    133, 130, 127, 124, 121, 118, 115, 111, 108, 105, 102, 99, 96, 93, 90, 87, 84, 81, 78, 76,
    73, 70, 67, 64, 62, 59, 56, 54, 51, 49, 46, 44, 42, 39, 37, 35, 33, 31, 29, 27, 25, 23,
    21, 20, 18, 16, 15, 14, 12, 11, 10, 9, 7, 6, 5, 5, 4, 3, 2, 2, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 1, 2, 2, 3, 4, 5, 5, 6, 7, 9, 10, 11, 12, 14, 15, 16, 18, 20, 21, 23, 25,
    27, 29, 31, 33, 35, 37, 39, 42, 44, 46, 49, 51, 54, 56, 59, 62, 64, 67, 70, 73, 76, 78,
    81, 84, 87, 90, 93, 96, 99, 102, 105, 108, 111, 115, 118, 121, 124
};

uint16_t pulse_width = 128;
uint32_t phase_accumulator = 0;
uint8_t angle = 0;

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
