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

#include "ConnectServerPage.h"

public class ServerPage : public Page {
public:

    std::vector<Button> gameButtons;
    std::vector<Button> buttons;
    std::vector<Image> images;
    UIText text;

    GameControl gameController;
    gcroot<Lobby^> lobby;

    ServerPage(ShapeHandler& _shapeHandler, IOStuff& _iostuff, ConnectServerPage* connServPage) : Page(_shapeHandler, _iostuff) {
        state = iostuff.loadLuaFile(FileNames::localPVPLua);
        lobby = connServPage->lobby;
        std::cout << "TEST START" << std::endl;
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

        Image latestBrick = gameController.getLastBrick(renderer, shapeHandler);
        latestBrick.draw(renderer);

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
        CppToLua::initLuaFile(state, iostuff.getLuaFilePath() + FileNames::localPVPLua, miscInfo);

        buttons = CppToLua::getButtonsFromLua(state, shapeHandler, renderer);
        gameButtons = CppToLua::getButtonsFromLua(state, shapeHandler, renderer, "getGameButtons");
        gameController.setGameControllerDimensions(gameButtons);

        images = CppToLua::getImagesFromLua(state, shapeHandler, renderer);

        for (auto& button : buttons) {
            if (button.getText().size() > 0)
                button.initBtnText(shapeHandler.getTextTexture(renderer, button.getText(), SDL_Color{ 255,255,0,255 }, "arial.ttf", 50));
        }
    }

    virtual void updateContent(MiscInfo miscInfo, InputManager& inputmanager, SDL_Renderer* renderer) {
        if (iostuff.isFileModified(FileNames::localPVPLua) || inputmanager.resizedWindow)
        {
            setupContentFromLua(renderer, miscInfo);
        }
        gameController.miscInfo = miscInfo;
        if (!gameController.game->isHumanTurn()) {
            int aimove = gameController.game->getAIMove();
            if (gameController.doneAnimatingBrickDrop())
                gameController.tryPlace(aimove);
        }

    }

    virtual void onStart(SDL_Renderer* renderer, MiscInfo miscInfo) {
        setupContentFromLua(renderer, miscInfo);
    }


    int getSelectedColumn(InputManager& inputs) {
        int mx = inputs.mousePosition.first;
        int my = inputs.mousePosition.second;
        for (auto& button : gameButtons) {
            if (button.insideShape(mx, my))
                return button.value;
        }
        return -1;
    }

    void handleGameButtonClicks(InputManager& inputs) {

        int selectedCol = getSelectedColumn(inputs);

        for (auto& button : gameButtons) {
            if (inputs.wasMouseLeftDown) {
                button.clickPress(inputs.mouseDown.first, inputs.mouseDown.second);
            }
            if (inputs.wasMouseLeftUp) {
                button.clickRelease(inputs.mouseUp.first, inputs.mouseUp.second);
            }
            if (button.isClicked()) {
                if (gameController.doneAnimatingBrickDrop() && gameController.game->isHumanTurn())
                    gameController.tryPlace(button.value);
            }
            button.setHover(true);
            button.setSelected(false);
            if (selectedCol == button.value)
                button.setSelected(true);
        }
    }


};