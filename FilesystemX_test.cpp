//
// Created by bobro on 12/08/2020.
//

#include "FilesystemX.hpp"
#include <stdio.h>
#include <cassert>
int main() {
    printf("Starting FilesystemX unit tests\n");
    ProtoFS::fileEntry myFile("testFile.txt","/home/test/testFile.txt",ProtoFS::File);
    assert(myFile[0] == "/");
    assert(myFile[1] == "/home/");
    assert(myFile[2] == "/home/test/");
    assert(myFile[3] == "/home/test/testFile.");
    assert(myFile.getExt() == ".txt");
#ifdef __linux__
    ProtoFS::FilesystemX fs("/home/");
#else
    ProtoFS::FilesystemX fs("C:\\*.*");
#endif
    std::vector<ProtoFS::fileEntry> ret = fs.listDir();
    for (int i = 0; i < ret.size(); i++) {
        printf((ret[i].filePath+"\n").c_str());
    }
    printf("Completed unit tests successfully\n");
}
