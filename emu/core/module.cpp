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
#include "module.h"
#include "core_modules.h"
#include "system.h"

CModule::CModule(int x, int y, int width, int height)
{
    m_posX = x;
    m_posY = y;
    m_width = width;
    m_height = height;
    coreRegisterModule(this);
}


CModule::~CModule()
{
}


bool  CModule::OnEvent(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        return OnKeyDown(event.key.keysym.scancode);
    }
    else if (event.type == SDL_KEYUP)
    {
        return OnKeyUp(event.key.keysym.scancode);
    }
    return false;
}


bool  CModule::OnKeyDown(SDL_Scancode code)
{
    return false;
}


bool  CModule::OnKeyUp(SDL_Scancode code)
{
    return false;
}


void CModule::OnDraw(SDL_Renderer * renderer)
{
}


int32_t CModule::GetSupplyVoltage()
{
    return g_powerVoltage;
}

