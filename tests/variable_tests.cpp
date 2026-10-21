#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "lexer.h"
#include "parser.h"
#include "ast.h"

using namespace std;

bool runValidTest(
    const string& title,
    const string& code,
    const RuntimeVariables& expected
) {

    cout << "\n==========================\n";
    cout << title << "\n";
    cout << "==========================\n";

    ASTNode* root = nullptr;

    try {
        Lexer lexer;
        vector<Token> tokens = lexer.tokenize(code);

        Parser parser(tokens);
        root = parser.parseProgram();

        if (root == nullptr) {
            throw runtime_error("Parsing failed");
        }

        RuntimeVariables variables;

        root->evaluate(variables);

        delete root;
        root = nullptr;

        bool passed = (variables == expected);

        if (passed) {
            cout << "PASS\n";
        } else {
            cout << "FAIL: Incorrect variable values\n";
        }

        for (const auto& entry : expected) {
            cout << entry.first << " = ";

            auto it = variables.find(entry.first);

            if (it != variables.end())
                cout << it->second;
            else
                cout << "<missing>";

            cout << "\n";
        }

        return passed;

    } catch (const exception& e) {

        delete root;

        cout << "FAIL: " << e.what() << "\n";
        return false;
    }
}

bool runErrorTest(
    const string& title,
    const string& code
) {

    cout << "\n==========================\n";
    cout << title << "\n";
    cout << "==========================\n";

    ASTNode* root = nullptr;

    try {
        Lexer lexer;
        vector<Token> tokens = lexer.tokenize(code);

        Parser parser(tokens);
        root = parser.parseProgram();

        if (root == nullptr) {
            throw runtime_error("Parsing failed");
        }

        RuntimeVariables variables;
        root->evaluate(variables);

        delete root;

        cout << "FAIL: Error was not detected\n";
        return false;

    } catch (const runtime_error& e) {

        delete root;

        cout << "PASS: Error detected\n";
        cout << e.what() << "\n";
        return true;

    } catch (const exception& e) {

        delete root;

        cout << "FAIL: Unexpected exception: "
             << e.what() << "\n";

        return false;
    }
}

int main() {

    int passed = 0;
    int total = 0;

    total++;
    passed += runValidTest(
        "Test 1: Variable Declaration",
        "int x = 10;",
        {{"x", 10}}
    );

    total++;
    passed += runValidTest(
        "Test 2: Variable Assignment",
        "int x = 10; x = 20;",
        {{"x", 20}}
    );

    total++;
    passed += runValidTest(
        "Test 3: Variable in Expression",
        "int x = 10; int y = x + 5;",
        {{"x", 10}, {"y", 15}}
    );

    total++;
    passed += runValidTest(
        "Test 4: Multiple Statements",
        "int x = 10; x = x + 5; int y = x * 2;",
        {{"x", 15}, {"y", 30}}
    );

    total++;
    passed += runErrorTest(
        "Test 5: Undeclared Assignment",
        "x = 10;"
    );

    total++;
    passed += runErrorTest(
        "Test 6: Duplicate Declaration",
        "int x = 10; int x = 20;"
    );

    total++;
    passed += runErrorTest(
        "Test 7: Undefined Expression Variable",
        "int y = x + 5;"
    );

    cout << "\n==========================\n";
    cout << "Passed: " << passed << "/" << total << "\n";
    cout << "==========================\n";

    return passed == total ? 0 : 1;
}
