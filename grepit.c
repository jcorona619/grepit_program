#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants for changing color of any results sent to stdout
#define RED_COLOR_TEXT 		"\x1b[1;31m"
#define GREEN_COLOR_TEXT	"\x1b[0;32m"
#define TEXT_COLOR_RESET 	"\x1b[0m"

// FLAG CONSTANTS
#define LINE_NUMBER			"-n"
#define WORD_COUNT			"-w"
#define COUNT   			"-c"

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

	// FLAGS: [options]
	int lineFlag = 0;



	// Error checks for command line arguments
	if(argc < 3){
		fprintf(stderr,"Not enough arguments. Must include 'keyword' and 'filename'.\n");
		fprintf(stderr,"Correct Usage: grepit [keyword] [filename] [options]\n");
		exit(-1);
	}
	// Check for valid file, open as read-only
	if((fp = fopen(argv[2],"r")) == NULL){
		perror("Error");
		return(-1);
	}

	keyword = argv[1];

	/*
	* This while loop is responsible for parsing the file line by line.
	* Each line is copied to a temporary varialbe to preserve the original line.
	* Each line is then parsed and split into space delimited tokens.
	* Each token is checked and compared against user chosen keyword.
	* If a match is found, the word position in the line is stored.
	* Each word is stored in a pointer array for printing use later.
	*/
	while(getline(&line,&length,fp) != -1){
		temp = (char *)malloc(length);
		strncpy(temp,line,length);
		token = strtok(temp," ");
        while(token != NULL){
        	if(strcmp(keyword,token)==0){
        		match = 1;
        		tokenMatch = wordCount;
        	}
        	// Simple bounds check if for some reason there are 
        	// more than 1000 words in a line. Security Measure
        	if(wordCount > 1000){
        		fprintf(stderr,"Too many words on a single line. Max: 1000\n");
        		exit(-1);
        	}
        	tokens[wordCount] = token;
        	wordCount++;
        	token = strtok(NULL," ");
        }

        /*  Match Condition:
        * If the keyword matches any word in a line, that line is printed to stdout.
        * Each word is printed from the pointer array storing the words.
        * Since the location of the matching word is known, it is printed in bold red.
        */
        if(match){
        	printf(GREEN_COLOR_TEXT"%d:"TEXT_COLOR_RESET,lineCount);
        	for(int i=0;i<wordCount;i++){
        	if(tokenMatch == i)
        		printf(RED_COLOR_TEXT "%s " TEXT_COLOR_RESET,tokens[i]);
        	else
        		printf("%s ",tokens[i]);
        	}
        	match = 0;
        	ungetc(stdout)
        }
        wordCount = 0;
        lineCount++;
	}

	free(temp);
	free(line);
	fclose(fp);
	return(EXIT_SUCCESS);
}