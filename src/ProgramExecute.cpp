//
// Created by sander on 4-4-17.
//

#include <unistd.h>
#include <wait.h>
#include <iostream>
#include "ProgramExecute.h"

void ProgramExecute::execute(int prevInputPipe, int prevOutputPipe) {
    int returnValues;
    int cid = fork();
    if (cid == 0) { //child
        //get arguments
        std::vector<std::string> pArgs = getArgs();

        //make new char array
        char *argv[pArgs.size() + 1];

        //make counter
        int i = 0;

        //transfer all arguments
        for (std::vector<std::string>::iterator it = pArgs.begin(); it != pArgs.end(); ++it) {
            std::string temp = *it;

            argv[i] = (char *) temp.c_str();
            ++i;
        }

        //add NULL to last index of the char array
        argv[pArgs.size()] = NULL;

        //if we're piping output
        if (inputPipe != 0) {
//            int t[2];
//            pipe(t);
//            std::cout << "foute0: " << t[0] << "foute1: " << t[1] << std::endl;
//            std::cout << "pipe not null" << std::endl;
//            std::cout << "inputPipe: " << inputPipe << std::endl;
//            std::cout << "outputPipe: " << outputPipe << std::endl;
            dup2(outputPipe, 1);
//            std::cout << "test1" << std::endl;
            close(inputPipe);
//            std::cout << "test2" << std::endl;
            close(outputPipe);
//            std::cout << "test3" << std::endl;
        }

//        std::cout << "test" << std::endl;

        //if we're piping input
        if (prevInputPipe != 0) {
//            std::cout << "prev pipe not null" << std::endl;
            dup2(prevInputPipe, 0);
            close(prevInputPipe);
            close(prevOutputPipe);

        }

//        std::cout << "testtest" << std::endl;

        //execute program
        execvp((*pArgs.begin()).c_str(), argv);
    } else { //parent
        if (inputPipe == 0) {
            waitpid(cid, &returnValues, 0);
        }
    }
}

ProgramExecute::ProgramExecute(const std::vector<std::string> &args, int inputPipe, int outputPipe, const std::string &inputRedirect, const std::string &outputRedirect, const std::string &errorRedirect)
        : args(args), inputPipe(inputPipe), outputPipe(outputPipe), inputRedirect(inputRedirect), outputRedirect(outputRedirect), errorRedirect(errorRedirect) {}

int ProgramExecute::getInputPipe() const {
    return inputPipe;
}

int ProgramExecute::getOutputPipe() const {
    return outputPipe;
}
