/*
 * afsk.h
 *
 * Created: 1/5/2014 9:10:13 PM
 *  Author: aadamson
 */


#pragma once

#define MODEM_CLOCK_RATE        72000000 // SystemCoreClock
#define REST_DUTY               127     // 256 max value
#define SIN_TABLE_SIZE          512     // sine wave table size
#define PLAYBACK_RATE           100000  // rate that pwm period is updated (sample rate)

/*
extern const uint32_t MODEM_CLOCK_RATE;
extern const uint8_t REST_DUTY;
extern const uint16_t SIN_TABLE_SIZE;
//extern const uint32_t PLAYBACK_RATE;
extern const uint32_t PLAYBACK_RATE;
*/

#define BAUD_RATE           1200
#define SAMPLES_PER_BAUD    (PLAYBACK_RATE / BAUD_RATE)
#define PHASE_DELTA_1200    ((uint16_t)(((SIN_TABLE_SIZE * 1200L) << 7) / PLAYBACK_RATE))
#define PHASE_DELTA_2200    ((uint16_t)(((SIN_TABLE_SIZE * 2200L) << 7) / PLAYBACK_RATE))
//#define PHASE_DELTA_1200    786
//#define PHASE_DELTA_2200    1442

void afskSetFrequency(unsigned long freq);
void afskSend(const uint8_t *buffer, int len);
void afskStart(void);
bool afskBusy(void);
void afskISR(void);
void afskInit(void);
void afskTimerStop(void);
void afskTimerStart(void);
#ifdef DEBUG_MODEM
void afskDebug(void);
#endif
