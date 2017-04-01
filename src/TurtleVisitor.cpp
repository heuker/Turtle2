//
// Created by sander on 1-4-17.
//

#include "TurtleVisitor.h"

antlrcpp::Any TurtleVisitor::visitStart(ShellGrammarParser::StartContext *context) {
    visitChildren(context);
    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitListWorkingDirectory(ShellGrammarParser::ListWorkingDirectoryContext *context) {
    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitGetWorkingDirectory(ShellGrammarParser::GetWorkingDirectoryContext *context) {
//    cout << workingDirectory << endl;
    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitChangeWorkingDirectory(ShellGrammarParser::ChangeWorkingDirectoryContext *context) {
    return nullptr;
}

antlrcpp::Any TurtleVisitor::visitExecuteProgram(ShellGrammarParser::ExecuteProgramContext *context) {
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
