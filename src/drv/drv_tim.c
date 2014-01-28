/*
 * drv_tim.c
 *
 *  Created on: Jan 19, 2014
 *      Author: aadamson
 */
#include "board.h"

static void tim3CH2_gpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* TIM3_CH2_CLK Clocks enable */
    RCC_AHBPeriphClockCmd(TIM3_CH2_CLK, ENABLE);

    /* TIM3_CH2_PORT Configuration: Channel 1, 2, 3 and 4 as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin     = TIM3_CH2_Pin;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_NOPULL;

    GPIO_Init(TIM3_CH2_PORT, &GPIO_InitStructure);

    GPIO_PinAFConfig(TIM3_CH2_PORT, TIM3_CH2_PinSource, GPIO_AF_2);
}

static void tim3Init(uint32_t frequency)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    uint16_t timerPeriod = 0;

    /* TIM3 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);

    /* Compute the value to be set in ARR register to generate signal frequency at frequency/100 Khz */
    /* based upon a 256 pulse */
    timerPeriod = (uint16_t)(SystemCoreClock / frequency) - 1;

    /* Time Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler         = 1 - 1;  // run at full rate
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period            = timerPeriod;
    TIM_TimeBaseStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_Cmd(TIM3, ENABLE);
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
#ifdef DEBUG_TIMING
        GPIO_SetBits(TIM2D_GPIO_PORT, TIM2D_PIN);
#endif

        afskISR();

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

#ifdef DEBUG_TIMING
        GPIO_ResetBits(TIM2D_GPIO_PORT, TIM2D_PIN);
#endif
    }
}

void tim2Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    /* Enable the TIM2 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                      = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    /* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period        = 10 - 1;  // 1 MHz down to 100 KHz
    TIM_TimeBaseStructure.TIM_Prescaler     = 72 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* TIM IT enable */
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);
}


void timersInit(void)
{
    // Init the Timer 3 channel 2
    // with a pwm rate of 281.250 khz
    tim3CH2_gpioInit();
    tim3Init(281250);

    tim2Init();
}
