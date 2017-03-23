#include <PosixFilesystem/FileImpl.hpp>

#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

using std::strerror;
using std::runtime_error;

POSIXFILESYSTEM_NAMESPACE_BEGIN

// Lifecycle
FileImpl::FileImpl(const String& path, FileMode mode) :
    path_(path),
    mode_(mode),
    fd_(0)
{
    int flags = 0;
    if (mode_ & Read && !(mode_ & Write))
    {
        flags = O_RDONLY;
    }
    else if (mode_ & Write && !(mode_ & Read))
    {
        flags = O_WRONLY;
    }
    else
    {
        flags = O_RDWR;
    }

    fd_ = ::open(path_.c_str(), flags);
    if (-1 == fd_)
    {
        throw runtime_error(String("An error occurred when opening thefile '") + path + String("': ") + strerror(errno));
    }
}

FileImpl::~FileImpl()
{
    if (0 != ::close(fd_))
    {
        // Ignore error.
    }
}

// Accessors
FileMode FileImpl::mode() const
{
    return mode_;
}

String FileImpl::path() const
{
    return path_;
}

// Mutators
size_t FileImpl::read(Byte* buffer, size_t bytes)
{
    auto pointer = &buffer[0];
    auto totalBytesRead = 0;
    while (bytes)
    {
        auto bytesRead = ::read(fd_, pointer, bytes);
        if (0 == bytesRead)
        {
            break;
        }

        if (-1 == bytesRead)
        {
            String error = String("An error occurred when reading the contents of the file '") + path_ + String("': ") + strerror(errno);
            throw runtime_error(error);
        }

        totalBytesRead += bytesRead;

        bytes -= bytesRead;
        pointer += bytesRead;
    }

    return totalBytesRead;
}

void FileImpl::write(const Byte* buffer, size_t bytes)
{
    if (!bytes)
    {
        return;
    }

    auto pointer = &buffer[0];
    auto bytesToWrite = bytes;

    while (bytesToWrite)
    {
        auto bytesWritten = ::write(fd_, pointer, bytesToWrite);
        if (-1 == bytesWritten)
        {
            String error = String("An error occurred when writing to the file '") + path_ + String("': ") + strerror(errno);
            throw runtime_error(error);
        }

        bytesToWrite -= bytesWritten;
        pointer += bytesWritten;
    }
}

size_t FileImpl::size()
{
    struct stat st;
    auto result = fstat(fd_, &st);
    if (-1 == result)
    {
        throw runtime_error("An error occurred when trying to obtain the size of the file '" + path_ + "': " + String(strerror(errno)));
    }
    return st.st_size;
}

void FileImpl::seek(size_t offset)
{
    auto result = lseek(fd_, offset, SEEK_SET);
    if (-1 == result)
    {
        String error = String("An error occurred when seeking to an offset in file '") + path_ + String("': ") + strerror(errno);
        throw runtime_error(error);
    }
}

void FileImpl::flush()
{
    if (-1 == fsync(fd_))
    {
        String error = String("An error occurred when flushing the contents of the file '") + path_ + "' to disk: " + String(strerror(errno));
        throw runtime_error(error);
    }
}

// TODO: Add basename and dirname to this class (and facade).

void FileImpl::lock(const Callback& callback)
{
    struct flock l;

    if (mode_ & Write)
    {
        l.l_type = F_WRLCK;
    }
    else
    {
        l.l_type = F_RDLCK;
    }

    l.l_whence = SEEK_SET;
    l.l_start = 0;
    l.l_len = 0;
    l.l_pid = getpid();

    int lockResult = fcntl(fd_, F_SETLKW, &l);
    if (0 != lockResult)
    {
        String error = String("An error occurred when obtaining an exclusive write lock on '") + path_ + String("': ") + strerror(errno);
        throw runtime_error(error);
    }

    try
    {
        // Run the callback.
        callback();

        // Unlock the file before returning.
        l.l_type = F_UNLCK;
        if (0 != fcntl(fd_, F_SETLKW, &l))
        {
            // Ignore error.
        }
    }
    catch (...)
    {
        // Unlock the file.
        l.l_type = F_UNLCK;
        if (0 != fcntl(fd_, F_SETLKW, &l))
        {
            // Ignore error.
        }

        // Make sure the exception bubbles up.
        throw;
    }
}

POSIXFILESYSTEM_NAMESPACE_END

