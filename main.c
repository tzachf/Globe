#include <stdio.h>
#include "KeyValuePair.h"
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "HashTable.h"
#include "Countries.h"

int main(int argc,char* argv[]) {

    FILE *configFile = fopen(argv[3],"r");

    if(configFile==NULL){
        return failure;
    }
    hashTable CountriesHash = createHashTable(GcopyKey,GfreeKey,GprintKey,GcopyCountry,GfreeCountry,GprintCountry,GcmpKey,transformKeyIntoNumberFunction,atoi(argv[1]));
    char line[300];
    int cordx1;
    int cordy1;
    int cordx2;
    int cordy2;
    char* favoriteFood;
    int numOfResindents;
    int i = 0;
    bool firstCountry=true;
    country thisCountry=NULL;

    while ( fgets(line, 300,configFile) != NULL) {

        if(!(line[0]=='\t')) {

            if (firstCountry == true) {
                char *const countryName = strtok(line, ",");
                cordx1 = atoi(strtok(NULL, ","));
                cordy1 = atoi(strtok(NULL, ","));
                cordx2 = atoi(strtok(NULL, ","));
                cordy2 = atoi(strtok(NULL, ","));

                thisCountry = addCountry(countryName, cordx1, cordy1, cordx2, cordy2);
                firstCountry = false;
            } else {

                Element key = (Element)getCountryName(thisCountry);
                addToHashTable(CountriesHash,key,(Element)thisCountry);
                freeCountry(thisCountry);
                free(thisCountry);
                char *const countryName = strtok(line, ",");
                cordx1 = atoi(strtok(NULL, ","));
                cordy1 = atoi(strtok(NULL, ","));
                cordx2 = atoi(strtok(NULL, ","));
                cordy2 = atoi(strtok(NULL, ","));

                thisCountry = addCountry(countryName, cordx1, cordy1, cordx2, cordy2);
            }
        }
        else{

            char* cityName = strtok(line,",");
            memmove(cityName,cityName+1,strlen(cityName));
            favoriteFood = strtok(NULL,",");
            numOfResindents = atoi(strtok(NULL,"\n"));

            city thisCity;
            thisCity = addNewCity(cityName, favoriteFood, numOfResindents);
            addCityToCountry(thisCity,thisCountry);
            freeCityFields(thisCity);
            free(thisCity);
        }
    }
    Element key = (Element)getCountryName(thisCountry);
    addToHashTable(CountriesHash,key,(Element)thisCountry);
    freeCountry(thisCountry);
    free(thisCountry);
    fclose(configFile);

    int choice = 0;
    while(choice != 8){
        printf("Please choose one of the following numbers:\n");
        printf("1: print Countries\n");
        printf("2: add country\n");
        printf("3: add city to country\n");
        printf("4: delete city from country\n");
        printf("5: print country by name\n");
        printf("6: delete country\n");
        printf("7: is country in area\n");
        printf("8: exit\n");

        scanf("%d",&choice);

        switch (choice){
            case 1:{
                displayHashElements(CountriesHash);
                break;
            }
            case 2:{
                printf("please enter a new country name\n");
                char countryname[300];
                scanf("%s",countryname);
                Element key1 = countryname;
                if(lookupInHashTable(CountriesHash,key1)!=NULL){
                    printf("country with this name already exist\n");
                    break;
                }
                printf("please enter two x and y coordinates :x1,y1,x2,y2\n");
                int x1;
                int y1;
                int x2;
                int y2;
                scanf("%d" "%d" "%d" "%d" , &x1 ,&y1 ,&x2, &y2);
                country newCountry=addCountry(countryname, x1, y1, x2, y2);
                addToHashTable(CountriesHash,key1,(Element)newCountry);
                freeCountry(newCountry);
                free(newCountry);
                break;

            }
            case 3:{
                printf("please enter a country name\n");
                char countryname[300];
                scanf("%s",countryname);
                Element key3 = (Element)countryname;
                if(lookupInHashTable(CountriesHash,key3)!=NULL){
                    country countryToAdd= copyCountry((country)lookupInHashTable(CountriesHash,key3));
                    printf("please enter a city name\n");
                    char cityname[300];
                    scanf("%s",cityname);
                    if(searchCity(countryToAdd,cityname) == -1) {
                        printf("please enter the city favorite food\n");
                        char food[300];
                        scanf("%s", food);
                        printf("please enter number of residents in city\n");
                        int population;
                        scanf("%d", &population);
                        city newCity = addNewCity(cityname, food, population);
                        addCityToCountry(newCity, countryToAdd);
                        removeFromHashTable(CountriesHash, key3);
                        addToHashTable(CountriesHash, key3, countryToAdd);
                        freeCityFields(newCity);
                        free(newCity);
                        freeCountry(countryToAdd);
                        free(countryToAdd);
                        break;
                    }
                    printf("the city already exist in this country\n");
                    break;
                }
                printf("country not exist\n");
                break;
            }
            case 4:{
                printf("please enter a country name\n");
                char countryname[300];
                scanf("%s",countryname);
                Element key1 = (Element)countryname;

                country existCountry = (country)lookupInHashTable(CountriesHash, key1);
                if(existCountry!=NULL){
                    printf("please enter a city name\n");
                    char cityname[300];
                    scanf("%s",cityname);
                    if((searchCity(existCountry,cityname) != -1)){
                        deleteCity(existCountry,cityname);
                        break;
                    }
                    printf("the city not exist in this country\n");
                    break;
                }
                printf("country name not exist\n");
                break;
            }
            case 5:{
                printf("please enter a country name\n");
                char countryName[300];
                scanf("%s",countryName);
                Element key5 = (Element) countryName;
                if(lookupInHashTable(CountriesHash,key5)==NULL){
                    printf("country name not exist\n");
                    break;
                }
                printCountry((country)lookupInHashTable(CountriesHash,key5));
                break;
            }
            case 6:{
                printf("please enter a country name\n");
                char countryName[300];
                scanf("%s",countryName);
                Element key6 = (Element) countryName;

                if(removeFromHashTable(CountriesHash,key6)==failure){
                    printf("can't delete the country\n");
                    break;
                }
                printf("country deleted\n");
                break;
            }
            case 7:{
                printf("please enter a country name\n");
                char countryName[300];
                scanf("%s",countryName);
                Element key7 = (Element) countryName;
                country testCountry = (country)lookupInHashTable(CountriesHash,key7);
                if(testCountry==NULL){
                    printf("country name not exist\n");
                    break;
                }
                printf("please enter x and y coordinations:x,y\n");
                int x1;
                int y1;
                scanf("%d",&x1);
                scanf("%d",&y1);
                if(isBounded(testCountry,x1,y1) != success){
                    printf("the coordinate not in the country\n");
                    break;
                }
                printf("the coordinate in the country\n");
                break;

            }
            case 8:{
                destroyHashTable(CountriesHash);
                break;
            }
            default: {
                printf("please choose a valid number\n");
                break;
            }
        }


    }
    return 0;
}
