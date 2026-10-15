#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include "lexer.h"
#include "parser.h"
#include "ast.h"

using namespace std;

struct TestCase {
    string name;
    string code;
    bool shouldBeValid;
};

int main() {

    vector<TestCase> tests = {

        {
            "Missing Expression",
            "int x = ;",
            false
        },

        {
            "Missing Semicolon",
            "int x = 10",
            false
        },

        {
            "Invalid If Condition",
            "if (x > ) { x = 5; }",
            false
        },

        {
            "Missing Closing Parenthesis",
            "while (x < 5 { x = x + 1; }",
            false
        },

        {
            "Missing Closing Brace",
            "while (x < 5) { x = x + 1;",
            false
        },

        {
            "Valid Program",
            "int x = 0; while (x < 5) { x = x + 1; }",
            true
        }
    };

    int failures = 0;

    for (const TestCase& test : tests) {

        cout << "\n==========================\n";
        cout << "Test: " << test.name << endl;
        cout << "==========================\n";

        try {
            Lexer lexer;

            vector<Token> tokens =
                lexer.tokenize(test.code);

            Parser parser(tokens);

            ASTNode* root = parser.parseProgram();

            delete root;

            if (test.shouldBeValid) {
                cout << "PASS: Valid program accepted\n";
            } else {
                cout << "FAIL: Invalid program accepted\n";
                failures++;
            }

        } catch (const exception& e) {

            if (test.shouldBeValid) {
                cout << "FAIL: " << e.what() << endl;
                failures++;
            } else {
                cout << "PASS: Syntax error detected\n";
                cout << e.what() << endl;
            }
        }
    }

    cout << "\nTests failed: " << failures << endl;

    return failures == 0 ? 0 : 1;
}
