#ifndef ASSETS_H
#define ASSETS_H

typedef struct GameAssets GameAssets;
typedef struct GameEntities GameEntities;



//forward declare
struct MapData;

GameAssets* createGameAssets(void);
void setCustomMapString(GameAssets*, char*);
char* getBoxString(GameAssets*);
void removeGameAssets(GameAssets*);

GameEntities* createGameEntities(int, int , char);
char getEntityIcon(GameEntities*);
int getEntityXPosition(GameEntities*);
int getEntityYPosition(GameEntities* );
void removeGameEntities(GameEntities*);
#endif
