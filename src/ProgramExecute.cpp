//
// Created by sander on 4-4-17.
//

#include <unistd.h>
#include <wait.h>
#include "ProgramExecute.h"

void ProgramExecute::execute() {
    int returnValues;
    int cid = fork();
    if (cid == 0) {
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

        //execute program
        execvp( (* pArgs.begin()).c_str(), argv);
    } else {
        waitpid(cid, &returnValues, 0);
    }
}
