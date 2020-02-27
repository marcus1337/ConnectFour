#pragma once

#include "GenericPage.h"

public class LocalPVPPage : public GenericPage {
public:

    LocalPVPPage(ShapeHandler& _shapeHandler, IOStuff& _iostuff) : GenericPage(_shapeHandler, _iostuff, FileNames::localPVPLua) {
    };

    virtual void handleGameButtonClick(Button& button) {
        if (gameController.doneAnimatingBrickDrop())
            gameController.tryPlace(button.value);
    }


};