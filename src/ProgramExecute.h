//
// Created by sander on 4-4-17.
//

#ifndef TURTLE_PROGRAM_H
#define TURTLE_PROGRAM_H

#include <string>
#include <vector>

class ProgramExecute {
public:
    ProgramExecute(std::vector<std::string> args, bool pipedTo, bool pipedFrom)
    {
        this->args = args;
        this->pipedTo = pipedTo;
        this->pipedFrom = pipedFrom;
    }

    //defaul destructor
    ~ProgramExecute(){
    }

    const std::vector<std::string> &getArgs() const {
        return args;
    }

    bool isPipedTo() const {
        return pipedTo;
    }

    bool isPipedFrom() const {
        return pipedFrom;
    }

private:
    std::vector<std::string> args;
    bool pipedTo = false;
    bool pipedFrom = false;
};


#endif //TURTLE_PROGRAM_H
