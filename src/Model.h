//
// Created by sander on 4-4-17.
//

#ifndef TURTLE_MODEL_H
#define TURTLE_MODEL_H


#include <vector>
#include "ProgramExecute.h"

class Model {
public:
    //constructor
    Model()
    {}

    //destructor
    ~Model(){

        //remove every programExecute
        for (std::vector<ProgramExecute*>::iterator it = programExecutes.begin(); it != programExecutes.end(); ++it) {
            delete *it;
        }
    }

private:
    //vector filled with all programExecutes
    std::vector<ProgramExecute*> programExecutes;

public:
    void addProgramExecute(ProgramExecute* programExecute){
        programExecutes.push_back(programExecute);
    };

    const std::vector<ProgramExecute*> &getProgramExecutes() const{
        return programExecutes;
    };

};


#endif //TURTLE_MODEL_H
