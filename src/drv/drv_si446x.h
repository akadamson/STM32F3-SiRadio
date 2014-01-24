/*
 * drv_si446x.h
 *
 *  Created on: Jan 20, 2014
 *      Author: aadamson
 */

#pragma once

#define SI446x_SPI                            SPI1
#define SI446x_CS_PIN                         GPIO_Pin_0
#define SI446x_CS_GPIO_PORT                   GPIOB
#define SI446x_CS_GPIO_CLK                    RCC_AHBPeriph_GPIOB

#define SI446x_SDN_PIN                        GPIO_Pin_3
#define SI446x_SDN_GPIO_PORT                  GPIOB
#define SI446x_SDN_GPIO_CLK                   RCC_AHBPeriph_GPIOB

#define SI446x_VCXO_PIN                       GPIO_Pin_15
#define SI446x_VCXO_GPIO_PORT                 GPIOA
#define SI446x_VCXO_GPIO_CLK                  RCC_AHBPeriph_GPIOA

#define SI446x_IRQ_PIN                        GPIO_Pin_4
#define SI446x_IRQ_GPIO_PORT                  GPIOB
#define SI446x_IRQ_GPIO_CLK                   RCC_AHBPeriph_GPIOB

#define SI446x_GPIO0_PIN                      GPIO_Pin_5
#define SI446x_GPIO0_GPIO_PORT                GPIOB
#define SI446x_GPIO0_GPIO_CLK                 RCC_AHBPeriph_GPIOB

void si446xInit(void);
void si446xPTTOn(void);
void si446xPTTOff(void);
void si446xSetFreq(uint32_t freq);
void si446xSetPower(uint8_t pwr);
uint16_t si446xGetPower(void);
