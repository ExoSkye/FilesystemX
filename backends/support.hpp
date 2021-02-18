//
// Created by bobro on 12/08/2020.
//

#ifndef FILESYSTEMX_FILESYSTEM_PLATFORM_INDEPENDENT_HPP
#define FILESYSTEMX_FILESYSTEM_PLATFORM_INDEPENDENT_HPP

#include <string>
#include <stdexcept>
#include <vector>

namespace ProtoFS {
    enum fileType {
        Special,
        File,
        Folder
    };

    class fileEntry {
    public:
        fileEntry(std::string _fileName, std::string _filePath, fileType _type) {
            fileName = _fileName;
            filePath = _filePath;
            type = _type;
        }

        std::string fileName;
        std::string filePath;
        fileType type;

        std::string operator[](const int index) {
            int j = 0;
            bool outofbounds = false;
            for (int i = 0; i < index + 1; i++) {
                while (!(filePath.substr(j, 1) == "/" || filePath.substr(j, 1) == "\\" ||
                         filePath.substr(j, 1) == ".")) {
                    if (filePath.length() == (long unsigned int)j) {
                        outofbounds = true;
                        break;
                    }
                    j++;
                }
                if (outofbounds) {
#ifndef NXDK
                    throw std::out_of_range("String index out of bounds");
#else
                    break;
#endif
                }
                j++;
            }
            return filePath.substr(0, j);
        }

        std::string getExt() {
            int lastDot = filePath.rfind('.');
            return filePath.substr(lastDot, filePath.length() - lastDot);
        }
    };

    class FilesystemTemplate {
    public:
        std::string path;

        virtual std::vector<fileEntry> ls() = 0;
        virtual bool mk(fileEntry entry) = 0;
        virtual bool rm(fileEntry entry) = 0;
    };
}

#endif //FILESYSTEMX_FILESYSTEM_PLATFORM_INDEPENDENT_HPP
