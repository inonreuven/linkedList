#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "userToLinkedList.h"
#include "generalConstant.h"


#define ASCII_CAPITAL_LETTER_A 0x41
#define ASCII_CAPITAL_LETTER_Z 0x5a
#define ASCII_SHIFT_TO_SMALL_LETTER 32
#define ADD_AFTER_ARGUMENTS_NUM 2

int readOrder(char* theOrder);
void readFromUser(int* pointerToOrder, int SizeOfArray);
void setUpCommand(char* order, int* commandArguments, int sizeOfCommandArguments);
void turnIntValue(char* command, int* commandArguments, int sizeOfCommandArguments, int howMuchToRead);
int convertStringToNumber(char* order, int i);
int convertCommandToIndexCommand(char* order);
int returnTypeOfCommand(char* orderInLowerCase);
int howManyArguments(int orderNumber);

void readFromUser(int* commandArguments, int sizeOfCommandArguments) {
  char order[MAX_ORDER_SIZE];
  fgets(order, MAX_ORDER_SIZE, stdin);
  setUpCommand(order, commandArguments, sizeOfCommandArguments);
}

int readOrder(char* theOrder) {
  return convertCommandToIndexCommand(theOrder);
}

void setUpCommand(char* command, int* commandArguments, int sizeOfCommandArguments) {
  int commandIndex = readOrder(command);
  commandArguments[0] = commandIndex;
  int howMuchToRead = howManyArguments(commandIndex);
  turnIntValue(command, commandArguments, sizeOfCommandArguments, howMuchToRead);
}

void turnIntValue(char* command, int* commandArguments, int sizeOfCommandArguments, int howMuchToRead) {
  int i = 0;
  while (howMuchToRead) {
    if (command[i] == ' ') {
      command[i] = '_';
      commandArguments[howMuchToRead] = convertStringToNumber(command, i + 1);
      howMuchToRead--;
    }
    i++;
  }
}
int convertStringToNumber(char* command, int i) {
  int j = 0;
  char numberInStringFormat[MAX_ORDER_SIZE];
  while (command[i] != ' ' && command[i] != '\0') {
    numberInStringFormat[j] = command[i];
    i++;
    j++;
  }
  numberInStringFormat[j] = '\0';
  return atoi(numberInStringFormat);
}

int convertCommandToIndexCommand(char* command) {
  int i = 0;
  char orderTranslated[MAX_ORDER_SIZE];
  while (command[i] != '\0' && command[i] != ' ')
    {
      char letter = command[i];
      if (ASCII_CAPITAL_LETTER_A  <= (int)letter && (int)letter <= ASCII_CAPITAL_LETTER_Z)
        letter += ASCII_SHIFT_TO_SMALL_LETTER;
      orderTranslated[i] = letter;
      i++;
    }
  orderTranslated[i] = '\0';
  return returnTypeOfCommand(orderTranslated);
}

int returnTypeOfCommand(char* orderInLowerCase) {
    char ordersArray[MAX_ORDER_SIZE][MAX_ORDER_SIZE] =
      { "add_end", "add_start", "add_after", "index", "del", "print\n", "exit\n" };
    int result = 0;
    int commandIndex;
    for (commandIndex = 0; commandIndex <= NUM_OF_COMMANDS; commandIndex++) {
      result = strcmp(ordersArray[commandIndex], orderInLowerCase);
      if (result == 0)
        break;
    }
    return commandIndex;
}

int howManyArguments(int orderNumber) {
  int numberOfCharToRead = 0;
  if(orderNumber == ADD_END)
     numberOfCharToRead++;
  else if(orderNumber == ADD_START)
    numberOfCharToRead++;
  else if(orderNumber == ADD_AFTER)
    numberOfCharToRead =  ADD_AFTER_ARGUMENTS_NUM;
  else if(orderNumber == INDEX)
    numberOfCharToRead++;
  else if(orderNumber == DEL)
    numberOfCharToRead++;
  return numberOfCharToRead;
}
