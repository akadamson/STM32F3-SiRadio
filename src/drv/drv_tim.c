/*
 * drv_tim.c
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

/*
uint16_t sin_table[] =
{
        512, 518, 525, 531, 537, 543, 550, 556, 562, 568, 575, 581, 587, 593, 599, 606, 612,
        618, 624, 630, 636, 642, 648, 654, 660, 666, 672, 678, 684, 690, 696, 702, 708, 713,
        719, 725, 730, 736, 742, 747, 753, 758, 764, 769, 775, 780, 785, 791, 796, 801, 806,
        811, 816, 821, 826, 831, 836, 841, 846, 850, 855, 860, 864, 869, 873, 878, 882, 886,
        891, 895, 899, 903, 907, 911, 915, 919, 922, 926, 930, 933, 937, 940, 944, 947, 950,
        953, 957, 960, 963, 966, 968, 971, 974, 977, 979, 982, 984, 986, 989, 991, 993, 995,
        997, 999, 1001, 1003, 1004, 1006, 1008, 1009, 1011, 1012, 1013, 1014, 1015, 1017,
        1017, 1018, 1019, 1020, 1021, 1021, 1022, 1022, 1022, 1023, 1023, 1023, 1023, 1023,
        1023, 1023, 1022, 1022, 1022, 1021, 1021, 1020, 1019, 1018, 1017, 1017, 1015, 1014,
        1013, 1012, 1011, 1009, 1008, 1006, 1004, 1003, 1001, 999, 997, 995, 993, 991, 989, 986,
        984, 982, 979, 977, 974, 971, 968, 966, 963, 960, 957, 953, 950, 947, 944, 940, 937, 933,
        930, 926, 922, 919, 915, 911, 907, 903, 899, 895, 891, 886, 882, 878, 873, 869, 864, 860,
        855, 850, 846, 841, 836, 831, 826, 821, 816, 811, 806, 801, 796, 791, 785, 780, 775, 769,
        764, 758, 753, 747, 742, 736, 730, 725, 719, 713, 708, 702, 696, 690, 684, 678, 672, 666,
        660, 654, 648, 642, 636, 630, 624, 618, 612, 606, 599, 593, 587, 581, 575, 568, 562, 556,
        550, 543, 537, 531, 525, 518, 512, 506, 499, 493, 487, 481, 474, 468, 462, 456, 449, 443,
        437, 431, 425, 418, 412, 406, 400, 394, 388, 382, 376, 370, 364, 358, 352, 346, 340, 334,
        328, 322, 316, 311, 305, 299, 294, 288, 282, 277, 271, 266, 260, 255, 249, 244, 239, 233,
        228, 223, 218, 213, 208, 203, 198, 193, 188, 183, 178, 174, 169, 164, 160, 155, 151, 146,
        142, 138, 133, 129, 125, 121, 117, 113, 109, 105, 102, 98, 94, 91, 87, 84, 80, 77, 74, 71,
        67, 64, 61, 58, 56, 53, 50, 47, 45, 42, 40, 38, 35, 33, 31, 29, 27, 25, 23, 21, 20, 18, 16,
        15, 13, 12, 11, 10, 9, 7, 7, 6, 5, 4, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4,
        5, 6, 7, 7, 9, 10, 11, 12, 13, 15, 16, 18, 20, 21, 23, 25, 27, 29, 31, 33, 35, 38, 40, 42,
        45, 47, 50, 53, 56, 58, 61, 64, 67, 71, 74, 77, 80, 84, 87, 91, 94, 98, 102, 105, 109, 113,
        117, 121, 125, 129, 133, 138, 142, 146, 151, 155, 160, 164, 169, 174, 178, 183, 188, 193,
        198, 203, 208, 213, 218, 223, 228, 233, 239, 244, 249, 255, 260, 266, 271, 277, 282, 288,
        294, 299, 305, 311, 316, 322, 328, 334, 340, 346, 352, 358, 364, 370, 376, 382, 388, 394,
        400, 406, 412, 418, 425, 431, 437, 443, 449, 456, 462, 468, 474, 481, 487, 493, 499, 506
};
*/

uint16_t pulse_width = 128;
uint32_t phase_accumulator = 0;
uint8_t angle = 0;

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
#ifdef DEBUG_TIM2
        GPIO_SetBits(TIM2D_GPIO_PORT, TIM2D_PIN);
#endif

        setPWM_dutycycle(4, pulse_width);

        // Calculate a new pulse width
        phase_accumulator += R;
        angle = (uint16_t)(phase_accumulator >> 24);
        pulse_width = sin_table[angle];

        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

#ifdef DEBUG_TIM2
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
