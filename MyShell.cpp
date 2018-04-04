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
	}
	else if (command == "setprompt") {
		changePrompt(tokens);
	}
	//keep creating else if's for rest of commands
}
void setvar(vector<string> tokens) {
	if (tokens.size() > 3) {
		if (tokens[3] != '#') {
			perror("Too many arguments for setvar");
			return;
		}
	}
	if (tokens.size() < 3) {
		perror("Too few arguments for setvar");
		return;
	}
	string variable = tokens[1];
	if (variable == "#") {
		perror("Too few arguments for setvar");
		return;
	}
	if (!isalpha(variable[0])) {
		perror("Variable names must start with a letter.");
		return;
	}
	for (int i = 1; i < variable.length(); i++) {
		if (!isalnum(variable[i])) {
			perror("Variable names must only consist of letters and numbers.");
		}
	}
	string value = tokens[2];
	if (value == "#") {
		perror("Too few arguments for setvar");
		return;
	}
	variables.insert(pair<string, string>(variable, value));

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
			for (auto& str : tokens)
				cout << str << endl;
	}
	return 0;
}

