#pragma once
#include "SDL.h"
#include <string>
#include "Text.h"
#include <iostream>

class Button {
public:

    Button();
    Text btnText;

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

        if (title.size() > 0) {
            btnText.draw(renderer);
        }
    }

    void adjustTextRectSize(SDL_Texture* txtTexture) {
        auto tmpRect = getRect();
        int maxW = (int)(tmpRect.w*1.8f);
        tmpRect.h -= (int)tmpRect.h / 2.0f;
        int w, h;
        SDL_QueryTexture(txtTexture, NULL, NULL, &w, &h);
        if (w < maxW && maxW != 0 ) {
            float diffWPercent = 1.0f - ((float)w / maxW);
            tmpRect.w -= (int)((diffWPercent * maxW) / 2);
        }

        int minSpacingW = getRect().w / 8;
        int currentSpacingW = (getRect().w - tmpRect.w)/2;
        if (minSpacingW > currentSpacingW) {
            tmpRect.w -= (minSpacingW - currentSpacingW)*2;
        }
        
        btnText.setRect(tmpRect);
    }

    void adjustTextRectPosition() {
        auto tmpRectButton = getRect();
        auto tmpRectText = btnText.getRect();
        int yDiff = tmpRectButton.h - tmpRectText.h;
        int xDiff = tmpRectButton.w - tmpRectText.w;
        tmpRectText.y += yDiff / 2;
        tmpRectText.x += xDiff / 2;
        btnText.setRect(tmpRectText);
    }

    void initBtnText(SDL_Texture* txtTexture) {
        btnText.setTexture(txtTexture);
        adjustTextRectSize(txtTexture);
        adjustTextRectPosition();

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
        return x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h;
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

    std::string getText() {
        return title;
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