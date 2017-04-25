/*
    Copyright (C) 2016-2017 Alexey Dynda

    This file is part of AVR Simulator project.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include "core.h"
#include <Arduino.h>
#include <avr/io.h>
#include "system.h"


void pinMode(uint8_t pin, uint8_t mode)
{
    uint8_t port = digitalPinToPort(pin);
    uint8_t mask = digitalPinToBitMask(pin);
    if ((port == 0xFF) || (mask == 0xFF))
    {
        return;
    }
    if (mode == INPUT)
    {
        portModeRegister(port) &= ~mask;
        portOutputRegister(port) &= ~mask;
    }
    if (mode == INPUT_PULLUP)
    {
        portModeRegister(port) &= ~mask;
        portOutputRegister(port) |= mask;
    }
    if (mode == OUTPUT)
    {
        portModeRegister(port) |= mask;
    }
}

void digitalWrite(uint8_t pin, uint8_t mode)
{
    uint8_t port = digitalPinToPort(pin);
    uint8_t mask = digitalPinToBitMask(pin);
    if ((port == 0xFF) || (mask == 0xFF))
    {
        return;
    }
    if (mode == HIGH)
        portOutputRegister(port) |= mask;
    if (mode == LOW)
        portOutputRegister(port) &= ~mask;
}


int digitalRead(uint8_t pin)
{
    uint8_t port = digitalPinToPort(pin);
    uint8_t mask = digitalPinToBitMask(pin);
    if ((port == 0xFF) || (mask == 0xFF))
    {
        return LOW;
    }
    if (portInputRegister(port).Get() & mask)
    {
        return HIGH;
    }
    return LOW;
}

int analogRead(uint8_t)
{
    return 0;
}

void analogReference(uint8_t mode)
{
}

void analogWrite(uint8_t, int)
{
}


unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout);


