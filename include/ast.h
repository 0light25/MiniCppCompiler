#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>

using namespace std;

class ASTNode {
public:
    virtual void print(int indent = 0) = 0;
    virtual ~ASTNode() {}
};


// Number node
class NumberNode : public ASTNode {
private:
    int value;

public:
    NumberNode(int value);

    void print(int indent = 0) override;
};


// Binary operation node
class BinaryNode : public ASTNode {
private:
    string op;
    ASTNode* left;
    ASTNode* right;

public:
    BinaryNode(string op, ASTNode* left, ASTNode* right);

    void print(int indent = 0) override;

    ~BinaryNode();
};


// Variable declaration node
class VariableDeclarationNode : public ASTNode {
private:
    string type;
    string name;
    ASTNode* value;

public:
    VariableDeclarationNode(
        string type,
        string name,
        ASTNode* value
    );

    void print(int indent = 0) override;

    ~VariableDeclarationNode();
};

#endif
