#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "userToLinkedList.h"
#include "generalConstant.h"

int freeList(List* head);
void print(List* head);
void executeCommand(List* head, int* commandArguments, int SizeOfCommandArguments);
void addEnd(List* head, int element);
void addStart(List* head, int element);
void addAfter(int* pointerToOrder, int SizeOfArray, List* head, int elementJ, int elementI);
List* addIAfterJ(List* head, int elementJ, int elementI);
List* elementFound(List* head, int elementJ);
void InsertElementI(List* head, int elementI);
void indexI(List* head, int elementI);
void delIndex(int* pointerToOrder, int SizeOfArray, List* head, int index);
void delIndexFromList(List* head, int index);

List* newList() {
    List* newNode;
    newNode = malloc(sizeof(List));
    if (newNode == NULL)
        return NULL;
    newNode->next = NULL;
    newNode->data = 0;
    return newNode;
}

void executeCommand(List* head, int* commandArguments, int SizeOfCommandArguments) {
    if (commandArguments[0] == ADD_END)
        addEnd(head, commandArguments[1]);
    else if (commandArguments[0] == ADD_START)
        addStart(head, commandArguments[1]);
    else if (commandArguments[0] == ADD_AFTER)
        addAfter(commandArguments, SizeOfCommandArguments, head, commandArguments[1], commandArguments[2]);
    else if (commandArguments[0] == INDEX)
        indexI(head, commandArguments[1]);
    else if (commandArguments[0] == DEL)
        delIndex(commandArguments, SizeOfCommandArguments, head, commandArguments[1]);
    else if (commandArguments[0] == PRINT)
        print(head);
}

void addEnd(List* head, int element) {
    head->data += 1;
    while (head->next != NULL) {
        head = head->next;
    }
    head->next = newList();
    head->next->data = element;
}

void addStart(List* head, int element) {
    List* newNode = newList();
    head->data += 1;
    newNode->next = head->next;
    newNode->data = element;
    head->next = newNode;
}

void addAfter(int* commandArgumentsArray, int sizeOfCommandArgumentsArray, List* head, int elementJ, int elementI) {
    List* copyOfHead = addIAfterJ(head, elementJ, elementI);
    if (copyOfHead == NULL) {
        printf("error\n");
        commandArgumentsArray[0] = EXIT;
    }
}

List* addIAfterJ(List* head, int elementJ, int elementI) {
    List* copyOfHead = elementFound(head, elementJ);
    if (copyOfHead->next != NULL) {
        head->data++;
        InsertElementI(copyOfHead, elementI);
        return head;
    }
    else
        return NULL;
}

List* elementFound(List* head, int elementJ) {
    int noElementFound = head->data;
    while (noElementFound) {
        if (head->next->data == elementJ)
            noElementFound = 0;
        else {
            head = head->next;
            noElementFound = (head->next != NULL);
        }
    }
    return head;
}

void InsertElementI(List* head, int elementI) {
    List* insertElement = newList();
    insertElement->data = elementI;
    insertElement->next = head->next->next;
    head->next->next = insertElement;
}

void indexI(List* head, int elementI) {
    int index = -1;
    int counter = 0;
    while (head->next != NULL) {
        head = head->next;
        if (head->data == elementI) {
            index = counter;
            break;
        }
        counter++;
    }
    printf("%d\n", index);
}

void delIndex(int* commandArgumentsArray, int sizeOfCommandArgumentsArray, List* head, int index) {
    if (head->data <= index) {
        printf("error\n");
        commandArgumentsArray[0] = EXIT;
    }
    else
        delIndexFromList(head, index);
}

void delIndexFromList(List* head, int index) {
    head->data--;
    List* copyOfhead;
    int i;
    for (i = 0; i < index; i++)
        head = head->next;
    copyOfhead = head->next;
    head->next = head->next->next;
    free(copyOfhead);
}

void print(List* head) {
    printf("[");
    int numberOfElements = head->data;
    head = head->next;
    int i;
    for (i = 0; i < numberOfElements; i++) {
        printf("%d", head->data);
        head = head->next;
        if (head != NULL)
            printf(", ");
    }
    printf("]\n");
}

int freeList(List* head)
{
    if (head == NULL)
        return 0;
    List* current = head;
    List* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    return 1;
}
