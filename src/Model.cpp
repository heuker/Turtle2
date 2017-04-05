//
// Created by sander on 4-4-17.
//

#include "Model.h"

void Model::addProgramExecute(ProgramExecute* programExecute) {
    programExecutes.push_back(programExecute);
}

const std::vector<ProgramExecute*> &Model::getProgramExecutes() const {
    return programExecutes;
}
