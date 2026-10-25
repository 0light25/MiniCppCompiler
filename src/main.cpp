#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>

#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "symbol_table.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Step 1: Check command-line argument
    if (argc != 2) {
        cerr << "Usage: compiler <source_file>" << endl;
        return 1;
    }

    // Step 2: Read source code
    ifstream file(argv[1]);

    if (!file.is_open()) {
        cerr << "Error: Cannot open file: "
             << argv[1] << endl;
        return 1;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string sourceCode = buffer.str();

    try {

        // Step 3: Lexical Analysis
        Lexer lexer;
        vector<Token> tokens = lexer.tokenize(sourceCode);

        cout << "Lexical Analysis: PASS" << endl;

        // Step 4: Syntax Analysis
        Parser parser(tokens);

        unique_ptr<ASTNode> root(parser.parseMainProgram());

        if (!root) {
            throw runtime_error("Parsing failed");
        }

        cout << "Syntax Analysis: PASS" << endl;

        // Step 5: Semantic Analysis
        SymbolTable symbols;
        root->checkSemantics(symbols);

        cout << "Semantic Analysis: PASS" << endl;

        // Step 6: Execute AST
        RuntimeVariables variables;
        root->evaluate(variables);

        cout << "Execution: PASS" << endl;

        // Step 7: Display final values
        cout << "\nFinal Variable Values:" << endl;

        vector<string> names;

        for (const auto& item : variables) {
            names.push_back(item.first);
        }

        sort(names.begin(), names.end());

        for (const string& name : names) {
            cout << name << " = "
                 << variables.at(name) << endl;
        }

        cout << "\nProgram executed successfully!"
             << endl;

    } catch (const exception& e) {

        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

