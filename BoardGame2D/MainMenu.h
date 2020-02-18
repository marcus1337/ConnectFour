#pragma once
#include "Page.h"
#include "Button.h"
#include "Text.h"

class MainMenu : public Page {
public:
    std::vector<Button> buttons;
    Text text;

    MainMenu(ShapeHandler& _shapeHandler, IOStuff& _iostuff) : Page(_shapeHandler, _iostuff) {
        state = iostuff.loadLuaFile(FileNames::mainMenuLua);
    };

    virtual void draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 80, 0, 255);
        SDL_RenderClear(renderer);

        //text.setTexture(shapeHandler.getTextTexture(renderer, "Hello World 123", SDL_Color{ 0,255,255,255 }, "calibrib.ttf",100));

        for (auto& button : buttons) {
            button.render(renderer);
        }
    }

    virtual void updateContent(MiscInfo miscInfo, InputManager& inputmanager, SDL_Renderer* renderer) {
        if (iostuff.isFileModified(FileNames::mainMenuLua) || inputmanager.resizedWindow)
        {
            inputmanager.resizedWindow = false;
            CppToLua::initLuaFile(state, iostuff.getLuaFilePath() + FileNames::mainMenuLua, miscInfo);
            buttons = CppToLua::getButtonsFromLua(state, shapeHandler);

            for (auto& button : buttons) {
                if (button.getText().size() > 0)
                    button.initBtnText(shapeHandler.getTextTexture(renderer, button.getText(), SDL_Color{ 255,255,0,255 }, "arial.ttf", 50));
            }

        }
    }

};