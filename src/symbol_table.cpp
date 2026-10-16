
#include "symbol_table.h"
#include <stdexcept>

using namespace std;

// Declare a new variable
void SymbolTable::declareVariable(
    string name,
    string type
) {
    if (isDeclared(name)) {
        throw runtime_error(
            "Semantic Error: Variable '" +
            name + "' already declared"
        );
    }

    symbols[name] = type;
}

// Check whether variable exists
bool SymbolTable::isDeclared(string name) const {

    return symbols.find(name) != symbols.end();
}

// Report undeclared variables
void SymbolTable::checkVariable(string name) const {

    if (!isDeclared(name)) {
        throw runtime_error(
            "Semantic Error: Undeclared variable '" +
            name + "'"
        );
    }
}

// Get variable type
string SymbolTable::getType(string name) const {

    checkVariable(name);

    return symbols.at(name);
}

