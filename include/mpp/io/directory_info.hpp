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
#include <dirent.h>
#include <sys/stat.h>
#endif

#include "fs_item.hpp"
#include "file_info.hpp"
#include "path.hpp"

namespace mpp
{

struct directory_info : public fs_item
{
public:
    directory_info(const std::string& p)
        : directory_info(path(p)) {}

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
        DIR *dir;
        dirent *ent;
        struct stat st;

        dir = opendir(full_path.get().c_str());
        while ((ent = readdir(dir)) != NULL)
        {
            const std::string file_name = ent->d_name;
            const std::string full_file_name = full_path.get() + "/" + file_name;

            if (stat(full_file_name.c_str(), &st) == -1)
                continue;

            const bool is_directory = (st.st_mode & S_IFDIR) != 0;

            if (is_directory)
                directories.push_back(directory_info(file_name, full_path.get()));
            else
                files.push_back(file_info(file_name, full_path.get(), st.st_size));
        }
        closedir(dir);
    }
#endif
    std::vector<directory_info> directories;
    std::vector<file_info> files;

    bool filled = false;
};

}

#endif
