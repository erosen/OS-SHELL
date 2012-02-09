/**********************/
/* Shell Assignment   */
/* Elie Rosen         */
/* 02/05/2012         */
/**********************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXARG 50
#define BUFSIZE 2048

void getTok() {

	char cmd[BUFSIZE];
	char *tok_val[MAXARG];
	int tok_count = 0;
	
	printf("$: ");
	fgets(cmd, sizeof(cmd), stdin);
	cmd[strlen(cmd) - 1] = '\0';
	
	int i = 0;
	
	while (cmd[i]) {
	
		if (tok_count >= MAXARG) {
				fprintf(stderr, "err: too many arguments\n");
				getTok(); /* START OVER */
		} 
		int place = 0;
		
		if (cmd[i] == '"') {
			printf("Beginning a double quote\n");
			i++;
			
			char buffer[BUFSIZE];
						
			while (cmd[i]) {
				if (cmd[i] == '"') {
					printf("Close double quote\n");
					tok_val[tok_count] = buffer;
					tok_count++;
					i++;
					break;
				}
				
				buffer[place] = cmd[i];
				place++;
				i++;
			}
		}
		
		
		if (cmd[i] == '\'') {
			printf("Beginning a single quote\n");
			i++;
			
			char buffer[BUFSIZE];
						
			while (cmd[i]) {
				if (cmd[i] == '\'') {
					printf("Close single quote\n");
					tok_val[tok_count] = buffer;
					tok_count++;
					i++;
					break;
				}
				
				buffer[place] = cmd[i];
				place++;
				i++;
			}
		}
		
		
		if (cmd[i] == ' ') {
			printf("Beginning a space\n");
			i++;
			
			char buffer[BUFSIZE];
						
			while (cmd[i]) {
				if (cmd[i] == ' ') {
					printf("Close space\n");
					tok_val[tok_count] = buffer;
					tok_count++;
					i++;
					break;
				}
				
				buffer[place] = cmd[i];
				place++;
				i++;
			}
		}
		
		if (cmd[i] == '|') {
			printf("A pipe was found\n");
			tok_val[tok_count] = "|";
			tok_count++;
			i++;
		}
	
		else {
			printf("Token without space\n");
			char buffer[BUFSIZE];
			while (cmd[i]) {
				buffer[place] = cmd[i];
				printf("%l", sizeof(cmd));
				place++;
				i++;
				
				if ((cmd[i] == ' ') || (cmd[i] == '"') || (cmd[i] == '\'') || (cmd[i] == '|')) {
					break;
				}
				
			}
			
			tok_val[tok_count] = buffer;
			tok_count++;
			i++; 
		}
	
	}
	printf("%s\n", tok_val[0]);
	//return tok_val;
	
}

int main(int argc, char **argv) {
	
	getTok();
	
	return 0;
	
}
