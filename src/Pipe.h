//
// Created by sander on 5-4-17.
//

#ifndef TURTLE_PIPE_H
#define TURTLE_PIPE_H


#include <vector>
#include <unistd.h>

class ProgramExecute;

class Pipe {
private:
    int p[2];


public:
    Pipe(){
        pipe(p);
    }

    const int getInput() const {
        return p[0];
    }

    const int getOutput() const {
        return p[1];
    }
};


#endif //TURTLE_PIPE_H
