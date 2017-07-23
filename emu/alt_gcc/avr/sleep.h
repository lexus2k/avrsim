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

#ifndef _AVR_SLEEP_H_
#define _AVR_SLEEP_H_ 1

#include <avr/io.h>
#include <stdint.h>

#define set_sleep_mode(mode)
#define sleep_enable()
#define sleep_disable()
#define sleep_cpu()
#define sleep_mode() \
do {                 \
    sleep_enable();  \
    sleep_cpu();     \
    sleep_disable(); \
} while (0)

#endif /* _AVR_SLEEP_H_ */
