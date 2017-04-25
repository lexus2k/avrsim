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


#ifndef _MODULE_DIGITAL_BUTTON_H_
#define _MODULE_DIGITAL_BUTTON_H_

#include <stdint.h>
#include <SDL2/SDL.h>
#include <core/mcupins.h>
#include <core/system.h>
#include <core/module.h>

#include <Arduino.h>

class CDigitalButton: public CModule
{
public:
    CDigitalButton(int x, int y, int scancode);
    ~CDigitalButton();

    void BindPins(CMcuPin &input);
    virtual bool          OnEvent(SDL_Event &event);
    virtual void OnDraw(SDL_Renderer *renderer);
private:
    CMcuPin  *m_input;
    int       m_scancode;
    bool      m_pressed;
};

// ----------------------------------------------------------------------------
#endif // _MODULE_DIGITAL_BUTTON_H_
