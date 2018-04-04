#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
#define PARAMETERSMAX 20
using namespace std;
void printTokens(istringstream iss) {
    vector<string> v;
    istringstream s;

    while (iss >> quoted(s)) {
        v.push_back(s);
    }

    for(auto& str: v)
        cout << str << std::endl;
}

int main() {
	string cmd;
    string command;
	char *parameters[PARAMETERSMAX];

    while (true) {
        cout << "Enter command: ";
        getline(std::cin, command);
        cout << "Command: \"" << command << "\"!\n";
        printTokens(command);
    }
    return 0;
}

