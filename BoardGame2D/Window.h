#pragma once
#include "SDL.h"
#include "MainMenu.h"
#include <iostream>

class Window {
public:

    SDL_Window *window;
    SDL_Renderer *renderer;
    Page* page = nullptr;

    void changePage(Page* newPage) {
        delete page;
        page = newPage;
    }

    Window() {
        SDL_Init(SDL_INIT_EVERYTHING);
        window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetWindowResizable(window, SDL_TRUE);
    }

    ~Window() {
        delete page;
    }


    


};