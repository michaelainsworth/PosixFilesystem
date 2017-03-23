#ifndef POSIXFILESYSTEM_DIRECTORY_HPP
#define POSIXFILESYSTEM_DIRECTORY_HPP

#include <PosixFilesystem/Common.hpp>
#include <PosixFilesystem/File.hpp>
#include <PosixFilesystem/FileMode.hpp>

POSIXFILESYSTEM_NAMESPACE_BEGIN

class Directory
{
public:

    // Constructor
    Directory(const String& path);
    ~Directory();

    // Accessors
    String path() const;

    // Potential mutators
    File file(const String& filename, FileMode mode) const;
    Directory subdirectory(const String& path) const;

private:

    // Variables
    SharedDirectoryImplPointer pDirectoryImpl_;

};

POSIXFILESYSTEM_NAMESPACE_END

#endif // POSIXFILESYSTEM_DIRECTORY_HPP
