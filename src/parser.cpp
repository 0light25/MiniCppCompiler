#include "parser.h"
#include <iostream>

using namespace std;

Parser::Parser(vector<Token> tokens) {
    this->tokens = tokens;
    position = 0;
}

ASTNode* Parser::parseProgram() {

    ProgramNode* program = new ProgramNode();

    while (position < tokens.size()) {

        ASTNode* statement = parseDeclaration();

        if (statement != nullptr) {
            program->addStatement(statement);
        }
        else {
            cout << "Error: Unable to parse statement" << endl;
            break;
        }
    }

    return program;
}

// Parse a number
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


// Parse number OR parentheses
ASTNode* Parser::parseFactor() {

    if (position >= tokens.size()) {
        return nullptr;
    }

    // Normal number
    if (tokens[position].type == NUMBER) {
        return parseNumber();
    }

    // Parentheses
    if (tokens[position].value == "(") {

        // Skip '('
        position++;

        // Parse expression inside parentheses
        ASTNode* node = parseExpression();

        // Check for ')'
        if (position < tokens.size() &&
            tokens[position].value == ")") {

            // Skip ')'
            position++;
        }
        else {
            cout << "Error: Expected )" << endl;
        }

        return node;
    }

    return nullptr;
}


// Handle * and /
ASTNode* Parser::parseTerm() {

    ASTNode* left = parseFactor();

    while (position < tokens.size() &&
          (tokens[position].value == "*" ||
           tokens[position].value == "/")) {

        string op = tokens[position].value;

        position++;

        ASTNode* right = parseFactor();

        left = new BinaryNode(op, left, right);
    }

    return left;
}


// Handle + and -
ASTNode* Parser::parseExpression() {

    ASTNode* left = parseTerm();

    while (position < tokens.size() &&
          (tokens[position].value == "+" ||
           tokens[position].value == "-")) {

        string op = tokens[position].value;

        position++;

        ASTNode* right = parseTerm();

        left = new BinaryNode(op, left, right);
    }

    return left;
}

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
