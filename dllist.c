#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dllist.h"

Node *createNode(char *word, uint32_t time, uint32_t repeat){
	Node *item = (Node*) malloc(sizeof(Node));
	strcpy(item->word, word);
	item->time = time;
	item->repeat = repeat;
	return item;
}

Node *processTasks(Node *head, uint32_t clock){
	while(head && head->time < clock){
		Node *removed = head;
		head = head->next;
		if(head) head->previous = NULL;
		if(removed->repeat != 0){
			Node *item = createNode(removed->word, (removed->time + 				removed->repeat), removed->repeat);
			head = insertFront(head, item);
		}
	}
	return head;
}

Node *insert(Node *tail, Node *item){
	//empty list
	if(!tail) return item;
	//goes on end of list
	if(item->time > tail->time){
		item->previous = tail; 
		tail->next = item; 
		return item;
	}
	Node *current = tail;
	for( ; current->previous; current = current->previous){
		if(item->time >= current->time){
			current->next->previous = item;
			item->next = current->next;
			item->previous = current;
			current->next = item;
			return tail;
		}
	}
	if(item->time >= current->time){
		current->next->previous = item;
		item->next = current->next;
		item->previous = current;
		current->next = item;
		return tail;
	}
	current->previous = item;
	item->next = current;
	return tail;
}

Node *deleteNode(Node *head, char* item){
	Node *curr;
	for(curr = head; curr != NULL; curr = curr->next){
		if(strcmp(curr->word, item) == 0){
			//removing from the front of list
			if(!curr->previous){ 
				head = curr->next;
				//check for only one item in the list
				if(head) head->previous = NULL;
			}
			//removing from the end of list			
			else if(!curr->next) {
				curr->previous->next = NULL;
				printf("previous was: %s\n", curr->previous->word);
			}
			//removing from the middle of list
			else {
				curr->previous->next = curr->next;
				curr->next->previous = curr->previous;
			}
		free(curr);
		return head;
		}
	}
	//if nothing was found, keep list the same
	return head;
}

void printList(Node *head, uint32_t clock){
	printf("Upcoming tasks:\n");
	for(;head; head = head->next){
		printf("%s %d \n", head->word, head->time - clock);
	}
}

void clearList(Node *list){
	Node *temp;
	while(list){
		temp = list;
		list = list->next;
		free(temp);
	}
}


