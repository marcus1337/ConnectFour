#pragma once

#include "GenericPage.h"
#include "ConnectServerPage.h"

public class ServerPage : public GenericPage {
public:

    gcroot<Lobby^> lobby;

    ServerPage(ShapeHandler& _shapeHandler, IOStuff& _iostuff, ConnectServerPage* connServPage) : GenericPage(_shapeHandler, _iostuff, FileNames::localPVPLua) {
        lobby = connServPage->lobby;
        std::cout << "TEST START" << std::endl;
    };

    virtual void handleGameButtonClick(Button& button) {
        if (gameController.doneAnimatingBrickDrop())
            gameController.tryPlace(button.value);
    }

    virtual void updateGame(MiscInfo miscInfo, InputManager& inputmanager, SDL_Renderer* renderer) {
        
    }


};