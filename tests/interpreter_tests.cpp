
#include <iostream>
#include <stdexcept>
#include <string>
#include "ast.h"

using namespace std;

int passed = 0;
int total = 0;

void runTest(
    string name,
    ASTNode* expression,
    int expected
) {
    total++;

    cout << "\n==========================\n";
    cout << name << endl;
    cout << "==========================\n";

    try {
        int result = expression->evaluate();

        cout << "Expected: " << expected << endl;
        cout << "Actual:   " << result << endl;

        if (result == expected) {
            cout << "PASS" << endl;
            passed++;
        } else {
            cout << "FAIL" << endl;
        }

    } catch (const exception& e) {
        cout << "FAIL: " << e.what() << endl;
    }

    delete expression;
}

void runErrorTest(
    string name,
    ASTNode* expression
) {
    total++;

    cout << "\n==========================\n";
    cout << name << endl;
    cout << "==========================\n";

    try {
        int result = expression->evaluate();

        cout << "FAIL: Expected runtime error" << endl;
        cout << "Actual: " << result << endl;

    } catch (const runtime_error& e) {
        cout << e.what() << endl;
        cout << "PASS" << endl;
        passed++;
    }

    delete expression;
}

int main() {

    // Test 1: Number
    runTest(
        "Test 1: Number Evaluation",
        new NumberNode(10),
        10
    );

    // Test 2: Addition
    runTest(
        "Test 2: Addition",
        new BinaryNode(
            "+",
            new NumberNode(10),
            new NumberNode(5)
        ),
        15
    );

    // Test 3: Subtraction
    runTest(
        "Test 3: Subtraction",
        new BinaryNode(
            "-",
            new NumberNode(20),
            new NumberNode(8)
        ),
        12
    );

    // Test 4: Multiplication
    runTest(
        "Test 4: Multiplication",
        new BinaryNode(
            "*",
            new NumberNode(6),
            new NumberNode(7)
        ),
        42
    );

    // Test 5: Division
    runTest(
        "Test 5: Division",
        new BinaryNode(
            "/",
            new NumberNode(20),
            new NumberNode(4)
        ),
        5
    );

    // Test 6: Operator Precedence
    // 10 + (5 * 2) = 20
    runTest(
        "Test 6: Operator Precedence",
        new BinaryNode(
            "+",
            new NumberNode(10),
            new BinaryNode(
                "*",
                new NumberNode(5),
                new NumberNode(2)
            )
        ),
        20
    );

    // Test 7: Parentheses
    // (10 + 5) * 2 = 30
    runTest(
        "Test 7: Parentheses",
        new BinaryNode(
            "*",
            new BinaryNode(
                "+",
                new NumberNode(10),
                new NumberNode(5)
            ),
            new NumberNode(2)
        ),
        30
    );

    // Test 8: Division by zero
    runErrorTest(
        "Test 8: Division by Zero",
        new BinaryNode(
            "/",
            new NumberNode(10),
            new NumberNode(0)
        )
    );

    cout << "\n==========================\n";
    cout << "Passed: " << passed
         << "/" << total << endl;
    cout << "==========================\n";

    return passed == total ? 0 : 1;
}

