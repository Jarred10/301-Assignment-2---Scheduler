#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dllist.h"

int main(int argc, char *argv[]){
	
	//initiates our list that stores schedule
	List *list = createList();
	FILE *fr;
	char buffer[1024];
	char* token;
	uint32_t clock, exectime, reptime;
	//opens the file passed in as argument
	fr = fopen(argv[1], "rt");
	
	//error checking for file
	if(!fr){
		perror("Error");
		return(-1);		
	}	
	
	//loops through all lines in the file
	while(fgets(buffer, 1025, fr) != NULL){
		token = strtok(buffer, " \n");
		//adding a non-repeating task
		if(strcmp(token, "ADD") == 0){
			exectime = atoi(strtok(NULL, " "));
			//only add the task if it is after the current time
			if(exectime > clock){
				token = strtok(NULL, "\n");
				//creates node for word
				Node *item = createNode(token, exectime, 0);
				//inserts the node into list
				list = insert(list, item);
			}
		}
		//adding a repeating task
		else if(strcmp(token, "ADDREP") == 0){
			exectime = atoi(strtok(NULL, " "));
			reptime = atoi(strtok(NULL, " "));
			//if the execute time is before clock, add repeat time until it isnt
			while(exectime < clock) exectime += reptime;
			token = strtok(NULL, "\n");
			Node *item = createNode(token, exectime, reptime);
			list = insert(list, item);
		}
		//time update
		else if(strcmp(token, "TIME") == 0){
			token = strtok(NULL, " ");
			clock = atoi(token);
			//processes all tasks with new time
			list = processTasks(list, clock);
		}
		//deleting a task
		else if(strcmp(token, "DEL") == 0){
			token = strtok(NULL, "\n");
			//deletes node with the name
			list = deleteNode(list, token);
		}
		//lists all tasks
		else if(strcmp(token, "LIST") == 0) printList(list, clock);
		//clears list
		else if(strcmp(token, "CLEAR") == 0) clearList(list);
	}

	return 0;
	
}
