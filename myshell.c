/**************************/
/*    Shell Assignment    */
/* Elie Rosen  Paul Kania */
/*     02/11/2012         */
/**************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define MAXARG 50
#define BUFSIZE 2048

typedef int (command_t)(int argc, char *const *argv);
typedef struct builtin_s {
char const *name;
command_t *func;
} builtin_t;

/* Default case for if the command is not in the dictionary */
static int cmdDef(int argc, char *const *argv) {
	printf("....");
	return 0;
}

/* code that performs the CD command */
static int cmdCd(int argc, char *const *argv) {
	char const *n = NULL;
	int x;
	
	if (argc < 2) {
		n = getenv("HOME"); /* if there is 1 argument go to home dir */
		
		if (!n) { /* add a / to adjoin the following argument */
			n = "/";
		}
		
	} 
	
	else if (argc == 2) {
		n = argv[1]; /* set n to the target dir */
	
	} 
	
	else {
		fprintf(stderr, "cd: too many arguments\n"); /* error if there's an invalid amount of args */
		return -1;
	}
	
	x = chdir(n); /* set the directory */

	if (!x) {
		return 0;
	}

	fprintf(stderr, "%s: %s: %s\n", argv[0], strerror(errno), n);
	return -1;

}

/* Code that performs the exit command */
static int cmdExit(int argc, char *const *argv) {
	if (argc < 2) { /* if there's one arg just exit gracefully */
		exit(0);
	} else {
		int ret; /* exit code placeholder */

		if (argc > 3) {
			fprintf(stderr, "exit: too many arguments\n");
			return -1;
		}

		ret = 0;
		sscanf(argv[1], "%d", &ret); 

		/* if sscanf fails, exit with 0 */
		exit(ret);
	}
	
	return 0;
}

/* builtin struct */
static const builtin_t builtins[] = {
	{ "exit", cmdExit },
	{ "cd", cmdCd },
	{ NULL, cmdDef }
};

/* struct search function */
static command_t *builtin_get(builtin_t const *dict, const char  *name) {
	while (dict->name != NULL) { /* keep searching while there's commands */
		if (!strcmp(dict->name, name))
			break;
		++dict; /*move to the next command */
	}
	
	return dict->func; /* go to the function from builtin */
}

int main(int argc, char **argv) {
	
	
	int place = 0;
	
	if (isatty(0)) { /* get terminal input, otherwise content is already in argv*/
		char cmd[BUFSIZE];
		
		/* get input*/
		printf("$: ");
		fgets(cmd, sizeof(cmd), stdin); /* use fgets to recieve input */
		cmd[strlen(cmd) - 1] = '\0'; /* remove the ret char at the end of line */

		if(strlen(cmd) == 0) { /* if no input startover */
			main(argc, argv);
		}

		/* alocate space for counter and token array */
		int argc = 0;
		char argv[50][100];
		
		/* var to maintain arg place */
		int place = 0;
	
		int j;
		for(j = 0; j <= strlen(cmd); j++ ) { /* cycle through each letter */
			
			if (argc >= MAXARG) { /* RAGE QUIT */
				exit(0);
			}
			/* the following section is the culmination of 30+ hours of work */
			/* and debugging, we tried about 3 different more complicated    */
			/* methods and non of them worked until this, Thanks Lee Zhou    */
			/* for recommending to use "else if" - FML moment at 3:00am      */
			if (isspace(cmd[j])) {
				continue;
			}
			
			else if (cmd[j] == '|') {
			
				argv[argc][place] = '|';
				argc++;
				
			}
			
			else if (cmd[j] == '\'') { 
				j++;
				while (cmd[j] != '\'') {
					argv[argc][place] = cmd[j];
					place++;
					j++;
				} 
				argc++;
				place = 0;
				j++;
			}
			
			else if (cmd[j] == '"') { 
				j++;
				while (cmd[j] != '"') {
					argv[argc][place] = cmd[j];
					place++;
					j++;
				} 
				argc++;
				place = 0;
				
			}
			
			else  {
					argv[argc][place] = cmd[j];
					place++;
					
					if( (isspace(cmd[j+1])) || (cmd[j+1] == '\'') || (cmd[j+1] == '"') || (cmd[j+1] == '|') ) {
						argc++;
						place=0;
						
					}
			}
				
			
		}
		
		/* parse out any pipes */ 
		int command_num = 0;
		char* commands[50][100];
		
		int k;
		for(k = 0; k <= argc; k++) {
			
			printf("Token %d: \"%s\"\n", k, argv[k]); /* print existing tokens */
		
			if (strcmp(argv[k], "|")) {
				commands[command_num][place] =  argv[k]; /* place token into a command */
				place++;
			
			}
			else { 
				command_num++; /* increment the command counter */
				place = 0; 
			}
		}
		
		/* Search for existing commmands */
		int h;
		for (h = 0; h < command_num; h++) {
			if (command_num > 0) {
				builtin_get(builtins, commands[h][0])(command_num, commands[h]);
			}
		}
	}
	
	else { 
	
		/* parse out any pipes */ 
		int command_num = 0;
		char* commands[50][100];
		
		int k;
		for(k = 0; k <= argc; k++) {
			
			printf("Token %d: \"%s\"\n", k, argv[k]); /* print existing tokens */
		
			if (strcmp(argv[k], "|")) {
				commands[command_num][place] =  argv[k]; /* place token into a command */
				place++;
			
			}
			else { 
				command_num++; /* increment the command counter */
				place = 0; 
			}
		}
		
		/* Search for existing commmands */
		if (argc > 0) {
			argv[argc] = NULL;
			builtin_get(builtins, argv[0])(argc, argv);
		}
	}
	
	return 0;
	
}
