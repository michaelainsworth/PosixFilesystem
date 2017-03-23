#ifndef POSIXFILESYSTEM_FILEIMPL_HPP
#define POSIXFILESYSTEM_FILEIMPL_HPP

#include <PosixFilesystem/FileMode.hpp>
#include <PosixFilesystem/Common.hpp>

struct flock;

POSIXFILESYSTEM_NAMESPACE_BEGIN

class FileImpl
{
public:

    // Typedefs
    typedef uint8_t Byte;
    typedef std::function<void()> Callback;

    // Lifecycle
    FileImpl(const String& path, FileMode mode);
    FileImpl(const FileImpl&) = delete;
    FileImpl(FileImpl&&) = delete;
    FileImpl& operator =(const FileImpl&) = delete;
    FileImpl& operator =(FileImpl&&) = delete;
    ~FileImpl();

    // Accessors
    FileMode mode() const;
    String path() const;

    // Mutators
    size_t read(Byte* buffer, size_t bytes);
    void write(const Byte* buffer, size_t bytes);
    void seek(size_t offset);
    size_t size();
    void flush();
    void lock(const Callback& callback);

private:

    // Variables
    String path_;
    FileMode mode_;
    int fd_;

};

POSIXFILESYSTEM_NAMESPACE_END

#endif // POSIXFILESYSTEM_FILEIMPL_HPP

