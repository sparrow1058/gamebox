#include "libxml/parser.h"
#include <stdlib.h>
#include <string.h>
#include "gamelist.h"
typedef struct XMLINFO
{
	char name[60];
	int	 idMini;
	int	 idMax;
}xmlInfo;
gameList *gGameList=NULL;
xmlInfo	gXml;
//char xmlName[48];

void xmlUpdateFile(char *fileName)
{
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL, pcur = NULL;
	xmlChar *szKey;
	xmlKeepBlanksDefault(0);//必须加上，防止程序把元素前后的空白文本符号当作一个node
	xmlIndentTreeOutput = 1;
	pdoc = xmlReadFile (fileName, "GBK", XML_PARSE_NOBLANKS);////libxml只能解析UTF-8格式数据 XML_PARSE_RECOVER); XML_PARSE_NOBLANKS
	if (pdoc == NULL)
	{
		printf ("error:can't open xml file!\n");
		exit (1);
	}
	proot = xmlDocGetRootElement (pdoc);
	if (proot == NULL)
	{
		printf("error: file is empty!\n");
		exit (1);
	}
	pcur = proot->xmlChildrenNode;
  while (pcur != NULL)
  {
	if (!xmlStrcmp(pcur->name, BAD_CAST("game_info")))
    {
		szKey=xmlNodeGetContent(pcur);
		printf("newNode:%s \n",szKey);
		xmlFree(szKey);
		xmlAttrPtr attrPtr=	pcur->properties;
		while(attrPtr!=NULL)
		{
			xmlChar *szAttr=xmlGetProp(pcur,attrPtr->name);
			if(!xmlStrcmp(attrPtr->name,BAD_CAST("cnt")))
			{
				char *cntStr=(char *)szAttr;
				int cnt=atoi(cntStr);
				sprintf(cntStr,"%d",++cnt);
				xmlSetProp(pcur,attrPtr->name,BAD_CAST(cntStr));
			}

			xmlFree(szAttr);
			attrPtr=attrPtr->next;
		}


    }
    pcur = pcur->next;
  }
	xmlSaveFormatFile(fileName,pdoc,1);
//	xmlSaveFile(fileName,pdoc);
  xmlFreeDoc (pdoc);
  xmlCleanupParser ();
  xmlMemoryDump ();

}
int xmlParserGameList(char *fileName,gameList **game,xmlInfo *xmlinfo,int startId,int len)
{
	xmlDocPtr pdoc = NULL;
	xmlNodePtr proot = NULL, pcur = NULL;
	xmlChar *szKey;
	gameInfo gg;
	int	idFlag=0;
	//int idmin,idGet;
	int nums=0;
	xmlKeepBlanksDefault(0);//必须加上，防止程序把元素前后的空白文本符号当作一个node
	pdoc = xmlReadFile (fileName, "GBK", XML_PARSE_NOBLANKS);//libxml只能解析UTF-8格式数据
	if (pdoc == NULL)
	{
		printf ("error:can't open xml file!\n");
		exit (1);
	}
	proot = xmlDocGetRootElement (pdoc);
	if (proot == NULL)
	{
		printf("error: file is empty!\n");
		exit (1);
	}
//	gameListInit(&gGameList);		//Init the gamelist
	pcur = proot->xmlChildrenNode;
	  while (pcur != NULL)
	  {
		if (!xmlStrcmp(pcur->name, BAD_CAST("game_head")))
		{
			szKey=xmlNodeGetContent(pcur);
			strcpy(xmlinfo->name,(char *)szKey);
			xmlFree(szKey);
		}
		if (!xmlStrcmp(pcur->name, BAD_CAST("game_info")))
		{

			xmlAttrPtr attrPtr=	pcur->properties;
			while(attrPtr!=NULL)
			{
				xmlChar *szAttr=xmlGetProp(pcur,attrPtr->name);
				if(!xmlStrcmp(attrPtr->name,BAD_CAST("id")))
				{
					char *cntStr=(char *)szAttr;
					int id=atoi(cntStr);
				//	idGet=id;
					if(id <= startId)
					{
						xmlFree(szAttr);		//freee the
						idFlag=0;	// small than the find flag
					//	printf("szAttr free2 \n");
						break;				//break to the  next node
					}else
					{
						idFlag=1;
						gg.id=id;
					}
				}else if(!xmlStrcmp(attrPtr->name,BAD_CAST("name")))
				{
					strcpy(gg.name,(char *)szAttr);
				}
				xmlFree(szAttr);
				attrPtr=attrPtr->next;
			}
			if(idFlag)
			{
				idFlag=0;
				szKey=xmlNodeGetContent(pcur);
				strcpy(gg.res,(char *)szKey);		//copy res name to res
				xmlFree(szKey);
				if(gGameList==NULL)
					gameListInit(&gGameList,&gg);	//Init first element
				else
					gameListAppend(&gGameList,&gg);
				nums++;
				if(nums>=len)		//get the total games
					break;		//break; all while
			}
						// update gameinfo gg


		}

		pcur = pcur->next;
	  }

  xmlFreeDoc (pdoc);
  xmlCleanupParser ();
  xmlMemoryDump ();
  return nums;
}
