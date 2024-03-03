#ifndef _BODY_H_
#define _BODY_H_
#include"POINT.h"
class Body
{public:
Point *p1;
Point *p2;
Body(Point &a1,Point &a2)
{p1=&a1;p2=&a2;}
void BodyIn();
void BodyOut();
};
void Body::BodyIn()
{line(p1->x,p1->y,p2->x,p2->y);}
void Body::BodyOut()
{line(p1->x,p1->y,p2->x,p2->y);}
#endif