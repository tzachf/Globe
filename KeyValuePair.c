//
// Created by zahi on 11/30/18.
//

#include "KeyValuePair.h"

typedef struct Val_Key_t{
    Element Key;
    Element elem;
    freeFunction elemFreeFunc;
    //equalFunction elemCmpFunc;
    copyFunction elemCopyFunc;
    printFunction elemPrtFunc;
    freeFunction keyFreeFunc;
    equalFunction keyCmpFunc;
    copyFunction keyCopyFunc;
    printFunction keyPrtFunc;


}*Val_Key;

Val_Key createKeyValuePair(Element Key, Element elem, freeFunction elemFreeFunc, /*equalFunction elemCmpFunc,*/ copyFunction elemCopyFunc,printFunction elemPrtFunc,freeFunction keyFreeFunc,equalFunction keyCmpFunc,copyFunction keyCopyFunc,printFunction keyPrtFunc){

    Val_Key newValKey = (Val_Key)malloc(sizeof(struct Val_Key_t));
    if(newValKey==NULL){
        return NULL;
    }
    newValKey->keyFreeFunc = keyFreeFunc;
    newValKey->keyPrtFunc=keyPrtFunc;
    newValKey->elemCopyFunc=elemCopyFunc;
    newValKey->elemPrtFunc=elemPrtFunc;
    newValKey->keyCmpFunc=keyCmpFunc;
    newValKey->elemFreeFunc=elemFreeFunc;
    newValKey->keyCopyFunc=keyCopyFunc;
    newValKey->elem=elemCopyFunc(elem);
    newValKey->Key=keyCopyFunc(Key);

    return newValKey;

}

status destroyKeyValuePair(Val_Key dValKey){

    dValKey->elemFreeFunc(dValKey->elem);
    dValKey->keyFreeFunc(dValKey->Key);
    free(dValKey->elem);
    free(dValKey);
    return success;
}

void displayValue(Val_Key valKey){
    valKey->elemPrtFunc(valKey->elem);
}

void displayKey(Val_Key val_key){
    val_key->keyPrtFunc(val_key->Key);
}

Element getValue(Val_Key valKey){
    return  valKey->elem;
}

Element getKey(Val_Key valKey) {
    return valKey->Key;
}

bool isEqualKey(Val_Key valKey1,Val_Key valKey2) {

    Element Key1 =getKey(valKey1);
    Element Key2 =getKey(valKey2);

    return (valKey1->keyCmpFunc(Key1,Key2));
}

Element copyValKey(Element elem){
    Val_Key copyValKey = (Val_Key)malloc(sizeof(struct Val_Key_t));
    if (copyValKey == NULL){
        return NULL;
    }
    copyValKey->keyFreeFunc = ((Val_Key)elem)->keyFreeFunc;
    copyValKey->keyPrtFunc=((Val_Key)elem)->keyPrtFunc;
    copyValKey->elemCopyFunc=((Val_Key)elem)->elemCopyFunc;
    copyValKey->elemPrtFunc=((Val_Key)elem)->elemPrtFunc;
    copyValKey->keyCmpFunc=((Val_Key)elem)->keyCmpFunc;
    copyValKey->elemFreeFunc=((Val_Key)elem)->elemFreeFunc;
    copyValKey->keyCopyFunc=((Val_Key)elem)->keyCopyFunc;
    copyValKey->elem=((Val_Key)elem)->elemCopyFunc(((Val_Key)elem)->elem);
    copyValKey->Key=((Val_Key)elem)->keyCopyFunc(((Val_Key)elem)->Key);

    return copyValKey;

}

status displayPair(Element elem){
    elem= (Val_Key)elem;
    displayValue(elem);
}
status freeValKey(Element elem){
    elem=(Val_Key)elem;
    destroyKeyValuePair(elem);
}

bool valKeyCmp(Element elem1,Element elem2){
    elem1=(Val_Key)elem1;
    elem2=(Val_Key)elem2;
    return isEqualKey(elem1,elem2);
}

Element GcopyKey(Element key){
    char*x = (char*)key;
    char* copyKey=(char*)malloc(strlen(key)+1);
    strcpy(copyKey,x);
    return (Element)copyKey;
}
status GfreeKey(Element key){
    char*x=(char*)key;
    free(x);
    return success;
}
status GprintKey(Element key){
    char *x=(char*)key;
    printf("%s",x);
    return success;
}
bool GcmpKey(Element key1,Element key2){
    char*x=(char*)key1;
    char*y=(char*)key2;
    if(strcmp(x,y)==0){
        return true;
    }
    return false;
}
int transformKeyIntoNumberFunction(Element key){
    char*x=(char*)key;
    int sum=0;
    for (int i = 0; i <strlen(x) ; ++i) {
        sum=sum+x[i];
    }
    return sum;
}