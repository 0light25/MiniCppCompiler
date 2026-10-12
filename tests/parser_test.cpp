
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

using namespace std;

int main() {

    string code = R"(
  int x = 3;
if (x == 0) {
    x = 1;
} else {
    x = x + 2;
    x = x * 3;
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
        cerr << "Parser Error: "
             << e.what() << endl;

        return 1;
    }

    return 0;
}

