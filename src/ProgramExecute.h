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
    ProgramExecute(const std::vector<std::string> &args, const std::string &inputRedirect,
                   const std::string &outputRedirect, const std::string &errorRedirect)
            : args(args), inputRedirect(inputRedirect), outputRedirect(outputRedirect),
              errorRedirect(errorRedirect) {}

    //default destructor
    ~ProgramExecute() {}

    void execute();

    const std::vector<std::string> &getArgs() const {
        return args;
    }

//    Pipe *getPipe() const {
//        return pipe;
//    }

    const std::string &getInputRedirect() const {
        return inputRedirect;
    }

    const std::string &getOutputRedirect() const {
        return outputRedirect;
    }

    const std::string &getErrorRedirect() const {
        return errorRedirect;
    }

private:
    std::vector<std::string> args;
//    Pipe* pipe;
//    int links

    std::string inputRedirect;
    std::string outputRedirect;
    std::string errorRedirect;

};


#endif //TURTLE_PROGRAM_H
