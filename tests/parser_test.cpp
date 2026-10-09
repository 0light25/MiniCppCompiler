#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "ast.h"

using namespace std;

int main() {
string code = R"(
    int x = 10;
    x = x + 5;

    int y = 20;
    y = y * 2;
)";


    Lexer lexer;

    vector<Token> tokens = lexer.tokenize(code);

    Parser parser(tokens);

    ASTNode* root = parser.parseProgram();

    if (root != nullptr) {
        root->print();
    }
    else {
        cout << "Parsing failed" << endl;
    }

    delete root;

    return 0;
}
