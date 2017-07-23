/*
    Copyright (C) 2017 Alexey Dynda

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
#include <SDL.h>
#include <core/core.h>
#include <board.h>

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

