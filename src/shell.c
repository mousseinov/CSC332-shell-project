#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define LIST_SIZE 5
//char* history[LIST_SIZE];
char history[LIST_SIZE][20];
int curr_size = 0;
void add_command_to_history(char* command);
void print_history();


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

int main (int argc, char* argv[]) {
	char command[32];
	char *split;
    char *arg[20];

	printf("Welcome to our shell! Here are the following custom commands:\n");
	printf("Exit*\n");
	printf("History*\n");
	printf("Cd*\n");
	printf("Clear*\n");

	printf (">>> ");
	scanf(" %[^\n]s", command); //will read all characters until you reach \n (or EOF), replace white spaces with 0

  for(int i = 0; i<strlen(command); i++){
      command[i] = tolower(command[i]);
  }

  while (strcmp(command, "exit")!=0) { //while the command isnt quit
  	   //parse the command
	   parse(command, arg);

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
			int child = fork();
			if(child < 0){ //error
          	printf("ERROR: error forking child");
          	exit(1);
			}
			else if (child == 0) {
			// in the child process
			execvp (arg[0],arg);
			printf ("ERROR: exec failed\n"); //error will show only if execvp encounters an error
		    exit(1);												 //else it will never reach here for the exit
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
	if(strcmp(command,"exit")==0){
		printf("This shell wouldn't have been possible without these awesome people <3\n");
		printf("Team Members:\n");
		printf("Tahsin Jahin: Linux Performance Engineer\n");
		printf("Current MM.La Fleur Software Intern\n");
		printf("Krystal Leong: High Performance Computing Cloud Engineer\n");
		printf("Incoming Google Software Engineering Intern 2019\n");

		printf("Michael Ousseinov: Deadlock Systems Specialist (Consultant)\n");
		printf("Angelica Hernandez: Amazon Developer  \n");
		printf("Incoming Bank of America Intern\n");

		fgetc(stdin);
		char ch;
		printf("PRESS ENTER!");
		//here also if you press any other key will wait until you press ENTER
		scanf("%c",&ch);
		return 0; //return control to original shell on machine
	}
	return 0; //we don't ever make it here due to the return 0 in the  if statement above
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
		printf("--- No History\n");
	for(int i = 0; i < curr_size; i++)
		printf("--- %s\n", history[i]);

}



