#ifndef __GAME_LIST_H
#define __GAME_LIST_H

typedef struct GameInfo
{
	int id;
	int type;
	int cnt;
	char name[128];
	char res[128];
}gameInfo;
typedef struct GameList
{
	gameInfo curGame;
    struct GameList * pre;
    struct GameList * next;
}gameList,*pGameList;		//size 276byte
void gameListInit(gameList **game,gameInfo *elemnt);
void gameListClear(gameList **game);
void gameListDestroy(gameList **game);
int gameListLength(gameList * game);
int gameListInsert(gameList * *game,int i,gameInfo *element);
int gameListAppend(gameList * *game,gameInfo *element);
int gameListIsEmpty(gameList * game);
int gameListShow(gameList * game);
int gameListVal(gameList *game,int place,gameInfo *gInfo);
#endif
