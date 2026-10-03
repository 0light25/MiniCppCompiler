#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

int main() {

    Lexer lexer;

   // string code = "10 + 20;";
// string code = "10 - 5;";
string code = "10;";
    vector<Token> tokens = lexer.tokenize(code);

    Parser parser(tokens);

    ASTNode* root = parser.parseExpression();

    cout << "AST for: " << code << endl;
    cout << "-------------------" << endl;

    if (root != nullptr) {
        root->print();
    }
    else {
        cout << "Parser error" << endl;
    }

    delete root;

    return 0;
}
