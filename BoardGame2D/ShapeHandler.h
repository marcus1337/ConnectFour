#pragma once
#include "SDL.h"
#include <string>

class ShapeHandler {
public:

    std::string rpath;
    SDL_Texture* button1_pressed;
    SDL_Texture* button1;
    SDL_Texture* background1;

    ShapeHandler(std::string exePath);
    void init(SDL_Renderer* _renderer);
    void deleteVariables();

private:

};