//
// Created by bobro on 13/08/2020.
//

#ifndef FILESYSTEMX_FILESYSTEM_POSIX_HPP
#define FILESYSTEMX_FILESYSTEM_POSIX_HPP

#include "filesystem_platform_independent.hpp"

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <cassert>
#include <algorithm>

namespace ProtoFS {
    class FilesystemX : public FilesystemTemplate {
    public:
        FilesystemX(std::string _path) {
            path = _path;
        }

        std::vector <fileEntry> listDir() {
            std::replace(path.begin(),path.end(),"\\","/");
            std::vector <fileEntry> ret;
            DIR *dp;
            struct dirent *ep;
            dp = opendir(path.c_str());
            if (dp == NULL) {
                printf("Couldn't open the directory %s, it likely doesn't exist or this user doesn't have access rights to it",path.c_str());
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
            std::vector <fileEntry> vec;
            std::copy(ret.begin(), ret.begin() + (ret.size() - 2), std::back_inserter(vec));
            return vec;
        }
    };
}

#endif //FILESYSTEMX_FILESYSTEM_POSIX_HPP
