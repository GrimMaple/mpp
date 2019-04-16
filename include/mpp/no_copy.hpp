/* - no_copy.hpp ----------------------------------------------------------------------------------
* Provides a basic non-copyable class
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2019
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_NO_COPY_
#define _MPP_NO_COPY_

namespace mpp
{

class no_copy
{
public:
    no_copy() = default;
    virtual ~no_copy() = default;

    no_copy(const no_copy& other) = delete;
    no_copy(no_copy& other) = delete;
    void operator=(const no_copy& other) = delete;
    void operator=(no_copy& other) = delete;
};

}

#endif