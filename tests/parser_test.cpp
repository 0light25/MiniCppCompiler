#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

int main() {

    string code = R"(

        int x = 10;

        if (x >= 10) {
            x = x + 1;
        }

        if (x <= 20) {
            x = x + 2;
        }

        if (x == 13) {
            x = x + 3;
        }

        if (x != 0) {
            x = x * 2;
        }

    )";

    try {

        Lexer lexer;

        vector<Token> tokens =
            lexer.tokenize(code);

        Parser parser(tokens);

        ASTNode* root =
            parser.parseProgram();

        root->print();

        delete root;

    }
    catch (const exception& e) {

        cerr << "Parser Error: "
             << e.what()
             << endl;

        return 1;
    }

    return 0;
}
