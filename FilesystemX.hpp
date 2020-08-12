#if defined(NXDK)
|| defined(_WIN32)
#pragma message("Using nxdk/win32 version of FilesystemX")
#include "filesystem_xbx.hpp"
#elif __cplusplus > 201600L
#pragma message "Using C++17 crossplatform version of FilesystemX"
#include "filesystem_cpp17.hpp"
#elif __cplusplus > 201302L
#pragma message "Using C++14 crossplatform version of FilesystemX"
#include "filesystem_cpp14.hpp"
#else
#error This library only supports NXDK (compiling for the OG Xbox) or higher using a compiler that supports the C++14 standard
#endif
