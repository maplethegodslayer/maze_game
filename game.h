#ifndef GAME_H
#define GAME_H

typedef struct GameData GameData;


void generateRandomSeed();
int zeroToTenRNG(int number);
void initGame(char*);
void removeGameData(GameData*);
#endif
