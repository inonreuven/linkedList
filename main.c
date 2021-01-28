#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedList.h"
#include "userToLinkedList.h"
#define EXIT 6
#define SIZE_OF_COMMAND_ARGUMENTS 3



void welcomeToProgram();
int main()
{
  int commandArguments[SIZE_OF_COMMAND_ARGUMENTS] = { 0 };

  bool stayInProgram = true;
  List* head = newList();
  while (stayInProgram) {
    readFromUser(commandArguments, SIZE_OF_COMMAND_ARGUMENTS);
    executeCommand(head, commandArguments, SIZE_OF_COMMAND_ARGUMENTS);
    stayInProgram = (commandArguments[0] != EXIT);
  }
  stayInProgram = freeList(head);
  exit(0);
}
