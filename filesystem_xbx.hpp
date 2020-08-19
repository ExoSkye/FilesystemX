//
// Created by bobro on 12/08/2020.
//

#ifndef FILESYSTEMX_FILESYSTEM_XBX_HPP
#define FILESYSTEMX_FILESYSTEM_XBX_HPP

#include "filesystem_platform_independent.hpp"
#include "windows.h"
namespace ProtoFS {
    class FilesystemX : public FilesystemTemplate {
    public:
        FilesystemX(std::string _path) {
            path = _path;
        }
        std::vector<fileEntry> listDir() override {
            std::vector<fileEntry> ret;
            WIN32_FIND_DATA data;
            HANDLE hFind = hFind = FindFirstFile(path.c_str(), &data);      // DIRECTORY

            if ( hFind != INVALID_HANDLE_VALUE ) {
                do {
                    fileType type = File;
                    if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        type = Folder;
                    }
                    ret.emplace_back(fileEntry((data.cFileName, "\n"),(data.cAlternateFileName, "\n"),type));
                } while (FindNextFile(hFind, &data) != 0);
                FindClose(hFind);
            }
            else {
                ret.emplace_back(fileEntry("INVALID HANDLE\n","INVALID HANDLE\n",File));
            }
            return ret;
        }
    };
}
#endif //FILESYSTEMX_FILESYSTEM_XBX_HPP
