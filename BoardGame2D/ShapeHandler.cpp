#include "ShapeHandler.h"
#include "ShapeFuncs.h"
#include "Utils.h"

ShapeHandler::ShapeHandler(std::string exePath) {
    rpath = exePath + "res\\";
    fontPath = exePath + "res\\fonts\\";
}

void ShapeHandler::init(SDL_Renderer* _renderer) {
    button1 = ShapeFuncs::textureFromPath(_renderer, rpath + "button1.png");
    button1_pressed = ShapeFuncs::textureFromPath(_renderer, rpath + "button1_pressed.png");
    // background1 = textureFromPath(_renderer, rpath + "background1.png");
}

void ShapeHandler::deleteVariables() {
    SDL_DestroyTexture(button1_pressed);
    SDL_DestroyTexture(button1);
    SDL_DestroyTexture(background1);

    for (auto const&[key, val] : fonts)
        TTF_CloseFont(val);
    for (auto const&[key, val] : textTextures)
        SDL_DestroyTexture(val);
}

TTF_Font* ShapeHandler::getFont(std::string fontName, int _fSize) {
    fontKey key = std::make_pair(fontName, _fSize);
    if (Utils::mapContainsKey<fontKey, TTF_Font*>(fonts, key))
        return fonts[key];
    TTF_Font* font = nullptr;
    font = TTF_OpenFont((fontPath+fontName).c_str(), _fSize);
    fonts[key] = font;
    return font;
}

SDL_Texture* ShapeHandler::getTextTexture(SDL_Renderer* renderer, std::string txt, SDL_Color _colorcode, std::string fontName, int _fSize) {
    fontKey fontkey = std::make_pair(fontName, _fSize);
    MsgAndColor msgAndColor = std::make_pair(txt, std::array<Uint8, 4>{_colorcode.r, _colorcode.g, _colorcode.b, _colorcode.a});
    textKey key = std::make_pair(fontkey, msgAndColor);
    if(Utils::mapContainsKey< textKey, SDL_Texture*>(textTextures, key))
        return textTextures[key];
    SDL_Texture* textTexture = ShapeFuncs::makeTextTexture(renderer, txt, _colorcode, getFont(fontName, _fSize));
    textTextures[key] = textTexture;
    return textTexture;
}