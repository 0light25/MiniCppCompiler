
#include "lexer.h"
#include <cctype>
#include <stdexcept>
#include <set>

using namespace std;

bool isKeyword(string word) {
    set<string> keywords = {
        "int", "float", "char", "if", "else",
        "while", "for", "return", "class", "void"
    };

    return keywords.count(word) > 0;
}

vector<Token> Lexer::tokenize(string code) {

    vector<Token> tokens;

    for (int i = 0; i < code.length(); i++) {

        // 1. Skip whitespace
        if (isspace(code[i])) {
            continue;
        }

        // 2. Numbers
        else if (isdigit(code[i])) {

            string number = "";

            while (i < code.length() && isdigit(code[i])) {
                number += code[i];
                i++;
            }

            i--;

            tokens.push_back({NUMBER, number});
        }

        // 3. Identifiers and keywords
        else if (isalpha(code[i]) || code[i] == '_') {

            string word = "";

            while (i < code.length() &&
                   (isalnum(code[i]) || code[i] == '_')) {

                word += code[i];
                i++;
            }

            i--;

            if (isKeyword(word)) {
                tokens.push_back({KEYWORD, word});
            }
            else {
                tokens.push_back({IDENTIFIER, word});
            }
        }

        // 4. Single-line comments
        else if (code[i] == '/' &&
                 i + 1 < code.length() &&
                 code[i + 1] == '/') {

            i += 2;

            while (i < code.length() && code[i] != '\n') {
                i++;
            }
        }

        // 5. Multi-line comments
        else if (code[i] == '/' &&
                 i + 1 < code.length() &&
                 code[i + 1] == '*') {

            i += 2;

            while (i + 1 < code.length() &&
                   !(code[i] == '*' && code[i + 1] == '/')) {
                i++;
            }

            if (i + 1 >= code.length()) {
                throw runtime_error("Unterminated comment");
            }

            i++;
        }

        // 6. String literals (Day 31)
        else if (code[i] == '"') {

            i++;

            string value = "";

            while (i < code.length() && code[i] != '"') {

                if (code[i] == '\\' &&
                    i + 1 < code.length()) {

                    if (code[i + 1] == 'n') {
                        value += '\n';
                        i += 2;
                        continue;
                    }

                    if (code[i + 1] == '"' ||
                        code[i + 1] == '\\') {
                        value += code[i + 1];
                        i += 2;
                        continue;
                    }
                }

                value += code[i];
                i++;
            }

            if (i >= code.length()) {
                throw runtime_error("Unterminated string literal");
            }

            tokens.push_back({STRING_LITERAL, value});
        }

        // 7. cout insertion operator (Day 31)
        else if (code[i] == '<' &&
                 i + 1 < code.length() &&
                 code[i + 1] == '<') {

            tokens.push_back({OPERATOR, "<<"});
            i++;
        }

        // 8. Other operators
        else if (code[i] == '+' ||
                 code[i] == '-' ||
                 code[i] == '*' ||
                 code[i] == '/' ||
                 code[i] == '=' ||
                 code[i] == '<' ||
                 code[i] == '>' ||
                 code[i] == '!') {

            string op(1, code[i]);

            // Two-character comparison operators
            if (i + 1 < code.length() &&
                code[i + 1] == '=' &&
                (code[i] == '>' ||
                 code[i] == '<' ||
                 code[i] == '=' ||
                 code[i] == '!')) {

                op += '=';
                i++;
            }

            if (op == "!") {
                tokens.push_back({UNKNOWN, op});
            }
            else {
                tokens.push_back({OPERATOR, op});
            }
        }

        // 9. Symbols
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

        // 10. Unknown characters
        else {

            string unknown(1, code[i]);
            tokens.push_back({UNKNOWN, unknown});
        }
    }

    return tokens;
}

