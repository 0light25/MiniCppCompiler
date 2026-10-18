
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>

class SymbolTable {
private:
    std::unordered_map<std::string, std::string> symbols;

    // Link to the outer scope
    SymbolTable* parent;

public:
    explicit SymbolTable(SymbolTable* parent = nullptr);

    void declareVariable(const std::string& name,
                         const std::string& type);

    bool isDeclared(const std::string& name) const;

    void checkVariable(const std::string& name) const;

    std::string getType(const std::string& name) const;
};

#endif

