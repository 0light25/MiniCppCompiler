#include "ast.h"


NumberNode::NumberNode(int value) {
    this->value = value;
}


void NumberNode::print(int indent) {

    for (int i = 0; i < indent; i++) {
        cout << "  ";
    }

    cout << "Number: " << value << endl;
}


BinaryNode::BinaryNode(string op, ASTNode* left, ASTNode* right) {

    this->op = op;
    this->left = left;
    this->right = right;
}


void BinaryNode::print(int indent) {

    for (int i = 0; i < indent; i++) {
        cout << "  ";
    }

    cout << "BinaryOperator: " << op << endl;

    left->print(indent + 1);
    right->print(indent + 1);
}
