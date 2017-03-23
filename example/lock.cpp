#include <PosixFilesystem/File.hpp>
#include <PosixFilesystem/Directory.hpp>
using PosixFilesystem::File;
using PosixFilesystem::Directory;
using PosixFilesystem::Write;
#include <iostream>
#include <thread>
#include <chrono>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
#include <cstdlib>
#include <stdexcept>
using std::runtime_error;
using std::exception;
#include <string>
using std::string;
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;

int main(int argc, const char**argv)
{
    try
    {
        Directory directory(".");

        if (4 != argc)
        {
            throw runtime_error("You must supply exactly three arguments.\n"
                                "The first is the file to write to.\n"
                                "The second is the message to write to the file.\n"
                                "The third is the number of seconds to sleep for.\n"
                                "after writing to the file.\n");
        }

        string filename = argv[1];
        string message = argv[2];
        unsigned int sleep = lexical_cast<unsigned int>(argv[3]);

        File file = directory.file(filename, Write);
        file.lock([&file, &message, sleep](){
            file.write(reinterpret_cast<const File::Byte*>(message.c_str()),
                    message.length());
            std::this_thread::sleep_for (std::chrono::seconds(sleep));
        });

        return EXIT_SUCCESS;
    }
    catch (const exception& e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
}
