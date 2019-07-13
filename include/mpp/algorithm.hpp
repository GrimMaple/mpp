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
#include <string>

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

inline std::vector<std::string> split(std::string::iterator begin, std::string::iterator end, const char ref)
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

template<typename It>
bool starts_with(It abegin, It aend, It bbegin, It bend)
{
    if(aend - abegin < bend - bbegin)
        return false;
    for(auto i = bbegin, j = abegin; i < bend; ++i, ++j)
    {
        if(*i != *j)
            return false;
    }

    return true;
}

inline bool starts_with(std::string a, std::string b)
{
    auto abegin = a.begin();
    auto aend = a.end();
    auto bbegin = b.begin();
    auto bend = b.end();

    return starts_with(abegin, aend, bbegin, bend);
}

inline bool starts_with(std::string::iterator abegin, std::string::iterator aend, std::string substr)
{
    auto bbegin = substr.begin();
    auto bend = substr.end();

    return starts_with(abegin, aend, bbegin, bend);
}

inline bool ends_with(std::string a, std::string b)
{
    auto abegin = a.rbegin();
    auto aend = a.rend();
    auto bbegin = b.rbegin();
    auto bend = b.rend();

    return starts_with(abegin, aend, bbegin, bend);
}

inline bool ends_with(std::string::reverse_iterator abegin, std::string::reverse_iterator aend, std::string substr)
{
    auto bbegin = substr.rbegin();
    auto bend = substr.rend();

    return starts_with(abegin, aend, bbegin, bend);
}

}

#endif