/* - io/directory_info.hpp ------------------------------------------------------------------------
* Directory Info. Provides an abstraction on top of files and directories.
*
* This file is a part of MPP project.
*
* This software is in public domain, distributed on "AS IS" basis, without technical support,
* and with no warranty, epress or implied, as to its usefulness for any purpose.
*
* Copyright (c) Grim Maple @ 2019
* -------------------------------------------------------------------------------------------------
*/

#ifndef _MPP_IO_DIRECTORY_INFO_
#define _MPP_IO_DIRECTORY_INFO_

#include <string>
#include <vector>
#include <algorithm>

#ifdef WIN32
#include <Windows.h>
#else

#endif

#include "fs_item.hpp"
#include "file_info.hpp"
#include "path.hpp"

namespace mpp
{

struct directory_info : public fs_item
{
public:
    directory_info(const path& p)
    {
        full_path = p;
        name = p.last_entry();
    }

    std::vector<file_info> get_files()
    {
        fill();
        return files;
    }

    std::vector<directory_info> get_directories()
    {
        fill();
        return directories;
    }

private:
    directory_info(const std::string& name, const std::string& path)
        : fs_item(name, path) {}
#ifdef WIN32
    void fill()
    {
        if(filled)
            return;

        filled = true;
        WIN32_FIND_DATA ffd;
        LARGE_INTEGER filesize;
        TCHAR szDir[MAX_PATH];
        HANDLE hFind = INVALID_HANDLE_VALUE;

        hFind = FindFirstFile((full_path.get() + "/*").c_str(), &ffd);
        if(hFind == INVALID_HANDLE_VALUE)
            return;

        do
        {
            if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                directories.push_back(directory_info(ffd.cFileName, full_path.get()));
            }
            else
            {
                filesize.LowPart = ffd.nFileSizeLow;
                filesize.HighPart = ffd.nFileSizeHigh;
                files.push_back(file_info(ffd.cFileName, full_path.get(), filesize.QuadPart));
            }
        } while(FindNextFile(hFind, &ffd) != 0);
        FindClose(hFind);
    }
#else
    void fill()
    {
        // TODO: Implement for linux
    }
#endif
    std::vector<directory_info> directories;
    std::vector<file_info> files;

    bool filled = false;
};

}

#endif
