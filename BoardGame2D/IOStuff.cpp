#include "IOStuff.h"
using namespace LuaToCpp;
using namespace CppToLua;

IOStuff::IOStuff() {
    dirpath = IOStuff::getexepath();
}

IOStuff::~IOStuff() {
   // lua_close(state);
}

std::string IOStuff::getLuaFilePath() {
    return dirpath + "lua\\";
}

std::string IOStuff::getexepath()
{
    wchar_t result[MAX_PATH];
    std::wstring  filepath = std::wstring(result, GetModuleFileName(NULL, result, MAX_PATH));
    while (filepath.size() > 0 && filepath[filepath.size() - 1] != '\\') {
        filepath = filepath.substr(0, filepath.size() - 1);
    }
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
    std::string utf8NativeString = convert.to_bytes(filepath);
    return utf8NativeString;
}

bool IOStuff::isFileModified(std::string filename) {
    struct stat result;
    std::string filePathAndName = getLuaFilePath() + filename;
    if (stat(filePathAndName.c_str(), &result) == 0)
    {
        time_t mod_time = result.st_mtime;

        std::map<std::string, time_t>::iterator lb = modFiles.lower_bound(filename);

        if (lb != modFiles.end())
        {
            // key already exists
            time_t oldTime = lb->second;
            modFiles[filename] = mod_time;
            return oldTime != mod_time;
        }
        else
        {
            // the key does not exist in the map
            modFiles.insert(lb, std::map<std::string, time_t>::value_type(filename, mod_time));
            return true;
        }
    }
    return false;
}

lua_State* IOStuff::loadLuaFile(std::string filename) {
    lua_State* result = luaL_newstate();
    luaL_openlibs(result);
    std::string scriptFileName = getLuaFilePath() + filename;
    if (!reloadLuaFile(result, scriptFileName.c_str())) {
        std::cout << "READ ERROR!" << std::endl;
        lua_close(result);
        return nullptr;
    }
    loadCppFunctionsToLuaState(result);
    return result;
}

void IOStuff::loadCppFunctionsToLuaState(lua_State* _state) {
    lua_pushcfunction(_state, lua_sleep);
    lua_setglobal(_state, "sleep");
}


/*static long getFileSize(std::string filename)
{
    struct stat stat_buf;
    std::string dirpath = IOStuff::getexepath() + filename;
    int rc = stat(dirpath.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}*/