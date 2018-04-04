//pushing this again
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
bool errorchecker(vector<string> tokens, int wantedArguements);

string ShowTokens = "0";
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
	else if () {

	}
	//keep creating else if's for rest of commands
}
void doRun(vector<string> tokens) {
}
void doFly(vector<string> tokens) {
}
void doTovar(vector<string> tokens) {
}
void setvar(vector<string> tokens) {
	if (errorchecker(tokens, 3)) {
		return;
	}
	string variable = tokens[1];
	
	//if the first character in the variable is not a letter
	if (!isalpha(variable[0])) {
		fprintf(stderr,"Variable names must start with a letter.");
		return;
	}
	//if the variable consists of anything other than letters/numbers
	for (int i = 1; i < variable.length(); i++) {
		if (!isalnum(variable[i])) {
			fprintf(stderr,"Variable names must only consist of letters and numbers.");
			return;
		}
	}
	string value = tokens[2];
	if (variable == "ShowTokens") {
		ShowTokens = value;
	}
		perror("Too few arguments for setvar");
	if (tokens.size() < 3) {
	}
	variables.insert(pair<string, string>(variable, value));
	else
		variables.insert(pair<string, string>(variable, value));

}
//returns true if there is an error relating to number of tokens
bool errorchecker(vector<string> tokens, int wantedArguements) {
	if (tokens.size()>wantedArguements) {
		if (tokens[wantedArguements] != "#") {
			fprintf(stderr,"Too many arguements for %s\n", tokens[0]);
			return true;
		}
	}
	if (tokens.size() < wantedArguements) {
		fprintf(stderr,"Too few arguements for %s\n", tokens[0]);
		return true;
	}
	for (int i = 1; i < wantedArguements; i++) {
		if (tokens[i]=="#") {
			fprintf(stderr, "Too few arguements for %s\n", tokens[0]);
			return true;
		}
	}
	return false;
}
void changePrompt(vector<string> tokens) {
	if (errorchecker(tokens, 2)) {
		return;
	}
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
		execCommand(tokens);
		if (ShowTokens=="1")
			for (auto& str : tokens)
				cout << str << endl;
	}
	return 0;
}

