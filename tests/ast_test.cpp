#include <iostream>
#include "ast.h"

using namespace std;

int main() {

    NumberNode num10(10);
    NumberNode num20(20);
    NumberNode num5(5);

    BinaryNode multiply(
        "*",
        &num20,
        &num5
    );

    BinaryNode add(
        "+",
        &num10,
        &multiply
    );

    cout << "AST for: 10 + 20 * 5" << endl;
    cout << "----------------------" << endl;

    add.print();

    return 0;
}
