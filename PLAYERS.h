#ifndef _PLAYERS_H_
#define _PLAYERS_H_
#include"ARMS.h"
#include"BODY.h"
#include"HEAD.h"
#include"LEGS.h"
#include"REMOTEARMS.h"
#include"POINT.h"
#include<math.h>
struct Command
{int Kick;
int Hit;
int MoveLeft;
int MoveRight;
int Jump;
int Squat;
int RemoteAttack;
};
struct GetAttacked
{int Stumble;//后退
int GetKnockedDown;//小飞
int GetKickedFlew;//大飞
int ComeToSky;//上天；
int AlmostDie;//被大招击中；
int DoubleHurt;//被双踢；
int DefendSucceed;//成功的防御；
};
class Players
{friend class Object;
private:
	static float sum;
	Point p1,p2,p3;
	Head PlayerHead;
	Body PlayerBody;
	double PlayersBlood;
	double PlayersMagicPoint;
	Arms LeftArm;
	Legs RightLeg;
	Arms RightArm;
	Legs LeftLeg;
	Dart *MyDart;
	Command cmd;
	GetAttacked atk; 
	int ActionSpeed;
	int MoveSpeed;
	public:
	int direction;
	Players();
	Players(int i);
	void PlayersDirection(int di);
	void PlayersIn();
	void PlayersOut();
	void PlayersMove(int i);
	void PlayersHit(int i);
	void PlayersThump(int i);
	void PlayersKick(int i);
	void PlayersDoubleKick(int i);
	void PlayersFlyKick(int i);
	void PlayersTrample(int i);
	void PlayersFirePunch(int i);
	void PlayersJump(int i);
	void PlayersSquat(int i);
	void PlayersRay(int i);
    void PlayersDart(int i);
	void PlayersChange(int *i,int *k);
	void PlayersStumble(int i,int di);
	void PlayersGetKnockedDown(int i,int di);
	void PlayersGetKickedFlew(int i,int di);
	void PlayersComeToSky(int i,int di);
	void PlayersAlmostDie(int i,int di);
	void PlayersGetDoubleHurt(int i,int di);
	void PlayersDefendSucceed(int i);
	void PlayersGetHurt(int *i);
	void PlayersDrawStatus(int x);
	void PlayersAngleReset(int i);
	void PlayersHightReset(int i);
	void PlayersBodyReset(int i);
	void PlayersAttackReset();
	void PlayersCommandReset();
	void PlayersAllReset(int i,int di);
	
};
float Players::sum = 0;
Players::Players():p1(520,461),p2(520,526),p3(520,476),LeftLeg(p2,100,95),RightLeg(p2,75,85),PlayerHead(p1,15),PlayerBody(p1,p2),RightArm(p3,80,73),LeftArm(p3,100,74), direction(1)
{PlayersBlood=100;
PlayersMagicPoint=100;
sum+=1;
PlayersCommandReset();
PlayersAttackReset();
MyDart=NULL;
ActionSpeed=0;MoveSpeed=0;}
Players::Players(int i):p1(800,461),p2(800,526),p3(800,476),LeftLeg(p2,80,85),RightLeg(p2,105,95),PlayerHead(p1,15),PlayerBody(p1,p2),RightArm(p3,100,107),LeftArm(p3,80,106),direction(-1)
{PlayersBlood=100;
PlayersMagicPoint=100;
PlayersCommandReset();
PlayersAttackReset();
sum+=1;
MyDart=NULL;
ActionSpeed=0;MoveSpeed=0;}
void Players::PlayersDirection(int di)
{
	direction = di;
}
void Players::PlayersIn()//PlayersIn函数（刷新相关）；
{
	
	RightArm.ArmsIn();
	LeftArm.ArmsIn();
	RightLeg.LegsIn();
	LeftLeg.LegsIn();
	PlayerHead.HeadIn();
	PlayerBody.BodyIn();
	
}
void Players::PlayersOut()//PlayersOut函数（刷新相关）；
{PlayersIn();}
void Players::PlayersMove(int i)//PlayersMove函数（行走的实现）；
{
	if(direction == 1)
	{
		p1.x+=i/2;
		p2.x+=i/2;
		p3.x+=i/2;
		if(LeftArm.angle1==75)//RightArm(p3,80,73),LeftArm(p3,100,74)
		{
			LeftArm.angle1 = 100;	
			LeftArm.angle2 = 74;
			RightArm.angle1 = 80;
			RightArm.angle2 = 73;
		}
		if(LeftLeg.angle1==70)//LeftLeg(p2,100, 95),RightLeg(p2,75, 85)
		{
			LeftLeg.angle1 = 100;
			LeftLeg.angle2 = 105;
			RightLeg.angle1 = 75;
			RightLeg.angle2 = 70;
        }
	LeftArm.ArmsChange(-5, -5);
	RightArm.ArmsChange(5, 5);
	LeftLeg.LegsChange(-5, -4);
	RightLeg.LegsChange(5, 6);
	}
	else
		{
		p1.x+=i/2;
		p2.x+=i/2;
		p3.x+=i/2;
		if(LeftArm.angle1==105)
		{
			LeftArm.angle1 = 75;	
			LeftArm.angle2 = 100;
			RightArm.angle1 = 105;
			RightArm.angle2 = 125;
		}
		if(LeftLeg.angle1==110)
		{
			LeftLeg.angle1 = 80;
			LeftLeg.angle2 = 75;
			RightLeg.angle1 = 105;
			RightLeg.angle2 = 110;
        }
		LeftArm.ArmsChange(5,5);
	    RightArm.ArmsChange(-5,-5);
	    LeftLeg.LegsChange(5,4);
	    RightLeg.LegsChange(-5,-6);
	}

}
void Players::PlayersHit(int i)//PlayersHit函数（普通攻击的实现）；
{
if(i<4)
{if(i==0)
ActionSpeed=40;
RightArm.ArmsChange(direction*17.5,0);}
if(i==4)
{RightArm.ArmsChange(direction*(-150),direction*(-73));
LeftArm.ArmsChange(direction*30,0);
LeftLeg.LegsChange(40*direction,25*direction);
RightLeg.LegsChange((-40)*direction,7*direction);
p2.y+=15;p2.x+=27*direction;
p1.x=p2.x+65*cos(80*(PI/180))*direction;
p1.y=p2.y-65*sin(80*(PI/180));
p3.x=p2.x+50*cos(80*(PI/180))*direction;
p3.y=p2.y-50*sin(80*(PI/180));
}
if(i>4&&i<13)
{
if(i==12)
ActionSpeed=0;
}
}
void Players::PlayersKick(int i)//PlayersKick函数（踢腿的实现）；
{if(i>=0&&i<5)
{if(i==0)
ActionSpeed=55;
RightLeg.LegsChange(3*direction,direction);
LeftLeg.LegsChange(5*direction,0);
RightArm.ArmsChange(10*direction,(-10)*direction);
LeftArm.ArmsChange(10*direction,(-10)*direction);
p1.y-=0.2;p2.y-=0.2;p3.y-=0.2;
p1.x+=2.32*direction;p2.x+=2.32*direction;p3.x+=2.32*direction;}
if(i>=5&&i<8)
{LeftLeg.LegsChange((-51)*direction,(-41)*direction);
LeftArm.ArmsChange((-15)*direction,(15)*direction);
RightArm.ArmsChange((-45)*direction,(30)*direction);
RightArm.length-=3;
p1.y+=1.3;p1.x-=7.3*direction;
p3.y+=1;p3.x-=5.6*direction;}
if(i>=8&&i<13)
{if(i==12)
{RightArm.length+=9;ActionSpeed=0;}
}
}
void Players::PlayersTrample(int i)//PlayersTrample函数（暴踢）；
{if(i>=0&&i<7)
{if(i==0)
{ActionSpeed=95;
MoveSpeed=25;
}
p1.y+=1.4;p2.y+=1.4;p3.y+=1.4;
p1.x+=2.6*direction;p2.x+=2.6*direction;p3.x+=2.6*direction;
RightArm.ArmsChange((-6)*direction,0);
LeftLeg.LegsChange(5*direction,0);
RightLeg.LegsChange((-5)*direction,0);
}
if(i>=7&&i<17)
{p2.x+=2.5*direction;p2.y-=1;
p1.x=p2.x-65*sin(30*(PI/180))*direction;
p1.y=p2.y-65*cos(30*(PI/180));
p3.x=p2.x-50*sin(30*(PI/180))*direction;
p3.x=p2.x-50*sin(30*(PI/180))*direction;
RightArm.ArmsChange(8*direction,0);
LeftArm.ArmsChange(6*direction,0);
LeftLeg.LegsChange((-18)*direction,0);}
if(i==17)
{p2.x+=26*direction;p2.y-=5;
p1.x=p2.x-65*sin(30*(PI/180))*direction;
p1.y=p2.y-65*cos(30*(PI/180));
p3.x=p2.x-50*sin(30*(PI/180))*direction;
p3.x=p2.x-50*sin(30*(PI/180))*direction;
RightLeg.LegsChange(45*direction,5*direction);}
if(i==18)
{p2.x+=2*direction;p2.y-=2;p3.x+=25*direction;p3.y-=6.5;
p1.x+=35*direction;p1.y-=8.5;
LeftLeg.LegsChange(0,(-137)*direction);
RightLeg.LegsChange((2)*direction,0);}
if(i>=18&&i<28)
{
if(i==27)
{ActionSpeed=0;MoveSpeed=0;PlayersMagicPoint-=10;}
}
}
void Players::PlayersDoubleKick(int i)//DoubleKick函数（双踢的实现）；
{if(i>=0&&i<5)
{if(i==0)
{ActionSpeed=160;
MoveSpeed=45;}
p1.y+=2;p2.y+=2;p3.y+=2;
p1.x+=5*direction;p2.x+=5*direction;p3.x+=5*direction;
p1.y-=10;p2.y-=10;p3.y-=10;
LeftLeg.LegsChange(7*direction,0);
RightLeg.LegsChange((-6)*direction,0);
LeftArm.ArmsChange(7*direction,3*direction);
RightArm.ArmsChange((-7)*direction,0);
LeftLeg.LegsChange((-5)*direction,0);
RightLeg.LegsChange(5*direction,0);
LeftArm.ArmsChange((-4)*direction,0);
RightArm.ArmsChange(4*direction,2*direction);
p1.x+=3*direction;p2.x+=3*direction;p3.x+=3*direction;
p1.y-=4;p2.y-=4;p3.y-=4;
LeftLeg.LegsChange(10*direction,0);
RightLeg.LegsChange((-10)*direction,0);
LeftArm.ArmsChange(5*direction,0);
RightArm.ArmsChange((-5)*direction,0);}
if(i==5)
{p1.x+=25*direction;p1.y-=15;p2.x+=25*direction;p2.y-=15;p3.x+=25*direction;p3.y-=15;
LeftLeg.LegsChange((-40)*direction,0);
RightLeg.LegsChange((-40)*direction,(-105)*direction);
RightArm.ArmsChange(75*direction,15*direction);}
if(i>=6&&i<16)
{p1.x+=1.5*direction;p2.x+=1.5*direction;p3.x+=1.5*direction;
p1.y-=6;p2.y-=6;p3.y-=6;
p3.x-=3.5*direction;p3.y+=1.5;p1.x-=4.6*direction;p1.y+=1.9;
RightLeg.LegsChange(13*direction,10*direction);
LeftLeg.LegsChange((-13)*direction,(-5)*direction);
RightArm.ArmsChange((-18)*direction,-(15)*direction);LeftArm.ArmsChange(5*direction,8*direction);}
if(i>=16&&i<21)
{RightArm.ArmsChange(0,(-13)*direction);
LeftArm.ArmsChange(0,13*direction);
RightLeg.LegsChange(-4*direction,0);
LeftLeg.LegsChange((7)*direction,0);}
if(i>=21&&i<26)
{p1.x+=20*direction;p1.y+=28;p2.x+=20*direction;p2.y+=28;p3.x+=20*direction;p3.y+=28;
LeftLeg.LegsChange(2*direction,0);
RightLeg.LegsChange((-2)*direction,(-4)*direction);}
if(i>=26&&i<31)
{p2.x+=6*direction;p2.y-=1;
p1.x+=15*direction;p1.y-=6;p3.x+=13*direction;p3.y-=5;
LeftLeg.LegsChange(7*direction,8*direction);
RightLeg.LegsChange(13*direction,4*direction);
RightArm.ArmsChange(10*direction,0);}
if(i>=31&&i<36)
{p1.y+=2.5;p2.y+=2.5;p3.y+=2.5;
LeftLeg.LegsChange(-5*direction,0);
RightLeg.LegsChange(5*direction,4*direction);
RightArm.ArmsChange(0,(8)*direction);
}
if(i>=36&&i<40)
{p1.y-=5;p2.y-=5;p3.y-=5;
RightArm.ArmsChange(20*direction,23*direction);
LeftArm.ArmsChange((-20)*direction,(-24)*direction);
RightLeg.LegsChange(-10*direction,0);
LeftLeg.LegsChange(10*direction,0);
if(i==39)
{PlayersMagicPoint-=20;ActionSpeed=0;MoveSpeed=0;}
}
}
void Players::PlayersFlyKick(int i)//PlayersFlyKick函数(飞踢的实现)；
{if(i>=0&&i<10)
{if(i==0)
{ActionSpeed=190;MoveSpeed=100;}
p1.y+=1.9;p2.y+=1.9;p3.y+=1.9;
RightLeg.LegsChange((-4.5)*direction,(-2.5)*direction);
LeftLeg.LegsChange(5*direction,2.5*direction);}
if(i>=10&&i<15)
{p1.y-=12;p2.y-=12;p3.y-=12;
p1.x+=20*direction;p2.x=p1.x;p3.x=p1.x;
p1.x-=direction*6.6;p1.y+=1.8;p3.x-=direction*5;p3.y+=1.4;
LeftLeg.LegsChange(0,4*direction);
RightLeg.LegsChange(3*direction,6*direction);
LeftArm.ArmsChange(10*direction,0);
RightArm.ArmsChange((-14)*direction,0);
RightLeg.LegsChange((-8)*direction,0);
LeftLeg.LegsChange((-8)*direction,(-10)*direction);}
if(i==15)
{RightArm.ArmsChange(90*direction,0);
RightLeg.LegsChange((-30)*direction,-(115)*direction);}
if(i>=16&&i<20)
{p1.x+=50*direction;p1.y-=6;p2.x+=50*direction;p2.y-=6;p3.x+=50*direction;p3.y-=6;}
if(i>=20&&i<30)
{p1.x+=(50-i)*direction;p1.y+=(i-17);p2.x+=(50-i)*direction;p2.y+=(i-17);p3.x+=(50-i)*direction;p3.y+=(i-17);
p1.x+=direction*3.3;p1.y-=0.9;p3.x+=direction*2.5;p3.y-=0.7;
p2.y+=0.5;p1.x+=direction*3.3;p1.y+=0.9;p3.x+=direction*2.5;p3.y+=0.7;
RightLeg.LegsChange(8*direction,13*direction);
RightArm.ArmsChange((-5)*direction,0);
LeftLeg.LegsChange(4*direction,4*direction);
RightLeg.LegsChange((-2.5)*direction,(-2.5)*direction);}
if(i>=30&&i<35)
{p1.y+=4;p2.y+=4;p3.y+=4;
RightLeg.LegsChange((-5)*direction,0);
LeftLeg.LegsChange(5*direction,0);
RightArm.ArmsChange((-8)*direction,0);
LeftArm.ArmsChange((8)*direction,0);}
if(i>=35&&i<40)
{if(i==39)
{MoveSpeed=0;ActionSpeed=0;PlayersMagicPoint-=35;}
p2.x-=0.5;p2.y-=5.2;p1.x-=direction*6.6;p1.y-=6.8;p3.x-=direction*5;p3.y-=6.4;
RightLeg.LegsChange(10*direction,(-2)*direction);
LeftLeg.LegsChange((-10)*direction,(-5)*direction);
RightArm.ArmsChange(11*direction,direction);
LeftArm.ArmsChange((-13)*direction,3*direction);
}
}
void Players::PlayersThump(int i)//PlayersThump函数（重击的实现）；
{
if(i==0)
{p1.x-=direction*30;
p1.y+=direction*12;
p3.x-=direction*25;
p3.y+=direction*7;
ActionSpeed=90;MoveSpeed=15;}
if(i>0&&i<6)
{LeftArm.ArmsChange(direction*10,direction*(-5));
RightLeg.LegsChange(direction*(-8),0);}
if(i==6)
{}
if(i==7)
{p2.y+=24;
p2.x+=direction*48;
p3.x=p2.x+(direction*35);
p3.y=p2.y-35;
p1.x=p2.x+(direction*46);
p1.y=p2.y-46;
LeftArm.ArmsChange(direction*(-150),(-49)*direction);
RightArm.ArmsChange(direction*90,0);
LeftLeg.LegsChange(direction*50,direction*55);
RightLeg.LegsChange(direction*(-10),direction*55);
}
if(i>7&&i<20)
{}
if(i==21)
{p2.x-=direction*48;p2.y-=24;
p1.x=p2.x;p1.y=p2.y-65;
p3.x=p2.x;p3.y=p2.y-50;
ActionSpeed=0;MoveSpeed=0;PlayersMagicPoint-=8;}
//LeftLeg(p2,100, 95),RightLeg(p2,75, 85)
}
void Players::PlayersFirePunch(int i)//PlayersFirePunch函数（升龙拳的实现）；
{
 if(i>=0&&i<11)
{
	if(i==0)
   {
	 ActionSpeed=160;
     MoveSpeed=55;
	}
    LeftLeg.LegsChange(6.5*direction,4*direction);
    RightLeg.LegsChange((-4.5)*direction,(-4)*direction);
    LeftArm.ArmsChange(6.5*direction,3*direction);
    RightArm.ArmsChange((-2)*direction,0);
    p2.y+=3.3;p1.x=p2.x+65*cos(80*(PI/180))*direction;
    p3.x=p1.x=p2.x+50*cos(80*(PI/180))*direction;
    p1.y=p2.y-65*sin(80*(PI/180));
    p3.y=p2.y-50*sin(80*(PI/180));
}
if(i>=11&&i<16)
{
	LeftLeg.LegsChange((-9)*direction,0);
	RightLeg.LegsChange(9*direction,0);
	LeftArm.ArmsChange((-17)*direction,(-20)*direction);
	RightArm.ArmsChange(18*direction,0);
	p1.y-=4;p2.y-=4;p3.y-=4;
}
if(i==16)
{
	p1.x=p3.x=p2.x;
}
if(i>=17&&i<22)
{
	LeftLeg.LegsChange((-4)*direction,(-8)*direction);
	RightLeg.LegsChange(4*direction,8*direction);
	LeftArm.ArmsChange((-32)*direction,(-20)*direction);
	RightArm.ArmsChange((-4)*direction,0);
	p1.x+=16*direction;p2.x+=16*direction;p3.x+=16*direction;
	p1.y-=30;p2.y-=30;p3.y-=30;
}
if(i>=22&&i<28)
{
	p1.y-=7;p2.y-=7;p3.y-=7;
}
if(i>=28&&i<45)
{
	if(i==28)
	PlayersAngleReset(direction);
	if(i>=28&&i<38)
    {
	RightArm.ArmsChange(3.5*direction,4.8*direction);
	LeftArm.ArmsChange((-3.5)*direction,(-2.3)*direction);
	LeftLeg.LegsChange(4*direction,0);
	RightLeg.LegsChange((-3.5)*direction,0);
	}
	p1.y+=11;p2.y+=11;p3.y+=11;
}
if(i>=45&&i<55)
{
	LeftLeg.LegsChange(4*direction,0);
    RightLeg.LegsChange((-4)*direction,0);
    LeftArm.ArmsChange((-3)*direction,2*direction);
    RightArm.ArmsChange((3)*direction,(-2)*direction);
    p1.y+=2;p2.y+=2;p3.y+=2;
if(i==54)
{
	PlayersMagicPoint-=30;ActionSpeed=0;MoveSpeed=0;
}
}
}
void Players::PlayersJump(int i)
{
	if(i>=0&&i<6)
   {
	LeftLeg.LegsChange(8*direction,0);
    RightLeg.LegsChange((-7)*direction,0);
    p1.y+=3.2;p2.y+=3.2;p3.y+=3.2;
	}
    if(i>=6&&i<8)
   {
	LeftLeg.LegsChange((-10)*direction,0);
    RightLeg.LegsChange(10*direction,0);
    p1.y-=6.5;p2.y-=6.5;p3.y-=6.5;
    }
    if(i>=8&&i<10)
    {
	RightLeg.LegsChange(10*direction,0);
    LeftLeg.LegsChange((-10)*direction,0);
    p1.y-=9;p2.y-=9;p3.y-=9;
	}
    if(i>=10&&i<20)
   {  
	p2.y-=38-2.7*sqrt(461-p1.y);
	p3.y-=38-2.7*sqrt(461-p1.y);
	p1.y-=38-2.7*sqrt(461-p1.y);
	}
    if(i>=20&&i<22)
    {}

	if(i>=22&&i<34)
    { 
	p2.y+=2*sqrt(p1.y-311);
	p3.y+=2*sqrt(p1.y-311);
	p1.y+=2*sqrt(p1.y-311);
	}
}
void Players::PlayersSquat(int i)
{
if(i>=0&&i<6)
{if(i==0)
MoveSpeed=-75;
RightLeg.LegsChange((-10)*direction,(-8)*direction);
LeftLeg.LegsChange(10*direction,8*direction);
RightArm.ArmsChange((-13)*direction,(-25)*direction);
LeftArm.ArmsChange((-21)*direction,(-25)*direction);
p1.y+=9;p1.x+=6.6*direction;p2.y+=7;p3.y+=9;p3.x+=5*direction;}
if(i>=6&&i<16)
{if(i==15)
MoveSpeed=0;
}
}
void Players::PlayersRay(int i)//必杀技；
{if(i>=0&&i<10)
{if(i==0)
{ActionSpeed=500;}
p1.y+=2;p2.y+=2;p3.y+=2;
RightArm.ArmsChange(-8*direction,-7*direction);
LeftArm.ArmsChange(5*direction,3*direction);
RightLeg.LegsChange(-6*direction,-direction);
LeftLeg.LegsChange(4*direction,4*direction);
}
if(i>=10&&i<25)
{if((i%2)==0)
 solidcircle(RightArm.GetHandX(),RightArm.GetHandY(),i);
 else
 solidcircle(RightArm.GetHandX(),RightArm.GetHandY(),i-1);
}
if(i>=25&&i<30)
{if((i%2)==0)
 solidcircle(RightArm.GetHandX(),RightArm.GetHandY(),51-i);
  else
 solidcircle(RightArm.GetHandX(),RightArm.GetHandY(),50-i);
}
if(i>=30&&i<45)
{
	if(i==30)
solidcircle(RightArm.GetHandX(),RightArm.GetHandY(),25);
solidcircle(RightArm.GetHandX(),RightArm.GetHandY(),25);
solidrectangle(RightArm.GetHandX()+0.92*direction*sqrt((double)(25*25-(53-i)*(53-i))),RightArm.GetHandY()-(53-i),RightArm.GetHandX()+1500*direction,RightArm.GetHandY()+(53-i));}
if(i>=45&&i<70)
{solidcircle(RightArm.GetHandX(),RightArm.GetHandY(),70-i);
if(i==69)
{PlayersMagicPoint-=100;ActionSpeed=0;}
}
}
void Players::PlayersDart(int i)
{if(i==0)
{MyDart=new Dart(LeftArm.GetHandX(),LeftArm.GetHandY());}
if(i>0&&i<10)
{RightLeg.LegsChange(-4*direction,0);
LeftLeg.LegsChange(4*direction,4*direction);
LeftArm.ArmsChange(10*direction,18*direction);
RightArm.ArmsChange(-10*direction,-10*direction);
p1.y+=2;p2.y+=2;p3.y+=2;
p1.x-=3.3*direction;p3.x-=2.5*direction;p1.y+=0.9;p3.y+=0.7;
MyDart->DartSet(LeftArm.GetHandX(),LeftArm.GetHandY());
}
if(i==10)
{p1.x+=65*direction;p3.x+=50*direction;
LeftArm.ArmsChange(0,(-120)*direction);
RightArm.ArmsChange(12*direction,15*direction);
MyDart->DartSet(RightArm.GetHandX(),RightArm.GetHandY());
}
if(i>=11&&i<22)
{MyDart->DartChange(MyDart->MoveSpeed*direction,0);}
if(i==22)
{delete MyDart;}
MyDart->DartIn(direction);
}
void Players::PlayersGetHurt(int *i)
{
	if((1333-p2.x)<=55)
    {
	  PlayersAttackReset();PlayersCommandReset();PlayersHightReset(direction);PlayersBodyReset(direction);(*i)=0;
      p2.x-=120;p1.x-=120;p3.x-=120;
	}
	if(p2.x<=55)
	{
	  PlayersAttackReset();PlayersCommandReset();PlayersHightReset(direction);PlayersBodyReset(direction);(*i)=0;
      p2.x+=120;p1.x+=120;p3.x+=120;
	}
	if(atk.Stumble!=0)
	{
		MoveSpeed=0;
		ActionSpeed=0;
		if((*i)==0)
		{PlayersBodyReset(direction);
		PlayersHightReset(direction);}
		PlayersStumble(*i,atk.Stumble);
		(*i)++;
		if((*i)==16)
		{atk.Stumble=0;
		(*i)=0;
		PlayersBodyReset(direction);
		PlayersHightReset(direction);
		}
	}
	if(atk.AlmostDie!=0)
	{
		MoveSpeed=0;
		ActionSpeed=0;
		if((*i)==0)
		{PlayersBodyReset(direction);
		PlayersHightReset(direction);}
		PlayersAlmostDie(*i,atk.AlmostDie);
		(*i)++;
		if((*i)==25)
		{atk.AlmostDie=0;
		(*i)=0;
		PlayersBodyReset(direction);
		PlayersHightReset(direction);
		}
	}
	if(atk.ComeToSky!=0)
	{
		MoveSpeed=0;
		ActionSpeed=0;
		if((*i)==0)
		{PlayersBodyReset(direction);
		PlayersHightReset(direction);}
		PlayersComeToSky(*i,atk.ComeToSky);
		(*i)++;
		if((*i)==25)
		{atk.ComeToSky=0;
		(*i)=0;
		PlayersBodyReset(direction);
		PlayersHightReset(direction);
		}
	}
	if(atk.DoubleHurt!=0)
	{
		MoveSpeed=0;
		ActionSpeed=0;
		if((*i)==0)
		{PlayersBodyReset(direction);
		PlayersHightReset(direction);}
		PlayersGetDoubleHurt(*i,atk.DoubleHurt);
		(*i)++;
		if((*i)==37)
		{atk.DoubleHurt=0;
		(*i)=0;
		PlayersBodyReset(direction);
		PlayersHightReset(direction);
		}
	}
	if(atk.GetKnockedDown!=0)
	{
		MoveSpeed=0;
		ActionSpeed=0;
		if((*i)==0)
		{PlayersBodyReset(direction);
		PlayersHightReset(direction);}
		PlayersGetKnockedDown(*i,atk.GetKnockedDown);
		(*i)++;
		if((*i)==30)
		{atk.GetKnockedDown=0;
		(*i)=0;
		PlayersBodyReset(direction);
		PlayersHightReset(direction);
		}
	}
	if(atk.GetKickedFlew!=0)
	{
		MoveSpeed=0;
		ActionSpeed=0;
		if((*i)==0)
		{PlayersBodyReset(direction);
		PlayersHightReset(direction);}
		PlayersGetKickedFlew(*i,atk.GetKickedFlew);
		(*i)++;
		if((*i)==20)
		{atk.GetKickedFlew=0;
		(*i)=0;
		PlayersBodyReset(direction);
		PlayersHightReset(direction);
		}
	}
	if(atk.DefendSucceed!=0)
	{
		MoveSpeed=0;
		ActionSpeed=0;
		if((*i)==0)
		{PlayersBodyReset(direction);
		PlayersHightReset(direction);}
		PlayersDefendSucceed(*i);
		(*i)++;
		if((*i)==10)
		{atk.DefendSucceed=0;
		(*i)=0;
		PlayersBodyReset(direction);
		PlayersHightReset(direction);
		}
	}
	
}
void Players::PlayersStumble(int i,int di)
{

	int v=100;
	if(i==0)
	{
		PlayersHightReset(direction);
		PlayersBodyReset(direction);
		p1.x+=15*direction*di;
		p3.x+=12*direction*di;
		RightArm.ArmsSet(90-45*direction,90-70*direction);
		LeftArm.ArmsSet(90-35*direction,90-60*direction);
		LeftLeg.LegsSet(90+10*direction,90+25*direction);
		RightLeg.LegsSet(90-70*direction,90-10*direction);
	}
	if(i>0&&i<=3)
	{
		p1.x+=v*0.05*direction*di;
		p2.x+=v*0.05*direction*di;
		p3.x+=v*0.05*direction*di;
		LeftArm.ArmsChange(-5*direction,0);
		RightArm.ArmsChange(-5*direction,0);
		LeftLeg.LegsChange(-10*direction,-8*direction);
		RightLeg.LegsChange(-10*direction,0);
	}
	if(i>3&&i<=6)
	{
		p1.x+=v*0.05*direction*di;
		p2.x+=v*0.05*direction*di;
		p3.x+=v*0.05*direction*di;
		LeftArm.ArmsChange(0,0);
		RightArm.ArmsChange(0,0);
		LeftLeg.LegsChange(-10*direction,-5*direction);
		RightLeg.LegsChange(20*direction,5*direction);
	}
	if(i>6&&i<=9)
	{
		p1.x+=v*0.03*direction*di;
		p2.x+=v*0.03*direction*di;
		p3.x+=v*0.03*direction*di;
		LeftArm.ArmsChange(5*direction,3*direction);
		RightArm.ArmsChange(5*direction,3*direction);
		LeftLeg.LegsChange(17*direction,30*direction);
		RightLeg.LegsChange(-10*direction,-5*direction);
	}
	if(i>9&&i<=12)
	{
		p1.x+=v*0.01*direction*di;
		p2.x+=v*0.01*direction*di;
		p3.x+=v*0.01*direction*di;
		LeftArm.ArmsChange(5*direction,3*direction);
		RightArm.ArmsChange(5*direction*di,3*direction);
		LeftLeg.LegsChange(-10*direction,-20*direction);
		RightLeg.LegsChange(25*direction,15*direction);
	}
	if(i>12&&i<=15)
	{
		p1.x+=v*0.01*direction*di;
		p2.x+=v*0.01*direction*di;
		p3.x+=v*0.01*direction*di;
		LeftArm.ArmsChange(5*direction,3*direction);
		RightArm.ArmsChange(5*direction,3*direction);
		LeftLeg.LegsChange(10*direction,7*direction);
		RightLeg.LegsChange(-2*direction,-10*direction);
	
    }
}
void Players::PlayersGetKnockedDown(int i,int di)
{
	if(i==0)
	{   p1.x=p2.x+sin(30*(PI/180))*65*di/abs(di);
		p1.y=p2.y-cos(30*(PI/180))*65;
		p3.x=p2.x+sin(30*(PI/180))*50*di/abs(di);
		p3.y=p2.y-cos(30*(PI/180))*50;
		RightArm.ArmsChange(50*direction,45*direction);
		LeftArm.ArmsChange(50*direction,50*direction);
	}
	if(i>0&&i<8)
	{}
	if(i>=8&&i<15)
	{
		p1.x+=25*di/abs(di);
		p2.x+=25*di/abs(di);
		p3.x+=25*di/abs(di);
	}

}
void Players::PlayersGetKickedFlew(int i,int di)
{
	if(i==0)
	{   p1.x=p2.x+sin(30*(PI/180))*65*di/abs(di);
		p1.y=p2.y-cos(30*(PI/180))*65;
		p3.x=p2.x+sin(30*(PI/180))*50*di/abs(di);
		p3.y=p2.y-cos(30*(PI/180))*50;
		RightArm.ArmsChange(50*direction,45*direction);
		LeftArm.ArmsChange(50*direction,50*direction);
	}
	if(i>0&&i<5)
	{
		p1.x+=70*di/abs(di);
		p2.x+=70*di/abs(di);
		p3.x+=70*di/abs(di);
		p1.y-=10;
		p2.y-=10;
		p3.y-=10;
    }
	if(i>=5&&i<=10)
	{
		p1.x+=60*di/abs(di);
		p2.x+=60*di/abs(di);
		p3.x+=60*di/abs(di);
		p1.y+=17.5;
		p2.y+=17.5;
		p3.y+=17.5;
		RightLeg.LegsChange(-18*direction,-17*direction);
		LeftLeg.LegsChange(-18*direction,-17*direction);
	}
	if(i>10&&i<20)
	{
		p1.x+=(60-3*i)*di/abs(di);
		p2.x+=(60-3*i)*di/abs(di);
		p3.x+=(60-3*i)*di/abs(di);
	}

	
}
void Players::PlayersAlmostDie(int i,int di)
{
	if(i>=0&&i<5)
	{
		p1.x+=9*direction*di;
		p1.y+=5.1;
		p3.x+=7.2*direction*di;
		p3.y+=4.8;
		p2.x+=3.9*direction*di;
		RightArm.ArmsChange(-24*direction*di,-30*direction*di);
		LeftArm.ArmsChange(15*direction*di,25.5*direction*di);

	}
	if(i>=5&&i<25)
	{
		p1.x+=25*direction*di;
		p2.x+=25*direction*di;
		p3.x+=25*direction*di;
	}
	
}

void Players::PlayersDefendSucceed(int i)
{
	if(i>=0&&i<5)
	{
		if(i==0)
        {
			p1.x-=100*direction;
		    p2.x-=100*direction;
		    p3.x-=100*direction;
		}
	RightArm.ArmsChange(30*direction,30*direction);
	LeftArm.ArmsChange(24*direction,24*direction);
	p1.x-=5*direction;
	p1.y-=3.5;
	p3.x-=4.6*direction;
	p3.y-=3.2;
	}
	if(i>=5&&i<10)
	{
		

		p1.x-=5*direction;
	    p3.x-=5*direction;
		p2.x-=5*direction;

	}

}
void Players::PlayersGetDoubleHurt(int i,int di)
{
	if(i>=0&&i<10)
	{
		p2.x+=4.5*di/abs(di);
		p2.y-=3.8;
		p1.x=p2.x+sin(30*(PI/180))*65*di/abs(di);
		p1.y=p2.y-cos(30*(PI/180))*65;
		p3.x=p2.x+sin(30*(PI/180))*50*di/abs(di);
		p3.y=p2.y-cos(30*(PI/180))*50;
		LeftLeg.LegsChange(-5*direction,-5*direction);
		RightLeg.LegsChange(-4.5*direction,-4.5*direction);
		RightArm.ArmsChange(-12.5*direction,-9.5*direction);
		LeftArm.ArmsChange(-13.5*direction,-11.5*direction);
	}
	if(i>=10&&i<17)
	{
		p1.x+=1.5*di/abs(di);
		p2.x+=1.5*di/abs(di);
		p3.x+=1.5*di/abs(di);
	}
	if(i>=17&&i<27)
	{
		p2.y+=11;
		p2.x+=15*di/abs(di);
		p1.x=p2.x+sin(30*(PI/180))*65*di/abs(di);
		p1.y=p2.y-cos(30*(PI/180))*65;
		p3.x=p2.x+sin(30*(PI/180))*50*di/abs(di);
		p3.y=p2.y-cos(30*(PI/180))*50;
		LeftLeg.LegsChange(-9*direction,-9*direction);
		RightLeg.LegsChange(-4.5*direction,-4.5*direction);
		/*RightArm.ArmsChange(4*direction,4*direction);*/
		LeftArm.ArmsChange(-4*direction,-4*direction);
    }
	if(i>=27&&i<32)
	{  
		if(i==27)
		{
			p1.x=p2.x=p3.x;
			p1.x=p2.x+sin(30*(PI/180))*65*di/abs(di);
			p1.y=p2.y-cos(30*(PI/180))*65;
			p3.x=p2.x+sin(30*(PI/180))*50*di/abs(di);
			p3.y=p2.y-cos(30*(PI/180))*50;
		}
		p1.x+=10*di/abs(di);
		p2.x+=10*di/abs(di);
		p3.x+=10*di/abs(di);
	}
	if(i>=32&&i<37)
	{}
}
void Players::PlayersComeToSky(int i,int di)
{
	if(i>=0&&i<10)
	{
		if(i==0)
		{
		
			p1.x=p2.x+sin(30*(PI/180))*65*direction*di;
		    p1.y=p2.y-cos(30*(PI/180))*65;
		    p3.x=p2.x+sin(30*(PI/180))*50*direction*di;
		    p3.y=p2.y-cos(30*(PI/180))*50;
		}
		    RightArm.ArmsChange(2*direction,2*direction);
		    LeftArm.ArmsChange(2*direction,2*direction);
		    RightLeg.LegsChange(2*direction,2*direction);
		    LeftLeg.LegsChange(2*direction,2*direction);
		    p2.x+=14*direction*di;
		    p2.y-=15;
		    p1.x=p2.x+sin(30*(PI/180))*65*direction*di;
		    p1.y=p2.y-cos(30*(PI/180))*65;
		    p3.x=p2.x+sin(30*(PI/180))*50*direction*di;
		    p3.y=p2.y-cos(30*(PI/180))*50;
		    
	}
	if(i>=10&&i<20)
	{
		p1.x+=2.2*direction*di;
		p2.x+=2.2*direction*di;
		p3.x+=2.2*direction*di;
	}
	if(i>=20&&i<30)
	{
		p2.y+=i-10;
		p1.y+=i-10;
		p3.y+=i-10;
	}
}
void Players::PlayersChange(int *i,int *k)//PlayersChange函数（实现所有动作的帧数控制）；
{if((1333-p2.x)<=40||(p2.x)<=40)
{PlayersCommandReset();PlayersHightReset(direction);PlayersBodyReset(direction);(*i)=0;
p2.x-=50*direction;p1.x-=50*direction;p3.x-=50*direction;}
if((cmd.MoveLeft+cmd.MoveRight+cmd.Jump+cmd.Squat)==0)
{    
     if((cmd.Hit+cmd.Kick+cmd.RemoteAttack)==1)
     {
          if(cmd.Hit==1)
          {
			  PlayersHit(*i);
              (*i)++;
              if((*i)==13)
              {
				 cmd.Hit=0;
                 (*i)=0;
                 PlayersBodyReset(direction);
                 PlayersHightReset(direction);
			  }
		  }
          else if(cmd.Kick==1)
          {
			  PlayersKick(*i);
              (*i)++;
              if((*i)==13)
              {
				  cmd.Kick=0;
                  (*i)=0;
                  PlayersHightReset(direction);
                  PlayersBodyReset(direction);
			  }
		  }
          else
		  {
			  if(PlayersMagicPoint>=100)
			  {
			   PlayersRay(*i);
			  (*i)++;
			  if((*i)==70)
			  {cmd.RemoteAttack=0;
			  (*i)=0;
			   PlayersBodyReset(direction);
			   PlayersHightReset(direction);
			  }
			  }
			  else
			  {
		       PlayersDart(*i);
			  (*i)++;
			  if((*i)==23)
			  {
			   MyDart=NULL;
               cmd.RemoteAttack=0;
			   (*i)=0;
			   PlayersBodyReset(direction);
			   PlayersHightReset(direction);
		       }
               }
          }
	 }
     else if((cmd.Hit+cmd.Kick+cmd.RemoteAttack)==2)
     {
	      if(cmd.Hit==1&&cmd.Kick==1)
	      {                   
			  if(PlayersMagicPoint>=10)
			  {PlayersTrample(*i);
              (*i)++;
              if((*i)==28)
              {
				  (*i)=0;
                  cmd.Hit=0;cmd.Kick=0;
                  PlayersHightReset(direction);
                  PlayersBodyReset(direction);
              }
			  }
			  else
			  {cmd.Hit=cmd.Kick=0;
			  }
		  }
	 
	      else
	      {PlayersCommandReset();}
      }
     else
     {PlayersCommandReset();}
}
else if((cmd.MoveLeft+cmd.MoveRight+cmd.Jump+cmd.Squat)==1)
{     
	if((cmd.Hit+cmd.Kick+cmd.RemoteAttack)==0)
	{
		if(cmd.Jump==1)
		{
			PlayersJump(*i);
             if((*k)!=0)
            {
			p1.x+=5*(*k);
            p2.x+=5*(*k);
            p3.x+=5*(*k);
		    }
            (*i)++;
            if((*i)==34)
            {
				(*i)=0;
                cmd.Jump=0;
                PlayersHightReset(direction);
                (*k)=0;
			}
		}
		else if(cmd.MoveLeft==1)
		{
			direction=-1;
			MoveSpeed=20;
            PlayersMove(-20);
            (*i)++;
            if((*i)==3)
            {
			 MoveSpeed=0;
			 cmd.MoveLeft=0;
             (*i)=0;
             PlayersBodyReset(-1);
			}
		}
		else if(cmd.MoveRight==1)
		{
		 direction=1;
		 MoveSpeed=20;
         PlayersMove(20);
         (*i)++;
         if((*i)==3)
         {
			 MoveSpeed=0;
			 cmd.MoveRight=0;
             (*i)=0;
             PlayersBodyReset(1);
		 }
		}
		else
		{PlayersSquat(*i);
		(*i)++;
		if((*i)>=16)
		{
			cmd.Squat=0;
		    (*i)=0;
		    PlayersHightReset(direction);
		    PlayersBodyReset(direction);}
		}
	}
	else if((cmd.Hit+cmd.Kick+cmd.RemoteAttack)==1)
	{
		if((cmd.MoveLeft+cmd.MoveRight)==1)
		{
			if(cmd.MoveLeft==1)
			{
				if(direction==1)
			    {
					if(cmd.Kick==1)
					{
						if(PlayersMagicPoint>=35)
						{PlayersFlyKick(*i);//飞踢；
                        (*i)++;
                        if((*i)==40)
                       {
						 cmd.MoveLeft=0;
                         cmd.Kick=0;
                         (*i)=0;
                         PlayersBodyReset(direction);
                         PlayersHightReset(direction);
                       }
						}
						else
						cmd.MoveLeft=cmd.Kick=0;
					}
					else if(cmd.Hit==1)
					{
						if(PlayersMagicPoint>=30)
						{PlayersFirePunch(*i);//升龙拳
                        (*i)++;
                        if((*i)==55)
                        {
						 cmd.MoveLeft=0;cmd.Hit=0;
                         (*i)=0;
                         PlayersHightReset(direction);
						}
						}
						else
							cmd.MoveLeft=cmd.Hit=0;
					}
					else
					{PlayersCommandReset();}
				}
			    else
			    {
					if(cmd.Kick==1)
					{
						if(PlayersMagicPoint>=25)
						{PlayersDoubleKick(*i);//双踢；
                        (*i)++;
                        if((*i)==40)
                        {
	                     cmd.MoveLeft=0;
                         cmd.Kick=0;
                         (*i)=0;
                         PlayersBodyReset(direction);
                         PlayersHightReset(direction);
                        }
						}
						else
							cmd.MoveLeft=cmd.Kick=0;
					}
					else if(cmd.Hit==1)
					{
						if(PlayersMagicPoint>=8)
						{PlayersThump(*i);//重击
                        (*i)++;
                        if((*i)==22)
                       {
	                    cmd.MoveLeft=0;
                        cmd.Hit=0;
                        (*i)=0;
                        PlayersBodyReset(direction);
                       }
						}
						else
						cmd.MoveLeft=cmd.Hit=0;
					}
					else
					{PlayersCommandReset();}
				}
			}
			else//MoveRight==1；
			{
				if(direction==1)
			    {
					if(cmd.Kick==1)
					{
						if(PlayersMagicPoint>=25)
						{PlayersDoubleKick(*i);//双踢；
                        (*i)++;
                        if((*i)==40)
                        {
						 cmd.MoveRight=0;
                         cmd.Kick=0;
                         (*i)=0;
                         PlayersBodyReset(direction);
                         PlayersHightReset(direction);
                        }
						}
						else
						cmd.MoveRight=cmd.Kick=0;
					}
					else if(cmd.Hit==1)
				    {
						if(PlayersMagicPoint>=8) 
						{PlayersThump(*i);//重击
                         (*i)++;
                         if((*i)==22)
                         {
						  cmd.MoveRight=0;
                          cmd.Hit=0;
                          (*i)=0;
                          PlayersBodyReset(direction);
                         }
					}
						 else
							 cmd.MoveRight=cmd.Hit=0;
					}
					else
					{PlayersCommandReset();}
				}
			    else
			    {
				if(cmd.Kick==1)
				{
					if(PlayersMagicPoint>=35)
                    {PlayersFlyKick(*i);
                    (*i)++;
                    if((*i)==40)
                   {
					   cmd.MoveRight=0;
                       cmd.Kick=0;
                       (*i)=0;
                       PlayersBodyReset(direction);
                       PlayersHightReset(direction);
					}
					}
					else
						cmd.MoveRight=cmd.Kick=0;
				}
					else if(cmd.Hit==1)
					{
						if(PlayersMagicPoint>=35)
						{
						PlayersFirePunch(*i);//升龙拳
                        (*i)++;
                        if((*i)==55)
                        {
							cmd.MoveRight=0;cmd.Hit=0;
                            (*i)=0; 
                            PlayersHightReset(direction);
						}
						}
					    else
							cmd.Hit=cmd.MoveRight=0;
				    }
					else
					{PlayersCommandReset();}
				}
			}
		}
		else
		{PlayersCommandReset();}
	}
	else
	{PlayersCommandReset();}
}
else
{PlayersCommandReset();}
}
 void Players::PlayersAngleReset(int i)//PlayersAngleReset函数（四肢恢复默认）；
{if(i==1)
{
	LeftLeg.LegsSet(100,95);
	RightLeg.LegsSet(75,85);
	RightArm.ArmsSet(80,73);
	LeftArm.ArmsSet(100,74);}
else
{
	LeftLeg.LegsSet(80,85);
	RightLeg.LegsSet(105,95);
	RightArm.ArmsSet(100,107);
	LeftArm.ArmsSet(80,106);}
}

void Players::PlayersHightReset(int i)//PlayersHightReset（高度还原）；
{if(i==1)
{
	p1.y=461;
	p2.y=526;
	p3.y=476;
	LeftLeg.LegsSet(100,95);
	RightLeg.LegsSet(75,85);
	RightArm.ArmsSet(80,73);
	LeftArm.ArmsSet(100,74);
}
else
{
	p1.y=461;
	p2.y=526;
	p3.y=476;
	LeftLeg.LegsSet(80,85);
	RightLeg.LegsSet(105,95);
	RightArm.ArmsSet(100,107);
	LeftArm.ArmsSet(80,106);
}
}

void Players::PlayersBodyReset(int i)//PlayersBodyReset函数（恢复直立状态）；
{
	if(i==1)
	{
		p1.x=p2.x;
		p3.x=p2.x;
		LeftLeg.LegsSet(100,95);
		RightLeg.LegsSet(75,85);
		RightArm.ArmsSet(80,73);
		LeftArm.ArmsSet(100,74);
	}
	else
	{
		p1.x=p2.x;
		p3.x=p2.x;
		LeftLeg.LegsSet(80,85);
		RightLeg.LegsSet(105,95);
		RightArm.ArmsSet(100,107);
		LeftArm.ArmsSet(80,106);
	}
}
void Players::PlayersCommandReset()//PlayersCommandReset函数（所有命令参数归零）；
{cmd.RemoteAttack=0;
cmd.Hit=0;cmd.Kick=0;
cmd.MoveLeft=0;
cmd.MoveRight=0;
cmd.Squat=0;
cmd.Jump=0;}
void Players::PlayersAttackReset()
{atk.AlmostDie=0;
atk.ComeToSky=0;
atk.DoubleHurt=0;
atk.GetKickedFlew=0;
atk.GetKnockedDown=0;
atk.Stumble=0;
atk.DefendSucceed=0;}
void Players::PlayersDrawStatus(int x)
{
    if(x<100)
	{
		rectangle(x+40,635,x+442,660);
		rectangle(x+40,670,x+242,695);
		setfillcolor(RED);
		solidrectangle(x+41,636,x+41+4*PlayersBlood,659);
		setfillcolor(BLUE);
		solidrectangle(x+41,671,x+41+2*PlayersMagicPoint,694);
		outtextxy(x+10,640,'H');
		outtextxy(x+20,640,'P');
		outtextxy(x+10,675,'M');
		outtextxy(x+20,675,'P');
	}
	else	
	{
		rectangle(x+40,635,x+442,660);
		rectangle(x+240,670,x+442,695);
		setfillcolor(RED);
		solidrectangle(x+441-4*PlayersBlood,636,x+441,659);
		setfillcolor(BLUE);
		solidrectangle(x+441-2*PlayersMagicPoint,671,x+441,694);
		outtextxy(x+450,640,'H');
		outtextxy(x+460,640,'P');
		outtextxy(x+450,675,'M');
		outtextxy(x+460,675,'P');
	}
}
void Players::PlayersAllReset(int i,int di)
{
PlayersCommandReset();
PlayersAttackReset();
direction=di;
PlayersHightReset(direction);
PlayersBodyReset(direction);
p1.x=p2.x=p3.x=i;
}
#endif