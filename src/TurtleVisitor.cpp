//
// Created by sander on 1-4-17.
//

#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include "TurtleVisitor.h"

/**
 * Gets the working directory of the program
 * @return cwd of program
 */
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

antlrcpp::Any TurtleVisitor::visitStartProgram(ShellGrammarParser::StartProgramContext *context) {
    vector<string> args;
    //push programName to the first parameter in argument list
    args.push_back(context->program->getText());

    vector<ShellGrammarParser::ArgumentContext*> arguments = context->argument();

    //push every parameter to argument list
    for (vector<ShellGrammarParser::ArgumentContext *>::iterator it = arguments.begin(); it != arguments.end(); ++it) {
        string arg = visitArgument(*it);
        args.push_back(arg);
    }

    //todo visit IoRedirect here
    int input = 0, output = 0, err = 0;
    pair<string,int> pair;
    vector<ShellGrammarParser::IORedirectContext *> ioRedirectVector = context->iORedirect();
    for (vector<ShellGrammarParser::IORedirectContext *>::iterator it = ioRedirectVector.begin();
            it != ioRedirectVector.end(); ++it)
    {
        pair = visitIORedirect(*it);

        if (pair.first == ">" || pair.first == ">>")
        {
            cout << pair.second << endl;
            output = pair.second;
        } else if (pair.first == "2>")
        {
            err = pair.second;
        } else if (pair.first == "<")
        {
            input = pair.second;
        }
    }

    //see wheter we have to make a pipe or not
    if (context->startProgram().size() != 0){
        int p[2];
        pipe(p);
        model->addProgramExecute(new ProgramExecute(args, inBackground, p[0], p[1], input, output, err));
    } else {
        model->addProgramExecute(new ProgramExecute(args, inBackground, 0, 0, input, output, err));
    }
    cout << output;

    //change inBackground
    inBackground = context->background != nullptr;

    //visit programs piped to
    vector<ShellGrammarParser::StartProgramContext *> startProgramVector = context->startProgram();
    for (vector<ShellGrammarParser::StartProgramContext *>::iterator it = startProgramVector.begin();
         it != startProgramVector.end(); ++it)
    {
        visitStartProgram(*it);
    }
    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitArgument(ShellGrammarParser::ArgumentContext *context) {
    return context->getText();
}

antlrcpp::Any TurtleVisitor::visitIORedirect(ShellGrammarParser::IORedirectContext *context) {
    string op(context->op->getText());
    string filename = context->fileName->getText();
    pair<string,int> returnPair;

    if (op == ">")
    {
        returnPair = make_pair<string,int>(context->op->getText(), open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC));
    } else if (op == ">>")
    {
        returnPair = make_pair<string,int>(context->op->getText(), open(filename.c_str(), O_APPEND | O_CREAT));
    } else if (op == "2>")
    {
        returnPair = make_pair<string,int>(context->op->getText(), open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC));
    } else if (op == "<")
    {
        returnPair = make_pair<string,int>(context->op->getText(), open(filename.c_str(), O_RDONLY));
    }

    return returnPair;
}

TurtleVisitor::~TurtleVisitor() {

}
