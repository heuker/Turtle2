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
//            std::string temp = *it; todo remove

            argv[i] = (char *) (*it).c_str();
            ++i;
        }

        //add NULL to last index of the char array
        argv[pArgs.size()] = NULL;

        //if we're piping output
        if (inputPipe != 0) {
            dup2(outputPipe, 1);
            close(inputPipe);
            close(outputPipe);
        }


        //if we're piping input
        if (prevInputPipe != 0) {
            dup2(prevInputPipe, 0);
            close(prevInputPipe);
            close(prevOutputPipe);

        }

        //execute program
        execvp((*pArgs.begin()).c_str(), argv);
    } else { //parent
        if (inputPipe == 0) {
            if (!inBackGround) {
                waitpid(0, &returnValues, 0);
            }
        }
    }
}

int ProgramExecute::getInputPipe() const {
    return inputPipe;
}

int ProgramExecute::getOutputPipe() const {
    return outputPipe;
}

int ProgramExecute::getInputRedirect() const {
    return inputRedirect;
}

int ProgramExecute::getOutputRedirect() const {
    return outputRedirect;
}

int ProgramExecute::getErrorRedirect() const {
    return errorRedirect;
}

ProgramExecute::ProgramExecute(const std::vector<std::string> &args, bool inBackGround, int inputPipe, int outputPipe,
                               int inputRedirect, int outputRedirect, int errorRedirect) : args(args),
                                                                                           inBackGround(inBackGround),
                                                                                           inputPipe(inputPipe),
                                                                                           outputPipe(outputPipe),
                                                                                           inputRedirect(inputRedirect),
                                                                                           outputRedirect(
                                                                                                   outputRedirect),
                                                                                           errorRedirect(
                                                                                                   errorRedirect) {}
