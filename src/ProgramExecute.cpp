//
// Created by sander on 4-4-17.
//

#include <unistd.h>
#include <wait.h>
#include <iostream>
#include "ProgramExecute.h"

void ProgramExecute::execute(int prevOutPartOfPipe, int prevInPartOfPipe) {
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
            argv[i] = (char *) (*it).c_str();
            ++i;
        }

        std::cout << "in: " << inputRedirect << std::endl;
        std::cout << "out: " << outputRedirect << std::endl;
        std::cout << "errr: " << errorRedirect << std::endl;

        //add NULL to last index of the char array
        argv[pArgs.size()] = NULL;

        //if we're piping output to the inPart of the pipe
        if (inPartOfPipe != 0) {
            dup2(inPartOfPipe, 1);
            close(outPartOfPipe);
            close(inPartOfPipe);

            //if we're not piping output check if we're writing to a file
        } else if(outputRedirect != 0){
            std::cout << "This is an out file test." << std::endl;
            dup2(outputRedirect, 1);
            //todo check this
            close(outputRedirect);
        }


        //if we're piping input
        if (prevOutPartOfPipe != 0) {
            dup2(prevOutPartOfPipe, 0);
            close(prevOutPartOfPipe);
            close(prevInPartOfPipe);

            //if we're not piping input check if we're getting input from a file
        } else if(inputRedirect != 0){
            dup2(inputRedirect, 0);
            //todo check this
            close(inputRedirect);
        }

        //check if we're redirecting the error output
        if (errorRedirect != 0){
            dup2(errorRedirect, 2);
            //todo check this
            close(errorRedirect);
        }


        //execute program
        execvp((*pArgs.begin()).c_str(), argv);
    } else { //parent
        if (outPartOfPipe == 0) {
            if (!inBackGround) {
                waitpid(0, &returnValues, 0);
            }
        }
    }
}

int ProgramExecute::getOutPartOfPipe() const {
    return outPartOfPipe;
}

int ProgramExecute::getInPartOfPipe() const {
    return inPartOfPipe;
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
                                                                                           outPartOfPipe(inputPipe),
                                                                                           inPartOfPipe(outputPipe),
                                                                                           inputRedirect(inputRedirect),
                                                                                           outputRedirect(
                                                                                                   outputRedirect),
                                                                                           errorRedirect(
                                                                                                   errorRedirect) {}