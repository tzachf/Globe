//
// Created by Zahi Kapri on 14/11/2018.
//
#include "Countries.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct city_t{
    char* nameCity;
    char* favoriteFood;
    int population;
} *city;

typedef struct country_t{
    char* name;
    city* cities;
    cordination upper;
    cordination down;
    int numOfCities;
}*country;

typedef struct cordination_t{
    int x;
    int y;
}*cordination;







country addCountry(char* name , int x1, int y1, int x2, int y2){

    country newCountry = (country)malloc(sizeof(struct country_t));
    cordination cord1 = (cordination)malloc(sizeof(struct cordination_t));
    cordination cord2 = (cordination)malloc(sizeof(struct cordination_t));
    newCountry->name=(char*)malloc(strlen(name)+1);

    if (newCountry == NULL||cord1==NULL||cord2==NULL||newCountry->name==NULL){
        return NULL;
    }
    cord1->x=x1;
    cord1->y=y1;
    cord2->x=x2;
    cord2->y=y2;
    newCountry->upper=cord1;
    newCountry->down=cord2;
    newCountry->name = strcpy(newCountry->name,name);
    newCountry->cities=NULL;
    newCountry->numOfCities = 0;

    return newCountry;

}
city addNewCity(char* name, char* favoriteFood,int population){

    city newCity1 = (city) malloc(sizeof(struct city_t));
    newCity1->favoriteFood=(char*)malloc(strlen(favoriteFood)+1);
    newCity1->nameCity=(char*)malloc(strlen(name)+1);
    if(newCity1==NULL||newCity1->favoriteFood==NULL||newCity1->nameCity==NULL){
        return NULL;
    }
    newCity1->population=population;
    strcpy(newCity1->favoriteFood,favoriteFood);
    strcpy(newCity1->nameCity,name);


    return newCity1;

}
status addCityToCountry(city newCity,country uCountry){

    if(uCountry->numOfCities==0){
        uCountry->cities=(city*)malloc(sizeof(city));
    }else {
        uCountry->cities = (city*) realloc(uCountry->cities, ((sizeof(city)) * ((uCountry->numOfCities) + 1)));
    }
    uCountry->cities[uCountry->numOfCities]= (city)malloc(sizeof(struct city_t));
    if(uCountry->cities==NULL||uCountry->cities[uCountry->numOfCities]==NULL){
        return failure;
    }
    uCountry->cities[uCountry->numOfCities]->nameCity=(char*)malloc(strlen(newCity->nameCity)+1);
    uCountry->cities[uCountry->numOfCities]->favoriteFood = (char*)malloc(strlen(newCity->favoriteFood)+1);

    if(uCountry->cities[uCountry->numOfCities]->nameCity==NULL||uCountry->cities[uCountry->numOfCities]->favoriteFood==NULL){
        return failure;
    }
    uCountry->cities[uCountry->numOfCities]->population=newCity->population;
    strcpy(uCountry->cities[uCountry->numOfCities]->favoriteFood,newCity->favoriteFood);
    strcpy(uCountry->cities[uCountry->numOfCities]->nameCity,newCity->nameCity);

    uCountry->numOfCities++;
    return success;
}

int searchCity(country countryName , char* cityName ){
    for (int i = 0; i < countryName->numOfCities; ++i) {
        if (strcmp(countryName->cities[i]->nameCity,cityName) == 0){
            return i;
        }

    }
    return (-1);
}


status deleteCity(country uCountry, char* name){
    int index= searchCity(uCountry,name);

    if(index==(-1)){
        return failure;
    }
    free(uCountry->cities[index]->nameCity);
    free(uCountry->cities[index]->favoriteFood);
    free(uCountry->cities[index]);
    uCountry->numOfCities--;
    if(uCountry->numOfCities==0){
        free(uCountry->cities);
        return success;
    }
    for(int i=index;i<uCountry->numOfCities;i++)
    {
        uCountry->cities[i]=uCountry->cities[i+1];
    }
    uCountry->cities=(city*)realloc(uCountry->cities,sizeof(city)*(uCountry->numOfCities));
    if(uCountry->cities==NULL){
        return failure;
    }
    return success;
}

status isBounded(country aCountry, int x, int y) {
    if(x < aCountry->upper->x || x > aCountry->down->x )
        return failure;

    if(y > aCountry->upper->y || y < aCountry->down->y )
        return failure;

    return success;
}

void freeCountry(country delCountry){

    for (int i = 0; i <delCountry->numOfCities ; i++) {
        free(delCountry->cities[i]->nameCity);
        free(delCountry->cities[i]->favoriteFood);
        free(delCountry->cities[i]);
    }
    free(delCountry->cities);
    free(delCountry->name);
    free(delCountry->down);
    free(delCountry->upper);
}

country copyCountry(country copyCountry){

    country newCountry=(country)malloc(sizeof(struct country_t));
    if(newCountry==NULL){
        return NULL;
    }
    if(copyCountry->cities!=NULL) {
        newCountry->cities = (city *) malloc(sizeof(city) * (copyCountry->numOfCities));
        if(newCountry->cities==NULL){
            return NULL;
        }
    }else{
        newCountry->cities=NULL;
    }
    for(int i=0;i<copyCountry->numOfCities;i++){
        newCountry->cities[i]=(city)malloc(sizeof(struct city_t));
        newCountry->cities[i]->nameCity=(char*)malloc((strlen(copyCountry->cities[i]->nameCity))+1);
        newCountry->cities[i]->favoriteFood=(char*)malloc((strlen(copyCountry->cities[i]->favoriteFood))+1);

        if(newCountry->cities[i]==NULL||newCountry->cities[i]->nameCity==NULL||newCountry->cities[i]->favoriteFood==NULL){
            return NULL;
        }
        newCountry->cities[i]->population=copyCountry->cities[i]->population;
        strcpy(newCountry->cities[i]->nameCity,copyCountry->cities[i]->nameCity);
        strcpy(newCountry->cities[i]->favoriteFood,copyCountry->cities[i]->favoriteFood);
    }
    newCountry->upper=(cordination)malloc(sizeof(struct cordination_t));
    newCountry->down=(cordination)malloc(sizeof(struct cordination_t));
    if(newCountry->down==NULL||newCountry->upper==NULL){
        return NULL;
    }
    newCountry->upper->x=copyCountry->upper->x;
    newCountry->upper->y=copyCountry->upper->y;

    newCountry->down->x=copyCountry->down->x;
    newCountry->down->y=copyCountry->down->y;
    newCountry->name=(char*)malloc((strlen(copyCountry->name))+1);
    if(newCountry->name==NULL){
        return NULL;
    }
    strcpy(newCountry->name,copyCountry->name);
    newCountry->numOfCities=copyCountry->numOfCities;
    return newCountry;
}

status printCountry(country pCountry){
    if(pCountry != NULL){
        printf("Country %s coordinations: <%d,%d> , <%d,%d>\n",pCountry->name,pCountry->upper->x,pCountry->upper->y,pCountry->down->x,pCountry->down->y);
        for(int i=0;i<pCountry->numOfCities;i++){
            printf("\t%s includes %d residents and their favorite food is %s.\n",pCountry->cities[i]->nameCity,pCountry->cities[i]->population,pCountry->cities[i]->favoriteFood);
        }
        return success;
    }
    return failure;

}
int searchCountry(char* name,country* countries,int numOfCountries) {
    for (int i = 0; i < numOfCountries; i++) {
        if (strcmp(countries[i]->name, name) == 0)
            return i;
    }
    return -1;
}

void freeCityFields(city thisCity){
    free(thisCity->favoriteFood);
    free(thisCity->nameCity);
}

char* getCountryName(country thisCountry){
    return thisCountry->name;
}

Element GcopyCountry (Element elemCountry){
    country x  =  (country)elemCountry;
    return  (Element)copyCountry(x);
}

status GfreeCountry (Element elemCountry){
    country x = (country)elemCountry;
    freeCountry(x);
    return success;
}

status GprintCountry(Element elemCountry){
    country x = (country)elemCountry;
    printCountry(x);
    return success;
}