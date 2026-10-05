#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

using namespace std;

int main() {

    string code = "10 + 20 * 3;";

    Lexer lexer;

    vector<Token> tokens = lexer.tokenize(code);

    Parser parser(tokens);

    ASTNode* root = parser.parseExpression();

    if (root != nullptr) {

        root->print();

        delete root;
    }

    return 0;
}
