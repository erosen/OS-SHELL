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

static int cmdDef(int argc, char *const *argv) {

	return 0;
}

static int cmdCd(int argc, char *const *argv) {
	char const *n = NULL;
	int x;
	
	if (argc < 2) {
		n = getenv("HOME");
		
		if (!n) {
			n = "/";
		}
		
	} 
	
	else if (argc == 2) {
		n = argv[1];
	
	} 
	
	else {
		fprintf(stderr, "Too many arguments\n");
		return -1;
	}
	
	x = chdir(n);

	if (!x) {
		return 0;
	}

	fprintf(stderr, "%s: %s: %s\n", argv[0], strerror(errno), n);
	return -1;

}

static int cmdExit(int argc, char *const *argv) {
	if (argc < 2) {
		exit(0);
	} else {
		int ret;

		if (argc > 3) {
			fprintf(stderr, "Too many arguments\n");
			return -1;
		}

		ret = 0;
		sscanf(argv[1], "%d", &ret);

		/* if sscanf fails, we exit with 0 */
		exit(ret);
	}
	return 0;
}

static const builtin_t builtins[] = {
	{ "exit", cmdExit },
	{ "cd", cmdCd },
	{ NULL, cmdDef }
};

static command_t *builtin_get(builtin_t const *dict, char const *name) {
	while (dict->name != NULL) {
		if (!strcmp(dict->name, name))
			break;
		++dict;
	}
	
	return dict->func;
}

int main(int argc, char **argv) {
	
	if (isatty(0)) { /* get terminal input, otherwise content is already in argv*/
		char cmd[BUFSIZE];
		
		printf("$: ");
		fgets(cmd, sizeof(cmd), stdin);
		cmd[strlen(cmd) - 1] = '\0';

		if(strlen(cmd) == 0) { /* if no input startover */
			main(argc, argv);
		}

		/* alocate space for counter and token array */
		int argc = 0;
		char **argv = (char**)malloc((MAXARG+1)*sizeof(char*));
		int i;
		for(i = 0; i < MAXARG+1; i++) {
			argv[i] = (char*)malloc((MAXARG+1)*sizeof(char));
		}
	
		int place = 0;
	
		int j;
		for(j = 0; j <= strlen(cmd); j++ ) {
			
			if (argc >= MAXARG) { /* restart and deallocate space*/
				exit(0);
			}
			
			if (isspace(cmd[j])) {
				continue;
			}
			
			else if (cmd[j] == '|') {
			
				argv[argc] = "|";
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
		int k;
		for(k = 0; k <= argc; k++) {	
		printf("Token %d: \"%s\"\n", k, argv[k]);
		
		//if (argv[argc] != "|") {
		//	commands[command_num][place] =  argv[argc];
			
		//}
		//else { 
		//	command_num++;
		//	place = 0;
		//}
		
		
			
		}
			
		
	}
	
	/* parse out any pipes */ 
	
	
	/* Search for existing commmands */
	 if (argc > 0) {
		argv[argc] = NULL;
		builtin_get(builtins, argv[0])(argc, argv);
	}
	
	
	return 0;
	
}
