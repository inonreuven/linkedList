#ifndef LINKEDLIST_H
#define LINKEDLIST_H
typedef struct _List {
  struct _List* next;
  int data;
} List;
List* newList();
void executeCommand(List* head, int* commandArguments, int SizeOfCommandArguments);
int freeList(List* head);

#endif
