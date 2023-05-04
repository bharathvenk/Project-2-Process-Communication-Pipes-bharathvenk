

#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

#include "Project2MultiProcessModifier.h"
#include "FileCopier.h"
#include "FileModifyException.h"

void Project2MultiProcessModifier::modifyAndCopyFile(IOType ioType, const char* sourceFile, const char* destFile) {
    if (ioType == IOType::WRITE) {
        int fd[2];
        pipe(fd);
        pid_t procid = fork();
        if (procid == 0) {
            close(fd[0]);
            try {
                FileCopier::makeCopy(STDIN_FILENO, destFile);
            } catch (FileModifyException& e) {
                std::cerr << "error modifying file: " << e.what() << std::endl;
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        } else if (procid == -1) {
            std::cerr << "fork failed" << std::endl;
            exit(EXIT_FAILURE);
        } else {
            close(fd[1]);
            waitpid(procid, nullptr, 0);
        }
    } else if (ioType == IOType::READ) {
        int fd[2];
        pipe(fd);
        pid_t procid = fork();
        if (procid == 0) {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            execl("./Project2", "Project2", "W", nullptr);
            std::cerr << "Error: execl() failed" << std::endl;
            exit(EXIT_FAILURE);
        } else if (procid == -1) {
            std::cerr << "fork failed" << std::endl;
            exit(EXIT_FAILURE);
        } else {
            close(fd[0]);
            try {
                FileCopier::makeCopy(sourceFile, fd[1]);
            } catch (FileModifyException& e) {
                std::cerr << "errormodifying file: " << e.what() << std::endl;
                exit(EXIT_FAILURE);
            }
            waitpid(procid, nullptr, 0);
        }
    }
}


