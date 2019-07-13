/* - algorithm.hpp --------------------------------------------------------------------------------
* Set of algorithms
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2019
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_ALGORITHM_
#define _MPP_ALGORITHM_

#include <vector>

namespace mpp
{

template<typename F, typename T>
T by_bit_cast(F from)
{
    return *reinterpret_cast<T*>(&from);
}

template<class It, class T>
std::vector<std::vector<T>> split(It begin, It end, const T& ref)
{
    while(*begin == ref) // Skip all possible occurances of split element in the beginning
        begin++;

    std::vector<std::vector<T>> ret;

    auto add = [] (It& b, It& e)
    {
        std::vector<T> a;
        if(e - b > 0)
            a = std::vector<T>(b, e);

        return a;
    };

    auto cur = begin;
    auto last = begin;
    while((++cur) != end)
    {
        if(*cur != ref)
            continue;

        auto added = add(last, cur);
        if(added.size() != 0)
            ret.push_back(added);
        last = cur;
        last++; // Makes it point to a non splitting character
    }

    auto added = add(last, cur);
    if(added.size() != 0)
        ret.push_back(added);

    return ret;
}

std::vector<std::string> split(std::string::iterator begin, std::string::iterator end, const char ref)
{
    while(*begin == ref) // Skip all possible occurances of split element in the beginning
        begin++;

    std::vector<std::string> ret;

    auto add = [] (std::string::iterator& b, std::string::iterator& e)
    {
        std::string a;
        if(e - b > 0)
            a = std::string(b, e);

        return a;
    };

    auto cur = begin;
    auto last = begin;
    while((++cur) != end)
    {
        if(*cur != ref)
            continue;

        auto added = add(last, cur);
        if(added.size() != 0)
            ret.push_back(added);

        last = cur;
        last++; // Makes it point to a non splitting character
    }

    auto added = add(last, cur);
    if(added.size() != 0)
        ret.push_back(added);

    return ret;
}

}

#endif