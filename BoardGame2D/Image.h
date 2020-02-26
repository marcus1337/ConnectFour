#pragma once
#include "SDL.h"
#include <string>

#include <iostream>

class Image {
public:
    SDL_Texture* texture;
    SDL_Rect rect;
    std::string imageName;

    Image() {
    }

    void draw(SDL_Renderer* renderer) {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void setRect(SDL_Rect _rect) {
        rect = _rect;
    }

    SDL_Rect getRect() {
        return rect;
    }

    void setY(int y) {
        rect.y = y;
    }

    void setX(int x) {
        rect.x = x;
    }

    void setXY(int x, int y) {
        rect.x = x;
        rect.y = y;
    }

    void setWH(int w, int h) {
        rect.w = w;
        rect.h = h;
    }

};