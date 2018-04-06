//pushing this again
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


#define MAX_ARGS 20


using namespace std;

void execcommand(vector<string> tokens);
vector<string> createtokens(string str);
void changeprompt(vector<string> tokens);
void setvar(vector<string> tokens);
void dorun(vector<string> tokens, int which);
void dofly(vector<string> tokens);
void dotovar(vector<string> tokens);
bool errorchecker(vector<string> tokens, int wantedarguments);
void showprocs(vector<string> tokens);
void done(vector<string> tokens);
int setdir(vector<string> tokens);


string showtokens = "0";
map<string, string> variables; //1st string is the name, 2nd is value
string prompt = "msh > ";
vector<string> procs; //vec of processes running in background
int exiting = -1; //this int is changed if done is called, if this is non neg, msh exits
//string path = "/bin:/usr/bin";


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
	if (tokens.size() == 0) {
		return;
	}
	string command = tokens[0];
	if (command == "setvar") {
		setvar(tokens);
	} else if (command == "setprompt") {
		changeprompt(tokens);
	} else if (command == "setdir") {
		setdir(tokens);
	} else if (command == "showprocs") {
		showprocs(tokens);
	} else if (command == "#") {
		//nothing belongs in here, because this means the entire line is a comment
	} else if (command == "done") {
		done(tokens);
	} else if (command == "run") {
		dorun(tokens, 0);
	} else if (command == "fly") {
		dofly(tokens);
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
	printf("Showing procs:\n");
	for (auto str: procs) {
		printf("PROC: %s",str.c_str());
	}
	printf("Done showing procs!\n");
}
//which is 0 for run, 1 for fly, 2 for tovar
void dorun(vector<string> tokens, int which) {
	if (which == 0)
		printf("Doing a run!\n");
	if (tokens.size() < 2) {
		errorchecker(tokens, 2);
		return;
	}
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i].substr(0, 1) == "^") {
			cout << tokens[i].substr(1) << " is being changed to " << variables.find(tokens[i].substr(1))->second << endl;
			tokens[i] = variables.find(tokens[i].substr(1))->second;
		}
	}
	char* args[tokens.size()];
	string pathstring = variables.find("PATH")->second;
	char* path = pathstring.c_str();
	int sizedif = 1;
	if (which == 3) {
		sizedif = 2;
	}
	for (int i=sizedif; i<tokens.size(); i++) {
				args[i-sizedif] = const_cast<char*>(tokens[i].c_str());
	}
	args[tokens.size() - sizedif] = NULL;
	//printf("Full contents of args array:\n");
	//for (int i = 0; i < sizeof(args)/sizeof(args[0]); i++) {
	//	printf("ARG %d: %s\n", i, args[i]);
	//}
	int pid = fork();
	int firstFork = pid;
	if (pid == 0 && which == 1) {
		pid = fork();
	}
	printf("My PID is %d.\n", pid);
	
	if (pid==0) {
	//	cout << "Path: " << path << endl;
		printf("Executing %s...\n", args[0]);
		//printf("Pushing proc: %s\n", tokens[1].c_str());
		//procs.push_back(tokens[1]);
		//printf("There are now %d procs.\n", procs.size());
		if (which == 3) {
			variables[tokens[1]] = execvp(args[0], args);
		}
		else {
			execvp(args[0], args);
		}
		fprintf(stderr, "Execv did not work \n");
		exit(1);
	}
	if (pid != firstFork && which == 1) {
		waitpid(pid, NULL, 0); 
		string argsString = args[0];
		for (int i = 1; i < (tokens.size() - 1); i++) {
			argsString = argsString + " " + args[i];
		}
		//TAKING THIS LINE OUT
		//procs.erase(remove(procs.begin(), procs.end(), tokens[1]), procs.end());
		printf("Done executing %s!\n", args[0]);
		exit(1);
	}
	if(which == 0) {
		waitpid(pid, NULL, 0);
	}

	printf("Continuing...\n");
}
void dofly(vector<string> tokens) {
	printf("Doing a fly!\n");
	dorun(tokens, 1);
	//printf("Done flying!\n");
}
void dotovar(vector<string> tokens) {
	printf("Doing a tovar!\n");
	dorun(tokens, 3);
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
	else
		variables[variable] = value;

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
bool errorchecker(vector<string> tokens, int wantedarguments) {
	if (tokens.size()>wantedarguments) {
		if (tokens[wantedarguments] != "#") {
			fprintf(stderr,"Too many arguements for %s\n", tokens[0].c_str());
			return true;
		}
	}
	if (tokens.size() < wantedarguments) {
		fprintf(stderr,"Too few arguements for %s\n", tokens[0].c_str());
		return true;
	}
	for (int i = 1; i < wantedarguments; i++) {
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
	variables["PATH"] = "/bin:/usr/bin";
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

