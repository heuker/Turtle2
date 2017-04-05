//
// Created by sander on 1-4-17.
//

#ifndef TURTLE_TURTLEVISITOR_H
#define TURTLE_TURTLEVISITOR_H


#include "../gen/ShellGrammarVisitor.h"
#include "Model.h"

using namespace std;

class TurtleVisitor : public ShellGrammarVisitor{
public:
    TurtleVisitor()
    : workingDirectory(getCwd()){};

private:
    Model* model;

public:
    antlrcpp::Any visitStart(ShellGrammarParser::StartContext *context) override;

    antlrcpp::Any visitGetWorkingDirectory(ShellGrammarParser::GetWorkingDirectoryContext *context) override;

    antlrcpp::Any visitChangeWorkingDirectory(ShellGrammarParser::ChangeWorkingDirectoryContext *context) override;

    antlrcpp::Any visitExecuteProgram(ShellGrammarParser::ExecuteProgramContext *context) override;

    antlrcpp::Any visitIORedirect(ShellGrammarParser::IORedirectContext *context) override;

    antlrcpp::Any visitProgramPipedTo(ShellGrammarParser::ProgramPipedToContext *context) override;

    virtual ~TurtleVisitor();

    string getCwd();

    antlrcpp::Any visitArgument(ShellGrammarParser::ArgumentContext *context) override;

private:
    string workingDirectory;

};


#endif //TURTLE_TURTLEVISITOR_H
