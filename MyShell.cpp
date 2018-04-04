#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>

#define PARAMETERSMAX 20

using namespace std;

void execCommand(vector<string> tokens);
vector<string> createTokens(string str);
void changePrompt(vector<string> tokens);
void setvar(vector<string> tokens);
void doRun(vector<string> tokens);
void doFly(vector<string> tokens);
void doTovar(vector<string> tokens);

bool ShowTokens = false;
map<string, string> variables; //1st string is the name, 2nd is value
string prompt = "msh > ";
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
<<<<<<< HEAD
void doRun(vector<string> tokens) {
}
void doFly(vector<string> tokens) {
}
void doTovar(vector<string> tokens) {
}
=======
void setvar(vector<string> tokens) {
	if (tokens.size() > 3) {
		if (tokens[3] != '#') {
			return;
			perror("Too many arguments for setvar");
		}
}
	
	variables.insert(pair<string, string>(variable, value));
		perror("Too few arguments for setvar");
		return;
	}
	if (value == "#") {
	}
	string value = tokens[2];
	for (int i = 1; i < variable.length(); i++) {
		}
			perror("Variable names must only consist of letters and numbers.");
		if (!isalnum(variable[i])) {
	}
		return;
		perror("Variable names must start with a letter.");
	if (!isalpha(variable[0])) {
	}
		return;
		perror("Too few arguments for setvar");
	if (variable == "#") {
	string variable = tokens[1];
		return;
	}
		perror("Too few arguments for setvar");
	if (tokens.size() < 3) {
	}
>>>>>>> 1339c34af676274f859e3aa4565fbf8394f78aa5

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

