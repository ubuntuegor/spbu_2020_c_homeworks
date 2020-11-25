#include "../library/graph/graph.h"
#include "../library/numeric/list.h"
#include <stdio.h>
#include <stdlib.h>

const char inputFilename[] = "hw7task2_input.txt";

typedef struct Country {
    int capital;
    List* cities;
    List* nearestCitiesIds;
    List* nearestCitiesDistance;
} Country;

int sortCitiesByDistance(const void* a, const void* b)
{
    return getDistanceGraphNode(*(GraphNode**)a) - getDistanceGraphNode(*(GraphNode**)b);
}

void addCity(Graph* citiesGraph, bool* occupiedCities, Country* country, int city)
{
    insert(country->cities, getLength(country->cities), createListElement(city));
    occupiedCities[city] = true;

    GraphNode** newNeighborCities = NULL;
    int newNeighborCitiesCount = getOutwardGraphConnections(citiesGraph, city, &newNeighborCities);
    if (newNeighborCitiesCount == 0)
        return;

    qsort(newNeighborCities, newNeighborCitiesCount, sizeof(GraphNode*), sortCitiesByDistance);
    ListElement* nearestCityIdElement = getFirstElement(country->nearestCitiesIds);
    ListElement* nearestCityDistanceElement = getFirstElement(country->nearestCitiesDistance);
    int cityListPosition = 0;
    bool* cityIsAlreadyNear = (bool*)calloc(getGraphNodeCount(citiesGraph), sizeof(bool));

    for (int i = 0; i < newNeighborCitiesCount; ++i) {
        int newNeighborCityId = getIdGraphNode(newNeighborCities[i]);
        int newNeighborCityDistance = getDistanceGraphNode(newNeighborCities[i]);
        if (occupiedCities[newNeighborCityId])
            continue;

        int nearestCityId = getElementValue(nearestCityIdElement);
        int nearestCityDistance = getElementValue(nearestCityDistanceElement);

        while (nearestCityDistanceElement != NULL && nearestCityDistance <= newNeighborCityDistance) {
            cityIsAlreadyNear[nearestCityId] = true;
            nearestCityIdElement = getNextElement(nearestCityIdElement);
            nearestCityDistanceElement = getNextElement(nearestCityDistanceElement);
            nearestCityId = getElementValue(nearestCityIdElement);
            nearestCityDistance = getElementValue(nearestCityDistanceElement);
            cityListPosition++;
        }

        if (!cityIsAlreadyNear[newNeighborCityId]) {
            insert(country->nearestCitiesIds, cityListPosition, createListElement(newNeighborCityId));
            insert(country->nearestCitiesDistance, cityListPosition, createListElement(newNeighborCityDistance));
            cityListPosition++;
        }
    }

    destroyGraphConnections(&newNeighborCities, newNeighborCitiesCount);
    free(cityIsAlreadyNear);
}

void printListIncremented(List* list, int increment)
{
    ListElement* element = getFirstElement(list);
    while (element != NULL) {
        printf("%d ", getElementValue(element) + 1);
        element = getNextElement(element);
    }
    printf("\n");
}

bool expandCountry(Graph* citiesGraph, bool* occupiedCities, Country* country)
{
    bool didSuccessfullyExpand = false;
    ListElement* candidateCityIdElement = getFirstElement(country->nearestCitiesIds);
    while (!didSuccessfullyExpand) {
        if (candidateCityIdElement == NULL)
            return false;

        int candidateCityId = getElementValue(candidateCityIdElement);
        candidateCityIdElement = getNextElement(candidateCityIdElement);

        eject(country->nearestCitiesIds, 0);
        eject(country->nearestCitiesDistance, 0);

        if (!occupiedCities[candidateCityId]) {
            addCity(citiesGraph, occupiedCities, country, candidateCityId);
            didSuccessfullyExpand = true;
        }
    }
    return true;
}

Country* createCountry(Graph* citiesGraph, bool* occupiedCities, int capital)
{
    Country* country = (Country*)malloc(sizeof(Country));
    country->capital = capital;
    country->cities = createList();
    country->nearestCitiesIds = createList();
    country->nearestCitiesDistance = createList();

    addCity(citiesGraph, occupiedCities, country, capital);

    return country;
}

void printCountry(Country* country, int number)
{
    printf("Country %d with capital %d\n", number, country->capital + 1);
    printf("Cities: ");
    printListIncremented(country->cities, 1);
}

void destroyCountry(Country* country)
{
    destroyList(&country->cities);
    destroyList(&country->nearestCitiesIds);
    destroyList(&country->nearestCitiesDistance);
    free(country);
}

void readRoadsData(FILE* inputFile, Graph* citiesGraph, int roadsCount)
{
    for (int i = 0; i < roadsCount; ++i) {
        int fromNode = 0;
        int toNode = 0;
        int length = 0;
        fscanf(inputFile, "%d %d %d", &fromNode, &toNode, &length);
        connectGraph(citiesGraph, fromNode - 1, toNode - 1, length);
    }
}

void readCapitalsData(FILE* inputFile, Graph* citiesGraph, Country** countries, bool* occupiedCities, int capitalCount)
{
    for (int i = 0; i < capitalCount; ++i) {
        int capital = 0;
        fscanf(inputFile, "%d", &capital);
        countries[i] = createCountry(citiesGraph, occupiedCities, capital - 1);
    }
}

int main()
{
    printf("Reading input from %s\n", inputFilename);
    FILE* inputFile = fopen(inputFilename, "r");

    if (inputFile == NULL) {
        printf("Fail! Make sure this input file exists.\n");
        return 0;
    }

    int citiesCount = 0;
    int roadsCount = 0;
    fscanf(inputFile, "%d %d", &citiesCount, &roadsCount);

    Graph* citiesGraph = createGraph(citiesCount, true);
    readRoadsData(inputFile, citiesGraph, roadsCount);

    int capitalCount = 0;
    fscanf(inputFile, "%d", &capitalCount);

    Country** countries = (Country**)calloc(capitalCount, sizeof(Country*));
    bool* occupiedCities = (bool*)calloc(citiesCount, sizeof(bool));
    readCapitalsData(inputFile, citiesGraph, countries, occupiedCities, capitalCount);

    fclose(inputFile);

    bool canExpand = true;
    while (canExpand) {
        canExpand = false;
        for (int i = 0; i < capitalCount; ++i) {
            bool expanded = expandCountry(citiesGraph, occupiedCities, countries[i]);
            if (expanded)
                canExpand = true;
        }
    }

    destroyGraph(&citiesGraph);
    free(occupiedCities);

    printf("\n");
    for (int i = 0; i < capitalCount; ++i) {
        Country* country = countries[i];
        printCountry(country, i + 1);
        printf("\n");
        destroyCountry(country);
    }

    free(countries);

    return 0;
}
