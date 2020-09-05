#include<stdio.h>
#include <windows.h>
#include<conio.h>
#include<time.h>

void gotoxy(int x,int y);//���ƹ�ꡣX��ʾ�����꣬Y��ʾ������
void my_print();//���ý���
void print_thing();//��ӡ��Ʒ
void print_home();//��ӡ�ϼ�
void refresh_map();//ˢ�µ�ͼ
void stop();//��ͣ

void print_my_tank();//��ӡ�ҵ�̹��
void print_tank_1();//��ӡ̹��1��
void print_tank_2();//��ӡ̹��2��
void print_tank_3();//��ӡ̹��3��

void clear_my_tank();//����ҵ�̹�ˣ�����̹���ƶ���
void clear_tank_1();//���̹��1��
void clear_tank_2();//���̹��2��
void clear_tank_3();//���̹��3��

void turn_up(int a[][3]);//�ҵ�̹����ת
void turn_down(int a[][3]);//�ҵ�̹����ת
void turn_left(int a[][3]);//�ҵ�̹����ת
void turn_right(int a[][3]);//�ҵ�̹����ת

void turn_up_1(int a[][3]);//̹��1����ת
void turn_down_1(int a[][3]);//̹��1����ת
void turn_left_1(int a[][3]);//̹��1����ת
void turn_right_1(int a[][3]);//̹��1����ת

void turn_up_2(int a[][3]);//̹��2����ת
void turn_down_2(int a[][3]);//̹��2����ת
void turn_left_2(int a[][3]);//̹��2����ת
void turn_right_2(int a[][3]);//̹��2����ת

void turn_up_3(int a[][3]);//̹��3����ת
void turn_down_3(int a[][3]);//̹��3����ת
void turn_left_3(int a[][3]);//̹��3����ת
void turn_right_3(int a[][3]);//̹��3����ת

void my_move();//�ҵ�̹���ƶ�
void move_1();//̹��1���ƶ�
void move_2();//̹��2���ƶ�
void move_3();//̹��3���ƶ�

void print_bullet(int x,int y);//��ӡ�з�̹�˵��ӵ�
void print_my_bullet(int x,int y);//��ӡ�ҵ��ӵ�
void clear_bullet(int x,int y);//����ӵ�
int  check_bullet(int x,int y);//����ӵ��Ƿ���ײ��û������1����������0
void shoot();//�����ҵ�̹���ӵ�������
void shoot_1();//����̹��1���ӵ�������
void shoot_2();//����̹��2���ӵ�������
void shoot_3();//����̹��3���ӵ�������

void change_thing();//��¼��Ʒ�ı仯
void change_home();//��¼�ϼҵı仯
void change_bullet();//��¼�ӵ��ı仯
void change_star();//��¼���ǵı仯
void change_tank();//��¼�ҵ�̹�˵ı仯
void change_tank_1();//��¼̹��1�ŵı仯
void change_tank_2();//��¼̹��2�ŵı仯
void change_tank_3();//��¼̹��3�ŵı仯

void switch_weapons();//�л�����
void switch_skin();//�л�Ƥ��
void help();//����
void check_game();//�����Ϸʤ��
void check_lv();//���ȼ�
void next_level();//��һ��
void get_map();//���ÿһ�صĵ�ͼ
void initial();//����������ʼ��
void gameover();//��Ϸ����

void console();//���ƴ���
void screen_1();//��Ļ1
void screen_2(char *p,int color);//��Ļ2
void screen_3();//��Ļ3
void produce_star();//����һ������
void print_star();//��ӡ����
void check_star();//������ǵ�����
void clear_star();//�������

int my_abs(int x);//����ֵ��������ϵͳ�Ļ�������
int judge(int x,int y,int state);//�ж��ҵ�̹���ܷ�ǰ��
int judge2(int x,int y,int state);// ���������ж��ܷ�ǰ��

int check1(int x,int y);//���������жϵĺ���
int check2(int x,int y);//���������жϵĺ���
int check3(int x,int y);//���������жϵĺ���


int life=3;//����
int enemy=13;//��������
int level=1;//�ؿ�
int weapons=1;//����
int skin=1;//Ƥ��
int star=1;//����
int s=0,t=0;//��������
int score=0;//����
int lv=1;//�ȼ�
int speed=10;//�ٶ�
char *info[5]={" "," "," "," "," "};//֪ͨ

int map[30][30]={0};//��¼������Ļ�ϵ�����
int thing[28][28]={0};//�ϰ���������߽�
int home[3][4]={{2,2,2,2},{2,1,1,2},{2,1,1,2}};//�ϼ�,3��4��

int my_tank[3][3]={0};//�ҵ�̹��
int tank_1[3][3]={0};//���˵�̹��1��
int tank_2[3][3]={0};//���˵�̹��2��
int tank_3[3][3]={0};//���˵�̹��3��

int x  , y ;//�ҵ�̹����������
int x1 , y1;//̹��1����������
int x2 , y2;//̹��2����������
int x3 , y3;//̹��3����������

int m=0  , n=0 ;//�ҵ�̹���ӵ�������
int m1=0 , n1=0;//̹��1���ӵ�������
int m2=0 , n2=0;//̹��2���ӵ�������
int m3=0 , n3=0;//̹��3���ӵ�������

int state=0; //�ҵ�̹�˷���(1�ϣ�2�£�3��4��)
int state_1=0;//̹��1�ŷ���
int state_2=0;//̹��2�ŷ���
int state_3=0;//̹��3�ŷ���

int direction=0;//�ҵ�̹���ӵ�����
int direction_1=0;//̹��1���ӵ�����
int direction_2=0;//̹��2���ӵ�����
int direction_3=0;//̹��3���ӵ�����

int cp1=2;//���������жϵı���
int cp2=2;//���������жϵı���
int cp3=2;//���������жϵı���

void main()//������
{
	srand(time(NULL));//�������������
	console();//���ô���
	my_print();//��ӡ�߿�
	initial();//��������ʼ��
	while(1)
	{
		int i1,i2,i3,i4,i5,i6,i7;
		my_move();//�����ҵ�̹���ƶ�
		if(i1++%30==0) //���Ƶ���̹���ٶ�
			move_1();
 		if(i2++%30==0) 
			move_2();
		if(i3++%30==0) 
			move_3();
		if(i4++%speed==0)   //�����ӵ��ٶ�
			shoot();
		if(i5++%speed==0)
			shoot_1();
		if(i6++%speed==0)
			shoot_2();
		if(i7++%speed==0)
			shoot_3();
		screen_1();//ˢ����Ļ
		Sleep(30);
	}
}

//���ù�������λ�ú���
void gotoxy(int x,int y)//X��ʾ�����꣬Y��ʾ�����ꡣ
{
	HANDLE app;
	COORD  pos;
	pos.X=x;
	pos.Y=y;
	app=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(app,pos);
}

//���ƴ���
void console()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);	
	CONSOLE_SCREEN_BUFFER_INFO bInfo; 
	GetConsoleScreenBufferInfo(hOut, &bInfo );	
	SetConsoleTitle("̹�˴�ս"); // ���ô��ڵı���
	COORD size = {90, 32};//���ô��ڴ�С
	SetConsoleScreenBufferSize(hOut,size); 	
	SMALL_RECT rc = {0,0, 63, 31};
	SetConsoleWindowInfo(hOut,true ,&rc);
}

//��ӡ�߽�
void my_print()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE |FOREGROUND_INTENSITY);//��ɫ
	printf("������������������������������������������������������������ |�i�i�i�i�i�i�i�i�i�i�i�i�i|\n");
	for(int i=0;i<13;i++)
	printf("��                                                        �� |                          |\n");
	printf("��                                                        �� |--------------------------|\n");
	for(int j=14;j<28;j++)
	printf("��                                                        �� |                          |\n");
	printf("������������������������������������������������������������ |�l�l�l�l�l�l�l�l�l�l�l�l�l|\n");
}


//��ӡ�����̹��
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
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);//����ɫ
						gotoxy(2*x+2*j-2,y+i-1);
						printf("��");
					}break;
				case 2 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);//��ɫ
						gotoxy(2*x+2*j-2,y+i-1);
						printf("��");
					}break;
				case 3 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);//��ɫ
						gotoxy(2*x+2*j-2,y+i-1);
						printf("��");
					}break;
				case 4 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);//��ɫ
						gotoxy(2*x+2*j-2,y+i-1);
						printf("��");
					}break;
				case 5 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);//��ɫ
						gotoxy(2*x+2*j-2,y+i-1);
						printf("��");
					}break;
				case 6 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);//��ɫ
						gotoxy(2*x+2*j-2,y+i-1);
						printf("��");
					}break;
				case 7 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);//��ɫ
						gotoxy(2*x+2*j-2,y+i-1);
						printf("��");
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);// ��ɫ
				gotoxy(2*x1+2*j-2,y1+i-1);
				printf("��");
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);// ��ɫ
				gotoxy(2*x2+2*j-2,y2+i-1);
				printf("��");
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);// ��ɫ
				gotoxy(2*x3+2*j-2,y3+i-1);
				printf("��");
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

void print_thing()                // ��ӡ��Ʒ
{
	for(int j=0;j<28;j++)         // ������(1,1)�㿪ʼ��ӡ
		for(int i=0;i<28;i++)
			if(thing[i][j]==1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
				gotoxy(2+2*j,1+i);
				printf("��");
			}
			else if(thing[i][j]==2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
				gotoxy(2+2*j,1+i);
				printf("��");
			}
			else if(thing[i][j]==3)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
				gotoxy(2+2*j,1+i);
				printf("��");
			}
			else if(thing[i][j]==4)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
				gotoxy(2+2*j,1+i);
				printf("��");
			}
}

void print_home()                 //��ӡ�ϼ�
{


	for(int i=0;i<3;i++)          //��ӡ�ϼ���ǽ       
		for(int j=0;j<4;j++)
			if(home[i][j]==1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
					gotoxy(26+2*j,26+i);
					printf("��");
				}
			else if(home[i][j]==2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
					gotoxy(26+2*j,26+i);
					printf("��");
				}
			else if(home[i][j]==3)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
					gotoxy(26+2*j,26+i);
					printf("��");
				}


	{
	for(int i=1;i<3;i++)          //��ӡ�ϼ��ڲ�
		for(int j=1;j<3;j++)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
					gotoxy(26+2*j,26+i);
					printf("��");
				}
	}

}


void print_bullet(int x,int y)    //��ӡ�з�̹�˵��ӵ��ӵ�
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	gotoxy(2*x,y);
	printf("��");
}

void print_my_bullet(int x,int y)    //��ӡ�ҵ��ӵ�
{
	switch(weapons)
	{
	case 1 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
			gotoxy(2*x,y);
			printf("��");
		}break;
	case 2 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
			gotoxy(2*x,y);
			printf("��");
		}break;
	case 3 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
			gotoxy(2*x,y);
			printf("��");
		}break;
	case 4 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
			gotoxy(2*x,y);
			printf("��");
		}break;
	case 5 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
			gotoxy(2*x,y);
			printf("��");
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
	printf("          �� %d ��         ",level);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	gotoxy(62,4);
	printf("����: %d",score);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_RED);
	gotoxy(80,4);
	printf("LV: %d ",lv);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	gotoxy(62,6);
	printf("����:     ̹�ˡ�%d         ",life-1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
	gotoxy(62,8);
	printf("�з�:     ̹�ˡ�%d        ",enemy);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	gotoxy(62,11);
	printf("��ǰ����:                 ");
	switch(weapons)
	{
	case 1 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
			gotoxy(62,13);
			printf("         ��ͨ�ӵ� ��      ");
		}break;
	case 2 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
			gotoxy(62,13);
			printf("           ɢ��   ��      ");
		}break;
	case 3 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
			gotoxy(62,13);
			printf("          ���ݵ�  ��      ");
		}break;
	case 4 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
			gotoxy(62,13);
			printf("          ѩ����  ��      ");
		}break;
	case 5 :
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
			gotoxy(62,13);
			printf("         �����ڵ� ��      ");
		}break;
	}


}

void screen_2(char *p,int color)
{

	for(int i=15;i<27;i++)//������
	{
		gotoxy(62,i);
		printf("                          ");
	}

	info[0]=info[1];//��������
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
			 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);//��
			 gotoxy(62,23);
			 printf("%s",info[4]);
		}break;
	case 2 :
		{
			 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);//����
			 gotoxy(62,23);
			 printf("%s",info[4]);
		}break;
	case 3 :
		{
			 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);//��
			 gotoxy(62,23);
			 printf("%s",info[4]);
		}break;
	case 4 :
		{
		     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);//��
			 gotoxy(62,23);
			 printf("%s",info[4]);
		}break;
	}
}

void screen_3()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
	gotoxy(62,27);
	printf("          h������  Esc�˳�");
	gotoxy(62,28);
	printf("                          ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
	if(star<=13)
	for(int i=1;i<=star;i++)
	{
		gotoxy(60+2*i,28);
		printf("��");
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
		printf("��");
}

void change_star()
{
	if(s==x&&t==(y-1) || s==x&&t==(y+1) || s==(x-1)&&t==y || s==(x+1)&&t==y)
	{
		clear_star();
		s=0,t=0;
		star++;
		screen_2("��ϲ����һ������",2);
		printf("\7");
		check_star();
		print_my_tank();
	}
	if(s==x1&&t==(y1-1) || s==x1&&t==(y1+1) || s==(x1-1)&&t==y1 || s==(x1+1)&&t==y1)
	{
		clear_star();
		s=0,t=0;
		screen_2("���ź����Ǳ�������",4);
		printf("\7");
		print_tank_1();
	}
	if(s==x2&&t==(y2-1) || s==x2&&t==(y2+1) || s==(x2-1)&&t==y2 || s==(x2+1)&&t==y2)
	{
		clear_star();
		s=0,t=0;
		screen_2("���ź����Ǳ�������",4);
		printf("\7");
		print_tank_2();
	}

	if(s==x3&&t==(y3-1) || s==x3&&t==(y3+1) || s==(x3-1)&&t==y3 || s==(x3+1)&&t==y3)
	{
		clear_star();
		s=0,t=0;
		screen_2("���ź����Ǳ�������",4);
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
	case 2 :screen_2("������������  ɢ��",4),screen_3();break;
	case 3 :screen_2("�ɹ�����  ��ɫƤ��",2),screen_3();break;
	case 4 :screen_2("������������  ���ݵ�",2),screen_3();break;
	case 5 :screen_2("�ɹ�����  ��ɫƤ��",3),screen_3();break;
	case 6 :screen_2("������������  ѩ����",1),screen_3();break;
	case 7 :screen_2("�ɹ�����  ��ɫƤ��",1),screen_3();break;
	case 8 :screen_2("������������  �����ڵ�",4),screen_3();break;
	case 9 :screen_2("�ɹ�����  ��ɫƤ��",1),screen_3();break;
	case 10 :screen_2("����ӵ��10������",3),screen_3();break;
	case 11 :screen_2("�ɹ�����  ��ɫƤ��",4),screen_3();break;
	case 12 :screen_2("����ӵ��12������",3),screen_3();break;
	case 13 :screen_2("�ɹ����� ��ɫƤ��",1),screen_3();break;
	}

}

void switch_weapons()
{
	weapons++;
	if(weapons>star/2+1)
		weapons=1;
	if(star==1)
		screen_2("��ǰ���������㣬�Ͽ��ռ���",1);
	else
	{
		switch(weapons)
		{
		case 1 :screen_2("�л�����ͨ�ӵ�",1);break;
		case 2 :screen_2("�л���ɢ��",1);break;
		case 3 :screen_2("�л������ݵ�",1);break;
		case 4 :screen_2("�л���ѩ����",1);break;
		case 5 :screen_2("�л��������ڵ���",1);break;
		}
	}

}

void switch_skin()
{
	skin++;
	if(skin>(star-1)/2+1)
		skin=1;
	if(star==1 || star==2)
		screen_2("��ǰ���������㣬�Ͽ��ռ���",1);
	else
	{
		switch(skin)
		{
		case 1 :screen_2("�л�������ɫƤ��",1);break;
		case 2 :screen_2("�л�����ɫƤ��",1);break;
		case 3 :screen_2("�л�����ɫƤ��",1);break;
		case 4 :screen_2("�л�����ɫƤ��",1);break;
		case 5 :screen_2("�л�����ɫƤ��",1);break;
		case 6 :screen_2("�л�����ɫƤ��",1);break;
		case 7 :screen_2("�л�����ɫƤ��",1);break;
		}
	}


}

void shoot()
{

	if(m!=0 || n!=0)
		if(map[n][m]==0)//����ӵ������ڵ�ͼ�ϣ��������		
			clear_bullet(m,n);
	if(m==0 && n==0)//�������ڳ���û���ҵ�̹�˵��ӵ�,�����·����ӵ�
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
	change_thing();//����Ƿ�����ϰ���
	change_home();//����Ƿ�����ϼ�
	change_bullet();//����Ƿ�����ӵ�
	change_tank_1();//����Ƿ����̹��1��
	change_tank_2();//����Ƿ����̹��2��
	change_tank_3();//����Ƿ����̹��3��
	if(check_bullet(m,n))	
		print_my_bullet(m,n);
	else
		m=0,n=0;
}

void shoot_1()
{

	if(m1!=0 || n1!=0)
		if(map[n1][m1]==0)//����ӵ������ڵ�ͼ�ϣ��������		
			clear_bullet(m1,n1);
	if(m1==0 && n1==0)//�������ڳ���û��̹��1�ŵ��ӵ�,�����·����ӵ�
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
	change_thing();//����Ƿ�����ϰ���
	change_home();//����Ƿ�����ϼ�
	change_bullet();//����Ƿ�����ӵ�
	change_tank();//����Ƿ�����ҵ�̹��
	if(check_bullet(m1,n1))	
		print_bullet(m1,n1);
	else
		m1=0,n1=0;
}

void shoot_2()
{

	if(m2!=0 || n2!=0)
		if(map[n2][m2]==0)//����ӵ������ڵ�ͼ�ϣ��������		
			clear_bullet(m2,n2);
	if(m2==0 && n2==0)//�������ڳ���û��̹��2�ŵ��ӵ�,�����·����ӵ�
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
	change_thing();//����Ƿ�����ϰ���
	change_home();//����Ƿ�����ϼ�
	change_bullet();//����Ƿ�����ӵ�
	change_tank();//����Ƿ�����ҵ�̹��
	if(check_bullet(m2,n2))	
		print_bullet(m2,n2);
	else
		m2=0,n2=0;
}


void shoot_3()
{

	if(m3!=0 || n3!=0)
		if(map[n3][m3]==0)//����ӵ������ڵ�ͼ�ϣ��������		
			clear_bullet(m3,n3);
	if(m3==0 && n3==0)//�������ڳ���û��̹��3�ŵ��ӵ�,�����·����ӵ�
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
	change_thing();//����Ƿ�����ϰ���
	change_home();//����Ƿ�����ϼ�
	change_bullet();//����Ƿ�����ӵ�
	change_tank();//����Ƿ�����ҵ�̹��
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

int judge(int x,int y,int state)//x,y̹�˵�ǰ����,state̹�˵�ǰ����
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

int judge2(int x,int y,int state)//x,y̹�˵�ǰ����,state̹�˵�ǰ����
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

void refresh_map()               //i�����У��������ꣻj�����У���������
{
	{
		for(int i=0;i<30;i++)          //���ȵ�ͼ����
			for(int j=0;j<30;j++)
				map[i][j]=0;
	}

	{
		for(int i=0;i<30;i++)    //��ͼ��һ���֣�Χǽ����ȫ������
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
		for(int i=0;i<3;i++)   //��ͼ�ڶ����֣��ϼң�����������
			for(int j=0;j<4;j++)
				map[i+26][j+13]=home[i][j];
	}

	{
		for(int i=0;i<28;i++)  //��ͼ�������֣��ϰ����ʱ�ı䣩
			for(int j=0;j<28;j++)
				map[i+1][j+1]=thing[i][j];
	}

	{
		switch(state)          //��ͼ���Ĳ��֣�̹�ˣ����Ǹı䣩
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
	if (kbhit()) //��⣬����а�����ִ��if�����
	{
		key = getch();//���񰴼�
		switch( key ) 
		{
		case 72:turn_up(my_tank);//��
			break;
		case 75:turn_left(my_tank);//��
			break;
		case 77:turn_right(my_tank);//��
			break;
		case 80:turn_down(my_tank);//��
			break;
		case 32:stop();//�ո� ��ͣ��ʼ
			break;
		case 104:help();//Сh�л��������˵�
			break;
		case 115:switch_skin(),print_my_tank();//Сs���л�Ƥ��
			break;
		case 119:switch_weapons();//Сw���л�����
			break;

		case 27:exit(0);//Esc �˳�
		default: ;
		}
	}
}

int check1(int x,int y)//�������棬�������
{
	for(int j=y;j<27;j++)
		if(map[j][x]==4)
			return 0;
	return 1;
}

int check2(int x,int y)//�������棬�������
{
	for(int i=x;i<14;i++)
		if(map[y][i]==4)
			return 0;
	return 1;
}

int check3(int x,int y)//�������棬�������
{
	for(int i=x;i>15;i--)
		if(map[y][i]==4)
			return 0;
	return 1;
}

void move_1()
{
	if((x1==14 || x1==15) && check1(x1,y1))//��������
	{
			if(state_1!=2)
				turn_down_1(tank_1);
	}
	else if(x1<14 && y1==27 && check2(x1,y1))//��������
	{
			if(state_1!=4)
				turn_right_1(tank_1);
	}
	else if(x1>15 && y1==27 && check3(x1,y1))//��������
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
	if((x2==14 || x2==15) && check1(x2,y2))//��������
	{
			if(state_2!=2)
				turn_down_2(tank_2);
	}
	else if(x2<14 && y2==27 && check2(x2,y2))//��������
	{
			if(state_2!=4)
				turn_right_2(tank_2);
	}
	else if(x2>15 && y2==27 && check3(x2,y2))//��������
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
	if((x3==14 || x3==15) && check1(x3,y3))//��������
	{
			if(state_3!=2)
				turn_down_3(tank_3);
	}
	else if(x3<14 && y3==27 && check2(x3,y3))//��������
	{
			if(state_3!=4)
				turn_right_3(tank_3);
	}
	else if(x3>15 && y3==27 && check3(x3,y3))//��������
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

void change_thing()//��Ʒ���ӵ����л�ı�
{
	if(m>0&&m<29 && n>0&&n<29)//���ҵ��ӵ�����
		if(thing[n-1][m-1]==1)//���е�һ�ַ���
		{
			if(weapons==2)
			{
				if(thing[n][m-1]==1)
					thing[n][m-1]=0;
					gotoxy(2*m,n+1);
					printf("  ");//��ȥ����
				if(thing[n-2][m-1]==1)
					thing[n-2][m-1]=0;
					gotoxy(2*m,n-1);
					printf("  ");//��ȥ����
				if(thing[n-1][m]==1)
					thing[n-1][m]=0;
					gotoxy(2*(m+1),n);
					printf("  ");//��ȥ����
				if(thing[n-1][m-2]==1)
					thing[n-1][m-2]=0;
					gotoxy(2*(m-1),n);
					printf("  ");//��ȥ����
				thing[n-1][m-1]=0;
				gotoxy(2*m,n);
				printf("  ");//��ȥ����
				m=0,n=0;//�ӵ���ʧ
				print_thing();
				refresh_map();
			}
			else if(weapons==3)
			{
				thing[n-1][m-1]=0;
				gotoxy(2*m,n);
				printf("  ");//��ȥ����
				print_my_bullet(m,n);
				print_thing();
				refresh_map();
			}
			else
			{
				thing[n-1][m-1]=0;
				gotoxy(2*m,n);
				printf("  ");//��ȥ����
				m=0,n=0;//�ӵ���ʧ
				print_thing();
				refresh_map();
			}



		}

		else if(thing[n-1][m-1]==2)//�򵽵ڶ��ַ���
		{
			if(weapons==5)
			{
				thing[n-1][m-1]=0;
				gotoxy(2*m,n);
				printf("  ");
				m=0,n=0;//�ӵ���ʧ
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
				m=0,n=0;//�ӵ���ʧ
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
				m=0,n=0;//�ӵ���ʧ
				print_thing();
				refresh_map();
			}
			else
			{
				thing[n-1][m-1]=2;
				m=0,n=0;//�ӵ���ʧ
				print_thing();
				refresh_map();
			}
		}

		else if(thing[n-1][m-1]==4)//�˷��鲻���ӵ�Ӱ��
		{
			m=0,n=0;//�ӵ���ʧ
		}

	if(m1>0&&m1<29 && n1>0&&n1<29)//��̹��1���ӵ�����
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
			m1=0,n1=0;//�ӵ���ʧ
			print_thing();
			refresh_map();
		}
		else if(thing[n1-1][m1-1]==3)
		{
			thing[n1-1][m1-1]=2;
			m1=0,n1=0;//�ӵ���ʧ
			print_thing();
			refresh_map();
		}
		else if(thing[n-1][m-1]==4)//�˷��鲻���ӵ�Ӱ��
		{
			m1=0,n1=0;//�ӵ���ʧ
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
			m2=0,n2=0;//�ӵ���ʧ
			print_thing();
			refresh_map();
		}
		else if(thing[n2-1][m2-1]==3)
		{
			thing[n2-1][m2-1]=2;
			m2=0,n2=0;//�ӵ���ʧ
			print_thing();
			refresh_map();
		}
		else if(thing[n2-1][m2-1]==4)//�˷��鲻���ӵ�Ӱ��
		{
			m2=0,n2=0;//�ӵ���ʧ
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
			m3=0,n3=0;//�ӵ���ʧ
			print_thing();
			refresh_map();
		}
		else if(thing[n3-1][m3-1]==3)
		{
			thing[n3-1][m3-1]=2;
			m3=0,n3=0;//�ӵ���ʧ
			print_thing();
			refresh_map();
		}
		else if(thing[n3-1][m3-1]==4)//�˷��鲻���ӵ�Ӱ��
		{
			m3=0,n3=0;//�ӵ���ʧ
		}



}

void change_home()
{
	if(m==14&&n==27 || m==15&&n==27 || m==14&&n==28 || m==15&&n==28)//����ӵ����ϼ����Ϸ����
		 gameover();
	else if(m>12 && n>25 && m<17 && n<29)
		if(weapons==4)//ֻ��4���ӵ����ϼҵ�ǽ��Ч
		{
			home[n-26][m-13]=3;
			screen_2("���޸����ϼ�Ŷ��",1);
			m=0,n=0;   //�ӵ���ʧ
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
				screen_2("����! ����!",4);
				gotoxy(2*m1,n1);
				printf("  ");
				m1=0,n1=0;
				print_home();
				refresh_map();
			}
			else if(home[n1-26][m1-13]==2)        
			{
				home[n1-26][m1-13]=1;
				screen_2("������в��������ϼ�",4);
				m1=0,n1=0;   //�ӵ���ʧ
				print_home();
				refresh_map();
			}
			else if(home[n1-26][m1-13]==3)         
			{
				home[n1-26][m1-13]=2;
				screen_2("���˶���ķ�����ʼ�˴��",4);
				m1=0,n1=0;   //�ӵ���ʧ
				print_home();
				refresh_map();
			}

	if(m2==14&&n2==27 || m2==15&&n2==27 || m2==14&&n2==28 || m2==15&&n2==28)
		 gameover();
	else if(m2>12 && n2>25 && m2<17 && n2<29)
		if(home[n2-26][m2-13]==1)         
		{
			home[n2-26][m2-13]=0;
			screen_2("����! ����!",4);
			gotoxy(2*m2,n2);
			printf("  ");
			m2=0,n2=0;
			print_home();
			refresh_map();
		}
		else if(home[n2-26][m2-13]==2)        
		{
			home[n2-26][m2-13]=1;
			screen_2("������в��������ϼ�",4);
			m2=0,n2=0;   //�ӵ���ʧ
			print_home();
			refresh_map();
		}
		else if(home[n2-26][m2-13]==3)         
		{
			home[n2-26][m2-13]=2;
			screen_2("���˶���ķ�����ʼ�˴��",4);
			m2=0,n2=0;   //�ӵ���ʧ
			print_home();
			refresh_map();
		}

	if(m3==14&&n3==27 || m3==15&&n3==27 || m3==14&&n3==28 || m3==15&&n3==28)
		 gameover();
	else if(m3>12 && n3>25 && m3<17 && n3<29)
		if(home[n3-26][m3-13]==1)        
		{
			home[n3-26][m3-13]=0;
			screen_2("����! ����!",4);
			gotoxy(2*m3,n3);
			printf("  ");
			m3=0,n3=0;
			print_home();
			refresh_map();
		}
		else if(home[n3-26][m3-13]==2)        
		{
			home[n3-26][m3-13]=1;
			screen_2("������в��������ϼ�",4);
			m3=0,n3=0;   //�ӵ���ʧ
			print_home();
			refresh_map();
		}
		else if(home[n3-26][m3-13]==3)         
		{
			home[n3-26][m3-13]=2;
			screen_2("���˶���ķ�����ʼ�˴��",4);
			m3=0,n3=0;   //�ӵ���ʧ
			print_home();
			refresh_map();
		}


}

void change_bullet()//���ҵ�̹���ӵ��͵���̹���ӵ���ײ
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
	case 1 :                           //���ҵ�̹�˷�������ʱ
		{
			if(x==m1&&(y-1)==n1 || (x-1)==m1&&y==n1 || x==m1&&y==n1 || (x+1)==m1&&y==n1 || (x-1)==m1&&(y+1)==n1 || (x+1)==m1&&(y+1)==n1)//���̹��1���ӵ����ҵ�̹��
				clear_my_tank(),screen_2("̹��1�Ż�������  ����ֵ��1",4),x=10,y=27,m1=0,n1=0,life--,check_game(),turn_up(my_tank);//�ҵ�̹�˻ص���ʼλ�ã�̹��1���ӵ���ʧ������ֵ��1�������Ϸ�Ƿ��������û������ʼ������
			if(x==m2&&(y-1)==n2 || (x-1)==m2&&y==n2 || x==m2&&y==n2 || (x+1)==m2&&y==n2 || (x-1)==m2&&(y+1)==n2 || (x+1)==m2&&(y+1)==n2)//���̹��2���ӵ����ҵ�̹��
				clear_my_tank(),screen_2("̹��2�Ż�������  ����ֵ��1",4),x=10,y=27,m2=0,n2=0,life--,check_game(),turn_up(my_tank);//�ҵ�̹�˻ص���ʼλ�ã�̹��2���ӵ���ʧ������ֵ��1�������Ϸ�Ƿ��������û������ʼ������
			if(x==m3&&(y-1)==n3 || (x-1)==m3&&y==n3 || x==m3&&y==n3 || (x+1)==m3&&y==n3 || (x-1)==m3&&(y+1)==n3 || (x+1)==m3&&(y+1)==n3)//���̹��3���ӵ����ҵ�̹��
				clear_my_tank(),screen_2("̹��3�Ż�������  ����ֵ��1",4),x=10,y=27,m3=0,n3=0,life--,check_game(),turn_up(my_tank);//�ҵ�̹�˻ص���ʼλ�ã�̹��3���ӵ���ʧ������ֵ��1�������Ϸ�Ƿ��������û������ʼ������
		}break;
	case 2 :
		{
			if(x==m1&&(y+1)==n1 || (x-1)==m1&&y==n1 || x==m1&&y==n1 || (x+1)==m1&&y==n1 || (x-1)==m1&&(y-1)==n1 || (x+1)==m1&&(y-1)==n1)
				clear_my_tank(),screen_2("̹��1�Ż�������  ����ֵ��1",4),x=10,y=27,m1=0,n1=0,life--,check_game(),turn_up(my_tank);
			if(x==m2&&(y+1)==n2 || (x-1)==m2&&y==n2 || x==m2&&y==n2 || (x+1)==m2&&y==n2 || (x-1)==m2&&(y-1)==n2 || (x+1)==m2&&(y-1)==n2)
				clear_my_tank(),screen_2("̹��2�Ż�������  ����ֵ��1",4),x=10,y=27,m2=0,n2=0,life--,check_game(),turn_up(my_tank);
			if(x==m3&&(y+1)==n3 || (x-1)==m3&&y==n3 || x==m3&&y==n3 || (x+1)==m3&&y==n3 || (x-1)==m3&&(y-1)==n3 || (x+1)==m3&&(y-1)==n3)
				clear_my_tank(),screen_2("̹��3�Ż�������  ����ֵ��1",4),x=10,y=27,m3=0,n3=0,life--,check_game(),turn_up(my_tank);

		}
	case 3 :
		{
			if(x==m1&&(y-1)==n1 || (x-1)==m1&&y==n1 || x==m1&&y==n1 || (x+1)==m1&&(y-1)==n1 || x==m1&&(y+1)==n1 || (x+1)==m1&&(y+1)==n1)
				clear_my_tank(),screen_2("̹��1�Ż�������  ����ֵ��1",4),x=10,y=27,m1=0,n1=0,life--,check_game(),turn_up(my_tank);
			if(x==m2&&(y-1)==n2 || (x-1)==m2&&y==n2 || x==m2&&y==n2 || (x+1)==m2&&(y-1)==n2 || x==m2&&(y+1)==n2 || (x+1)==m2&&(y+1)==n2)
				clear_my_tank(),screen_2("̹��2�Ż�������  ����ֵ��1",4),x=10,y=27,m2=0,n2=0,life--,check_game(),turn_up(my_tank);
			if(x==m3&&(y-1)==n3 || (x-1)==m3&&y==n3 || x==m3&&y==n3 || (x+1)==m3&&(y-1)==n3 || x==m3&&(y+1)==n3 || (x+1)==m3&&(y+1)==n3)
				clear_my_tank(),screen_2("̹��3�Ż�������  ����ֵ��1",4),x=10,y=27,m3=0,n3=0,life--,check_game(),turn_up(my_tank);
		}
	case 4 :
		{
			if(x==m1&&(y-1)==n1 || (x-1)==m1&&(y-1)==n1 || x==m1&&y==n1 || (x-1)==m1&&(y+1)==n1 || x==m1&&(y+1)==n1 || (x+1)==m1&&y==n1)
				clear_my_tank(),screen_2("̹��1�Ż�������  ����ֵ��1",4),x=10,y=27,m1=0,n1=0,life--,check_game(),turn_up(my_tank);
			if(x==m2&&(y-1)==n2 || (x-1)==m2&&(y-1)==n2 || x==m2&&y==n2 || (x-1)==m2&&(y+1)==n2 || x==m2&&(y+1)==n2 || (x+1)==m2&&y==n2)
				clear_my_tank(),screen_2("̹��2�Ż�������  ����ֵ��1",4),x=10,y=27,m2=0,n2=0,life--,check_game(),turn_up(my_tank);
			if(x==m3&&(y-1)==n3 || (x-1)==m3&&(y-1)==n3 || x==m3&&y==n3 || (x-1)==m3&&(y+1)==n3 || x==m3&&(y+1)==n3 || (x+1)==m3&&y==n3)
				clear_my_tank(),screen_2("̹��3�Ż�������  ����ֵ��1",4),x=10,y=27,m3=0,n3=0,life--,check_game(),turn_up(my_tank);
		}
	}
}

void change_tank_1()
{
	switch(state_1)
	{
	case 1 :
		{
			if(x1==m&&(y1-1)==n || (x1-1)==m&&y1==n || x1==m&&y1==n || (x1+1)==m&&y1==n || (x1-1)==m&&(y1+1)==n || (x1+1)==m&&(y1+1)==n)//����ҵ�̹���ӵ���̹��1��
				clear_tank_1(),screen_2("�������̹��1��   +100��",3),x1=2,y1=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();//̹��1�Żص���ʼλ�ã��ҵ�̹�˺��ӵ���ʧ����������ֵ��1,������100�����ʤ��

		}break;
	case 2 :
		{
			if(x1==m&&(y1+1)==n || (x1-1)==m&&y1==n || x1==m&&y1==n || (x1+1)==m&&y1==n || (x1-1)==m&&(y1-1)==n || (x1+1)==m&&(y1-1)==n)
				clear_tank_1(),screen_2("�������̹��1��   +100��",3),x1=2,y1=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	case 3 :
		{
			if(x1==m&&(y1-1)==n || (x1-1)==m&&y1==n || x1==m&&y1==n || (x1+1)==m&&(y1-1)==n || x1==m&&(y1+1)==n || (x1+1)==m&&(y1+1)==n)
				clear_tank_1(),screen_2("�������̹��1��   +100��",3),x1=2,y1=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	case 4 :
		{
			if(x1==m&&(y1-1)==n || (x1-1)==m&&(y1-1)==n || x1==m&&y1==n || (x1-1)==m&&(y1+1)==n || x1==m&&(y1+1)==n || (x1+1)==m&&y1==n)
				clear_tank_1(),screen_2("�������̹��1��   +100��",3),x1=2,y1=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	}
}

void change_tank_2()
{
	switch(state_2)
	{
	case 1 :
		{
			if(x2==m&&(y2-1)==n || (x2-1)==m&&y2==n || x2==m&&y2==n || (x2+1)==m&&y2==n || (x2-1)==m&&(y2+1)==n || (x2+1)==m&&(y2+1)==n)//����ҵ�̹���ӵ���̹��2��
				clear_tank_2(),screen_2("�������̹��2��   +100��",3),x2=14,y2=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();//̹��2�Żص���ʼλ�ã��ҵ�̹�˺��ӵ���ʧ����������ֵ��1,������100�����ʤ��

		}break;
	case 2 :
		{
			if(x2==m&&(y2+1)==n || (x2-1)==m&&y2==n || x2==m&&y2==n || (x2+1)==m&&y2==n || (x2-1)==m&&(y2-1)==n || (x2+1)==m&&(y2-1)==n)
				clear_tank_2(),screen_2("�������̹��2��   +100��",3),x2=14,y2=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	case 3 :
		{
			if(x2==m&&(y2-1)==n || (x2-1)==m&&y2==n || x2==m&&y2==n || (x2+1)==m&&(y2-1)==n || x2==m&&(y2+1)==n || (x2+1)==m&&(y2+1)==n)
				clear_tank_2(),screen_2("�������̹��2��   +100��",3),x2=14,y2=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	case 4 :
		{
			if(x2==m&&(y2-1)==n || (x2-1)==m&&(y2-1)==n || x2==m&&y2==n || (x2-1)==m&&(y2+1)==n || x2==m&&(y2+1)==n || (x2+1)==m&&y2==n)
				clear_tank_2(),screen_2("�������̹��2��   +100��",3),x2=14,y2=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	}
}

void change_tank_3()
{
	switch(state_3)
	{
	case 1 :
		{
			if(x3==m&&(y3-1)==n || (x3-1)==m&&y3==n || x3==m&&y3==n || (x3+1)==m&&y3==n || (x3-1)==m&&(y3+1)==n || (x3+1)==m&&(y3+1)==n)//����ҵ�̹���ӵ���̹��3��
				clear_tank_3(),screen_2("�������̹��3��   +100��",3),x3=27,y3=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();//̹��3�Żص���ʼλ�ã��ҵ�̹�˺��ӵ���ʧ����������ֵ��1,������100�����ʤ��

		}break;
	case 2 :
		{
			if(x3==m&&(y3+1)==n || (x3-1)==m&&y3==n || x3==m&&y3==n || (x3+1)==m&&y3==n || (x3-1)==m&&(y3-1)==n || (x3+1)==m&&(y3-1)==n)
				clear_tank_3(),screen_2("�������̹��3��   +100��",3),x3=27,y3=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	case 3 :
		{
			if(x3==m&&(y3-1)==n || (x3-1)==m&&y3==n || x3==m&&y3==n || (x3+1)==m&&(y3-1)==n || x3==m&&(y3+1)==n || (x3+1)==m&&(y3+1)==n)
				clear_tank_3(),screen_2("�������̹��3��   +100��",3),x3=27,y3=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	case 4 :
		{
			if(x3==m&&(y3-1)==n || (x3-1)==m&&(y3-1)==n || x3==m&&y3==n || (x3-1)==m&&(y3+1)==n || x3==m&&(y3+1)==n || (x3+1)==m&&y3==n)
				clear_tank_3(),screen_2("�������̹��3��   +100��",3),x3=27,y3=2,m=0,n=0,enemy--,score=score+100,check_lv(),produce_star(),check_game();

		}
	}
}

void check_lv()
{

	switch(score/1000)
	{
	case 0 :lv=1,speed=10;break;
	case 1 :if(lv==1) screen_2("��ϲ����2����",2);lv=2,speed=9;break;
	case 2 :if(lv==2) screen_2("��ϲ����3����",2);lv=3,speed=8;break;
	case 3 :if(lv==3) screen_2("��ϲ����4����",2);lv=4,speed=7;break;
	case 4 :if(lv==4) screen_2("��ϲ����5����",2);lv=5,speed=6;break;
	case 5 :if(lv==5) screen_2("��ϲ����6����",2);lv=6,speed=5;break;
	case 6 :if(lv==6) screen_2("��ϲ����7����",2);lv=7,speed=4;break;
	case 7 :if(lv==7) screen_2("��ϲ����8����",2);lv=8,speed=3;break;
	case 8 :if(lv==8) screen_2("��ϲ����9����",2);lv=9,speed=2;break;
	case 9 :if(lv==9) screen_2("��ϲ����10����,������",2);lv=10,speed=1;break;
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


	switch(level)//�ж��ǵڼ��أ�Ȼ��������Ӧ��ͼ
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
	char *poem[50]={"      ׳����½����","      �ɰ˶��Ұ�Ӫ��","      һ����������Զ","      ����Ԭ��ֻ����","      ������Ѫ�����","      �������ƿ���԰","      ת�۶���ȫ�й�","      �������������","      ����ȫ������Ǵ","      һ�����绮����","      ���ľ�Ӫ��ʮ��","      һҹ�ص����ǰ","      ���Ѿ�������ɢ","      ��������������","      ������֮��̾��","      ֻ����Ц����","      �����ƶѺܼ�","      ���ԾȲ�ҪǮ","      ��������������","      �����Լ��ȶ���","      ��������˭�ܹ�","      Ц�����˱�ը��","      ֻ�ǵ���̫��թ","      ����ˢ�Ƹ��ֿ�","      ���˽�η������","      ��̫����û����","      ����װ��ȫ����","      ����˲��ͻ���","      ����ȫ����ô��","      ����½��Ҫ����","      �񽫱�ʾĪ����","      �ͳ������ӿ���","      Ҫ��������ʲô","      ����44ɱ��ȫ��","      ���˱�ʾϹ����","      ��ʶ������ǰ","      �Ӵ��������´�","      ������֮�Թ���","      ��Ѱ����������","      ˭�˲�ʶ½����"," "," "," "," ","     ���Ȼ���ꡣ����     ","  ","  ","  ","  ","  "};
	char key;
	screen_2("��Ϸ��ͣ",4);
	while(1)
	{
		for(int i=0;i<50;i++)
		{
			Sleep(2000);
			if (kbhit()) //���
			{
				key = getch();//���񰴼�
				if(key==32)
				{
					screen_2("׼����ʼ",2);
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
	for(int i=15;i<29;i++)//������
	{
		gotoxy(62,i);
		printf("                          ");
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	gotoxy(62,15);
	printf("           ����           ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,17);
	printf("�� �� �� ��   ���Ʒ���");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,19);
	printf(" Сд w       �л�����");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,21);
	printf(" Сд s       �л�Ƥ��");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,23);
	printf(" Сд h       ����/�˳�");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,25);
	printf("  �ո�        ��ͣ/��ʼ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN);
	gotoxy(62,27);
	printf("��0�鿴����");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
	gotoxy(62,28);
	printf("                 �汾:1.0");

	while(1)
	{
		if (kbhit()) //��⣬����а�����ִ��if�����
		{
			key1 = getch();//���񰴼�
			if( 104 == key1 )
			{
				screen_2("������� ������Ϸ��",2);
				screen_3();
				break;
			}

			else if( 48 == key1 )
			{
				while(1)
				{
				for(int i=17;i<29;i++)//������
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
						printf("��  ��ɫ����ɳ���һ�δ��");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED);
						gotoxy(62,19);
						printf("��  ��ɫ�Ϳ�ɳ������δ��");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
						gotoxy(62,21);
						printf("��  ��ɫ����ɳ������δ��");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
						gotoxy(62,23);
						printf("��  ��ɫʯ���޷����ƻ�");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN);
						gotoxy(62,27);
						printf("���ո������");

					}break;

				case 2 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
						gotoxy(62,17);
						printf("��  ��ͨ�ӵ�������Ϊ1     ");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
						gotoxy(62,19);
						printf("��  ɢ���ɶ���ɫ������ɴ�");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
						gotoxy(62,21);
						printf("��Χ�ƻ��������޷���������");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
						gotoxy(62,23);
						printf("�͵ķ�������ƻ�          ");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
						gotoxy(62,25);
						printf("��  ���ݵ����Զ�һ�ŵ���ɫ");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
						gotoxy(62,27);
						printf("��������ƻ�");

					}break;

				case 3 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,17);
						printf("��  ѩ�����԰�ɫ������Ч��");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,19);
						printf("���ǿ��Խ��ϼҵ�Χǽ�޳ɰ�");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,21);
						printf("ɫ���飬�Ӷ������ϼ�");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
						gotoxy(62,23);
						printf("��  �����ڵ����ԶԳ���ɫʯ");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
						gotoxy(62,25);
						printf("�������з������һ���Եľ�");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
						gotoxy(62,27);
						printf("���ƻ�");

					}break;

				case 4 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,17);
						printf("ÿ���һ��̹�˼�100 �֣�ͬ");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,19);
						printf("ʱ��һ�����ʵ������ǣ��ռ�");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,21);
						printf("���ǿɽ���������Ƥ����ÿ��");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,23);
						printf("�����ﵽ��ǧʱ���㽫������");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,25);
						printf("�������ӵ��ٶȽ����죬");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,27);
						printf("ͬʱ����Ҳ����ǿ");

					}break;

				case 5 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,17);
						printf("��Ϸ�������ŵ�ͼ����������");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,19);
						printf("�󽫻����ϵͳ�������ͼ");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,21);
						printf("������ʾ�����Լ����ӵ���");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,23);
						printf("�޷����ϼҵ�Χǽ����ƻ�");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,25);
						printf("�����ǿ��Զ��ڲ�����ƻ�");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
						gotoxy(62,27);
						printf("����˱��ܰ�ǹ�ڶ����ϼ�");

					}break;

				case 6 :
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN);
						gotoxy(62,27);
						printf("���ո���˳�");

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
				screen_2("������� ������Ϸ��",2);
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
	for(int i=15;i<29;i++)//������
	{
		gotoxy(62,i);
		printf("                          ");
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
	gotoxy(62,17);
	printf("          ��ϲ����        ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,23);
	printf("    �� �ո�� ������Ϸ    ");

	while(1)
	{
		if(32 == getch())
		{

			int home0[3][4]={{2,2,2,2},{2,1,1,2},{2,1,1,2}};//����һ���ϼҵĳ�ʼ��ֵ

			{
				for(int i=0;i<5;i++)
					info[i]=" ";//֪ͨ����
			}
			{
				for(int i=0;i<3;i++)//�ϼҳ�ʼ��
					for(int j=0;j<4;j++)
						home[i][j]=home0[i][j];
			}	

			m=0  , n=0 ;//�ҵ�̹���ӵ�����������
			m1=0 , n1=0;//̹��1���ӵ�����������
			m2=0 , n2=0;//̹��2���ӵ�����������
			m3=0 , n3=0;//̹��3���ӵ�����������

			{
			for(int i=1;i<29;i++)
				for(int j=1;j<29;j++)
				{
					gotoxy(2*i,j);
					printf("  ");
				}
			}


			life=3;//������ʼ��
			enemy=13;//����������ʼ��
			s=0,t=0;//��������
			get_map();//��õ�ͼ
			refresh_map();//ˢ�µ�ͼ
			print_home();//��ӡ�ϼ�
			print_thing();//��ӡ��Ʒ

			direction=0;//�ҵ�̹���ӵ������ʼ��
			direction_1=0;//̹��1���ӵ������ʼ��
			direction_2=0;//̹��2���ӵ������ʼ��
			direction_3=0;//̹��3���ӵ������ʼ��

			x=10;y=27;//�ҵ�̹��λ�ó�ʼ��
			state=0;
			turn_up(my_tank);//�ҵ�̹�˷����ʼ��


			x1=2;y1=2;//̹��1��λ�ó�ʼ��
			state_1=0;
			turn_down_1(tank_1);//̹��1�ŷ����ʼ��

			x2=14;y2=2;//̹��2��λ�ó�ʼ��
			state_2=0;
			turn_down_2(tank_2);//̹��2�ŷ����ʼ��

			x3=27;y3=2;//̹��3��λ�ó�ʼ��
			state_3=0;
			turn_down_3(tank_3);//̹��3�ŷ����ʼ��

			screen_1();
			screen_2("��Ϸ��ʼ",4);
			break;
		}
	}



}


void gameover()
{

	for(int i=15;i<29;i++)//������
	{
		gotoxy(62,i);
		printf("                          ");
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
	gotoxy(62,17);
	printf("          ��Ϸ����        ");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
	gotoxy(62,23);
	printf("    �� �ո�� ���¿�ʼ    ");

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
			int home0[3][4]={{2,2,2,2},{2,1,1,2},{2,1,1,2}};//����һ���ϼҵĳ�ʼ��ֵ
			life=3;//������ʼ��
			enemy=13;//����������ʼ��
			level=1;//�ؿ���ʼ��
			weapons=1;//������ʼ��
			skin=1;//Ƥ����ʼ��
			star=1;//���ǳ�ʼ��
			s=0,t=0;//��������
			score=0;//������ʼ��
			lv=1;//�ȼ���ʼ��
			speed=10;//�ٶȳ�ʼ��
			{
				for(int i=0;i<5;i++)
					info[i]=" ";//֪ͨ����
			}
			{
				for(int i=0;i<3;i++)//�ϼҳ�ʼ��
					for(int j=0;j<4;j++)
						home[i][j]=home0[i][j];
			}	

			m=0  , n=0 ;//�ҵ�̹���ӵ�����������
			m1=0 , n1=0;//̹��1���ӵ�����������
			m2=0 , n2=0;//̹��2���ӵ�����������
			m3=0 , n3=0;//̹��3���ӵ�����������

			{
			for(int i=1;i<29;i++)
				for(int j=1;j<29;j++)
				{
					gotoxy(2*i,j);
					printf("  ");
				}
			}

			get_map();//��õ�ͼ
			refresh_map();//ˢ�µ�ͼ
			print_home();//��ӡ�ϼ�
			print_thing();//��ӡ��Ʒ

			direction=0;//�ҵ�̹���ӵ������ʼ��
			direction_1=0;//̹��1���ӵ������ʼ��
			direction_2=0;//̹��2���ӵ������ʼ��
			direction_3=0;//̹��3���ӵ������ʼ��

			x=10;y=27;//�ҵ�̹��λ�ó�ʼ��
			state=0;
			turn_up(my_tank);//�ҵ�̹�˷����ʼ��

			x1=2;y1=2;//̹��1��λ�ó�ʼ��
			state_1=0;
			turn_down_1(tank_1);//̹��1�ŷ����ʼ��

			x2=14;y2=2;//̹��2��λ�ó�ʼ��
			state_2=0;
			turn_down_2(tank_2);//̹��2�ŷ����ʼ��

			x3=27;y3=2;//̹��3��λ�ó�ʼ��
			state_3=0;
			turn_down_3(tank_3);//̹��3�ŷ����ʼ��

			screen_1();
			screen_2("��Ϸ��ʼ",4);
			screen_3();
}