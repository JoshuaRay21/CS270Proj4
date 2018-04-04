#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

#define PARAMETERSMAX 20
bool ShowTokens = false;
vector<string> variableNames;
vector<string> variableValues;
//The 2 above vectors should be thought of as parallel, 

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
void execCommand(vector<string> tokens) {
	string command = tokens[0];
	if (strcmp(command, "setvar") == 0) {
		setvar();
	}
	//keep creating else if's for rest of commands
}

int main() {
    string cmd;
    string command;
	char *parameters[PARAMETERSMAX];
	char *envp[] = { (char*) "PATH!=bin", 0 };

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

