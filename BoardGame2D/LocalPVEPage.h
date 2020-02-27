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
#include "GenericPage.h"

public class LocalPVEPage : public GenericPage {
public:

    LocalPVEPage(ShapeHandler& _shapeHandler, IOStuff& _iostuff) : GenericPage(_shapeHandler, _iostuff, FileNames::localPVPLua) {

    };

    virtual void handleGameButtonClick(Button& button) {
        if (gameController.doneAnimatingBrickDrop() && gameController.game->isHumanTurn())
            gameController.tryPlace(button.value);
    }

    virtual void updateGame(MiscInfo miscInfo, InputManager& inputmanager, SDL_Renderer* renderer) {
        if (!gameController.game->isHumanTurn()) {
            int aimove = gameController.game->getAIMove();
            if (gameController.doneAnimatingBrickDrop())
                gameController.tryPlace(aimove);
        }
    }

};