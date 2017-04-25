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

#ifndef _MODULE_H_
#define _MODULE_H_

#include <stdint.h>
#include <SDL2/SDL.h>

class CModule
{
public:
    CModule(int x, int y, int width, int height);
    ~CModule();

    /* Returns voltage in internal units. Use ITOV macro */
    static int32_t        GetSupplyVoltage();
    virtual bool          OnEvent(SDL_Event &event);
    virtual bool          OnKeyDown(SDL_Scancode code);
    virtual bool          OnKeyUp(SDL_Scancode code);
    virtual void          OnDraw(SDL_Renderer * renderer);
protected:
    int  m_posX;
    int  m_posY;
    int  m_width;
    int  m_height;
};

#endif

