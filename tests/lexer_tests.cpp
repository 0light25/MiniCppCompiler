#include <iostream>
#include "lexer.h"

using namespace std;

void runTest(string testName, string code) {

    cout << "\n==============================" << endl;
    cout << testName << endl;
    cout << "==============================" << endl;

    Lexer lexer;

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
}

int main() {

    // Test 1
    runTest(
        "Test 1 - Variable Declaration",
        "int x = 10;"
    );

    // Test 2
    runTest(
        "Test 2 - Arithmetic Expression",
        "int result = x + 20;"
    );

    // Test 3
    runTest(
        "Test 3 - If Condition",
        "if (x > 10) { return x; }"
    );

    // Test 4
    runTest(
        "Test 4 - Comments",
        R"(
            int age = 20;

            // this is a single line comment

            /* this is a
               multi line comment */

            return age;
        )"
    );

    return 0;
}
