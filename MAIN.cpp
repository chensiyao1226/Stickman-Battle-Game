#include<conio.h>
#include<graphics.h>
#include"PLAYERS.h"
#include"OBJECT.h"
void UI()
{
	initgraph(1333, 700);				// 窗口初始化大小
	IMAGE img;
	loadimage(&img, _T("火柴人背景.jpg"), 1333, 700);
	putimage(0, 0, &img);
	setlinecolor(BLACK);				// 设置绘图颜色
	settextcolor(BLACK);				// 设置文字颜色
	setfillcolor(HSVtoRGB(96,96,96));			// 设置填充颜色
	settextstyle(25, 0, _T("宋体"));	// 字体样式大小
	setlinestyle(PS_SOLID,5,PS_ENDCAP_ROUND);
}
void main()
{
	Object Mode1;
	UI();					// 界面初始化
	Mode1.Login();				// 登录界面
    getch();
}



