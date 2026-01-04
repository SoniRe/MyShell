## Compile & Run
1) ```gcc myShell.c -lreadline -o myShell```
2) ```./myShell```

## Features

This shell implementation supports the following functionalities:

- Basic Command Execution  
  Execute standard system commands available in the operating system.
  
- Built-in Commands  
  - echo – Display a line of text  
  - builtin – Display information about built-in shell commands  
  - exit – Exit the shell  
  - env – Display environment variables
  - <img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/293f6881-d8f3-4587-91d9-8198dd000093" />

- Command History  
  - Stores previously executed commands  
  - Navigate through history using Up (↑) and Down (↓) arrow keys  

- Input and Output Redirection  
  - Output redirection using `>`  
  - Input redirection using `<`  
  - Append output using `>>`
  - <img width="1435" height="294" alt="image" src="https://github.com/user-attachments/assets/721e5aa1-d13c-4d81-b09d-7585281fd7af" />
  - <img width="400" height="400" alt="IO Redirections" src="https://github.com/user-attachments/assets/025ed487-7a20-4142-b052-1c521b7ff744" />

- Pipeline Support  
  - Chain multiple commands using the pipe operator `|`
  - <img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/8140f81a-c608-4478-bbab-64889035c102" />
  - <img width="400" height="400" alt="Pipe" src="https://github.com/user-attachments/assets/cf3068fd-9448-406e-b201-689b09c9ee76" />
  - <img width="400" height="400" alt="Pipes" src="https://github.com/user-attachments/assets/e28d449c-41b6-4b84-b375-39d3612cf7fd" />


- Background Process Execution  
  - Run commands in the background using `&`
  - <img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/8fda777f-f1ac-41ad-b83c-53932e6f46c7" />
  
- Signal Handling  
  - Ctrl + C – Interrupt the current process  
  - Ctrl + Z – Suspend the current process  
  - <img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/874a8b60-2440-444b-a145-5c3ef138b6fd" />

- Tab Completion  
  - Auto-completion for file paths using the Tab key
