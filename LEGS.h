#ifndef _LEGS_H_
#define _LEGS_H_
#include"POINT.h"
#include<math.h>
#define PI 3.1415926
class Legs
{public:
Point *p;
double angle1,angle2;
double length;
Legs(Point &p1,double ang1,double ang2):length(33)
{p=&p1;angle1=ang1;angle2=ang2;}
void LegsIn();
void LegsOut();
void LegsChange(double ang1,double ang2);
void LegsSet(double ang1,double ang2);
double GetFootX();
double GetFootY();
double GetLegX();
double GetLegY();
};
void Legs::LegsIn()
{line(p->x,p->y,p->x+cos(angle1*(PI/180))*length,p->y+sin(angle1*(PI/180))*length);
line(p->x+cos(angle1*(PI/180))*length,p->y+sin(angle1*(PI/180))*length,p->x+cos(angle1*(PI/180))*length+cos(angle2*(PI/180))*33,p->y+sin(angle1*(PI/180))*length+sin(angle2*(PI/180))*33);
solidellipse(GetFootX()-10,GetFootY()+3.5,GetFootX()+10,GetFootY()-3.5);
}
void Legs::LegsOut()
{LegsIn();}
void Legs::LegsChange(double ang1,double ang2)
{angle1+=ang1;
angle2+=ang2;}
void Legs::LegsSet(double ang1,double ang2)
{angle1=ang1;angle2=ang2;}
double Legs::GetFootX()
{return p->x+cos(angle1*(PI/180))*length+cos(angle2*(PI/180))*33;}
double Legs::GetFootY()
{return p->y+sin(angle1*(PI/180))*length+sin(angle2*(PI/180))*33;}
double Legs::GetLegX()
{return (p->x+cos(angle1*(PI/180))*length+p->x+cos(angle1*(PI/180))*length+cos(angle2*(PI/180))*33)/2;}
double Legs::GetLegY()
{return (p->y+sin(angle1*(PI/180))*length+p->y+sin(angle1*(PI/180))*length+sin(angle2*(PI/180))*33)/2;}
#endif
