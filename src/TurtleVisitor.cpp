//
// Created by sander on 1-4-17.
//

#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <wait.h>
#include "TurtleVisitor.h"


string TurtleVisitor::getCwd() {
    char buff[PATH_MAX];
    getcwd(buff, PATH_MAX);
    string cwd(buff);
    return cwd;
}

antlrcpp::Any TurtleVisitor::visitStart(ShellGrammarParser::StartContext *context) {
    visitChildren(context);

    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitGetWorkingDirectory(ShellGrammarParser::GetWorkingDirectoryContext *context) {
    cout << workingDirectory << endl;
    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitChangeWorkingDirectory(ShellGrammarParser::ChangeWorkingDirectoryContext *context) {
    //get newDir
    string newDir = context->newDir->getText();

    //check if weŕe updating the entire path
    if (newDir[0] == '/' || newDir[0] == '~') {

        //change program working directory
        int res = chdir(newDir.c_str());

        //if program working directory could not be changed than reset workingDirectory
        if (res != 0) {
            cout << "Whoops! " << strerror(errno) << endl;
        }

        //if its not a whole path than append new String
    } else {
        workingDirectory.append("/");
        workingDirectory.append(newDir);

        //change program working directory
        int res = chdir(workingDirectory.c_str());

        //if program working directory could not be changed than reset workingDirectory
        if (res != 0) {
            cout << "Whoops! " << strerror(errno) << endl;
        }
    }

    workingDirectory = getCwd();
    return nullptr;

}


antlrcpp::Any TurtleVisitor::visitExecuteProgram(ShellGrammarParser::ExecuteProgramContext *context) {
    int returnValues;
    int cid = fork();
    if (cid == 0) {
        char *argv[] = {(char *) context->program->getText().c_str(), NULL};
        execvp((char *) context->program->getText().c_str(), argv);
    } else {
        waitpid(cid, & returnValues , 0);
    }

    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitIORedirect(ShellGrammarParser::IORedirectContext *context) {
    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitProgramPipedTo(ShellGrammarParser::ProgramPipedToContext *context) {
    return nullptr;
}

TurtleVisitor::~TurtleVisitor() {

}
