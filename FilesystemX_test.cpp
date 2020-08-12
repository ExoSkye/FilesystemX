//
// Created by bobro on 12/08/2020.
//

#include "FilesystemX.hpp"
#include <stdio.h>
int main() {
    printf("Starting FilesystemX unit tests\n");
    ProtoFS::fileEntry myFile("testFile","/home/test/testFile",ProtoFS::File);
    printf("%s %s %s",myFile[0].c_str(),myFile[1].c_str(),myFile[1].c_str());
}