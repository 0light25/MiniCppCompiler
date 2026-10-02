#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "lexer.h"
#include "ast.h"

using namespace std;

class Parser {
private:
    vector<Token> tokens;
    int position;

public:
    Parser(vector<Token> tokens);

    ASTNode* parseNumber();
};

#endif
