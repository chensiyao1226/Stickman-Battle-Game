#ifndef _OBJECT_H_
#define _OBJECT_H_
#include"PLAYERS.h"
#include<conio.h>
#include<graphics.h>
class Object
{private:
Players p1;
Players p2;
public:
Object();
void ObjectStart();
void ObjectCommandInput(int i,int j,int *k1,int *k2);
void PlayersHurtJudge(int *i,int *j);
void PlayersHurtAchieve(int *i,int *j);
void PlayersAct(int *i,int *j,int *k1,int *k2);
void ObjectUpdate();
void Login();
};
Object::Object():p1(),p2(1)
{initgraph(1333,700);
setbkcolor(HSVtoRGB(0,0,0));
cleardevice();
/*setwritemode(R2_XORPEN);*/
setlinestyle(PS_SOLID,5,PS_ENDCAP_ROUND);
}
void Object::ObjectCommandInput(int i,int j,int *k1,int *k2)//ObjectCommandInput�������������룩��
{       if(i==0)
	    {if(GetAsyncKeyState(87))
		p1.cmd.Jump=1;
		if(GetAsyncKeyState(65))
		{p1.cmd.MoveLeft=1;}   
		if(GetAsyncKeyState(68))
		{p1.cmd.MoveRight=1;}
		if(GetAsyncKeyState(74))
		p1.cmd.Hit=1;
		if(GetAsyncKeyState(75))
		p1.cmd.Kick=1;
        if(GetAsyncKeyState(83))
		p1.cmd.Squat=1;
		if(GetAsyncKeyState(76))
		p1.cmd.RemoteAttack=1;
        }
		if(j==0)
        {if(GetAsyncKeyState(VK_LEFT))//p2
		{p2.cmd.MoveLeft=1;}
		if(GetAsyncKeyState(VK_RIGHT))
		{p2.cmd.MoveRight=1;}
		if(GetAsyncKeyState(VK_UP))
		p2.cmd.Jump=1;
		if(GetAsyncKeyState(VK_DOWN))
		p2.cmd.Squat=1;
		if(GetAsyncKeyState(VK_NUMPAD1))
		p2.cmd.Hit=1;
		if(GetAsyncKeyState(VK_NUMPAD2))
		p2.cmd.Kick=1;
		if(GetAsyncKeyState(VK_NUMPAD3))
		p2.cmd.RemoteAttack=1;
		}
(*k1)=(*k2)=0;
if(GetAsyncKeyState(VK_LEFT))
(*k1)=-1;
if(GetAsyncKeyState(VK_RIGHT))
(*k1)=1;
if(GetAsyncKeyState(65))
(*k2)=-1;
if(GetAsyncKeyState(68))
(*k2)=1;
}
void Object::ObjectStart()//ObjectStart��������Ϸ��ʼ����
{   int i=0,j=0,k1=0,k2=0;   
    loadimage(NULL,_T("1.bmp"),1333,240);
   while(1)
	   {
		BeginBatchDraw();
        p1.PlayersIn();
        FlushBatchDraw();
		setfillcolor(RED);
		setlinecolor(RED);
        p2.PlayersIn();
        EndBatchDraw();
		setfillcolor(WHITE);
		setlinecolor(WHITE);
		ObjectCommandInput(i,j,&k1,&k2);//cmd 
	    PlayersAct(&i,&j,&k1,&k2);
		if(p1.atk.AlmostDie+p1.atk.ComeToSky+p1.atk.DefendSucceed+p1.atk.DoubleHurt+p1.atk.GetKickedFlew+p1.atk.GetKnockedDown+p1.atk.Stumble+p2.atk.AlmostDie+p2.atk.ComeToSky+p2.atk.DefendSucceed+p2.atk.DoubleHurt+p2.atk.GetKickedFlew+p2.atk.GetKnockedDown+p2.atk.Stumble==0)
		PlayersHurtJudge(&i,&j);//atk
		PlayersHurtAchieve(&i,&j);
		if(p1.PlayersBlood<=0)
		{
			while(1)
			{
				IMAGE img;
				loadimage(&img,_T("21.bmp"),1200,300);
				putimage(60,265,&img);
				if(GetAsyncKeyState(VK_SPACE))
				{
					p1.PlayersBlood=100;p1.PlayersAllReset(520,1);
					p2.PlayersBlood=100;p2.PlayersAllReset(800,-1);
					j=0;i=0,k1=0,k2=0;
				    break;
				}
			}

		}
		if(p2.PlayersBlood<=0)
		{
			while(1)
			{
				IMAGE img;
				loadimage(&img,_T("22.bmp"),1200,300);
				putimage(60,265,&img);
				if(GetAsyncKeyState(VK_SPACE))
				{
					p1.PlayersBlood=100;p1.PlayersAllReset(520,1);
					p2.PlayersBlood=100;p2.PlayersAllReset(800,-1);
					j=0;i=0,k1=0,k2=0;
				    break;
				}
			}

		}
		Sleep(30);
		ObjectUpdate();
		}
}
void Object::PlayersHurtJudge(int *i,int *j)//�˺���أ�
{
	double k1=(p1.p1.y-p1.p2.y)/(p1.p1.x-p1.p2.x);
	if(p1.p1.x==p1.p2.x)
	k1=9999999;
	double k2=(p2.p1.y-p2.p2.y)/(p2.p1.x-p2.p2.x);
	if(p2.p1.x==p2.p2.x)
	k2=9999999;
	if(p1.cmd.Hit==1&&p1.cmd.Kick==0)//p1Hit;
	{
		if(p2.cmd.Hit==1&&p2.cmd.Kick==0)//p1ȭ+p2ȭ��
		{
		 double Distance1_Left_=fabs(p1.LeftArm.GetArmY()-k2*(p1.LeftArm.GetArmX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
         double Distance1_Right_=fabs(p1.RightArm.GetArmY()-k2*(p1.RightArm.GetArmX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2); 
		 double Distance2_Left_=fabs(p2.LeftArm.GetArmY()-k1*(p2.LeftArm.GetArmX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
		 double Distance2_Right_=fabs(p2.RightArm.GetArmY()-k1*(p2.RightArm.GetArmX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
		 if((Distance1_Left_<=40&&p1.LeftArm.GetArmY()<p2.p2.y)||(Distance1_Right_<=40&&p1.RightArm.GetArmY()<p2.p2.y))/*p1��ȭ������p2*/
		 {
			 int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
			 p2.PlayersCommandReset();
			 (*j)=0;
			 if(p1.direction==1)
			 {
				 if(p1.cmd.MoveLeft==1)
				 {
					 if((Distance1_Right_<=40)&&((*i)<=22&&(*i)>16))
					 {p2.atk.ComeToSky=1*p1.direction*p2.direction;
					 p2.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					 p2.PlayersBlood-=RelativeSpeed/10;
					 if(RelativeSpeed<=85)
					 {p2.atk.Stumble=1*(p1.direction*p2.direction);}
					 else if(RelativeSpeed<125)
					 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					 else
					 {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				 }
			 }
			 else
			 {
				 if(p1.cmd.MoveRight==1)
				 {
					 if((Distance1_Right_<=40)&&((*i)<=22&&(*j)>16))
					 {p2.atk.ComeToSky=1*p1.direction*p2.direction;
					 p2.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					 p2.PlayersBlood-=RelativeSpeed/10;
					 if(RelativeSpeed<=85)
					 {p2.atk.Stumble=1*p1.direction*p2.direction;}
					else if(RelativeSpeed<125)
					 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					 else
					 {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				 }
			 }
		 
		 
		 }
		 if((Distance2_Left_<=40&&p2.LeftArm.GetArmY()<p1.p2.y)||(Distance2_Right_<=40&&p2.RightArm.GetArmY()<p1.p2.y))/*p2��ȭ������p1*/
		 {
			 int RelativeSpeed=p2.ActionSpeed-(p2.direction*p1.direction*p1.MoveSpeed);
			 p1.PlayersCommandReset();
			 
			 (*i)=0;
			 if(p2.direction==1)
			 {
				 if(p2.cmd.MoveLeft==1)
				 {
					 if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
					 {p1.atk.ComeToSky=1*p1.direction*p2.direction;
					 p1.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					 p1.PlayersBlood-=RelativeSpeed/10;
					 if(RelativeSpeed<=85)
					 {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					 
					 else if(RelativeSpeed<125)
					 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					 else
					 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				 }
			 }
			 else
			 {
				 if(p2.cmd.MoveRight==1)
				 {
					 if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
					 {p1.atk.ComeToSky=1*p1.direction*p2.direction;
					 p1.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					 p1.PlayersBlood-=RelativeSpeed/10;
					 if(RelativeSpeed<=85)
					 {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					  else if(RelativeSpeed<125)
					 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					 else
					 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				 }
			 }
		  }

 		}
		else if(p2.cmd.Kick==1)//p1ȭ+p2�ţ�
		{
	     double Distance1_Left_=fabs(p1.LeftArm.GetArmY()-k2*(p1.LeftArm.GetArmX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
         double Distance1_Right_=fabs(p1.RightArm.GetArmY()-k2*(p1.RightArm.GetArmX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2); 
		 double Distance2_Left_=fabs(p2.LeftLeg.GetLegY()-k1*(p2.LeftLeg.GetLegX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
		 double Distance2_Right_=fabs(p2.RightLeg.GetLegY()-k1*(p2.RightLeg.GetLegX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
 		 if((Distance1_Left_<=40&&p1.LeftArm.GetArmY()<p2.p2.y)||(Distance1_Right_<=40&&p1.RightArm.GetArmY()<p2.p2.y))///*p1��ȭ������p2*/
		 {   
			 int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
			 p2.PlayersCommandReset();
			 
			 (*j)=0;
			 if(p1.direction==1)
			 {
				 if(p1.cmd.MoveLeft==1)
				 {
					 if((Distance1_Right_<=40)&&((*i)<=22&&(*i)>16))
					 {p2.atk.ComeToSky=1*p1.direction*p2.direction;
					 p2.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					 p2.PlayersBlood-=RelativeSpeed/10;
					 if(RelativeSpeed<=85)
					 {p2.atk.Stumble=1*(p1.direction*p2.direction);}
					 else if(RelativeSpeed<125)
					 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					 else
					 {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				 }
			 }
			 else
			 {
				 if(p1.cmd.MoveRight==1)
				 {
					 if((Distance1_Right_<=40)&&((*i)<=22&&(*i)>16))
					{ p2.atk.ComeToSky=1*p1.direction*p2.direction;
					 p2.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					 p2.PlayersBlood-=RelativeSpeed/10;
					 if(RelativeSpeed<=85)
					 {p2.atk.Stumble=1*p1.direction*p2.direction;}
					 else if(RelativeSpeed<125)
					 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					 else
					 {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				 }
			 }
		 }
		 if((Distance2_Left_<=40&&p2.LeftLeg.GetLegY()<p1.p2.y)||(Distance2_Right_<=40&&p2.RightLeg.GetLegY()<p1.p2.y))
			 /*p2�ýŻ�����p1*/
		 {
			 int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
			 p1.PlayersCommandReset();
			
			 (*i)=0;
			 if(p2.direction==1)
			 {
				 
				 if(p2.cmd.MoveRight==1)
				 {
					 if((*j)>=0&&(*i)<=6)
					 {p1.atk.DoubleHurt=1*p1.p1.x-p2.p1.x;
					p1.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					  p1.PlayersBlood-=RelativeSpeed/10;
					 if(RelativeSpeed<=85)
					 {p1.atk.Stumble=p1.direction*p2.direction;}
				 else if(RelativeSpeed<125)
					 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					 else
					 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				 }
			 }
			 else
			 {
				 
				 if(p2.cmd.MoveLeft==1)
				 {
					  if((*j)>=0&&(*i)<=6)
					 {p1.atk.DoubleHurt=1*p1.direction*p2.direction;
					p1.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					 p1.PlayersBlood-=RelativeSpeed/10;
					 if(RelativeSpeed<=85)
					 {p1.atk.Stumble=p1.direction*p2.direction;}
					else if(RelativeSpeed<125)
					 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					 else
					 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				 }
			 }
		 }
		}
		else if(p2.cmd.RemoteAttack==1)//p1ȭ+p2Զ�̣�
		{
		 double Distance1_Left_=fabs(p1.LeftArm.GetArmY()-k2*(p1.LeftArm.GetArmX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
         double Distance1_Right_=fabs(p1.RightArm.GetArmY()-k2*(p1.RightArm.GetArmX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
		 if(p2.MyDart==NULL)//p2���У�
		 {
			 if((*j)>=31&&(*j)<45)//p2�����ѷ�����
		     {
				 int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
			    if(p2.p1.x>p1.p1.x&&p2.direction==-1)
		        {
					/*p2���д���p1*/
					p1.PlayersBlood-=RelativeSpeed/10;			
					p1.atk.AlmostDie=1*p1.direction*p2.direction;
					p1.PlayersCommandReset();
					(*i)=0;
				}
		        else if(p2.p1.x<p1.p1.x&&p2.direction==1)
		        {
					/*p2���д���p1*/
					p1.PlayersBlood-=RelativeSpeed/10;			
					p1.atk.AlmostDie=1*p1.direction*p2.direction;
					p1.PlayersCommandReset();
					(*i)=0;
				}
				else
				{
					/*p1ȭ��p2*/
					if((Distance1_Left_<=40&&p1.LeftArm.GetArmY()<p2.p2.y)||(Distance1_Right_<=40&&p1.RightArm.GetArmY()<p2.p2.y))
				    {
						int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
			            p2.PlayersCommandReset();
			            
			            (*j)=0;
			            if(p1.direction==1)
			            {
				            if(p1.cmd.MoveLeft==1)
				            {
								if((Distance1_Right_<=40)&&((*i)<=22&&(*i)>16))
								{p2.atk.ComeToSky=1*p1.direction*p2.direction;
								p2.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p2.atk.Stumble=1*(p1.direction*p2.direction);}
					           	 else if(RelativeSpeed<125)
					            {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					             else
					             {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
			            else
			            {
				             if(p1.cmd.MoveRight==1)
				            {
								if((Distance1_Right_<=40)&&((*i)<=22&&(*i)>16))
								{p2.atk.ComeToSky=1*p1.direction*p2.direction;
								p2.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p2.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
					            {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					             else
					             {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			            }
						
					 }
				}
		     }
			 else//p2����δ������
			 {
				if((Distance1_Left_<=40&&p1.LeftArm.GetArmY()<p2.p2.y)||(Distance1_Right_<=40&&p1.RightArm.GetArmY()<p2.p2.y))
				{
					/*p1��ȭ����p2*/
				        int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
			            p2.PlayersCommandReset();
			            
			            (*j)=0;
			            if(p1.direction==1)
			            {
				            if(p1.cmd.MoveLeft==1)
				            {
								if((Distance1_Right_<=40)&&((*i)<=22&&(*i)>16))
								{p2.atk.ComeToSky=1*p1.direction*p2.direction;
								p2.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p2.atk.Stumble=1*(p1.direction*p2.direction);}
					           
								 else if(RelativeSpeed<125)
					            {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					             else
					             {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
			            else
			            {
				             if(p1.cmd.MoveRight==1)
				            {
								if((Distance1_Right_<=40)&&((*i)<=22&&(*i)>16))
								{p2.atk.ComeToSky=1*p1.direction*p2.direction;
								p2.PlayersBlood-=RelativeSpeed/10;}
							 }
				             else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
								if(RelativeSpeed<=85)
					             {p2.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
					            {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					             else
					             {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
				  }	

			 }
		 }
		 else//p2���ڣ�
		 {
			 double Distance2_Dart_=fabs(p2.MyDart->GetDartY()-k1*(p2.MyDart->GetDartX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
			 if(Distance2_Dart_<=100)
			 {
				 /*p2���ڴ���p1*/
				 int RelativeSpeed=50-(p1.direction*p2.direction*p1.MoveSpeed);
				 p1.PlayersCommandReset();
				 p1.PlayersBlood-=RelativeSpeed/10;
				 (*i)=0;
				 if(RelativeSpeed<=85)
			     {p1.atk.Stumble=1*p1.direction*p2.direction;}
				 else if(RelativeSpeed<125)
				 {p1.atk.GetKnockedDown=1*p1.direction*p2.direction;}
				 else
				 {p1.atk.GetKickedFlew=1*p1.direction*p2.direction;}
			 }
			 if((Distance1_Left_<=40&&p1.LeftArm.GetArmY()<p2.p2.y)||(Distance1_Right_<=40&&p1.RightArm.GetArmY()<p2.p2.y))/*p1��ȭ����p2*/
			 {
				        int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
			            p2.PlayersCommandReset();
			            
			            (*j)=0;
			            if(p1.direction==1)
			            {
				            if(p1.cmd.MoveLeft==1)
				            {
								if((Distance1_Right_<=40)&&((*i)<=22&&(*i)>16))
								{p2.atk.ComeToSky=1*p1.direction*p2.direction;
								p2.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					
					            if(RelativeSpeed<=85)
					            {p2.atk.Stumble=1*(p1.direction*p2.direction);}
					             else if(RelativeSpeed<125)
					            {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					             else
					             {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
			            else
			            {
				             if(p1.cmd.MoveRight==1)
				            {
								if((Distance1_Right_<=40)&&((*i)<=22&&(*i)>16))
								{p2.atk.ComeToSky=1*p1.direction*p2.direction;
								p2.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p2.atk.Stumble=1*p1.direction*p2.direction;}
					              else if(RelativeSpeed<125)
					            {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					             else
					             {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
			 }
		 }
		}
		else if(p2.cmd.Squat==1)//p1ȭ+p2����
		{
			double Distance1_Left_=fabs(p1.LeftArm.GetArmY()-k2*(p1.LeftArm.GetArmX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
            double Distance1_Right_=fabs(p1.RightArm.GetArmY()-k2*(p1.RightArm.GetArmX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
			if((Distance1_Left_<=40&&p1.LeftArm.GetArmY()<p2.p2.y)||(Distance1_Right_<=40&&p1.RightArm.GetArmY()<p2.p2.y))
			{
				if(p1.direction==1&&p2.direction==-1)
                {
					/*p1ȭ���˷���״̬��p2*/
					int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
					p2.PlayersCommandReset();
					(*j)=0;
					p2.PlayersBlood-=RelativeSpeed/10;
					p2.atk.DefendSucceed=1*p1.direction*p2.direction;
				}
	            else if(p1.direction==-1&&p2.direction==1)
                {
					/*p1ȭ���˷���״̬��p2*/
					int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
					p2.PlayersCommandReset();
					(*j)=0;
					p2.PlayersBlood-=RelativeSpeed/10;
					p2.atk.DefendSucceed=1*p1.direction*p2.direction;
				}
				else
				{/*p1ȭ���˾�ֹ״̬�µ�p2*/
                        int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*0);
			            p2.PlayersCommandReset();
			            
			            (*j)=0;
			            if(p1.direction==1)
			            {
				            if(p1.cmd.MoveLeft==1)
				            {
								if((Distance1_Right_<=40)&&((*i)<=22&&(*i)>16))
								{p2.atk.ComeToSky=1*p1.direction*p2.direction;
								p2.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					
					            if(RelativeSpeed<=85)
					            {p2.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
					            {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					             else
					             {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
			            else
			            {
				             if(p1.cmd.MoveRight==1)
				            {
								if((Distance1_Right_<=40)&&((*i)<=22&&(*i)>16))
								{p2.atk.ComeToSky=1*p1.direction*p2.direction;
								p2.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
							 {
								 p2.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p2.atk.Stumble=1*p1.direction*p2.direction;}
					             
								  else if(RelativeSpeed<125)
					            {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					             else
					             {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }			
				}
			}
		}
		else   //p1ȭ+p2�����ң�����
		{
		    double Distance1_Left_=fabs(p1.LeftArm.GetArmY()-k2*(p1.LeftArm.GetArmX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
            double Distance1_Right_=fabs(p1.RightArm.GetArmY()-k2*(p1.RightArm.GetArmX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
			if(Distance1_Left_<=40||Distance1_Right_<=40)
			{/*p1��ȭ������ͨ״̬�µ�p2*/
				int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
			    (*j)=0;
				p2.PlayersCommandReset();
				
				if(p1.direction==1)
			            {
				            if(p1.cmd.MoveLeft==1)
				            {
								if((Distance1_Right_<=40)&&((*i)<=22&&(*i)>16))
								{p2.atk.ComeToSky=1*p1.direction*p2.direction;
								p2.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
					            p2.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p2.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					            else
								{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
			            else
			            {
				             if(p1.cmd.MoveRight==1)
				            {
								if((Distance1_Right_<=40)&&((*i)<=22&&(*i)>16))
								{p2.atk.ComeToSky=1*p1.direction*p2.direction;
								p2.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					 
					             if(RelativeSpeed<=85)
					             {p2.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					             else
								 {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }			

			}
		}
	}
    else if(p1.cmd.Kick==1)//p1kick;
	{
		if(p2.cmd.Hit==1&&p2.cmd.Kick==0)//p1jiao+p2ȭ��
		{
		 double Distance1_Left_=fabs(p1.LeftLeg.GetLegY()-k2*(p1.LeftLeg.GetLegX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
         double Distance1_Right_=fabs(p1.RightLeg.GetLegY()-k2*(p1.RightLeg.GetLegX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2); 
		 double Distance2_Left_=fabs(p2.LeftArm.GetArmY()-k1*(p2.LeftArm.GetArmX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
		 double Distance2_Right_=fabs(p2.RightArm.GetArmY()-k1*(p2.RightArm.GetArmX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
		 if((Distance1_Left_<=40&&p1.LeftLeg.GetLegY()<p2.p2.y)||(Distance1_Right_<=40&&p1.RightLeg.GetLegY()<p2.p2.y))/*p1��jiao������p2*/
		 {
			 int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
			 p2.PlayersCommandReset();
			 
			 (*j)=0;
			 if(p1.direction==1)
			 {
				 if(p1.cmd.MoveRight==1)
				 {
					 if((*i)>=0&&(*i)<6)
					 {p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;
					 p2.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					 p2.PlayersBlood-=RelativeSpeed/10;
					
					 if(RelativeSpeed<=85)
					 {p2.atk.Stumble=1*(p1.direction*p2.direction);}
						else if(RelativeSpeed<125)
					    {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					     else
					    {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				 }
			 }
			 else
			 {
				 if(p1.cmd.MoveLeft==1)
				 {
					 
					 if((*i)>=0&&(*i)<6)
					{p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;
					 p2.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					 p2.PlayersBlood-=RelativeSpeed/10;
					 if(RelativeSpeed<=85)
					 {p2.atk.Stumble=1*p1.direction*p2.direction;}
					 else if(RelativeSpeed<125)
					    {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					     else
					    {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				 }
			 }
		 
		 
		 }
		 if((Distance2_Left_<=40&&p2.LeftArm.GetArmY()<p1.p2.y)||(Distance2_Right_<=40&&p2.RightArm.GetArmY()<p1.p2.y))/*p2��ȭ������p1*/
		 {
			 int RelativeSpeed=p2.ActionSpeed-(p2.direction*p1.direction*p1.MoveSpeed);
			 p1.PlayersCommandReset();
			
			 (*i)=0;
			 if(p2.direction==1)
			 {
				 if(p2.cmd.MoveLeft==1)
				 {
					 if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
					 {p1.atk.ComeToSky=1*p1.direction*p2.direction;
					 p1.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					  p1.PlayersBlood-=RelativeSpeed/10;
					 if(RelativeSpeed<=85)
					 {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					 else if(RelativeSpeed<125)
					 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					 else
					 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				 }
			 }
			 else
			 {
				 if(p2.cmd.MoveRight==1)
				 {
					 if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
					 {p1.atk.ComeToSky=1*p1.direction*p2.direction;
					 p1.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					  p1.PlayersBlood-=RelativeSpeed/10;
					 
					 if(RelativeSpeed<=85)
					 {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					 else if(RelativeSpeed<125)
				     {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					 else
					 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				 }
			 }
		  }

 		}
	else if(p2.cmd.Kick==1)//p1jiao+p2�ţ�
		{
	     double Distance1_Left_=fabs(p1.LeftLeg.GetLegY()-k2*(p1.LeftLeg.GetLegX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
         double Distance1_Right_=fabs(p1.RightLeg.GetLegY()-k2*(p1.RightLeg.GetLegX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2); 
		 double Distance2_Left_=fabs(p2.LeftLeg.GetLegY()-k1*(p2.LeftLeg.GetLegX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
		 double Distance2_Right_=fabs(p2.RightLeg.GetLegY()-k1*(p2.RightLeg.GetLegX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
 		 if((Distance1_Left_<=40&&p1.LeftLeg.GetLegY()<p2.p2.y)||(Distance1_Right_<=40&&p1.RightLeg.GetLegY()<p2.p2.y))///*p1��jiao������p2*/
		 {   
			 int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
			 p2.PlayersCommandReset();
			
			 (*j)=0;
			 if(p1.direction==1)
			 {
				 if(p1.cmd.MoveRight==1)
				 {
					 if((*i)<=6)
					 {p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;
					 p2.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					 p2.PlayersBlood-=RelativeSpeed/10;
					 if(RelativeSpeed<=85)
					 {p2.atk.Stumble=1*(p1.direction*p2.direction);}
					 else if(RelativeSpeed<125)
					 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					 else
					 {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				 }
			 }
			 else
			 {
				 if(p1.cmd.MoveLeft==1)
				 {
					 if((*i)<=6)
					  {p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;
					 p2.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					  p2.PlayersBlood-=RelativeSpeed/10;
					 
					 if(RelativeSpeed<=85)
					 {p2.atk.Stumble=1*p1.direction*p2.direction;}
					 else if(RelativeSpeed<125)
					 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					 else
					 {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				 }
			 }
		 }
		 if((Distance2_Left_<=40&&p2.LeftLeg.GetLegY()<p1.p2.y)||(Distance2_Right_<=40&&p2.RightLeg.GetLegY()<p1.p2.y))
			 /*p2�ýŻ�����p1*/
		 {
			 int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
			 p1.PlayersCommandReset();
			
			 (*i)=0;
			 if(p2.direction==1)
			 {
				 
				 if(p2.cmd.MoveRight==1)
				 {
					 if((*j)<=6)
					 {p1.atk.DoubleHurt=1*p1.p1.x-p2.p1.x;
					 p1.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					  p1.PlayersBlood-=RelativeSpeed/10;
					 if(RelativeSpeed<=85)
					 {p1.atk.Stumble=p1.direction*p2.direction;}
					 else if(RelativeSpeed<125)
					 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					 else
					 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				 }
			 }
			 else
			 {
				 
				 if(p2.cmd.MoveLeft==1)
				 {
					 if((*j)<=6)
					 {p1.atk.DoubleHurt=1*p1.p1.x-p2.p1.x;
					 p1.PlayersBlood-=RelativeSpeed/10;}
				 }
				 else
				 {
					  p1.PlayersBlood-=RelativeSpeed/10;
					 if(RelativeSpeed<=85)
					 {p1.atk.Stumble=p1.direction*p2.direction;}
					else if(RelativeSpeed<125)
					 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					 else
					 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				 
				 }
			 }
		 }
		}
		else if(p2.cmd.RemoteAttack==1)//p1jiao+p2Զ�̣�
		{
		 double Distance1_Left_=fabs(p1.LeftLeg.GetLegY()-k2*(p1.LeftLeg.GetLegX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
         double Distance1_Right_=fabs(p1.RightLeg.GetLegY()-k2*(p1.RightLeg.GetLegX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
		 if(p2.MyDart==NULL)//p2���У�
		 {
			 if((*j)>=31&&(*j)<45)//p2�����ѷ�����
		     {
				 int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
			    if(p2.p1.x>p1.p1.x&&p2.direction==-1)
		        {
					/*p2���д���p1*/
					p1.PlayersBlood-=RelativeSpeed/10;			
					p1.atk.AlmostDie=1*p1.direction*p2.direction;
					p1.PlayersCommandReset();
					(*i)=0;
				}
		        else if(p2.p1.x<p1.p1.x&&p2.direction==1)
		        {
					/*p2���д���p1*/
					p1.PlayersBlood-=RelativeSpeed/10;			
					p1.atk.AlmostDie=1*p1.direction*p2.direction;
					p1.PlayersCommandReset();
					(*i)=0;
				}
				else
				{
					/*p1jiao��p2*/
					if((Distance1_Left_<=40&&p1.LeftLeg.GetLegY()<p2.p2.y)||(Distance1_Right_<=40&&p1.RightLeg.GetLegY()<p2.p2.y))
				    {
						int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
			            p2.PlayersCommandReset();
			            
			            (*j)=0;
			            if(p1.direction==1)
			            {
				            if(p1.cmd.MoveRight==1)
				            {
								if((*i)<=6)
								{p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;
								p2.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
					            p2.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p2.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					            else
								{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
			            else
			            {
				             if(p1.cmd.MoveLeft==1)
				            {
								
								if((*i)<=6)
								{p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;
								p2.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p2.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					             else
								 {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			            }
						
					 }
				}
		     }
			 else//p2����δ������
			 {
				if((Distance1_Left_<=40&&p1.LeftLeg.GetLegY()<p2.p2.y)||(Distance1_Right_<=40&&p1.RightLeg.GetLegY()<p2.p2.y))
				{
					/*p1��jiao����p2*/
				        int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
			            p2.PlayersCommandReset();
			            p2.PlayersBlood-=RelativeSpeed/10;
			            (*j)=0;
			            if(p1.direction==1)
			            {
				            if(p1.cmd.MoveRight==1)
				            {
								if((*i)<=6)
								{p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;
								p2.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					
					            if(RelativeSpeed<=85)
					            {p2.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					            else
								{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
			            else
			            {
				             if(p1.cmd.MoveLeft==1)
				            {
								
								if((*i)<=6)
								{p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;
								p2.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p2.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					             else
								 {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
				  }	

			 }
		 }
		 else//p2���ڣ�
		 {
			 double Distance2_Dart_=fabs(p2.MyDart->GetDartY()-k1*(p2.MyDart->GetDartX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
			 if(Distance2_Dart_<=100)
			 {
				 /*p2���ڴ���p1*/
				 int RelativeSpeed=50-(p1.direction*p2.direction*p1.MoveSpeed);
				 p1.PlayersCommandReset();
				 p1.PlayersBlood-=RelativeSpeed/10;
				 (*i)=0;
				 if(RelativeSpeed<=85)
			     {p1.atk.Stumble=1*p1.direction*p2.direction;}
				 else if(RelativeSpeed<125)
				 {p1.atk.GetKnockedDown=1*p1.direction*p2.direction;}
				 else
				 {p1.atk.GetKickedFlew=1*p1.direction*p2.direction;}
			 }
			 if((Distance1_Left_<=40&&p1.LeftLeg.GetLegY()<p2.p2.y)||(Distance1_Right_<=40&&p1.RightLeg.GetLegY()<p2.p2.y))/*p1��jiao����p2*/
			 {
				        int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
			            p2.PlayersCommandReset();
			            
			            (*j)=0;
			            if(p1.direction==1)
			            {
				            if(p1.cmd.MoveRight==1)
				            {
								if((*i)<=6)
								{p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;
								p2.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p2.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					            else
								{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
			            else
			            {
				             if(p1.cmd.MoveLeft==1)
				            {
								
								if((*i)<=6)
								{p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;
								p2.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p2.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					             else
								 {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
			 }
		 }
		}
		else if(p2.cmd.Squat==1)//p1jiao+p2����
		{
			double Distance1_Left_=fabs(p1.LeftLeg.GetLegY()-k2*(p1.LeftLeg.GetLegX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
            double Distance1_Right_=fabs(p1.RightLeg.GetLegY()-k2*(p1.RightLeg.GetLegX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
			if((Distance1_Left_<=40&&p1.LeftLeg.GetLegY()<p2.p2.y)||(Distance1_Right_<=40&&p1.RightLeg.GetLegY()<p2.p2.y))
			{
				if(p1.direction==1&&p2.direction==-1)
                {
					/*p1jiao���˷���״̬��p2*/
					int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
					p2.PlayersCommandReset();
					(*j)=0;
					p2.PlayersBlood-=RelativeSpeed/10;
					p2.atk.DefendSucceed=1*p1.direction*p2.direction;
				}
	            else if(p1.direction==-1&&p2.direction==1)
                {
					/*p1jiao���˷���״̬��p2*/
					int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
					p2.PlayersCommandReset();
					(*j)=0;
					p2.PlayersBlood-=RelativeSpeed/10;
					p2.atk.DefendSucceed=1*p1.direction*p2.direction;
				}
				else
				{/*p1jiao���˾�ֹ״̬�µ�p2*/
                        int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*0);
			            p2.PlayersCommandReset();
			            p2.PlayersBlood-=RelativeSpeed/10;
			            (*j)=0;
			            if(p1.direction==1)
			            {
				            if(p1.cmd.MoveRight==1)
				            {
								
								if((*i)<=6)
								{p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;
								p2.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p2.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					            else
								{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
			            else
			            {
				             if(p1.cmd.MoveLeft==1)
				            {
								
								if((*i)<=6)
								{p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;;
								p2.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p2.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					             else
								 {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }			
				}
			}
		}
		else   //p1jiao+p2�����ң�����
		{
		    double Distance1_Left_=fabs(p1.LeftLeg.GetLegY()-k2*(p1.LeftLeg.GetLegX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
            double Distance1_Right_=fabs(p1.RightLeg.GetLegY()-k2*(p1.RightLeg.GetLegX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
			if(Distance1_Left_<=40||Distance1_Right_<=40)
			{/*p1��jiao������ͨ״̬�µ�p2*/
				int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
				(*j)=0;
				p2.PlayersCommandReset();
				
				if(p1.direction==1)
			            {
				            if(p1.cmd.MoveRight==1)
				            {
								if((*i)<=6)
								{p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;;
								p2.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p2.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					            else
								{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }
			            else
			            {
				             if(p1.cmd.MoveLeft==1)
				            {
								
								if((*i)<=6)
								{p2.atk.DoubleHurt=1*p2.p1.x-p1.p1.x;
								p2.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p2.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p2.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
					            else
								{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
				             }
			             }			

			}
		}
	}
	    else if(p1.cmd.RemoteAttack==1)//p1Զ
	    { 
		if(p2.cmd.Hit==1&&p2.cmd.Kick==0)//p1Զ��+p2ȭ
		{
		 double Distance2_Left_=fabs(p2.LeftArm.GetArmY()-k1*(p2.LeftArm.GetArmX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
         double Distance2_Right_=fabs(p2.RightArm.GetArmY()-k1*(p2.RightArm.GetArmX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
		 if(p1.MyDart==NULL)//p1���У�
		 {
			 if((*i)>=31&&(*i)<45)//p1�����ѷ�����
		     {
				 int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
			    if(p1.p1.x>p2.p1.x&&p1.direction==-1)
		        {
					/*p1���д���p2*/
					p2.PlayersBlood-=RelativeSpeed/10;			
					p2.atk.AlmostDie=1*p1.direction*p2.direction;
					p2.PlayersCommandReset();
					(*j)=0;
				}
		        else if(p1.p1.x<p2.p1.x&&p1.direction==1)
		        {
					/*p1���д���p2*/
					p2.PlayersBlood-=RelativeSpeed/10;			
					p2.atk.AlmostDie=1*p1.direction*p2.direction;
					p2.PlayersCommandReset();
					(*j)=0;
				}
				else
				{
					/*p2quan��p1*/
					if((Distance2_Left_<=40&&p2.LeftArm.GetArmY()<p1.p2.y)||(Distance2_Right_<=40&&p2.RightArm.GetArmY()<p1.p2.y))
				    {
						int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
			            p1.PlayersCommandReset();
			            
			            (*i)=0;
			            if(p2.direction==1)
			            {
				            if(p2.cmd.MoveLeft==1)
				            {
								if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
					           {p1.atk.ComeToSky=1*p1.direction*p2.direction;
					            p1.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					            else
								{p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }
			            else
			            {
				             if(p2.cmd.MoveRight==1)
				            {
								
								if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
					           {p1.atk.ComeToSky=1*p1.direction*p2.direction;
					            p1.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								 p1.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p1.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					             else
								 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			            }
						
					 }
				}
		     }
			 else//p1����δ������
			 {
				     if(Distance2_Left_<=40||Distance2_Right_<=40)
				     {
					   
						int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
			            p1.PlayersCommandReset();
			            p1.PlayersBlood-=RelativeSpeed/10;
			            (*i)=0;
			            if(p2.direction==1)
			            {
				            if(p2.cmd.MoveLeft==1)
				            {
								
								if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
					           {p1.atk.ComeToSky=1*p1.direction*p2.direction;
					            p1.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					            else
								{p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }
					 
			            else
			            {
				             if(p2.cmd.MoveRight==1)
				            {
								
								if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
					           {p1.atk.ComeToSky=1*p1.direction*p2.direction;
					            p1.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p1.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					             else
								 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			            }
					 }
						
					}
				}		 
			 
		 
		 else//p1���ڣ�
		 {
			 double Distance1_Dart_=fabs(p1.MyDart->GetDartY()-k2*(p1.MyDart->GetDartX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
			 if(Distance1_Dart_<=40)
			 {/*p1���ڴ���p2*/
				 int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
				 p2.PlayersCommandReset();
				 p2.PlayersBlood-=RelativeSpeed/10;
				 (*j)=0;
				 if(RelativeSpeed<=85)
			     {p2.atk.Stumble=1*p1.direction*p2.direction;}
				 else if(RelativeSpeed<125)
				 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
				 else
				 {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
			 }
			 if(Distance2_Left_<=40||Distance2_Right_<=40)
			 {/*p2quan��p1*/
					if((Distance2_Left_<=40&&p2.LeftArm.GetArmY()<p1.p2.y)||(Distance2_Right_<=40&&p2.RightArm.GetArmY()<p1.p2.y))
				    {
						int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
			            p1.PlayersCommandReset();
			            
			            (*i)=0;
			            if(p2.direction==1)
			            {
				            if(p2.cmd.MoveLeft==1)
				            {
								if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
					           {p1.atk.ComeToSky=1*p1.direction*p2.direction;
					            p1.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					            else
								{p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }
			            else
			            {
				             if(p2.cmd.MoveRight==1)
				            {
								
								if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
					           {p1.atk.ComeToSky=1*p1.direction*p2.direction;
					            p1.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					 
					             if(RelativeSpeed<=85)
					             {p1.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					             else
								 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			            }
						
					 }
			 }
		 }
		}
		else if(p2.cmd.Kick==1)//p1Զ��+p2�ţ�
	{
		 double Distance2_Left_=fabs(p2.LeftLeg.GetLegY()-k1*(p2.LeftLeg.GetLegX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
         double Distance2_Right_=fabs(p2.RightLeg.GetLegY()-k1*(p2.RightLeg.GetLegX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
		 if(p1.MyDart==NULL)//p1���У�
		 {
			 if((*i)>=31&&(*i)<45)//p1�����ѷ�����
		     {
				 int RelativeSpeed=p1.ActionSpeed-(p1.direction*p2.direction*p2.MoveSpeed);
			    if(p1.p1.x>p2.p1.x&&p1.direction==-1)
		        {
					/*p1���д���p2*/
					p2.PlayersBlood-=RelativeSpeed/10;			
					p2.atk.AlmostDie=1*p1.direction*p2.direction;
					p2.PlayersCommandReset();
					(*j)=0;
				}
		        else if(p1.p1.x<p2.p1.x&&p1.direction==1)
		        {
					/*p1���д���p2*/
					p2.PlayersBlood-=RelativeSpeed/10;			
					p2.atk.AlmostDie=1*p1.direction*p2.direction;
					(*j)=0;
					p2.PlayersCommandReset();
				}
				else
				{
					/*p2jiao��p1*/
					if((Distance2_Left_<=40&&p2.LeftLeg.GetLegY()<p1.p2.y)||(Distance2_Right_<=40&&p2.RightLeg.GetLegY()<p1.p2.y))
				    {
						int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
			            p1.PlayersCommandReset();
			            
			            (*i)=0;
			            if(p2.direction==1)
			            {
				            if(p2.cmd.MoveRight==1)
				            {
								if((*j)<=6)
								{p1.atk.DoubleHurt=1*p1.p1.x-p2.p1.x;
								p1.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					            else
								{p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }
			            else
			            {
				             if(p2.cmd.MoveLeft==1)
				            {
								
								if((*j)<=6)
								{p1.atk.DoubleHurt=1*p1.p1.x-p2.p1.x;
								p1.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p1.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					             else
								 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			            }
						
					 }
				}
		     }
			 else//p1����δ������
			 {
				     if(Distance2_Left_<=40||Distance2_Right_<=40)
				     {
					   
						int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
			            p1.PlayersCommandReset();
			            
			            (*i)=0;
			            if(p2.direction==1)
			            {
				            if(p2.cmd.MoveRight==1)
				            {
								if((*j)<=6)
								{p1.atk.DoubleHurt=1*p1.p1.x-p2.p1.x;
								p1.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					            else
								{p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }
					 
			            else
			            {
				             if(p2.cmd.MoveLeft==1)
				            {
								
								if((*j)<=6)
								{p1.atk.DoubleHurt=1*p1.p1.x-p2.p1.x;
								p1.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p1.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					             else
								 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			            }
					 }
						
					}
				}		 
			 
		 
		 else//p1���ڣ�
		 {
			 double Distance1_Dart_=fabs(p1.MyDart->GetDartY()-k2*(p1.MyDart->GetDartX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
			 if(Distance1_Dart_<=40)
			 {
				 /*p1���ڴ���p2*/
				 int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
				 p2.PlayersCommandReset();
				 p2.PlayersBlood-=RelativeSpeed/10;
				 (*j)=0;
				 if(RelativeSpeed<=85)
			     {p2.atk.Stumble=1*p1.direction*p2.direction;}
				 else if(RelativeSpeed<125)
				 {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
				 else
				 {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
			 }
			 if(Distance2_Left_<=40||Distance2_Right_<=40)
			 {/*p2quan��p1*/
					if((Distance2_Left_<=40&&p2.LeftArm.GetArmY()<p1.p2.y)||(Distance2_Right_<=40&&p2.RightArm.GetArmY()<p1.p2.y))
				    {
						int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
			            p1.PlayersCommandReset();
			           
			            (*i)=0;
			            if(p2.direction==1)
			            {
				            if(p2.cmd.MoveLeft==1)
				            {
								if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
								{p1.atk.ComeToSky=1*p1.direction*p2.direction;
								p1.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								 p1.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					            else
								{p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }
			            else
			            {
				             if(p2.cmd.MoveRight==1)
				            {
								
								if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
								{p1.atk.ComeToSky=1*p1.direction*p2.direction;
								p1.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p1.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					             else
								 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			            }
						
					 }
			 }
		 }
	}
		else if(p2.cmd.RemoteAttack==1)//p1Զ��+p2Զ�̣�
		{
			if(p1.MyDart==NULL&&p2.MyDart==NULL)//p1����+p2���У�
			{
				if((*i)>=31&&(*i)<45)//p1�����ѷ�����
				{
					if((*j)>=31&&(*j)<45)//p1����+p2���У�
					{
						if(p1.direction==1)
						{
							if(p2.direction==1)
							{
								if(p1.p1.x>p2.p1.x)
								{/*p2���д���p1*/
					               p1.PlayersBlood-=500/10;
								   p1.PlayersCommandReset();
								   (*i)=0;
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;}
								else
								{
									/*p1���д���p2*/
					               p2.PlayersBlood-=500/10;
								   p2.PlayersCommandReset();
								   (*j)=0;
					               p2.atk.AlmostDie=1*p1.direction*p2.direction;
								}
							
							}
							else
							{
								if(p1.p1.x>p2.p1.x)
								{/*����ͬʱ�ſ�*/}
								else
								{
								   p1.PlayersBlood-=500/10;			
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;
								   p1.PlayersCommandReset();
								   (*i)=0;
								   p2.PlayersBlood-=500/10;			
					               p2.atk.AlmostDie=1*p1.direction*p2.direction;
								   p2.PlayersCommandReset();
								   (*j)=0;
								}
							
							}
						
						}
						else
						{
							if(p2.direction==1)
							{
								if(p1.p1.x>p2.p1.x)
								{
								    p1.PlayersBlood-=500/10;			
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;
								   p1.PlayersCommandReset();
								   (*i)=0;
								   p2.PlayersBlood-=500/10;			
					               p2.atk.AlmostDie=1*p1.direction*p2.direction;
								   p2.PlayersCommandReset();
								   (*j)=0;
								}
								else
								{/*����ͬʱ�ſ�*/}
							
							}
							else
							{
								if(p1.p1.x>p2.p1.x)
								{/*p1���д���p2*/
					               p2.PlayersBlood-=500/10;	
								   p2.PlayersCommandReset();
					               p2.atk.AlmostDie=1*p1.direction*p2.direction;
								   (*j)=0;
								}
								else
								{
									p1.PlayersBlood-=500/10;			
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;
								   p1.PlayersCommandReset();
								   (*i)=0;
								}
							
							}
						}
					  
					}
					else//p1����+��ͨ״̬p2��
					{
						if(p2.p1.x>p1.p1.x)
						{
							if(p1.direction==1)
							{/*p1���д򵽾�ֹ״̬p2*/
							       p2.PlayersBlood-=500/10;	
								   p2.PlayersCommandReset();
					               p2.atk.AlmostDie=1*p1.direction*p2.direction;
								   (*j)=0;
							}
							else
							{/*p1���зſ�*/}
						}
						else
						{
							if(p1.direction==-1)
							{/*p1���д򵽾�ֹ״̬p2*/
							       p2.PlayersBlood-=500/10;	
								   p2.PlayersCommandReset();
					               p2.atk.AlmostDie=1*p1.direction*p2.direction;
								   (*j)=0;
							}
							else
							{/*p1���зſ�*/}
						}
				    }
				}
				else//p1����δ������
				{
					if((*j)>=31&&(*j)<45)//p2����+p1��ֹ��
					{
						if(p1.direction==1)
						{
							if(p2.direction==1)
							{
								if(p1.p1.x>p2.p1.x)
								{/*p2���д��˾�ֹ״̬��p1*/
								   p1.PlayersBlood-=500/10;			
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;
								   p1.PlayersCommandReset();
								   (*i)=0;
								}
								else
								{/*p2���зſ�*/}
							
							}
							else
							{
								if(p1.p1.x>p2.p1.x)
								{/*p2���зſ�*/}
								else
								{
								   p1.PlayersBlood-=500/10;			
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;
								   p1.PlayersCommandReset();
								   (*i)=0;
								}
							
							}
						
						}
						else
						{
							if(p2.direction==1)
							{
								if(p1.p1.x>p2.p1.x)
								{/*p2���л���p1*/
								   p1.PlayersBlood-=500/10;			
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;
								   p1.PlayersCommandReset();
								   (*i)=0;
								}
								else
								{/*p2���зſ�*/}
							
							}
							else
							{
								if(p1.p1.x>p2.p1.x)
								{/*p2���д��˾�ֹ״̬��p1*/
								   p1.PlayersBlood-=500/10;			
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;
								   p1.PlayersCommandReset();
								   (*i)=0;
								}
								else
								{/*p2���зſ�*/}
							
							}
						}
					
					}
					else//p1,p2���ж�δ������
					{/*����*/}
				}
			}
			else if(p1.MyDart!=NULL&&p2.MyDart!=NULL)//p1��+p2�ڣ�
			{
				double Distance1_Dart_=fabs(p1.MyDart->GetDartY()-k2*(p1.MyDart->GetDartX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
				double Distance2_Dart_=fabs(p2.MyDart->GetDartY()-k1*(p2.MyDart->GetDartX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
				if(p1.direction==1)
				{
					if(p2.direction==1)
					{
						if(p1.p1.x<p2.p1.x)
						{
							if(Distance1_Dart_<=40)
							{/*p1�ڵ���p2*/
							
				             int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
				             p2.PlayersCommandReset();
				             p2.PlayersBlood-=RelativeSpeed/10;
				             (*j)=0;
				             if(RelativeSpeed<=85)
			                 {p2.atk.Stumble=1*p1.direction*p2.direction;}
				             else if(RelativeSpeed<125)
				             {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
				             else
				             {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
							}
						}
						else
						{
							if(Distance2_Dart_<=40)
							{
							/*p2���ڴ���p1*/
				             int RelativeSpeed=50-(p1.direction*p2.direction*p1.MoveSpeed);
				             p1.PlayersCommandReset();
				             p1.PlayersBlood-=RelativeSpeed/10;
				             (*i)=0;
				             if(RelativeSpeed<=85)
			                 {p1.atk.Stumble=1*p1.direction*p2.direction;}
				             else if(RelativeSpeed<125)
				             {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
				             else
				             {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
							 }
						
						}
					}
					else
					{
						if(p1.p1.x<p2.p1.x)
						{
							if(Distance1_Dart_<=40)
							{/*p1�ڵ���p2*/
							int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
				             p2.PlayersCommandReset();
				             p2.PlayersBlood-=RelativeSpeed/10;
				             (*j)=0;
				             if(RelativeSpeed<=85)
			                 {p2.atk.Stumble=1*p1.direction*p2.direction;}
				             else if(RelativeSpeed<125)
				             {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
				             else
				             {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
							}
							if(Distance2_Dart_<=40)
							{/*p2�ڵ���p1*/
							int RelativeSpeed=50-(p1.direction*p2.direction*p1.MoveSpeed);
				             p1.PlayersCommandReset();
				             p1.PlayersBlood-=RelativeSpeed/10;
				             (*i)=0;
				             if(RelativeSpeed<=85)
			                 {p1.atk.Stumble=1*p1.direction*p2.direction;}
				             else if(RelativeSpeed<125)
				             {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
				             else
				             {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
							}
						}
						else
						{
							
							/*�����ɣ�˭���򲻵���*/
						
						}
					}
				}
				else
				{
					if(p2.direction==1)
					{
						if(p1.p1.x<p2.p1.x)
						{
							/*�����ɣ�˭���򲻵���*/
							
						}
						else
						{
							
							if(Distance1_Dart_<=40)
							{
								int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
				             p2.PlayersCommandReset();
				             p2.PlayersBlood-=RelativeSpeed/10;
				             (*j)=0;
				             if(RelativeSpeed<=85)
			                 {p2.atk.Stumble=1*p1.direction*p2.direction;}
				             else if(RelativeSpeed<125)
				             {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
				             else
				             {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
							}
							if(Distance2_Dart_<=40)
							{
							 int RelativeSpeed=50-(p1.direction*p2.direction*p1.MoveSpeed);
				             p1.PlayersCommandReset();
				             p1.PlayersBlood-=RelativeSpeed/10;
				             (*i)=0;
				             if(RelativeSpeed<=85)
			                 {p1.atk.Stumble=1*p1.direction*p2.direction;}
				             else if(RelativeSpeed<125)
				             {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
				             else
				             {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}/*p2�ڵ���p1*/
							}
						
						}

					}
					else
					{
						if(p1.p1.x<p2.p1.x)
						{
							if(Distance2_Dart_<=40)
							{/*p2�ڵ���p1*/
							int RelativeSpeed=50-(p1.direction*p2.direction*p1.MoveSpeed);
				             p1.PlayersCommandReset();
				             p1.PlayersBlood-=RelativeSpeed/10;
				             (*i)=0;
				             if(RelativeSpeed<=85)
			                 {p1.atk.Stumble=1*p1.direction*p2.direction;}
				             else if(RelativeSpeed<125)
				             {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
				             else
				             {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
							}
							if(Distance1_Dart_<=40)
							{/*p1�ڵ���p2*/
							int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
				             p2.PlayersCommandReset();
				             p2.PlayersBlood-=RelativeSpeed/10;
				             (*j)=0;
				             if(RelativeSpeed<=85)
			                 {p2.atk.Stumble=1*p1.direction*p2.direction;}
				             else if(RelativeSpeed<125)
				             {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
				             else
				             {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
							}
						}
						else
						{
							if(Distance1_Dart_<=40)
							{/*p1�ڵ���p2*/
							int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
				             p2.PlayersCommandReset();
				             p2.PlayersBlood-=RelativeSpeed/10;
				             (*j)=0;
				             if(RelativeSpeed<=85)
							 {p2.atk.Stumble=1*p2.direction*p1.direction;}
				             else if(RelativeSpeed<125)
				             {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
				             else
				             {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
							}
						
						}

					}
				}
}
			else//p1,p2һ������һ���ڣ�
			{
				if(p1.MyDart==NULL&&p2.MyDart!=NULL)
				{/*p1����p2��*/
					double Distanse2_Dart_=fabs(p2.MyDart->GetDartY()-k1*(p2.MyDart->GetDartX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
					if((*i)>=31&&(*i)<45)
					{
						if(p1.direction==1)
						{
							if(p1.p1.x<p2.p1.x)
							{/*p1���л���p2*/
							       p2.PlayersBlood-=500/10;	
								   p2.PlayersCommandReset();
					               p2.atk.AlmostDie=1*p1.direction*p2.direction;
								   (*j)=0;
							}
							else
							{
								if(p2.direction==1)
								{
									if(Distanse2_Dart_<=40)
									{/*p2���ڻ��о�ֹp1*/
									int RelativeSpeed=50-(p1.direction*p2.direction*p1.MoveSpeed);
				                    p1.PlayersCommandReset();
				                    p1.PlayersBlood-=RelativeSpeed/10;
				                    (*i)=0;
				                    if(RelativeSpeed<=85)
			                        {p1.atk.Stumble=1*p1.direction*p2.direction;}
				                     else if(RelativeSpeed<125)
				                     {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
				                     else
				                     {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
									}
								}
								else
								{/*����*/}
							
							}
						}
						else
						{
							if(p1.p1.x>p2.p1.x)
							{/*p1���л���p2*/
							       p2.PlayersBlood-=500/10;	
								   p2.PlayersCommandReset();
					               p2.atk.AlmostDie=1*p1.direction*p2.direction;
								   (*j)=0;
							}
							else
							{
								if(p2.direction==-1)
								{
									if(Distanse2_Dart_<=40)
									{/*p2���ڻ��о�ֹp1*/
									int RelativeSpeed=50-(p1.direction*p2.direction*p1.MoveSpeed);
				                    p1.PlayersCommandReset();
				                    p1.PlayersBlood-=RelativeSpeed/10;
				                    (*i)=0;
				                    if(RelativeSpeed<=85)
			                        {p1.atk.Stumble=1*p1.direction*p2.direction;}
				                     else if(RelativeSpeed<125)
				                     {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
				                     else
				                     {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
									}
								}
								else
								{/*����*/}
							
							}
						}
					}
					else
					{
						if(p2.direction==1)
						{
							if(p2.p1.x<p1.p1.x)
							{
								if(Distanse2_Dart_<=40)
								{/*p2���ڻ��о�ֹp1*/
								    int RelativeSpeed=50-(p1.direction*p2.direction*p1.MoveSpeed);
				                    p1.PlayersCommandReset();
				                    p1.PlayersBlood-=RelativeSpeed/10;
				                    (*i)=0;
				                    if(RelativeSpeed<=85)
			                        {p1.atk.Stumble=1*p1.direction*p2.direction;}
				                     else if(RelativeSpeed<125)
				                     {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
				                     else
				                     {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
								}
							}
							else
							{/*����*/}
						}
						else
						{
							if(p2.p1.x>p1.p1.x)
							{
								if(Distanse2_Dart_<=40)
								{/*p2���ڻ��о�ֹp1*/
								    int RelativeSpeed=50-(p1.direction*p2.direction*p1.MoveSpeed);
				                    p1.PlayersCommandReset();
				                    p1.PlayersBlood-=RelativeSpeed/10;
				                    (*i)=0;
				                    if(RelativeSpeed<=85)
			                        {p1.atk.Stumble=1*p1.direction*p2.direction;}
				                     else if(RelativeSpeed<125)
				                     {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
				                     else
				                     {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
								}
							}
							else
							{/*����*/}
						}
					}
				
				}
				else
				{
					double Distanse1_Dart_=fabs(p1.MyDart->GetDartY()-k2*(p1.MyDart->GetDartX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
					if((*j)>=31&&(*j)<45)
					{
						if(p2.direction==1)
						{
							if(p2.p1.x<p1.p1.x)
							{/*p2���л���p1*/
							   p1.PlayersBlood-=500/10;			
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;
								   p1.PlayersCommandReset();
								   (*i)=0;
							}
							else
							{
								if(p1.direction==1)
								{
									if(Distanse1_Dart_<=40)
									{/*p1���ڻ��о�ֹp2*/
									int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
				                    p2.PlayersCommandReset();
				                    p2.PlayersBlood-=RelativeSpeed/10;
				                   (*j)=0;
				                    if(RelativeSpeed<=85)
			                       {p2.atk.Stumble=1*p1.direction*p2.direction;}
				                   else if(RelativeSpeed<125)
				                   {p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
				                   else
				                    {p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
									}
								}
								else
								{/*����*/}
							
							}
						}
						else
						{
							if(p2.p1.x>p1.p1.x)
							{/*p2���л���p1*/
							         p1.PlayersBlood-=500/10;			
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;
								   p1.PlayersCommandReset();
								   (*i)=0;
							}
							else
							{
								if(p1.direction==-1)
								{
									if(Distanse1_Dart_<=40)
									{/*p1���ڻ��о�ֹp2*/
									int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
				                    p2.PlayersCommandReset();
				                    p2.PlayersBlood-=RelativeSpeed/10;
				                    (*j)=0;
				                    if(RelativeSpeed<=85)
			                        {p2.atk.Stumble=1*p1.direction*p2.direction;}
									else if(RelativeSpeed<125)
									{p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
									else
									{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
									}
								}
								else
								{/*����*/}
							
							}
						}
					}
					else
					{
						if(p1.direction==1)
						{
							if(p1.p1.x<p2.p1.x)
							{
								if(Distanse1_Dart_<=40)
								{/*p1���ڻ��о�ֹp2*/
								int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
								p2.PlayersCommandReset();
								p2.PlayersBlood-=RelativeSpeed/10;
								(*j)=0;
								if(RelativeSpeed<=85)
								{p2.atk.Stumble=1*p1.direction*p2.direction;}
								else if(RelativeSpeed<125)
								{p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
								else
								{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
								}
							}
							else
							{/*����*/}
						}
						else
						{
							if(p1.p1.x>p2.p1.x)
							{
								if(Distanse1_Dart_<=40)
								{/*p1���ڻ��о�ֹp2*/
								int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
								p2.PlayersCommandReset();
								p2.PlayersBlood-=RelativeSpeed/10;
								(*j)=0;
								if(RelativeSpeed<=85)
								{p2.atk.Stumble=1*p1.direction*p2.direction;}
								else if(RelativeSpeed<125)
								{p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
								else
								{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
								}
							}
							else
							{/*����*/}
						}
					}/*p2����p1��*/
				}
			
			}
		
		
		}
		else if(p2.cmd.Squat==1)//p1Զ��+p2������
		{
			if(p1.MyDart==NULL)//p1���У�
			{
				if((*i)>=31&&(*i)<=45)
				{
					if(p1.direction==1)
					{
						if(p1.p1.x<p2.p1.x)
						{
							if(p2.direction==-1)
							{/*p2�ڷ���״̬�����л���*/
							       p2.PlayersBlood-=350/10;
								   p2.PlayersCommandReset();
								   (*j)=0;
					               p2.atk.DefendSucceed=1*p1.direction*p2.direction;
							}
							else
							{/*p2�ھ�ֹ״̬�����л���*/
							         p2.PlayersBlood-=500/10;			
					               p2.atk.AlmostDie=1*p1.direction*p2.direction;
								   p2.PlayersCommandReset();
								   (*j)=0;
							}
						}
						else
						{/*����*/}
					}
					else
					{
						if(p1.p1.x>p2.p1.x)
						{
							if(p2.direction==1)
							{/*p2�ڷ���״̬�����л���*/
							  p2.PlayersBlood-=350/10;
								   p2.PlayersCommandReset();
								   (*j)=0;
					               p2.atk.DefendSucceed=1*p1.direction*p2.direction;
							}
							else
							{/*p2�ھ�ֹ״̬�����л���*/
							  p2.PlayersBlood-=500/10;			
					               p2.atk.AlmostDie=1*p1.direction*p2.direction;
								   p2.PlayersCommandReset();
								   (*j)=0;
							}
						}
						else
						{/*����*/}
					}
				}
			}
			else//p1�ڣ�
			{
				double Distanse1_Dart_=fabs(p1.MyDart->GetDartY()-k2*(p1.MyDart->GetDartX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
				if(p1.direction==1)
				{
					if(p1.p1.x<p2.p1.x)
					{
						if(p2.direction==-1)
						{
							if(Distanse1_Dart_<=40)
							{/*p1�ڵ��˷���״̬��p2*/
							
								p2.PlayersCommandReset();
								
								(*j)=0;
								p2.atk.DefendSucceed=1;
							}
						}
						else
						{
							if(Distanse1_Dart_<=40)
							{/*p1쭵��˾�ֹ״̬��p2*/
							    int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
								p2.PlayersCommandReset();
								p2.PlayersBlood-=RelativeSpeed/10;
								(*j)=0;
								if(RelativeSpeed<=85)
								{p2.atk.Stumble=1*p1.direction*p2.direction;}
								else if(RelativeSpeed<125)
								{p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
								else
								{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
							}
						}
					}
				}
				else
				{
					if(p1.p1.x>p2.p1.x)
					{
						if(p2.direction==1)
						{
							if(Distanse1_Dart_<=40)
							{/*p1�ڵ��˷���״̬��p2*/
							    
								p2.PlayersCommandReset();
								
								(*j)=0;
								p2.atk.DefendSucceed=1;
						    }
						}
						else
						{
							if(Distanse1_Dart_<=40)
							{/*p1쭵��˾�ֹ״̬��p2*/
							    int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
								p2.PlayersCommandReset();
								p2.PlayersBlood-=RelativeSpeed/10;
								(*j)=0;
								if(RelativeSpeed<=85)
								{p2.atk.Stumble=1*p2.p1.x-p1.p1.x;}
								else if(RelativeSpeed<125)
								{p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
								else
								{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
							}
						}
					}

				}
			}


         }
		else//p1Զ��+p2�����ң�����
		{
			if(p1.MyDart==NULL)
			{
				if((*i)>=31&&(*i)<45)
				{
					if(p1.direction==1)
				{
					if(p1.p1.x<p2.p1.x)
					{/*p1���д��˾�ֹ��p2*/
					               p2.PlayersBlood-=500/10;			
					               p2.atk.AlmostDie=1*p1.direction*p2.direction;
								   p2.PlayersCommandReset();
								   (*j)=0;
					}
					else
					{/*����*/}
				}
				else
				{
					if(p1.p1.x>p2.p1.x)
					{/*p1���д��˾�ֹ��p2*/
					               p2.PlayersBlood-=500/10;			
					               p2.atk.AlmostDie=1*p1.direction*p2.direction;
								   p2.PlayersCommandReset();
								   (*j)=0;
					}
					else
					{/*����*/}
				}
			    }
			}
			else
			{
				double Distanse1_Dart_=fabs(p1.MyDart->GetDartY()-k2*(p1.MyDart->GetDartX()-p2.p2.x)-p2.p2.y)/sqrt(1+k2*k2);
				if(p1.direction==1)
				{
					if(p1.p1.x<p2.p1.x)
					{
						if(Distanse1_Dart_<=40)
						{/*p1�ڵ���ֹ��p2*/
						        int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
								p2.PlayersCommandReset();
								p2.PlayersBlood-=RelativeSpeed/10;
								(*j)=0;
								if(RelativeSpeed<=85)
								{p2.atk.Stumble=p1.direction*p2.direction;}
								else if(RelativeSpeed<125)
								{p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
								else
								{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
						}
					}
					else
					{/*����*/}
				}
				else
				{
					if(p1.p1.x>p2.p1.x)
					{
						if(Distanse1_Dart_<=40)
						{/*p1�ڵ���ֹ��p2*/
					            int RelativeSpeed=50-(p1.direction*p2.direction*p2.MoveSpeed);
								p2.PlayersCommandReset();
								p2.PlayersBlood-=RelativeSpeed/10;
								(*j)=0;
								if(RelativeSpeed<=85)
								{p2.atk.Stumble=1*p1.direction*p2.direction;}
								else if(RelativeSpeed<125)
								{p2.atk.GetKnockedDown=1*p2.p1.x-p1.p1.x;}
								else
								{p2.atk.GetKickedFlew=1*p2.p1.x-p1.p1.x;}
						}
					}
					else
					{/*����*/}
				}

			}
		}
    }
	else if(p1.cmd.Squat==1)//p1����
	{
		if(p2.cmd.Hit==1&&p2.cmd.Kick==0)
		{
			double Distance2_Left_=fabs(p2.LeftArm.GetArmY()-k1*(p2.LeftArm.GetArmX()-p1.p1.x)-p1.p1.y)/sqrt(1+k1*k1);
            double Distance2_Right_=fabs(p2.RightArm.GetArmY()-k1*(p2.RightArm.GetArmX()-p1.p1.x)-p1.p1.y)/sqrt(1+k1*k1);
			if(Distance2_Left_<=40||Distance2_Right_<=40)
			{
				if(p2.direction==1&&p1.direction==-1)
                {/*p2ȭ���˷���״̬��p1*/
					int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
					p1.PlayersCommandReset();
					(*i)=0;
					p1.PlayersBlood-=RelativeSpeed/10;
					p1.atk.DefendSucceed=1*p1.direction*p2.direction;
				
				}
	            else if(p2.direction==-1&&p1.direction==1)
                {/*p2ȭ���˷���״̬��p1*/
				int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
					p1.PlayersCommandReset();
					(*i)=0;
					p1.PlayersBlood-=RelativeSpeed/10;
					p1.atk.DefendSucceed=1*p1.direction*p2.direction;
				}
				else
				{/*p2ȭ������ͨ״̬�µ�p1*/
					    int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*0);
			            p1.PlayersCommandReset();
			            
			            (*i)=0;
			            if(p2.direction==1)
			            {
				            if(p1.cmd.MoveLeft==1)
				            {
								if((Distance2_Right_<=40)&&((*i)<=22&&(*i)>16))
								{p1.atk.ComeToSky=1*p1.direction*p2.direction;
								p1.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					            else
								{p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }
			            else
			            {
				             if(p1.cmd.MoveRight==1)
				            {
								if((Distance2_Right_<=40)&&((*i)<=22&&(*i)>16))
								{p1.atk.ComeToSky=1*p1.direction*p2.direction;
								p1.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p1.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					             else
								 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }	
				
				}
			}


		}
		else if(p2.cmd.Kick==1)
		{
			if(p2.direction==1&&p1.direction==-1)
                {
					/*p2jiao���˷���״̬��p1*/
					int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
					p1.PlayersCommandReset();
					(*i)=0;
					p1.PlayersBlood-=RelativeSpeed/10;
					p1.atk.DefendSucceed=1*p1.direction*p2.direction;
				}
	            else if(p2.direction==-1&&p1.direction==1)
                {
					/*p2jiao���˷���״̬��p1*/
					int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
					p1.PlayersCommandReset();
					(*i)=0;
					p1.PlayersBlood-=RelativeSpeed/10;
					p1.atk.DefendSucceed=1*p1.direction*p2.direction;
				}
				else
				{/*p2jiao���˾�ֹ״̬�µ�p1*/
                        int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*0);
			            p1.PlayersCommandReset();
			            
			            (*i)=0;
			            if(p2.direction==1)
			            {
				            if(p2.cmd.MoveRight==1)
				            {
								if((*j)<=6)
								{p1.atk.DoubleHurt=1*p1.p1.x-p2.p1.x;
								p1.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					            else
								{p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }
			            else
			            {
				             if(p2.cmd.MoveLeft==1)
				            {
								
								if((*j)<=6)
								{p1.atk.DoubleHurt=1*p1.p1.x-p2.p1.x;
								p1.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p1.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					             else
								 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }			
		}
				}
		else if(p2.cmd.RemoteAttack==1)
		{
			if(p2.MyDart==NULL)//p2���У�
			{
				if((*j)>=31&&(*j)<=45)
				{
					if(p2.direction==1)
					{
						if(p2.p1.x<p1.p1.x)
						{
							if(p1.direction==-1)
							{/*p1�ڷ���״̬�����л���*/
							       p1.PlayersBlood-=350/10;
								   p1.PlayersCommandReset();
								   (*i)=0;
					               p1.atk.DefendSucceed=1*p1.direction*p2.direction;
							}
							else
							{/*p1�ھ�ֹ״̬�����л���*/
							         p1.PlayersBlood-=500/10;			
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;
								   p1.PlayersCommandReset();
								   (*i)=0;
							}
						}
						else
						{/*����*/}
					}
					else
					{
						if(p2.p1.x>p1.p1.x)
						{
							if(p1.direction==1)
							{/*p1�ڷ���״̬�����л���*/
							  p1.PlayersBlood-=350/10;
								   p1.PlayersCommandReset();
								   (*i)=0;
					               p1.atk.DefendSucceed=1*p1.direction*p2.direction;
							}
							else
							{/*p1�ھ�ֹ״̬�����л���*/
							  p1.PlayersBlood-=500/10;			
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;
								   p1.PlayersCommandReset();
								   (*i)=0;
							}
						}
						else
						{/*����*/}
					}
				}
			}
			else//p2�ڣ�
			{
				double Distanse2_Dart_=fabs(p2.MyDart->GetDartY()-k1*(p2.MyDart->GetDartX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
				if(p2.direction==1)
				{
					if(p2.p1.x<p1.p1.x)
					{
						if(p1.direction==-1)
						{
							if(Distanse2_Dart_<=40)
							{/*p2�ڵ��˷���״̬��p1*/
							
								p1.PlayersCommandReset();
								
								(*i)=0;
								p1.atk.DefendSucceed=1;
							}
						}
						else
						{
							if(Distanse2_Dart_<=40)
							{/*p2쭵��˾�ֹ״̬��p1*/
							    int RelativeSpeed=50-(p2.direction*p1.direction*p1.MoveSpeed);
								p1.PlayersCommandReset();
								p1.PlayersBlood-=RelativeSpeed/10;
								(*i)=0;
								if(RelativeSpeed<=85)
								{p1.atk.Stumble=1*p1.direction*p2.direction;}
								else if(RelativeSpeed<125)
								{p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
								else
								{p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
							}
						}
					}
				}
				else
				{
					if(p2.p1.x>p1.p1.x)
					{
						if(p1.direction==1)
						{
							if(Distanse2_Dart_<=40)
							{/*p2�ڵ��˷���״̬��p1*/
							    
								p1.PlayersCommandReset();
								
								(*i)=0;
								p1.atk.DefendSucceed=1;
						    }
						}
						else
						{
							if(Distanse2_Dart_<=40)
							{/*p2쭵��˾�ֹ״̬��p1*/
							    int RelativeSpeed=50-(p1.direction*p2.direction*p1.MoveSpeed);
								p1.PlayersCommandReset();
								p1.PlayersBlood-=RelativeSpeed/10;
								(*i)=0;
								if(RelativeSpeed<=85)
								{p1.atk.Stumble=1*p1.direction*p2.direction;}
								else if(RelativeSpeed<125)
								{p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
								else
								{p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
							}
						}
					}

				}
			}

	}
	}
	else
	{
		if(p2.cmd.Hit==1&&p2.cmd.Kick==0)
		{
		    double Distance2_Left_=fabs(p2.LeftArm.GetArmY()-k1*(p2.LeftArm.GetArmX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
            double Distance2_Right_=fabs(p2.RightArm.GetArmY()-k1*(p2.RightArm.GetArmX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
			if(Distance2_Left_<=40||Distance2_Right_<=40)
			{/*p2��ȭ������ͨ״̬�µ�p1*/
				int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
				(*i)=0;
				p1.PlayersCommandReset();
				
				if(p2.direction==1)
			            {
				            if(p2.cmd.MoveLeft==1)
				            {
								if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
								{p1.atk.ComeToSky=1*p1.direction*p2.direction;
								p1.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					            else
								{p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }
			            else
			            {
				             if(p2.cmd.MoveRight==1)
				            {
								if((Distance2_Right_<=40)&&((*j)<=22&&(*j)>16))
								{p1.atk.ComeToSky=1*p1.direction*p2.direction;
								p1.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p1.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					             else
								 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }			

			}
		}
		else if(p2.cmd.Kick==1)
		{
			 double Distance2_Left_=fabs(p2.LeftLeg.GetLegY()-k1*(p2.LeftLeg.GetLegX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
            double Distance2_Right_=fabs(p2.RightLeg.GetLegY()-k1*(p2.RightLeg.GetLegX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
			if(Distance2_Left_<=40||Distance2_Right_<=40)
			{/*p2��jiao������ͨ״̬�µ�p1*/
				int RelativeSpeed=p2.ActionSpeed-(p1.direction*p2.direction*p1.MoveSpeed);
				(*i)=0;
				p1.PlayersCommandReset();
				
				if(p2.direction==1)
			            {
				            if(p2.cmd.MoveRight==1)
				            {
								if((*j)<=6)
								{p1.atk.DoubleHurt=1*p1.p1.x-p2.p1.x;
								p1.PlayersBlood-=RelativeSpeed/10;}
				            }
				            else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					            if(RelativeSpeed<=85)
					            {p1.atk.Stumble=1*(p1.direction*p2.direction);}
					            else if(RelativeSpeed<125)
								{p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					            else
								{p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }
			            else
			            {
				             if(p2.cmd.MoveLeft==1)
				            {
								
								if((*j)<=6)
								{p1.atk.DoubleHurt=1*p1.p1.x-p2.p1.x;
								p1.PlayersBlood-=RelativeSpeed/10;}
				             }
				             else
				            {
								p1.PlayersBlood-=RelativeSpeed/10;
					             if(RelativeSpeed<=85)
					             {p1.atk.Stumble=1*p1.direction*p2.direction;}
					             else if(RelativeSpeed<125)
								 {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
					             else
								 {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
				             }
			             }			

			}
		}
		else if(p2.cmd.RemoteAttack==1)
		{
			if(p2.MyDart==NULL)
			{
			    if((*j)>=31&&(*j)<45)
				{
					if(p2.direction==1)
				{
					if(p2.p1.x<p1.p1.x)
					{/*p2���д��˾�ֹ��p1*/
					               p1.PlayersBlood-=500/10;			
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;
								   p1.PlayersCommandReset();
								   (*i)=0;
					}
					else
					{/*����*/}
				}
				else
				{
					if(p2.p1.x>p1.p1.x)
					{/*p2���д��˾�ֹ��p1*/
					
						           p1.PlayersBlood-=500/10;			
					               p1.atk.AlmostDie=1*p1.direction*p2.direction;
								   p1.PlayersCommandReset();
								   (*i)=0;
					}
					
					else
					{/*����*/}
				}
				}
			}
			else
			{
				double Distanse2_Dart_=fabs(p2.MyDart->GetDartY()-k1*(p2.MyDart->GetDartX()-p1.p2.x)-p1.p2.y)/sqrt(1+k1*k1);
				if(p2.direction==1)
				{
					if(p2.p1.x<p1.p1.x)
					{
						if(Distanse2_Dart_<=40)
						{/*p2�ڵ���ֹ��p1*/
						
							 int RelativeSpeed=50-(p1.direction*p2.direction*p1.MoveSpeed);
				                    p1.PlayersCommandReset();
				                    p1.PlayersBlood-=RelativeSpeed/10;
				                    (*i)=0;
				                    if(RelativeSpeed<=85)
			                        {p1.atk.Stumble=1*p1.direction*p2.direction;}
				                     else if(RelativeSpeed<125)
				                     {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
				                     else
				                     {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
						}
					}
					else
					{/*����*/}
				}
				else
				{
					if(p2.p1.x>p1.p1.x)
					{
						if(Distanse2_Dart_<=40)
						{/*p2�ڵ���ֹ��p1*/
						
							 int RelativeSpeed=50-(p1.direction*p2.direction*p1.MoveSpeed);
				                    p1.PlayersCommandReset();
				                    p1.PlayersBlood-=RelativeSpeed/10;
				                    (*i)=0;
				                    if(RelativeSpeed<=85)
			                        {p1.atk.Stumble=1*p1.direction*p2.direction;}
				                     else if(RelativeSpeed<125)
				                     {p1.atk.GetKnockedDown=1*p1.p1.x-p2.p1.x;}
				                     else
				                     {p1.atk.GetKickedFlew=1*p1.p1.x-p2.p1.x;}
						}
					}
					else
					{/*����*/}
				}

			}

		}
		else if(p2.cmd.Squat==1)
		{/*����*/}
		else
		{/*����*/}
	}
}
void Object::PlayersHurtAchieve(int *i,int *j)
{
	
	p1.PlayersGetHurt(i);
	p2.PlayersGetHurt(j);
}
void Object::PlayersAct(int *i,int *j,int *k1,int *k2)//PlayersAct���������״̬�ı䣩��
{p1.PlayersChange(i,k2);
p2.PlayersChange(j,k1);
p1.PlayersDrawStatus(0);
p2.PlayersDrawStatus(850);
}
void Object::ObjectUpdate()//ObjectUpdate������ˢ�£���
{
static int k=1;

if(p1.PlayersMagicPoint<100)
p1.PlayersMagicPoint+=0.3;
if(p2.PlayersMagicPoint<100)
p2.PlayersMagicPoint+=0.3;
if(k==15)
{
	setfillcolor(DARKGRAY);
    solidrectangle(0,630,1333,700);
    k=1;   
}
k++;
setfillcolor(DARKGRAY);
solidrectangle(0,595,1333,630);
setfillcolor(HSVtoRGB(0,0,0));
solidrectangle(0,220,1333,595);
setfillcolor(WHITE);
}
void Object::Login()
{
	setfillstyle(BS_SOLID);
	setbkcolor(HSVtoRGB(96,96,96));
	MOUSEMSG m;
	solidrectangle(140, 30, 280, 80);
	solidrectangle(140, 90, 280, 140);
	settextcolor(BLACK);					// ����������ɫ
	outtextxy(160, 43, _T("��ʼ��Ϸ"));
	outtextxy(160, 103, _T("�˳���Ϸ"));
	setbkcolor(HSVtoRGB(96,96,96));
	setfillcolor(WHITE);         //�������������ɫ
	while(true)
	{
		m = GetMouseMsg();				// �ж��Ƿ������
		if(m.x >= 140 && m.x <= 280 && m.y >= 30 && m.y <= 80)
		{
			setlinecolor(WHITE);			// ѡ�п������������������ɫ
			rectangle(135, 25, 285, 85);
			if(m.uMsg==WM_LBUTTONDOWN )
			{
				clearrectangle(140, 30, 280, 80);
				clearrectangle(140, 90, 280, 140);
				
				Object::ObjectStart();
			}
		}
		else if(m.x >= 140 && m.x <= 280 && m.y >= 90 && m.y <= 140)
		{
			setlinecolor(HSVtoRGB(96,96,96));			// ѡ�п��������ɫ
			rectangle(135, 85, 285,145);
			if(m.uMsg==WM_LBUTTONDOWN)
			{
				exit(1);
			}
		}
		else
		{
			setlinecolor(HSVtoRGB(96,96,96));
			rectangle(135, 25,  285, 85);
			rectangle(135, 85, 285, 145);
		}
	}
}
#endif