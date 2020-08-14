# FilesystemX
Filesystem library for programs made to work on the OG Xbox (nxdk) and PCs (Win32, POSIX, original Xbox and any compiler supporting C++14 and has a properly working implementation of std::filesystem)

# Building the test app
Run these commands:

```
mkdir build
cd build
cmake ..
make
```
This should generate three programs on a *UNIX system named TestApp17, TestApp14 and TestAppPOSIX and on Windows it should generate a program called TestAppWindows.exe

If you run any of the programs *should* print:
```
Starting FilesystemX unit tests
/home/<YOURUSERNAME>
Completed unit tests successfully
```
On Windows it should show:
```
Starting FilesystemX unit tests
<THE CONTENTS OF THE YOUR C:\ PATH>
Completed unit tests successfully
```

# Using this library 
To use this library in any of your projects just copy the files (or better use a git submodule) and include ```FilesystemX.hpp```
