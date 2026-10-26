
#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;

// Day 27: Runtime variable storage
using RuntimeVariables = std::unordered_map<std::string, int>;

class SymbolTable;

class ASTNode {
public:
    virtual void print(int indent = 0) = 0;
    virtual void checkSemantics(SymbolTable& symbols) = 0;
    virtual string inferType(SymbolTable& symbols);

    virtual int evaluate();
    virtual int evaluate(RuntimeVariables& variables);

    virtual ~ASTNode() {}
};

class NumberNode : public ASTNode {
public:
    int value;

    NumberNode(int value);

    void print(int indent = 0) override;
    void checkSemantics(SymbolTable& symbols) override;
    string inferType(SymbolTable& symbols) override;

    int evaluate() override;
};

class BinaryNode : public ASTNode {
public:
    string op;
    ASTNode* left;
    ASTNode* right;

    BinaryNode(string op, ASTNode* left, ASTNode* right);

    void print(int indent = 0) override;
    void checkSemantics(SymbolTable& symbols) override;
    string inferType(SymbolTable& symbols) override;

    int evaluate() override;
    int evaluate(RuntimeVariables& variables) override;

    ~BinaryNode();
};

class VariableDeclarationNode : public ASTNode {
public:
    string type;
    string name;
    ASTNode* value;

    VariableDeclarationNode(
        string type,
        string name,
        ASTNode* value
    );

    void print(int indent = 0) override;
    void checkSemantics(SymbolTable& symbols) override;

    int evaluate(RuntimeVariables& variables) override;

    ~VariableDeclarationNode();
};

class ProgramNode : public ASTNode {
public:
    vector<ASTNode*> statements;

    void addStatement(ASTNode* statement);

    void print(int indent = 0) override;
    void checkSemantics(SymbolTable& symbols) override;

    int evaluate(RuntimeVariables& variables) override;

    ~ProgramNode();
};

class IdentifierNode : public ASTNode {
public:
    string name;

    IdentifierNode(string name);

    void print(int indent = 0) override;
    void checkSemantics(SymbolTable& symbols) override;
    string inferType(SymbolTable& symbols) override;

    int evaluate(RuntimeVariables& variables) override;
};

class AssignmentNode : public ASTNode {
public:
    string name;
    ASTNode* expression;

    AssignmentNode(string name, ASTNode* expression);

    void print(int indent = 0) override;
    void checkSemantics(SymbolTable& symbols) override;

    int evaluate(RuntimeVariables& variables) override;

    ~AssignmentNode();
};

class IfNode : public ASTNode {
private:
    ASTNode* condition;
    ProgramNode* body;
    ProgramNode* elseBody;

public:
    IfNode(
        ASTNode* condition,
        ProgramNode* body,
        ProgramNode* elseBody = nullptr
    );

    void print(int indent = 0) override;
    void checkSemantics(SymbolTable& symbols) override;
int evaluate(RuntimeVariables& variables) override;
    ~IfNode() override;
};

class WhileNode : public ASTNode {
public:
    ASTNode* condition;
    ProgramNode* body;

    WhileNode(ASTNode* condition, ProgramNode* body);
int evaluate(RuntimeVariables& variables) override;
    void print(int indent = 0) override;
    void checkSemantics(SymbolTable& symbols) override;

    ~WhileNode();
};

class CoutNode : public ASTNode {
public:
    enum Kind {
        TEXT,
        EXPRESSION,
        NEWLINE
    };

    struct Item {
        Kind kind;
        string text;
        ASTNode* expression;
    };

private:
    vector<Item> items;

public:
    void addText(const string& text);
    void addExpression(ASTNode* expression);
    void addEndl();

    ~CoutNode() override;

    void print(int indent = 0) override;

    void checkSemantics(SymbolTable& symbols) override;

    string inferType(SymbolTable& symbols) override;

    int evaluate() override;

    int evaluate(RuntimeVariables& variables) override;
};

#endif

