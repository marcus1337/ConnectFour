#pragma once
#include "Page.h"
#include "Button.h"

class MainMenu : public Page {
public:
    std::vector<Button> buttons;

    MainMenu(ShapeHandler& _shapeHandler, IOStuff& _iostuff) : Page(_shapeHandler, _iostuff) {
        state = iostuff.loadLuaFile(FileNames::mainMenuLua);
    };

    virtual void draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 80, 0, 255);
        SDL_RenderClear(renderer);
        for (auto& button : buttons) {
            button.render(renderer);
        }
    }

    virtual void updateContent(MiscInfo miscInfo, InputManager& inputmanager) {
        if (iostuff.isFileModified(FileNames::mainMenuLua) || inputmanager.resizedWindow)
        {
            inputmanager.resizedWindow = false;
            CppToLua::initLuaFile(state, iostuff.getLuaFilePath() + FileNames::mainMenuLua, miscInfo);
            buttons = CppToLua::getButtonsFromLua(state, shapeHandler);
        }
    }

};