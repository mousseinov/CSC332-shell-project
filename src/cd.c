#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	char cwd[100];
	if (getcwd(cwd, 100) == NULL){
		perror("chdir() error");
	}
	else {
		int cd = chdir("..");
		if (cd != 0){
			perror("cd failed: cannot go up any further.\n");
		}
		else {
			argv[1] = getcwd(cwd, 100);
			printf("%s >>>\n", argv[1]);
		}
	}
	return 0;
}
