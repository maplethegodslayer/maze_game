#ifndef GAME_H
#define GAME_H
#include <stdbool.h>

typedef struct GameData GameData;

void generateRandomSeed(void);
void title(void);
void gameOver(void);
void setupGame(void);
int mapBasedRNG(int);
int directionBasedRNG(void);
void initGame(char*);
bool isOdd(int);
void removeGameData(GameData*);
#endif
