#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include "ShapeFuncs.h"
#include "Windows.h"

class Text {
public:
    Text() {
        colorcode = { 255, 255, 255, 255 };
        rect = { 0,0,100,100 };
    }

    void setTexture(SDL_Texture* _message) {
        message = _message;
    }

    SDL_Rect getRect() {
        return rect;
    }

    void setX(int _x) {
        rect.x = _x;
    }

    int getX() {
        return rect.x;
    }

    void setXY(int _x, int _y) {
        rect.x = _x;
        rect.y = _y;
    }

    int getY() {
        return rect.y;
    }

    int getWidth() {
        return rect.w;
    }

    int getHeight() {
        return rect.h;
    }

    void setY(int _y) {
        rect.y = _y;
    }

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) {
        colorcode = { r,g,b, a };
    }

    int getAlpha() {
        return colorcode.a;
    }

    void setAlpha(Uint8 _a) {
        colorcode.a = _a;
    }

    //SDL_Surface* surf = TTF_RenderText_Blended_Wrapped(ttf, _msg.c_str(), colorcode, _maxWidth);

    void setRect(SDL_Rect _rect) {
        rect = _rect;
    }

    void draw(SDL_Renderer* renderer) {
        if(message)
            SDL_RenderCopy(renderer, message, NULL, &rect);
    }

private:
    SDL_Rect rect;
    SDL_Texture* message = nullptr;
    SDL_Color colorcode;
};