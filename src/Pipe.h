//
// Created by sander on 5-4-17.
//

#ifndef TURTLE_PIPE_H
#define TURTLE_PIPE_H


#include <vector>
class ProgramExecute;

class Pipe {
private:
    std::vector<ProgramExecute*> commands;

public:
    Pipe(std::vector<ProgramExecute*> commands){
        this->commands = commands;
    }

    const std::vector<ProgramExecute*> &getCommands() const {
        return commands;
    }
};


#endif //TURTLE_PIPE_H
