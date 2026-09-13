#ifndef GAME_H
#define GAME_H

typedef struct GameData GameData;


void generateRandomSeed(void);
int mapBasedRNG(int);
int directionBasedRNG(void);
void initGame(char*);
void removeGameData(GameData*);
#endif
