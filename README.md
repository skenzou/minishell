# minishell
minishell 42 school project

## DESCRIPTION

Minishell is the second project of the Unix branch at 42. It's a minimum viable version of a real shell.
The main goal is to have a good understanding of process creation and synchronisation using the C programmming language.

## HOW TO USE

```
$> make
$> ./minishell
```

## Main Project Instructions

### Mandatory

- Can only use C
- No memory leaks
- Implement a series of builtins: `echo`, `cd`, `setenv`, `unsetenv`, `env`, `exit`
- Manage the errors without using `errno`, by displaying a message adapted
to the error output
- Can only use these standard library functions:
    - malloc, free
    - access
    - open, close, read, write
    - opendir, readdir, closedir
    - getcwd, chdir
    - stat, lstat, fstat
    - fork, execve
    - wait, waitpid, wait3, wait4
    - signal, kill
    - exit
- Handle program interruption (Ctrl + D)

### Bonuses

- Signal management (specifically Ctrl + C)
- PATH's right management (error handling)
- Multiple commands (semi colons)
