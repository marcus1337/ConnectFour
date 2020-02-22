#pragma once

#include "LuaCalls.h"

#include <string>
#include <iostream>
#include <map>
#include <codecvt>

class IOStuff {
    std::map<std::string, time_t> modFiles;

public:
    std::string dirpath;

    IOStuff();
    ~IOStuff();

    static std::string getexepath();
    bool isFileModified(std::string filename);

    lua_State* loadLuaFile(std::string filename);
    void loadCppFunctionsToLuaState(lua_State*);
    std::string getLuaFilePath();


};
