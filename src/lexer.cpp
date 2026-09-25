#include "lexer.h"
#include <cctype>
#include <set>
using namespace std;

bool isKeyword(string word) {
    set<string> keywords = {
        "int",
        "if",
        "else",
        "while",
        "for",
        "return",
        "class",
        "void"
    };

    return keywords.count(word);
}
vector<Token> Lexer::tokenize(string code) {

    vector<Token> tokens;

    for (int i = 0; i < code.length(); i++) {

        // Skip spaces
        if (isspace(code[i])) {
            continue;
        }

        // Number
        if (isdigit(code[i])) {

            string number = "";

            while (i < code.length() && isdigit(code[i])) {
                number += code[i];
                i++;
            }

            i--;

            tokens.push_back({NUMBER, number});
        }

        // Identifier or keyword
        else if (isalpha(code[i]) || code[i] == '_') {

    string word = "";

    while (i < code.length() &&
           (isalnum(code[i]) || code[i] == '_')) {

        word += code[i];
        i++;
    }

    i--;

    if (word == "int" ||
        word == "float" ||
        word == "char" ||
        word == "return" ||
        word == "if" ||
        word == "else" ||
        word == "while" ||
        word == "for" ||
        word == "void") {

        tokens.push_back({KEYWORD, word});
    }
    else {
        tokens.push_back({IDENTIFIER, word});
    }
}

      // Operators
// Operators
else if (code[i] == '+' ||
         code[i] == '-' ||
         code[i] == '*' ||
         code[i] == '/' ||
         code[i] == '=' ||
         code[i] == '!' ||
         code[i] == '<' ||
         code[i] == '>') {

    string op(1, code[i]);

    // Check for two-character operators
    if (i + 1 < code.length() &&
        (code[i + 1] == '=')) {

        op += code[i + 1];
        i++;
    }

    tokens.push_back({OPERATOR, op});
}

        // Symbols
        else if (code[i] == ';' ||
         code[i] == '(' ||
         code[i] == ')' ||
         code[i] == '{' ||
         code[i] == '}' ||
         code[i] == '[' ||
         code[i] == ']' ||
         code[i] == ',') {

            string symbol(1, code[i]);

            tokens.push_back({SYMBOL, symbol});
        }

        // Unknown character
        else {
            string unknown(1, code[i]);

            tokens.push_back({UNKNOWN, unknown});
        }
    }

    return tokens;
}
