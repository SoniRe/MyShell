## Features

This shell implementation supports the following functionalities:

- Basic Command Execution  
  Execute standard system commands available in the operating system.

- Built-in Commands  
  - echo – Display a line of text  
  - builtin – Display information about built-in shell commands  
  - exit – Exit the shell  
  - env – Display environment variables
 
- Command History  
  - Stores previously executed commands  
  - Navigate through history using Up (↑) and Down (↓) arrow keys  

- Input and Output Redirection  
  - Output redirection using `>`  
  - Input redirection using `<`  
  - Append output using `>>`
  - <img width="1533" height="525" alt="IO Redirections" src="https://github.com/user-attachments/assets/025ed487-7a20-4142-b052-1c521b7ff744" />

- Pipeline Support  
  - Chain multiple commands using the pipe operator `|`

- Background Process Execution  
  - Run commands in the background using `&`

- Signal Handling  
  - Ctrl + C – Interrupt the current process  
  - Ctrl + Z – Suspend the current process  

- Tab Completion  
  - Auto-completion for commands and file paths using the Tab key
