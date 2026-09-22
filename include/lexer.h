#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

using namespace std;

enum TokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    SYMBOL,
    UNKNOWN
};

struct Token {
    TokenType type;
    string value;
};

class Lexer {
public:
    vector<Token> tokenize(string code);
};

#endif