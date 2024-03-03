#ifndef _REMOTEARMS_H_
#define _REMOTEARMS_H_
#include"POINT.h"
class Dart
{
public:
Point CenterPoint;
int MoveSpeed;
int Hurt;
int MP_Needed;
Dart(double xx,double yy);
void DartIn(int di);
void DartOut(int di);
void DartChange(double xx,double yy);
void DartSet(double xx,double yy);
double GetDartX();
double GetDartY();
};
Dart::Dart(double xx,double yy):CenterPoint(xx,yy)
{MoveSpeed=100;Hurt=10;MP_Needed=5;}
void Dart::DartIn(int di)
{line(CenterPoint.x-12*di,CenterPoint.y,CenterPoint.x+12*di,CenterPoint.y);
int pts[] = {CenterPoint.x+12*di,CenterPoint.y,CenterPoint.x+22*di,CenterPoint.y-9,CenterPoint.x+42*di,CenterPoint.y,CenterPoint.x+22*di,CenterPoint.y+9};
solidpolygon((POINT*)pts,4);
circle(CenterPoint.x-17*di,CenterPoint.y,5);
}
void Dart::DartOut(int di)
{DartIn(di);}
void Dart::DartChange(double xx,double yy)
{CenterPoint.x+=xx;CenterPoint.y+=yy;}
double Dart::GetDartX()
{return CenterPoint.x+42;}
double Dart::GetDartY()
{return CenterPoint.y;}
void Dart::DartSet(double xx,double yy)
{CenterPoint.x=xx;CenterPoint.y=yy;}
#endif
