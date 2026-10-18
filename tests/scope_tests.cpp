
#include <iostream>
#include <string>
#include <memory>
#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "symbol_table.h"

using namespace std;

bool runTest(const string& name,
             const string& code,
             bool expectError) {

    cout << "\n==========================\n";
    cout << name << "\n";
    cout << "==========================\n";

    try {
        Lexer lexer;
        vector<Token> tokens = lexer.tokenize(code);

        Parser parser(tokens);
        unique_ptr<ASTNode> root(parser.parseProgram());

        SymbolTable symbols;
        root->checkSemantics(symbols);

        if (expectError) {
            cout << "FAIL: Expected a semantic error\n";
            return false;
        }

        cout << "PASS: Semantic analysis successful\n";
        return true;

    } catch (const exception& e) {
        string message = e.what();
        cout << message << "\n";

        if (expectError &&
            message.find("Semantic Error") != string::npos) {
            cout << "PASS: Semantic error detected\n";
            return true;
        }

        cout << "FAIL: Unexpected error\n";
        return false;
    }
}

int main() {
    int passed = 0;
    int total = 8;

    passed += runTest(
        "Test 1: Access Outer Variable",
        "int x = 10;"
        "if (x > 5) {"
        "  int y = x;"
        "  x = y;"
        "}",
        false
    );

    passed += runTest(
        "Test 2: Access Variable Outside If",
        "int x = 10;"
        "if (x > 5) {"
        "  int y = 20;"
        "}"
        "y = 30;",
        true
    );

    passed += runTest(
        "Test 3: Valid While Scope",
        "int x = 0;"
        "while (x < 3) {"
        "  int temp = x;"
        "  x = x + 1;"
        "}",
        false
    );

    passed += runTest(
        "Test 4: Access Variable Outside While",
        "int x = 0;"
        "while (x < 3) {"
        "  int temp = x;"
        "  x = x + 1;"
        "}"
        "temp = 5;",
        true
    );

    passed += runTest(
        "Test 5: Variable Shadowing",
        "int x = 10;"
        "if (x > 5) {"
        "  int x = 20;"
        "  x = x + 1;"
        "}"
        "x = x + 1;",
        false
    );

    passed += runTest(
        "Test 6: Duplicate In Same Scope",
        "int x = 10;"
        "if (x > 5) {"
        "  int a = 1;"
        "  int a = 2;"
        "}",
        true
    );

    passed += runTest(
        "Test 7: Separate If Else Scopes",
        "int x = 10;"
        "if (x > 5) {"
        "  int a = 1;"
        "} else {"
        "  int a = 2;"
        "}",
        false
    );

    passed += runTest(
        "Test 8: If Variable Used In Else",
        "int x = 10;"
        "if (x > 5) {"
        "  int y = 1;"
        "} else {"
        "  y = 2;"
        "}",
        true
    );

    cout << "\n==========================\n";
    cout << "Passed: " << passed << "/" << total << "\n";
    cout << "==========================\n";

    return passed == total ? 0 : 1;
}

