#include<conio.h>
#include<graphics.h>
#include"PLAYERS.h"
#include"OBJECT.h"
void UI()
{
	initgraph(1333, 700);				// ���ڳ�ʼ����С
	IMAGE img;
	loadimage(&img, _T("����˱���.jpg"), 1333, 700);
	putimage(0, 0, &img);
	setlinecolor(BLACK);				// ���û�ͼ��ɫ
	settextcolor(BLACK);				// ����������ɫ
	setfillcolor(HSVtoRGB(96,96,96));			// ���������ɫ
	settextstyle(25, 0, _T("����"));	// ������ʽ��С
	setlinestyle(PS_SOLID,5,PS_ENDCAP_ROUND);
}
void main()
{
	Object Mode1;
	UI();					// �����ʼ��
	Mode1.Login();				// ��¼����
    getch();
}



