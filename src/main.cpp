#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  vector<string> shell_commands;
  shell_commands.emplace_back("exit");
  shell_commands.emplace_back("echo");
  while(true) {
    std::cout << "$ ";
    string command;
    getline(cin, command);
    if (command.substr(0, 4) == shell_commands[1]) {
      cout << command.substr(5) << "\n";
      continue;
    }
    if (command == shell_commands[0]) {
      break;
    }
    cout << command << ": command not found\n";
  }
}
