#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

int main() {

    string code = R"(

        int x = 10;

        x = x + 5;

        int y = 20;

        y = y * 2;

       if (y < 50) {
    y = y + 10;
}

    )";

    try {

        Lexer lexer;

        vector<Token> tokens = lexer.tokenize(code);

        Parser parser(tokens);

        ASTNode* root = parser.parseProgram();

        root->print();

        delete root;

    }
    catch (const exception& e) {

        cerr << "Parser error: "
             << e.what() << endl;

        return 1;
    }

    return 0;
}
