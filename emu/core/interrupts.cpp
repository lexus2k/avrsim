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

#include <avr/io.h>
#include <Arduino.h>
#include "core.h"

void __disableInterrupts()
{
    coreLock();
    SREG |= (uint8_t)(1<<SREG_I);
    coreUnlock();
}

void __enableInterrupts()
{
    coreLock();
    SREG &= (uint8_t)~(1<<SREG_I);
    coreUnlock();
}




void attachInterrupt(uint8_t interrupt, __int_handler handler, int mode)
{
    coreLock();
    g_vectors[interrupt + 1] = *handler;
    switch (interrupt)
    {
#define GIMSK GIMSK
#define MCUCR MCUCR
    case 0:
    #if defined(MCUCR) && defined(ISC00) && defined(GIMSK)
      MCUCR = (MCUCR & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
      GIMSK |= (1 << INT0);
    #else
      #error attachInterrupt not finished for this CPU (case 0)
    #endif
      break;

    case 1:
    #if defined(MCUCR) && defined(ISC10) && defined(GIMSK) && defined(GIMSK)
      MCUCR = (MCUCR & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
      GIMSK |= (1 << INT1);
    #else
//      #warning attachInterrupt may need some more work for this cpu (case 1)
    #endif
      break;
   }
   coreUnlock();
}

