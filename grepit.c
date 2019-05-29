#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants for changing color of any results sent to stdout
#define RED_COLOR_TEXT 		"\x1b[1;31m"
#define TEXT_COLOR_RESET 	"\x1b[0m"

// grepit program: grepit [keyword] [filename] [options]
int main(char argc, char* argv[]){

	FILE *fp = NULL;
	char *line = NULL;		// Pointer for each line retrived from the file
	char *temp = NULL;		// Temporary variable so each line is not altered using strtok()
	char *token = NULL;		// Pointer to each word
	char *keyword = NULL;	// Pointer to the keyword chosen by the user
	char *tokens[1000]; 	// Pointers to each word in a line, up to 1000 words per line
	size_t length = 0;		// Length of each line, neccessary for memory allocation
	ssize_t nread;			// Stores the length of each line (in characters, excluding additonal data)
	int match = 0;			// Flag for for checking if a matching word was found
	int tokenMatch = 0;		// Flags where in the line the matching word is located
	int wordCount = 0;		// Word count for each line
	int lineCount = 1;


	// Error checks for command line arguments
	if(argc < 3){
		printf("Not enough arguments. Must include 'keyword' and 'filename'.\n");
		printf("Correct Usage: grepit [keyword] [filename] [options]\n");
		exit(1);
	}
	// Check for valid file, open as read-only
	if((fp = fopen(argv[2],"r")) == NULL){
		perror("Error: ");
		return(-1);
	}

	keyword = argv[1];

	while(getline(&line,&length,fp) != -1){
		temp = (char *)malloc(length);
		strcpy(temp,line);
		token = strtok(temp," ");
        while(token != NULL){
        	if(strcmp(keyword,token)==0){
        		match = 1;
        		tokenMatch = wordCount;
        	}
        	tokens[wordCount] = token;
        	wordCount++;
        	token = strtok(NULL," ");
        }
        
        if(match){
        	for(int i=0;i<wordCount;i++){
        	if(tokenMatch == i)
        		printf(RED_COLOR_TEXT "%s " TEXT_COLOR_RESET,tokens[i]);
        	else
        		printf("%s ",tokens[i]);
        	}
        	match = 0;
        }
        wordCount = 0;
        lineCount++;
	}

	free(temp);
	free(line);
	fclose(fp);
	return(EXIT_SUCCESS);
}