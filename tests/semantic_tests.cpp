#include <iostream>
#include <string>
#include <memory>

#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "symbol_table.h"

using namespace std;

bool runTest(
    string testName,
    string code,
    bool expectError
) {
    cout << "\n==========================\n";
    cout << testName << endl;
    cout << "==========================\n";

    try {
        Lexer lexer;
        vector<Token> tokens = lexer.tokenize(code);

        Parser parser(tokens);

        unique_ptr<ASTNode> root(parser.parseProgram());

        SymbolTable symbols;

        root->checkSemantics(symbols);

        if (expectError) {
            cout << "FAIL: Expected semantic error\n";
            return false;
        }

        cout << "PASS: Semantic analysis successful\n";
        return true;

    } catch (const exception& e) {

        string error = e.what();

        if (expectError &&
            error.find("Semantic Error") != string::npos) {

            cout << "PASS: Semantic error detected\n";
            cout << error << endl;
            return true;
        }

        cout << "FAIL: " << error << endl;
        return false;
    }
}

int main() {

    int passed = 0;
    int total = 5;

    passed += runTest(
        "Test 1: Valid Declaration",
        "int x = 10; x = x + 5;",
        false
    );

    passed += runTest(
        "Test 2: Undeclared Assignment",
        "x = 10;",
        true
    );

    passed += runTest(
        "Test 3: Duplicate Declaration",
        "int x = 10; int x = 20;",
        true
    );

    passed += runTest(
        "Test 4: Undeclared Expression Variable",
        "int x = 10; x = x + y;",
        true
    );

    passed += runTest(
        "Test 5: Valid While Loop",
        "int x = 0; while (x < 3) { x = x + 1; }",
        false
    );

    cout << "\n==========================\n";
    cout << "Passed: " << passed << "/" << total << endl;
    cout << "==========================\n";

    return passed == total ? 0 : 1;
}
