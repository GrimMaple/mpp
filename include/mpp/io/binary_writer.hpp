/* - io/binary_writer.hpp -------------------------------------------------------------------------
* Binary File Writer. Provides a better alternative for std::ofstream 
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2018
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_IO_BINARY_WRITER_
#define _MPP_IO_BINARY_WRITER_

#include <string>
#include <vector>
#include <cstdio>

#include "file_stream.hpp"

namespace mpp
{

class binary_writer : public file_stream
{
public:
    binary_writer() 
        : file_stream()
    {
    }

    binary_writer(const char* fileName) : file_stream(fileName, mode::wr)
    {
    }

    binary_writer(const std::string& fileName) : binary_writer(fileName.c_str())
    {

    }

    template<typename T>
    binary_writer &operator<<(const T& left)
    {
        write(&left, sizeof(left), 1);
        return *this;
    }

    template<typename T>
    binary_writer &operator<<(T* left)
    {
        write(left, sizeof(T), 1);
        return *this;
    }

    bool open(const char *fileName)
    {
	    return file_stream::open(fileName, mode::wr);
    }

    bool open(const std::string& fileName)
    {
	    return open(fileName.c_str());
    }

    template<typename T>
    binary_writer &operator<<(const std::vector<T>& left)
    {
        write(left.data(), sizeof(T), left.size());
        return *this;
    }

    ~binary_writer()
    {
    }
};

}

#endif
