#include <iostream>
#include <vector>

#include "lexer.h"
#include "parser.h"
#include "ast.h"

using namespace std;

int main() {

   // string code = "10 + 20 * 3;";
string code = "100 - 20 / 4;";
    Lexer lexer;

    vector<Token> tokens = lexer.tokenize(code);

    Parser parser(tokens);

    ASTNode* root = parser.parseExpression();

    cout << "AST:" << endl;

    root->print();

    delete root;

    return 0;
}
