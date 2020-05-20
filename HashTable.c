//
// Created by zahi on 11/30/18.
//

#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"
typedef struct hashTable_s{
    LinkedList* listArray;
    transformIntoNumberFunction transformKeyIntoNumber;
    copyFunction copyKey;
    freeFunction freeKey;
    printFunction printKey;
    copyFunction copyValue;
    freeFunction freeValue;
    printFunction printValue;
    equalFunction cmpKey;
    int numOfElements;
    int hashNumber;

}*hashTable;

hashTable createHashTable(copyFunction copyKey, freeFunction freeKey, printFunction printKey, copyFunction copyValue, freeFunction freeValue, printFunction printValue, equalFunction equalKey, transformIntoNumberFunction transformKeyIntoNumber, int hashNumber){

    hashTable thisHashTable=(hashTable)malloc(sizeof(struct hashTable_s));
    thisHashTable->listArray=(LinkedList*)malloc(hashNumber*sizeof(LinkedList));
    for(int i=0;i<hashNumber;i++){
        thisHashTable->listArray[i]=NULL;
    }
    thisHashTable->transformKeyIntoNumber=transformKeyIntoNumber;
    thisHashTable->copyKey=copyKey;
    thisHashTable->freeValue=freeValue;
    thisHashTable->printKey=printKey;
    thisHashTable->copyValue=copyValue;
    thisHashTable->freeKey=freeKey;
    thisHashTable->printValue=printValue;
    thisHashTable->cmpKey=equalKey;
    thisHashTable->numOfElements=0;
    thisHashTable->hashNumber=hashNumber;
    return thisHashTable;
}

status destroyHashTable(hashTable dHashTable) {
    if(dHashTable != NULL) {
        for (int i = 0; i < dHashTable->hashNumber; ++i) {
            if(dHashTable->listArray[i]!=NULL) {
                destroyList(dHashTable->listArray[i]);
            }
        }
        free(dHashTable->listArray);
        free(dHashTable);
        return success;
    }
    return failure;
}

status addToHashTable(hashTable hash, Element key,Element value){

    int index = (hash->transformKeyIntoNumber(key)) % (hash->hashNumber);
    if (hash->listArray[index] == NULL) {
        hash->listArray[index] = createLinkedList(copyValKey, freeValKey, valKeyCmp,displayPair);
        if(hash->listArray[index]==NULL){
            return failure;
        }
    }

    Val_Key valKey = createKeyValuePair(key, value, hash->freeValue, hash->copyValue, hash->printValue,
                                        hash->freeKey, hash->cmpKey, hash->copyKey, hash->printKey);
    if(valKey==NULL){
        return failure;
    }
    if(appendNode(hash->listArray[index], valKey)==failure){
        return failure;
    }
    destroyKeyValuePair(valKey);
    hash->numOfElements++;
    return success;

}

Element lookupInHashTable(hashTable hash, Element key){

    int index = (hash->transformKeyIntoNumber(key)) % (hash->hashNumber);
    if(hash->listArray[index]==NULL){
        return NULL;
    }
    Element x=hash->copyValue((Element)getValue(getElement(getHead(hash->listArray[index]))));

    Element key1=hash->copyKey(key);
    Val_Key valkey= createKeyValuePair(key1,x, hash->freeValue, hash->copyValue, hash->printValue,
                                       hash->freeKey, hash->cmpKey, hash->copyKey, hash->printKey);
    if(valkey==NULL){
        return NULL;
    }
    Node value=searchInList(hash->listArray[index],valkey);
    if(value==NULL){
        hash->freeValue(x);
        hash->freeKey(key1);
        free(x);
        destroyKeyValuePair(valkey);
        return NULL;
    }
    hash->freeValue(x);
    hash->freeKey(key1);
    free(x);
    destroyKeyValuePair(valkey);
    return getValue(getElement(value));
}

status removeFromHashTable(hashTable hash, Element key){

    int index = (hash->transformKeyIntoNumber(key)) % (hash->hashNumber);
    if(hash->listArray[index]==NULL){
        return failure;
    }
    Element key1=hash->copyKey(key);
    Element x=hash->copyValue((Element)getValue(getElement(getHead(hash->listArray[index]))));
    Val_Key valkey= createKeyValuePair(key1,x, hash->freeValue, hash->copyValue, hash->printValue,
                                       hash->freeKey, hash->cmpKey, hash->copyKey, hash->printKey);
    if(valkey==NULL){
        return failure;
    }
    Node value=searchInList(hash->listArray[index],valkey);
    if(value==NULL){
        destroyKeyValuePair(valkey);
        hash->freeValue(x);
        hash->freeKey(key1);
        free(x);
        return  failure;
    }
    if((deleteNode(hash->listArray[index],getElement(value))==failure)){
        destroyKeyValuePair(valkey);
        hash->freeValue(x);
        hash->freeKey(key1);
        free(x);
        return failure;
    }
    if(getNumOfElements(hash->listArray[index])==0){
        destroyKeyValuePair(valkey);
        hash->freeValue(x);
        hash->freeKey(key1);
        free(x);
        //free(hash->listArray[index]);
        return success;
    }
    destroyKeyValuePair(valkey);
    hash->freeValue(x);
    hash->freeKey(key1);
    free(x);
    return success;
}
status displayHashElements(hashTable thisHash){
    if(thisHash != NULL){
        for (int i = 0; i < thisHash->hashNumber; ++i) {
            if (thisHash->listArray[i] != NULL) {
                displayList(thisHash->listArray[i]);
            }
        }
        return success;
    }
    return failure;
}