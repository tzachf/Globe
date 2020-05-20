//
// Created by Zahi Kapri on 14/11/2018.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Defs.h"
#ifndef Countries_H
#define Countries_H

typedef struct cordination_t* cordination;

typedef struct city_t* city;

typedef struct country_t* country;


// functions:

country addCountry(char* name , int x1, int y1, int x2, int y2);

status addCityToCountry(city newCity,country uCountry);

city addNewCity(char* name, char* favoriteFood,int population);

int searchCity(country countryName , char* cityName);

status deleteCity(country uCountry, char* name);

status isBounded(country aCountry, int x, int y);

void freeCountry(country delCountry);

status printCountry(country pCountry);

country copyCountry(country copyCountry);

int searchCountry(char* name,country* countries,int numOfCountries);

void freeCityFields(city thisCity);

char* getCountryName(country thisCountry);

status GfreeCountry (Element elemCountry);

Element GcopyCountry (Element elemCountry);

status GprintCountry(Element elemCountry);
#endif //Countries_H
