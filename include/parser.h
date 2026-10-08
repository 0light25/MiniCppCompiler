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

    ASTNode* parseExpression();
    ASTNode* parseTerm();
    ASTNode* parseFactor();
    ASTNode* parseNumber();

public:

    Parser(vector<Token> tokens);

    ASTNode* parseDeclaration();

    // DAY 15
    ASTNode* parseProgram();
};

#endif
