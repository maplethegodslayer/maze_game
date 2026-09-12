#include "map.h"
#include "assets.h"
#include <stdlib.h>
#include <stdio.h>

struct MapData{
    char** map;
//    int** mazeMask;  // for future use? i maybe? still reading about this..
    int mapSizeX;
    int mapSizeY;

};

MapData* createMap(int mapSizeX,int mapSizeY, GameEntities* player, GameEntities* enemy, GameEntities* exit){


    MapData* md = malloc(sizeof(MapData));
        if(!md) return NULL;

    md->mapSizeX = mapSizeX;
    md->mapSizeY = mapSizeY;

    md->map = (char**)malloc(mapSizeX * sizeof(char*));
        if(!md->map) return NULL;

    for(int x=0; x <= mapSizeX; x++) {
        md->map[x] = (char*)malloc(mapSizeY  * sizeof(char));
            if(!md->map[x]) {
                for(int y=0; y <= x; y++){
                    free(md->map[y]);
                }
                free(md->map);
            }
    }


//temporary things here
    int playerXPos = getEntityXPosition(player);
    int playerYPos = getEntityYPosition(player);
    int enemyXPos = getEntityXPosition(enemy);
    int enemyYPos = getEntityYPosition(enemy);
    int exitXPos = getEntityYPosition(exit);
    int exitYPos = getEntityYPosition(exit);
    char playerIcon = getEntityIcon(player);
    char enemyIcon = getEntityIcon(enemy);
    char exitIcon = getEntityIcon(exit);
//

        for(int a=0; a < mapSizeX; a++){
            for(int b=0; b < mapSizeY; b++){
                if(b == playerXPos && a == playerYPos){
                    md->map[a][b] = playerIcon;
                }else if(b == enemyXPos && a == enemyYPos){
                    md->map[a][b] = enemyIcon;
                }else if(b == exitXPos && a == exitYPos){
                    md->map[a][b] = exitIcon;
                }
            }
        }

    return md;
}

void printMap(MapData* md){
    for(int a=0; a < md->mapSizeX; a++){
        for(int b=0; b< md->mapSizeY; b++){
            printf(" %c ",md->map[a][b]);
        }
        printf("\n");
    }
}

void removeMapData(MapData* md){
    if(md->map) {
        for(int x=0; x<md->mapSizeX;x++){
            free(md->map[x]);
        }
        free(md->map);
    }
    free(md);
}
