/* trackuino copyright (C) 2010  EA5HAV Javi
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/* Credit to:
 *
 * Michael Smith for his Example of Audio generation with two timers and PWM:
 * http://www.arduino.cc/playground/Code/PCMAudio
 *
 * Ken Shirriff for his Great article on PWM:
 * http://arcfn.com/2009/07/secrets-of-arduino-pwm.html
 *
 * The large group of people who created the free AVR tools.
 * Documentation on interrupts:
 * http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html
 */

#include "board.h"

//#include "config.h"
//#include "afsk_avr.h"
//#include "afsk_pic32.h"
//#include "pin.h"
//#include "radio_si446x.h"
//#include <stdint.h>

//Sin table values
/*
const uint16_t sin_table[] =
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
*/

/* 100% PWM */
/*
const uint16_t sin_table[] =
{
    127, 129, 130, 132, 133, 135, 136, 138, 139, 141, 143, 144, 146, 147, 149, 150, 152, 153, 155, 156, 158,
    159, 161, 163, 164, 166, 167, 168, 170, 171, 173, 174, 176, 177, 179, 180, 182, 183, 184, 186, 187, 188,
    190, 191, 193, 194, 195, 197, 198, 199, 200, 202, 203, 204, 205, 207, 208, 209, 210, 211, 213, 214, 215,
    216, 217, 218, 219, 220, 221, 223, 224, 225, 226, 227, 228, 228, 229, 230, 231, 232, 233, 234, 235, 236,
    236, 237, 238, 239, 239, 240, 241, 242, 242, 243, 244, 244, 245, 245, 246, 247, 247, 248, 248, 249, 249,
    249, 250, 250, 251, 251, 251, 252, 252, 252, 253, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254,
    254, 254, 255, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 253, 253, 253, 253, 252, 252, 252, 251,
    251, 251, 250, 250, 249, 249, 249, 248, 248, 247, 247, 246, 245, 245, 244, 244, 243, 242, 242, 241, 240,
    239, 239, 238, 237, 236, 236, 235, 234, 233, 232, 231, 230, 229, 228, 228, 227, 226, 225, 224, 223, 221,
    220, 219, 218, 217, 216, 215, 214, 213, 211, 210, 209, 208, 207, 205, 204, 203, 202, 200, 199, 198, 197,
    195, 194, 193, 191, 190, 188, 187, 186, 184, 183, 182, 180, 179, 177, 176, 174, 173, 171, 170, 168, 167,
    166, 164, 163, 161, 159, 158, 156, 155, 153, 152, 150, 149, 147, 146, 144, 143, 141, 139, 138, 136, 135,
    133, 132, 130, 129, 127, 125, 124, 122, 121, 119, 118, 116, 115, 113, 111, 110, 108, 107, 105, 104, 102,
    101,  99,  98,  96,  95,  93,  91,  90,  88,  87,  86,  84,  83,  81,  80,  78,  77,  75,  74,  72,  71,
     70,  68,  67,  66,  64,  63,  61,  60,  59,  57,  56,  55,  54,  52,  51,  50,  49,  47,  46,  45,  44,
     43,  41,  40,  39,  38,  37,  36,  35,  34,  33,  31,  30,  29,  28,  27,  26,  26,  25,  24,  23,  22,
     21,  20,  19,  18,  18,  17,  16,  15,  15,  14,  13,  12,  12,  11,  10,  10,   9,   9,   8,   7,   7,
      6,   6,   5,   5,   5,   4,   4,   3,   3,   3,   2,   2,   2,   1,   1,   1,   1,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,
      2,   2,   2,   3,   3,   3,   4,   4,   5,   5,   5,   6,   6,   7,   7,   8,   9,   9,  10,  10,  11,
     12,  12,  13,  14,  15,  15,  16,  17,  18,  18,  19,  20,  21,  22,  23,  24,  25,  26,  26,  27,  28,
     29,  30,  31,  33,  34,  35,  36,  37,  38,  39,  40,  41,  43,  44,  45,  46,  47,  49,  50,  51,  52,
     54,  55,  56,  57,  59,  60,  61,  63,  64,  66,  67,  68,  70,  71,  72,  74,  75,  77,  78,  80,  81,
     83,  84,  86,  87,  88,  90,  91,  93,  95,  96,  98,  99, 101, 102, 104, 105, 107, 108, 110, 111, 113,
    115, 116, 118, 119, 121, 122, 124, 125
};
*/

/*
// 25% PWM
static const uint16_t sin_table[] =
{
        127, 127, 128, 128, 129, 129, 129, 130, 130, 130, 131, 131, 132, 132, 132, 133, 133, 133, 134, 134, 135,
        135, 135, 136, 136, 136, 137, 137, 137, 138, 138, 139, 139, 139, 140, 140, 140, 141, 141, 141, 142, 142,
        142, 143, 143, 143, 144, 144, 144, 145, 145, 145, 145, 146, 146, 146, 147, 147, 147, 148, 148, 148, 148,
        149, 149, 149, 149, 150, 150, 150, 150, 151, 151, 151, 151, 152, 152, 152, 152, 153, 153, 153, 153, 153,
        154, 154, 154, 154, 154, 155, 155, 155, 155, 155, 155, 155, 156, 156, 156, 156, 156, 156, 156, 157, 157,
        157, 157, 157, 157, 157, 157, 157, 157, 157, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158,
        158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 157, 157, 157, 157,
        157, 157, 157, 157, 157, 157, 157, 156, 156, 156, 156, 156, 156, 156, 155, 155, 155, 155, 155, 155, 155,
        154, 154, 154, 154, 154, 153, 153, 153, 153, 153, 152, 152, 152, 152, 151, 151, 151, 151, 150, 150, 150,
        150, 149, 149, 149, 149, 148, 148, 148, 148, 147, 147, 147, 146, 146, 146, 145, 145, 145, 145, 144, 144,
        144, 143, 143, 143, 142, 142, 142, 141, 141, 141, 140, 140, 140, 139, 139, 139, 138, 138, 137, 137, 137,
        136, 136, 136, 135, 135, 135, 134, 134, 133, 133, 133, 132, 132, 132, 131, 131, 130, 130, 130, 129, 129,
        129, 128, 128, 127, 127, 127, 126, 126, 125, 125, 125, 124, 124, 124, 123, 123, 122, 122, 122, 121, 121,
        121, 120, 120, 119, 119, 119, 118, 118, 118, 117, 117, 117, 116, 116, 115, 115, 115, 114, 114, 114, 113,
        113, 113, 112, 112, 112, 111, 111, 111, 110, 110, 110, 109, 109, 109, 109, 108, 108, 108, 107, 107, 107,
        106, 106, 106, 106, 105, 105, 105, 105, 104, 104, 104, 104, 103, 103, 103, 103, 102, 102, 102, 102, 101,
        101, 101, 101, 101, 100, 100, 100, 100, 100, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 98, 98, 98, 98, 97,
         97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96,
         96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 98, 98,
         98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 100, 100, 100, 100, 100, 101, 101, 101, 101, 101, 102,
        102, 102, 102, 103, 103, 103, 103, 104, 104, 104, 104, 105, 105, 105, 105, 106, 106, 106, 106, 107, 107,
        107, 108, 108, 108, 109, 109, 109, 109, 110, 110, 110, 111, 111, 111, 112, 112, 112, 113, 113, 113, 114,
        114, 114, 115, 115, 115, 116, 116, 117, 117, 117, 118, 118, 118, 119, 119, 119, 120, 120, 121, 121, 121,
        122, 122, 122, 123, 123, 124, 124, 124, 125, 125, 125, 126, 126, 127
};
*/

//Sin table values 22-23%
static const uint16_t sin_table[] =
{
        127, 127, 128, 128, 128, 129, 129, 129, 130, 130, 131, 131, 131, 132, 132, 132, 133, 133, 133, 134, 134,
        134, 135, 135, 135, 136, 136, 136, 137, 137, 137, 138, 138, 138, 139, 139, 139, 140, 140, 140, 141, 141,
        141, 142, 142, 142, 143, 143, 143, 143, 144, 144, 144, 145, 145, 145, 145, 146, 146, 146, 146, 147, 147,
        147, 148, 148, 148, 148, 148, 149, 149, 149, 149, 150, 150, 150, 150, 151, 151, 151, 151, 151, 152, 152,
        152, 152, 152, 152, 153, 153, 153, 153, 153, 153, 154, 154, 154, 154, 154, 154, 154, 154, 155, 155, 155,
        155, 155, 155, 155, 155, 155, 155, 155, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156,
        156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 155, 155, 155,
        155, 155, 155, 155, 155, 155, 155, 155, 154, 154, 154, 154, 154, 154, 154, 154, 153, 153, 153, 153, 153,
        153, 152, 152, 152, 152, 152, 152, 151, 151, 151, 151, 151, 150, 150, 150, 150, 149, 149, 149, 149, 148,
        148, 148, 148, 148, 147, 147, 147, 146, 146, 146, 146, 145, 145, 145, 145, 144, 144, 144, 143, 143, 143,
        143, 142, 142, 142, 141, 141, 141, 140, 140, 140, 139, 139, 139, 138, 138, 138, 137, 137, 137, 136, 136,
        136, 135, 135, 135, 134, 134, 134, 133, 133, 133, 132, 132, 132, 131, 131, 131, 130, 130, 129, 129, 129,
        128, 128, 128, 127, 127, 127, 126, 126, 126, 125, 125, 125, 124, 124, 123, 123, 123, 122, 122, 122, 121,
        121, 121, 120, 120, 120, 119, 119, 119, 118, 118, 118, 117, 117, 117, 116, 116, 116, 115, 115, 115, 114,
        114, 114, 113, 113, 113, 112, 112, 112, 111, 111, 111, 111, 110, 110, 110, 109, 109, 109, 109, 108, 108,
        108, 108, 107, 107, 107, 106, 106, 106, 106, 106, 105, 105, 105, 105, 104, 104, 104, 104, 103, 103, 103,
        103, 103, 102, 102, 102, 102, 102, 102, 101, 101, 101, 101, 101, 101, 100, 100, 100, 100, 100, 100, 100,
        100, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98,
        98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 99,
        99, 99, 100, 100, 100, 100, 100, 100, 100, 100, 101, 101, 101, 101, 101, 101, 102, 102, 102, 102, 102,
        102, 103, 103, 103, 103, 103, 104, 104, 104, 104, 105, 105, 105, 105, 106, 106, 106, 106, 106, 107, 107,
        107, 108, 108, 108, 108, 109, 109, 109, 109, 110, 110, 110, 111, 111, 111, 111, 112, 112, 112, 113, 113,
        113, 114, 114, 114, 115, 115, 115, 116, 116, 116, 117, 117, 117, 118, 118, 118, 119, 119, 119, 120, 120,
        120, 121, 121, 121, 122, 122, 122, 123, 123, 123, 124, 124, 125, 125, 125, 126, 126, 126, 127
};

/*
const uint32_t MODEM_CLOCK_RATE     = 72000000;
const uint8_t REST_DUTY             = 127;
const uint16_t SIN_TABLE_SIZE       = sizeof(sin_table);
//const uint32_t PLAYBACK_RATE      = MODEM_CLOCK_RATE / 510;  // Phase correct PWM
const uint32_t PLAYBACK_RATE        = MODEM_CLOCK_RATE / 256;  // Fast PWM
*/

// Module consts
/*
static const uint16_t BAUD_RATE       = 1200;
static const uint8_t SAMPLES_PER_BAUD = (PLAYBACK_RATE / BAUD_RATE);
static const uint16_t PHASE_DELTA_1200 = (((SIN_TABLE_SIZE * 1200L) << 7) / PLAYBACK_RATE); // Fixed point 9.7
static const uint16_t PHASE_DELTA_2200 = (((SIN_TABLE_SIZE * 2200L) << 7) / PLAYBACK_RATE);
*/

// Module globals
static volatile unsigned char current_byte;
static volatile unsigned char current_sample_in_baud;    // 1 bit = SAMPLES_PER_BAUD samples
static volatile bool go = false;                         // Modem is on
static volatile uint16_t phase_delta;                // 1200/2200 for standard AX.25
static volatile uint16_t phase;                      // Fixed point 9.7 (2PI = SIN_TABLE_SIZE)
static volatile unsigned int packet_pos;                 // Next bit to be sent out
#ifdef DEBUG_MODEM
static volatile int overruns = 0;
static volatile uint32_t isr_calls = 0;
static volatile uint32_t avg_isr_time = 0;
static volatile uint32_t fast_isr_time = 65535;
static volatile uint32_t slow_isr_time = 0;
static volatile unsigned int slow_packet_pos;
static volatile unsigned char slow_sample_in_baud;
#endif

uint16_t pulse_width = REST_DUTY;
//uint32_t phase_accumulator = 0;
uint16_t angle = 0;


// The radio (class defined in config.h)
//static RadioSi446x radio;

static volatile unsigned int afsk_packet_size = 0;
static volatile const uint8_t *afsk_packet;

// Exported functions
void afskInit(void)
{
    // Start radio
    //radio.setup();
}

void afskSend(const uint8_t *buffer, int len)
{
    afsk_packet_size = len;
    afsk_packet = buffer;
}

bool afskBusy(void)
{
    return go;
}

void afskSetFrequency(unsigned long freq)
{
    //radio.set_freq(freq);
    si446xSetFreq(freq);
}

void afskTimerStop(void)
{
    setPWM_dutycycle(4, REST_DUTY);

    TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
}

void afskTimerStart(void)
{
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void afskStart(void)
{
    phase_delta = PHASE_DELTA_1200;
    phase = 0;
    packet_pos = 0;
    current_sample_in_baud = 0;
    go = true;

    // Start timer (CPU-specific)
    //afskTimerSetup();

    // Key the radio
    si446xPTTOn();
    //radio.ptt_on();

    // Start transmission
    afskTimerStart();
}

// This is called at PLAYBACK_RATE Hz to load the next sample.
void afskISR(void)
{

#if 0

        setPWM_dutycycle(4, pulse_width);

        // Calculate a new pulse width
        phase += PHASE_DELTA_2200;
        angle = (uint16_t)(phase >> 7);
        pulse_width = sin_table[angle];

#else
    if (go)
    {
        // If done sending packet
        if (packet_pos == afsk_packet_size)
        {
            go = false;         // End of transmission

            afskTimerStop();    // Disable modem
            si446xPTTOff();
            //radio.ptt_off();  // Release PTT
            goto end_isr;       // Done, gather ISR stats
        }

        // If sent SAMPLES_PER_BAUD already, go to the next bit
        if (current_sample_in_baud == 0)      // Load up next bit
        {
            if ((packet_pos & 7) == 0)          // Load up next byte
                current_byte = afsk_packet[packet_pos >> 3];
            else
                current_byte = current_byte / 2;  // ">>1" forces int conversion

            if ((current_byte & 1) == 0)
            {
                // Toggle tone (1200 <> 2200)
                phase_delta ^= (PHASE_DELTA_1200 ^ PHASE_DELTA_2200);
                //phase_delta = PHASE_DELTA_2200;
            }
        }

        phase += phase_delta;
        angle = (uint16_t)((phase >> 7) & (SIN_TABLE_SIZE - 1)); // range of values have to stay between 0 and SIN_TABLE_SIZE - 1
        pulse_width = sin_table[angle];
        //uint8_t s = afskReadSample((phase >> 7) & (SIN_TABLE_SIZE - 1));

        setPWM_dutycycle(4, pulse_width);
        //afskOutputSample(s);

        if (++current_sample_in_baud == SAMPLES_PER_BAUD)
        {
            current_sample_in_baud = 0;
            packet_pos++;
        }
    }

end_isr:
#ifdef DEBUG_MODEM

    // Track overruns
    //if (afskIsrOverrun())
    //overruns++;
    overruns = 99;


    isr_calls++;
    uint32_t t = TIM_GetCounter(TIM2);
    //uint16_t t = afskTimerCounter();

    // Track slowest execution time in slow_isr_time
    if (t > slow_isr_time)
    {
        slow_isr_time = t;
        slow_packet_pos = packet_pos;
        slow_sample_in_baud = current_sample_in_baud;
    }

    // Track fastest execution time
    if (t < fast_isr_time)
    {
        fast_isr_time = t;
    }

    // Track average time
    avg_isr_time += t;
#endif
#endif
    return;
}

#ifdef DEBUG_MODEM
void afskDebug(void)
{
    cliPrintF("t(fast,avg,slow)=%ld,", fast_isr_time);
    //Serial.print("t(fast,avg,slow)=");
    //Serial.print(fast_isr_time);
    //Serial.print(",");

    if (isr_calls)
        cliPrintF("%ld", (avg_isr_time / isr_calls));
    //Serial.print(avg_isr_time / isr_calls);
    else
        cliPrint("INF");

    //Serial.print("INF");

    cliPrintF(",%ld; pos=%ld/%d; sam =%d; overruns/isr=%d/%ld\n", slow_isr_time, slow_packet_pos, afsk_packet_size, slow_sample_in_baud, overruns, isr_calls);
    //Serial.print(",");
    //Serial.print(slow_isr_time);
    //Serial.print("; pos=");
    //Serial.print(slow_packet_pos);
    //Serial.print("/");
    //Serial.print(afsk_packet_size);
    //Serial.print("; sam=");
    //Serial.print(slow_sample_in_baud, DEC);
    //Serial.print("; overruns/isr=");
    //Serial.print(overruns);
    //Serial.print("/");
    //Serial.println(isr_calls);

    isr_calls = 0;
    avg_isr_time = 0;
    slow_isr_time = 0;
    fast_isr_time = 65535;
    overruns = 0;
}
#endif
