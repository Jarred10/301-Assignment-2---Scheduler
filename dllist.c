#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dllist.h"

Node *createNode(char *word, uint32_t time, uint32_t repeat){
	Node *item = (Node*) malloc(sizeof(Node));
	strcpy(item->word, word);
	item->time = time;
	item->repeat = repeat;
	item->next = NULL;
	item->previous = NULL;
	return item;
}

List *createList(){
	List *list = (List*) malloc(sizeof(List));
	list->head = NULL;
	list->tail = NULL;
}

List *processTasks(List *list, uint32_t clock){
	Node *temp;
	for(temp = list->head; temp && temp->time <= clock;){
		Node *removed = temp;
		temp = temp->next;
		if(removed->repeat != 0){
			Node *item = createNode(removed->word, (removed->time + 				removed->repeat), removed->repeat);
			list = insert(list, item);
		}
		list = deleteNode(list, removed->word);
	}
	return list;
}

List *insert(List *list, Node *item){
	//empty list
	if(!list->tail){
		list->head = item; list->tail = item; return list;
	}
	
	//goes on end of list
	else if(item->time >= list->tail->time){
		list->tail->next = item;
		item->previous = list->tail; 
		list->tail = item;
		return list;
	}
	Node *current;
	for(current = list->tail; current->previous; current = current->previous){
		if(item->time >= current->time){
			current->next->previous = item;
			item->next = current->next;
			item->previous = current;
			current->next = item;
			return list;
		}
	}
	//item is second to first
	if(item->time >= current->time){
		current->next->previous = item;
		item->next = current->next;
		item->previous = current;
		current->next = item;
		return list;
	}
	//item is first
	else {
		current->previous = item;
		item->next = current;
		list->head = item;
	return list;
	}
}

List *deleteNode(List *list, char* item){
	Node *curr;
	for(curr = list->head; curr; curr = curr->next){
		if(strcmp(curr->word, item) == 0){
			//removing from the front of list
			if(!curr->previous){ 
				list->head = curr->next;
				//check for only one item in the list
				if(list->head) list->head->previous = NULL;
			}
			//removing from the end of list			
			else if(!curr->next) {
				list->tail = curr->previous;
				if(list->tail) list->tail->next = NULL;
			}
			//removing from the middle of list
			else {
				curr->previous->next = curr->next;
				curr->next->previous = curr->previous;
			}
		free(curr);
		return list;
		}
	}
	//if nothing was found, keep list the same
	return list;
}

void printList(List *list, uint32_t clock){
/*
	if(list->head){ printf("Head of list: %s, ",list->head->word);} else printf("Head of list: null, ");
	if(list->tail){ printf("Tail of list: %s\n",list->tail->word);} else printf("Tail of list: null\n");
	*/
	printf("Upcoming tasks:\n");
	Node *temp;
	for(temp = list->head;temp; temp = temp->next){
		printf("%s %d\n", temp->word, temp->time - clock);
	}
}

void clearList(List *list){
	Node *temp;
	while(list->head){
		temp = list->head;
		list->head = list->head->next;
		free(temp);
	}
	list->head = NULL; list->tail = NULL;
}



