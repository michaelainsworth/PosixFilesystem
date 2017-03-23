#ifndef POSIXFILESYSTEM_FILE_HPP
#define POSIXFILESYSTEM_FILE_HPP

#include <PosixFilesystem/Common.hpp>
#include <PosixFilesystem/FileMode.hpp>
#include <functional>

POSIXFILESYSTEM_NAMESPACE_BEGIN

class File
{
public:

    // Typedef
    typedef uint8_t Byte;
    typedef std::function<void()> Callback;

    // Lifecycle
    File(const String& path, FileMode mode);

    // Accessors
    String path() const;
    FileMode mode() const;

    // Mutators
    size_t read(Byte* buffer, size_t bytes);
    void write(const Byte* buffer, size_t bytes);
    void seek(size_t offset);
    size_t size();
    void flush();
    void lock(const Callback& callback);

private:

    // Variables
    SharedFileImplPointer pFileImpl_;

};

POSIXFILESYSTEM_NAMESPACE_END

#endif // POSIXFILESYSTEM_FILE_HPP

