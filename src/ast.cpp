#include "symbol_table.h"
#include "ast.h"
#include <stdexcept>
using namespace std;
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


IfNode::IfNode(ASTNode* condition,
               ProgramNode* body,
               ProgramNode* elseBody) {
    this->condition = condition;
    this->body = body;
    this->elseBody = elseBody;
}

IfNode::~IfNode() {
    delete condition;
    delete body;
    delete elseBody;
}

void IfNode::print(int indent) {

    cout << string(indent * 2, ' ')
         << "IfStatement" << endl;

    cout << string((indent + 1) * 2, ' ')
         << "Condition:" << endl;

    condition->print(indent + 2);

    cout << string((indent + 1) * 2, ' ')
         << "Then:" << endl;

    body->print(indent + 2);

    if (elseBody != nullptr) {

        cout << string((indent + 1) * 2, ' ')
             << "Else:" << endl;

        elseBody->print(indent + 2);
    }
}
WhileNode::WhileNode(ASTNode* condition, ProgramNode* body) {
    this->condition = condition;
    this->body = body;
}

void WhileNode::print(int indent) {

    cout << string(indent * 2, ' ')
         << "WhileStatement" << endl;

    cout << string((indent + 1) * 2, ' ')
         << "Condition:" << endl;

    condition->print(indent + 2);

    cout << string((indent + 1) * 2, ' ')
         << "Body:" << endl;

    body->print(indent + 2);
}

WhileNode::~WhileNode() {
    delete condition;
    delete body;
}
void NumberNode::checkSemantics(SymbolTable& symbols) {
    // Numbers don't require variable checking
}

void IdentifierNode::checkSemantics(SymbolTable& symbols) {
    symbols.checkVariable(name);
}
void BinaryNode::checkSemantics(SymbolTable& symbols) {
 //   left->checkSemantics(symbols);
  //  right->checkSemantics(symbols);
      inferType(symbols);
}
void VariableDeclarationNode::checkSemantics(
    SymbolTable& symbols
) {
    if (value != nullptr) {

        string valueType = value->inferType(symbols);

        if (valueType != type) {
            throw runtime_error(
                "Semantic Error: Type mismatch in declaration of '"
                + name + "'. Expected " + type
                + ", got " + valueType
            );
        }
    }

    symbols.declareVariable(name, type);
}
void AssignmentNode::checkSemantics(
    SymbolTable& symbols
) {
    string variableType = symbols.getType(name);

    if (expression == nullptr) {
        throw runtime_error(
            "Semantic Error: Missing assignment expression"
        );
    }

    string expressionType = expression->inferType(symbols);

    if (variableType != expressionType) {
        throw runtime_error(
            "Semantic Error: Type mismatch in assignment to '"
            + name + "'. Expected " + variableType
            + ", got " + expressionType
        );
    }
}
void ProgramNode::checkSemantics(SymbolTable& symbols) {

    for (ASTNode* statement : statements) {
        statement->checkSemantics(symbols);
    }
}

void IfNode::checkSemantics(SymbolTable& symbols) {

    // Condition uses the surrounding scope
    condition->checkSemantics(symbols);

    // New scope for the if block
    SymbolTable thenScope(&symbols);

    if (body != nullptr) {
        body->checkSemantics(thenScope);
    }

    // Separate scope for the else block
    if (elseBody != nullptr) {
        SymbolTable elseScope(&symbols);
        elseBody->checkSemantics(elseScope);
    }
}


void WhileNode::checkSemantics(SymbolTable& symbols) {

    // Condition uses the outer scope
    condition->checkSemantics(symbols);

    // New scope for the loop body
    SymbolTable loopScope(&symbols);

    if (body != nullptr) {
        body->checkSemantics(loopScope);
    }
}
string ASTNode::inferType(SymbolTable& symbols) {
    throw runtime_error(
        "Semantic Error: Node is not an expression"
    );
}
string NumberNode::inferType(SymbolTable& symbols) {
    return "int";
}
string IdentifierNode::inferType(SymbolTable& symbols) {
    return symbols.getType(name);
}
string BinaryNode::inferType(SymbolTable& symbols) {

    string leftType = left->inferType(symbols);
    string rightType = right->inferType(symbols);

    // Arithmetic operators
    if (op == "+" || op == "-" ||
        op == "*" || op == "/") {

        if (leftType != "int" || rightType != "int") {
            throw runtime_error(
                "Semantic Error: Arithmetic requires int operands"
            );
        }

        return "int";
    }

    // Relational operators
    if (op == ">" || op == "<" ||
        op == ">=" || op == "<=") {

        if (leftType != "int" || rightType != "int") {
            throw runtime_error(
                "Semantic Error: Comparison requires int operands"
            );
        }

        return "bool";
    }

    // Equality operators
    if (op == "==" || op == "!=") {

        if (leftType != rightType) {
            throw runtime_error(
                "Semantic Error: Incompatible comparison types"
            );
        }

        return "bool";
    }

    throw runtime_error(
        "Semantic Error: Unsupported binary operator " + op
    );
}
int ASTNode::evaluate() {
    throw runtime_error(
        "Evaluation not implemented for this AST node"
    );
}
int NumberNode::evaluate() {
    return value;
}
int BinaryNode::evaluate() {

    int leftValue = left->evaluate();
    int rightValue = right->evaluate();

    if (op == "+") {
        return leftValue + rightValue;
    }

    if (op == "-") {
        return leftValue - rightValue;
    }

    if (op == "*") {
        return leftValue * rightValue;
    }

    if (op == "/") {

        if (rightValue == 0) {
            throw runtime_error(
                "Runtime Error: Division by zero"
            );
        }

        return leftValue / rightValue;
    }

    throw runtime_error(
        "Unsupported operator: " + op
    );
}

