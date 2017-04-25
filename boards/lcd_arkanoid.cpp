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

#include <modules.h>
#include "Arduino.h"

SSD1306_I2C display(0, 0);
DIGITAL_BUTTON rightButton(200, 160, SDL_SCANCODE_M);
DIGITAL_BUTTON leftButton(10, 160, SDL_SCANCODE_Z);

void boardConfig()
{
    display.BindPins(MCU_PIN3, MCU_PIN2);
    rightButton.BindPins(MCU_PIN7);
    leftButton.BindPins(MCU_PIN5);
}

