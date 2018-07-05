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
#include  "includes.h"
#include  "app.h"
#include  "..\User\bsp\lcd\bsp_ili9341_lcd.h"
#include  "..\User\bsp\ESP8266\bsp_esp8266.h"
// USER END

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
extern uint8_t Ov7725_vsync;
// USER END

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
void cbCameraWin(WM_MESSAGE * pMsg)
{
	switch (pMsg->MsgId) 
	{
	  case WM_DELETE:
			OS_INFO("Cameraapp delete\n");
			DisableCamera();
			Flag_ICON108=0;
			UserApp_Flag = 0;		
			ILI9341_GramScan(1);
			tpad_flag=0;
			break;
		case WM_PAINT:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			GUI_DispStringHCenterAt("camera init fail",110,110);
			break;
	}
}
/*********************************************************************
*
*       CreateCamera
*/
void FUN_ICON108Clicked(void)
{
	WM_HWIN hWin;
	OS_ERR     err;
	uint32_t i=0;
	uint16_t Camera_Data;
	uint8_t count=0;
	
	ESP8266_stop();
	
	OS_INFO("Cameraapp create\n");
	hWin=WM_CreateWindowAsChild(0,0,240,320,WM_HBKWIN,WM_CF_SHOW,cbCameraWin,0);
	GUI_Delay(100);
	
	/* ov7725 gpio 初始化 */
	Ov7725_GPIO_Config();
	/* ov7725 寄存器配置初始化 */
	while(count<10)
	{		
		if(Ov7725_Init())break;
		bsp_DelayUS(1000);
		count++;
	}
	while(count==10)
	{		
		WM_InvalidateWindow(hWin);
		GUI_ExecCreatedDialog(MESSAGEBOX_Create("\r\n The Camera drive cannot work! \r\n","error",GUI_MESSAGEBOX_CF_MODAL));
		while(1)
		{
			WM_DeleteWindow(hWin);
			if(!Flag_ICON108)return;
			GUI_Delay(10);
		}
	}
	
	/* ov7725 场信号线初始化 */
	VSYNC_Init();
	Ov7725_vsync = 0;
	ILI9341_GramScan(2);
	bsp_DelayUS(10);
	while(Flag_ICON108)
	{
		if( Ov7725_vsync == 2 )
		{			
			OSSchedLock(&err);			
			FIFO_PREPARE;  			/*FIFO准备*/
			/*采集并显示*/
			for(i = 0; i < 240*320; i++)
			{
				READ_FIFO_PIXEL(Camera_Data);		/* 从FIFO读出一个rgb565像素到Camera_Data变量 */
				macFSMC_ILI9341_RAM=Camera_Data;
			}
			OSSchedUnlock(&err);
			Ov7725_vsync = 0;						
		}
		if(tpad_flag)WM_DeleteWindow(hWin);
		GUI_Delay(1);//WM_Exec();//
	}
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
