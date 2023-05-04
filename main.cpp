#include <iostream>
#include <unistd.h>

#include "FileChecker.h"
#include "FileModifyException.h"
#include "Project2MultiProcessModifier.h"
#include "Util.h"

//---------------------------------------------------------
// Arguments:
// IOType: No argment == (read from input file, write to the pipe)
//         'W' (read from the pipe, write to the output file)
//
//--------------------------------------------------------
int main(int argc, char** argv) {
    // Delete the output file so we're starting fresh
    unlink(Util::outputFilename);

    IOType ioType;

    if ( argc < 2) {
        ioType = IOType::READ;
    } else {
        try {
            ioType = Util::toIOType(argv[1][0]);
        } catch (FileModifyException e) {
            std::cerr << "Unable to determine I/O type of " << argv[1] << ": " << e.what() << "\n" << Util::usage;
        } catch (std::exception e) {
            std::cerr << "Is " << argv[1] << " a character? Couldn't convert it to an IOType\n" << Util::usage;
        }
    }

    Project2MultiProcessModifier modifier;
    try {
        modifier.modifyAndCopyFile(ioType, Util::inputFilename, Util::outputFilename);
    } catch (FileModifyException e) {
        std::cerr << "Error modifying file: " << e.what();
        exit(1);
    } catch ( std::exception e) {
        std::cerr << "Error modifying file: " << e.what();
        exit(1);
    }

    try {
        FileChecker::checkFile();
    } catch (std::exception e) {
        std::cerr << "File doesn't match" << std::endl;
        exit(1);
    }
}
