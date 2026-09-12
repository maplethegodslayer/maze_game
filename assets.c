#include <string.h>
#include <stdlib.h>
#include "assets.h"

#define BOXASCII "╔╗╚╝═║╠╣╦╩╬"

struct GameAssets {
    char* mapString;
};

struct GameEntities {
    int xCurrentPosition;
    int yCurrentPosition;
    char gameEntityIcon;
};

GameAssets* createGameAssets(void){
    GameAssets* ga = malloc(sizeof(GameAssets));
        if(!ga) return NULL;
        int stringLength = strlen(BOXASCII);
        char* tP = realloc(ga->mapString, stringLength);
        ga->mapString = tP;
        strncpy(ga->mapString, BOXASCII, stringLength);
        //ga->mapString[stringLength] = '\0'; // thanks Bro Code!
    return ga;
}

void setCustomMapString(GameAssets* ga, char* customString){

        int stringLength = strlen(customString);
        char* csP = realloc(ga->mapString, stringLength +1);
        ga->mapString = csP;

        strncpy(ga->mapString, customString, stringLength +1);
        ga->mapString[stringLength] = '\0';

}

char* getBoxString(GameAssets* ga){
    return ga->mapString;
}

void removeGameAssets(GameAssets* ga){
    free(ga);
}

GameEntities* createGameEntities(int xCoordinate, int yCoordinate, char entityIcon){
    GameEntities* ge = malloc(sizeof(GameEntities));
        if(!ge) return NULL;
        ge->xCurrentPosition = xCoordinate;
        ge->yCurrentPosition = yCoordinate;
        ge->gameEntityIcon = entityIcon;
    return ge;
}

char getEntityIcon(GameEntities* ge){
    return ge->gameEntityIcon;
}

int getEntityXPosition(GameEntities* ge){
    return ge->xCurrentPosition;
}

int getEntityYPosition(GameEntities* ge){
    return ge->yCurrentPosition;
}

void removeGameEntities(GameEntities* ge){
    free(ge);
}
