#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class SymbolTable;
class ASTNode {
public:
    virtual void print(int indent = 0) = 0;
    virtual void checkSemantics(SymbolTable& symbols) = 0;
    virtual string inferType(SymbolTable& symbols);
    virtual ~ASTNode() {}
};

class NumberNode : public ASTNode {
public:
	void checkSemantics(SymbolTable& symbols) override;
    int value;

    NumberNode(int value);
    void print(int indent = 0);
    string inferType(SymbolTable& symbols) override;
};

class BinaryNode : public ASTNode {
public:
	void checkSemantics(SymbolTable& symbols) override;
    string op;
    ASTNode* left;
    ASTNode* right;

    BinaryNode(string op, ASTNode* left, ASTNode* right);
    void print(int indent = 0);
    string inferType(SymbolTable& symbols) override;
    ~BinaryNode();
};

class VariableDeclarationNode : public ASTNode {
public:
	void checkSemantics(SymbolTable& symbols) override;
    string type;
    string name;
    ASTNode* value;

    VariableDeclarationNode(
        string type,
        string name,
        ASTNode* value
    );

    void print(int indent = 0);
    ~VariableDeclarationNode();
};

// New for Day 15
class ProgramNode : public ASTNode {
public:
	void checkSemantics(SymbolTable& symbols) override;
    vector<ASTNode*> statements;

    void addStatement(ASTNode* statement);
    void print(int indent = 0);
    ~ProgramNode();
};
class IdentifierNode : public ASTNode {
public:
	void checkSemantics(SymbolTable& symbols) override;
    string name;

    IdentifierNode(string name);
    string inferType(SymbolTable& symbols) override;
    void print(int indent = 0) override;
};

class AssignmentNode : public ASTNode {
public:
	void checkSemantics(SymbolTable& symbols) override;
    string name;
    ASTNode* expression;

    AssignmentNode(string name, ASTNode* expression);

    ~AssignmentNode();

    void print(int indent = 0) override;
};


class IfNode : public ASTNode {
private:
    ASTNode* condition;
    ProgramNode* body;
    ProgramNode* elseBody;

public:
	void checkSemantics(SymbolTable& symbols) override;
    IfNode(ASTNode* condition,
           ProgramNode* body,
           ProgramNode* elseBody = nullptr);

    ~IfNode() override;

    void print(int indent = 0) override;
};
class WhileNode : public ASTNode {
public:
    ASTNode* condition;
    ProgramNode* body;
void checkSemantics(SymbolTable& symbols) override;
    WhileNode(ASTNode* condition, ProgramNode* body);

    void print(int indent = 0) override;

    ~WhileNode();
};
#endif
