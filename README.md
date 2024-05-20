# Minishell

Minishell is a simple imitation of the bash command line interface. Developed as part of the 42 Istanbul coding school, this project aims to recreate the basic functionality of a Unix shell and offer a customized terminal experience supporting various commands.

## Getting Started

To clone this project onto your local machine, follow these steps:

```bash
git clone https://github.com/asdsec/minishell.git
cd minishell
```

## Requirements

The necessary libraries and tools for Minishell to operate:

- GCC compiler
- Make
- readline library
- Installation

To compile and run the project, use the following commands:

```bash
make
./minishell
```

## Features

Minishell supports the following features:

- Command history and display prompts
- Search and launch the appropriate executable based on the PATH variable or through relative/absolute paths
- Manage environment variables and the exit status of the most recently executed foreground command
- Shortcut keys (ctrl-C, ctrl-D, ctrl-\)
- Basic redirections, heredoc and pipes
- Proper handling of text and environment variables with single and double quotes
- Built-in commands: echo, cd, pwd, export, unset, env, exit

## Usage

When Minishell is run, it displays a command prompt waiting for a new command from the user. Users can enter commands and execute them by pressing ENTER. Use the exit command to terminate the program.

## Contributing

If you would like to contribute to the project:

- Fork the project and make improvements in your own branch.
- Commit your changes and create a pull request.
- Describe your pull request in detail.

## License

This project is licensed under the [MIT License](./LICENSE).

## Authors
- Samet Demir
- Mehmet Ali Keklik
- Ali Berk Pancar
- Hülya Kızrak Yiğit
- Ahmet Cemil Bostanoğlu
- Ahmet Faruk Basaran
