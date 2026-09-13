#ifndef MAP_H
#define MAP_H

#include "game.h"
typedef struct MapData MapData;

// forward dec
struct GameAssets;
struct GameEntities;
struct GameData;

MapData* createMap(int,int, struct GameEntities*, struct  GameEntities* , struct  GameEntities* );
static void generateMaze(MapData* md);
void drawMap(MapData* md);
void drawMazeMask(MapData* md);
void removeMapData(MapData*);

#endif
