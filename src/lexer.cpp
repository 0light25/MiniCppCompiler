#include "lexer.h"
#include <sstream>

vector<string> tokenize(string code) {
    vector<string> tokens;
    string word;

    stringstream ss(code);

    while (ss >> word) {
        tokens.push_back(word);
    }

    return tokens;
}