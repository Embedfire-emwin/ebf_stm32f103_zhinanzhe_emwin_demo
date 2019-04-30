/**************************************************************************************
* 因为emWin显示只支持UTF-8编码格式的中文，如果希望直接显示在Keil直接输入的中文，      *
*            比如使用：GUI_DispStringHCenterAt("流水灯",110,120);                     *
* 该文件必须以UTF-8编码格式，不然中文无法正常显示。                                   *
*                                                                                     *
* 如果只是个别例程出现中文显示乱码（如果所有例程都无法显示中文可能是字库问题），      *
* 把对应的例程文件(比如LEDapp.c)用电脑的记事本软件打开，然后选择另存为，在弹出对      *
* 话框中“保存(S)"按钮的左边有个"编码(E)"选项，选择"UTF-8",然后同样保存为同名称的      *
* C语言文件(覆盖原来文件)，再编译。                                                   *
*                                                                                     *
* 如果编译工程时出现下面类似错误也是该文件编码格式问题,必须把文件保存为UTF-8格式      *
* 再编译                                                                              *
* ..\..\User\app\LEDapp.c(275): error:  #8: missing closing quote                     *
*        GUI_DispStringHCenterAt("娴?姘?鐏?",110,120);                                *
* ..\..\User\app\LEDapp.c(276): error:  #165: too few arguments in function call      *
*        GUI_DispStringHCenterAt("瑙?鎽?鍋?宸?澶?鎵?闇€瑕?瑙?鎽?鏍?鍑?",110,215);     *
* ..\..\User\app\LEDapp.c(276): error:  #18: expected a ")"                           *
*        GUI_DispStringHCenterAt("瑙?鎽?鍋?宸?澶?鎵?闇€瑕?瑙?鎽?鏍?鍑?",110,215);     *
*                                                                                     *
* 修改文件后编译就出错这是Keil5软件问题(Keil4没这问题)，推荐使用其他程序编辑工具，    *
* 只用Keil5完成编译和下载工作。                                                       *
***************************************************************************************
*                      实验平台: 野火STM32 ISO 开发板                                 *
*                      论    坛: http://www.chuxue123.com                             *
*                      淘    宝: http://firestm32.taobao.com                          *
*                      邮    箱: wildfireteam@163.com                                 *
***************************************************************************************
*/
/**************************************************************************************
*                                                                                     *
*                SEGGER Microcontroller GmbH & Co. KG                                 *
*        Solutions for real time microcontroller applications                         *
*                                                                                     *
***************************************************************************************
*                                                                                     *
* C-file generated by:                                                                *
*                                                                                     *
*        GUI_Builder for emWin version 5.22                                           *
*        Compiled Jul  4 2013, 15:16:01                                               *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG                                *
*                                                                                     *
***************************************************************************************
*                                                                                     *
*        Internet: www.segger.com  Support: support@segger.com                        *
*                                                                                     *
***************************************************************************************
*/
// USER START (Optionally insert additional includes)
#include "includes.h"
#include  "app.h"
// USER END
/*
***************************************************************************************
*                                         宏定义 
***************************************************************************************
*/ 
#define COLOR_BORDER           0xBD814F
#define COLOR_KEYPAD0          0xA8D403
#define COLOR_KEYPAD1          0xBF5C00

#define ID_BUTTON              (GUI_ID_USER + 50)

#define BUTTON_WHITH   53
#define BUTTON_HIGHT   43
#define BUTTON_SpaceX  (3+BUTTON_WHITH) 
#define BUTTON_SpaceY  (3+BUTTON_HIGHT)
#define textlength   	20

typedef struct {
  int          xPos;
  int          yPos;
  int          xSize;
  int          ySize;
  const char * acLabel;   /* 按钮对应的字符 */
} BUTTON;

static const BUTTON ButtonData[] = 
{

	/* 第1排按钮 */
	{ 5,                   63, 				 	BUTTON_WHITH, 		BUTTON_HIGHT, "C"    },
	{ 5+BUTTON_SpaceX,     63,  				BUTTON_WHITH, 		BUTTON_HIGHT, "+/-"  },
	{ 5+BUTTON_SpaceX*2,   63,  				BUTTON_WHITH, 		BUTTON_HIGHT, "1/x"  },
	{ 5+BUTTON_SpaceX*3,   63,  				BUTTON_WHITH, 		BUTTON_HIGHT, "/"    },
	/* 第2排按钮 */
	{ 5,                   63+BUTTON_SpaceY,  	BUTTON_WHITH, 		BUTTON_HIGHT, "7" 	},
	{ 5+BUTTON_SpaceX,     63+BUTTON_SpaceY,  	BUTTON_WHITH, 		BUTTON_HIGHT, "8" 	},
	{ 5+BUTTON_SpaceX*2,   63+BUTTON_SpaceY,  	BUTTON_WHITH, 		BUTTON_HIGHT, "9" 	},
	{ 5+BUTTON_SpaceX*3,   63+BUTTON_SpaceY,  	BUTTON_WHITH, 		BUTTON_HIGHT, "*" 	},
	/* 第3排按钮 */
	{ 5,                   63+BUTTON_SpaceY*2,  BUTTON_WHITH, 		BUTTON_HIGHT, "4" 	},
	{ 5+BUTTON_SpaceX,     63+BUTTON_SpaceY*2,  BUTTON_WHITH, 		BUTTON_HIGHT, "5" 	},
	{ 5+BUTTON_SpaceX*2,   63+BUTTON_SpaceY*2,  BUTTON_WHITH, 		BUTTON_HIGHT, "6" 	},
	{ 5+BUTTON_SpaceX*3,   63+BUTTON_SpaceY*2,  BUTTON_WHITH, 		BUTTON_HIGHT, "-" 	},

	/* 第4排按钮 */
	{ 5,                   63+BUTTON_SpaceY*3,  BUTTON_WHITH,  		BUTTON_HIGHT, "1" 	},
	{ 5+BUTTON_SpaceX,     63+BUTTON_SpaceY*3,  BUTTON_WHITH, 		BUTTON_HIGHT, "2" 	},
	{ 5+BUTTON_SpaceX*2,   63+BUTTON_SpaceY*3,  BUTTON_WHITH, 		BUTTON_HIGHT, "3" 	},
	{ 5+BUTTON_SpaceX*3,   63+BUTTON_SpaceY*3,  BUTTON_WHITH, 		BUTTON_HIGHT, "+" 	},

	/* 第5排按钮 */
	{ 5,                   63+BUTTON_SpaceY*4,  BUTTON_WHITH*2+3, 	BUTTON_HIGHT, "0" 	},
	{ 5+BUTTON_SpaceX*2,   63+BUTTON_SpaceY*4,  BUTTON_WHITH, 		BUTTON_HIGHT, "." 	},
	{ 5+BUTTON_SpaceX*3,   63+BUTTON_SpaceY*4,  BUTTON_WHITH, 		BUTTON_HIGHT, "=" 	}
};
/*
*****************************************************************************************
*                                      变量
*****************************************************************************************
*/ 
extern GUI_FONT    	XBF_Font;
static uint8_t 		s_Key;
static char 		text1[textlength]={0},	text2[textlength]={0};
static double 		data1=0.0,		data2=0.0;
static uint8_t    	offset=0,calculating=0,floaton=0,floatoffset=0;
static char cal=0;
//static int calinteger=0;
//static double d=0;
/***************************************************************************/
char* str(char *string)
{
	uint8_t i=0;
	while(string[i]!='\0')i++;
	do
	{
		string[i]='\0';
		i--;
	}
	while(string[i]==48 && i>0);
	if(string[i]=='.')string[i]='\0';
	return string;
}

void num(double data,char st[20])
{
	char text[40]={0},*string={0};
	uint8_t i=0;
	sprintf(text,"%.12f",data);
	//printf("text=%s\n",text);
	string=str(text);
	string[19]='\0';
	//printf("string=%s\n",string);
	for(i=0;i<20;i++)
	{
		st[i]=string[i];
	}
}

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreateCal[] = {
  { FRAMEWIN_CreateIndirect, "Calculator",0, 0, 0, 240, 320, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "calculator", GUI_ID_TEXT0, 7, 5, 218, 25, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "input", GUI_ID_TEXT1, 7, 5, 218, 50, 0, 0x64, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};
/*
**************************************************************************************
*	函 数 名: _cbKeyPad
*	功能说明: 回调函数
*	形    参：pMsg  指针参数
*	返 回 值: 无
**************************************************************************************
*/
static void _cbDialogCal(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	WM_HWIN    hButton;
	int        Id;
	int        NCode;
	uint8_t    xSize=0;
	uint16_t   ySize=0;
	uint8_t    i=0;
	hItem = pMsg->hWin;
	switch (pMsg->MsgId) 
	{
		case WM_DELETE:
		OS_INFO("Calculatorapp delete\n");
		Flag_ICON109 = 0;
		s_Key=0;
		text1[0]='\0';
		text2[0]='\0';
		data1=0.0;
		data2=0.0;
		offset=0;
		calculating=0;
		floaton=0;
		floatoffset=0;
		UserApp_Flag = 0;
		tpad_flag=0;
		break;
		case WM_INIT_DIALOG:
			//
			// Initialization of 'Calculator'
			//
			FRAMEWIN_SetFont(hItem, GUI_FONT_16B_ASCII);
			FRAMEWIN_SetTitleHeight(hItem, 20);
			FRAMEWIN_SetTextColor(hItem,GUI_DARKGRAY);
			FRAMEWIN_AddCloseButton(hItem,FRAMEWIN_BUTTON_RIGHT,0);
			//
			// Initialization of 'calculator'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
			TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
			TEXT_SetText(hItem, "");
			WM_BringToTop(hItem);
			TEXT_SetBkColor(hItem,GUI_WHITE);
			//
			// Initialization of 'input'
			//
			hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1);
			TEXT_SetFont(hItem, GUI_FONT_24B_ASCII);
			TEXT_SetTextColor(hItem, GUI_BLACK);
			TEXT_SetText(hItem, "0");
			TEXT_SetBkColor(hItem,GUI_WHITE);
			TEXT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_BOTTOM);
			// USER START (Optionally insert additional code for further widget initialization)
			/* 创建所需的按钮 */
			for (i = 0; i < GUI_COUNTOF(ButtonData); i++) 
			{
				hButton = BUTTON_CreateEx(ButtonData[i].xPos, ButtonData[i].yPos, ButtonData[i].xSize, ButtonData[i].ySize, 
				WM_GetClientWindow(pMsg->hWin), WM_CF_SHOW, 0, ID_BUTTON + i);
				BUTTON_SetFont(hButton, &GUI_Font24B_ASCII);
				BUTTON_SetText(hButton, ButtonData[i].acLabel);
				BUTTON_SetTextAlign(hButton,GUI_TA_HCENTER|GUI_TA_VCENTER);
				//BUTTON_SetFocussable(hButton, 0);
			}
			WM_SetFocus(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1));
			// USER END
			break;
		/* 绘制背景 */	
		case WM_PAINT:	
			xSize = WM_GetWindowSizeX(hItem);
			ySize = WM_GetWindowSizeY(hItem);
			GUI_SetColor(COLOR_BORDER);
			GUI_DrawRect(0, 0, xSize - 1, ySize - 1);
			GUI_DrawGradientV(1, 1, xSize - 2, ySize - 2, COLOR_KEYPAD0, COLOR_KEYPAD1);
			break;
		
		/* 用于处理按钮的消息 */
		case WM_NOTIFY_PARENT:
			Id    = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			if(Id==GUI_ID_TEXT0||Id==GUI_ID_TEXT1)break;
			switch (NCode) 
			{
				case WM_NOTIFICATION_CLICKED:
					// USER START (Optionally insert code for reacting on notification message)
					LED1_ON;
				#ifdef USERBEEP
					macBEEP_ON();
				#endif
					// USER END
				break;
				case WM_NOTIFICATION_RELEASED:
					LED1_OFF;
				#ifdef USERBEEP
					macBEEP_OFF();
				#endif
					if (ButtonData[Id - ID_BUTTON].acLabel)
					{
						if(Id == (ID_BUTTON+0))//"C"
						{
							offset=0;
							floaton=0;
							floatoffset=0;
							data2=0;
							text2[0]='0';
							text2[1]='\0';
							TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1),text2);
							if(calculating==0)
							{
								data1=0;
								text1[0]='\0';
								TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0),text1);
							}
							/* 功能键处理完要退出 */
							break;
						}
						if(Id == (ID_BUTTON+1))//"+/-"
						{							
							data2=-data2;	
							num(data2,text2);						
							TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1),text2);
							/* 功能键处理完要退出 */
							break;
						}
						if(Id == (ID_BUTTON+2))//"1/x"
						{
							calculating=0;
							offset=0;
							data1=data2;
							data2=1/data2;
							num(data2,text2);
							TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1),text2);
							
							num(data1,text1);
							TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0),text1);
							/* 功能键处理完要退出 */
							break;
						}
						if(Id == (ID_BUTTON+3))//"/"
						{
							calculating=1;
							floaton=0;
							data1=data2;
							text2[0]='\0';
							cal='/';
							num(data1,text1);
							sprintf(text1,"%s%s",text1,"/");
							TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0),text1);
							/* 功能键处理完要退出 */
							break;
						}
						if(Id == (ID_BUTTON+7))//"*"
						{
							calculating=1;
							floaton=0;
							data1=data2;
							text2[0]='\0';
							cal='*';
							num(data1,text1);
							sprintf(text1,"%s%s",text1,"*");
							TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0),text1);
							/* 功能键处理完要退出 */
							break;
						}
						if(Id == (ID_BUTTON+11))//"-"
						{
							calculating=1;
							floaton=0;
							data1=data2;
							text2[0]='\0';
							cal='-';
							num(data1,text1);
							sprintf(text1,"%s%s",text1,"-");
							TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0),text1);
							/* 功能键处理完要退出 */
							break;
						}
						if(Id == (ID_BUTTON+15))//"+"
						{
							calculating=1;
							floaton=0;
							data1=data2;
							text2[0]='\0';
							cal='+';
							num(data1,text1);
							sprintf(text1,"%s%s",text1,"+");
							TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0),text1);
							/* 功能键处理完要退出 */
							break;
						}
						if(Id == (ID_BUTTON+18))//"="
						{
							calculating=0;
							floatoffset=0;
							offset=0;
							floaton=0;
							switch(cal)
							{
								case '+':
									data2=data1+data2;
									break;
								case '-':
									data2=data1-data2;
									break;
								case '*':
									data2=data1*data2;
									break;
								case '/':
									data2=data1/data2;
									break;
								default:break;
							}
							num(data2,text2);						
							TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1),text2);
							text1[0]='\0';
							TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0),text1);
							/* 功能键处理完要退出 */
							break;
						}
						s_Key = ButtonData[Id - ID_BUTTON].acLabel[0];
						if(s_Key=='.')
						{
							if(floaton)break;
							if(offset==0)
							{
								offset=2;
								text2[0]='0';
								text2[1]='.';
								text2[2]='\0';
							}
							else
							{
								offset++;
								sprintf(text2,"%s%s",text2,".");
							}
							text2[19]='\0';//防止超出范围
							TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1),text2);
							floaton=1;
							break;
						}
						if((s_Key>='0')&&(s_Key<='9'))
						{
							if(s_Key=='0' && data2==0 && offset==0)break;		//最开始状态，按‘0’无效					
							if(offset==0)
								sprintf(text2,"%d",s_Key-48);
							else
								sprintf(text2,"%s%d",text2,s_Key-48);
							offset++;
							if(floaton)
							{
								floatoffset++;
							}
							data2=atof(text2);
							text2[19]='\0';//防止超出范围
							TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1),text2);
							break;
						}
					}
					break;
			}
			break;
	}
}
/*
*********************************************************************************************************
*	函 数 名: MainAPP
*	功能说明: GUI主函数 
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void FUN_ICON109Clicked(void)
{
	WM_HWIN hWin;
	OS_INFO("Calculatorapp create\n");
	hWin=GUI_CreateDialogBox(_aDialogCreateCal, GUI_COUNTOF(_aDialogCreateCal), _cbDialogCal, WM_HBKWIN, 0, 0);
	
	while(Flag_ICON109)
	{
		if(tpad_flag)WM_DeleteWindow(hWin);
		GUI_Delay(10);
	}
}