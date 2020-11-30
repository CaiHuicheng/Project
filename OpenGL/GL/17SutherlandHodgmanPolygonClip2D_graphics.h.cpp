//编译环境：Visual C++ 6.0，EasyX_20190219(beta)
#include<graphics.h>
#include<conio.h>
#include<iostream>
#define max 30
using namespace std;

//设置裁剪框的大小和位置,裁剪多边形顶点和顶点数，以全局变量给出
double xl=5,xr=140,yt=190,yb=74;
int inlength=9;
POINT Vertex[]={ {110,84},{160,94},{90,169},{90,94},{70,90},{50,230}, {165,230},{175,89},{163,54} };
//求多边形的一条边sp和裁剪边point0 point1的交点
void Intersect(POINT S,POINT P,POINT point0,POINT point1,POINT &I)
{
	if(point0.y==point1.y)//水平裁剪边
	{
		I.y=point0.y;
		I.x=S.x+(point0.y-S.y)*(P.x-S.x)/(P.y-S.y);
	}
	else//竖直裁剪边
	{
		I.x=point0.x;
		I.y=S.y+(point0.x-S.x)*(P.y-S.y)/(P.x-S.x);
	}
}

//测试顶点与裁剪边的内外关系
bool Inside(POINT text,POINT point0,POINT point1)
{
	if(point1.x>point0.x){//裁剪边为窗口的下边
		if(text.y>=point0.y)
			return true;}

	else if(point1.x<point0.x){//裁剪边为窗口的上边
        if(text.y<=point0.y)
			return true;}

	else if(point1.y>point0.y){//裁剪边为窗口的右边
		if(text.x<=point0.x)
			return true;}

	else if(point1.y<point0.y){//裁剪边为窗口的左边
		if(text.x>=point0.x)
			return true;}

	return false;
}

//将新的定点加入结果多边形顶点表
void Output(POINT newpoint,int &length,POINT outps[])
{
	outps[length].x=newpoint.x;
	outps[length].y=newpoint.y;
	length++;
}

//裁剪算法
void SutherlandHodgmanPolygonClip(int inlength,POINT inpoints[],int &outlength,POINT outpoints[],POINT point0,POINT point1)
{
	POINT S,P,I;
	int j;
	outlength=0;
	S=inpoints[inlength-1];
	for(j=0;j<inlength;j++)
	{
		P=inpoints[j];
		if(Inside(P,point0,point1))
		{ 
			if(Inside(S,point0,point1))
			{Output(P,outlength,outpoints);}
			else
			{
				Intersect(S,P,point0,point1,I);
				Output(I,outlength,outpoints);
				Output(P,outlength,outpoints);}}
		else if(Inside(S,point0,point1))
		{
			Intersect(S,P,point0,point1,I);
			Output(I,outlength,outpoints);}
		S=P;}
}

int main()
{
	POINT Edge[]={ {xr,yb},{xr,yt},{xl,yt},{xl,yb} };
	initgraph(1000,900);
	polygon(Edge,4);
	setcolor(RED);
	polygon(Vertex,inlength);
    int i;
	POINT OutPts1[max],OutPts2[max],OutPts3[max],OutPts4[max];
	int length1,length2,length3,length4;
    SutherlandHodgmanPolygonClip(inlength,Vertex,length1,OutPts1,Edge[0],Edge[1]);//右边窗口裁剪边
	SutherlandHodgmanPolygonClip(length1,OutPts1,length2,OutPts2,Edge[1],Edge[2]);//下边窗口裁剪边
	SutherlandHodgmanPolygonClip(length2,OutPts2,length3,OutPts3,Edge[2],Edge[3]);//左边窗口裁剪边
	SutherlandHodgmanPolygonClip(length3,OutPts3,length4,OutPts4,Edge[3],Edge[0]);//上边窗口裁剪边
	MOUSEMSG m;
	while(true)
	{		  
		  m=GetMouseMsg();
		  switch(m.uMsg)
		  {
		    case WM_LBUTTONDOWN:
				cleardevice();
				setcolor(RED);
				polygon(Edge,4);
				setcolor(YELLOW);
				polygon(OutPts4,length4);
				for(i=0;i<length4;i++)
				{OutPts4[i].x+=300;}
				polygon(OutPts4,length4);
				break;
			case WM_RBUTTONDOWN:
				return 0;
		  }
	}
	_getch();
	closegraph();
	return 0;
}

