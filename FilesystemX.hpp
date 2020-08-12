#ifdef NXDK
#include "filesystem_xbx.hpp"
#elif __cplusplus > 201703L
#include "filesystem_cpp17.hpp"
#elif __cplusplus > 201402L 
#include "filesystem_cpp14.hpp"
#else
#error This library only supports NXDK (compiling for the OG Xbox) or higher using a compiler that supports the C++14 standard
#endif
