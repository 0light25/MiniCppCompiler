#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

using namespace std;

int main() {

    string code = "10;";

    Lexer lexer;

    vector<Token> tokens = lexer.tokenize(code);

    Parser parser(tokens);

    ASTNode* root = parser.parseNumber();

    if (root != nullptr) {
        root->print();
    }
    else {
        cout << "Parsing failed" << endl;
    }

    delete root;

    return 0;
}
