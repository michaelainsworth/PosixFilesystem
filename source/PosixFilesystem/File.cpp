#include <PosixFilesystem/File.hpp>
#include <PosixFilesystem/FileImpl.hpp>

using std::logic_error;

POSIXFILESYSTEM_NAMESPACE_BEGIN

// Lifecycle
File::File(const String& path, FileMode mode) :
    pFileImpl_(new FileImpl(path, mode))
{
    if (!(mode & Read) && !(mode & Write))
    {
        throw logic_error("The file could not be created because the file mode was invalid.");
    }
}

// Accessors
String File::path() const
{
    return pFileImpl_->path();
}

FileMode File::mode() const
{
    return pFileImpl_->mode();
}

// Mutators
size_t File::read(Byte* buffer, size_t bytes)
{
    return pFileImpl_->read(buffer, bytes);
}

void File::write(const Byte* buffer, size_t bytes)
{
    return pFileImpl_->write(buffer, bytes);
}

size_t File::size()
{
    return pFileImpl_->size();
}

void File::seek(size_t offset)
{
    pFileImpl_->seek(offset);
}

void File::flush()
{
    pFileImpl_->flush();
}

void File::lock(const Callback& callback)
{
    pFileImpl_->lock(callback);
}


POSIXFILESYSTEM_NAMESPACE_END
