/* - io/path.hpp ----------------------------------------------------------------------------------
* Path. Bottom-level abstraction on filesystem path.
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2019
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_PATH_
#define _MPP_PATH_

#include <algorithm>
#include <string>

namespace mpp
{

class path
{
public:
    path() = default;

    path(const std::string& p)
        : path_str(p)
    {
        normalize_path();
    }

    path operator+(const std::string& add) const { return path(path_str + "/" + add); }
    const path& operator+=(const std::string& add) 
    {
        path_str += ("/" + add);
        normalize_path();

        return *this;
    }

    std::string last_entry() const
    {
        auto end = path_str.end() - 1;
        if(*end == '/') end--;
        auto tmp = end;
        while(*tmp != '/') tmp--;

        return std::string(tmp+1, end+1);
    }

    const std::string& get() const { return path_str; }

private:
    void normalize_path()
    {
        // Normalize all wrong slashes to correct ones
        std::replace_if(path_str.begin(), path_str.end(), [](const auto& e){return e == '\\';}, '/');

        // Remove all duplicating slashes
        for(auto it = path_str.begin(); it != path_str.end(); ++it)
        {
            if(*it == '/' && *(it-1) == '/')
            {
                path_str.erase(it);
                it--;
            }
        }
    }

    std::string path_str;
};

}

#endif