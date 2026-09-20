#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    ifstream file("examples/program.mc");

    if (!file) {
        cout << "Could not open source file!" << endl;
        return 1;
    }

    string line;

    cout << "Source Code:" << endl;

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();

    return 0;
}