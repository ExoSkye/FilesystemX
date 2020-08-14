#if defined(NXDK) || defined(_WIN32)
    //#pragma message "Using nxdk/win32 version of FilesystemX"
    #include "filesystem_xbx.hpp"
#elif __cplusplus > 201600L
    //#pragma message "Using C++17 crossplatform version of FilesystemX"
    #define CPP17
    #include "filesystem_std.hpp"
#elif __cplusplus > 201302L
    //#pragma message "Using C++14 crossplatform version of FilesystemX"
    #define CPP14
    #include "filesystem_std.hpp"
#else
    //#pragma message "Using C++98 POSIX version of FilesystemX"
    #include "filesystem_posix.hpp"
#endif