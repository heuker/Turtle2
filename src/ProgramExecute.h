//
// Created by sander on 4-4-17.
//

#ifndef TURTLE_PROGRAM_H
#define TURTLE_PROGRAM_H

#include <string>
#include <vector>
#include "Pipe.h"

class ProgramExecute {
public:
    ProgramExecute(const std::vector<std::string> &args, bool inBackGround, int inputPipe, int outputPipe,
                   int inputRedirect, int outputRedirect, int errorRedirect);


    //default destructor
    ~ProgramExecute() {}

    void execute(int prevInputPipe, int prevOutputPipe);

    const std::vector<std::string> &getArgs() const {
        return args;
    }

    int getInputPipe() const;

    int getOutputPipe() const;

    int getInputRedirect() const;

    int getOutputRedirect() const;

    int getErrorRedirect() const;

private:
    std::vector<std::string> args;

    bool inBackGround;

    int inputPipe;
    int outputPipe;

    int inputRedirect;
    int outputRedirect;
    int errorRedirect;

};


#endif //TURTLE_PROGRAM_H
