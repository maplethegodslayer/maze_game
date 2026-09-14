#include "game.h"
#include "assets.h"
#include "terminal.h"
#include "map.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//set game defaults here
#define DEFAULT_LEVEL 1
#define DEFAULT_MAPSIZE 10

struct GameData{
    int level;
//    int lives;
//    int score;
};

int main(int argc, char *argv[]) {

    generateRandomSeed();

    char chInput, chConfirm;
    bool outerloop = true;
    bool innerloop = true;

        while(outerloop){
            printf(FOREGROUND_BLUE "Enter your character ");
            printf(FOREGROUND_RED "(cannot be ! or $): " FOREGROUND_GREEN);
            scanf(" %c", &chInput);
            fflush(stdin);

                switch(chInput){
                    case '!':
                        case '$':
                            printf(FOREGROUND_RED "Invalid input!\n");
                            break;
                    default:
                        printf(FOREGROUND_BLUE "Your character is:" FOREGROUND_GREEN " %c\n" , chInput);

                            while(innerloop){
                                printf(FOREGROUND_BLUE "Confirm?" FOREGROUND_GREEN "(y/n): ");
                                scanf(" %c", &chConfirm);

                                switch(chConfirm){
                                    case 'y':
                                        case 'Y':
                                            innerloop = false;
                                            outerloop = false;
                                            //clrscr and proceed to game
                                            clearAndResetScreen();
                                            // init the game here~

                                            initGame(&chInput);
                                            break;
                                    case 'n':
                                        case 'N':
                                            innerloop = false;
                                            outerloop = true;
                                            break;
                                    default:
                                        printf(FOREGROUND_RED "Invalid input!\n");
                                        break;
                                }
                            }
                        innerloop = true;

                    break;
                }
        }

return 0;
}

void initGame(char* pIcon){

    GameAssets* ga = createGameAssets();
    GameData* gd = malloc(sizeof(GameData));
        gd->level = DEFAULT_LEVEL;

    GameEntities* player = createGameEntities(mapBasedRNG(DEFAULT_MAPSIZE), mapBasedRNG(DEFAULT_MAPSIZE), *pIcon);
    GameEntities* enemy = createGameEntities(mapBasedRNG(DEFAULT_MAPSIZE),mapBasedRNG(DEFAULT_MAPSIZE), '!');
    GameEntities* exit = createGameEntities(mapBasedRNG(DEFAULT_MAPSIZE), mapBasedRNG(DEFAULT_MAPSIZE), '$');

    int mapsizeX;
    int mapsizeY;
    mapsizeX = mapsizeY = DEFAULT_MAPSIZE;

    MapData* md = createMap(mapsizeX, mapsizeY, player, enemy, exit);

    drawMap(md);    // commented it out for testing. trying to make maze generation to work first.
    printf("\n");
    generateMaze(md);
    printf("\n");
    drawMazeMask(md);

    removeGameAssets(ga);
    removeGameEntities(player);
    removeGameData(gd);
    removeMapData(md);

}

void generateRandomSeed(){
    srand(time(NULL));
}

int mapBasedRNG(int number){
    return rand() % (number - 1); // randomizes from 0 to N-1
}

int directionBasedRNG(void){
    return rand() % 5; // randomizes 0 - 4
}

void removeGameData(GameData* gd){
    free(gd);
}
