#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

#define PARAMETERSMAX 20
bool ShowTokens = true;

using namespace std;

vector<string> createTokens(string str) {
    istringstream iss(str);
    vector<string> tokens;
    string s;

    while (iss >> quoted(s)) {
        tokens.push_back(s);
    }

    return tokens;
}

int main() {
    string cmd;
    string command;
    char *parameters[PARAMETERSMAX];

    while (true) {
        cout << "Enter command: ";
        getline(cin, command);
        cout << "Command: \"" << command << "\"!\n";
        vector<string> tokens = createTokens(command);
        if (ShowTokens)
            for(auto& str: tokens)
                cout << str << endl;
    }
    return 0;
}

