/**************************/
/*    Shell Assignment    */
/* Elie Rosen  Paul Kania */
/*     02/11/2012         */
/**************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXARG 50
#define BUFSIZE 2048

void getTok() {

	char cmd[BUFSIZE];
	char *tok_val[MAXARG];
	int tok_num = 0;
	
	printf("$: ");
	fgets(cmd, sizeof(cmd), stdin);
	cmd[strlen(cmd) - 1] = '\0';
	
	if(strlen(cmd) == 0) { /* if no input startover */
		getTok();
	}
	
	int i;
	
	int dflag = 0;
	int sflag = 0;
	int spflag = 0;
	int aflag = 0;
	
	
	
	char buffer[BUFSIZE];
	int place = 0;
	
	
	for(i = 0; i < strlen(cmd); i++) {
	
		switch (cmd[i]) {
		
			case '"': /* double quote */
				
				if ((sflag == 0) && (spflag == 0) ) {
					dflag++;
					
				}
				else {
					buffer[place] = cmd[i];
					place++;
				}
				break;
			
			case '\'': /* single quote */
		
				if ((dflag == 0) && (spflag == 0)) {
					sflag++;
					
				}
				else {
					buffer[place] = cmd[i];
					place++;
				}
				break;
			
			case ' ':  /* space */
		
				if ((dflag == 0) && (sflag == 0)) {
					spflag++;
				}
				break;
			
			case '|':  /* pipe */
				
				if ((dflag == 0) && (sflag == 0)) {
					tok_val[tok_num] = "|";
					tok_num++;
				}
				else {
					buffer[place] = cmd[i];
					place++;
				}
				break;
			
			default: 
				if (isalnum(cmd[i]) || (cmd[i] == '-')) {
					buffer[place] = cmd[i];
					place++;
				}
				if ((!isalnum(cmd[i+1]) && (cmd[i+1] != '-')) ) {
					aflag++;
				}
				break;
			
		}
				
		if ((dflag == 2) || (sflag == 2) || (spflag == 2) || aflag) {
			tok_val[tok_num] = buffer;
			tok_num++;
			
			place = 0; dflag = 0; sflag = 0; spflag = 0; aflag = 0;
			continue;
			
			
			
			int j;
			for (j = 0; j <= strlen(buffer); j++) {
				buffer[j] = '\0';
			}
		}
	}
	
	int k;
	for(k = 0; k < tok_num; k++)	
			printf("tok_val[%i] = \"%s\"\n", i, tok_val[i]);
	

}

int main(int argc, char **argv) {
	
	getTok();
	
	return 0;
	
}

