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
#define EMULATOR_MAIN
#include "core.h"
#include <Arduino.h>
#include <avr/io.h>
#include "system.h"

extern void setup();
extern void loop();

int32_t         g_powerVoltage = VTOI(5.0);

void delay(unsigned long x)
{
   while (x--)
   {
       SDL_Delay(1);
       if (coreIsStopped()) break;
   }
}

void delayMicroseconds(unsigned int us)
{
   usleep(us);
}

unsigned long millis(void)
{
   struct timespec ts;
   clock_gettime(CLOCK_MONOTONIC, &ts);
   return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

unsigned long micros(void)
{
   struct timespec ts;
   clock_gettime(CLOCK_MONOTONIC, &ts);
   return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}


long random(long v)
{
    return rand() % v;
}

void randomSeed(unsigned long v)
{
}

long random(long min, long max)
{
    return rand() % (max - min + 1) + min;
}


void boardConfig() __attribute__((weak));
void boardConfig()
{
}


int main (int argc, char** argv)
{
    initMcu();
    boardConfig();
    coreInit();
    setup();
    while (!coreIsStopped())
    {
        loop();
        SDL_Delay(0);
    }
    coreStop();
    return 0;
}

