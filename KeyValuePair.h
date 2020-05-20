//
// Created by zahi on 11/30/18.
//
#include "Defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#ifndef MYGLOBE_KEYVALUEPAIR_H
#define MYGLOBE_KEYVALUEPAIR_H

typedef struct Val_Key_t* Val_Key;

///Functions:

Val_Key createKeyValuePair(Element Key, Element elem, freeFunction elemFreeFunc, /*equalFunction elemCmpFunc,*/ copyFunction elemCopyFunc,printFunction elemPrtFunc,freeFunction keyFreeFunc,equalFunction keyCmpFunc,copyFunction keyCopyFunc,printFunction keyPrtFunc);

status destroyKeyValuePair(Val_Key dValKey);

void displayValue(Val_Key valKey);

void displayKey(Val_Key val_key);

Element getValue(Val_Key valKey);

Element getKey(Val_Key valKey);

bool isEqualKey(Val_Key valKey1,Val_Key valKey2);

Element copyValKey (Element elem);

status displayPair(Element valkey);

status freeValKey(Element elem);

bool valKeyCmp(Element elem1,Element elem2);

Element GcopyKey(Element key);

status GfreeKey(Element key);

status GprintKey(Element key);

bool GcmpKey(Element key1,Element key2);

int transformKeyIntoNumberFunction(Element key);

#endif //MYGLOBE_KEYVALUEPAIR_H