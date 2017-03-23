#include <PosixFilesystem/File.hpp>
#include <PosixFilesystem/Directory.hpp>
using PosixFilesystem::File;
using PosixFilesystem::Directory;
using PosixFilesystem::Read;
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, const char**argv)
{
    Directory directory(".");

    // Loop over all the file names specified on the command
    // line, and write the output.
    for (int i = 1; i < argc; ++i)
    {
        File file = directory.file(argv[i], Read);
        for (size_t k = 0, s = file.size(); k < s; ++k)
        {
            char c;
            file.read(reinterpret_cast<File::Byte*>(&c), 1);
            cout.write(&c, 1);
        }
    }
     
    return EXIT_SUCCESS;
}
