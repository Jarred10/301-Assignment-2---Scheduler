#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dllist.h"

FILE *fr;

int main(int argc, char *argv[]){
	
	List *list = createList();

	char buffer[1024];
	char* token;
	uint32_t clock, exectime, reptime;
	fr = fopen(argv[1], "rt");

	while(fgets(buffer, 1024, fr) != NULL){
		token = strtok(buffer, " \n");
		
		if(strcmp(token, "ADD") == 0){
			exectime = atoi(strtok(NULL, " "));
			if(exectime > clock){
				token = strtok(NULL, "\n");
				Node *item = createNode(token, exectime, 0);
				list = insert(list, item);
			}
		}
		else if(strcmp(token, "ADDREP") == 0){
			exectime = atoi(strtok(NULL, " "));
			reptime = atoi(strtok(NULL, " "));
			while(exectime < clock) exectime += reptime;
			token = strtok(NULL, "\n");
			Node *item = createNode(token, exectime, reptime);
			list = insert(list, item);
		}
		else if(strcmp(token, "TIME") == 0){
			token = strtok(NULL, " ");
			clock = atoi(token);
			list = processTasks(list, clock);
		}
		else if(strcmp(token, "DEL") == 0){
			token = strtok(NULL, "\n");
			list = deleteNode(list, token);
		}
		else if(strcmp(token, "LIST") == 0){
			printList(list, clock);
		}
		else if(strcmp(token, "CLEAR") == 0){
			clearList(list);	
		}
	}

	return 0;
	
}
