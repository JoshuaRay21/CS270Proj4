//pushing this again
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <unistd.h>
#include <stdio.h>


#define MAX_ARGS 20


using namespace std;

void execcommand(vector<string> tokens);
vector<string> createtokens(string str);
void changeprompt(vector<string> tokens);
void setvar(vector<string> tokens);
void dorun(vector<string> tokens);
void dofly(vector<string> tokens);
void dotovar(vector<string> tokens);
bool errorchecker(vector<string> tokens, int wantedarguements);
void showprocs(vector<string> tokens);
void done(vector<string> tokens);
int setdir(vector<string> tokens);


string showtokens = "0";
map<string, string> variables; //1st string is the name, 2nd is value
string prompt = "msh > ";
vector<string> procs; //vec of processes running in background
int exiting = -1; //this int is changed if done is called, if this is non neg, msh exits
string path = "/bin:/usr/bin";

vector<string> createtokens(string str) {
	istringstream iss(str);
	vector<string> tokens;
	string s;

	while (iss >> quoted(s)) {
		if (s[0] == '#')
			break;
		tokens.push_back(s);
	}

	return tokens;
}
void execcommand(vector<string> tokens) {
	string command = tokens[0];
	if (command == "setvar") {
		setvar(tokens);
	}
	else if (command == "setprompt") {
		changeprompt(tokens);
	}
	else if (command == "setdir") {
		setdir(tokens);
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
	else if (command == "run") {
		dorun(tokens);
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
				fprintf(stderr, "Values after done must only consist of numbers.\n");
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
void dorun(vector<string> tokens) {
	if (tokens.size() < 2) {
		errorchecker(tokens, 2);
		return;
	}
	char* args[tokens.size()];
	int pid = fork();
	//char* const args[] = {"ls","/usr"};
	for (int i = 1; i < tokens.size(); i++) {
		//args[i-1] = (char*)tokens[i];
		string param = tokens[i];
		if (param[0] == '^') {
			param = variables.find(param.substr(1))->second;
		}
		args[i - 1] = const_cast<char*>(.c_str());
	}
	args[tokens.size() - 1] = NULL;
	printf("PID: %d\n", pid);
	printing args to see what args consists of
	for (int i = 0; i < tokens.size(); i++) {
		cout << args[i] << endl;
	}
	if (pid==0) {
		printf("executing %s...\n", args[0]);
		execvp(args[0], args);
	}
}
/*
int findActualLength(vector<string> tokens) {
	int i;
	for (i = 1; i < tokens.size(); i++) {
		if (tokens[i] == "#")
			return i;
	}
	return i;
}
*/
void dofly(vector<string> tokens) {
}
void dotovar(vector<string> tokens) {
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
		fprintf(stderr,"Variable names must start with a letter.\n");
		return;
	}
	//if the variable consists of anything other than letters/numbers
	for (int i = 1; i < variable.length(); i++) {
		if (isalpha(variable[i]) || isdigit(variable[i])) {
		}
		else{
			fprintf(stderr,"Variable names must only consist of letters and numbers.\n");
			return;
		}
	}
	string value = tokens[2];
	if (variable == "ShowTokens") {
		showtokens = value;
	}
	else if (variable == "PATH") {
		path = value;
	}
	else
		variables.insert(pair<string, string>(variable, value));

}
int setdir(vector<string> tokens) {
	if (errorchecker(tokens, 2)) {
		return -1;
	}
	int code = chdir(tokens[1].c_str());
	if (code != 0) {
		fprintf(stderr, "%s: No such directory\n", tokens[1].c_str());
		return -1;
	}
	return 0;
}
//returns true if there is an error relating to number of tokens
bool errorchecker(vector<string> tokens, int wantedarguements) {
	if (tokens.size()>wantedarguements) {
		if (tokens[wantedarguements] != "#") {
			fprintf(stderr,"Too many arguements for %s\n", tokens[0].c_str());
			return true;
		}
	}
	if (tokens.size() < wantedarguements) {
		fprintf(stderr,"Too few arguements for %s\n", tokens[0].c_str());
		return true;
	}
	for (int i = 1; i < wantedarguements; i++) {
		if (tokens[i]=="#") {
			fprintf(stderr, "Too few arguements for %s\n", tokens[0].c_str());
			return true;
		}
	}
	return false;
}
void changeprompt(vector<string> tokens) {
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
		vector<string> tokens = createtokens(command);
		execcommand(tokens);
		if (exiting > -1) {
			return exiting;
		}
		if (showtokens=="1")
			for (auto& str : tokens)
				cout << str << endl;
	}
	return -1; // this should never be called, so i wanted to make it an error if it is called
}

