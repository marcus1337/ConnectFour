#pragma once
#include "GenericPage.h"

class MainMenu : public GenericPage {
public:

    MainMenu(ShapeHandler& _shapeHandler, IOStuff& _iostuff) : GenericPage(_shapeHandler, _iostuff, FileNames::mainMenuLua) {

    };

};