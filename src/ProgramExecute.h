//
// Created by sander on 4-4-17.
//

#ifndef TURTLE_PROGRAM_H
#define TURTLE_PROGRAM_H

#include <string>
#include <vector>

class ProgramExecute {
public:
    ProgramExecute(const std::vector<std::string> &args, bool inBackGround, int inputPipe, int outputPipe,
                   int inputRedirect, int outputRedirect, int errorRedirect);


    //default destructor
    ~ProgramExecute() {}

    void execute(int prevOutPartOfPipe, int prevInPartOfPipe);

    const std::vector<std::string> &getArgs() const {
        return args;
    }

    int getOutPartOfPipe() const;

    int getInPartOfPipe() const;

private:
    std::vector<std::string> args;

    bool inBackGround;

    int outPartOfPipe;
    int inPartOfPipe;

    int inputRedirect;
    int outputRedirect;
    int errorRedirect;

};


#endif //TURTLE_PROGRAM_H
