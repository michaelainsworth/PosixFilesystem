#include <PosixFilesystem/File.hpp>
#include <PosixFilesystem/Directory.hpp>
using PosixFilesystem::File;
using PosixFilesystem::Directory;
using PosixFilesystem::Write;
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, const char**argv)
{
    Directory directory(".");

    // Loop over all the file names specified on the command
    // line, creating files as appropriate.
    for (int i = 1; i < argc; ++i)
    {
        directory.file(argv[i], Write);
    }
     
    return EXIT_SUCCESS;
}
