#pragma once
#include <lua.hpp>
#include <windows.h>
#include <string>
#include "Button.h"
#include "MiscInfo.h"
#include <vector>
#include "ShapeHandler.h"

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
    }

    static Button makeButtonFromStackData(lua_State* _L) {
        Button button;
        int tmpWidth  = lua_tonumber(_L, -6);
        int tmpHeight = lua_tonumber(_L, -5);
        std::string tmpTitle = lua_tostring(_L, -4);
        int tmpX = lua_tonumber(_L, -3);
        int tmpY = lua_tonumber(_L, -2);
        int btnValue = lua_tonumber(_L, -1);
        auto btnRect = button.getRect();
        btnRect.w = tmpWidth;
        btnRect.h = tmpHeight;
        btnRect.x = tmpX;
        btnRect.y = tmpY;
        button.setRect(btnRect);
        button.setText(tmpTitle);
        button.value = btnValue;
        return button;
    }

    static Button getButtonFromTable(lua_State* _L) {
        loadButtonTableToStack(_L);
        Button button = makeButtonFromStackData(_L);
        lua_pop(_L, 7);
        return button;
    }

    static std::vector<Button> getButtonsFromLua(lua_State* _L, ShapeHandler& shapeHandler) {
        std::vector<Button> tmpButtons;
        lua_getglobal(_L, "getButtons");
        lua_pcall(_L, 0, LUA_MULTRET, 0);
        int numberOfTables = lua_gettop(_L) - 1;

        for (int i = 0; i < numberOfTables; i++) {
            Button button = getButtonFromTable(_L);
            button.setImage(shapeHandler.button1, shapeHandler.button1_pressed);
            tmpButtons.push_back(button);
        }
        return tmpButtons;
    }

}