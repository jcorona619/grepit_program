#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// grepit program: grepit [keyword] [filename] [options]

int main(char argc, char* argv[]){

	FILE *fp = NULL;
	char *line = NULL;
	char *results[1000]; // Reads up to 1000 lines from a file
	size_t len = 0;		// 
	ssize_t nread;


	if(argc < 3){
		printf("Not enough arguments. Must include 'keyword' and 'filename'");
		exit(1);
	}
	if((fp = fopen(argv[2],"r")) == NULL){
		perror("Error: ");
		return(-1);
	}
	while(getline(&line,&len,fp) != -1){
		printf("%s",line);
	}

	free(line);
	fclose(fp);
	return(EXIT_SUCCESS);
}