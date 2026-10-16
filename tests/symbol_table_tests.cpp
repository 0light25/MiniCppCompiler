
#include <iostream>
#include <stdexcept>
#include "symbol_table.h"

using namespace std;

int main() {

    SymbolTable table;
    int failed = 0;

    // Test 1: Valid declarations
    cout << "\nTest 1: Valid Declarations\n";

    try {
        table.declareVariable("x", "int");
        table.declareVariable("y", "int");

        table.checkVariable("x");
        table.checkVariable("y");

        cout << "PASS: Variables declared successfully\n";
    }
    catch (const exception& e) {
        cout << "FAIL: " << e.what() << endl;
        failed++;
    }

    // Test 2: Undeclared variable
    cout << "\nTest 2: Undeclared Variable\n";

    try {
        table.checkVariable("z");

        cout << "FAIL: Undeclared variable accepted\n";
        failed++;
    }
    catch (const exception& e) {
        cout << "PASS: " << e.what() << endl;
    }

    // Test 3: Duplicate declaration
    cout << "\nTest 3: Duplicate Declaration\n";

    try {
        table.declareVariable("x", "int");

        cout << "FAIL: Duplicate declaration accepted\n";
        failed++;
    }
    catch (const exception& e) {
        cout << "PASS: " << e.what() << endl;
    }

    // Test 4: Type lookup
    cout << "\nTest 4: Variable Type\n";

    try {
        string type = table.getType("x");

        if (type == "int") {
            cout << "PASS: x has type int\n";
        }
        else {
            cout << "FAIL: Wrong type\n";
            failed++;
        }
    }
    catch (const exception& e) {
        cout << "FAIL: " << e.what() << endl;
        failed++;
    }

    cout << "\nTests failed: " << failed << endl;

    return failed == 0 ? 0 : 1;
}

