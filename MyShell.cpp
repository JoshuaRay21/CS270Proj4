#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

#define PARAMETERSMAX 20

using namespace std;

void execCommand(vector<string> tokens);
vector<string> createTokens(string str);
void changePrompt(vector<string> tokens);
void setvar(vector<string> tokens);

bool ShowTokens = false;
string prompt = "msh > ";

vector<string> variableNames;
vector<string> variableValues;

//The 2 above vectors should be thought of as parallel, 

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
    if (command == "setvar") {
        setvar(tokens);
    } else if (command == "setprompt") {
        changePrompt(tokens);
    }
    //keep creating else if's for rest of commands
}

void changePrompt(vector<string> tokens) {
    prompt = tokens[1];
}

int main() {
    string command;
    vector<string> parameters;
    string envp = "PATH";
    while (true) {
        cout << prompt;
        getline(cin, command);
        cout << "Command: \"" << command << "\"!\n";
        vector<string> tokens = createTokens(command);
        if (ShowTokens)
            for(auto& str: tokens)
                cout << str << endl;
    }
    return 0;
}

