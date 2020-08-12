//
// Created by bobro on 12/08/2020.
//

#ifndef FILESYSTEMX_FILESYSTEM_CPP14_HPP
#define FILESYSTEMX_FILESYSTEM_CPP14_HPP

#include "filesystem_platform_independent.hpp"

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

namespace ProtoFS {
    class FilesystemX : public FilesystemTemplate {
    public:
        FilesystemX(std::string _path) {
            path = _path;
        }
        std::vector<fileEntry> listDir() override {
            std::vector<fileEntry> ret;
            for(const fs::directory_entry& entry : fs::directory_iterator(path)) {
                // Is it a file / directory?
                fileType type = Folder;
                if (fs::is_directory(entry)) {
                    type = File;
                }
                auto path = entry.path();
                std::string pathString = path.string();
                std::string filenameString = path.filename().string();
                ret.emplace_back(fileEntry(filenameString,pathString,type));
            }
            return ret;
        }
    };
}

#endif //FILESYSTEMX_FILESYSTEM_CPP14_HPP
