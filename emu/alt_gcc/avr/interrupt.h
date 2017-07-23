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

#ifndef _AVR_INTERRUPT_H_
#define _AVR_INTERRUPT_H_

#include <avr/io.h>
#include <core/interrupts.h>

#ifndef _VECTOR
#define _VECTOR(N) __vector_ ## N
#endif

#define sei() __enableInterrupts();

#define cli() __disableInterrupts();

#  define ISR(vector, ...)   void vector ()

#  define SIGNAL(vector)     void SIGNAL_function(uint8_t vector)
#  define EMPTY_INTERRUPT(vector)  void ISR_function(uint8_t vector) {}
#  define reti()  return
#  define ISR_BLOCK
#  define ISR_NOBLOCK
#  define ISR_NAKED
#  define ISR_ALIASOF(v)

#endif
