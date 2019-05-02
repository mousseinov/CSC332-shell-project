# CSC332-shell-project
## Tasks
- **shell**: which will a list of custom commands
- **Exit**: print a list of the team all members, then it will wait for the user to hit the “return” key to
terminate the shell and return the control to the original shell program on your machine
- **History** : view the last 5 executed commands.
- **cd**: move to the parent directory of current directory, and print the current path ( i.e. equivalent
to cd .. + pwd).

- **clear**: clear the terminal screen and print the list of directory and files in the current directory
(i.e. equivalent to clear + ls).

## Making
For shell:
```make -B```<br/><br/>
For extras(like snake and shelly):
```make extras -B```<br/><br/>
(warning snake requires ncurses) <br/><br/>
To clean:
```make clean```<br/><br/>

## Running
To run shell:
 ```./shell```
 
## Notes
For this project, if the user enters `ls` as the command, it will execute `ls` as a custom command (using execl) since we have our own `ls.c` and ls executable as a part of this directory 

