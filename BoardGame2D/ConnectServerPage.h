#pragma once

#include "GenericPage.h"

public class ConnectServerPage : public GenericPage {
public:

    gcroot<Lobby^> lobby;

    ConnectServerPage(ShapeHandler& _shapeHandler, IOStuff& _iostuff) : GenericPage(_shapeHandler, _iostuff, FileNames::connectingLua) {
        lobby = gcnew Lobby();
        lobby->hostLANAsync();
    };

    virtual PageState process(MiscInfo miscInfo, InputManager& inputs) {
        PageState pageChange = handleButtonClicks(inputs);
        if (!System::Object::ReferenceEquals(lobby->server, nullptr) && lobby->server->startedGame)
            pageChange = PageState::LANSERVER;
        return pageChange;
    }

};