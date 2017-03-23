#ifndef POSIXFILESYSTEM_FILEMODE_HPP
#define POSIXFILESYSTEM_FILEMODE_HPP

#include <PosixFilesystem/Common.hpp>

POSIXFILESYSTEM_NAMESPACE_BEGIN

typedef int FileMode;

const FileMode Read         = 0x00000001;
const FileMode Write        = 0x00000002;

POSIXFILESYSTEM_NAMESPACE_END

#endif // POSIXFILESYSTEM_FILEMODE_HPP

