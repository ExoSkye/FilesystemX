//
// Created by bobro on 13/08/2020.
//

#ifndef FILESYSTEMX_FILESYSTEM_POSIX_HPP
#define FILESYSTEMX_FILESYSTEM_POSIX_HPP

#include "support.hpp"

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <cassert>
#include <algorithm>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace ProtoFS {
    class FilesystemX : public FilesystemTemplate {
    public:
        FilesystemX(std::string _path) {
            path = _path;
        }

        std::vector<fileEntry> ls() {
            //std::replace(path.begin(), path.end(), "\\", "/");
            std::vector<fileEntry> ret;
            DIR *dp;
            struct dirent *ep;
            dp = opendir(path.c_str());
            if (dp == NULL) {
                printf("Couldn't open the directory %s, it likely doesn't exist or this user doesn't have access rights to it",
                       path.c_str());
                return ret;
            }
            while ((ep = readdir(dp)) != NULL) {
                fileType _type = File;
                if (ep->d_type == *std::string("DT_DIR").c_str())
                    _type = Folder;
                fileEntry temp(std::string(ep->d_name), path + std::string(ep->d_name), _type);
                ret.push_back(temp);
            }
            (void) closedir(dp);
            #ifdef FLX_IncludeSpecialDirs
            return ret;
            #else
            std::vector<fileEntry> vec;
            std::copy(ret.begin()+2, ret.begin()+ret.size(), std::back_inserter(vec));
            return vec;
            #endif
        }

        bool mk(fileEntry entry) {
            int ret;
            if (entry.type == File) {
                ret = creat(entry.filePath.c_str(),S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            }
            else {
                ret = mkdir(entry.filePath.c_str(),S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            }
            return ret == 0;
        }

        bool rm(fileEntry entry) {
            int ret;
            if (entry.type == File) {
                ret = unlink(entry.filePath.c_str());
            }
            else {
                ret = rmdir(entry.filePath.c_str());
            }
            return ret == 0;
        }
    };
}

#endif //FILESYSTEMX_FILESYSTEM_POSIX_HPP
