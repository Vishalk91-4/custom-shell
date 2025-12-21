#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
using namespace std;

// ------------------------ BUILTINS ------------------------
vector<string> builtins = {"exit", "echo", "type", "pwd"};

bool is_builtin(const string &cmd) {
  for (const string &b : builtins)
    if (cmd == b) return true;
  return false;
}

// ------------------------ TOKENIZER ------------------------
vector<string> tokenize(const string &line) {
  stringstream ss(line);
  vector<string> tokens;
  string tok;
  while (ss >> tok)
    tokens.push_back(tok);
  return tokens;
}

// ------------------------ PATH SEARCH ------------------------
string search_path(const string &cmd) {
  char *path_env = getenv("PATH");
  if (!path_env) return "";
  string path_str = path_env;
  stringstream ss(path_str);
  string dir;
  while (getline(ss, dir, ':')) {
    string full_path = dir + "/" + cmd;
    if (access(full_path.c_str(), X_OK) == 0) return full_path;
  }
  return "";
}

// ------------------------ ECHO BUILTIN ------------------------
void handle_echo(const vector<string> &args) {
  for (size_t i = 1; i < args.size(); i++) {
    cout << args[i];
    if (i + 1 < args.size()) cout << " ";
  }
  cout << "\n";
}

// ------------------------ TYPE BUILTIN ------------------------
void handle_type(const vector<string> &args) {
  if (args.size() < 2) {
    cout << "type: missing argument\n";
    return;
  }
  string cmd = args[1];
  if (is_builtin(cmd)) {
    cout << cmd << " is a shell builtin\n";
    return;
  }
  string found = search_path(cmd);
  if (!found.empty()) {
    cout << cmd << " is " << found << "\n";
    return;
  }
  cout << cmd << ": not found\n";
}

// ------------------------ PWD BUILTIN ------------------------
void handle_pwd(const vector<string> &args) {
  string cmd = "";
  string found = search_path(cmd);
  cout << found << "\n";
}

// ------------------------ EXEC ARGUMENT BUILDER ------------------------
char** build_exec_argv(const vector<string> &args) {
  char **argv = new char*[args.size() + 1];
  for (size_t i = 0; i < args.size(); i++) argv[i] = strdup(args[i].c_str());
  argv[args.size()] = NULL;
  return argv;
}

// ------------------------ RUN EXTERNAL PROGRAM ------------------------
void run_external(vector<string> &args) {
  if (args.empty()) return;
  string cmd = args[0];
  string fullpath = search_path(cmd);
  if (fullpath.empty()) {
    cout << cmd << ": command not found\n";
    return;
  }
  char **exec_args = build_exec_argv(args);
  pid_t pid = fork();
  if (pid == 0) {
    execvp(fullpath.c_str(), exec_args);
    perror("execvp");
    exit(1);
  }
  int status;
  waitpid(pid, &status, 0);
  for (size_t i = 0; exec_args[i] != NULL; i++) free(exec_args[i]);
  delete[] exec_args;
}


// ------------------------ MAIN LOOP ------------------------
int main() {
  cout << unitbuf;
  cerr << unitbuf;
  while (true) {
    cout << "$ ";
    string line;
    getline(cin, line);
    vector<string> args = tokenize(line);
    if (args.empty()) continue;
    string cmd = args[0];
    if (cmd == "exit") break;
    else if (cmd == "echo") handle_echo(args);
    else if (cmd == "type") handle_type(args);
    else if (cmd == "pwd") handle_pwd(args);
    else run_external(args);
  }
  return 0;
}