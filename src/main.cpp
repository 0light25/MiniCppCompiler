#include <iostream>
#include "lexer.h"

using namespace std;

int main() {

    string code = "int x = 10;";

    vector<string> tokens = tokenize(code);

    for (string token : tokens) {
        cout << token << endl;
    }

    return 0;
}