#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sstream>
#include <cstring>
using namespace std;

// --------------------------------------------------
// Builtin Commands List
// --------------------------------------------------
vector<string> builtins = {"exit", "echo", "type"};

// Check if string is a builtin
bool is_builtin(const string &cmd) {
    for (const string &b : builtins)
        if (cmd == b) return true;
    return false;
}

// --------------------------------------------------
// Echo builtin implementation
// --------------------------------------------------
void handle_echo(const string &command) {
    // Remove "echo " (5 chars)
    cout << command.substr(5) << "\n";
}

// --------------------------------------------------
// Search PATH for an executable
// --------------------------------------------------
string search_path(const string &cmd) {
    char *path_env = getenv("PATH");
    if (!path_env) return "";

    string path_str = path_env;
    stringstream ss(path_str);
    string dir;

    while (getline(ss, dir, ':')) {
        string full_path = dir + "/" + cmd;
        if (access(full_path.c_str(), X_OK) == 0) {
            return full_path;
        }
    }
    return ""; // not found
}

// --------------------------------------------------
// Type builtin implementation
// --------------------------------------------------
void handle_type(const string &command) {
    // Extract name after "type "
    string cmd = command.substr(5);

    if (cmd.empty()) {
        cout << "type: missing argument\n";
        return;
    }

    if (is_builtin(cmd)) {
        cout << cmd << " is a shell builtin\n";
        return;
    }

    // Check PATH
    string found = search_path(cmd);
    if (!found.empty()) {
        cout << cmd << " is " << found << "\n";
        return;
    }

    cout << cmd << ": not found\n";
}

// --------------------------------------------------
// Handle unknown commands
// --------------------------------------------------
void handle_unknown(const string &cmd) {
    cout << cmd << ": command not found\n";
}

// --------------------------------------------------
// Main Loop
// --------------------------------------------------
int main() {
    cout << unitbuf;
    cerr << unitbuf;

    while (true) {
        cout << "$ ";
        string command;
        getline(cin, command);

        if (command.rfind("exit", 0) == 0) {
            break;
        }
        else if (command.rfind("echo ", 0) == 0) {
            handle_echo(command);
        }
        else if (command.rfind("type ", 0) == 0) {
            handle_type(command);
        }
        else {
            handle_unknown(command);
        }
    }
}
