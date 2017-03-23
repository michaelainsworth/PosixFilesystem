#ifndef POSIXFILESYSTEM_COMMON_HPP
#define POSIXFILESYSTEM_COMMON_HPP

#define POSIXFILESYSTEM_NAMESPACE PosixFilesystem
#define POSIXFILESYSTEM_NAMESPACE_BEGIN namespace POSIXFILESYSTEM_NAMESPACE {
#define POSIXFILESYSTEM_NAMESPACE_END }

#include <string>
#include <memory>

POSIXFILESYSTEM_NAMESPACE_BEGIN

class File;
class FileImpl;
class Directory;
class DirectoryImpl;

typedef std::string String;
typedef std::shared_ptr<FileImpl> SharedFileImplPointer;
typedef std::shared_ptr<DirectoryImpl> SharedDirectoryImplPointer;

POSIXFILESYSTEM_NAMESPACE_END

#endif // POSIXFILESYSTEM_COMMON_HPP
