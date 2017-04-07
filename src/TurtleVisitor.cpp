//
// Created by sander on 1-4-17.
//

#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include "TurtleVisitor.h"


string TurtleVisitor::getCwd() {
    char buff[PATH_MAX];
    getcwd(buff, PATH_MAX);
    string cwd(buff);
    return cwd;
}

antlrcpp::Any TurtleVisitor::visitStart(ShellGrammarParser::StartContext *context) {
    model = new Model();

    visitChildren(context);

    return model;
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

        //if program working directory could not be changed than show the error
        if (res != 0) {
            cout << "Whoops! " << strerror(errno) << endl;
        }

        //if its not a whole path than append new String
    } else {
        workingDirectory.append("/");
        workingDirectory.append(newDir);

        //change program working directory
        int res = chdir(workingDirectory.c_str());

        //if program working directory could not be changed than show the error
        if (res != 0) {
            cout << "Whoops! " << strerror(errno) << endl;
        }
    }

    //update workingDirectory
    workingDirectory = getCwd();
    return nullptr;

}


antlrcpp::Any TurtleVisitor::visitExecuteProgram(ShellGrammarParser::ExecuteProgramContext *context) {
    vector<string> args;
    //push programName to the first parameter in argument list
    args.push_back(context->program->getText());

    vector<ShellGrammarParser::ArgumentContext*> arguments = context->argument();

    //push every parameter to argument list
    for (vector<ShellGrammarParser::ArgumentContext *>::iterator it = arguments.begin(); it != arguments.end(); ++it) {
        string arg = visitArgument(*it);
        args.push_back(arg);
    }

    //see wheter we have to make a pipe or not
    if (context->startProgram().size() != 0){
        cout << "with pipes" << endl;
        int p[2];
        pipe(p);
        model->addProgramExecute(new ProgramExecute(args, p[0], p[1], "", "", ""));
    } else {
        cout << "without pipes" << endl;
        model->addProgramExecute(new ProgramExecute(args, 0, 0, "", "", ""));
    }

    //visit children
    visitChildren(context);
    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitArgument(ShellGrammarParser::ArgumentContext *context) {
    return context->getText();
}

antlrcpp::Any TurtleVisitor::visitIORedirect(ShellGrammarParser::IORedirectContext *context) {
    return nullptr;
}

TurtleVisitor::~TurtleVisitor() {

}
