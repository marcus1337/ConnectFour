#pragma once
#include <map>

namespace Utils {

    template <class K, class V>
    static bool mapContainsKey(std::map<K, V>& map, K key)
    {
        if (map.find(key) == map.end()) return false;
        return true;
    }

};