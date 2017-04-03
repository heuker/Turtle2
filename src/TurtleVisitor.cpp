//
// Created by sander on 1-4-17.
//

#include <dirent.h>
#include "TurtleVisitor.h"

static string workingDirectory = "/home/sander";

antlrcpp::Any TurtleVisitor::visitStart(ShellGrammarParser::StartContext *context) {
    visitChildren(context);

    cout << workingDirectory << " $ ";
    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitListWorkingDirectory(ShellGrammarParser::ListWorkingDirectoryContext *context) {
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

        DIR *dir = opendir(&newDir[0]);
        //check if directory exists, if not print error and don't change the working directory
        if (!dir) {
            cout << newDir << " does not exists" << endl;
            return nullptr;
        }

        //change workingDirectory
        workingDirectory = newDir;
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


            return nullptr;
        }

        string t = workingDirectory + "/" + newDir;

        DIR *dir = opendir(&t[0]);
        //check if directory exists, if not print error and don't change the working directory
        if (!dir) {
            cout << newDir << " does not exists" << endl;
            return nullptr;
        }

        //append newDir to workingDirectory
        workingDirectory.append("/");
        workingDirectory.append(newDir);

        return nullptr;
    }

}

antlrcpp::Any TurtleVisitor::visitExecuteProgram(ShellGrammarParser::ExecuteProgramContext *context) {
    char* argv[1];
    cout << context->arguments->getText();

    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitIORedirect(ShellGrammarParser::IORedirectContext *context) {
    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitProgramPipedTo(ShellGrammarParser::ProgramPipedToContext *context) {
    return nullptr;
}

TurtleVisitor::TurtleVisitor() {}

TurtleVisitor::~TurtleVisitor() {

}
