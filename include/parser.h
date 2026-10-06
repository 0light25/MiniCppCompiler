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

    ASTNode* parseNumber();
    ASTNode* parseFactor();
    ASTNode* parseTerm();
 //   ASTNode* parseDeclaration();

public:
    Parser(vector<Token> tokens);
 ASTNode* parseDeclaration();
    ASTNode* parseExpression();
};

#endif
