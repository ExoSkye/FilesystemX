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
            HANDLE hFind = FindFirstFile(path.c_str(), &data);      // DIRECTORY

            if ( hFind != INVALID_HANDLE_VALUE ) {
                do {
                    fileType type = File;
                    if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        type = Folder;
                    }
                    ret.emplace_back(fileEntry(data.cAlternateFileName,data.cFileName,type));
                } while (FindNextFile(hFind, &data));
                FindClose(hFind);
            }
            return ret;
        }
    };
}
/*
void GetFiles(char* driveletter, file filesArray[]) {
  WIN32_FIND_DATA findFileData;
  HANDLE hFind;

  file foundFiles[NUMFILES] = {NULL};

  size_t currentFileDirCount = 0;

  char* driveWav;
  sprintf(driveWav, "%s\\.wav", driveletter);

  hFind = FindFirstFileA(driveWav, &findFileData);

  do {
    XVideoWaitForVBlank();
    debugClearScreen();
    if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      continue;
    }
    else {
      if (currentFileDirCount < NUMFILES) {
        foundFiles[currentFileDirCount].fileIndex = currentFileDirCount;
        strcpy(foundFiles[currentFileDirCount].fileName, findFileData.cFileName);
        sprintf(foundFiles[currentFileDirCount].filePath, "%s\\%s", driveletter, foundFiles[currentFileDirCount].fileName);
        currentFileDirCount++;
      }
    }
  }
  while (FindNextFileA(hFind, &findFileData) != 0);
  FindClose(hFind);

  filesArray = foundFiles;
}
 */
#endif //FILESYSTEMX_FILESYSTEM_XBX_HPP
