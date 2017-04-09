#include <iostream>
#include <ANTLRInputStream.h>
#include <CommonTokenStream.h>
#include <tree/ParseTree.h>
#include "../gen/ShellGrammarLexer.h"
#include "../gen/ShellGrammarParser.h"
#include "TurtleVisitor.h"

int main() {

    // Read some line of input....
    std::string input;

    TurtleVisitor *visitor = new TurtleVisitor;

    while (std::cin) {
        cout << visitor->getCwd() << "$ ";
        getline(cin, input);

        // Create input stream, create lexer and use lexer to create stream of tokens
        antlr4::ANTLRInputStream inputStream(input);
        ShellGrammarLexer lexer(&inputStream);
        antlr4::CommonTokenStream tokens(&lexer);

        // Create parser
        ShellGrammarParser parser(&tokens);
        antlr4::tree::ParseTree *parseTree = parser.start();

        // Then, visit your tree
        Model *model = visitor->visit(parseTree);

        std::vector<ProgramExecute *> commands = model->getProgramExecutes();

        int prevOutPartOfPipe = 0;
        int prevInPartOfPipe = 0;

        for (std::vector<ProgramExecute *>::iterator it = commands.begin(); it != commands.end(); ++it) {
            ProgramExecute *p = *it;
            p->execute(prevOutPartOfPipe, prevInPartOfPipe);

            prevOutPartOfPipe = p->getOutPartOfPipe();
            prevInPartOfPipe = p->getInPartOfPipe();
        }

        //delete model
        delete model;
    }

    delete visitor;

    //return
    return 0;
}

