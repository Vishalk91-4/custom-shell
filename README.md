# Custom Unix Shell

A lightweight **Unix-like shell** implemented from scratch in **C**, using low-level POSIX system calls.  
This project demonstrates core operating-system concepts such as **process creation, inter-process communication, file descriptor management, and signal handling**.

---

## Overview

This shell supports executing Unix commands, pipelines, I/O redirection, background processes, and basic job control.  
It is designed to be **educational, minimal, and close to how real shells work internally**.

---

## Features

### Command Execution
- Execute standard Unix commands
- Argument parsing and PATH-based executable lookup
- Implemented using `fork()` and `execvp()`

### Pipelines
- Supports multi-stage pipelines using `|`
- Implemented with `pipe()` and `dup2()`

Example:
ls -l | grep txt | wc -l


---

### I/O Redirection
- Input redirection: `<`
- Output redirection: `>`
- Append redirection: `>>`

Example:


cat input.txt | grep error > output.txt


---

### Background & Foreground Jobs
- Background execution using `&`
- Foreground execution with blocking waits
- Job tracking using process groups

Example:


sleep 30 &
jobs
fg 1


---

### Built-in Commands
- `cd` — change working directory
- `exit` — exit the shell
- `export` — set environment variables
- `jobs` — list background jobs
- `fg` / `bg` — job control

---

### Signal Handling
- Handles `SIGINT` (Ctrl+C)
- Handles `SIGTSTP` (Ctrl+Z)
- Handles `SIGCHLD` (child termination)

The shell itself does not terminate on Ctrl+C / Ctrl+Z.

---

### Environment Variable Support
- Environment variable expansion (`$VAR`)
- PATH-based command resolution

---

## Technologies Used

- **Language:** C (GNU C / C17)
- **System Calls & APIs:**
  - `fork`, `execvp`
  - `pipe`, `dup2`
  - `waitpid`
  - `kill`
  - `setpgid`
  - `signal`
- **Headers:** `unistd.h`, `signal.h`, `fcntl.h`, `sys/wait.h`


## Build Instructions

### Compile using Makefile


make


### Compile manually


gcc -std=gnu11 -O2 -Wall -Wextra shell.c -o mysh


---

## Running the Shell



./mysh


---

## Example Usage



ls
ls -l | grep cpp
cat input.txt | grep error > output.txt
sleep 10 &
jobs
fg 1
export PATH=/usr/local/bin:$PATH
cd /tmp
exit


---

If you find this project useful, feel free to ⭐ the repository!
