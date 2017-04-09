//
// Command class
//

#ifndef TURTLE_PROGRAM_H
#define TURTLE_PROGRAM_H

#include <string>
#include <vector>

class Command {
public:
    //constructor
    Command(const std::vector<std::string> &args, bool inBackGround, int inputPipe, int outputPipe,
            int inputRedirect, int outputRedirect, int errorRedirect);


    //default destructor
    ~Command() {}

    //executes the command
    void execute(int prevOutPartOfPipe, int prevInPartOfPipe);


    //gettters
    const std::vector<std::string> &getArgs() const {
        return args;
    }

    int getOutPartOfPipe() const;

    int getInPartOfPipe() const;

private:
    //list of arguments
    std::vector<std::string> args;

    bool inBackGround;

    int outPartOfPipe;
    int inPartOfPipe;

    int inputRedirect;
    int outputRedirect;
    int errorRedirect;

};


#endif //TURTLE_PROGRAM_H
