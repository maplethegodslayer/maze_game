#ifndef MAP_H
#define MAP_H

#include "game.h"
typedef struct MapData MapData;

// forward dec
struct GameAssets;
struct GameEntities;
struct GameData;

void drawMap();
MapData* createMap(int,int, struct GameEntities*, struct  GameEntities* , struct  GameEntities* );
static void generateMaze(int, int);
void printMap(MapData*);
void removeMapData(MapData*);

#endif
