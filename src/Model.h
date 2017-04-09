//
// Created by sander on 4-4-17.
//

#ifndef TURTLE_MODEL_H
#define TURTLE_MODEL_H


#include <vector>
#include "Command.h"

class Model {
public:
    //constructor
    Model() {}

    //destructor
    ~Model() {

        //remove every programExecute
        for (std::vector<Command *>::iterator it = commands.begin(); it != commands.end(); ++it) {
            delete *it;
        }
    }

private:
    //vector filled with all commands
    std::vector<Command *> commands;

public:
    //adder
    void addCommand(Command *programExecute) {
        commands.push_back(programExecute);
    };

    //getter
    const std::vector<Command *> &getCommands() const {
        return commands;
    };

};


#endif //TURTLE_MODEL_H
