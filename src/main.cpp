/*
#include <iostream>
#include "lexer.h"

using namespace std;

int main() {

    Lexer lexer;

    string code = R"(
        int x = 10 + 20;
        if (x >= 20) {
            x = x - 5;
        }
    )";

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
*/
#include <iostream>
#include "lexer.h"

using namespace std;

int main() {

    string code = "int age = 20; if age return age;";

    Lexer lexer;

    vector<Token> tokens = lexer.tokenize(code);

    for (auto token : tokens) {
        cout << token.type << " : " << token.value << endl;
    }

    return 0;
}
