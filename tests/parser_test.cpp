#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

using namespace std;

int main() {

    string code = R"(
        int x = 0;

        while (x < 5) {
            x = x + 1;
        }
    )";

    Lexer lexer;

    vector<Token> tokens = lexer.tokenize(code);

    Parser parser(tokens);

    ASTNode* root = parser.parseProgram();

    root->print();

    delete root;

    return 0;
}
