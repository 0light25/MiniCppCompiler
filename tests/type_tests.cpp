#include <iostream>
#include <memory>
#include <exception>
#include "ast.h"
#include "symbol_table.h"

using namespace std;

int passed = 0;
int total = 0;

void runTest(
    const string& testName,
    ASTNode* node,
    bool expectError
) {
    total++;

    unique_ptr<ASTNode> root(node);
    SymbolTable symbols;

    cout << "\n==========================\n";
    cout << testName << endl;
    cout << "==========================\n";

    bool errorOccurred = false;

    try {
        root->checkSemantics(symbols);
    }
    catch (const exception& e) {
        errorOccurred = true;
        cout << e.what() << endl;
    }

    if (errorOccurred == expectError) {
        cout << "PASS\n";
        passed++;
    }
    else {
        cout << "FAIL\n";
    }
}

int main() {

    // Test 1: Valid integer declaration
    runTest(
        "Test 1: Valid Declaration",
        new VariableDeclarationNode(
            "int",
            "x",
            new NumberNode(10)
        ),
        false
    );

    // Test 2: Valid arithmetic
    runTest(
        "Test 2: Valid Arithmetic",
        new VariableDeclarationNode(
            "int",
            "x",
            new BinaryNode(
                "+",
                new NumberNode(10),
                new NumberNode(5)
            )
        ),
        false
    );

    // Test 3: Invalid declaration (bool assigned to int)
    runTest(
        "Test 3: Declaration Type Mismatch",
        new VariableDeclarationNode(
            "int",
            "x",
            new BinaryNode(
                ">",
                new NumberNode(10),
                new NumberNode(5)
            )
        ),
        true
    );

    // Test 4: Valid assignment
    ProgramNode* program1 = new ProgramNode();

    program1->addStatement(
        new VariableDeclarationNode(
            "int", "x", new NumberNode(10)
        )
    );

    program1->addStatement(
        new AssignmentNode(
            "x",
            new BinaryNode(
                "+",
                new IdentifierNode("x"),
                new NumberNode(5)
            )
        )
    );

    runTest("Test 4: Valid Assignment", program1, false);

    // Test 5: Invalid assignment
    ProgramNode* program2 = new ProgramNode();

    program2->addStatement(
        new VariableDeclarationNode(
            "int", "x", new NumberNode(10)
        )
    );

    program2->addStatement(
        new AssignmentNode(
            "x",
            new BinaryNode(
                ">",
                new IdentifierNode("x"),
                new NumberNode(5)
            )
        )
    );

    runTest("Test 5: Assignment Type Mismatch", program2, true);

    // Test 6: Invalid arithmetic (int + bool)
    runTest(
        "Test 6: Invalid Arithmetic",
        new BinaryNode(
            "+",
            new NumberNode(10),
            new BinaryNode(
                ">",
                new NumberNode(5),
                new NumberNode(2)
            )
        ),
        true
    );

    cout << "\n==========================\n";
    cout << "Passed: " << passed << "/" << total << endl;
    cout << "==========================\n";

    return passed == total ? 0 : 1;
}
