/*
 * drv_pwm.h
 *
 *  Created on: Jan 19, 2014
 *      Author: aadamson
 */

#pragma once

void pwmTim3_Channel4Init(void);
void setPWM_dutycycle(uint16_t channel, uint16_t dutycycle);
