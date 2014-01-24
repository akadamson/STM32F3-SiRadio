/*
  August 2013

  Focused Flight32 Rev -

  Copyright (c) 2013 John Ihlein.  All rights reserved.

  Open Source STM32 Based Multicopter Controller Software

  Designed to run on the Naze32Pro Flight Control Board

  Includes code and/or ideas from:

  1)AeroQuad
  2)BaseFlight
  3)CH Robotics
  4)MultiWii
  5)Paparazzi UAV
  5)S.O.H. Madgwick
  6)UAVX

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

///////////////////////////////////////////////////////////////////////////////

#include "board.h"

///////////////////////////////////////////////////////////////////////////////

uint8_t cliBusy = false;

static volatile uint8_t cliQuery        = 'x';
static volatile uint8_t validCliCommand = false;

///////////////////////////////////////////////////////////////////////////////
// Read Character String from CLI
///////////////////////////////////////////////////////////////////////////////

char *readStringCLI(char *data, uint8_t length)
{
    uint8_t index    = 0;
    uint8_t timeout  = 0;

    do
    {
        if (cliAvailable() == false)
        {
            delay(10);
            timeout++;
        }
        else
        {
            data[index] = cliRead();
            timeout = 0;
            index++;
        }
    }
    while ((index == 0 || data[index - 1] != ';') && (timeout < 5) && (index < length));

    data[index] = '\0';

    return data;
}

///////////////////////////////////////////////////////////////////////////////
// Read Float from CLI
///////////////////////////////////////////////////////////////////////////////

float readFloatCLI(void)
{
    uint8_t index    = 0;
    uint8_t timeout  = 0;
    char    data[13] = "";

    do
    {
        if (cliAvailable() == false)
        {
            delay(10);
            timeout++;
        }
        else
        {
            data[index] = cliRead();
            timeout = 0;
            index++;
        }
    }
    while ((index == 0 || data[index - 1] != ';') && (timeout < 5) && (index < sizeof(data) - 1));

    data[index] = '\0';

    return stringToFloat(data);
}

///////////////////////////////////////////////////////////////////////////////
// CLI Communication
///////////////////////////////////////////////////////////////////////////////

void cliCom(void)
{
    //uint8_t  index;

    if ((cliAvailable() && !validCliCommand))
        cliQuery = cliRead();

    switch (cliQuery)
    {
            ///////////////////////////////

        case 'a': // Not Used

            cliQuery = 'x';
            validCliCommand = false;
            break;

         ///////////////////////////////


        case 'b': // Not Used

            cliQuery = 'x';
            validCliCommand = false;
            break;

         ///////////////////////////////
        case 'e': // Loop Delta Times
            cliPrintF("%7ld, %7ld, %7ld, %7ld, %7ld, %7ld, %7ld\n", deltaTime1000Hz,
                      deltaTime500Hz,
                      deltaTime100Hz,
                      deltaTime50Hz,
                      deltaTime10Hz,
                      deltaTime5Hz,
                      deltaTime1Hz);
            validCliCommand = false;
            break;

            ///////////////////////////////

        case 'f': // Loop Execution Times
            cliPrintF("%7ld, %7ld, %7ld, %7ld, %7ld, %7ld, %7ld\n", executionTime1000Hz,
                      executionTime500Hz,
                      executionTime100Hz,
                      executionTime50Hz,
                      executionTime10Hz,
                      executionTime5Hz,
                      executionTime1Hz);
            validCliCommand = false;
            break;

            ///////////////////////////////

        case 'g': // Not Used
            cliPrintF("spiErrors: %04d\n", spiGetErrorCounter(SI446x_SPI));

            cliQuery = 'x';
            validCliCommand = false;
            break;

            ///////////////////////////////

        case 'q': // Not Used
            cliQuery = 'x';
            validCliCommand = false;
            break;

            ///////////////////////////////

        case 's': // Not Used
            cliPrint("TX off\n");
            si446xPTTOff();

            cliQuery = 'x';
            validCliCommand = false;
            break;

             ///////////////////////////////

        case 't': // Not Used
            cliPrint("TX on\n");
            si446xPTTOn();

            cliQuery = 'x';
            validCliCommand = false;
            break;

            ///////////////////////////////

        case 'x':
            validCliCommand = false;
            break;

            ///////////////////////////////

            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////

        case 'S': // Reset System
            cliPrint("\nSystem Reseting....\n\n");
            delay(100);
            systemReset(false);
            break;

            ///////////////////////////////

        case 'X': // Not Used
            cliQuery = 'x';
            validCliCommand = false;
            break;

            ///////////////////////////////

        case 'Y': // Not Used
            cliQuery = 'x';
            break;

            ///////////////////////////////

        case 'Z': // Not Used
            cliQuery = 'x';
            break;

            ///////////////////////////////

        case '?': // Command Summary
            cliBusy = true;

            cliPrint("\n");
            cliPrint("'a' Rate PIDs                              'A' Set Roll Rate PID Data   AB;P;I;D;windupGuard;dErrorCalc\n");
            cliPrint("'b' Attitude PIDs                          'B' Set Pitch Rate PID Data  BB;P;I;D;windupGuard;dErrorCalc\n");
            cliPrint("'c' Velocity PIDs                          'C' Set Yaw Rate PID Data    CB;P;I;D;windupGuard;dErrorCalc\n");
            cliPrint("'d' Position PIDs                          'D' Set Roll Att PID Data    DB;P;I;D;windupGuard;dErrorCalc\n");
            cliPrint("'e' Loop Delta Times                       'E' Set Pitch Att PID Data   EB;P;I;D;windupGuard;dErrorCalc\n");
            cliPrint("'f' Loop Execution Times                   'F' Set Hdg Hold PID Data    FB;P;I;D;windupGuard;dErrorCalc\n");
            cliPrint("'g' 500 Hz Accels                          'G' Set nDot PID Data        GB;P;I;D;windupGuard;dErrorCalc\n");
            cliPrint("'h' 100 Hz Earth Axis Accels               'H' Set eDot PID Data        HB;P;I;D;windupGuard;dErrorCalc\n");
            cliPrint("'i' 500 Hz Gyros                           'I' Set hDot PID Data        IB;P;I;D;windupGuard;dErrorCalc\n");
            cliPrint("'j' 10 hz Mag Data                         'J' Set n PID Data           JB;P;I;D;windupGuard;dErrorCalc\n");
            cliPrint("'k' Vertical Axis Variable                 'K' Set e PID Data           KB;P;I;D;windupGuard;dErrorCalc\n");
            cliPrint("'l' Attitudes                              'L' Set h PID Data           LB;P;I;D;windupGuard;dErrorCalc\n");
            cliPrint("\n");

            cliPrint("Press space bar for more, or enter a command....\n");

            while (cliAvailable() == false);

            cliQuery = cliRead();

            if (cliQuery != ' ')
            {
                validCliCommand = true;
                cliBusy = false;
                return;
            }

            cliPrint("\n");
            cliPrint("'m' Axis PIDs                              'M' Not Used\n");
            cliPrint("'n' Not Used                               'N' Mixer CLI\n");
            cliPrint("'o' Battery Voltage                        'O' Receiver CLI\n");
            cliPrint("'p' Not Used                               'P' Sensor CLI\n");
            cliPrint("'q' Primary Spektrum Raw Data              'Q' Not Used\n");
            cliPrint("'r' Mode States                            'R' Reset and Enter Bootloader\n");
            cliPrint("'s' Raw Receiver Commands                  'S' Reset\n");
            cliPrint("'t' Processed Receiver Commands            'T' Telemetry CLI\n");
            cliPrint("'u' Command In Detent Discretes            'U' EEPROM CLI\n");
            cliPrint("'v' Motor PWM Outputs                      'V' Reset EEPROM Parameters\n");
            cliPrint("'w' Servo PWM Outputs                      'W' Write EEPROM Parameters\n");
            cliPrint("'x' Terminate Serial Communication         'X' Not Used\n");
            cliPrint("\n");

            cliPrint("Press space bar for more, or enter a command....\n");

            while (cliAvailable() == false);

            cliQuery = cliRead();

            if (cliQuery != ' ')
            {
                validCliCommand = true;
                cliBusy = false;
                return;
            }

            cliPrint("\n");
            cliPrint("'y' ESC Calibration                        'Y' Not Used\n");
            cliPrint("'z' ADC Values                             'Z' Not Used\n");
            cliPrint("                                           '?' Command Summary\n");
            cliPrint("\n");

            cliQuery = 'x';
            cliBusy = false;
            break;

            ///////////////////////////////
    }
}

///////////////////////////////////////////////////////////////////////////////
