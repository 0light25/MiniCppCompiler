
#include "parser.h"
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

// Constructor
Parser::Parser(vector<Token> tokens) {
    this->tokens = tokens;
    position = 0;
}


// Parse complete program

ASTNode* Parser::parseProgram() {

    ProgramNode* program = new ProgramNode();

    while (position < tokens.size()) {

        ASTNode* statement = parseStatement();

        program->addStatement(statement);
    }

    return program;
}

// Parse assignment statement
// Example: x = x + 5;
ASTNode* Parser::parseAssignment() {

    if (position >= tokens.size() ||
        tokens[position].type != IDENTIFIER) {

        throw runtime_error("Expected variable name");
    }

    string variableName = tokens[position].value;
    position++;

    // Check =
    if (position >= tokens.size() ||
        tokens[position].value != "=") {

        throw runtime_error("Expected =");
    }

    position++;

    // Parse right-hand side expression
    ASTNode* expression = parseExpression();

    if (expression == nullptr) {
        throw runtime_error("Invalid assignment expression");
    }

    // Check ;
    if (position >= tokens.size() ||
        tokens[position].value != ";") {

        delete expression;
        throw runtime_error("Expected ;");
    }

    position++;

    return new AssignmentNode(variableName, expression);
}


// Parse number
ASTNode* Parser::parseNumber() {

    if (position >= tokens.size()) {
        return nullptr;
    }

    Token token = tokens[position];

    if (token.type == NUMBER) {

        position++;

        return new NumberNode(stoi(token.value));
    }

    return nullptr;
}


// Parse number, identifier, or parentheses
ASTNode* Parser::parseFactor() {

    if (position >= tokens.size()) {
        return nullptr;
    }

    // Number
    if (tokens[position].type == NUMBER) {

        return parseNumber();
    }

    // Identifier
    if (tokens[position].type == IDENTIFIER) {

        string name = tokens[position].value;
        position++;

        return new IdentifierNode(name);
    }

    // Parentheses
    if (tokens[position].value == "(") {

        // Skip (
        position++;

        ASTNode* node = parseExpression();

        // Check )
        if (position < tokens.size() &&
            tokens[position].value == ")") {

            position++;
        }
        else {
            cout << "Error: Expected )" << endl;
            delete node;
            return nullptr;
        }

        return node;
    }

    return nullptr;
}


// Handle multiplication and division
ASTNode* Parser::parseTerm() {

    ASTNode* left = parseFactor();

    if (left == nullptr) {
        return nullptr;
    }

    while (position < tokens.size() &&
          (tokens[position].value == "*" ||
           tokens[position].value == "/")) {

        string op = tokens[position].value;

        position++;

        ASTNode* right = parseFactor();

        if (right == nullptr) {
            delete left;
            return nullptr;
        }

        left = new BinaryNode(op, left, right);
    }

    return left;
}


// Handle addition and subtraction
ASTNode* Parser::parseExpression() {

    ASTNode* left = parseTerm();

    if (left == nullptr) {
        return nullptr;
    }

    while (position < tokens.size() &&
          (tokens[position].value == "+" ||
           tokens[position].value == "-")) {

        string op = tokens[position].value;

        position++;

        ASTNode* right = parseTerm();

        if (right == nullptr) {
            delete left;
            return nullptr;
        }

        left = new BinaryNode(op, left, right);
    }

    return left;
}


// Parse variable declaration
// Example: int x = 10;
ASTNode* Parser::parseDeclaration() {

    // Check data type
    if (position >= tokens.size() ||
        tokens[position].type != KEYWORD) {

        cout << "Error: Expected data type" << endl;
        return nullptr;
    }

    string type = tokens[position].value;
    position++;

    // Check variable name
    if (position >= tokens.size() ||
        tokens[position].type != IDENTIFIER) {

        cout << "Error: Expected variable name" << endl;
        return nullptr;
    }

    string name = tokens[position].value;
    position++;

    // Check =
    if (position >= tokens.size() ||
        tokens[position].value != "=") {

        cout << "Error: Expected =" << endl;
        return nullptr;
    }

    position++;

    // Parse expression
    ASTNode* value = parseExpression();

    if (value == nullptr) {
        cout << "Error: Invalid expression" << endl;
        return nullptr;
    }

    // Check ;
    if (position >= tokens.size() ||
        tokens[position].value != ";") {

        cout << "Error: Expected ;" << endl;

        delete value;
        return nullptr;
    }

    position++;

    return new VariableDeclarationNode(
        type,
        name,
        value
    );
}

void Parser::expect(const string& value) {

    if (position >= tokens.size() ||
        tokens[position].value != value) {

        throw runtime_error("Expected '" + value + "'");
    }

    position++;
}

ASTNode* Parser::parseCondition() {

    // Parse left expression
    ASTNode* left = parseExpression();

    // Check operator
    if (position >= tokens.size()) {
        delete left;
        throw runtime_error(
            "Expected comparison operator"
        );
    }

    string op = tokens[position].value;

    // Supported operators
    if (op != ">" &&
        op != "<" &&
        op != ">=" &&
        op != "<=" &&
        op != "==" &&
        op != "!=") {

        delete left;

        throw runtime_error(
            "Invalid comparison operator"
        );
    }

    position++;

    // Parse right expression
    ASTNode* right = parseExpression();

    // Construct comparison AST
    return new BinaryNode(op, left, right);
}


ASTNode* Parser::parseIfStatement() {

    // Step 1: Expect if (
    expect("if");
    expect("(");

    // Step 2: Parse condition
    ASTNode* condition = parseCondition();

    expect(")");

    // Step 3: Parse if body
    expect("{");

    ProgramNode* body = new ProgramNode();

    while (position < tokens.size() &&
           tokens[position].value != "}") {

        ASTNode* statement = parseStatement();
        body->addStatement(statement);
    }

    expect("}");

    // Step 4: Check for optional else
    ProgramNode* elseBody = nullptr;

    if (position < tokens.size() &&
        tokens[position].value == "else") {

        expect("else");
        expect("{");

        elseBody = new ProgramNode();

        while (position < tokens.size() &&
               tokens[position].value != "}") {

            ASTNode* statement = parseStatement();
            elseBody->addStatement(statement);
        }

        expect("}");
    }

    // Step 5: Create AST node
    return new IfNode(condition, body, elseBody);
}

ASTNode* Parser::parseStatement() {

    if (position >= tokens.size()) {
        throw runtime_error("Expected statement");
    }

    string value = tokens[position].value;

    // If statement
    if (value == "if") {
        return parseIfStatement();
    }

    // Variable declaration
    if (value == "int" ||
        value == "float" ||
        value == "char") {

        return parseDeclaration();
    }

    // Assignment
    if (tokens[position].type == IDENTIFIER) {
        return parseAssignment();
    }

    throw runtime_error(
        "Unexpected token: " + value
    );
}

