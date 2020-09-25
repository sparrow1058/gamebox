#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gamelist.h"
//defined the global game list
void gameListInit(gameList **game,gameInfo *element)	//结构体指针的指针
{
	*game=(gameList *)malloc(sizeof(gameList));
	if(*game==NULL)
	{
		printf("can't malloc a game list");
		exit(0);

	}
	(*game)->curGame.id=element->id;
	(*game)->curGame.type=element->type;
	(*game)->curGame.cnt=element->cnt;
	strcpy((*game)->curGame.name,element->name);
	strcpy((*game)->curGame.res,element->res);
	(*game)-> next=*game;
	(*game)-> pre=*game;
}
void gameListClear(gameList **game)	//指针
{
	gameList *p= (*game)->next;	//
	while(p!=*game)
	{
		p=p->next;
		free(p->pre);
	}
	(*game)->next=*game;
	(*game)->pre=*game;
}
void gameListDestroy(gameList **game)
{
	gameListClear(game);
	free(*game);
	*game=NULL;
}
int gameListLength(gameList * game)
{
	int j=1;
	gameList * p=game->next;
	if(game==NULL)		//not init
		return 0;
	else if(p==game)
		return 1;		//only one element
	else{
		while(p!=game)		//more than one element
		{
			j++;
			p=p->next;
		}
	}
	return j;
}

int gameListInsert(gameList * *game,int i,gameInfo *element)
{
	gameList * p= *game;
	gameList * pCur, *pNext;
	int j=0;
	if(i<1||i>gameListLength(*game)+1)
		return 0;
	while(j<i-1)
	{
		++j;			//search the i gameinfo
		p=p->next;

	}
	pCur=(gameList *)malloc(sizeof(struct GameList));
	pCur->curGame.id=element->id;
	pCur->curGame.type=element->type;
	pCur->curGame.cnt=element->cnt;
	strcpy(pCur->curGame.name,element->name);
	strcpy(pCur->curGame.res,element->res);

	pNext=p->next;


	p->next=pCur;
	pCur->pre=p;		//the left pointer

	pCur->next=pNext;
	pNext->pre=pCur;	//the right pointer
	return 0;
}
void gameListInfoChange(gameList **game,int i,gameInfo *element)
{
	gameList * p= *game;
	int j=0;
	while(j<i-1)	//if i=1 the first one element
	{
		++j;			//search the i gameinfo
		p=p->next;
	}
	p->curGame.id=element->id;
	p->curGame.type=element->type;
	p->curGame.cnt=element->cnt;
	strcpy(p->curGame.name,element->name);
	strcpy(p->curGame.res,element->res);
}

int gameListAppend(gameList * *game,gameInfo *element)
{
	int tail=gameListLength(*game);
	gameListInsert(game,tail,element);
	return tail+1;
}
int gameListIsEmpty(gameList * game)
{
	if(game->pre==game&&game->next==game)
		return 0;
	else
		return 1;
}

int gameListShow(gameList * game)
{
	gameList * p=game;
	int i,len;
	if(game==NULL)
		return 0;
	if(gameListIsEmpty(game))
	{
		 len=gameListLength(game);
		printf("gamelist len is %d \n",len);
		for( i=0;i<len;i++)
		{
			printf("game info:id=%4d name=%s  res=%s \n",p->curGame.id,p->curGame.name,p->curGame.res);
			p=p->next;
		}
		return len;


	}else
	{
		printf("game List is empty \n");
		return 0;
	}


}
int gameListVal(gameList *game,int place,gameInfo *gInfo)
{
	int i=1,len;
	gameList *p=game;
	len=gameListLength(game);
	if(place>0&&place<len+1)
	{
		for(i=1;i<place;i++,p=p->next);
		gInfo->id=p->curGame.id;
		gInfo->cnt=p->curGame.cnt;
		gInfo->type=p->curGame.type;
		strcpy(gInfo->name,p->curGame.name);
		strcpy(gInfo->res,p->curGame.res);
		printf("gameListVal:id=%4d name=%s  res=%s \n",p->curGame.id,p->curGame.name,p->curGame.res);
		return 0;
	}
	return 1;

}
