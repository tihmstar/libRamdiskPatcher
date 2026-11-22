//
//  utils.hpp
//  libRamdiskPatcher
//
//  Created by tihmstar on 17.11.26.
//

#ifndef utils_hpp
#define utils_hpp

#include <iostream>

#include <libgeneral/Mem.hpp>

#ifdef WIN32
#define PATH_DELIMITER_STRING "\\"
#define PATH_DELIMITER_CHAR '\\'
#else
#define PATH_DELIMITER_STRING "/"
#define PATH_DELIMITER_CHAR '/'
#endif

#if defined(WIN32) && !__clang__
#   define RAMDISK_PATCHER_API __declspec( dllexport )
#else
#   ifdef HAVE_FVISIBILITY
#       define RAMDISK_PATCHER_API __attribute__((visibility("default")))
#   else
#       define RAMDISK_PATCHER_API
#   endif
#endif

namespace RamdiskPatcher {
namespace utils {
std::string getTmpdir();
std::string genpassp(const char *platform, const void *ramdiskBuf, size_t ramdiskSize);
tihmstar::Mem resignFile(const void *buf, size_t bufSize);
}
}

#endif /* utils_hpp */
