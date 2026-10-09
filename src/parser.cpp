
#include "parser.h"
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

        ASTNode* statement = nullptr;

        try {

            // Variable declaration
            if (tokens[position].value == "int" ||
                tokens[position].value == "float" ||
                tokens[position].value == "char") {

                statement = parseDeclaration();
            }

            // Assignment statement
            else if (tokens[position].type == IDENTIFIER) {

                statement = parseAssignment();
            }

            else {
                cout << "Error: Unexpected token: "
                     << tokens[position].value << endl;
                break;
            }

            if (statement != nullptr) {
                program->addStatement(statement);
            }
            else {
                cout << "Error: Unable to parse statement" << endl;
                break;
            }

        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            break;
        }
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

