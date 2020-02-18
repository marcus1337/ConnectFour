#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include "ShapeFuncs.h"
#include "Windows.h"

class Text {
public:
    Text(TTF_Font* _ttf, SDL_Texture* _message) : ttf(_ttf), message(_message) {
        colorcode = { 255, 255, 255, 255 };
        rect = { 0,0,100,100 };
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

    SDL_Texture* makeTextTexture(std::string _fontPath, std::string _msg, TTF_Font* _ttf, SDL_Renderer* renderer, SDL_Color _colorcode) {
       // ttf = TTF_OpenFont(_fontPath.c_str(), _fSize);
        SDL_Texture* tmpMessage = nullptr;
        SDL_Surface* surfaceMessage = TTF_RenderText_Blended(_ttf, _msg.c_str(), _colorcode);
        ShapeFuncs::setSurfaceAlpha(surfaceMessage, _colorcode.a);
        tmpMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
        SDL_FreeSurface(surfaceMessage);
        return tmpMessage;
    }

    /*void init2(SDL_Renderer* _renderer, int _fSize, std::string _fontPath, const std::string &_msg, int _maxWidth) {
        ttf = TTF_OpenFont(_fontPath.c_str(), _fSize);
        SDL_Surface* surf = TTF_RenderText_Blended_Wrapped(ttf, _msg.c_str(), colorcode, _maxWidth);
        ShapeFuncs::setSurfaceAlpha(surf, colorcode.a);
        message = SDL_CreateTextureFromSurface(_renderer, surf);
        SDL_FreeSurface(surf);
        SDL_QueryTexture(message, nullptr, nullptr, &rect.w, &rect.h);
    }*/

    /*void reInit2(SDL_Renderer* _renderer, const std::string &_msg, int _maxWidth) {
        SDL_Surface* surf = TTF_RenderText_Blended_Wrapped(ttf, _msg.c_str(), colorcode, _maxWidth);
        if (!surf)
            return;
        ShapeFuncs::setSurfaceAlpha(surf, colorcode.a);
        SDL_Texture* tmp = SDL_CreateTextureFromSurface(_renderer, surf);
        SDL_FreeSurface(surf);
        SDL_QueryTexture(message, nullptr, nullptr, &rect.w, &rect.h);
        if (tmp) {
            SDL_DestroyTexture(message);
            message = tmp;
        }
    }*/

    void setRect(SDL_Rect _rect) {
        rect = _rect;
    }

    void render(SDL_Renderer* renderer) {
        SDL_RenderCopy(renderer, message, NULL, &rect);
    }

private:
    SDL_Rect rect;
    SDL_Texture* message;
    SDL_Color colorcode;
    TTF_Font* ttf;

};