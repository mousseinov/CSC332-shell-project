#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define LIST_SIZE 5
char history[LIST_SIZE][20];
int curr_size = 0;
void parse(char command[], char *arg[]);
void add_command_to_history(char* command);
void print_history();
void print_team_banner();
void exit_shell();

char* shell_dir;

int main (int argc, char* argv[]) {
	char command[32];
	char *split;
  char *arg[20];
	char filepath[100];
	shell_dir = getcwd(filepath, 100);
	strcat(shell_dir, "/");

	printf("Welcome to our shell! Here are the following custom commands: OwO UwU\n");
	printf("Exit*\n");
	printf("History*\n");
	printf("Cd*\n");
	printf("Clear*\n");

	printf (">>> ");
	scanf(" %[^\n]s", command); //will read all characters until you reach \n (or EOF), replace white spaces with 0

  for(int i = 0; i<strlen(command); i++){
      command[i] = tolower(command[i]);
  }

  while (strcmp(command, "exit")!=0) { //while the command isnt exit
	  parse(command, arg); //parse the command
      //create new child
	  if(strcmp(arg[0],"history")==0) {
	  	print_history();
	  	for (int j = 0; j < 20; ++j) // need to clear the whole arg array
			arg[j] = NULL;
			printf (">>> ");
			scanf(" %[^\n]s", command);
			for(int i = 0; i<strlen(command); i++){
				command[i] = tolower(command[i]);
			}
	  }
	  else {
			add_command_to_history(arg[0]);
			if(strcmp(arg[0],"cd")==0) {
	      char cwd[100];
	    	if (getcwd(cwd, 100) == NULL){
	        perror("chdir() error");
	      }
	    	else {
	        int cd = chdir("..");
	        if (cd != 0){
						perror("cd failed.... (/# 0 A0)/\n");
	      	}
	        else {
						char* current_dir = getcwd(cwd, 100);
						printf("%s ", current_dir);
	      	}
	      }
				for (int j = 0; j < 20; ++j) // need to clear the whole arg array
					arg[j] = NULL;
				printf (">>> ");
				scanf(" %[^\n]s", command);
				for(int i = 0; i<strlen(command); i++){
					command[i] = tolower(command[i]);
				}
			}
			else {
				int child = fork();
				if(child < 0){ //error
      		printf("ERROR: error forking child 0n0");
  		  	exit(1);
				}
				else if (child == 0) {
					// in the child process
					char* path = shell_dir;
					strcat(path, arg[0]);
					printf("%s", path);
					execl(path, "", NULL);
					printf ("ERROR: ~>A<~  ~>A<~\n\texecl failed for custom commands. Attempting to use default commands\n"); //error will show only if execl encounters an error
			    execvp(arg[0], arg); //if execl doesnt work, then will fall into testing for execvp
			    printf("ERROR: >.> >.> >.> >.> >.>\n\texecvp failed too!\n");
			    exit(1); //if it enters either one of the two execs, it will never reach here for the exit
				}
				else{
					wait(NULL); //parent waits for child proc to complete
					for (int j = 0; j < 20; ++j) // need to clear the whole arg array
						arg[j] = NULL;
					printf (">>> ");
					scanf(" %[^\n]s", command);
					for(int i = 0; i<strlen(command); i++){
						command[i] = tolower(command[i]);
					}
				}
			}
	  }
  }
	if(strcmp(command,"exit")==0){
		exit_shell();
	}
	return 0; //returns control to the original shell
}

void add_command_to_history(char* command) {
	if(curr_size < LIST_SIZE) {
		strcpy(history[curr_size], command);
		curr_size += 1;
	} else {
		for(int i = 0; i < LIST_SIZE - 1; i++){
			strcpy(history[i],history[i+1]);
		}
		strcpy(history[LIST_SIZE-1], command);
	}
}

void print_history() {
	if(curr_size == 0)
		printf("--- No History ;A;\n");
	for(int i = 0; i < curr_size; i++)
		printf("--- %s\n", history[i]);
}

void print_team_banner() {
		printf("This shell wouldn't have been possible without these awesome people <3\n");
		printf("Team Members: UwU\n");
		printf("----------------\n");
		printf("Tahsin Jahin: Linux Performance Engineer \\(>u<)/\n");
		printf("--------------------------------------------------\n");
		printf("Krystal Leong: High Performance Computing Cloud Engineer /(=A=)/ ==3\n");
		printf("--------------------------------------------------\n");
		printf("Michael Ousseinov: Deadlock Systems Specialist (Consultant) (`@ w @`)\n");
		printf("--------------------------------------------------\n");
		printf("Angelica Hernandez: Amazon Developer v(0u<)v \n");
		printf("--------------------------------------------------\n");
}

void exit_shell(){
	print_team_banner();
	printf("PRESS ENTER!");
	fgetc(stdin); //waits for user to input something on keyboard; waiting for keystroke
	char ch;
	//here also if you press any other key will wait until you press ENTER
	scanf("%c",&ch);
}

void parse(char command[], char *arg[]){
	char *split;
	split = strtok(command," "); // split at space
	int i = 0;
	while(split != NULL) {
		arg[i]= split;  // array to store arguments
		split = strtok(NULL," "); // continue to tokenize
		i++; // keeps track of number of arguments
	}
}
