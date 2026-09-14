#include "map.h"
#include "assets.h"
#include "game.h"
#include <stdlib.h>
#include <stdio.h>

struct MapData{
    char** map;
    int** mazeMask;  // Note to self: mask helps with the maze generation
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

    for(int x=0; x < mapSizeX; x++) {
        md->map[x] = (char*)malloc(mapSizeY  * sizeof(char));
            if(!md->map[x]) {
                for(int y=0; y < x; y++){
                    free(md->map[y]);
                }
                free(md->map);
            }
    }

    md->mazeMask = (int**)malloc(mapSizeX * sizeof(int*));
        if(!md->mazeMask) return NULL;

    for(int x=0; x < mapSizeX; x++) {
        md->mazeMask[x] = (int*)malloc(mapSizeY  * sizeof(int));
            if(!md->mazeMask[x]) {
                for(int y=0; y < x; y++){
                    free(md->mazeMask[y]);
                }
                free(md->mazeMask);
            }
    }

        //Note to self: entity placement code here
        for(int a=0; a < mapSizeX; a++){
            for(int b=0; b < mapSizeY; b++){
                if(b == getEntityXPosition(player) && a == getEntityYPosition(player)){
                    md->map[a][b] = getEntityIcon(player);
                    md->mazeMask[a][b] = 1;
                }else if(b == getEntityXPosition(enemy) && a == getEntityYPosition(enemy)){
                    md->map[a][b] = getEntityIcon(enemy);
                    md->mazeMask[a][b] = 1;
                }else if(b == getEntityXPosition(exit) && a == getEntityYPosition(exit)){
                    md->map[a][b] = getEntityIcon(exit);
                    md->mazeMask[a][b] = 1;
                }else{
                    md->mazeMask[a][b] = 0;
                }
            }
        }
        //
    return md;
}

void generateMaze(MapData *md){
    //establish starting position first
    //maybe do it on the game code instead?
    int x = mapBasedRNG(md->mapSizeX);
    int y = mapBasedRNG(md->mapSizeY);

    int totalMapSize = md->mapSizeX * md->mapSizeY; // total amount of cells in the table
    int* moveBuffer = calloc(totalMapSize, sizeof(int));  //contains directions made
    moveBuffer[0] = -1;         //initialize to illegal direction
    int moveCounter = 0;
    int positionCounter = 0;
    int* positionBufferX = calloc(totalMapSize, sizeof(int));
    int* positionBufferY = calloc(totalMapSize, sizeof(int));



    enum directions { UP, DOWN, LEFT, RIGHT };
    enum cellStatus { UNVISITED, VISITED }; // my approach is wrong. better to just simply generate the freaking maze
                                            // first before doing fancy stuff and cleaning up code. what is a node?

        positionBufferX[positionCounter] = 0;
        positionBufferY[positionCounter] = 0;
        moveBuffer[moveCounter] = 0;
        // starting position: check position, store it on the buffer, mark it as visited then move to next position
        // that's the plan. for now, at least
        printf("at point: %i at move: %i pos x: %i pos y: %i mapSize: %i\n", positionCounter, moveBuffer[moveCounter], positionBufferX[positionCounter], positionBufferY[positionCounter], totalMapSize);
        positionCounter++;
        moveCounter++;
         while(totalMapSize > 0){

            positionBufferX[positionCounter] = positionBufferX[positionCounter - 1] + 1;
            positionBufferY[positionCounter] = positionBufferY[positionCounter - 1] + 1;
            moveBuffer[moveCounter] = moveBuffer[moveCounter - 1] + 1;
            printf("at point: %i at move: %i pos x: %i pos y: %i mapSize: %i\n", positionCounter, moveBuffer[moveCounter], positionBufferX[positionCounter], positionBufferY[positionCounter], totalMapSize);

            positionCounter++;
            moveCounter++;
            totalMapSize--;

        }

}

void drawMap(MapData* md){
    for(int a=0; a < md->mapSizeX; a++){
        for(int b=0; b < md->mapSizeY; b++){
            printf(" %c ",md->map[a][b]);
        }
        printf("\n");
    }
}

void drawMazeMask(MapData* md){
    for(int a=0; a < md->mapSizeX; a++){
        for(int b=0; b < md->mapSizeY; b++){
            printf(" %i ",md->mazeMask[a][b]);
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
    if(md->mazeMask) {
        for(int x=0; x<md->mapSizeX;x++){
            free(md->mazeMask[x]);
        }
        free(md->mazeMask);
    }
    free(md);
}
