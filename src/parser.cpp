#include "parser.h"
#include <cstdlib>

Parser::Parser(vector<Token> tokens) {
    this->tokens = tokens;
    position = 0;
}

ASTNode* Parser::parseNumber() {

    if (position >= tokens.size()) {
        return nullptr;
    }

    Token token = tokens[position];

    if (token.type == NUMBER) {

        position++;

        int value = stoi(token.value);

        return new NumberNode(value);
    }

    return nullptr;
}
