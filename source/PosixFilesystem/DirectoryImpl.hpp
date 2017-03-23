#ifndef POSIXFILESYSTEM_DIRECTORYIMPL_HPP
#define POSIXFILESYSTEM_DIRECTORYIMPL_HPP

#include <PosixFilesystem/Directory.hpp>
#include <PosixFilesystem/File.hpp>
#include <PosixFilesystem/FileMode.hpp>
#include <PosixFilesystem/Common.hpp>
#include <sys/types.h>
#include <dirent.h>

POSIXFILESYSTEM_NAMESPACE_BEGIN

class DirectoryImpl
{
public:

    // Lifecycle
    DirectoryImpl(const String& path);
    ~DirectoryImpl();

    // Non-copyable
    DirectoryImpl(const DirectoryImpl&) = delete;
    DirectoryImpl(DirectoryImpl&&) = delete;
    DirectoryImpl& operator =(const DirectoryImpl&) = delete;
    DirectoryImpl& operator =(DirectoryImpl&&) = delete;

    // Accessors
    String path() const;

    // Mutators
    File file(const String& filename, FileMode mode) const;
    Directory subdirectory(const String& path) const;

private:

    // Variables
    String path_;
    DIR* dir_;

};

POSIXFILESYSTEM_NAMESPACE_END

#endif // POSIXFILESYSTEM_DIRECTORYIMPL_HPP

