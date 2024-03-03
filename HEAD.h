#ifndef _HEAD_H_
#define _HEAD_H_
#include"POINT.h"
class Head
{public:
Point *p;
double r;
Head(Point &p1,double rr)
{p=&p1;
r=rr;}
void HeadIn();
void HeadOut();
};
void Head::HeadIn()
{fillcircle(p->x,p->y-r,r);}
void Head::HeadOut()
{fillcircle(p->x,p->y-r,r);}
#endif