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

public class ConnectServerPage : public Page {
public:

    std::vector<Button> buttons;
    std::vector<Image> images;
    UIText text;

    gcroot<Lobby^> lobby;

    ConnectServerPage(ShapeHandler& _shapeHandler, IOStuff& _iostuff) : Page(_shapeHandler, _iostuff) {
        state = iostuff.loadLuaFile(FileNames::connectingLua);
        lobby = gcnew Lobby();
        lobby->hostLANAsync();
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

        if (!System::Object::ReferenceEquals(lobby->server, nullptr) && lobby->server->startedGame)
            pageChange = PageState::LANSERVER;

        return pageChange;
    }

    virtual PageState process(MiscInfo miscInfo, InputManager& inputs) {
        PageState pageChange = handleButtonClicks(inputs);

        return pageChange;
    }

    void setupContentFromLua(SDL_Renderer* renderer, MiscInfo miscInfo) {
        CppToLua::initLuaFile(state, iostuff.getLuaFilePath() + FileNames::utilityFile, miscInfo);
        CppToLua::initLuaFile(state, iostuff.getLuaFilePath() + FileNames::connectingLua, miscInfo);

        buttons = CppToLua::getButtonsFromLua(state, shapeHandler, renderer);
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
    }

    virtual void onStart(SDL_Renderer* renderer, MiscInfo miscInfo) {
        setupContentFromLua(renderer, miscInfo);
    }

};