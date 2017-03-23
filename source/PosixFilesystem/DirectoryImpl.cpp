#include <PosixFilesystem/DirectoryImpl.hpp>

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <libgen.h>

using std::runtime_error;
using std::cerr;
using std::endl;

POSIXFILESYSTEM_NAMESPACE_BEGIN

// Lifecycle
DirectoryImpl::DirectoryImpl(const String& path) : path_()
{
    char buffer[PATH_MAX];
    auto result = realpath(path.c_str(), buffer);
    if (!result)
    {
        String error = String("An error occurred when resolving the directory '") + path + String("': ") + strerror(errno);
        throw runtime_error(error);
    }

    path_ = result;
    dir_ = opendir(path_.c_str());
    if (!dir_)
    {
        String error = String("An error occurred when opening the directory '") + path_ + String("': ") + strerror(errno);
        throw runtime_error(error);
    }
}

DirectoryImpl::~DirectoryImpl()
{
    if (0 != closedir(dir_))
    {
        // Don't throw in destructor.
    }
}

// Accessors
String DirectoryImpl::path() const
{
    return path_;
}

// Mutators
File DirectoryImpl::file(const String& filename, FileMode mode) const
{
    auto size = filename.size();
    char* buffer = new char[size + 1];
    memcpy(buffer, filename.c_str(), size);
    buffer[size] = '\0';
    String baseFilename = basename(buffer);
    delete [] buffer;

    if (filename != baseFilename)
    {
        String error = String("An error occurred when creating the file '") + filename + String("' in the directory '") + path_ + String("'. The file name is invalid.");
        throw runtime_error(error);
    }

    String canonical = path_ + "/" + filename;

    // If the file doesn't exist, create it and fsync the directory.
    int fd = open(canonical.c_str(), O_RDONLY);
    if (-1 == fd)
    {
        if (ENOENT == errno)
        {
            // Create the new file
            auto result = creat(canonical.c_str(), S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
            if (-1 == result)
            {
                String error = String("An error occurred when creating the file '") + filename + String("' in the directory '") + path_ + String("'. The file could not be created: ") + strerror(errno);
                throw runtime_error(error);
            }

            // Close the newly created file.
            close(result);

            // Sync the directory.
            auto dirfd = open(path_.c_str(), O_RDONLY);
            if (-1 == dirfd)
            {
                String error = String("An error occurred when creating the file '") + filename + String("' in the directory '") + path_ + String("'. The directory entry could not be opened for synchronisation: ") + strerror(errno);
                throw runtime_error(error);
            }

            if (-1 == fsync(dirfd))
            {
                close(dirfd);
                String error = String("An error occurred when creating the file '") + filename + String("' in the directory '") + path_ + String("'. The directory could not be synchronised to disk: ") + strerror(errno);
                throw runtime_error(error);
            }

            close(dirfd);
        }
        else
        {
            String error = String("An error occurred when creating the file '") + filename + String("' in the directory '") + path_ + String("': ") + strerror(errno);
            throw runtime_error(error);
        }
    }
    else
    {
        close(fd);
    }

    return File(canonical, mode);
}

Directory DirectoryImpl::subdirectory(const String& p) const
{
    String absolutePath = path_ + "/" + p;
    DIR* dir = ::opendir(absolutePath.c_str());
    if (dir)
    {
        if (0 != closedir(dir))
        {
            String error = String("An error occurred when creating the directory '") + absolutePath + String("' in the directory '") + path_ + String("'. The directory already exists, but closing the directory after performing this test failed: ") + strerror(errno);
            throw runtime_error(error);
        }
    }
    else if (ENOENT != errno)
    {
        String error = String("An error occurred when creating the directory '") + absolutePath + String("' in the directory '") + path_ + String("': ") + strerror(errno);
        throw runtime_error(error);
    }
    else
    {
        auto mkdirResult = mkdir(absolutePath.c_str(), S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP);
        if (0 != mkdirResult)
        {
            String error = String("An error occurred when creating the directory '") + absolutePath + String("' in the directory '") + path_ + String("': ") + strerror(errno);
            throw runtime_error(error);
        }

        int dirfd = ::open(path_.c_str(), O_RDONLY);
        if (-1 == dirfd)
        {
            String error = String("An error occurred when creating the directory '") + absolutePath + String("' in the directory '") + path_ + String("'. Opening the parent directory for synchronisation failed: ") + strerror(errno);
            throw runtime_error(error);
        }

        if (-1 == fsync(dirfd))
        {
            close(dirfd);
            String error = String("An error occurred when creating the directory '") + absolutePath + String("' in the directory '") + path_ + String("'. Opening the parent directory for synchronisation failed: ") + strerror(errno);
            throw runtime_error(error);
        }

        close(dirfd);
    }

    return Directory(absolutePath);
}

POSIXFILESYSTEM_NAMESPACE_END


