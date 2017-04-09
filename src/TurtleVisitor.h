//
// Created by sander on 1-4-17.
//

#ifndef TURTLE_TURTLEVISITOR_H
#define TURTLE_TURTLEVISITOR_H


#include "../gen/ShellGrammarVisitor.h"
#include "Model.h"

using namespace std;

class TurtleVisitor : public ShellGrammarVisitor {
public:
    TurtleVisitor()
            : workingDirectory(getCwd()), inBackground(false) {};

private:
    Model *model;

public:
    //desctructor
    virtual ~TurtleVisitor();

    //method that gets working directory of proces
    string getCwd();


    //overrided visits
    antlrcpp::Any visitStart(ShellGrammarParser::StartContext *context) override;

    antlrcpp::Any visitGetWorkingDirectory(ShellGrammarParser::GetWorkingDirectoryContext *context) override;

    antlrcpp::Any visitChangeWorkingDirectory(ShellGrammarParser::ChangeWorkingDirectoryContext *context) override;

    antlrcpp::Any visitStartProgram(ShellGrammarParser::StartProgramContext *context) override;

    antlrcpp::Any visitIORedirect(ShellGrammarParser::IORedirectContext *context) override;

    antlrcpp::Any visitArgument(ShellGrammarParser::ArgumentContext *context) override;

private:
    //working directory
    string workingDirectory;

    //bool needed for building a command
    bool inBackground;
};


#endif //TURTLE_TURTLEVISITOR_H
