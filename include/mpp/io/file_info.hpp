/* - io/file_info.hpp -----------------------------------------------------------------------------
* File Info. Provides an abstraction on top of files and directories.
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2018
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_IO_FILE_INFO_
#define _MPP_IO_FILE_INFO_

#include <string>

#include "fs_item.hpp"

namespace mpp
{

struct file_info : public fs_item
{
public:
    size_t get_size() const { return size; }
private:
    file_info(const std::string& name, const std::string& path, size_t size)
        : fs_item(name, path), size(size) {}
    
    size_t size;

    friend class directory_info;
};

}

#endif
