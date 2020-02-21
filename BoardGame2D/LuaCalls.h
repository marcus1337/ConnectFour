#pragma once
#include <lua.hpp>
#include <windows.h>
#include <string>
#include "Button.h"
#include "MiscInfo.h"
#include <vector>
#include "ShapeHandler.h"
#include "Image.h"

#include <iostream>

namespace LuaToCpp {

    static int lua_sleep(lua_State *L)
    {
        int m = static_cast<int> (luaL_checknumber(L, 1));
        Sleep(m);
        return 0;
    }

}

namespace CppToLua {

    static void pushInfoToLua(lua_State* _L, MiscInfo miscInfo) {
        lua_newtable(_L);
        lua_pushnumber(_L, miscInfo.windowWidth);
        lua_setfield(_L, -2, "width");
        lua_pushnumber(_L, miscInfo.windowHeight);
        lua_setfield(_L, -2, "height");
        lua_pushnumber(_L, miscInfo.ticks);
        lua_setfield(_L, -2, "ticks");
        lua_setglobal(_L, "info");
    }

    static void runLuaFile(lua_State *L) {
        lua_pcall(L, 0, LUA_MULTRET, 0);
    }

    static bool reloadLuaFile(lua_State *L, std::string filePathAndName) {
        int error = luaL_loadfile(L, filePathAndName.c_str());
        if (error == LUA_ERRFILE) {
            return false;
        }
        return true;
    }

    static void initLuaFile(lua_State* _L, std::string fileLocation, MiscInfo miscInfo) {
        CppToLua::reloadLuaFile(_L, fileLocation);
        CppToLua::pushInfoToLua(_L, miscInfo);
        lua_pcall(_L, 0, LUA_MULTRET, 0);
    }

    static void loadButtonTableToStack(lua_State* _L) {
        lua_pushstring(_L, "width");
        lua_gettable(_L, -2);
        lua_pushstring(_L, "height");
        lua_gettable(_L, -3);
        lua_pushstring(_L, "title");
        lua_gettable(_L, -4);
        lua_pushstring(_L, "x");
        lua_gettable(_L, -5);
        lua_pushstring(_L, "y");
        lua_gettable(_L, -6);
        lua_pushstring(_L, "value");
        lua_gettable(_L, -7);
        lua_pushstring(_L, "downImg");
        lua_gettable(_L, -8);
        lua_pushstring(_L, "upImg");
        lua_gettable(_L, -9);
        lua_pushstring(_L, "hoverImg");
        lua_gettable(_L, -10);
    }

    static Button makeButtonFromStackData(lua_State* _L) {
        Button button;
        auto btnRect = button.getRect();
        btnRect.w =     lua_tonumber(_L, -9);
        btnRect.h =     lua_tonumber(_L, -8);
        button.setText( lua_tostring(_L, -7));
        btnRect.x =     lua_tonumber(_L, -6);
        btnRect.y =     lua_tonumber(_L, -5);
        button.value =  lua_tonumber(_L, -4);
        button.downImageName =  lua_tostring(_L, -3);
        button.upImageName =    lua_tostring(_L, -2);
        button.hoverImageName = lua_tostring(_L, -1);
        button.setRect(btnRect);
        return button;
    }

    static Button getButtonFromTable(lua_State* _L) {
        loadButtonTableToStack(_L);
        Button button = makeButtonFromStackData(_L);
        lua_pop(_L, 10);
        return button;
    }

    static void loadImageTableToStack(lua_State* _L) {
        lua_pushstring(_L, "width");
        lua_gettable(_L, -2);
        lua_pushstring(_L, "height");
        lua_gettable(_L, -3);
        lua_pushstring(_L, "x");
        lua_gettable(_L, -4);
        lua_pushstring(_L, "y");
        lua_gettable(_L, -5);
        lua_pushstring(_L, "imageName");
        lua_gettable(_L, -6);
    }

    static Image makeImageFromStackData(lua_State* _L) {
        Image image;
        int tmpWidth = lua_tonumber(_L, -5);
        int tmpHeight = lua_tonumber(_L, -4);
        int tmpX = lua_tonumber(_L, -3);
        int tmpY = lua_tonumber(_L, -2);
        std::string imageName = lua_tostring(_L, -1);
        auto imageRect = image.getRect();
        imageRect.w = tmpWidth;
        imageRect.h = tmpHeight;
        imageRect.x = tmpX;
        imageRect.y = tmpY;
        image.setRect(imageRect);
        image.imageName = imageName;
        return image;
    }

    static Image getImageFromTable(lua_State* _L) {
        loadImageTableToStack(_L);
        Image image = makeImageFromStackData(_L);
        lua_pop(_L, 6);
        return image;
    }

    static bool loadedLuaFunction(lua_State* _L, std::string functionName) {
        lua_getglobal(_L, functionName.c_str());
        bool isAFunction = lua_isfunction(_L, -1);
        if (!isAFunction) {
            lua_pop(_L, 1);
            return false;
        }
        return true;
    }

    static void setButtonImageTextures(Button& button, ShapeHandler& shapeHandler, SDL_Renderer* renderer) {
        button.setImage(shapeHandler.button1, shapeHandler.button1_pressed);
        if (button.downImageName != "")
            button.textureDown = shapeHandler.getImageTexture(renderer, button.downImageName);
        if (button.upImageName != "") {
            button.textureUp = shapeHandler.getImageTexture(renderer, button.upImageName);
        }
        if (button.hoverImageName != "")
            button.textureHover = shapeHandler.getImageTexture(renderer, button.hoverImageName);
    }

    static std::vector<Button> getButtonsFromLua(lua_State* _L, ShapeHandler& shapeHandler, SDL_Renderer* renderer) {
        std::vector<Button> tmpButtons;
        if (!loadedLuaFunction(_L, "getButtons"))
            return tmpButtons;

        lua_pcall(_L, 0, LUA_MULTRET, 0);
        int numberOfTables = lua_gettop(_L) - 1;

        if (numberOfTables == 1 && lua_isnil(_L, -1)) {
            lua_pop(_L, 1);
            return tmpButtons;
        }

        for (int i = 0; i < numberOfTables; i++) {
            Button button = getButtonFromTable(_L);
            setButtonImageTextures(button, shapeHandler, renderer);
            tmpButtons.push_back(button);
        }

        return tmpButtons;
    }

    static std::vector<Image> getImagesFromLua(lua_State* _L, ShapeHandler& shapeHandler, SDL_Renderer* renderer) {
        std::vector<Image> tmpImages;
        if (!loadedLuaFunction(_L, "getImages"))
            return tmpImages;

        lua_pcall(_L, 0, LUA_MULTRET, 0);
        int numberOfTables = lua_gettop(_L) - 1;

        if (numberOfTables == 1 && lua_isnil(_L, -1)) {
            lua_pop(_L, 1);
            return tmpImages;
        }

        for (int i = 0; i < numberOfTables; i++) {
            Image image = getImageFromTable(_L);
            image.texture = shapeHandler.getImageTexture(renderer, image.imageName);
            tmpImages.push_back(image);
        }

        return tmpImages;
    }

}