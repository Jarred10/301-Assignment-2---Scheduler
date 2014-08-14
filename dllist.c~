#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dllist.h"

//creates a node from parameters, copying the string word, setting previous and next to null
Node *createNode(char *word, uint32_t time, uint32_t repeat){
	Node *item = (Node*) malloc(sizeof(Node));
	strncpy(item->word, word, sizeof(word));
	item->time = time;
	item->repeat = repeat;
	item->next = NULL;
	item->previous = NULL;
	return item;
}

//creates a list from no parameters, with an empty head and tail
List *createList(){
	List *list = (List*) malloc(sizeof(List));
	list->head = NULL;
	list->tail = NULL;
}

//processes what tasks have finished. called from a TIME command
List *processTasks(List *list, uint32_t clock){
	Node *temp;
	//loops through all tasks, while the task isn’t null and task time is before or equal to clock time
	for(temp = list->head; temp && temp->time <= clock;){
		Node *removed = temp;
		printf("%d %s\n", temp->time, temp->word);
		temp = temp->next;
		//if repeating task, create a new node from old one with new time
		if(removed->repeat != 0){
			Node *item = createNode(removed->word, (removed->time + 				removed->repeat), removed->repeat);
			list = insert(list, item);
		}
		//remove old task
		list = deleteNode(list, removed->word);
	}
	return list;
}

//inserts a node into list in sorted order, starting from tail
List *insert(List *list, Node *item){
	//if empty list
	if(!list->tail){
		//sets head and tail, returns list
		list->head = item; list->tail = item; return list;
	}
	
	//if item goes on end of list
	else if(item->time >= list->tail->time){
		list->tail->next = item;
		item->previous = list->tail; 
		list->tail = item;
		return list;
	}
	Node *current;
	//if node goes in middle of list. if the loop ends we are on last item
	for(current = list->tail; current->previous; current = current->previous){
		if(item->time >= current->time){
			current->next->previous = item;
			item->next = current->next;
			item->previous = current;
			current->next = item;
			return list;
		}
	}
	//if item is second to first
	if(item->time >= current->time){
		current->next->previous = item;
		item->next = current->next;
		item->previous = current;
		current->next = item;
	}
	//if item is first
	else {
		current->previous = item;
		item->next = current;
		list->head = item;
	}
	return list;
}

//deletes node from list, starting from head
List *deleteNode(List *list, char* item){
	Node *curr;
	//loops through all items in list
	for(curr = list->head; curr; curr = curr->next){
		//if the node matches the word we want to delete
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
		//de allocates space of node
		free(curr);
		return list;
		}
	}
	//if nothing was found, keep list the same
	return list;
}

//prints all items in list, in head to tail order
void printList(List *list, uint32_t clock){
	printf("Upcoming tasks:\n");
	Node *temp;
	for(temp = list->head;temp; temp = temp->next){
		printf("%s %d\n", temp->word, temp->time - clock);
	}
}

//deallocates all items in list
void clearList(List *list){
	Node *temp;
	//while head exists
	while(list->head){
		//save old head
		temp = list->head;
		//move head to next
		list->head = list->head->next;
		//delete old head
		free(temp);
	}
	//unsets list head and tail
	list->head = NULL; list->tail = NULL;
}



