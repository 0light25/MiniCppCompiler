
#include "symbol_table.h"
#include <stdexcept>

using namespace std;

// Constructor
SymbolTable::SymbolTable(SymbolTable* parent)
    : parent(parent) {}

// Declare a variable in the current scope
void SymbolTable::declareVariable(
    const string& name,
    const string& type
) {
    if (symbols.find(name) != symbols.end()) {
        throw runtime_error(
            "Semantic Error: Variable '" + name +
            "' already declared in this scope"
        );
    }

    symbols[name] = type;
}

// Search current scope, then parent scopes
bool SymbolTable::isDeclared(const string& name) const {
    if (symbols.find(name) != symbols.end()) {
        return true;
    }

    if (parent != nullptr) {
        return parent->isDeclared(name);
    }

    return false;
}

// Check whether a variable is accessible
void SymbolTable::checkVariable(
    const string& name
) const {
    if (!isDeclared(name)) {
        throw runtime_error(
            "Semantic Error: Undeclared variable '" +
            name + "'"
        );
    }
}

// Get the type of a variable
string SymbolTable::getType(
    const string& name
) const {
    auto it = symbols.find(name);

    if (it != symbols.end()) {
        return it->second;
    }

    if (parent != nullptr) {
        return parent->getType(name);
    }

    throw runtime_error(
        "Semantic Error: Undeclared variable '" +
        name + "'"
    );
}

