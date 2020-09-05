#include<stdio.h>
#include <windows.h>
#include<conio.h>
#include<time.h>

void gotoxy(int x,int y);//控制光标。X表示横坐标，Y表示纵坐标
void my_print();//设置界面
void print_thing();//打印物品
void print_home();//打印老家
void refresh_map();//刷新地图
void stop();//暂停

void print_my_tank();//打印我的坦克
void print_tank_1();//打印坦克1号
void print_tank_2();//打印坦克2号
void print_tank_3();//打印坦克3号

void clear_my_tank();//清除我的坦克，用于坦克移动后
void clear_tank_1();//清除坦克1号
void clear_tank_2();//清除坦克2号
void clear_tank_3();//清除坦克3号

void turn_up(int a[][3]);//我的坦克上转
void turn_down(int a[][3]);//我的坦克下转
void turn_left(int a[][3]);//我的坦克左转
void turn_right(int a[][3]);//我的坦克右转

void turn_up_1(int a[][3]);//坦克1号上转
void turn_down_1(int a[][3]);//坦克1号下转
void turn_left_1(int a[][3]);//坦克1号左转
void turn_right_1(int a[][3]);//坦克1号右转

void turn_up_2(int a[][3]);//坦克2号上转
void turn_down_2(int a[][3]);//坦克2号下转
void turn_left_2(int a[][3]);//坦克2号左转
void turn_right_2(int a[][3]);//坦克2号右转

void turn_up_3(int a[][3]);//坦克3号上转
void turn_down_3(int a[][3]);//坦克3号下转
void turn_left_3(int a[][3]);//坦克3号左转
void turn_right_3(int a[][3]);//坦克3号右转

void my_move();//我的坦克移动
void move_1();//坦克1号移动
void move_2();//坦克2号移动
void move_3();//坦克3号移动

void print_bullet(int x,int y);//打印敌方坦克的子弹
void print_my_bullet(int x,int y);//打印我的子弹
void clear_bullet(int x,int y);//清楚子弹
int  check_bullet(int x,int y);//检查子弹是否碰撞，没碰返回1，碰到返回0
void shoot();//计算我的坦克子弹的坐标
void shoot_1();//计算坦克1号子弹的坐标
void shoot_2();//计算坦克2号子弹的坐标
void shoot_3();//计算坦克3号子弹的坐标

void change_thing();//记录物品的变化
void change_home();//记录老家的变化
void change_bullet();//纪录子弹的变化
void change_star();//记录星星的变化
void change_tank();//记录我的坦克的变化
void change_tank_1();//记录坦克1号的变化
void change_tank_2();//记录坦克2号的变化
void change_tank_3();//记录坦克3号的变化

void switch_weapons();//切换武器
void switch_skin();//切换皮肤
void help();//帮助
void check_game();//检查游戏胜负
void check_lv();//检查等级
void next_level();//下一关
void get_map();//获得每一关的地图
void initial();//将所有量初始化
void gameover();//游戏结束

void console();//控制窗口
void screen_1();//屏幕1
void screen_2(char *p,int color);//屏幕2
void screen_3();//屏幕3
void produce_star();//产生一个星星
void print_star();//打印星星
void check_star();//检查星星的数量
void clear_star();//清除星星

int my_abs(int x);//绝对值函数，用系统的会有问题
int judge(int x,int y,int state);//判断我的坦克能否前进
int judge2(int x,int y,int state);// 辅助电脑判断能否前进

int check1(int x,int y);//辅助电脑判断的函数
int check2(int x,int y);//辅助电脑判断的函数
int check3(int x,int y);//辅助电脑判断的函数


int life=3;//生命
int enemy=13;//敌人数量
int level=1;//关卡
int weapons=1;//武器
int skin=1;//皮肤
int star=1;//星星
int s=0,t=0;//星星坐标
int score=0;//分数
int lv=1;//等级
int speed=10;//速度
char *info[5]={" "," "," "," "," "};//通知

int map[30][30]={0};//记录整个屏幕上的物体
int thing[28][28]={0};//障碍物，不包括边界
int home[3][4]={{2,2,2,2},{2,1,1,2},{2,1,1,2}};//老家,3行4列

int my_tank[3][3]={0};//我的坦克
int tank_1[3][3]={0};//敌人的坦克1号
int tank_2[3][3]={0};//敌人的坦克2号
int tank_3[3][3]={0};//敌人的坦克3号

int x  , y ;//我的坦克中心坐标
int x1 , y1;//坦克1号中心坐标
int x2 , y2;//坦克2号中心坐标
int x3 , y3;//坦克3号中心坐标

int m=0  , n=0 ;//我的坦克子弹的坐标
int m1=0 , n1=0;//坦克1号子弹的坐标
int m2=0 , n2=0;//坦克2号子弹的坐标
int m3=0 , n3=0;//坦克3号子弹的坐标

int state=0; //我的坦克方向(1上，2下，3左，4右)
int state_1=0;//坦克1号方向
int state_2=0;//坦克2号方向
int state_3=0;//坦克3号方向

int direction=0;//我的坦克子弹射向
int direction_1=0;//坦克1号子弹射向
int direction_2=0;//坦克2号子弹射向
int direction_3=0;//坦克3号子弹射向

int cp1=2;//辅助电脑判断的变量
int cp2=2;//辅助电脑判断的变量
int cp3=2;//辅助电脑判断的变量

void main()//主函数
{
	srand(time(NULL));//设置随机数种子
	console();//设置窗口
	my_print();//打印边框
	initial();//所有量初始化
	while(1)
	{
		int i1,i2,i3,i4,i5,i6,i7;
		my_move();//控制我的坦克移动
		if(i1++%30==0) //控制敌人坦克速度
			move_1();
 		if(i2++%30==0) 
			move_2();
		if(i3++%30==0) 
			move_3();
		if(i4++%speed==0)   //控制子弹速度
			shoot();
		if(i5++%speed==0)
			shoot_1();
		if(i6++%speed==0)
			shoot_2();
		if(i7++%speed==0)
			shoot_3();
		screen_1();//刷新屏幕
		Sleep(30);
	}
}

//设置光标输出的位置函数
void gotoxy(int x,int y)//X表示横坐标，Y表示纵坐标。
{
	HANDLE app;
	COORD  pos;
	pos.X=x;
	pos.Y=y;
	app=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(app,pos);
}

//控制窗口
void console()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);	
	CONSOLE_SCREEN_BUFFER_INFO bInfo; 
	GetConsoleScreenBufferInfo(hOut, &bInfo );	
	SetConsoleTitle("坦克大战"); // 设置窗口的标题
	COORD size = {90, 32};//设置窗口大小
	SetConsoleScreenBufferSize(hOut,size); 	
	SMALL_RECT rc = {0,0, 63, 31};
	SetConsoleWindowInfo(hOut,true ,&rc);
}

//打印边界
void my_print()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE |FOREGROUND_INTENSITY);//蓝色
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ |﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊﹊|\n");
	for(int i=0;i<13;i++)
	printf("■                                                        ■ |                          |\n");
	printf("■                                                        ■ |--------------------------|\n");
	for(int j=14;j<28;j++)
	printf("■                                                        ■ |                          |\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ |﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍|\n");
}


//打印与清除坦克
void print_my_tank()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(my_tank[i][j]==1)
			{
				switch(skin)
				{
				case 1 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);//淡蓝色
						gotoxy(2*x+2*j-2,y+i-1);
						printf("■");
					}break;
				case 2 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);//绿色
						gotoxy(2*x+2*j-2,y+i-1);
						printf("■");
					}break;
				case 3 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);//黄色
						gotoxy(2*x+2*j-2,y+i-1);
						printf("■");
					}break;
				case 4 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);//白色
						gotoxy(2*x+2*j-2,y+i-1);
						printf("■");
					}break;
				case 5 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);//紫色
						gotoxy(2*x+2*j-2,y+i-1);
						printf("■");
					}break;
				case 6 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);//红色
						gotoxy(2*x+2*j-2,y+i-1);
						printf("■");
					}break;
				case 7 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);//蓝色
						gotoxy(2*x+2*j-2,y+i-1);
						printf("■");
					}break;

				}

			}
}
void clear_my_tank()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			{
				gotoxy(2*x+2*j-2,y+i-1);
				printf("  ");
			}
}
void print_tank_1()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(tank_1[i][j]==1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);// 紫色
				gotoxy(2*x1+2*j-2,y1+i-1);
				printf("■");
			}
}
void clear_tank_1()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			{
				gotoxy(2*x1+2*j-2,y1+i-1);
				printf("  ");
			}
}
void print_tank_2()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(tank_2[i][j]==1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);// 紫色
				gotoxy(2*x2+2*j-2,y2+i-1);
				printf("■");
			}
}
void clear_tank_2()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			{
				gotoxy(2*x2+2*j-2,y2+i-1);
				printf("  ");
			}
}
void print_tank_3()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(tank_3[i][j]==1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);// 紫色
				gotoxy(2*x3+2*j-2,y3+i-1);
				printf("■");
			}
}
void clear_tank_3()
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			{
				gotoxy(2*x3+2*j-2,y3+i-1);
				printf("  ");
			}
}

void print_thing()                // 打印物品
{
	for(int j=0;j<28;j++)         // 从坐标(1,1)点开始打印
		for(int i=0;i<28;i++)
			if(thing[i][j]==1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
				gotoxy(2+2*j,1+i);
				printf("■");
			}
			else if(thing[i][j]==2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
				gotoxy(2+2*j,1+i);
				printf("■");
			}
			else if(thing[i][j]==3)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
				gotoxy(2+2*j,1+i);
				printf("■");
			}
			else if(thing[i][j]==4)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
				gotoxy(2+2*j,1+i);
				printf("■");
			}
}

void print_home()                 //打印老家
{


	for(int i=0;i<3;i++)          //打印老家外墙       
		for(int j=0;j<4;j++)
			if(home[i][j]==1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
					gotoxy(26+2*j,26+i);
					printf("■");
				}
			else if(home[i][j]==2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
					gotoxy(26+2*j,26+i);
					printf("■");
				}
			else if(home[i][j]==3)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
					gotoxy(26+2*j,26+i);
					printf("■");
				}


	{
	for(int i=1;i<3;i++)          //打印老家内部
		for(int j=1;j<3;j++)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
					gotoxy(26+2*j,26+i);
					printf("■");
				}
	}

}


void print_bullet(int x,int y)    //打印敌方坦克的子弹子弹
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	gotoxy(2*x,y);
	printf("⊕");
}

void print_my_bullet(int x,int y)    //打印我的子弹
{
	switch(weapons)
	{
	case 1 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
			gotoxy(2*x,y);
			printf("⊕");
		}break;
	case 2 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
			gotoxy(2*x,y);
			printf("∷");
		}break;
	case 3 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
			gotoxy(2*x,y);
			printf("◎");
		}break;
	case 4 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
			gotoxy(2*x,y);
			printf("※");
		}break;
	case 5 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
			gotoxy(2*x,y);
			printf("●");
		}break;
	}

}

void clear_bullet(int x,int y)
{
	gotoxy(2*x,y);
	printf("  ");
}


void screen_1()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
	gotoxy(62,2);
	printf("          第 %d 关         ",level);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	gotoxy(62,4);
	printf("分数: %d",score);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_RED);
	gotoxy(80,4);
	printf("LV: %d ",lv);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	gotoxy(62,6);
	printf("生命:     坦克×%d         ",life-1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
	gotoxy(62,8);
	printf("敌方:     坦克×%d        ",enemy);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	gotoxy(62,11);
	printf("当前武器:                 ");
	switch(weapons)
	{
	case 1 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
			gotoxy(62,13);
			printf("         普通子弹 ⊕      ");
		}break;
	case 2 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
			gotoxy(62,13);
			printf("           散弹   ∷      ");
		}break;
	case 3 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
			gotoxy(62,13);
			printf("          气泡弹  ◎      ");
		}break;
	case 4 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
			gotoxy(62,13);
			printf("          雪花弹  ※      ");
		}break;
	case 5 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
			gotoxy(62,13);
			printf("         超级炮弹 ●      ");
		}break;
	}


}

void screen_2(char *p,int color)
{

	for(int i=15;i<27;i++)//先清屏
	{
		gotoxy(62,i);
		printf("                          ");
	}

	info[0]=info[1];//内容上移
	info[1]=info[2];
	info[2]=info[3];
	info[3]=info[4];
	info[4]=p;

	for(int j=15;j<22;j=j+2)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
		gotoxy(62,j);
		printf("%s",info[(j+1)/2-8]);
	}
	switch(color)
	{
	case 1 :
		{
			 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);//绿
			 gotoxy(62,23);
			 printf("%s",info[4]);
		}break;
	case 2 :
		{
			 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);//淡蓝
			 gotoxy(62,23);
			 printf("%s",info[4]);
		}break;
	case 3 :
		{
			 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);//黄
			 gotoxy(62,23);
			 printf("%s",info[4]);
		}break;
	case 4 :
		{
		     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);//红
			 gotoxy(62,23);
			 printf("%s",info[4]);
		}break;
	}
}

void screen_3()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
	gotoxy(62,27);
	printf("          h键帮助  Esc退出");
	gotoxy(62,28);
	printf("                          ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
	if(star<=13)
	for(int i=1;i<=star;i++)
	{
		gotoxy(60+2*i,28);
		printf("★");
	}
}


void produce_star()
{
	int a=0;
	for(int i=4;i<26;i++)
	{
		for(int j=1;j<29;j++)
			if(map[i][j]==0 && rand()%300==0)
			{
				s=j,t=i;
				print_star();
				a=1;
				break;
			}
		if(a)
			break;
	}

}

void print_star()
{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
		gotoxy(2*s,t);
		printf("★");
}

void change_star()
{
	if(s==x&&t==(y-1) || s==x&&t==(y+1) || s==(x-1)&&t==y || s==(x+1)&&t==y)
	{
		clear_star();
		s=0,t=0;
		star++;
		screen_2("恭喜你获得一颗星星",2);
		printf("\7");
		check_star();
		print_my_tank();
	}
	if(s==x1&&t==(y1-1) || s==x1&&t==(y1+1) || s==(x1-1)&&t==y1 || s==(x1+1)&&t==y1)
	{
		clear_star();
		s=0,t=0;
		screen_2("很遗憾星星被抢走了",4);
		printf("\7");
		print_tank_1();
	}
	if(s==x2&&t==(y2-1) || s==x2&&t==(y2+1) || s==(x2-1)&&t==y2 || s==(x2+1)&&t==y2)
	{
		clear_star();
		s=0,t=0;
		screen_2("很遗憾星星被抢走了",4);
		printf("\7");
		print_tank_2();
	}

	if(s==x3&&t==(y3-1) || s==x3&&t==(y3+1) || s==(x3-1)&&t==y3 || s==(x3+1)&&t==y3)
	{
		clear_star();
		s=0,t=0;
		screen_2("很遗憾星星被抢走了",4);
		printf("\7");
		print_tank_3();
	}



}

void clear_star()
{
	gotoxy(2*s,t);
	printf("  ");
}

void check_star()
{
	switch(star)
	{
	case 2 :screen_2("解锁新武器：  散弹",4),screen_3();break;
	case 3 :screen_2("成功解锁  绿色皮肤",2),screen_3();break;
	case 4 :screen_2("解锁新武器：  气泡弹",2),screen_3();break;
	case 5 :screen_2("成功解锁  黄色皮肤",3),screen_3();break;
	case 6 :screen_2("解锁新武器：  雪花弹",1),screen_3();break;
	case 7 :screen_2("成功解锁  白色皮肤",1),screen_3();break;
	case 8 :screen_2("解锁新武器：  超级炮弹",4),screen_3();break;
	case 9 :screen_2("成功解锁  紫色皮肤",1),screen_3();break;
	case 10 :screen_2("您已拥有10颗星啦",3),screen_3();break;
	case 11 :screen_2("成功解锁  红色皮肤",4),screen_3();break;
	case 12 :screen_2("您已拥有12颗星啦",3),screen_3();break;
	case 13 :screen_2("成功解锁 蓝色皮肤",1),screen_3();break;
	}

}

void switch_weapons()
{
	weapons++;
	if(weapons>star/2+1)
		weapons=1;
	if(star==1)
		screen_2("当前星星数不足，赶快收集吧",1);
	else
	{
		switch(weapons)
		{
		case 1 :screen_2("切换到普通子弹",1);break;
		case 2 :screen_2("切换到散弹",1);break;
		case 3 :screen_2("切换到气泡弹",1);break;
		case 4 :screen_2("切换到雪花弹",1);break;
		case 5 :screen_2("切换到超级炮弹弹",1);break;
		}
	}

}

void switch_skin()
{
	skin++;
	if(skin>(star-1)/2+1)
		skin=1;
	if(star==1 || star==2)
		screen_2("当前星星数不足，赶快收集吧",1);
	else
	{
		switch(skin)
		{
		case 1 :screen_2("切换到淡蓝色皮肤",1);break;
		case 2 :screen_2("切换到绿色皮肤",1);break;
		case 3 :screen_2("切换到黄色皮肤",1);break;
		case 4 :screen_2("切换到白色皮肤",1);break;
		case 5 :screen_2("切换到紫色皮肤",1);break;
		case 6 :screen_2("切换到红色皮肤",1);break;
		case 7 :screen_2("切换到蓝色皮肤",1);break;
		}
	}


}

void shoot()
{

	if(m!=0 || n!=0)
		if(map[n][m]==0)//如果子弹还留在地图上，就清除掉		
			clear_bullet(m,n);
	if(m==0 && n==0)//代表现在场上没有我的坦克的子弹,则重新发射子弹
	{
		switch(state)
		{
			case 1 :
				{
					m=x;
					n=y-2;
					direction=1;
				}break;
			case 2 :
				{
					m=x;
					n=y+2;
					direction=2;
				}break;
			case 3 :
				{
					m=x-2;
					n=y;
					direction=3;
				}break;
			case 4 :
				{
					m=x+2;
					n=y;
					direction=4;
				}break;
		}
	}
	else
	{
		switch(direction)
		{
			case 1 :n--;break;
			case 2 :n++;break;
			case 3 :m--;break;
			case 4 :m++;break;
		}
	}
	change_thing();//检查是否击中障碍物
	change_home();//检查是否击中老家
	change_bullet();//检查是否击中子弹
	change_tank_1();//检查是否击中坦克1号
	change_tank_2();//检查是否击中坦克2号
	change_tank_3();//检查是否击中坦克3号
	if(check_bullet(m,n))	
		print_my_bullet(m,n);
	else
		m=0,n=0;
}

void shoot_1()
{

	if(m1!=0 || n1!=0)
		if(map[n1][m1]==0)//如果子弹还留在地图上，就清除掉		
			clear_bullet(m1,n1);
	if(m1==0 && n1==0)//代表现在场上没有坦克1号的子弹,则重新发射子弹
	{
		switch(state_1)
		{
			case 1 :
				{
					m1=x1;
					n1=y1-2;
					direction_1=1;
				}break;
			case 2 :
				{
					m1=x1;
					n1=y1+2;
					direction_1=2;
				}break;
			case 3 :
				{
					m1=x1-2;
					n1=y1;
					direction_1=3;
				}break;
			case 4 :
				{
					m1=x1+2;
					n1=y1;
					direction_1=4;
				}break;
		}
	}
	else
	{
		switch(direction_1)
		{
			case 1 :n1--;break;
			case 2 :n1++;break;
			case 3 :m1--;break;
			case 4 :m1++;break;
		}
	}
	change_thing();//检查是否击中障碍物
	change_home();//检查是否击中老家
	change_bullet();//检查是否击中子弹
	change_tank();//检查是否击中我的坦克
	if(check_bullet(m1,n1))	
		print_bullet(m1,n1);
	else
		m1=0,n1=0;
}

void shoot_2()
{

	if(m2!=0 || n2!=0)
		if(map[n2][m2]==0)//如果子弹还留在地图上，就清除掉		
			clear_bullet(m2,n2);
	if(m2==0 && n2==0)//代表现在场上没有坦克2号的子弹,则重新发射子弹
	{
		switch(state_2)
		{
			case 1 :
				{
					m2=x2;
					n2=y2-2;
					direction_2=1;
				}break;
			case 2 :
				{
					m2=x2;
					n2=y2+2;
					direction_2=2;
				}break;
			case 3 :
				{
					m2=x2-2;
					n2=y2;
					direction_2=3;
				}break;
			case 4 :
				{
					m2=x2+2;
					n2=y2;
					direction_2=4;
				}break;
		}
	}
	else
	{
		switch(direction_2)
		{
			case 1 :n2--;break;
			case 2 :n2++;break;
			case 3 :m2--;break;
			case 4 :m2++;break;
		}
	}
	change_thing();//检查是否击中障碍物
	change_home();//检查是否击中老家
	change_bullet();//检查是否击中子弹
	change_tank();//检查是否击中我的坦克
	if(check_bullet(m2,n2))	
		print_bullet(m2,n2);
	else
		m2=0,n2=0;
}


void shoot_3()
{

	if(m3!=0 || n3!=0)
		if(map[n3][m3]==0)//如果子弹还留在地图上，就清除掉		
			clear_bullet(m3,n3);
	if(m3==0 && n3==0)//代表现在场上没有坦克3号的子弹,则重新发射子弹
	{
		switch(state_3)
		{
			case 1 :
				{
					m3=x3;
					n3=y3-2;
					direction_3=1;
				}break;
			case 2 :
				{
					m3=x3;
					n3=y3+2;
					direction_3=2;
				}break;
			case 3 :
				{
					m3=x3-2;
					n3=y3;
					direction_3=3;
				}break;
			case 4 :
				{
					m3=x3+2;
					n3=y3;
					direction_3=4;
				}break;
		}
	}
	else
	{
		switch(direction_3)
		{
			case 1 :n3--;break;
			case 2 :n3++;break;
			case 3 :m3--;break;
			case 4 :m3++;break;
		}
	}
	change_thing();//检查是否击中障碍物
	change_home();//检查是否击中老家
	change_bullet();//检查是否击中子弹
	change_tank();//检查是否击中我的坦克
	if(check_bullet(m3,n3))
		print_bullet(m3,n3);
	else
		m3=0,n3=0;
}

void turn_up(int a[][3])
{
	int tank_up[3][3]={{0,1,0},{1,1,1},{1,0,1}};
	if(state==1)
	{
		if(judge(x,y,state))
		{
			clear_my_tank();
			y--;
			print_my_tank();
			refresh_map();
		}
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_up[i][j];
		clear_my_tank();
		print_my_tank();
		state=1;
		refresh_map();

	}
	change_star();
}


void turn_down(int a[][3])
{
	int tank_down[3][3]={{1,0,1},{1,1,1},{0,1,0}};
	if(state==2)
	{
		if(judge(x,y,state))
		{
			clear_my_tank();
			y++;
			print_my_tank();
			refresh_map();
		}
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_down[i][j];
		clear_my_tank();
		print_my_tank();
		state=2;
		refresh_map();
	}
	change_star();

}

void turn_left(int a[][3])
{
	int tank_left[3][3]={{0,1,1},{1,1,0},{0,1,1}};
	if(state==3)
	{
		if(judge(x,y,state))
		{
			clear_my_tank();
			x--;
			print_my_tank();
			refresh_map();
		}
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_left[i][j];
		clear_my_tank();
		print_my_tank();
		state=3;
		refresh_map();
	}
	change_star();

}

void turn_right(int a[][3])
{
	int tank_right[3][3]={{1,1,0},{0,1,1},{1,1,0}};
	if(state==4)
	{
		if(judge(x,y,state))
		{
			clear_my_tank();
			x++;
			print_my_tank();
			refresh_map();
		}
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_right[i][j];
		clear_my_tank();
		print_my_tank();
		state=4;
		refresh_map();
	}
	change_star();

}

void turn_up_1(int a[][3])
{
	int tank_up[3][3]={{0,1,0},{1,1,1},{1,0,1}};
	if(state_1==1)
	{
		clear_tank_1();
		y1--;
		print_tank_1();
		refresh_map();
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_up[i][j];
		clear_tank_1();
		print_tank_1();
		state_1=1;
		refresh_map();
	}
}

void turn_down_1(int a[][3])
{
	int tank_down[3][3]={{1,0,1},{1,1,1},{0,1,0}};
	if(state_1==2)
	{
		clear_tank_1();
		y1++;
		print_tank_1();
		refresh_map();
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_down[i][j];
		clear_tank_1();
		print_tank_1();
		state_1=2;
		refresh_map();
	}
}

void turn_left_1(int a[][3])
{
	int tank_left[3][3]={{0,1,1},{1,1,0},{0,1,1}};
	if(state_1==3)
	{
		clear_tank_1();
		x1--;
		print_tank_1();
		refresh_map();
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_left[i][j];
		clear_tank_1();
		print_tank_1();
		state_1=3;
		refresh_map();
	}
}

void turn_right_1(int a[][3])
{
	int tank_right[3][3]={{1,1,0},{0,1,1},{1,1,0}};
	if(state_1==4)
	{
		clear_tank_1();
		x1++;
		print_tank_1();
		refresh_map();
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_right[i][j];
		clear_tank_1();
		print_tank_1();
		state_1=4;
		refresh_map();
	}
}

void turn_up_2(int a[][3])
{
	int tank_up[3][3]={{0,1,0},{1,1,1},{1,0,1}};
	if(state_2==1)
	{
		clear_tank_2();
		y2--;
		print_tank_2();
		refresh_map();
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_up[i][j];
		clear_tank_2();
		print_tank_2();
		state_2=1;
		refresh_map();
	}
}

void turn_down_2(int a[][3])
{
	int tank_down[3][3]={{1,0,1},{1,1,1},{0,1,0}};
	if(state_2==2)
	{
		clear_tank_2();
		y2++;
		print_tank_2();
		refresh_map();
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_down[i][j];
		clear_tank_2();
		print_tank_2();
		state_2=2;
		refresh_map();
	}
}

void turn_left_2(int a[][3])
{
	int tank_left[3][3]={{0,1,1},{1,1,0},{0,1,1}};
	if(state_2==3)
	{
		clear_tank_2();
		x2--;
		print_tank_2();
		refresh_map();
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_left[i][j];
		clear_tank_2();
		print_tank_2();
		state_2=3;
		refresh_map();
	}
}

void turn_right_2(int a[][3])
{
	int tank_right[3][3]={{1,1,0},{0,1,1},{1,1,0}};
	if(state_2==4)
	{
		clear_tank_2();
		x2++;
		print_tank_2();
		refresh_map();
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_right[i][j];
		clear_tank_2();
		print_tank_2();
		state_2=4;
		refresh_map();
	}
}

void turn_up_3(int a[][3])
{
	int tank_up[3][3]={{0,1,0},{1,1,1},{1,0,1}};
	if(state_3==1)
	{
		clear_tank_3();
		y3--;
		print_tank_3();
		refresh_map();
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_up[i][j];
		clear_tank_3();
		print_tank_3();
		state_3=1;
		refresh_map();
	}
}

void turn_down_3(int a[][3])
{
	int tank_down[3][3]={{1,0,1},{1,1,1},{0,1,0}};
	if(state_3==2)
	{
		clear_tank_3();
		y3++;
		print_tank_3();
		refresh_map();
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_down[i][j];
		clear_tank_3();
		print_tank_3();
		state_3=2;
		refresh_map();
	}
}

void turn_left_3(int a[][3])
{
	int tank_left[3][3]={{0,1,1},{1,1,0},{0,1,1}};
	if(state_3==3)
	{
		clear_tank_3();
		x3--;
		print_tank_3();
		refresh_map();
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_left[i][j];
		clear_tank_3();
		print_tank_3();
		state_3=3;
		refresh_map();
	}
}

void turn_right_3(int a[][3])
{
	int tank_right[3][3]={{1,1,0},{0,1,1},{1,1,0}};
	if(state_3==4)
	{
		clear_tank_3();
		x3++;
		print_tank_3();
		refresh_map();
	}
	else
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				a[i][j]=tank_right[i][j];
		clear_tank_3();
		print_tank_3();
		state_3=4;
		refresh_map();
	}
}

int judge(int x,int y,int state)//x,y坦克当前坐标,state坦克当前方向
{
	switch(state)
	{
	case 1 :if(map[y-2][x]==0 && map[y-1][x-1]==0 && map[y-1][x+1]==0 && map[y-2][x-1]==0 && map[y-2][x+1]==0)
				return 1;
			else
				return 0;
	case 2 :if(map[y+2][x]==0 && map[y+1][x-1]==0 && map[y+1][x+1]==0 && map[y+2][x-1]==0 && map[y+2][x+1]==0)
				return 1;
			else
				return 0;
	case 3 :if(map[y][x-2]==0 && map[y-1][x-1]==0 && map[y+1][x-1]==0 && map[y-1][x-2]==0 && map[y+1][x-2]==0)
				return 1;
			else
				return 0;
	case 4 :if(map[y][x+2]==0 && map[y-1][x+1]==0 && map[y+1][x+1]==0 && map[y-1][x+2]==0 && map[y+1][x+2]==0)
				return 1;
			else
				return 0;
	}
}

int judge2(int x,int y,int state)//x,y坦克当前坐标,state坦克当前方向
{
	switch(state)
	{
	case 1 :if(map[y-2][x]==0 && map[y-2][x-1]==0 && map[y-2][x+1]==0)
				return 1;
			else
				return 0;
	case 2 :if(map[y+2][x]==0 && map[y+2][x-1]==0 && map[y+2][x+1]==0)
				return 1;
			else
				return 0;
	case 3 :if(map[y][x-2]==0 && map[y-1][x-2]==0 && map[y+1][x-2]==0)
				return 1;
			else
				return 0;
	case 4 :if(map[y][x+2]==0 && map[y-1][x+2]==0 && map[y+1][x+2]==0)
				return 1;
			else
				return 0;
	}
}

void refresh_map()               //i代表行，即纵坐标；j代表列，即横坐标
{
	{
		for(int i=0;i<30;i++)          //首先地图清零
			for(int j=0;j<30;j++)
				map[i][j]=0;
	}

	{
		for(int i=0;i<30;i++)    //地图第一部分：围墙（完全不动）
		{
			map[i][0]=1;
			map[i][29]=1;
		}
		for(int j=0;j<30;j++) 
		{
			map[0][j]=1;
			map[29][j]=1;
		}
	}

	{
		for(int i=0;i<3;i++)   //地图第二部分：老家（几乎不动）
			for(int j=0;j<4;j++)
				map[i+26][j+13]=home[i][j];
	}

	{
		for(int i=0;i<28;i++)  //地图第三部分：障碍物（有时改变）
			for(int j=0;j<28;j++)
				map[i+1][j+1]=thing[i][j];
	}

	{
		switch(state)          //地图第四部分：坦克（总是改变）
		{
		case 1 :
			{
				map[y-1][x-1]=0;  map[y-1][x]=1;      map[y-1][x+1]=0;
				map[y][x-1]=1;    map[y][x]=1;        map[y][x+1]=1;
				map[y+1][x-1]=1;  map[y+1][x]=0;      map[y+1][x+1]=1;

			}break;
		case 2 :
			{
				map[y-1][x-1]=1;  map[y-1][x]=0;      map[y-1][x+1]=1;
				map[y][x-1]=1;    map[y][x]=1;        map[y][x+1]=1;
				map[y+1][x-1]=0;  map[y+1][x]=1;      map[y+1][x+1]=0;
			}break;
		case 3 :
			{
				map[y-1][x-1]=0;  map[y-1][x]=1;      map[y-1][x+1]=1;
				map[y][x-1]=1;    map[y][x]=1;        map[y][x+1]=0;
				map[y+1][x-1]=0;  map[y+1][x]=1;      map[y+1][x+1]=1;
			}break;
		case 4 :
			{
				map[y-1][x-1]=1;  map[y-1][x]=1;      map[y-1][x+1]=0;
				map[y][x-1]=0;    map[y][x]=1;        map[y][x+1]=1;
				map[y+1][x-1]=1;  map[y+1][x]=1;      map[y+1][x+1]=0;
			}break;
		}

		switch(state_1)
		{
		case 1 :
			{
				map[y1-1][x1-1]=0;  map[y1-1][x1]=1;      map[y1-1][x1+1]=0;
				map[y1][x1-1]=1;    map[y1][x1]=1;        map[y1][x1+1]=1;
				map[y1+1][x1-1]=1;  map[y1+1][x1]=0;      map[y1+1][x1+1]=1;

			}break;
		case 2 :
			{
				map[y1-1][x1-1]=1;  map[y1-1][x1]=0;      map[y1-1][x1+1]=1;
				map[y1][x1-1]=1;    map[y1][x1]=1;        map[y1][x1+1]=1;
				map[y1+1][x1-1]=0;  map[y1+1][x1]=1;      map[y1+1][x1+1]=0;
			}break;
		case 3 :
			{
				map[y1-1][x1-1]=0;  map[y1-1][x1]=1;      map[y1-1][x1+1]=1;
				map[y1][x1-1]=1;    map[y1][x1]=1;        map[y1][x1+1]=0;
				map[y1+1][x1-1]=0;  map[y1+1][x1]=1;      map[y1+1][x1+1]=1;
			}break;
		case 4 :
			{
				map[y1-1][x1-1]=1;  map[y1-1][x1]=1;      map[y1-1][x1+1]=0;
				map[y1][x1-1]=0;    map[y1][x1]=1;        map[y1][x1+1]=1;
				map[y1+1][x1-1]=1;  map[y1+1][x1]=1;      map[y1+1][x1+1]=0;
			}break;
		}

		switch(state_2)
		{
		case 1 :
			{
				map[y2-1][x2-1]=0;  map[y2-1][x2]=1;      map[y2-1][x2+1]=0;
				map[y2][x2-1]=1;    map[y2][x2]=1;        map[y2][x2+1]=1;
				map[y2+1][x2-1]=1;  map[y2+1][x2]=0;      map[y2+1][x2+1]=1;

			}break;
		case 2 :
			{
				map[y2-1][x2-1]=1;  map[y2-1][x2]=0;      map[y2-1][x2+1]=1;
				map[y2][x2-1]=1;    map[y2][x2]=1;        map[y2][x2+1]=1;
				map[y2+1][x2-1]=0;  map[y2+1][x2]=1;      map[y2+1][x2+1]=0;
			}break;
		case 3 :
			{
				map[y2-1][x2-1]=0;  map[y2-1][x2]=1;      map[y2-1][x2+1]=1;
				map[y2][x2-1]=1;    map[y2][x2]=1;        map[y2][x2+1]=0;
				map[y2+1][x2-1]=0;  map[y2+1][x2]=1;      map[y2+1][x2+1]=1;
			}break;
		case 4 :
			{
				map[y2-1][x2-1]=1;  map[y2-1][x2]=1;      map[y2-1][x2+1]=0;
				map[y2][x2-1]=0;    map[y2][x2]=1;        map[y2][x2+1]=1;
				map[y2+1][x2-1]=1;  map[y2+1][x2]=1;      map[y2+1][x2+1]=0;
			}break;
		}

		switch(state_3)
		{
		case 1 :
			{
				map[y3-1][x3-1]=0;  map[y3-1][x3]=1;      map[y3-1][x3+1]=0;
				map[y3][x3-1]=1;    map[y3][x3]=1;        map[y3][x3+1]=1;
				map[y3+1][x3-1]=1;  map[y3+1][x3]=0;      map[y3+1][x3+1]=1;

			}break;
		case 2 :
			{
				map[y3-1][x3-1]=1;  map[y3-1][x3]=0;      map[y3-1][x3+1]=1;
				map[y3][x3-1]=1;    map[y3][x3]=1;        map[y3][x3+1]=1;
				map[y3+1][x3-1]=0;  map[y3+1][x3]=1;      map[y3+1][x3+1]=0;
			}break;
		case 3 :
			{
				map[y3-1][x3-1]=0;  map[y3-1][x3]=1;      map[y3-1][x3+1]=1;
				map[y3][x3-1]=1;    map[y3][x3]=1;        map[y3][x3+1]=0;
				map[y3+1][x3-1]=0;  map[y3+1][x3]=1;      map[y3+1][x3+1]=1;
			}break;
		case 4 :
			{
				map[y3-1][x3-1]=1;  map[y3-1][x3]=1;      map[y3-1][x3+1]=0;
				map[y3][x3-1]=0;    map[y3][x3]=1;        map[y3][x3+1]=1;
				map[y3+1][x3-1]=1;  map[y3+1][x3]=1;      map[y3+1][x3+1]=0;
			}break;
		}
	}
}


void my_move()
{
	char key;
	if (kbhit()) //检测，如果有按键就执行if里面的
	{
		key = getch();//捕获按键
		switch( key ) 
		{
		case 72:turn_up(my_tank);//上
			break;
		case 75:turn_left(my_tank);//左
			break;
		case 77:turn_right(my_tank);//右
			break;
		case 80:turn_down(my_tank);//下
			break;
		case 32:stop();//空格 暂停或开始
			break;
		case 104:help();//小h切换到帮助菜单
			break;
		case 115:switch_skin(),print_my_tank();//小s键切换皮肤
			break;
		case 119:switch_weapons();//小w键切换武器
			break;

		case 27:exit(0);//Esc 退出
		default: ;
		}
	}
}

int check1(int x,int y)//在正上面，用它检测
{
	for(int j=y;j<27;j++)
		if(map[j][x]==4)
			return 0;
	return 1;
}

int check2(int x,int y)//在正左面，用它检测
{
	for(int i=x;i<14;i++)
		if(map[y][i]==4)
			return 0;
	return 1;
}

int check3(int x,int y)//在正右面，用它检测
{
	for(int i=x;i>15;i--)
		if(map[y][i]==4)
			return 0;
	return 1;
}

void move_1()
{
	if((x1==14 || x1==15) && check1(x1,y1))//在正上面
	{
			if(state_1!=2)
				turn_down_1(tank_1);
	}
	else if(x1<14 && y1==27 && check2(x1,y1))//在正左面
	{
			if(state_1!=4)
				turn_right_1(tank_1);
	}
	else if(x1>15 && y1==27 && check3(x1,y1))//在正右面
	{
			if(state_1!=3)
				turn_left_1(tank_1);
	}
	else
	{
		if(judge2(x1,y1,cp1))
			switch(cp1)
			{
			case 1 :turn_up_1(tank_1);break;
			case 2 :turn_down_1(tank_1);break;
			case 3 :turn_left_1(tank_1);break;
			case 4 :turn_right_1(tank_1);break;
			}
		while(judge2(x1,y1,cp1) == 0)
		{
			cp1=(rand()%4+1);
		}

	}


}

void move_2()
{
	if((x2==14 || x2==15) && check1(x2,y2))//在正上面
	{
			if(state_2!=2)
				turn_down_2(tank_2);
	}
	else if(x2<14 && y2==27 && check2(x2,y2))//在正左面
	{
			if(state_2!=4)
				turn_right_2(tank_2);
	}
	else if(x2>15 && y2==27 && check3(x2,y2))//在正右面
	{
			if(state_2!=3)
				turn_left_2(tank_2);
	}
	else
	{
		if(judge2(x2,y2,cp2))
			switch(cp2)
			{
			case 1 :turn_up_2(tank_2);break;
			case 2 :turn_down_2(tank_2);break;
			case 3 :turn_left_2(tank_2);break;
			case 4 :turn_right_2(tank_2);break;
			}
		while(judge2(x2,y2,cp2) == 0)
		{
			cp2=(rand()%4+1);
		}

	}
}

void move_3()
{
	if((x3==14 || x3==15) && check1(x3,y3))//在正上面
	{
			if(state_3!=2)
				turn_down_3(tank_3);
	}
	else if(x3<14 && y3==27 && check2(x3,y3))//在正左面
	{
			if(state_3!=4)
				turn_right_3(tank_3);
	}
	else if(x3>15 && y3==27 && check3(x3,y3))//在正右面
	{

			if(state_3!=3)
				turn_left_3(tank_3);
	}
	else
	{
		if(judge2(x3,y3,cp3))
			switch(cp3)
			{
			case 1 :turn_up_3(tank_3);break;
			case 2 :turn_down_3(tank_3);break;
			case 3 :turn_left_3(tank_3);break;
			case 4 :turn_right_3(tank_3);break;
			}
		while(judge2(x3,y3,cp3) == 0)
		{
			cp3=(rand()%4+1);
		}



	}
}

int check_bullet(int x,int y)
{
	if(map[y][x])
		return 0;
	return 1;
}

void change_thing()//物品被子弹击中会改变
{
	if(m>0&&m<29 && n>0&&n<29)//被我的子弹击中
		if(thing[n-1][m-1]==1)//打中第一种方块
		{
			if(weapons==2)
			{
				if(thing[n][m-1]==1)
					thing[n][m-1]=0;
					gotoxy(2*m,n+1);
					printf("  ");//擦去方块
				if(thing[n-2][m-1]==1)
					thing[n-2][m-1]=0;
					gotoxy(2*m,n-1);
					printf("  ");//擦去方块
				if(thing[n-1][m]==1)
					thing[n-1][m]=0;
					gotoxy(2*(m+1),n);
					printf("  ");//擦去方块
				if(thing[n-1][m-2]==1)
					thing[n-1][m-2]=0;
					gotoxy(2*(m-1),n);
					printf("  ");//擦去方块
				thing[n-1][m-1]=0;
				gotoxy(2*m,n);
				printf("  ");//擦去方块
				m=0,n=0;//子弹消失
				print_thing();
				refresh_map();
			}
			else if(weapons==3)
			{
				thing[n-1][m-1]=0;
				gotoxy(2*m,n);
				printf("  ");//擦去方块
				print_my_bullet(m,n);
				print_thing();
				refresh_map();
			}
			else
			{
				thing[n-1][m-1]=0;
				gotoxy(2*m,n);
				printf("  ");//擦去方块
				m=0,n=0;//子弹消失
				print_thing();
				refresh_map();
			}



		}

		else if(thing[n-1][m-1]==2)//打到第二种方块
		{
			if(weapons==5)
			{
				thing[n-1][m-1]=0;
				gotoxy(2*m,n);
				printf("  ");
				m=0,n=0;//子弹消失
				print_thing();
				refresh_map();
			}
			else if(weapons==2)
			{
				m=0,n=0;
			}
			else
			{
				thing[n-1][m-1]=1;
				m=0,n=0;//子弹消失
				print_thing();
				refresh_map();
			}
		}

		else if(thing[n-1][m-1]==3)
		{
			if(weapons==4 || weapons==2)
				m=0,n=0;
			else if(weapons==5)
			{
				thing[n-1][m-1]=0;
				gotoxy(2*m,n);
				printf("  ");
				m=0,n=0;//子弹消失
				print_thing();
				refresh_map();
			}
			else
			{
				thing[n-1][m-1]=2;
				m=0,n=0;//子弹消失
				print_thing();
				refresh_map();
			}
		}

		else if(thing[n-1][m-1]==4)//此方块不受子弹影响
		{
			m=0,n=0;//子弹消失
		}

	if(m1>0&&m1<29 && n1>0&&n1<29)//被坦克1号子弹击中
		if(thing[n1-1][m1-1]==1)
		{
			thing[n1-1][m1-1]=0;
			gotoxy(2*m1,n1);
			printf("  ");
			m1=0,n1=0;
			print_thing();
			refresh_map();
		}
		else if(thing[n1-1][m1-1]==2)
		{
			thing[n1-1][m1-1]=1;
			m1=0,n1=0;//子弹消失
			print_thing();
			refresh_map();
		}
		else if(thing[n1-1][m1-1]==3)
		{
			thing[n1-1][m1-1]=2;
			m1=0,n1=0;//子弹消失
			print_thing();
			refresh_map();
		}
		else if(thing[n-1][m-1]==4)//此方块不受子弹影响
		{
			m1=0,n1=0;//子弹消失
		}

	if(m2>0&&m2<29 && n2>0&&n2<29)
		if(thing[n2-1][m2-1]==1)
		{
			thing[n2-1][m2-1]=0;
			gotoxy(2*m2,n2);
			printf("  ");
			m2=0,n2=0;
			print_thing();
			refresh_map();
		}
		else if(thing[n2-1][m2-1]==2)
		{
			thing[n2-1][m2-1]=1;
			m2=0,n2=0;//子弹消失
			print_thing();
			refresh_map();
		}
		else if(thing[n2-1][m2-1]==3)
		{
			thing[n2-1][m2-1]=2;
			m2=0,n2=0;//子弹消失
			print_thing();
			refresh_map();
		}
		else if(thing[n2-1][m2-1]==4)//此方块不受子弹影响
		{
			m2=0,n2=0;//子弹消失
		}

	if(m3>0&&m3<29 && n3>0&&n3<29)
		if(thing[n3-1][m3-1]==1)
		{
			thing[n3-1][m3-1]=0;
			gotoxy(2*m3,n3);
			printf("  ");
			m3=0,n3=0;
			print_thing();
			refresh_map();
		}
		else if(thing[n3-1][m3-1]==2)
		{
			thing[n3-1][m3-1]=1;
			m3=0,n3=0;//子弹消失
			print_thing();
			refresh_map();
		}
		else if(thing[n3-1][m3-1]==3)
		{
			thing[n3-1][m3-1]=2;
			m3=0,n3=0;//子弹消失
			print_thing();
			refresh_map();
		}
		else if(thing[n3-1][m3-1]==4)//此方块不受子弹影响
		{
			m3=0,n3=0;//子弹消失
		}



}

void change_home()
{
	if(m==14&&n==27 || m==15&&n==27 || m==14&&n==28 || m==15&&n==28)//如果子弹打到老家里，游戏结束
		 gameover();
	else if(m>12 && n>25 && m<17 && n<29)
		if(weapons==4)//只有4号子弹对老家的墙有效
		{
			home[n-26][m-13]=3;
			screen_2("你修复了老家哦！",1);
			m=0,n=0;   //子弹消失
			print_home();
			refresh_map();
		}
		else
			m=0,n=0;


	if(m1==14&&n1==27 || m1==15&&n1==27 || m1==14&&n1==28 || m1==15&&n1==28)
		 gameover();
	else if(m1>12 && n1>25 && m1<17 && n1<29)

			if(home[n1-26][m1-13]==1)         
			{
				home[n1-26][m1-13]=0;
				screen_2("警报! 警报!",4);
				gotoxy(2*m1,n1);
				printf("  ");
				m1=0,n1=0;
				print_home();
				refresh_map();
			}
			else if(home[n1-26][m1-13]==2)        
			{
				home[n1-26][m1-13]=1;
				screen_2("敌人威胁到了你的老家",4);
				m1=0,n1=0;   //子弹消失
				print_home();
				refresh_map();
			}
			else if(home[n1-26][m1-13]==3)         
			{
				home[n1-26][m1-13]=2;
				screen_2("敌人对你的防御开始了打击",4);
				m1=0,n1=0;   //子弹消失
				print_home();
				refresh_map();
			}

	if(m2==14&&n2==27 || m2==15&&n2==27 || m2==14&&n2==28 || m2==15&&n2==28)
		 gameover();
	else if(m2>12 && n2>25 && m2<17 && n2<29)
		if(home[n2-26][m2-13]==1)         
		{
			home[n2-26][m2-13]=0;
			screen_2("警报! 警报!",4);
			gotoxy(2*m2,n2);
			printf("  ");
			m2=0,n2=0;
			print_home();
			refresh_map();
		}
		else if(home[n2-26][m2-13]==2)        
		{
			home[n2-26][m2-13]=1;
			screen_2("敌人威胁到了你的老家",4);
			m2=0,n2=0;   //子弹消失
			print_home();
			refresh_map();
		}
		else if(home[n2-26][m2-13]==3)         
		{
			home[n2-26][m2-13]=2;
			screen_2("敌人对你的防御开始了打击",4);
			m2=0,n2=0;   //子弹消失
			print_home();
			refresh_map();
		}

	if(m3==14&&n3==27 || m3==15&&n3==27 || m3==14&&n3==28 || m3==15&&n3==28)
		 gameover();
	else if(m3>12 && n3>25 && m3<17 && n3<29)
		if(home[n3-26][m3-13]==1)        
		{
			home[n3-26][m3-13]=0;
			screen_2("警报! 警报!",4);
			gotoxy(2*m3,n3);
			printf("  ");
			m3=0,n3=0;
			print_home();
			refresh_map();
		}
		else if(home[n3-26][m3-13]==2)        
		{
			home[n3-26][m3-13]=1;
			screen_2("敌人威胁到了你的老家",4);
			m3=0,n3=0;   //子弹消失
			print_home();
			refresh_map();
		}
		else if(home[n3-26][m3-13]==3)         
		{
			home[n3-26][m3-13]=2;
			screen_2("敌人对你的防御开始了打击",4);
			m3=0,n3=0;   //子弹消失
			print_home();
			refresh_map();
		}


}

void change_bullet()//当我的坦克子弹和敌人坦克子弹碰撞
{
	if(m!=0 && m==m1 && n==n1)
	{
		clear_bullet(m,n);
		m=0,n=0,
		clear_bullet(m1,n1);
		m1=0,n1=0;
	}
	if(m!=0 && m==m2 && n==n2)
	{
		clear_bullet(m,n);
		m=0,n=0,
		clear_bullet(m2,n2);
		m2=0,n2=0;
	}
	if(m!=0 && m==m3 && n==n3)
	{
		clear_bullet(m,n);
		m=0,n=0,
		clear_bullet(m3,n3);
		m3=0,n3=0;
	}
}

void change_tank()
{
	switch(state)
	{
	case 1 :                           //当我的坦克方向向上时
		{
			if(x==m1&&(y-1)==n1 || (x-1)==m1&&y==n1 || x==m1&&y==n1 || (x+1)==m1&&y==n1 || (x-1)==m1&&(y+1)==n1 || (x+1)==m1&&(y+1)==n1)//如果坦克1号子弹打到我的坦克
				clear_my_tank(),screen_2("坦克1号击中了你  生命值减1",4),x=10,y=27,m1=0,n1=0,life--,check_game(),turn_up(my_tank);//我的坦克回到初始位置，坦克1号子弹消失，生命值减1，检查游戏是否结束，若没结束初始化方向
			if(x==m2&&(y-1)==n2 || (x-1)==m2&&y==n2 || x==m2&&y==n2 || (x+1)==m2&&y==n2 || (x-1)==m2&&(y+1)==n2 || (x+1)==m2&&(y+1)==n2)//如果坦克2号子弹打到我的坦克
				clear_my_tank(),screen_2("坦克2号击中了你  生命值减1",4),x=10,y=27,m2=0,n2=0,life--,check_game(),turn_up(my_tank);//我的坦克回到初始位置，坦克2号子弹消失，生命值减1，检查游戏是否结束，若没结束初始化方向
			if(x==m3&&(y-1)==n3 || (x-1)==m3&&y==n3 || x==m3&&y==n3 || (x+1)==m3&&y==n3 || (x-1)==m3&&(y+1)==n3 || (x+1)==m3&&(y+1)==n3)//如果坦克3号子弹打到我的坦克
				clear_my_tank(),screen_2("坦克3号击中了你  生命值减1",4),x=10,y=27,m3=0,n3=0,life--,check_game(),turn_up(my_tank);//我的坦克回到初始位置，坦克3号子弹消失，生命值减1，检查游戏是否结束，若没结束初始化方向
		}break;
	case 2 :
		{
			if(x==m1&&(y+1)==n1 || (x-1)==m1&&y==n1 || x==m1&&y==n1 || (x+1)==m1&&y==n1 || (x-1)==m1&&(y-1)==n1 || (x+1)==m1&&(y-1)==n1)
				clear_my_tank(),screen_2("坦克1号击中了你  生命值减1",4),x=10,y=27,m1=0,n1=0,life--,check_game(),turn_up(my_tank);
			if(x==m2&&(y+1)==n2 || (x-1)==m2&&y==n2 || x==m2&&y==n2 || (x+1)==m2&&y==n2 || (x-1)==m2&&(y-1)==n2 || (x+1)==m2&&(y-1)==n2)
				clear_my_tank(),screen_2("坦克2号击中了你  生命值减1",4),x=10,y=27,m2=0,n2=0,life--,check_game(),turn_up(my_tank);
			if(x==m3&&(y+1)==n3 || (x-1)==m3&&y==n3 || x==m3&&y==n3 || (x+1)==m3&&y==n3 || (x-1)==m3&&(y-1)==n3 || (x+1)==m3&&(y-1)==n3)
				clear_my_tank(),screen_2("坦克3号击中了你  生命值减1",4),x=10,y=27,m3=0,n3=0,life--,check_game(),turn_up(my_tank);

		}
	case 3 :
		{
			if(x==m1&&(y-1)==n1 || (x-1)==m1&&y==n1 || x==m1&&y==n1 || (x+1)==m1&&(y-1)==n1 || x==m1&&(y+1)==n1 || (x+1)==m1&&(y+1)==n1)
				clear_my_tank(),screen_2("坦克1号击中了你  生命值减1",4),x=10,y=27,m1=0,n1=0,life--,check_game(),turn_up(my_tank);
			if(x==m2&&(y-1)==n2 || (x-1)==m2&&y==n2 || x==m2&&y==n2 || (x+1)==m2&&(y-1)==n2 || x==m2&&(y+1)==n2 || (x+1)==m2&&(y+1)==n2)
				clear_my_tank(),screen_2("坦克2号击中了你  生命值减1",4),x=10,y=27,m2=0,n2=0,life--,check_game(),turn_up(my_tank);
			if(x==m3&&(y-1)==n3 || (x-1)==m3&&y==n3 || x==m3&&y==n3 || (x+1)==m3&&(y-1)==n3 || x==m3&&(y+1)==n3 || (x+1)==m3&&(y+1)==n3)
				clear_my_tank(),screen_2("坦克3号击中了你  生命值减1",4),x=10,y=27,m3=0,n3=0,life--,check_game(),turn_up(my_tank);
		}
	case 4 :
		{
			if(x==m1&&(y-1)==n1 || (x-1)==m1&&(y-1)==n1 || x==m1&&y==n1 || (x-1)==m1&&(y+1)==n1 || x==m1&&(y+1)==n1 || (x+1)==m1&&y==n1)
				clear_my_tank(),screen_2("坦克1号击中了你  生命值减1",4),x=10,y=27,m1=0,n1=0,life--,check_game(),turn_up(my_tank);
			if(x==m2&&(y-1)==n2 || (x-1)==m2&&(y-1)==n2 || x==m2&&y==n2 || (x-1)==m2&&(y+1)==n2 || x==m2&&(y+1)==n2 || (x+1)==m2&&y==n2)
				clear_my_tank(),screen_2("坦克2号击中了你  生命值减1",4),x=10,y=27,m2=0,n2=0,life--,check_game(),turn_up(my_tank);
			if(x==m3&&(y-1)==n3 || (x-1)==m3&&(y-1)==n3 || x==m3&&y==n3 || (x-1)==m3&&(y+1)==n3 || x==m3&&(y+1)==n3 || (x+1)==m3&&y==n3)
				clear_my_tank(),screen_2("坦克3号击中了你  生命值减1",4),x=10,y=27,m3=0,n3=0,life--,check_game(),turn_up(my_tank);
		}
	}
}

void change_tank_1()
{
	switch(state_1)
	{
	case 1 :
		{
			if(x1==m&&(y1-1)==n || (x1-1)==m&&y1==n || x1==m&&y1==n || (x1+1)==m&&y1==n || (x1-1)==m&&(y1+1)==n || (x1+1)==m&&(y1+1)==n)//如果我的坦克子弹打到坦克1号
				clear_tank_1(),screen_2("你击中了坦克1号   +100分",3),x1=2,y1=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();//坦克1号回到初始位置，我的坦克号子弹消失，敌人数量值减1,分数加100，检查胜负

		}break;
	case 2 :
		{
			if(x1==m&&(y1+1)==n || (x1-1)==m&&y1==n || x1==m&&y1==n || (x1+1)==m&&y1==n || (x1-1)==m&&(y1-1)==n || (x1+1)==m&&(y1-1)==n)
				clear_tank_1(),screen_2("你击中了坦克1号   +100分",3),x1=2,y1=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	case 3 :
		{
			if(x1==m&&(y1-1)==n || (x1-1)==m&&y1==n || x1==m&&y1==n || (x1+1)==m&&(y1-1)==n || x1==m&&(y1+1)==n || (x1+1)==m&&(y1+1)==n)
				clear_tank_1(),screen_2("你击中了坦克1号   +100分",3),x1=2,y1=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	case 4 :
		{
			if(x1==m&&(y1-1)==n || (x1-1)==m&&(y1-1)==n || x1==m&&y1==n || (x1-1)==m&&(y1+1)==n || x1==m&&(y1+1)==n || (x1+1)==m&&y1==n)
				clear_tank_1(),screen_2("你击中了坦克1号   +100分",3),x1=2,y1=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	}
}

void change_tank_2()
{
	switch(state_2)
	{
	case 1 :
		{
			if(x2==m&&(y2-1)==n || (x2-1)==m&&y2==n || x2==m&&y2==n || (x2+1)==m&&y2==n || (x2-1)==m&&(y2+1)==n || (x2+1)==m&&(y2+1)==n)//如果我的坦克子弹打到坦克2号
				clear_tank_2(),screen_2("你击中了坦克2号   +100分",3),x2=14,y2=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();//坦克2号回到初始位置，我的坦克号子弹消失，敌人数量值减1,分数加100，检查胜负

		}break;
	case 2 :
		{
			if(x2==m&&(y2+1)==n || (x2-1)==m&&y2==n || x2==m&&y2==n || (x2+1)==m&&y2==n || (x2-1)==m&&(y2-1)==n || (x2+1)==m&&(y2-1)==n)
				clear_tank_2(),screen_2("你击中了坦克2号   +100分",3),x2=14,y2=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	case 3 :
		{
			if(x2==m&&(y2-1)==n || (x2-1)==m&&y2==n || x2==m&&y2==n || (x2+1)==m&&(y2-1)==n || x2==m&&(y2+1)==n || (x2+1)==m&&(y2+1)==n)
				clear_tank_2(),screen_2("你击中了坦克2号   +100分",3),x2=14,y2=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	case 4 :
		{
			if(x2==m&&(y2-1)==n || (x2-1)==m&&(y2-1)==n || x2==m&&y2==n || (x2-1)==m&&(y2+1)==n || x2==m&&(y2+1)==n || (x2+1)==m&&y2==n)
				clear_tank_2(),screen_2("你击中了坦克2号   +100分",3),x2=14,y2=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	}
}

void change_tank_3()
{
	switch(state_3)
	{
	case 1 :
		{
			if(x3==m&&(y3-1)==n || (x3-1)==m&&y3==n || x3==m&&y3==n || (x3+1)==m&&y3==n || (x3-1)==m&&(y3+1)==n || (x3+1)==m&&(y3+1)==n)//如果我的坦克子弹打到坦克3号
				clear_tank_3(),screen_2("你击中了坦克3号   +100分",3),x3=27,y3=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();//坦克3号回到初始位置，我的坦克号子弹消失，敌人数量值减1,分数加100，检查胜负

		}break;
	case 2 :
		{
			if(x3==m&&(y3+1)==n || (x3-1)==m&&y3==n || x3==m&&y3==n || (x3+1)==m&&y3==n || (x3-1)==m&&(y3-1)==n || (x3+1)==m&&(y3-1)==n)
				clear_tank_3(),screen_2("你击中了坦克3号   +100分",3),x3=27,y3=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	case 3 :
		{
			if(x3==m&&(y3-1)==n || (x3-1)==m&&y3==n || x3==m&&y3==n || (x3+1)==m&&(y3-1)==n || x3==m&&(y3+1)==n || (x3+1)==m&&(y3+1)==n)
				clear_tank_3(),screen_2("你击中了坦克3号   +100分",3),x3=27,y3=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	case 4 :
		{
			if(x3==m&&(y3-1)==n || (x3-1)==m&&(y3-1)==n || x3==m&&y3==n || (x3-1)==m&&(y3+1)==n || x3==m&&(y3+1)==n || (x3+1)==m&&y3==n)
				clear_tank_3(),screen_2("你击中了坦克3号   +100分",3),x3=27,y3=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	}
}

void check_lv()
{

	switch(score/1000)
	{
	case 0 :lv=1,speed=10;break;
	case 1 :if(lv==1) screen_2("恭喜升到2级！",2);lv=2,speed=9;break;
	case 2 :if(lv==2) screen_2("恭喜升到3级！",2);lv=3,speed=8;break;
	case 3 :if(lv==3) screen_2("恭喜升到4级！",2);lv=4,speed=7;break;
	case 4 :if(lv==4) screen_2("恭喜升到5级！",2);lv=5,speed=6;break;
	case 5 :if(lv==5) screen_2("恭喜升到6级！",2);lv=6,speed=5;break;
	case 6 :if(lv==6) screen_2("恭喜升到7级！",2);lv=7,speed=4;break;
	case 7 :if(lv==7) screen_2("恭喜升到8级！",2);lv=8,speed=3;break;
	case 8 :if(lv==8) screen_2("恭喜升到9级！",2);lv=9,speed=2;break;
	case 9 :if(lv==9) screen_2("恭喜升到10级！,满级啦",2);lv=10,speed=1;break;
	}

}

void get_map()
{
	int map1[28][28]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},{2,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,2},{2,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,2},{2,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,2},{2,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,2},{2,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,2},{2,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,2},{2,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,2},{2,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,2},{2,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,2},{2,0,4,4,4,0,0,0,0,4,4,4,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,2},{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},{1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,2},{2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2},{3,3,3,3,3,3,0,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,3,3,3,3,3,2},{1,1,0,0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,0,1,1},{3,3,3,3,3,3,0,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,3,3,3,3,3,3},{2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    int map2[28][28]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,3,0,0,0,0,0,0,0,0,0},{1,1,1,2,2,2,2,2,2,0,0,0,3,0,0,0,3,3,0,0,0,1,2,2,2,1,2,1},{0,0,4,4,4,4,4,0,0,0,3,0,0,0,3,3,0,0,3,0,1,1,1,1,1,0,0,0},{0,0,0,4,4,4,0,0,0,3,3,3,0,3,0,0,3,3,3,0,0,1,1,1,0,0,0,0},{0,0,0,4,4,4,0,0,3,3,3,3,3,0,3,3,3,3,0,0,0,1,1,1,0,0,0,0},{0,0,0,4,4,4,0,3,3,3,3,3,3,3,3,3,3,0,0,0,0,1,1,1,0,0,0,0},{0,0,0,4,4,4,0,3,3,3,3,3,3,3,3,0,0,0,0,0,0,1,1,1,0,0,0,0},{0,0,0,4,4,4,0,3,3,3,3,3,3,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},{0,0,0,4,4,4,0,3,3,3,3,3,3,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},{0,0,0,4,4,4,0,3,3,3,3,3,3,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},{0,0,0,4,4,4,0,0,3,3,3,3,3,3,0,0,0,0,0,0,0,1,1,1,0,0,0,0},{0,0,0,4,4,4,0,0,0,3,3,3,3,3,3,0,0,0,0,0,0,1,1,1,0,0,0,0},{0,0,0,4,4,4,0,0,0,0,0,3,3,3,3,3,0,0,0,0,0,1,1,1,0,0,0,0},{0,0,0,4,4,4,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,1,1,1,0,0,0,0},{2,2,2,2,4,4,4,0,0,0,0,0,0,0,0,3,3,0,0,0,0,1,1,1,2,2,2,2},{1,1,1,0,0,4,4,4,0,3,3,3,3,0,0,0,3,0,0,0,1,1,1,0,0,0,2,2},{4,4,1,0,0,0,4,4,4,0,0,3,3,3,3,0,3,0,0,1,1,1,2,2,2,0,4,4},{4,4,1,1,0,0,0,4,4,4,0,0,0,3,3,3,3,0,1,1,1,0,3,3,3,0,4,4},{1,1,1,1,1,0,0,0,4,4,4,0,0,0,0,0,0,1,1,1,0,0,0,2,2,2,2,2},{1,1,1,1,1,2,2,2,2,4,4,4,0,0,0,0,1,1,1,2,2,2,2,2,2,2,2,2},{1,1,1,1,1,1,1,2,2,2,4,4,4,4,0,1,1,1,2,2,2,2,2,2,2,2,2,2},{1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	int map3[28][28]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,2,2,2,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,0,0,0},{1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},{1,1,1,1,2,2,2,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{0,0,0,1,1,1,1,1,1,1,1,4,4,4,4,4,4,4,4,1,1,1,1,1,1,1,1,1},{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	int map4[28][28]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},{0,2,2,2,2,2,0,4,4,4,4,0,1,1,1,1,0,4,4,4,4,0,2,2,2,2,2,0},{0,0,2,2,2,0,4,4,4,4,4,4,0,1,1,0,4,4,4,4,4,4,0,2,2,2,0,0},{0,0,0,2,0,4,4,4,4,4,4,4,4,0,0,4,4,4,4,4,4,4,4,0,2,0,0,0},{0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0},{0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0},{0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0},{1,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,1},{1,1,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,1,1},{1,1,1,0,0,0,0,0,0,4,4,4,4,4,4,4,4,4,4,0,0,0,0,0,0,1,1,1},{1,1,1,4,0,0,0,0,0,0,4,4,4,4,4,4,4,4,0,0,0,0,0,0,1,1,1,1},{1,1,1,3,4,0,0,0,0,0,0,4,4,4,4,4,4,0,0,0,0,0,0,4,1,1,1,1},{1,1,1,1,3,4,0,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,4,3,1,1,1,1},{1,1,1,1,1,3,4,0,0,0,0,0,0,4,4,0,0,0,0,0,0,4,3,1,1,1,1,1},{1,1,1,1,1,1,3,4,0,0,0,0,0,0,0,0,0,0,1,0,4,3,1,1,1,1,1,1},{1,1,1,1,1,1,1,3,4,0,0,0,0,0,1,0,0,0,0,4,3,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,3,4,0,0,0,0,0,0,0,0,4,3,1,1,1,1,1,1,1,1},{3,3,3,3,3,3,3,3,4,0,0,0,0,0,0,0,0,0,0,4,3,3,3,3,3,3,3,3},{4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,4,4},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	int map5[28][28]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},{2,2,1,4,4,4,4,4,4,2,2,2,2,4,4,2,2,2,2,2,2,4,4,2,2,2,2,2},{3,3,4,4,4,4,4,4,4,3,3,3,3,3,4,4,3,3,3,3,4,4,3,3,3,3,3,3},{1,1,4,4,4,1,1,1,1,1,1,3,3,1,1,4,4,1,1,4,4,1,1,1,1,1,1,1},{1,1,4,4,1,1,1,1,1,1,1,3,3,1,1,1,4,4,4,4,1,1,1,1,1,1,1,1},{1,1,4,4,4,1,1,1,1,1,1,3,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,1},{1,1,4,4,4,4,4,4,1,1,1,3,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,1},{1,1,1,4,4,4,4,4,4,1,1,3,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,4,4,4,1,1,3,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,4,4,1,1,3,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,4,4,4,1,1,3,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,1},{1,1,4,4,4,4,4,4,4,1,1,3,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,1},{1,1,4,4,4,4,4,4,1,1,1,3,3,1,1,1,1,4,4,1,1,1,1,1,1,1,1,1},{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},{1,1,1,1,1,1,1,1,1,1,2,3,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,2,3,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,2,3,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,2,3,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	int map6[28][28]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,4,0,0,0,4,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0},{1,1,1,1,4,0,0,0,4,1,1,0,0,0,1,1,1,1,1,4,4,4,4,4,4,0,0,0},{1,1,0,1,4,0,0,0,4,1,1,0,0,0,1,1,1,1,1,4,0,0,0,0,0,0,0,0},{1,1,0,1,4,0,0,0,4,1,1,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0},{1,1,0,1,4,0,0,4,1,1,1,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0},{1,1,0,1,4,0,0,0,4,1,1,0,0,0,0,0,0,0,0,4,0,0,0,3,4,0,0,0},{1,1,0,1,4,0,0,0,4,4,4,4,4,4,4,4,0,0,0,4,0,0,0,3,4,0,0,0},{1,1,0,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,3,4,0,0,0},{1,1,0,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,3,4,0,0,0},{1,1,0,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,3,4,0,0,0},{4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,4,4,4,4,0,0,0,3,4,0,0,0},{1,1,0,1,1,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,4,0,0,0},{1,1,0,1,1,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,4,0,0,0},{1,1,0,1,1,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,4,0,0,0},{1,1,0,1,1,1,4,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,3,4,0,0,0},{1,1,0,1,1,1,4,0,0,0,1,2,1,3,3,3,3,3,3,3,3,3,3,3,4,0,0,0},{1,1,0,4,4,4,4,0,0,0,1,2,1,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0},{0,0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,1,1,1,1,1,1,1,1,2,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{0,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};


	switch(level)//判断是第几关，然后载入相应地图
	{
	case 1 :
		{
			for(int i=0;i<28;i++)
				for(int j=0;j<28;j++)
					thing[i][j]=map1[i][j];
		}break;
	case 2 :
		{
			for(int i=0;i<28;i++)
				for(int j=0;j<28;j++)
					thing[i][j]=map2[i][j];
		}break;
	case 3 :
		{
			for(int i=0;i<28;i++)
				for(int j=0;j<28;j++)
					thing[i][j]=map3[i][j];
		}break;
	case 4 :
		{
			for(int i=0;i<28;i++)
				for(int j=0;j<28;j++)
					thing[i][j]=map4[i][j];
		}break;
	case 5 :
		{
			for(int i=0;i<28;i++)
				for(int j=0;j<28;j++)
					thing[i][j]=map5[i][j];
		}break;
	case 6 :
		{
			for(int i=0;i<28;i++)
				for(int j=0;j<28;j++)
					thing[i][j]=map6[i][j];
		}break;
	default :
		{
			for(int i=4;i<24;i++)
				for(int j=0;j<28;j++)
					thing[i][j]=rand()%5;
		}
	}
}

void stop()
{
	int a=0;
	char *poem[50]={"      壮哉神将陆伯言","      丈八二桃把营连","      一兵队友张文远","      二兵袁术只等闲","      己方残血放万箭","      敌人弱势开桃园","      转眼队友全托管","      挂上闪电继续连","      铁索全场遭天谴","      一道闪电划过天","      苦心经营几十年","      一夜回到解放前","      队友绝望人心散","      濒死求桃无人怜","      凡人闻之结叹惋","      只见神将笑不言","      我有牌堆很简单","      神技自救不要钱","      连完桃来再连酒","      救完自己救队友","      年轻任性谁能管","      笑看三核被炸残","      只是敌人太狡诈","      各种刷牌各种卡","      凡人皆畏二术禅","      国太香香没得玩","      手牌装备全都有","      体力瞬间就回满","      队友全问怎么办","      怀疑陆神要崩盘","      神将表示莫惊慌","      掏出神器从裤裆","      要问神器是什么","      连弩44杀清全场","      凡人表示瞎狗眼","      不识神将在眼前","      从此美名天下传","      众神闻之皆跪舔","      遍寻三国名将传","      谁人不识陆伯言"," "," "," "," ","     你居然看完。。。     ","  ","  ","  ","  ","  "};
	char key;
	screen_2("游戏暂停",4);
	while(1)
	{
		for(int i=0;i<50;i++)
		{
			Sleep(2000);
			if (kbhit()) //检测
			{
				key = getch();//捕获按键
				if(key==32)
				{
					screen_2("准备开始",2);
					a=1;
					break;
				}
			}
			screen_2(poem[i],2);
			if(a)
				break;
		}
		if(a)
			break;

	}

}


void help()
{
	char key1,key2;
	int a=1;
	for(int i=15;i<29;i++)//先清屏
	{
		gotoxy(62,i);
		printf("                          ");
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	gotoxy(62,15);
	printf("           帮助           ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,17);
	printf("↑ ↓ ← →   控制方向");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,19);
	printf(" 小写 w       切换武器");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,21);
	printf(" 小写 s       切换皮肤");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,23);
	printf(" 小写 h       帮助/退出");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,25);
	printf("  空格        暂停/开始");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN);
	gotoxy(62,27);
	printf("按0查看更多");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	gotoxy(62,28);
	printf("                 版本:1.0");

	while(1)
	{
		if (kbhit()) //检测，如果有按键就执行if里面的
		{
			key1 = getch();//捕获按键
			if( 104 == key1 )
			{
				screen_2("看完帮助 继续游戏吧",2);
				screen_3();
				break;
			}

			else if( 48 == key1 )
			{
				while(1)
				{
				for(int i=17;i<29;i++)//先清屏
				{
					gotoxy(62,i);
					printf("                          ");
				}

				switch(a)
				{
				case 1 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
						gotoxy(62,17);
						printf("■  绿色方块可承受一次打击");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
						gotoxy(62,19);
						printf("■  黄色油块可承受两次打击");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
						gotoxy(62,21);
						printf("■  白色冰块可承受三次打击");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
						gotoxy(62,23);
						printf("■  蓝色石块无法被破环");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN);
						gotoxy(62,27);
						printf("按空格键继续");

					}break;

				case 2 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
						gotoxy(62,17);
						printf("⊕  普通子弹攻击力为1     ");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
						gotoxy(62,19);
						printf("∷  散弹可对绿色方块造成大");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
						gotoxy(62,21);
						printf("范围破坏，但是无法对其它类");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
						gotoxy(62,23);
						printf("型的方块造成破坏          ");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
						gotoxy(62,25);
						printf("◎  气泡弹可以对一排的绿色");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
						gotoxy(62,27);
						printf("方块造成破坏");

					}break;

				case 3 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,17);
						printf("※  雪花弹对白色冰块无效，");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,19);
						printf("但是可以将老家的围墙修成白");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,21);
						printf("色冰块，从而保护老家");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
						gotoxy(62,23);
						printf("●  超级炮弹可以对除蓝色石");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
						gotoxy(62,25);
						printf("块外所有方块造成一次性的巨");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
						gotoxy(62,27);
						printf("大破坏");

					}break;

				case 4 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,17);
						printf("每打掉一辆坦克加100 分，同");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,19);
						printf("时有一定几率掉落星星，收集");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,21);
						printf("星星可解锁武器和皮肤。每当");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,23);
						printf("分数达到整千时，你将升级，");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,25);
						printf("升级后，子弹速度将会变快，");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,27);
						printf("同时敌人也将变强");

					}break;

				case 5 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,17);
						printf("游戏内置六张地图，第六关往");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,19);
						printf("后将会出现系统的随机地图");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,21);
						printf("友情提示：你自己的子弹都");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,23);
						printf("无法对老家的围墙造成破坏");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,25);
						printf("，但是可以对内部造成破坏");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,27);
						printf("，因此别总把枪口对着老家");

					}break;

				case 6 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN);
						gotoxy(62,27);
						printf("按空格键退出");

					}break;

				}


				while(1)
				{
					if (32==getch()) a++;break;
				}
				if(a==7)break;
			}

		}
		}
		if(a==7)
			{
				screen_2("看完帮助 继续游戏吧",2);
				screen_3();
				break;
			}			
	}

}

void check_game()
{
	if(life==0)
		gameover();
	if(enemy==0)
		next_level();
}

void next_level()
{
	screen_1();
	level++;
	for(int i=15;i<29;i++)//先清屏
	{
		gotoxy(62,i);
		printf("                          ");
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	gotoxy(62,17);
	printf("          恭喜过关        ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,23);
	printf("    按 空格键 继续游戏    ");

	while(1)
	{
		if(32 == getch())
		{

			int home0[3][4]={{2,2,2,2},{2,1,1,2},{2,1,1,2}};//定义一个老家的初始化值

			{
				for(int i=0;i<5;i++)
					info[i]=" ";//通知清零
			}
			{
				for(int i=0;i<3;i++)//老家初始化
					for(int j=0;j<4;j++)
						home[i][j]=home0[i][j];
			}	

			m=0  , n=0 ;//我的坦克子弹的坐标清零
			m1=0 , n1=0;//坦克1号子弹的坐标清零
			m2=0 , n2=0;//坦克2号子弹的坐标清零
			m3=0 , n3=0;//坦克3号子弹的坐标清零

			{
			for(int i=1;i<29;i++)
				for(int j=1;j<29;j++)
				{
					gotoxy(2*i,j);
					printf("  ");
				}
			}


			life=3;//生命初始化
			enemy=13;//敌人数量初始化
			s=0,t=0;//星星坐标
			get_map();//获得地图
			refresh_map();//刷新地图
			print_home();//打印老家
			print_thing();//打印物品

			direction=0;//我的坦克子弹射向初始化
			direction_1=0;//坦克1号子弹射向初始化
			direction_2=0;//坦克2号子弹射向初始化
			direction_3=0;//坦克3号子弹射向初始化

			x=10;y=27;//我的坦克位置初始化
			state=0;
			turn_up(my_tank);//我的坦克方向初始化


			x1=2;y1=2;//坦克1号位置初始化
			state_1=0;
			turn_down_1(tank_1);//坦克1号方向初始化

			x2=14;y2=2;//坦克2号位置初始化
			state_2=0;
			turn_down_2(tank_2);//坦克2号方向初始化

			x3=27;y3=2;//坦克3号位置初始化
			state_3=0;
			turn_down_3(tank_3);//坦克3号方向初始化

			screen_1();
			screen_2("游戏开始",4);
			break;
		}
	}



}


void gameover()
{

	for(int i=15;i<29;i++)//先清屏
	{
		gotoxy(62,i);
		printf("                          ");
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
	gotoxy(62,17);
	printf("          游戏结束        ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,23);
	printf("    按 空格键 重新开始    ");

	while(1)
	{
		if(32 == getch())
		{
			initial();
			break;
		}
	}
}

void initial()
{
			int home0[3][4]={{2,2,2,2},{2,1,1,2},{2,1,1,2}};//定义一个老家的初始化值
			life=3;//生命初始化
			enemy=13;//敌人数量初始化
			level=1;//关卡初始化
			weapons=1;//武器初始化
			skin=1;//皮肤初始化
			star=1;//星星初始化
			s=0,t=0;//星星坐标
			score=0;//分数初始化
			lv=1;//等级初始化
			speed=10;//速度初始化
			{
				for(int i=0;i<5;i++)
					info[i]=" ";//通知清零
			}
			{
				for(int i=0;i<3;i++)//老家初始化
					for(int j=0;j<4;j++)
						home[i][j]=home0[i][j];
			}	

			m=0  , n=0 ;//我的坦克子弹的坐标清零
			m1=0 , n1=0;//坦克1号子弹的坐标清零
			m2=0 , n2=0;//坦克2号子弹的坐标清零
			m3=0 , n3=0;//坦克3号子弹的坐标清零

			{
			for(int i=1;i<29;i++)
				for(int j=1;j<29;j++)
				{
					gotoxy(2*i,j);
					printf("  ");
				}
			}

			get_map();//获得地图
			refresh_map();//刷新地图
			print_home();//打印老家
			print_thing();//打印物品

			direction=0;//我的坦克子弹射向初始化
			direction_1=0;//坦克1号子弹射向初始化
			direction_2=0;//坦克2号子弹射向初始化
			direction_3=0;//坦克3号子弹射向初始化

			x=10;y=27;//我的坦克位置初始化
			state=0;
			turn_up(my_tank);//我的坦克方向初始化

			x1=2;y1=2;//坦克1号位置初始化
			state_1=0;
			turn_down_1(tank_1);//坦克1号方向初始化

			x2=14;y2=2;//坦克2号位置初始化
			state_2=0;
			turn_down_2(tank_2);//坦克2号方向初始化

			x3=27;y3=2;//坦克3号位置初始化
			state_3=0;
			turn_down_3(tank_3);//坦克3号方向初始化

			screen_1();
			screen_2("游戏开始",4);
			screen_3();
}