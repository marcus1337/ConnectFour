#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <map>
#include <tuple>
#include <array>

class ShapeHandler {
private:
    typedef std::pair<std::string, int> fontKey;
    typedef std::pair<std::string, std::array<Uint8,4>> MsgAndColor;
    typedef std::pair<fontKey, MsgAndColor> textKey;

    std::map<fontKey, TTF_Font*> fonts;
    std::map<textKey, SDL_Texture*> textTextures;
    std::map<std::string, SDL_Texture*> imageTextures;
    std::string rpath;
    std::string fontPath;

public:
    SDL_Texture* button1_pressed;
    SDL_Texture* button1;
    SDL_Texture* background1;

    ShapeHandler(std::string exePath);
    void init(SDL_Renderer* _renderer);
    void deleteVariables();

    TTF_Font* getFont(std::string fontName ,int _fSize = 24);
    SDL_Texture* getTextTexture(SDL_Renderer* renderer, std::string txt, SDL_Color _colorcode, std::string fontName, int _fSize = 24);
    SDL_Texture* getImageTexture(SDL_Renderer* renderer, std::string imageName);

};