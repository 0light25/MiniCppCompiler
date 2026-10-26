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
    ASTNode* parseAssignment();
    ASTNode* parseExpression();
    ASTNode* parseTerm();
    ASTNode* parseFactor();
    ASTNode* parseNumber();
ASTNode* parseCondition();
ASTNode* parseCoutStatement();
ASTNode* parseIfStatement();
ASTNode* parseWhileStatement();
ASTNode* parseStatement();

void expect(const string& value);
public:

    Parser(vector<Token> tokens);
ASTNode* parseMainProgram();
    ASTNode* parseDeclaration();

    // DAY 15
    ASTNode* parseProgram();
};

#endif
