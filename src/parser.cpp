#include "parser.h"
#include <stdexcept>

Parser::Parser(vector<Token> tokens) {

    this->tokens = tokens;
    position = 0;
}


// Parse numbers
ASTNode* Parser::parseNumber() {

    if (position >= tokens.size()) {
        throw runtime_error("Expected number");
    }

    Token token = tokens[position];

    if (token.type != NUMBER) {
        throw runtime_error("Expected number");
    }

    position++;

    return new NumberNode(stoi(token.value));
}


// Handle * and /
ASTNode* Parser::parseTerm() {

    ASTNode* left = parseNumber();

    while (position < tokens.size() &&
           tokens[position].type == OPERATOR &&
           (tokens[position].value == "*" ||
            tokens[position].value == "/")) {

        string op = tokens[position].value;

        position++;

        ASTNode* right = parseNumber();

        left = new BinaryNode(op, left, right);
    }

    return left;
}


// Handle + and -
ASTNode* Parser::parseExpression() {

    ASTNode* left = parseTerm();

    while (position < tokens.size() &&
           tokens[position].type == OPERATOR &&
           (tokens[position].value == "+" ||
            tokens[position].value == "-")) {

        string op = tokens[position].value;

        position++;

        ASTNode* right = parseTerm();

        left = new BinaryNode(op, left, right);
    }

    return left;
}
