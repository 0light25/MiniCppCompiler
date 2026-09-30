#ifndef AST_H
#define AST_H

#include <iostream>
#include <string>

using namespace std;

// Base class for all AST nodes
class ASTNode {
public:
    virtual void print(int indent = 0) = 0;

    virtual ~ASTNode() {}
};


// Represents a number such as 10, 20, 100
class NumberNode : public ASTNode {
private:
    int value;

public:
    NumberNode(int value);

    void print(int indent = 0);
};


// Represents binary expressions such as:
// 10 + 20
// x * 5
class BinaryNode : public ASTNode {
private:
    string op;
    ASTNode* left;
    ASTNode* right;

public:
    BinaryNode(string op, ASTNode* left, ASTNode* right);

    void print(int indent = 0);
};

#endif