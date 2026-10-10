#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ASTNode {
public:
    virtual void print(int indent = 0) = 0;
    virtual ~ASTNode() {}
};

class NumberNode : public ASTNode {
public:
    int value;

    NumberNode(int value);
    void print(int indent = 0);
};

class BinaryNode : public ASTNode {
public:
    string op;
    ASTNode* left;
    ASTNode* right;

    BinaryNode(string op, ASTNode* left, ASTNode* right);
    void print(int indent = 0);
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

    void print(int indent = 0);
    ~VariableDeclarationNode();
};

// New for Day 15
class ProgramNode : public ASTNode {
public:
    vector<ASTNode*> statements;

    void addStatement(ASTNode* statement);
    void print(int indent = 0);
    ~ProgramNode();
};
class IdentifierNode : public ASTNode {
public:
    string name;

    IdentifierNode(string name);

    void print(int indent = 0) override;
};

class AssignmentNode : public ASTNode {
public:
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

public:
    IfNode(ASTNode* condition, ProgramNode* body);

    ~IfNode() override;

    void print(int indent = 0) override;
};
#endif
