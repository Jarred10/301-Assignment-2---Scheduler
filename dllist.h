#include <stdint.h>

typedef struct Node {
	struct Node *next;
	struct Node *previous;
	char word[256];
	uint32_t time;
	uint32_t repeat;
} Node;

Node *createNode(char *word, uint32_t time, uint32_t repeat);
Node *insertFront(Node *list, Node *item);
Node *deleteNode(Node *list, char* item);
void printList(Node *list, uint32_t clock);
void clearList(Node *list);

