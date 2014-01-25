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
//#include "config.h"
//#include "ax25.h"
//#include "gps.h"
//#include "aprs.h"
//#include "afsk.h"
//#include "sensors_avr.h"
//#include "sensors_pic32.h"
//#include <stdio.h>
//#include <stdlib.h>

// Module functions
float meters_to_feet(float m)
{
    // 10000 ft = 3048 m
    return m / 0.3048;
}

// Exported functions
void aprsSend()
{

    char temp[12];                   // Temperature (int/ext)
    const struct s_address addresses[] =
    {
        {D_CALLSIGN, D_CALLSIGN_ID},  // Destination callsign
        {S_CALLSIGN, S_CALLSIGN_ID},  // Source callsign (-11 = balloon, -9 = car)
#ifdef DIGI_PATH1
        {DIGI_PATH1, DIGI_PATH1_TTL}, // Digi1 (first digi in the chain)
#endif
#ifdef DIGI_PATH2
        {DIGI_PATH2, DIGI_PATH2_TTL}, // Digi2 (second digi in the chain)
#endif
    };

    ax25SendHeader(addresses, sizeof(addresses) / sizeof(struct s_address));
    ax25SendByte('/');                // Report w/ timestamp, no APRS messaging. $ = NMEA raw data
    // ax25SendString("021709z");     // 021709z = 2nd day of the month, 17:09 zulu (UTC/GMT)
    ax25SendString(gps_time);         // 170915 = 17h:09m:15s zulu (not allowed in Status Reports)
    ax25SendByte('h');
    ax25SendString(gps_aprs_lat);     // Lat: 38deg and 22.20 min (.20 are NOT seconds, but 1/100th of minutes)
    ax25SendByte(APRS_SYMBOL_TABLE);                // Symbol table
    ax25SendString(gps_aprs_lon);     // Lon: 000deg and 25.80 min
    ax25SendByte(APRS_SYMBOL_ID);                // Symbol: /O=balloon, /-=QTH, \N=buoy
    snprintf(temp, 4, "%03d", (int)(gps_course + 0.5));
    ax25SendString(temp);             // Course (degrees)
    ax25SendByte('/');                // and
    snprintf(temp, 4, "%03d", (int)(gps_speed + 0.5));
    ax25SendString(temp);             // speed (knots)
    ax25SendString("/A=");            // Altitude (feet). Goes anywhere in the comment area
    snprintf(temp, 7, "%06ld", (long)(meters_to_feet(gps_altitude) + 0.5));
    ax25SendString(temp);
    /* ax25SendString("/Ti=");
     snprintf(temp, 6, "%d", sensors_int_lm60());
     ax25SendString(temp);
     ax25SendString("/Te=");
     snprintf(temp, 6, "%d", sensors_ext_lm60());
     ax25SendString(temp);
     ax25SendString("/V=");
     snprintf(temp, 6, "%d", sensors_vin());
     ax25SendString(temp);
     */
    ax25SendByte(' ');
    ax25SendString(APRS_COMMENT);     // Comment
    ax25SendFooter();

    ax25FlushFrame();                 // Tell the modem to go
    afskSetFrequency(RADIO_FREQ);
}
