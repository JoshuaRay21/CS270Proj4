#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>

void printTokens(std::istringstream iss) {
    std::vector<std::string> v;
    std::istringstream s;

    while (iss >> std::quoted(s)) {
        v.push_back(s);
    }

    for(auto& str: v)
        std::cout << str << std::endl;
}

int main() {
    std::string command;
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);
        std::cout << "Command: \"" << command << "\"!\n";
        printTokens(command);
    }
    return 0;
}

