#include "ShapeHandler.h"
#include "ShapeFuncs.h"

ShapeHandler::ShapeHandler(std::string exePath) {
    rpath = exePath + "res\\";
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
}