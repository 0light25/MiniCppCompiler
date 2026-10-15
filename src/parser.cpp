
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
        throw runtime_error(
            "Syntax Error: Expected expression "
            "but reached end of input"
        );
    }

    Token token = tokens[position];

    // Number
    if (token.type == NUMBER) {
        position++;
       // return new NumberNode(token.value);
    return new NumberNode(stoi(token.value));
	}

    // Variable
    if (token.type == IDENTIFIER) {
        position++;
        return new IdentifierNode(token.value);
    }

    // Parentheses
    if (token.value == "(") {
        position++;

        ASTNode* node = parseExpression();

        expect(")");

        return node;
    }

    throw runtime_error(
        "Syntax Error at token " +
        to_string(position + 1) +
        ": Expected expression but found '" +
        token.value + "'"
    );
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

    delete value;

    throw runtime_error(
        "Syntax Error: Expected ';' after variable declaration"
    );
}

    position++;

    return new VariableDeclarationNode(
        type,
        name,
        value
    );
}

void Parser::expect(const string& expected) {

    if (position >= tokens.size()) {
        throw runtime_error(
            "Syntax Error: Expected '" + expected +
            "' but reached end of input"
        );
    }

    if (tokens[position].value != expected) {
        throw runtime_error(
            "Syntax Error at token " +
            to_string(position + 1) +
            ": Expected '" + expected +
            "' but found '" +
            tokens[position].value + "'"
        );
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
        throw runtime_error("Unexpected end of input");
    }

    if (tokens[position].value == "int") {
        return parseDeclaration();
    }

    if (tokens[position].value == "if") {
        return parseIfStatement();
    }

    // DAY 20 - ADD THIS
    if (tokens[position].value == "while") {
        return parseWhileStatement();
    }

    if (tokens[position].type == IDENTIFIER) {
        return parseAssignment();
    }

    throw runtime_error(
        "Unexpected token: " + tokens[position].value
    );
}

ASTNode* Parser::parseWhileStatement() {

    // Expect while
    if (position >= tokens.size() ||
        tokens[position].value != "while") {
        throw runtime_error("Expected while");
    }

    position++;

    // Expect (
    if (position >= tokens.size() ||
        tokens[position].value != "(") {
        throw runtime_error("Expected ( after while");
    }

    position++;

    // Parse condition
    ASTNode* condition = parseCondition();

    // Expect )
    if (position >= tokens.size() ||
        tokens[position].value != ")") {
        throw runtime_error("Expected ) after condition");
    }

    position++;

    // Expect {
    if (position >= tokens.size() ||
        tokens[position].value != "{") {
        throw runtime_error("Expected { after while");
    }

    position++;

    ProgramNode* body = new ProgramNode();

    // Parse statements inside while
    while (position < tokens.size() &&
           tokens[position].value != "}") {

        body->addStatement(parseStatement());
    }

    // Expect }
    if (position >= tokens.size() ||
        tokens[position].value != "}") {
        throw runtime_error("Expected } after while body");
    }

    position++;

    return new WhileNode(condition, body);
}
