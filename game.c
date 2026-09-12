#include "game.h"
#include "assets.h"
#include "terminal.h"
#include "map.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//set game defaults here
#define LEVEL 1
#define MAPSIZE 10

struct GameData{
    int level;
//    int lives;
//    int score;
};

int main(int argc, char *argv[]) {

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
    generateRandomSeed();
    GameAssets* ga = createGameAssets();
    GameData* gd = malloc(sizeof(GameData));
        gd->level = LEVEL;
    int x, y;
    x = zeroToTenRNG(MAPSIZE);
    y = zeroToTenRNG(MAPSIZE);
    GameEntities* player = createGameEntities(1, 2, *pIcon);
    GameEntities* enemy = createGameEntities(9, 9, '!');
    GameEntities* exit = createGameEntities(3, 3, '$');
    char* mapString = getBoxString(ga);
    //int playerXPos = zeroToTenRNG(MAPSIZE);
    int mapsizeX;
    int mapsizeY;
    mapsizeX = mapsizeY = MAPSIZE;

    MapData* md = createMap(mapsizeX, mapsizeY, player, enemy, exit);

    printMap(md);

    removeGameAssets(ga);
    removeGameEntities(player);
    removeGameData(gd);
    removeMapData(md);

}

void generateRandomSeed(){
    srand(time(NULL));
}

int zeroToTenRNG(int number){
    return rand() % number;
}

void removeGameData(GameData* gd){
    free(gd);
}
