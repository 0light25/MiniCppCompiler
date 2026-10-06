#include "ast.h"


// NumberNode
NumberNode::NumberNode(int value) {
    this->value = value;
}

void NumberNode::print(int indent) {

    for (int i = 0; i < indent; i++)
        cout << "  ";

    cout << "Number: " << value << endl;
}


// BinaryNode
BinaryNode::BinaryNode(
    string op,
    ASTNode* left,
    ASTNode* right
) {
    this->op = op;
    this->left = left;
    this->right = right;
}

void BinaryNode::print(int indent) {

    for (int i = 0; i < indent; i++)
        cout << "  ";

    cout << "BinaryOperator: " << op << endl;

    if (left)
        left->print(indent + 1);

    if (right)
        right->print(indent + 1);
}

BinaryNode::~BinaryNode() {
    delete left;
    delete right;
}


// VariableDeclarationNode
VariableDeclarationNode::VariableDeclarationNode(
    string type,
    string name,
    ASTNode* value
) {
    this->type = type;
    this->name = name;
    this->value = value;
}

void VariableDeclarationNode::print(int indent) {

    for (int i = 0; i < indent; i++)
        cout << "  ";

    cout << "VariableDeclaration: "
         << type << " "
         << name
         << endl;

    if (value)
        value->print(indent + 1);
}

VariableDeclarationNode::~VariableDeclarationNode() {
    delete value;
}
