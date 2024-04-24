# Minishell

The objective of this project is to create a custom shell program that mimics the behavior of a Bash shell. The shell is able to interpret and execute commands entered by the user, handle various special characters, implement built-in commands, and support advanced features like redirections and pipes.

## Key Features

- Display a prompt when waiting for a new command
- Implement a working history feature
- Search and launch the right executable based on the PATH variable or using a relative or absolute path
- Interpret quotes (single and double) to prevent shell interpretation of metacharacters
- Handle redirections for input (<), output (> and >>), and here documents (<<)
- Implement pipes (|)
- Handle environment variables expansion ($)
- Handle special variables such as $? for exit status
- Handle signals (ctrl-C, ctrl-D, ctrl-\) similar to bash
- Implement built-in commands:
  - echo with option -n
  - cd with relative or absolute path
  - pwd
  - export
  - unset
  - env
  - exit

## Knowledge Gained

- Shell scripting and command-line interface design
- Process management and execution in Unix-like operating systems
- Parsing and interpreting command-line arguments and options
- Handling signals and signal handlers
- Implementing redirections and pipes for I/O redirection
- Environment variable manipulation and expansion
- Built-in command implementation and shell scripting best practices

## Usage
Enter the minishell directory

```sh
cd minishell
``` 

To compile, use the provided Makefile:

```sh
make
```

Run the minishell:

```sh
./minishell
```

