/* - io/fs_item.hpp -------------------------------------------------------------------------------
* File System Item. Bottom-level abstraction on filesystem entries.
* Provides an abstraction on top of files and directories.
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2018
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_IO_FS_ITEM_
#define _MPP_IO_FS_ITEM_

#include <string>

namespace mpp
{

struct fs_item
{
public:
    const std::string& get_path() const { return path; }
    const std::string& get_name() const { return name; }
protected:
    fs_item(const std::string& name, const std::string& path)
        : path(path + name), name(name) {}

    std::string path;
    std::string name;
};

}

#endif
