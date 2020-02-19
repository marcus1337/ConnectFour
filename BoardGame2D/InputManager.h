#pragma once
#include "SDL.h"
#include <tuple>

#include <iostream>

class InputManager{
public:
    SDL_Event ev;
    bool shutdownGame = false;
    bool resizedWindow = false;
    std::pair<int, int> mouseDown, mouseUp, mousePosition;
    bool wasMouseLeftDown = false;
    bool wasMouseLeftUp = false;

    InputManager() {
        mouseDown = std::make_pair(-1, -1);
        mouseUp = std::make_pair(-1, -1);
        mousePosition = std::make_pair(-1, -1);
    }

    void resetStates() {
        resetMouseClickStateIfDoneClicking();
    }

    void resetMouseClickStateIfDoneClicking() {
        if (wasMouseLeftUp) {
            wasMouseLeftDown = false;
            wasMouseLeftUp = false;
        }
    }

    void handleMouseEvents() {
        if (ev.type == SDL_MOUSEMOTION) {
            mousePosition = std::make_pair(ev.button.x, ev.button.y);
        }

        if (ev.type == SDL_MOUSEBUTTONDOWN) {
            if (ev.button.button == SDL_BUTTON_LEFT) {
                mouseDown = std::make_pair(ev.button.x, ev.button.y);
                wasMouseLeftDown = true;
            }
        }
        if (ev.type == SDL_MOUSEBUTTONUP) {
            if (ev.button.button == SDL_BUTTON_LEFT) {
                mouseUp = std::make_pair(ev.button.x, ev.button.y);
                wasMouseLeftUp = true;
            }
        }
    }

    void processInput() {
        using namespace std;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                shutdownGame = true;
            }
            if (ev.type == SDL_KEYDOWN) {
                if (ev.key.keysym.sym == SDLK_ESCAPE) {

                }
            }
            if (ev.type == SDL_WINDOWEVENT) {
                if (ev.window.event == SDL_WINDOWEVENT_RESIZED) {
                    resizedWindow = true;
                }
            }
            handleMouseEvents();
        }
    }


};