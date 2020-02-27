#pragma once
#include "Page.h"
#include "Button.h"
#include "UIText.h"
#include <vector>
#include "Image.h"
#include "IOStuff.h"
#include "EnumManager.h"
#include <algorithm>

#include "GameControl.h"

public class GenericPage : public Page {
public:

    std::vector<Button> gameButtons;
    std::vector<Button> buttons;
    std::vector<Image> images;
    GameControl gameController;
    std::string luaScriptName;

    GenericPage(ShapeHandler& _shapeHandler, IOStuff& _iostuff, std::string _luaScriptName) : 
        Page(_shapeHandler, _iostuff), luaScriptName(_luaScriptName) {
        state = iostuff.loadLuaFile(luaScriptName);
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

        auto bricks = gameController.getPlacedBricksImages(renderer, shapeHandler);
        for (auto& b : bricks) {
            b.draw(renderer);
        }

        for (auto& button : gameButtons) {
            button.render(renderer);
        }
    }

    PageState handleButtonClicks(InputManager& inputs) {
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
        if (pageChange == PageState::REMATCH)
            gameController.newGame();

        return pageChange;
    }

    virtual PageState process(MiscInfo miscInfo, InputManager& inputs) {
        PageState pageChange = handleButtonClicks(inputs);
        handleGameButtonClicks(inputs);
        return pageChange;
    }

    void setupContentFromLua(SDL_Renderer* renderer, MiscInfo miscInfo) {
        CppToLua::initLuaFile(state, iostuff.getLuaFilePath() + FileNames::utilityFile, miscInfo);
        CppToLua::initLuaFile(state, iostuff.getLuaFilePath() + luaScriptName, miscInfo);

        buttons = CppToLua::getButtonsFromLua(state, shapeHandler, renderer);
        gameButtons = CppToLua::getButtonsFromLua(state, shapeHandler, renderer, "getGameButtons");
        gameController.setGameControllerDimensions(gameButtons);
        images = CppToLua::getImagesFromLua(state, shapeHandler, renderer);

        for (auto& button : buttons) {
            if (button.getText().size() > 0)
                button.initBtnText(shapeHandler.getTextTexture(renderer, button.getText(), SDL_Color{ 255,255,0,255 }, "arial.ttf", 50));
        }
    }

    virtual void updateGame(MiscInfo miscInfo, InputManager& inputmanager, SDL_Renderer* renderer) {}

    void updatePage(MiscInfo miscInfo, InputManager& inputmanager, SDL_Renderer* renderer){
        if (iostuff.isFileModified(luaScriptName) || inputmanager.resizedWindow)
        {
            setupContentFromLua(renderer, miscInfo);
        }
        gameController.miscInfo = miscInfo;
    }

    virtual void updateContent(MiscInfo miscInfo, InputManager& inputmanager, SDL_Renderer* renderer) {
        updatePage(miscInfo, inputmanager, renderer);
        updateGame(miscInfo, inputmanager, renderer);
    }

    virtual void onStart(SDL_Renderer* renderer, MiscInfo miscInfo) {
        setupContentFromLua(renderer, miscInfo);
    }

    void handleGameButtonState(InputManager& inputs, Button& button, int selectedCol) {
        if (inputs.wasMouseLeftDown) {
            button.clickPress(inputs.mouseDown.first, inputs.mouseDown.second);
        }
        if (inputs.wasMouseLeftUp) {
            button.clickRelease(inputs.mouseUp.first, inputs.mouseUp.second);
        }
        button.setHover(true);
        button.setSelected(false);
        if (selectedCol == button.value)
            button.setSelected(true);
    }

    virtual void handleGameButtonClick(Button& button) {};

    void handleGameButtonClicks(InputManager& inputs) {
        int selectedCol = gameController.getSelectedColumn(inputs.mousePosition.first, inputs.mousePosition.second, gameButtons);
        for (auto& button : gameButtons) {
            handleGameButtonState(inputs, button, selectedCol);
            if (button.isClicked()) {
                handleGameButtonClick(button);
            }
        }
    }


};