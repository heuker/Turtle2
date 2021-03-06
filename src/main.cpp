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

        //get all commands from the model
        std::vector<Command *> commands = model->getCommands();

        //set defaults to 0
        int prevOutPartOfPipe = 0;
        int prevInPartOfPipe = 0;

        //loop over all commands executing them
        for (std::vector<Command *>::iterator it = commands.begin(); it != commands.end(); ++it) {
            Command *p = *it;
            p->execute(prevOutPartOfPipe, prevInPartOfPipe);

            prevOutPartOfPipe = p->getOutPartOfPipe();
            prevInPartOfPipe = p->getInPartOfPipe();
        }

        //delete model
        delete model;
    }

    //delete visitor
    delete visitor;

    //return
    return 0;
}

