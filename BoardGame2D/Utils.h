#pragma once
#include <map>

namespace Utils {

    template <class K, class V>
    static bool mapContainsKey(std::map<K, V>& map, K key)
    {
        if (map.find(key) == map.end()) return false;
        return true;
    }

    template <class T>
    static T lerp(T start, T end, T t)
    {
        return start + t * (end - start);
    }

    template <class T>
    static bool floatEqual(T a, T b)
    {
        return abs(a-b) < 0.00005;
    }

};