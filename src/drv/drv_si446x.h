/*
 * drv_si446x.h
 *
 *  Created on: Jan 20, 2014
 *      Author: aadamson
 */

#pragma once

#define SI446x_CS_PIN                         GPIO_Pin_0
#define SI446x_CS_GPIO_PORT                   GPIOB
#define SI446x_CS_GPIO_CLK                    RCC_AHBPeriph_GPIOB
#define SI446x_SPI                            SPI1

void si446xInit(void);

