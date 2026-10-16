
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>

using namespace std;

class SymbolTable {

private:
    unordered_map<string, string> symbols;

public:
    void declareVariable(string name, string type);

    bool isDeclared(string name) const;

    void checkVariable(string name) const;

    string getType(string name) const;
};

#endif

