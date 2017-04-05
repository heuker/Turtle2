#include <iostream>
#include <ANTLRInputStream.h>
#include <CommonTokenStream.h>
#include <tree/ParseTree.h>
#include <unistd.h>
#include <wait.h>
#include <vector>
#include "../gen/ShellGrammarLexer.h"
#include "../gen/ShellGrammarParser.h"
#include "TurtleVisitor.h"

void executee(ProgramExecute* programExecute){
    int returnValues;
    int cid = fork();
    if (cid == 0) {
        //get arguments
        std::vector<std::string> pArgs = programExecute->getArgs();

        //make new char array
        char *argv[pArgs.size() + 1];

        //make counter
        int i = 0;

        string programName = "";

        //transfer all arguments
        for (std::vector<std::string>::iterator it = pArgs.begin(); it != pArgs.end(); ++it) {
            string temp = *it;
            if(i == 0){
                programName = temp;
            }
            cout << "Argument: " << i << " = " << temp << std::endl;
            argv[i] = (char *) temp.c_str();
            ++i;
        }

        //add NULL to last index of the char array
        argv[pArgs.size()] = NULL;

        //execute program
        execvp(programName.c_str(), argv);
    } else {
        waitpid(cid, &returnValues, 0);
    }
}

int main() {

    // Read some line of input....
    std::string input;

    TurtleVisitor *visitor = new TurtleVisitor;

    while(std::cin){
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
        Model* model = visitor->visit(parseTree);

        if (!model->getProgramExecutes().empty()) {
            executee(model->getProgramExecutes().back());
        }

        //delete model
        delete model;
    }

    delete visitor;

    //return
    return 0;
}

