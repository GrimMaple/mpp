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

namespace mpp
{

template<typename F, typename T>
T by_bit_cast(F from)
{
    return *reinterpret_cast<T*>(&from);
}

}

#endif