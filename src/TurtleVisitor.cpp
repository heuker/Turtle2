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

    vector<ShellGrammarParser::ArgumentContext *> arguments = context->argument();

    //push every parameter to argument list
    for (vector<ShellGrammarParser::ArgumentContext *>::iterator it = arguments.begin(); it != arguments.end(); ++it) {
        string arg = visitArgument(*it);
        args.push_back(arg);
    }

    //default values of I/O redirects
    int input = 0, output = 0, err = 0;
    pair<string, int> pair;

    //get all I/O redirects for this command and visit them
    vector<ShellGrammarParser::IORedirectContext *> ioRedirectVector = context->iORedirect();
    for (vector<ShellGrammarParser::IORedirectContext *>::iterator it = ioRedirectVector.begin();
         it != ioRedirectVector.end(); ++it) {

        pair = visitIORedirect(*it);

        //load file descriptor in correct variable
        if (pair.first == ">" || pair.first == ">>") {
            output = pair.second;
        } else if (pair.first == "2>") {
            err = pair.second;
        } else if (pair.first == "<") {
            input = pair.second;
        }
    }

    //see wheter we have to make a pipe or not
    if (context->startProgram().size() != 0) {
        //make new pipe
        int p[2];
        pipe(p);

        //add new command with pipe
        model->addCommand(new Command(args, inBackground, p[0], p[1], input, output, err));
    } else {
        //add new command without pipe
        model->addCommand(new Command(args, inBackground, 0, 0, input, output, err));
    }

    //change inBackground
    inBackground = context->background != nullptr;

    //visit programs piped to
    vector<ShellGrammarParser::StartProgramContext *> startProgramVector = context->startProgram();
    for (vector<ShellGrammarParser::StartProgramContext *>::iterator it = startProgramVector.begin();
         it != startProgramVector.end(); ++it) {
        visitStartProgram(*it);
    }

    //return
    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitArgument(ShellGrammarParser::ArgumentContext *context) {
    //return the argument
    return context->getText();
}

antlrcpp::Any TurtleVisitor::visitIORedirect(ShellGrammarParser::IORedirectContext *context) {
    //get operator
    string op(context->op->getText());

    //get filename
    string filename = context->fileName->getText();

    //make a new pair depending on operator, open file with fitting permissions
    pair<string, int> returnPair;
    if (op == ">") {
        returnPair = make_pair<string, int>(context->op->getText(),
                                            open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666));
    } else if (op == ">>") {
        returnPair = make_pair<string, int>(context->op->getText(), open(filename.c_str(), O_WRONLY | O_APPEND, 0666));
    } else if (op == "2>") {
        returnPair = make_pair<string, int>(context->op->getText(),
                                            open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666));
    } else if (op == "<") {
        returnPair = make_pair<string, int>(context->op->getText(), open(filename.c_str(), O_RDONLY, 0666));
    }

    //return the made pair
    return returnPair;
}

//destructor
TurtleVisitor::~TurtleVisitor() {}