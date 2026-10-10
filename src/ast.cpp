#include "ast.h"

NumberNode::NumberNode(int value) {
    this->value = value;
}

void NumberNode::print(int indent) {
    cout << string(indent * 2, ' ')
         << "Number: " << value << endl;
}

BinaryNode::BinaryNode(
    string op, ASTNode* left, ASTNode* right
) {
    this->op = op;
    this->left = left;
    this->right = right;
}

void BinaryNode::print(int indent) {
    cout << string(indent * 2, ' ')
         << "BinaryOperator: " << op << endl;

    if (left)
        left->print(indent + 1);

    if (right)
        right->print(indent + 1);
}

BinaryNode::~BinaryNode() {
    delete left;
    delete right;
}

VariableDeclarationNode::VariableDeclarationNode(
    string type, string name, ASTNode* value
) {
    this->type = type;
    this->name = name;
    this->value = value;
}

void VariableDeclarationNode::print(int indent) {
    cout << string(indent * 2, ' ')
         << "VariableDeclaration: "
         << type << " " << name << endl;

    if (value)
        value->print(indent + 1);
}

VariableDeclarationNode::~VariableDeclarationNode() {
    delete value;
}

// Day 15
void ProgramNode::addStatement(ASTNode* statement) {
    statements.push_back(statement);
}

void ProgramNode::print(int indent) {
    cout << string(indent * 2, ' ')
         << "Program" << endl;

    for (ASTNode* statement : statements) {
        if (statement)
            statement->print(indent + 1);
    }
}

ProgramNode::~ProgramNode() {
    for (ASTNode* statement : statements) {
        delete statement;
    }
}

IdentifierNode::IdentifierNode(string name) {
    this->name = name;
}

void IdentifierNode::print(int indent) {
    cout << string(indent, ' ')
         << "Identifier: " << name << endl;
}

AssignmentNode::AssignmentNode(
    string name, ASTNode* expression
) {
    this->name = name;
    this->expression = expression;
}

AssignmentNode::~AssignmentNode() {
    delete expression;
}

void AssignmentNode::print(int indent) {
    cout << string(indent, ' ')
         << "Assignment: " << name << endl;

    if (expression != nullptr) {
        expression->print(indent + 2);
    }
}

// Constructor
IfNode::IfNode(ASTNode* condition, ProgramNode* body) {
    this->condition = condition;
    this->body = body;
}

// Destructor
IfNode::~IfNode() {
    delete condition;
    delete body;
}

// Print the If AST
void IfNode::print(int indent) {

    cout << string(indent * 2, ' ')
         << "IfStatement" << endl;

    cout << string((indent + 1) * 2, ' ')
         << "Condition:" << endl;

    condition->print(indent + 2);

    cout << string((indent + 1) * 2, ' ')
         << "Body:" << endl;

    body->print(indent + 2);
}
