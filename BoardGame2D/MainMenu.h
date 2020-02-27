#pragma once
#include "Page.h"
#include "Button.h"
#include "UIText.h"

class MainMenu : public Page {
public:
    std::vector<Button> buttons;
    std::vector<Image> images;

    MainMenu(ShapeHandler& _shapeHandler, IOStuff& _iostuff) : Page(_shapeHandler, _iostuff) {
        state = iostuff.loadLuaFile(FileNames::mainMenuLua);
    };

    virtual void draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 80, 0, 255);
        SDL_RenderClear(renderer);

        for (auto& image : images) {
            image.draw(renderer);
        }

        for (auto& button : buttons) {
            button.render(renderer);
        }
    }

    virtual PageState process(MiscInfo miscInfo, InputManager& inputs) {
        PageState pageChange = PageState::NONE;
        for (auto& button : buttons) {
            if (inputs.wasMouseLeftDown) {
                button.clickPress(inputs.mouseDown.first, inputs.mouseDown.second);
            }
            if (inputs.wasMouseLeftUp) {
                button.clickRelease(inputs.mouseUp.first, inputs.mouseUp.second);
            }
            if (button.isClicked()) {
                pageChange = (PageState)button.value;
            }
        }

        return pageChange;
    }

    void setupContentFromLua(SDL_Renderer* renderer, MiscInfo miscInfo) {
        CppToLua::initLuaFile(state, iostuff.getLuaFilePath() + FileNames::utilityFile, miscInfo);
        CppToLua::initLuaFile(state, iostuff.getLuaFilePath() + FileNames::mainMenuLua, miscInfo);
        buttons = CppToLua::getButtonsFromLua(state, shapeHandler, renderer);
        images = CppToLua::getImagesFromLua(state, shapeHandler, renderer);

        for (auto& button : buttons) {
            if (button.getText().size() > 0)
                button.initBtnText(shapeHandler.getTextTexture(renderer, button.getText(), SDL_Color{ 200,200,0,255 }, "arial.ttf", 50));
        }
    }

    virtual void updateContent(MiscInfo miscInfo, InputManager& inputmanager, SDL_Renderer* renderer) {
        if (iostuff.isFileModified(FileNames::mainMenuLua) || inputmanager.resizedWindow)
        {
            inputmanager.resizedWindow = false;
            setupContentFromLua(renderer, miscInfo);

        }
    }

    virtual void onStart(SDL_Renderer* renderer, MiscInfo miscInfo) {
        setupContentFromLua(renderer, miscInfo);
    }

};