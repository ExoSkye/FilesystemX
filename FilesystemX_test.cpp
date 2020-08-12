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
    printf("Completed unit tests successfully\n");
}
