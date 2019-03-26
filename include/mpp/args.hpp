/* - args.hpp -------------------------------------------------------------------------------------
* A wrap over for command line arguments parsing.
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2019
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_ARGS_
#define _MPP_ARGS_

#include <unordered_map>
#include <vector>
#include <cstring>

namespace mpp
{

class args
{
public:
    static args parse(int argc, const char * const argv[])
    {
        args ret;
        std::vector<std::string> arg_data;
        std::string arg_name;
        for(int i=0; i<argc; i++)
        {
            if(argv[i][0] == arg_start)
            {
                if(arg_name.size() != 0)
                {
                    ret.values.insert({arg_name, arg_data});
                }
                else
                {
                    if(arg_data.size() > 0)
                    {
                        for(auto& i : arg_data)
                            ret.unnamed_values.push_back(i);
                    }
                }
                
                #ifdef WIN32
                arg_name = std::string(argv[i] + 1, argv[i] + std::strlen(argv[i]));
                #else
                arg_name = std::string(argv[i][1] == arg_start ? argv[i] + 2 : argv[i] + 1, argv[i] + strlen(argv[i]));
                #endif

                arg_data = std::vector<std::string>();
            }
            else
            {
                arg_data.push_back(argv[i]);
            }
            
        }
        
        if(arg_name.size() != 0)
        {
            ret.values.insert({arg_name, arg_data});
        }
        else
        {
            if(arg_data.size() > 0)
            {
                for(auto& i : arg_data)
                    ret.unnamed_values.push_back(i);
            }
        }
        return ret;
    }

    args(const args& other)
        : values(other.values),
        unnamed_values(other.unnamed_values)
    {

    }

    args(args&& other)
    {
        values = other.values;
        unnamed_values = other.unnamed_values;
    }


    args& operator=(const args& other)
    {
        values = other.values;
        unnamed_values = other.unnamed_values;
        return *this;
    }

    bool has(const std::string& name) const
    {
        return values.find(name) != values.end();
    }

    std::string get_one(const std::string& name) const
    {
        if(!has(name))
            throw std::exception();
        if(values[name].size() == 0)
            throw std::exception();
        return values[name][0];
    }

    std::vector<std::string> get_values(const std::string& name) const
    {
        if(!has(name))
            throw std::exception();
        if(values[name].size() == 0)
            throw std::exception();
        return values[name];
    }

    std::vector<std::string> get_unnamed_values() const
    {
        return unnamed_values;
    }
private:
    args()
    {

    }
#ifdef WIN32
    static const char arg_start = "/";
#else
    static const char arg_start = '-';
#endif

    mutable std::unordered_map<std::string, std::vector<std::string>> values;
    std::vector<std::string> unnamed_values;
};

}

#endif