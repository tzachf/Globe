//
// Created by zahi on 11/29/18.
//
#include "LinkedList.h"
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"


typedef struct LinkedList_t{
    Node Head;
    int numOfNodes;
    copyFunction copyFunc;
    freeFunction freeFunc;
    equalFunction cmpFunc;
    printFunction prtFunc;
} *LinkedList;


typedef struct Node_t{
    Element elem;
    Node nextNode;

} *Node;


LinkedList createLinkedList(copyFunction copyFunc, freeFunction freeFunc, equalFunction cmpFunc,printFunction prtFunc){

    LinkedList thisList = (LinkedList) malloc(sizeof(struct LinkedList_t));
    if(thisList==NULL) {
        return NULL;
    }
    thisList->prtFunc=prtFunc;
    thisList->freeFunc=freeFunc;
    thisList->cmpFunc=cmpFunc;
    thisList->copyFunc=copyFunc;
    thisList->Head = NULL;
    thisList->numOfNodes=0;
}

status destroyList(LinkedList list){

    if(list->Head==NULL){
        free(list);
        return success;
    }
    if(list->Head->nextNode==NULL){
        deleteNode(list,list->Head->elem);
        free(list);
        return success;
    }
    while (list->numOfNodes!=0){
        deleteNode(list,list->Head->elem);
    }
    free(list);
    return success;
}

status appendNode(LinkedList list, Element elem){
    Node thisNode1 = (Node)malloc(sizeof(struct Node_t));
    if(thisNode1==NULL){
        return failure;
    }
    thisNode1->nextNode=NULL;
    thisNode1->elem = list->copyFunc(elem);
    Node current = list->Head;
    if(list->Head == NULL){
        list->Head = thisNode1;
        list->numOfNodes++;
        return  success;
    }
    while(current->nextNode != NULL) {
        current = current->nextNode;
    }
    current->nextNode=thisNode1;
    list->numOfNodes++;
    return success;
}

int searchNode(LinkedList list, Element elem){
    Node current = list->Head;
    for (int i = 0; i < list->numOfNodes; ++i) {
        if(list->cmpFunc(current->elem,elem) == true){
            return i;
        }
        current=current->nextNode;
    }
    return -1;
}

status deleteNode(LinkedList list, Element elem){

    int index = searchNode(list, elem);
    if(index==-1){
        return failure;
    }
    Node temp = NULL;
    Node current=list->Head;
    if(index!=0&&index!=list->numOfNodes-1){

        for (int i = 0; i < index-1; ++i) {
            current=current->nextNode;
        }
        temp=current->nextNode;
        current->nextNode=temp->nextNode;
        list->freeFunc(temp->elem);
        free(temp);
        list->numOfNodes--;
        return  success;
    } else if(index==0) {
        current = list->Head;
        list->Head=list->Head->nextNode;
        list->freeFunc(current->elem);
        free(current);
        list->numOfNodes--;
        return success;
    }else{
        for (int i = 0; i < index; ++i) {
            current=current->nextNode;
        }
        list->freeFunc(current->elem);
        free(current);
        list->numOfNodes--;
        return success;
    }
}

void displayList(LinkedList list){
    Node current=list->Head;
    for(int i=0;i<list->numOfNodes;i++){
        list->prtFunc(current->elem);
        current=current->nextNode;
    }
}
Node  searchInList(LinkedList list, Element elem){

    int index= searchNode(list,elem);
    if(index==-1){
        return NULL;
    }
    Node current=list->Head;
    for(int i=0;i<index;i++){
        current=current->nextNode;
    }
    return current;
}

Element getElement(Node node){
    return node->elem;
}
Element getHead(LinkedList list){
    return list->Head;
}
int getNumOfElements(LinkedList list){
    return list->numOfNodes;
}