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
	int tok_num = 0;
	
	printf("$: ");
	fgets(cmd, sizeof(cmd), stdin);
	cmd[strlen(cmd) - 1] = '\0';
	
	int i = 0;
	
	int dflag = 0;
	int sflag = 0;
	int spflag = 0;
	
	
	
	char buffer[BUFSIZE];
	int place = 0;
	
	while (i <= strlen(cmd)) {
	
		switch (cmd[i]) {
		
			case '"' : { /* double quote */
				if ((sflag == 0) && (spflag == 0)) {
					dflag++;
					i++;
				}
			}
			case '\'' : { /* single quote */
				if ((dflag == 0) && (spflag == 0)) {
					sflag++;
					i++;
				}
			}
			case ' ' : {  /* space */
				if ((dflag == 0) && (sflag == 0)) {
					spflag++;
					i++;
				}
			}
			case '|' : {  /* pipe */
				if ((dflag == 0) && (sflag == 0) && (spflag == 0)) {
					tok_val[tok_num] = "|";
					tok_num++;
					i++;
				}
			}
			default : {
				buffer[place] = cmd[i];
				place++;
				i++;
			}
		}
				
		if ((dflag == 2) || (sflag == 2) || (spflag == 2)) {
			tok_val[tok_num] = buffer;
			tok_num++;
			
			int j;
			for (j = 0; j<= strlen(buffer); j++) {
				buffer[j] = '\0';
			}
			
			place = 0; dflag = 0; sflag = 0; spflag = 0;
			
		}
	}
	printf("%s\n", tok_val[0]);
}

int main(int argc, char **argv) {
	
	getTok();
	
	return 0;
	
}

