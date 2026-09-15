#include "game.h"
#include "assets.h"
#include "terminal.h"
#include "map.h"

#include <stdio.h>
//#include <stdbool.h>
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
    title();
    setupGame();

return 0;
}

void setupGame(void){
    char chInput, chConfirm;
    bool outerloop = true;
    bool innerloop = true;

        while(outerloop){
            printf(FOREGROUND_BLUE "Enter your character ");
            printf(FOREGROUND_RED "(cannot be ! or $): " FOREGROUND_GREEN);
            scanf(" %c", &chInput);

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
    createMazeMask(md);

    drawMap(md);
    drawMazeMask(md);
    printf("\n");
    //╔╗╚╝═║╠╣╦╩╬


    removeGameAssets(ga);
    removeGameEntities(player);
    removeGameData(gd);
    removeMazeMask(md);
    removeMap(md);
    removeMapData(md);
}

void title(void){
    char a;
clearAndResetScreen();

printf("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
printf("║\t\t\t\t\t\t\t\t\t\t\t\t\t\t║\n");
printf("║\t\t\t\t\t\t\t\t\t\t\t\t\t\t║\n");
printf("║\t\t\t\t\t\t\t\t\t\t\t\t\t\t║\n");
printf("║\t\t\t\t    /$$$$$$                      /$$ /$$\t\t\t\t\t║\n");
printf("║\t\t\t\t   /$$__  $$                    |__/|__/\t\t\t\t\t║\n");
printf("║\t\t\t\t  | $$  \\ $$  /$$$$$$$  /$$$$$$$ /$$ /$$\t\t\t\t\t║\n");
printf("║\t\t\t\t  | $$$$$$$$ /$$_____/ /$$_____/| $$| $$\t\t\t\t\t║\n");
printf("║\t\t\t\t  | $$__  $$|  $$$$$$ | $$      | $$| $$\t\t\t\t\t║\n");
printf("║\t\t\t\t  | $$  | $$ \\____  $$| $$      | $$| $$\t\t\t\t\t║\n");
printf("║\t\t\t\t  | $$  | $$ /$$$$$$$/|  $$$$$$$| $$| $$\t\t\t\t\t║\n");
printf("║\t\t\t\t  |__/  |__/|_______/  \\_______/|__/|__/\t\t\t\t\t║\n");
printf("║\t\t\t\t\t\t\t\t\t\t\t\t\t\t║\n");
printf("║\t   /$$      /$$\t\t\t\t\t\t\t\t\t\t\t\t║\n");
printf("║\t  | $$$    /$$$\t\t\t\t\t\t\t\t\t\t\t\t║\n");
printf("║\t  | $$$$  /$$$$  /$$$$$$  /$$$$$$$$  /$$$$$$         /$$$$$$   /$$$$$$  /$$$$$$/$$$$   /$$$$$$  \t║\n");
printf("║\t  | $$ $$/$$ $$ |____  $$|____ /$$/ /$$__  $$       /$$__  $$ |____  $$| $$_  $$_  $$ /$$__  $$  \t║\n");
printf("║\t  | $$  $$$| $$  /$$$$$$$   /$$$$/ | $$$$$$$$      | $$  \\ $$  /$$$$$$$| $$ \\ $$ \\ $$| $$$$$$$$  \t║\n");
printf("║\t  | $$ \\ $ | $$ /$$__  $$  /$$__/  | $$_____/      | $$  | $$ /$$__  $$| $$ | $$ | $$| $$_____/\t\t║\n");
printf("║\t  | $$ \\/  | $$|  $$$$$$$ /$$$$$$$$|  $$$$$$$      |  $$$$$$$|  $$$$$$$| $$ | $$ | $$|  $$$$$$$\t\t║\n");
printf("║\t  |__/     |__/ \\_______/|________/ \\_______/       \\____  $$\\_______/|__/ |__/ |__/ \\_______/\t\t║\n");
printf("║\t                                                    /$$   \\ $$\t\t\t\t\t\t║\n");
printf("║\t                                                   |  $$$$$$/\t\t\t\t\t\t║\n");
printf("║\t                                                    \\______/\t\t\t\t\t\t║\n");
printf("║\t\t\t\t\t\t\t\t\t\t\t\t\t\t║\n");
printf("║\t\t\t\t\t\t\t\t\t\t\t\t\t\t║\n");
printf("║\t\t\t\t\t\t\t\t\t\t\t\t\t\t║\n");
printf("╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n");
scanf(" %c", &a);
clearAndResetScreen();
}

void gameOver(void){

}

void generateRandomSeed(void){
    srand(time(NULL));
}

int mapBasedRNG(int number){
    return rand() % (number - 1); // randomizes from 0 to N-1
}

int directionBasedRNG(void){
    return rand() % 5; // randomizes 0 - 4
}

bool isOdd(int number){
    if(number & 1){
        return true;
    } else{
        return false;
    }
}

void removeGameData(GameData* gd){
    free(gd);
}
