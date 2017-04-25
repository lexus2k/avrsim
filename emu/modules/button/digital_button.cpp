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

#include "digital_button.h"
#include <core/system.h>

using namespace std::placeholders;


CDigitalButton::CDigitalButton(int x, int y, int scancode)
    :CModule(x,y,20,20)
    ,m_input(nullptr)
    ,m_scancode(scancode)
{
    m_pressed = false;
}

CDigitalButton::~CDigitalButton()
{
}

void CDigitalButton::BindPins(CMcuPin &input)
{
    m_input = &input;
}

bool CDigitalButton::OnEvent(SDL_Event &event)
{
    if (m_input != nullptr)
    {
        if ((event.type == SDL_KEYDOWN) && (event.key.keysym.scancode == m_scancode))
        {
            m_input->SetVoltage( GetSupplyVoltage() );
            m_pressed = true;
            return true;
        }
        else if ((event.type == SDL_KEYUP) && (event.key.keysym.scancode == m_scancode))
        {
            m_input->SetVoltage( 0 );
            m_pressed = false;
            return true;
        }
        else if (m_pressed)
        {
            m_input->SetVoltage( GetSupplyVoltage() );
        }
    }
    return false;
}


void CDigitalButton::OnDraw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor( renderer, 160, 160, 245, 255 );
    SDL_Rect r;
    r.x = m_posX;
    r.y = m_posY;
    r.w = m_width;
    r.h = m_height;
    SDL_RenderDrawRect( renderer, &r );
    r.x++;
    r.y++;
    r.w -= 2;
    r.h -= 2;
    if (m_pressed)
    {
        SDL_SetRenderDrawColor( renderer, 100, 100, 145, 255 );
    }
    else
    {
        SDL_SetRenderDrawColor( renderer, 20, 20, 20, 255 );
        SDL_RenderDrawRect( renderer, &r );
        r.x++;
        r.y++;
        r.w -= 2;
        r.h -= 2;
        SDL_SetRenderDrawColor( renderer, 160, 160, 245, 255 );
    }
    SDL_RenderFillRect( renderer, &r );
}

