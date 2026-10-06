#include <iostream>

#include "lexer.h"
#include "parser.h"

using namespace std;

int main() {

    string code = "int x = 10 + 20 * 3;";

    Lexer lexer;

    vector<Token> tokens = lexer.tokenize(code);

    Parser parser(tokens);

    ASTNode* root = parser.parseDeclaration();

    if (root != nullptr) {

        cout << "AST:" << endl;

        root->print();

        delete root;
    }

    return 0;
}
