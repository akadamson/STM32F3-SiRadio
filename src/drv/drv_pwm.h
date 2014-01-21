/*
 * drv_pwm.h
 *
 *  Created on: Jan 19, 2014
 *      Author: aadamson
 */

#pragma once

#define R 107374182

extern uint16_t sin_table[];
extern uint16_t pulse_width;
extern uint32_t phase_accumulator;
extern uint8_t angle;

void pwmTim3_Channel4Init(void);
void setPWM_dutycycle(uint16_t channel, uint16_t dutycycle);
