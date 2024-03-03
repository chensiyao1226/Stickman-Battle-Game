#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include"POINT.h"
#include<conio.h>
#include<graphics.h>
class Background
{public:
Background();
void BackgroundIn();
};
Background::Background()
{}
void Background::BackgroundIn()
{





/*setfillcolor(HSVtoRGB(0,0,0.55));
solidcircle(820,220,190);
/*solidellipse(1100,130,1333,210);////
solidrectangle(0,0,100,240);
solidrectangle(100,15,200,240);
solidrectangle(200,50,340,240);
solidrectangle(340,65,540,240);
solidrectangle(540,145,750,240);
solidrectangle(1100,145,1150,240);
solidrectangle(1150,120,1250,240);
solidrectangle(1250,100,1300,240);
solidrectangle(1300,50,1333,240);*/
/*setfillcolor(DARKGRAY);
fillrectangle(30,80,167,240);
fillrectangle(65,65,135,80);
int pts[]={350,240,350,65,470,65,500,95,500,240};
fillpolygon((POINT*)pts,5);
pts[0]=680;pts[1]=240;pts[2]=680;pts[3]=40;pts[4]=720;pts[5]=40;pts[6]=730;pts[7]=50;pts[8]=730;pts[9]=240;
fillpolygon((POINT*)pts,5);
pts[0]=800;pts[1]=240;pts[2]=800;pts[3]=60;pts[4]=860;pts[5]=60;pts[6]=870;pts[7]=68;pts[8]=870;pts[9]=240;
fillpolygon((POINT*)pts,5);
pts[0]=900;pts[1]=240;pts[2]=900;pts[3]=10;pts[4]=950;pts[5]=10;pts[6]=960;pts[7]=80;pts[8]=960;pts[9]=240;
fillpolygon((POINT*)pts,5);
int pts1[]={1000,240,1000,65,1080,65,1080,70,1120,70,1120,40,1150,25,1200,25,1230,40,1230,120,1340,120,1340,240};
fillpolygon((POINT*)pts1,12);
line(100,65,100,25);
for(int i=0;i<=12;i++)
{line(40+10*i,200,40+10*i,90);}
for(int i=0;i<=3;i++)
{line(360,75+8*i,460,75+8*i);}
for(int i=0;i<=3;i++)
{line(360,110+8*i,460,110+8*i);}
for(int i=0;i<=3;i++)
{line(360,145+8*i,460,145+8*i);}
for(int i=0;i<=3;i++)
{line(360,180+8*i,460,180+8*i);}
setlinestyle(PS_SOLID,4,PS_ENDCAP_ROUND);
for(int i=0;i<=17;i++)
{
	for(int j=0;j<=2;j++)
    line(690+8.4*j,50+10*i,690+8.4*j+3.8,50+10*i);
}
setlinestyle(PS_SOLID|PS_ENDCAP_SQUARE,10);
for(int i=0;i<=2;i++)
{line(818+i*15,235,818+15*i,75);}
setlinestyle(PS_SOLID|PS_ENDCAP_SQUARE,6);
for(int i=0;i<=17;i++)
{
	for(int j=0;j<=2;j++)
    line(912+12*j,20+10*i,912+12*j+3.8,20+10*i);
}
for(int i=0;i<=14;i++)
	line(1010,80+10*i,1072,80+10*i);
for(int i=0;i<=17;i++)
{
	for(int j=0;j<=7;j++)
    line(1132+12*j,48+10*i,1132+12*j+3.8,48+10*i);
}
setlinestyle(PS_SOLID,4,PS_ENDCAP_ROUND);
fillrectangle(0,140,80,240);
fillrectangle(110,110,245,240);
fillrectangle(385,125,535,240);
fillrectangle(720,90,760,240);
fillrectangle(925,120,975,240);
setlinestyle(PS_SOLID|PS_ENDCAP_SQUARE,5);
for(int i=0;i<=13;i++)
{	for(int j=0;j<=3;j++)
	line(118+9*i,125+30*j,118+9*i,145+30*j);
}
/*solidrectangle(50,100,120,240);
solidrectangle(120,200,140,240);
solidrectangle(140,80,240,240);///////
solidrectangle(240,240,260,240);
solidrectangle(260,110,330,240);
solidrectangle(330,220,400,240);
solidrectangle(400,40,540,240);
solidrectangle(540,10,560,240);
solidrectangle(560,200,640,240);
solidrectangle(640,15,680,240);
solidrectangle(680,220,820,240);//////////////////////////
solidrectangle(820,50,950,240);
solidrectangle(950,240,1000,240);//////////////
solidrectangle(1000,20,1100,240);
solidrectangle(1100,160,1333,240);
solidcircle(190,80,50);
solidrectangle(950,80,1000,100);
solidrectangle(850,15,920,50);
int pts[]={260,112,295,20,330,112};
solidpolygon((POINT*)pts,3);*/
setfillcolor(WHITE);}
#endif