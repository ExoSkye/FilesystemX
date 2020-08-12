//
// Created by bobro on 12/08/2020.
//

#ifndef FILESYSTEMX_FILESYSTEM_PLATFORM_INDEPENDENT_HPP
#define FILESYSTEMX_FILESYSTEM_PLATFORM_INDEPENDENT_HPP

#include <string>
#include <stdexcept>

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
        std::string operator[] (const int index) {
            int j = 0;
            bool outofbounds = false;
            for (int i = 0; i < index; i++) {
                while (filePath[j] != '/' || filePath[j] != '\\' || filePath[j] != '.') {
                    if (filePath.length() == j) {
                        outofbounds = true;
                        break;
                    }
                    j++;
                }
                if (outofbounds) {
                    break;
                }
                j++;
            }
            if (outofbounds) {
                throw std::out_of_range("String index out of bounds");
                return "OUT_OF_RANGE_ERROR";
            }
            else {
                return filePath.substr(0, j);
            }
        }
    };
}

#endif //FILESYSTEMX_FILESYSTEM_PLATFORM_INDEPENDENT_HPP
