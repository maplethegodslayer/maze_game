#include "map.h"
#include "assets.h"
//#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct MapData{
    char** map;
    int** mazeMask;  // Note to self: mask helps with the maze generation
    int mapSizeX;
    int mapSizeY;
    int mazeSizeX;
    int mazeSizeY;
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

        for(int a=0; a < mapSizeX; a++){
            for(int b=0; b < mapSizeY; b++){
                if(b == getEntityXPosition(player) && a == getEntityYPosition(player)){
                    md->map[a][b] = getEntityIcon(player);
                }else if(b == getEntityXPosition(enemy) && a == getEntityYPosition(enemy)){
                    md->map[a][b] = getEntityIcon(enemy);
                }else if(b == getEntityXPosition(exit) && a == getEntityYPosition(exit)){
                    md->map[a][b] = getEntityIcon(exit);
                }else{
                    md->map[a][b] = '.';
                }
            }
        }

    return md;
}

void createMazeMask(MapData* md){

    md->mazeSizeX = md->mapSizeX * 2 + 1;
    md->mazeSizeY = md->mapSizeY * 2 + 1;

    md->mazeMask = (int**)malloc(md->mazeSizeX * sizeof(int*));

        for(int x=0; x < md->mazeSizeX; x++) {
            md->mazeMask[x] = (int*)malloc(md->mazeSizeY * sizeof(int));
                if(!md->mazeMask[x]) {
                    for(int y=0; y < x; y++){
                        free(md->mazeMask[y]);
                    }
                    free(md->mazeMask);
                }
        }

    generateMaze(md);
}

static void generateMaze(MapData *md){

    int totalMazeSize = md->mazeSizeX * md->mazeSizeY; // total amount of cells in the maze
    int* moveBuffer = calloc(totalMazeSize, sizeof(int));  //contains directions made
    moveBuffer[0] = -1;         //initialize to illegal direction
    int moveCounter = 0;
    int positionCounter = 0;
    int* positionBufferX = calloc(totalMazeSize, sizeof(int));
    int* positionBufferY = calloc(totalMazeSize, sizeof(int));

    enum Directions { UP, DOWN, LEFT, RIGHT };
    enum CellStatus { UNVISITED, VISITED }; // my approach is wrong. better to just simply generate the freaking maze
                                            // first before doing fancy stuff and cleaning up code. what is a node?

    //  empty = 0, top_left = 1, top_right = 2, bottom_left = 3, bottom_right = 4, horizontal = 5
    //  vertical = 6, junc_left_hori = 7, junc_right_hori = 8, junct_top_vert = 9, junct_bottom_vert= 10
    //  11,junct_inside

        for(int a=0; a < md->mazeSizeX; a++){
            for(int b=0; b< md->mazeSizeY; b++){
                if(a == 0 && b == 0){
                    //  1, top_left
                    md->mazeMask[a][b] = 1;
                }else if(a == 0 && b == md->mazeSizeY - 1){
                    //  2, top_right
                    md->mazeMask[a][b] = 2;
                }else if(a == md->mazeSizeX-1 && b == 0){
                    //  3, bottom_left
                    md->mazeMask[a][b] = 3;
                }else if(a == md->mazeSizeX-1 && b == md->mazeSizeY-1){
                    //  4, bottom_right
                    md->mazeMask[a][b] = 4;
                }else if(a == 0 && b % 2 == 0){
                    //  9, junct_top_vert
                    md->mazeMask[a][b] = 9;
                }else if(a == md->mazeSizeX-1 && b % 2 == 0){
                    //  10, junct_bottom_vert
                    md->mazeMask[a][b] = 10;
                }else if(a == 0 || (a % 2 == 0 && b % 2 != 0) ||a == md->mazeSizeX-1){
                    //  5, horizontal
                    md->mazeMask[a][b] = 5;
                }else if(a % 2 == 0 && b == 0){
                    //  7, junc_left_hori
                    md->mazeMask[a][b] = 7;
                }else if(a % 2 == 0 && b == md->mazeSizeY-1){
                    //  8, junc_right_hori
                    md->mazeMask[a][b] = 8;
                }else if(b == 0 || (b % 2 == 0 && a % 2 != 0) || b == md->mazeSizeY-1){
                    //  6, vertical
                    md->mazeMask[a][b] = 6;
                }else if(a % 2 == 0 && b % 2 == 0){
                    //  11,junct_inside
                    md->mazeMask[a][b] = 11;
                }else{
                    md->mazeMask[a][b] = 0;
                }
            }
        }

    free(moveBuffer);
    free(positionBufferX);
    free(positionBufferY);
}

void drawMap(MapData* md){
    for(int a=0; a < md->mapSizeX; a++){
        for(int b=0; b < md->mapSizeY; b++){
            printf(" %c ",md->map[a][b]);
        }
        printf("\n\n");
    }
}

void drawMazeMask(MapData* md){
    enum MazeString{
        TOP_LEFT = 0,
        TOP_RIGHT = 3,
        BOTTOM_LEFT = 6,
        BOTTOM_RIGHT = 9,
        HORIZONTAL = 12,
        VERTICAL = 15,
        JUNC_LEFT_HORI = 18,
        JUNC_RIGHT_HORI = 21,
        JUNC_TOP_VERT = 24,
        JUNC_BOTTOM_VERT = 27,
        JUNC_INSIDE = 30
    };

    for(int a=0; a < md->mazeSizeX; a++){
        for(int b=0; b < md->mazeSizeY; b++){
            printf(" %i ",md->mazeMask[a][b]);
        }
        printf("\n");
    }
}

void removeMap(MapData* md){
    if(md->map) {
        for(int x=0; x<md->mapSizeX;x++){
            free(md->map[x]);
        }
        free(md->map);
    }
}

void removeMazeMask(MapData* md){
    if(md->mazeMask) {
        for(int x=0; x<md->mapSizeX;x++){
            free(md->mazeMask[x]);
        }
        free(md->mazeMask);
    }
}

void removeMapData(MapData* md){
    free(md);
}
