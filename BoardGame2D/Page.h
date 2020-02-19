#pragma once
#include "SDL.h"
#include "ShapeHandler.h"
#include "InputManager.h"
#include "MiscInfo.h"



enum PageState {
    NONE = 0, MAINMENU = 1, LOCALPVP = 2, LOCALPVE = 3
};

class Page {
protected:
    lua_State* state = nullptr;
    IOStuff& iostuff;
public:
    ShapeHandler& shapeHandler;
    Page(ShapeHandler& _shapeHandler, IOStuff& _iostuff) : shapeHandler(_shapeHandler), iostuff(_iostuff) {}
    virtual ~Page() {
        lua_close(state);
    }
    virtual void onStart(SDL_Renderer* renderer, MiscInfo miscInfo) = 0;
    virtual void draw(SDL_Renderer *) = 0;
    virtual void updateContent(MiscInfo miscInfo, InputManager& inputmanager, SDL_Renderer* renderer) = 0;
    virtual PageState process(MiscInfo miscInfo, InputManager& inputmanager) = 0;

};