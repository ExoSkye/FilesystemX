//
// Created by bobro on 12/08/2020.
//

#ifndef FILESYSTEMX_FILESYSTEM_XBX_HPP
#define FILESYSTEMX_FILESYSTEM_XBX_HPP

#include "support.hpp"
#include <windows.h>
#include <algorithm>

namespace ProtoFS {
    class FilesystemX : public FilesystemTemplate {
    public:
        FilesystemX(std::string _path) {
            path = _path;
        }

        std::vector<fileEntry> listDir() override {
            std::vector<fileEntry> ret;
            WIN32_FIND_DATA data;
            HANDLE hFind = FindFirstFile(path.append("*.*").c_str(), &data);      // DIRECTORY
            path = path.erase((path.length() - 3), path.length());
            if (hFind != INVALID_HANDLE_VALUE) {
                do {
                    fileType type = File;
                    if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        type = Folder;
                    }
                    ret.emplace_back(fileEntry(data.cFileName, path + data.cFileName, type));
                } while (FindNextFile(hFind, &data) != 0);
                FindClose(hFind);
            } else {
                ret.emplace_back(fileEntry("INVALID HANDLE\n", "INVALID HANDLE\n", File));
            }
            #ifdef FLX_IncludeSpecialDirs
            return ret;
            #else
            std::vector<fileEntry> vec;
            std::copy(ret.begin()+2,ret.begin()+ret.size(),std::back_inserter(vec));
            return vec;
            #endif
        }

        bool mk(fileEntry entry) override {
            HANDLE ret;
            if (entry.type == Folder) {
                ret = CreateFileA(
                        entry.filePath.c_str(),
                        GENERIC_WRITE,          // Desired access
                        FILE_SHARE_READ,        // Share mode
                        NULL,                   // Security attributes
                        CREATE_NEW,             // Creates a new file, only if it doesn't already exist
                        FILE_ATTRIBUTE_NORMAL,  // Flags and attributes
                        NULL);                  // Template file handle
            }
            else {
                ret = CreateDirectoryA(
                        entry.filePath.c_str(),
                        NULL
                        );
            }
            if (ret == nullptr) {
                return false;
            }
            else {
                return true;
            }
        }

        bool rm(fileEntry entry) override {
            bool ret = true;
            if (entry.type == File) {
                ret = DeleteFileA(entry.filePath.c_str());
            }
            else {
                ret = RemoveDirectoryA(entry.filePath.c_str());
            }
            return ret;
        }
    };
}
#endif //FILESYSTEMX_FILESYSTEM_XBX_HPP
