#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define NUM_OF_TOKENS 10
#define INPUT_SIZE 256
/*

1. Shell
2. cd
3. exit
4. history
6. clear


*/


void init();
int cd(char* directorypath);
void history();
int clear();


int main(int argc, char* argv[]) {

	init();
	return 1;
}


void init() {
	while(1) {
		printf(">>> ");
		
		char input[INPUT_SIZE];
		for(int i = 0; i < INPUT_SIZE; i++) {
			input[i] = '\0';
		}
		gets(input);
		if(input[0] != '\0') {
			char s[INPUT_SIZE];
			char* tokens[NUM_OF_TOKENS];
			for(int i = 0; i < 10; i++){
				tokens[i] = NULL;
			}

			strcpy(s, input);
			char* token = strtok(s, " ");
			int i = 0;
			while (token) {
		    	tokens[i] = token;
		    	i += 1;
		    	token = strtok(NULL, " ");
			}

			// If User enters quit leave the program!
			if (strcmp(tokens[0],"exit") == 0) {
				/*
				Print Names
				Then wait for user to press return

				*/
				printf("This shell wouldn't");
				printf("have been possible without these awesome people <3\n");
				printf("Team Members:\n");
				printf("Tahsin Jahin: Front End\n");
				printf("Krystal Leong: Back end\n");
				printf("Michael Ousseinov: Data Engineer\n");
				printf("Angelica Hernandez: Scheme & LISP Developer\n");
				printf("PRESS ENTER!");
				char ch=fgetc(stdin);
				if(ch==0x0A)
					break;

			}
			
			char* command = tokens[0];
			char* arguments[NUM_OF_TOKENS-1];
			for(int i = 0; i < NUM_OF_TOKENS-1; i++) {
				arguments[i] = tokens[i+1];
			}

			int run_command_process = fork();
			if(run_command_process < 0) {
				perror("Fork Error");
				return 1;
			} else if (run_command_process == 0) {
				execvp(command, arguments);
				perror("execvp failed");
				return 1;
			} else {
				wait(NULL);
			}
		}


	}
}





