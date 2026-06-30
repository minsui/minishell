*This project has been created as part of the 42 curriculum by <chan>.*

# Minishell - Parsing Part

## Description

This project is part of a simplified shell implementation inspired by Bash.

The goal of this part is to handle **input parsing only**, not command execution.

The parsing system is responsible for reading the user input and converting it into a structured format that can later be used by the executor.

### What this project does (parsing part only)

- Splits input into tokens (lexer)
- Builds command structures (parser)
- Checks syntax errors (syntax checker)
- Handles environment variable expansion ($?)
- Organizes redirection information (<, >, >>, <<)

This part does NOT execute commands, handle pipes execution, or run system calls like execve.

---

## Instructions

### Compilation

To compile the project, run:

```bash
make
````

### Execution

Run the shell program:

```bash
./minishell
```

Then you can type commands like:

```bash
cat < infile
echo hello > outfile
ls -l
```

⚠️ Note: In this project stage, only parsing is implemented. Execution behavior may be limited or handled separately.

---

## Project Structure (Parsing Part)

The parsing system is divided into the following modules:

* **Lexer**

  * Splits the input string into tokens

* **Parser**

  * Builds command structures from tokens
  * Organizes arguments and redirections

* **Syntax Checker**

  * Checks if the command input is valid
  * Detects errors like invalid pipe or redirection usage

* **Expander**

  * Replaces environment variables like `$?`

---

## Resources

### References

* Bash manual: [https://www.gnu.org/software/bash/manual/](https://www.gnu.org/software/bash/manual/)
* Unix shell basics: [https://www.tutorialspoint.com/unix_shell/](https://www.tutorialspoint.com/unix_shell/)
* Tokenization and parsing concepts: [https://en.wikipedia.org/wiki/Lexical_analysis](https://en.wikipedia.org/wiki/Lexical_analysis)
* 42 minishell subject (project PDF provided by 42)

### AI Usage

AI (ChatGPT) was used to:

* Help organize the project explanation in a clear structure
* Improve readability of technical descriptions
* Clarify the separation between lexer, parser, syntax, and expansion
---