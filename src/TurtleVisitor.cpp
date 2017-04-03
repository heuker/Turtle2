//
// Created by sander on 1-4-17.
//

#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include "TurtleVisitor.h"


string TurtleVisitor::getCwd(){
    char buff[PATH_MAX];
    getcwd(buff, PATH_MAX);
    string cwd(buff);
    return cwd;
}

antlrcpp::Any TurtleVisitor::visitStart(ShellGrammarParser::StartContext *context) {
    visitChildren(context);
    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitListWorkingDirectory(ShellGrammarParser::ListWorkingDirectoryContext *context) {
    char *argv[] = {"ls",  "-l", NULL};
    execvp("/bin/ls", argv);

    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitGetWorkingDirectory(ShellGrammarParser::GetWorkingDirectoryContext *context) {
    cout << workingDirectory << endl;
    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitChangeWorkingDirectory(ShellGrammarParser::ChangeWorkingDirectoryContext *context) {
    //get newDir
    string newDir = context->newDir->getText();

    //remove trailing forward slash
    if (newDir.length() != 1 && newDir.back() == '/') {
        newDir.pop_back();
    }

    //check if weŕe updating the entire path
    if (newDir[0] == '/' || newDir[0] == '~') {

        //change workingDirectory
        workingDirectory = newDir;

        //change program working directory
        int res = chdir(workingDirectory.c_str());

        //if program working directory could not be changed than reset workingDirectory
        if (res != 0){
            cout << "Whoops! " << strerror(errno) << endl;
            workingDirectory = getCwd();
        }

        return nullptr;

        //if its not a whole path than append new String
    } else {
        //if we need to go up
        if (newDir == ".." || newDir == "../") {
            //check if we're not at the top
            if (workingDirectory.length() == 1) {
                cout << "Already in root directory" << endl;
                return nullptr;
            }

            //remove directoryName till /
            while (workingDirectory.back() != '/') {
                workingDirectory.pop_back();
            }

            //and remove the /
            if (workingDirectory.length() != 1) {
                workingDirectory.pop_back();
            }

            //change program working directory
            int res = chdir(workingDirectory.c_str());

            //if program working directory could not be changed than reset workingDirectory
            if (res != 0){
                cout << "Whoops! " << strerror(errno) << endl;
                workingDirectory = getCwd();
            }

            return nullptr;
        }

        //append newDir to workingDirectory
        workingDirectory.append("/");
        workingDirectory.append(newDir);

        //change program working directory
        int res = chdir(workingDirectory.c_str());

        //if program working directory could not be changed than reset workingDirectory
        if (res != 0){
            cout << "Whoops! " << strerror(errno) << endl;
            workingDirectory = getCwd();
        }

        return nullptr;
    }

}

antlrcpp::Any TurtleVisitor::visitDerp(ShellGrammarParser::DerpContext *context) {
//    context->kabouter.
    return nullptr;
}


antlrcpp::Any TurtleVisitor::visitExecuteProgram(ShellGrammarParser::ExecuteProgramContext *context) {
    char *argv[] = {"ls",  "-l", NULL};

    if (context->buildIns() != nullptr) {
        return nullptr;
    }

    execvp(context->program->getText().c_str(), argv);

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
