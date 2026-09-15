#ifndef MAP_H
#define MAP_H
#include "game.h"

typedef struct MapData MapData;

// forward dec
struct GameAssets;
struct GameEntities;
struct GameData;

MapData* createMap(int,int,struct GameEntities*, struct  GameEntities* , struct  GameEntities* );
void createMazeMask(MapData*);
static void generateMaze(MapData*);
void drawMap(MapData*);
void drawMazeMask(MapData*);
void removeMap(MapData*);
void removeMazeMask(MapData*);
void removeMapData(MapData*);
#endif
