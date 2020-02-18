#pragma once
#include "SDL.h"

class InputManager{
public:
    SDL_Event ev;
    bool shutdownGame = false;
    bool resizedWindow = false;

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
        }
    }


};