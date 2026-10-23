
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <exception>
#include <stdexcept>

#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "symbol_table.h"

using namespace std;

struct TestCase {
    string name;
    string code;
    RuntimeVariables expected;
    bool expectError;
};

bool runTest(const TestCase& test) {

    try {
        Lexer lexer;
        vector<Token> tokens = lexer.tokenize(test.code);

        Parser parser(tokens);

        unique_ptr<ASTNode> root(parser.parseProgram());

        if (!root) {
            throw runtime_error("Parsing failed");
        }

        SymbolTable symbols;
        root->checkSemantics(symbols);

        RuntimeVariables variables;
        root->evaluate(variables);

        // An invalid program must not complete.
        if (test.expectError) {
            return false;
        }

        return variables == test.expected;

    } catch (const exception& e) {

        if (test.expectError) {
            return true;
        }

        cout << "Unexpected error: "
             << e.what() << endl;

        return false;
    }
}

int main() {

    vector<TestCase> tests = {

        {
            "Variable Declaration",
            "int x = 10;",
            {{"x", 10}},
            false
        },

        {
            "Variable Assignment",
            "int x = 10; x = x + 5;",
            {{"x", 15}},
            false
        },

        {
            "Arithmetic Precedence",
            "int x = 2 + 3 * 4;",
            {{"x", 14}},
            false
        },

        {
            "If True",
            "int x = 0; if (3 > 1) { x = 10; }",
            {{"x", 10}},
            false
        },

        {
            "If Else",
            "int x = 0; if (1 > 3) "
            "{ x = 10; } else { x = 20; }",
            {{"x", 20}},
            false
        },

        {
            "While Loop",
            "int x = 0; while (x < 5) "
            "{ x = x + 1; }",
            {{"x", 5}},
            false
        },

        {
            "Complete Program",
            "int x = 0; "
            "while (x < 5) { x = x + 1; } "
            "if (x > 3) { x = x + 10; } "
            "else { x = x - 10; }",
            {{"x", 15}},
            false
        },

        {
            "Missing Expression",
            "int x = ;",
            {},
            true
        },

        {
            "Missing Semicolon",
            "int x = 10",
            {},
            true
        },

        {
            "Undeclared Variable",
            "x = 20;",
            {},
            true
        },

        {
            "Duplicate Declaration",
            "int x = 10; int x = 20;",
            {},
            true
        }

    };

    int passed = 0;

    for (const TestCase& test : tests) {

        cout << "\nTest: " << test.name << endl;

        if (runTest(test)) {
            cout << "PASS" << endl;
            passed++;
        } else {
            cout << "FAIL" << endl;
        }
    }

    cout << "\n==========================" << endl;

    cout << "Passed: " << passed
         << "/" << tests.size() << endl;

    cout << "==========================" << endl;

    return passed == static_cast<int>(tests.size())
           ? 0 : 1;
}

