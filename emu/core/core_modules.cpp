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

#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <list>
#include <SDL2/SDL.h>
#include "core.h"
#include "module.h"
#include "system.h"
#include <avr/io.h>

static std::list<CModule *> s_modules;


std::list<CModule *> * coreGetModules()
{
    return &s_modules;
}

void coreRegisterModule(CModule *module)
{
    s_modules.push_back(module);
}

