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
void showprocs(vector<string> tokens);
void done(vector<string> tokens);


string ShowTokens = "0";
map<string, string> variables; //1st string is the name, 2nd is value
string prompt = "msh > ";
string workingDir = "";
vector<string> procs; //vec of processes running in background
int exiting = -1; //this int is changed if done is called, if this is non neg, msh exits

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
	else if (command == "setdir") {
		//JRAY DOESNT KNOW HOW TO DEAL WITH DIRECTORY
	}
	else if (command == "showprocs") {
		showprocs(tokens);
	}
	else if (command == "#") {
		//nothing belongs in here, because this means the entire line is a comment
	}
	else if (command == "done") {
		done(tokens);
	}
	//keep creating else if's for rest of commands
}
void done(vector<string> tokens) {
	//if no value parameter, change exiting to 0; 
	if (tokens.size() == 1) {
		if(errorchecker(tokens, 1))
			return;
		exiting = 0;

	}
	else {
		if (errorchecker(tokens, 2))
			return;
		string value = tokens[1];
		for (int i = 0; i < value.length(); i++) {
			if (isdigit(value[i])) {
			}
			else {
				fprintf(stderr, "Values after done must only consist of numbers.");
				return;
			}
		}
		exiting = stoi(value);
	}
}
void showprocs(vector<string> tokens) {
	if(errorchecker(tokens, 1))
		return;
	for (auto& str : procs)
		cout << str << endl;
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
	if (isalpha(variable[0])) {
	}
	else{
		fprintf(stderr,"Variable names must start with a letter.");
		return;
	}
	//if the variable consists of anything other than letters/numbers
	for (int i = 1; i < variable.length(); i++) {
		if (isalnum(variable[i])) {
		}
		else{
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
void setdir(vector<string> tokens) {
	workingDir = tokens[1];
	// TODO: check if valid directory and right number of args
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
		if (exiting > -1) {
			return exiting;
		}
		if (ShowTokens=="1")
			for (auto& str : tokens)
				cout << str << endl;
	}
	return -1; // this should never be called, so i wanted to make it an error if it is called
}

