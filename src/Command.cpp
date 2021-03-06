//
// Command class
//

#include <unistd.h>
#include <wait.h>
#include <iostream>
#include <cstring>
#include "Command.h"

/**
 * Executes this command
 * @param prevOutPartOfPipe outPartOfPipe of previous command default 0
 * @param prevInPartOfPipe inPartOfPipe of previous command default 0
 */
void Command::execute(int prevOutPartOfPipe, int prevInPartOfPipe) {
    int returnValues;

    //fork new proces, let child run execvp
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

        //add NULL to last index of the char array
        argv[pArgs.size()] = NULL;

        //if we're piping output to the inPart of the pipe
        if (inPartOfPipe != 0) {
            dup2(inPartOfPipe, 1);

            //no longer needed
            close(outPartOfPipe);
            close(inPartOfPipe);

            //if we're not piping output check if we're writing to a file
        } else if (outputRedirect != 0) {
            dup2(outputRedirect, 1);

            //no longer needed
            close(outputRedirect);
        }


        //if we're piping input
        if (prevOutPartOfPipe != 0) {
            dup2(prevOutPartOfPipe, 0);

            //no longer needed
            close(prevOutPartOfPipe);
            close(prevInPartOfPipe);

            //if we're not piping input check if we're getting input from a file
        } else if (inputRedirect != 0) {
            dup2(inputRedirect, 0);

            //no longer needed
            close(inputRedirect);
        }

        //check if we're redirecting the error output
        if (errorRedirect != 0) {
            dup2(errorRedirect, 2);

            //no longer needed
            close(errorRedirect);
        }

        //execute program
        execvp((*pArgs.begin()).c_str(), argv);

    } else { //parent
        if (outPartOfPipe == 0) {
            //if not inbackground command
            if (!inBackGround) {
                //wait on child
                waitpid(0, &returnValues, 0);
            }
        }
    }
}


//getters
int Command::getOutPartOfPipe() const {
    return outPartOfPipe;
}

int Command::getInPartOfPipe() const {
    return inPartOfPipe;
}

//constructor
Command::Command(const std::vector<std::string> &args, bool inBackGround, int inputPipe, int outputPipe,
                 int inputRedirect, int outputRedirect, int errorRedirect)
        : args(args), inBackGround(inBackGround), outPartOfPipe(inputPipe), inPartOfPipe(outputPipe),
          inputRedirect(inputRedirect), outputRedirect(outputRedirect), errorRedirect(errorRedirect) {}