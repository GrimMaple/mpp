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

namespace mpp
{

class binary_writer
{
public:
    binary_writer() 
        : f(nullptr),
          isOpen(false)
    {
    }

    binary_writer(const char* fileName) : binary_writer()
    {
        open(fileName);
    }

    binary_writer(const std::string& fileName) : binary_writer(fileName.c_str())
    {

    }

    bool open(const std::string& fileName)
    {
        return open(fileName.c_str());
    }

    bool open(const char* fileName)
    {
        f = fopen(fileName, "wb");
        return (isOpen = f != nullptr);
    }

    template<typename T>
    binary_writer &operator<<(const T& left)
    {
        fwrite(&left, sizeof(left), 1, f);
        return *this;
    }

    template<typename T>
    binary_writer &operator<<(T* left)
    {
        fwrite(left, sizeof(T), 1, f);
        return *this;
    }

    template<typename T>
    binary_writer &operator<<(std::vector<T> left)
    {
        fwrite(left.data(), sizeof(T), left.size(), f);
        return *this;
    }

    void close()
    {
        if(isOpen)
            fclose(f);
        isOpen = false;
    }

    bool is_open() const
    {
        return isOpen;
    }

    ~binary_writer()
    {
        close();
    }

private:
    FILE *f;
    bool isOpen;
};

}

#endif