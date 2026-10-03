#include "parser.h"

Parser::Parser(vector<Token> tokens) {
    this->tokens = tokens;
    position = 0;
}


// Day 10
ASTNode* Parser::parseNumber() {

    if (position >= tokens.size()) {
        return nullptr;
    }

    Token token = tokens[position];

    if (token.type != NUMBER) {
        return nullptr;
    }

    position++;

    int value = stoi(token.value);

    return new NumberNode(value);
}


// Day 11
ASTNode* Parser::parseExpression() {

    // Parse left side
    ASTNode* left = parseNumber();

    if (left == nullptr) {
        return nullptr;
    }

    // Check for operator
    if (position < tokens.size() &&
        tokens[position].type == OPERATOR &&
        (tokens[position].value == "+" ||
         tokens[position].value == "-")) {

        string op = tokens[position].value;

        position++;

        // Parse right side
        ASTNode* right = parseNumber();

        if (right == nullptr) {
            return left;
        }

        // Create BinaryNode
        return new BinaryNode(op, left, right);
    }

    // Only a number was present
    return left;
}
