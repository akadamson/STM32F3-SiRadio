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
// Constrain
///////////////////////////////////////////////////////////////////////////////

float constrain(float input, float minValue, float maxValue)
{
    if (input < minValue)
        return minValue;
    else if (input > maxValue)
        return maxValue;
    else
        return input;
}

/*
 sbrk
 Increase program data space.
 Malloc and related functions depend on this
 */
#if 0
caddr_t _sbrk(int incr)
{
    extern char _ebss; // Defined by the linker
    static char *heap_end;
    char *prev_heap_end;

    char *stack;

    if (heap_end == 0)
        heap_end = &_ebss;

    prev_heap_end = heap_end;

    stack = (char *) __get_MSP();

    if (heap_end + incr >  stack)
    {
        errno = ENOMEM;
        return (caddr_t) - 1;
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;
}
#endif
////////////////////////////////////////////////////////////////////////////////
// String to Float Conversion
///////////////////////////////////////////////////////////////////////////////

// Simple and fast atof (ascii to float) function.
//
// - Executes about 5x faster than standard MSCRT library atof().
// - An attractive alternative if the number of calls is in the millions.
// - Assumes input is a proper integer, fraction, or scientific format.
// - Matches library atof() to 15 digits (except at extreme exponents).
// - Follows atof() precedent of essentially no error checking.
//
// 09-May-2009 Tom Van Baak (tvb) www.LeapSecond.com
//

#define white_space(c) ((c) == ' ' || (c) == '\t')
#define valid_digit(c) ((c) >= '0' && (c) <= '9')

float stringToFloat(const char *p)
{
    int frac = 0;
    double sign, value, scale;

    // Skip leading white space, if any.

    while (white_space(*p))
    {
        p += 1;
    }

    // Get sign, if any.

    sign = 1.0;

    if (*p == '-')
    {
        sign = -1.0;
        p += 1;

    }
    else if (*p == '+')
    {
        p += 1;
    }

    // Get digits before decimal point or exponent, if any.

    value = 0.0;

    while (valid_digit(*p))
    {
        value = value * 10.0 + (*p - '0');
        p += 1;
    }

    // Get digits after decimal point, if any.

    if (*p == '.')
    {
        double pow10 = 10.0;
        p += 1;

        while (valid_digit(*p))
        {
            value += (*p - '0') / pow10;
            pow10 *= 10.0;
            p += 1;
        }
    }

    // Handle exponent, if any.

    scale = 1.0;

    if ((*p == 'e') || (*p == 'E'))
    {
        unsigned int expon;
        p += 1;

        // Get sign of exponent, if any.

        frac = 0;

        if (*p == '-')
        {
            frac = 1;
            p += 1;

        }
        else if (*p == '+')
        {
            p += 1;
        }

        // Get digits of exponent, if any.

        expon = 0;

        while (valid_digit(*p))
        {
            expon = expon * 10 + (*p - '0');
            p += 1;
        }

        if (expon > 308) expon = 308;

        // Calculate scaling factor.

        while (expon >= 50)
        {
            scale *= 1E50;
            expon -= 50;
        }

        while (expon >=  8)
        {
            scale *= 1E8;
            expon -=  8;
        }

        while (expon >   0)
        {
            scale *= 10.0;
            expon -=  1;
        }
    }

    // Return signed and scaled floating point result.

    return sign * (frac ? (value / scale) : (value * scale));
}

///////////////////////////////////////////////////////////////////////////////
