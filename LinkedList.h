//
// Created by zahi on 11/29/18.
//
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "Defs.h"


#ifndef MYGLOBE_LINKEDLIST_H
#define MYGLOBE_LINKEDLIST_H

typedef struct Node_t* Node;

typedef struct LinkedList_t* LinkedList;

///Function:

LinkedList createLinkedList(copyFunction copyFunc, freeFunction freeFunc, equalFunction cmpFunc,printFunction prtFunc);

status destroyList(LinkedList list);

status appendNode(LinkedList list, Element elem);

int searchNode(LinkedList list, Element elem);

status deleteNode(LinkedList list, Element elem);

void displayList(LinkedList list);

Node searchInList(LinkedList list, Element elem);

Element getElement(Node node);

Element getHead(LinkedList list);

int getNumOfElements(LinkedList list);
#endif //MYGLOBE_LINKEDLIST_H