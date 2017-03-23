#include <PosixFilesystem/Directory.hpp>
#include <iostream>
#include <PosixFilesystem/DirectoryImpl.hpp>

POSIXFILESYSTEM_NAMESPACE_BEGIN

// Constructor
Directory::Directory(const String& path) :
    pDirectoryImpl_(new DirectoryImpl(path))
{}

Directory::~Directory() {}

// Accessors
String Directory::path() const
{
    return pDirectoryImpl_->path();
}

// Potential mutators
File Directory::file(const String& filename, FileMode mode) const
{
    return pDirectoryImpl_->file(filename, mode);
}

Directory Directory::subdirectory(const String& path) const
{
    return pDirectoryImpl_->subdirectory(path);
}

POSIXFILESYSTEM_NAMESPACE_END

