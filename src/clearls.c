#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h> 

int main(int argc, char* argv[]) {
	printf("\033[H\033[J"); // clears screen
	struct dirent *director_entry;  // Pointer for directory entry 
    DIR *directory = opendir("."); // opendir() returns a pointer of DIR type.  
    if (directory == NULL) { // opendir returns NULL if couldn't open directory  
        printf("Unable to execute ls command" ); 
        return 0; 
    } 
	//readdir returns pointer to a dirent structure of the next directory entry
	//overwrites memory of previous readdir() call
    while ((director_entry = readdir(directory)) != NULL) {
            printf("%s\n", director_entry->d_name);
        }
    closedir(directory);      
    return 0;
}
