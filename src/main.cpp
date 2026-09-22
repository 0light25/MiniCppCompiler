#include <iostream>
#include "lexer.h"

using namespace std;

int main() {

    Lexer lexer;

    string code = "int x = 10;";

    vector<Token> tokens = lexer.tokenize(code);

    for (Token token : tokens) {

        cout << token.value << " : ";

        switch (token.type) {

            case KEYWORD:
                cout << "KEYWORD";
                break;

            case IDENTIFIER:
                cout << "IDENTIFIER";
                break;

            case NUMBER:
                cout << "NUMBER";
                break;

            case OPERATOR:
                cout << "OPERATOR";
                break;

            case SYMBOL:
                cout << "SYMBOL";
                break;

            case UNKNOWN:
                cout << "UNKNOWN";
                break;
        }

        cout << endl;
    }

    return 0;
}
