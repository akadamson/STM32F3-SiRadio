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

#include "board.h"
//#include "ax25.h"
//#include "config.h"
//#include "afsk_avr.h"
//#include "afsk_pic32.h"
//#include <stdint.h>

// Module constants
//static const unsigned int MAX_PACKET = 512;  // bytes
#define MAX_PACKET  512

// Module globals
static uint16_t crc;
static uint8_t ones_in_a_row;
static uint8_t packet[MAX_PACKET];
static unsigned int packet_size;

// Module functions
static void updateCrc(uint8_t a_bit)
{
    crc ^= a_bit;

    if (crc & 1)
        crc = (crc >> 1) ^ 0x8408;  // X-modem CRC poly
    else
        crc = crc >> 1;
}

static void sendByte(uint8_t a_byte)
{
    uint8_t i = 0;

    while (i++ < 8)
    {
        uint8_t a_bit = a_byte & 1;
        a_byte >>= 1;
        updateCrc(a_bit);

        if (a_bit)
        {
            // Next bit is a '1'
            if (packet_size >= MAX_PACKET * 8)  // Prevent buffer overrun
                return;

            packet[packet_size >> 3] |= (1 << (packet_size & 7));
            packet_size++;

            if (++ones_in_a_row < 5) continue;
        }

        // Next bit is a '0' or a zero padding after 5 ones in a row
        if (packet_size >= MAX_PACKET * 8)    // Prevent buffer overrun
            return;

        packet[packet_size >> 3] &= ~(1 << (packet_size & 7));
        packet_size++;
        ones_in_a_row = 0;
    }
}

// Exported functions
void ax25SendByte(uint8_t a_byte)
{
    // Wrap around sendByte, but prints debug info
    sendByte(a_byte);
#ifdef DEBUG_AX25
    cliPrintF("%c", (char)a_byte);
#endif
}

void ax25SendFlag(void)
{
    uint8_t flag = 0x7e;
    int i;

    for (i = 0; i < 8; i++, packet_size++)
    {
        if (packet_size >= MAX_PACKET * 8)  // Prevent buffer overrun
            return;

        if ((flag >> i) & 1)
            packet[packet_size >> 3] |= (1 << (packet_size & 7));
        else
            packet[packet_size >> 3] &= ~(1 << (packet_size & 7));
    }
}

void ax25SendString(const char *string)
{
    int i;

    for (i = 0; string[i]; i++)
    {
        ax25SendByte(string[i]);
    }
}

void ax25SendHeader(const struct s_address *addresses, int num_addresses)
{
    int i, j;
    packet_size = 0;
    ones_in_a_row = 0;
    crc = 0xffff;

    // Send flags during TX_DELAY milliseconds (8 bit-flag = 8000/1200 ms)
    for (i = 0; i < TX_DELAY * 3 / 20; i++)
    {
        ax25SendFlag();
    }

    for (i = 0; i < num_addresses; i++)
    {
        // Transmit callsign
        for (j = 0; addresses[i].callsign[j]; j++)
            sendByte(addresses[i].callsign[j] << 1);

        // Transmit pad
        for (; j < 6; j++)
            sendByte(' ' << 1);

        // Transmit SSID. Termination signaled with last bit = 1
        if (i == num_addresses - 1)
            sendByte(('0' + addresses[i].ssid) << 1 | 1);
        else
            sendByte(('0' + addresses[i].ssid) << 1);
    }

    // Control field: 3 = APRS-UI frame
    sendByte(0x03);

    // Protocol ID: 0xf0 = no layer 3 data
    sendByte(0xf0);

#ifdef DEBUG_AX25
    // Print source callsign
    cliPrintF("\n[%ld] %s", millis(), addresses[1].callsign);
    //Serial.println();
    //Serial.print('[');
    //Serial.print(millis());
    //Serial.print("] ");
    //Serial.print(addresses[1].callsign);

    if (addresses[1].ssid)
    {
        cliPrintF("-%d", addresses[1].ssid);
        //Serial.print('-');
        //Serial.print((unsigned int)addresses[1].ssid);
    }

    cliPrintF(">%s", addresses[0].callsign);
    //Serial.print('>');
    // Destination callsign
    //Serial.print(addresses[0].callsign);

    if (addresses[0].ssid)
    {
        cliPrintF("-%d", addresses[0].ssid);
        //Serial.print('-');
        //Serial.print((unsigned int)addresses[0].ssid);
    }

    for (i = 2; i < num_addresses; i++)
    {
        cliPrintF(",%s", addresses[i].callsign);
        //Serial.print(',');
        //Serial.print(addresses[i].callsign);

        if (addresses[i].ssid)
        {
            cliPrintF("-%d", addresses[i].ssid);
            //Serial.print('-');
            //Serial.print((unsigned int)addresses[i].ssid);
        }
    }

    cliPrint(":");
    //Serial.print(':');
#endif
}

void ax25SendFooter(void)
{
    // Save the crc so that it can be treated it atomically
    uint16_t final_crc = crc;

    // Send the CRC
    sendByte(~(final_crc & 0xff));
    final_crc >>= 8;
    sendByte(~(final_crc & 0xff));

    // Signal the end of frame
    ax25SendFlag();
#ifdef DEBUG_AX25
    cliPrint("\n");
#endif
}

void ax25FlushFrame(void)
{
    // Key the transmitter and send the frame
    afskSend(packet, packet_size);
    afskStart();
}
