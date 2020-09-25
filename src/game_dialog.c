#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
//#include <sys/ioctl.h>
//#include <sys/prctl.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include <unistd.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include "common.h"
#define GAME_TYPE_NUMS			4
static int batt = 0;
static char *pTitle = 0;
static BITMAP list_sel_bmap;

static BITMAP game_type[GAME_TYPE_NUMS][2];	//For game tag
static int game_type_sel	=0;
static int game_info_sel	= 0;
static char list_sel_flag=0;		// 0 means game type  , 1 means game list
static int loaders(void)
{
	int i;
	char img[128];
	char *respath=get_ui_image_path();
	snprintf(img,sizeof(img),"%slist_sel.png",respath);
	if(LoadBitmap(HDC_SCREEN,&list_sel_bmap,img))
		return -1;
	for(i=0;i<GAME_TYPE_NUMS;i++)
	{
		snprintf(img,sizeof(img),"%sgtype%d.png",respath,i+1);
		if(LoadBitmap(HDC_SCREEN,&game_type[i][0],img))
			return -1;
		snprintf(img,sizeof(img),"%sgtype%d_sel.png",respath,i+1);
		if(LoadBitmap(HDC_SCREEN,&game_type[i][1],img))
			return -1;
	}
	return 0;
}
static int unloaders(void)
{
	int i;
	UnloadBitmap(&list_sel_bmap);
	for(i=0;i<GAME_TYPE_NUMS;i++)
	{
		UnloadBitmap(&game_type[i][0]);
		UnloadBitmap(&game_type[i][1]);
	}
}

static LRESULT game_dialog_proc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	int i;
	switch (message){
	case MSG_INITDIALOG:
		{
			DWORD bkColor;
			HWND hFocus=GetDlgDefPushButton(hWnd);
			//loaders();
			bkColor=GetWindowElementPixel(hWnd,WE_BGC_WINDOW);
			SetWindowBkColor(hWnd,bkColor);
			if(hFocus)
				SetFocus(hFocus);
			batt=battery;
			SetTimer(hWnd,_ID_TIMER_BROWSER,TIMER_BROWSER);
			return 0;
		}
	case MSG_TIMER:
		if(wParam==_ID_TIMER_BROWSER)
		{

				if(batt!=battery)
				{
					batt=battery;
					InvalidateRect(hWnd,&msg_rcBatt,TRUE);
				}
		}
		break;
	case MSG_PAINT:
	//case MSG_PAINT:
	{
			//int page;
			gal_pixel old_brush;
			gal_pixel pixel =0xFFFFFFFF;
			hdc=BeginPaint(hWnd);
			old_brush=SetBrushColor(hdc,pixel);
			FillBoxWithBitmap(hdc,BG_PINT_X,BG_PINT_Y,BG_PINT_W,BG_PINT_H,&background_bmap);
		//	FillBoxWithBitmap(hdc,BATT_PINT_X,BATT_PINT_Y,BATT_PINT_W,BATT_PINT_H,&batt_bmap[batt]);
			/*
			SetBkColor(hdc,COLOR_transparent);
			SetBkMode(hdc,BM_TRANSPARENT);
			SetTextColor(hdc,RGB2Pixel(hdc,0xff,0xff,0xff));
			SelectFont(hdc,logfont);
			DrawText(hdc,pTitle,-1,&msg_rcTitle,DT_TOP);
			*/
		//	FillBox(hdc,TITLE_LINE_PINT_X,TITLE_LINE_PINT_Y,TITLE_LINE_
			for(i=0;i<GAME_TYPE_NUMS;i++)
			{
				if(game_type_sel==i)
					FillBoxWithBitmap(hdc,GAME_TYPE_PINT_X,GAME_TYPE_PINT_Y+i*GAME_TYPE_PINT_H,
											GAME_TYPE_PINT_W,GAME_TYPE_PINT_H,&game_type[i][1]);
				else
					FillBoxWithBitmap(hdc,GAME_TYPE_PINT_X,GAME_TYPE_PINT_Y+i*GAME_TYPE_PINT_H,
						GAME_TYPE_PINT_W,GAME_TYPE_PINT_H,&game_type[i][0]);
			}
			SetBrushColor(hdc,old_brush);
			EndPaint(hWnd,hdc);
			break;
	}
	case MSG_KEYDOWN:
			switch (wParam){
			case KEY_EXIT_FUNC:
				EndDialog(hWnd,wParam);
				break;
			case KEY_DOWN_FUNC:
				if(list_sel_flag==0)
				{
					game_type_sel++;
					if(game_type_sel>=GAME_TYPE_NUMS)
						game_type_sel=0;
				}else if(list_sel_flag==1)
				{
					game_info_sel++;


				}
				InvalidateRect(hWnd,&msg_rcBg,TRUE);
				break;
			case KEY_UP_FUNC:
				if(list_sel_flag==0)			//means game type select
				{
					game_type_sel--;
					if(game_type_sel<0)
						game_type_sel=GAME_TYPE_NUMS;
				}else if(list_sel_flag==1)
				{
						game_info_sel--;
				}

					InvalidateRect(hWnd,&msg_rcBg,TRUE);
				break;
			case KEY_LEFT_FUNC:
				if(list_sel_flag==1)
					list_sel_flag=0;
				break;
			case KEY_RIGHT_FUNC:
				if(list_sel_flag==0)
					list_sel_flag=1;
				break;
			case KEY_ENTER_FUNC:
				InvalidateRect(hWnd,&msg_rcBg,TRUE);
				break;
			}
			break;
	case MSG_COMMAND:
		break;
	case MSG_DESTROY:
			KillTimer(hWnd,TIMER_BROWSER);
			unloaders();
			break;
	}
		return DefaultDialogProc(hWnd,message,wParam,lParam);
}
void creat_game_dialog(HWND hWnd,int type,char *title)
{
	loaders();		//loade resouces
	DLGTEMPLATE gameDlg={WS_VISIBLE,WS_EX_NONE|WS_EX_AUTOSECONDARYDC,
			0,0,LCD_W,LCD_H,DESKTOP_DLG_STRING,0,0,0,NULL,0};
	pTitle=title;
	DialogBoxIndirectParam(&gameDlg,hWnd,game_dialog_proc,0L);
}



