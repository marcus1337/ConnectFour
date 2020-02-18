#pragma once
#include "SDL.h"
#include <string>

class Button {
public:

    Button();

    void setHover(bool _hoverOn) {
        hoverOn = _hoverOn;
    }

    void setImage(SDL_Texture* txt1, SDL_Texture* txt2) {
        textureUp = txt1;
        textureDown = txt2;
    }

    void swapImages() {
        SDL_Texture* tmp = textureUp;
        textureUp = textureDown;
        textureDown = tmp;
    }

    SDL_Rect getHoverRect() {
        SDL_Rect hovRect = rect;
        hovRect.x -= 10;
        hovRect.w += 20;
        hovRect.y -= 10;
        hovRect.h += 20;
        return hovRect;
    }

    void render(SDL_Renderer* renderer) {

        bool tmpPress = pressed;
        if (forcePress)
            tmpPress = !pressed;

        if (selected && hoverOn) {
            SDL_Rect hovRect = getHoverRect();
            SDL_SetRenderDrawColor(renderer, 200, 100, 40, 255);
            SDL_RenderFillRect(renderer, &hovRect);
        }

        if (!tmpPress)
            SDL_RenderCopy(renderer, textureUp, NULL, &rect);
        else
            SDL_RenderCopy(renderer, textureDown, NULL, &rect);
    }

    void setRect(SDL_Rect _rect) {
        rect = _rect;
    }

    SDL_Rect getRect() {
        return rect;
    }

    void setXY(int x, int y) {
        rect.x = x;
        rect.y = y;
    }

    void setActive(bool _activated) {
        activated = _activated;
    }

    bool isActive() {
        return activated;
    }

    bool insideShape(int x, int y) {
        return x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h;
    }

    void clickPress(int x, int y) {
        wasClicked = false;
        if (insideShape(x,y)) {
            pressed = true;
        }
    }

    void clickRelease(int x, int y) {
        pressed = false;
        if (insideShape(x, y)) {
            wasClicked = true;
        }
    }

    void hover(int x, int y) {
        if (insideShape(x, y)) {
            selected = true;
        }
        else {
            selected = false;
        }
    }

    void setPressed(bool _press) {
        forcePress = _press;
    }

    bool isPressed() {
        return forcePress;
    }

    void clearClick() {
        wasClicked = false;
    }

    bool isClicked() {
        bool _tmp = wasClicked;
        wasClicked = false;
        return _tmp;
    }

    void setText(std::string _title) {
        title = _title;
    }

private:
    SDL_Texture* textureDown;
    SDL_Texture* textureUp;
    SDL_Rect rect;
    bool selected;
    bool pressed;
    bool forcePress;
    bool wasClicked;
    bool activated;
    bool hoverOn;
    std::string title;

};