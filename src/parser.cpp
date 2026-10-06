#include "parser.h"
#include <iostream>

using namespace std;

Parser::Parser(vector<Token> tokens) {
    this->tokens = tokens;
    position = 0;
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
