
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
    RuntimeVariables expected;
};

bool runTest(const TestCase& test) {

    ASTNode* root = nullptr;

    try {
        Lexer lexer;

        vector<Token> tokens = lexer.tokenize(test.code);

        Parser parser(tokens);

        root = parser.parseProgram();

        if (root == nullptr) {
            cout << "FAIL: Parsing failed\n";
            return false;
        }

        RuntimeVariables variables;

        root->evaluate(variables);

        bool passed = (variables == test.expected);

        cout << (passed ? "PASS" : "FAIL") << endl;

        for (const auto& item : variables) {
            cout << item.first << " = "
                 << item.second << endl;
        }

        delete root;

        return passed;

    } catch (const exception& e) {

        delete root;

        cout << "FAIL: " << e.what() << endl;

        return false;
    }
}

int main() {

    vector<TestCase> tests = {

        {
            "If True",
            "int x = 10;"
            "if (x > 5) { x = x + 5; }",
            {{"x", 15}}
        },

        {
            "If False",
            "int x = 2;"
            "if (x > 5) { x = x + 10; }",
            {{"x", 2}}
        },

        {
            "If Else",
            "int x = 2;"
            "if (x > 5) { x = x + 10; }"
            "else { x = x + 6; }",
            {{"x", 8}}
        },

        {
            "While Loop",
            "int x = 0;"
            "while (x < 5) { x = x + 1; }",
            {{"x", 5}}
        },

        {
            "While Zero Iterations",
            "int x = 10;"
            "while (x < 5) { x = x + 1; }",
            {{"x", 10}}
        },

        {
            "Nested If Inside While",
            "int x = 0;"
            "int y = 0;"
            "while (x < 4) {"
            "  if (x > 1) { y = y + 1; }"
            "  x = x + 1;"
            "}",
            {{"x", 4}, {"y", 2}}
        }
    };

    int passed = 0;

    for (size_t i = 0; i < tests.size(); i++) {

        cout << "\n==========================\n";
        cout << "Test " << i + 1 << ": "
             << tests[i].name << endl;
        cout << "==========================\n";

        if (runTest(tests[i])) {
            passed++;
        }
    }

    cout << "\n==========================\n";
    cout << "Passed: " << passed
         << "/" << tests.size() << endl;
    cout << "==========================\n";

    return passed == tests.size() ? 0 : 1;
}

