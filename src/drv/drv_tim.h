/*
 * drv_tim.h
 *
 *  Created on: Jan 19, 2014
 *      Author: aadamson
 */

#pragma once

extern uint16_t sin_table[];
extern uint16_t pulse_width;
extern uint32_t phase_accumulator;
extern uint8_t angle;

#define TIM3_CH2_Pin        GPIO_Pin_1
#define TIM3_CH2_PinSource  GPIO_PinSource1
#define TIM3_CH2_PORT       GPIOB
#define TIM3_CH2_CLK        RCC_AHBPeriph_GPIOB

void timersInit(void);
