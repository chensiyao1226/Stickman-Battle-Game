#ifndef _ARMS_H_
#define _ARMS_H_
#include"POINT.h"
#include<math.h>
#define PI 3.1415926
class Arms
{public:
Point *p;
double angle1,angle2;
double length;
Arms(Point &p1,double ang1,double ang2):length(43)
{p=&p1;angle1=ang1;angle2=ang2;}
void ArmsIn();
void ArmsOut();
void ArmsChange(double ang1,double ang2);
void ArmsSet(double ang1,double ang2);
float GetHandX(){return p->x+(int)(cos(angle1*PI/180)*length)+(int)(cos(angle2*PI/180)*33);}       //补充  获取手的位置x
float GetHandY(){return p->y+(int)(sin(angle1*PI/180)*length)+(int)(sin(angle2*PI/180)*33);}     //补充  获取手的位置y
double GetArmX(){return (p->x+cos(angle1*(PI/180))*length+p->x+(int)(cos(angle1*PI/180)*length)+(int)(cos(angle2*PI/180)*33))/2;}
double GetArmY(){return (p->y+sin(angle1*(PI/180))*length+p->y+(int)(sin(angle1*PI/180)*length)+(int)(sin(angle2*PI/180)*33))/2;}
};
void Arms::ArmsIn()
{line(p->x,p->y,p->x+cos(angle1*(PI/180))*length,p->y+sin(angle1*(PI/180))*length);
line(p->x+cos(angle1*(PI/180))*length,p->y+sin(angle1*(PI/180))*length,GetHandX(),GetHandY());
solidcircle(GetHandX(),GetHandY(),7.5);
}
void Arms::ArmsOut()
{ArmsIn();}
void Arms::ArmsChange(double ang1,double ang2)
{angle1+=ang1;
angle2+=ang2;}
void Arms::ArmsSet(double ang1,double ang2)
{angle1=ang1;
angle2=ang2;}
#endif