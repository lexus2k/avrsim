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

#include "core_modules.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <list>
#include <SDL2/SDL.h>
#include "core.h"
#include "module.h"
#include "system.h"
#include <avr/io.h>

#define CANVAS_REFRESH_RATE  60

const int screenWidth = 320;
const int screenHeight = 240;

uint32_t milliseconds(void)
{
   struct timespec ts;
   clock_gettime(CLOCK_MONOTONIC, &ts);
   return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

static pthread_t s_thread;
static pthread_mutex_t s_mutex;
static bool s_stop;
static bool s_renderReady = false;

static void *coreMainThread(void *arg)
{
    while (!s_renderReady) { usleep(1); }
    while (!s_stop)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) s_stop = true;
        }
        else
        {
            event.type = SDL_USEREVENT;
            event.user.code = 0;
        }
//        if (SREG & (1<<SREG_I))
        coreLock();
        for (auto module: *coreGetModules())
        {
            if (module->OnEvent(event))
            {
                break;
            }
        }
        coreUnlock();
//        {
//            MCU_PIN7.SetVoltage(VTOI(5.0));
//            MCU_PIN7.SetVoltage(VTOI(0.0));
//        }
        usleep(1);
    }
    return nullptr;
}


static pthread_t s_rendererThread;

static void *coreRendererThread(void *arg)
{
    SDL_Window     *g_window = nullptr;
    SDL_Renderer   *g_renderer = nullptr;
    pthread_mutex_t s_sdlMutex;

    pthread_mutex_init(&s_sdlMutex, nullptr);
    SDL_Init(SDL_INIT_EVERYTHING);

    g_window = SDL_CreateWindow
    (
        "AVR SIMULATOR", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        screenWidth,
        screenHeight,
        SDL_WINDOW_SHOWN
    );

    g_renderer =  SDL_CreateRenderer( g_window, -1, SDL_RENDERER_ACCELERATED);

    // Set render color to black ( background will be rendered in this color )
    SDL_SetRenderDrawColor( g_renderer, 20, 20, 20, 255 );

    // Clear window
    SDL_RenderClear( g_renderer );

    // Render the rect to the screen
    SDL_RenderPresent(g_renderer);

    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = screenWidth;
    r.h = screenHeight;

    SDL_RenderFillRect( g_renderer, &r );

    s_renderReady = true;
    uint32_t lastRenderTs = milliseconds();
    while (!s_stop)
    {
        if (milliseconds() - lastRenderTs > (1000 / CANVAS_REFRESH_RATE))
        {
            for (auto module: *coreGetModules())
            {
                module->OnDraw(g_renderer);
            }
            SDL_RenderPresent(g_renderer);
            lastRenderTs = milliseconds();
        }
        usleep(5000);
    }

    SDL_DestroyWindow(g_window);
    SDL_Quit();
    pthread_mutex_destroy(&s_sdlMutex);
    return nullptr;
}




void coreInit()
{
    s_stop = false;
    pthread_mutex_init(&s_mutex, nullptr);
    pthread_create(&s_rendererThread, nullptr, &coreRendererThread, nullptr);
    pthread_create(&s_thread, nullptr, &coreMainThread, nullptr);
}

void coreStop()
{
    s_stop = true;
    pthread_join(s_thread, nullptr);
    pthread_join(s_rendererThread, nullptr);
    pthread_mutex_destroy(&s_mutex);
}


bool coreIsStopped()
{
    return s_stop;
}


void coreLock()
{
    pthread_mutex_lock(&s_mutex);
}


void coreUnlock()
{
    pthread_mutex_unlock(&s_mutex);
}


