#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dllist.h"

FILE *fr;

int main(int argc, char *argv[]){

	Node *head = Node *tail = NULL;

	char buffer[1024];
	char* token;
	uint32_t clock, exectime, reptime;
	fr = fopen(argv[1], "rt");

	while(fgets(buffer, 1024, fr) != NULL){
		token = strtok(buffer, " \n");
		
		if(strcmp(token, "ADD") == 0){
			exectime = atoi(strtok(NULL, " "));
			token = strtok(NULL, "\n");
			Node *item = createNode(token, exectime, 0);
			tail = insert(head, item);
		}
		else if(strcmp(token, "ADDREP") == 0){
			exectime = atoi(strtok(NULL, " "));
			reptime = atoi(strtok(NULL, " "));
			token = strtok(NULL, "\n");
			Node *item = createNode(token, exectime, reptime);
			tail = insert(head, item);
		}
		else if(strcmp(token, "TIME") == 0){
			token = strtok(NULL, " ");
			clock = atoi(token);
			head = processTasks(head, clock);
		}
		else if(strcmp(token, "DEL") == 0){
			token = strtok(NULL, "\n");
			head = deleteNode(head, token);
		}
		else if(strcmp(token, "head") == 0){
			printhead(head, clock);
		}
		else if(strcmp(token, "CLEAR") == 0){
			clearhead(head);
			head = NULL;		
		}
	}

	return 0;
	
}
