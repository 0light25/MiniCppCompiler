
#include <iostream>
#include "lexer.h"

using namespace std;

int main() {

    // Code that OUR lexer will analyze
    string code = R"(
        int age = 20;
//hello world!.==
        /* this is my comment */

        return age;
    )";

    Lexer lexer;

    vector<Token> tokens = lexer.tokenize(code);

    for (auto token : tokens) {

        cout << token.type << " : " << token.value << endl;
    }

    return 0;
}
