#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

#define PARAMETERSMAX 20
using namespace std;
void printTokens(string str) {
    istringstream iss(str);
    vector<string> v;
    string s;

    while (iss >> quoted(s)) {
        v.push_back(s);
    }
    for(auto& str: v)
        cout << str << endl;
}

int main() {
    string cmd;
    string command;
    char *parameters[PARAMETERSMAX];

    while (true) {
        cout << "Enter command: ";
        getline(cin, command);
        cout << "Command: \"" << command << "\"!\n";
        printTokens(command);
    }
    return 0;
}

