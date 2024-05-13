
# Minishell

## Project description
This project entails the development of a custom shell, akin to Bash, with the capability to execute commands, manage input/output redirections, handle pipelines, and implement built-in functionalities. 

## Pre-requisites
  - Readline library installed - [Download readline](https://ftp.gnu.org/gnu/readline/)

## Features

#### Command Execution
  - Parses and executes commands entered by the user.
  - Supports both built-in shell commands and external executable files.
    
#### Prompt Display:
  - Displays a prompt to indicate readiness to accept user input.

#### History Functionality:
  - Implements a functional history feature to recall previously executed commands.

#### Signal Handling:
  - Manages signals such as ctrl-C, ctrl-D, and ctrl-\ as per Bash behavior.

#### Redirections:
  - Implements input and output redirection using < and > operators.
  - Supports here documents (<<) for input redirection and append mode (>>) for output     redirection.

#### Pipelines:
  - Facilitates the execution of commands in pipelines using the | operator.
  - Connects the output of one command to the input of the next command in the pipeline.

#### Environment Variables:
  - Expands environment variables ($) to their respective values.

#### Exit Status:
  - Provides the exit status of the most recently executed command using $?.

#### Built-in Commands:
  - Implements essential built-in commands including echo, cd, pwd, export, unset, env, and exit.

## Usage
To utilize the custom shell, follow these steps:

  1. Compile the source code using a suitable compiler.
  2. Run the executable to launch the custom shell.
  3. Enter commands at the prompt and observe the shell's behavior.

## Resources
  - [Bash manual](https://www.gnu.org/software/bash/manual/bash.html)

    
