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
  shell_commands.emplace_back("type");
  while(true) {
    std::cout << "$ ";
    string command;
    getline(cin, command);
    if (count(shell_commands.begin(), shell_commands.end(), command.substr(5, 4)) > 0) {
      cout << command.substr(5, 4) << " is a shell builtin\n";
      continue;
    } else {
      cout << command.substr(5, 4) << ": not found\n";
      continue;
    }
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
