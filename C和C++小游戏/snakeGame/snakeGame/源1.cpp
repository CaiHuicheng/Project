#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdio.h>


const int WIDTH = 1024;			// ��Ļ��1024
const int HEIGHT = 768;			// ��Ļ��576
const int MAPW = (WIDTH * 4);	// ��ͼ��
const int MAPH = (HEIGHT * 4);	// ��ͼ��
const int AINUM = 300;			// AI ����
const int FNUM = 500;			// FOOD ����
const int IMGNUM = 10;
const double PI = 3.1415926;
#define DISTANCE(x1, y1, x2, y2)	(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)))

void set();
void delay(DWORD ms);
void start();
void Draw();
void run();

// ��� ���� ʳ�� ֮��
class Ball
{
public:
	bool		life;		// �Ƿ񱻳� �� 1,�� 0
	COLORREF	color;		// ��ɫ
	float		x;			// ����
	float		y;

	Ball();
	~Ball();
	virtual void draw() {};
};

// ��������(Ϸ�ƹ���) �̳�Ball
class Monster :public Ball
{
public:
	float r;		// �뾶
	Monster();
	~Monster();
	void draw();
	void move();	// ai����
	void control();	// ��ҿ���
	void eat(Monster& compare);
	void lostweight();
};

// ʳ�� �̳�Ball
class Food :public Ball
{
public:
	char shape;

	Food();
	~Food();
	void draw();
	void newfood();
	void eaten(Monster& compare);
	void lostweight();
};

Food* food = new Food[FNUM];
Monster* ai = new Monster[AINUM];
Monster* player = new Monster;
IMAGE		Map(MAPW, MAPH);
float lx = 0, ly = 0, rx = MAPW, ry = MAPH - 100;				// ����λ��


int main()
{
	initgraph(WIDTH, HEIGHT);
	set();
	start();
	BeginBatchDraw();
	while (true)
	{
		Draw();
		run();
		FlushBatchDraw();	// ��ʾ����Ļ�������
		delay(10);			// �����ӳ�
	}

	closegraph();
}

void set()
{
	srand((unsigned)time(NULL));		// �����
	SetWorkingImage(&Map);
	setbkcolor(WHITE);					// ��ɫ����
	cleardevice();						// ��ʼ������
	SetWorkingImage();

	// �����ֵ
	player->x = (float)(rand() % MAPW);
	player->y = (float)(rand() % MAPH);
	player->color = RGB(rand() % 256, rand() % 256, rand() % 256);		// �����ɫ
	for (int i = 0; i < AINUM; i++)
	{
		ai[i].x = (float)(rand() % MAPW);
		ai[i].y = (float)(rand() % MAPH);
		ai[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);	// �����ɫ
	}
	for (int i = 0; i < FNUM; i++)
	{
		food[i].x = (float)(rand() % MAPW);
		food[i].y = (float)(rand() % MAPH);
		food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);	// �����ɫ
	}
}

// ������Ϸ
void Draw()
{
	SetWorkingImage(&Map);
	cleardevice();
	for (int i = 0; i < FNUM; i++)
		food[i].draw();
	for (int i = 0; i < AINUM; i++)
		ai[i].draw();
	player->draw();

	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 20);	// �ıʵ���ɫ��״̬
	setlinecolor(RGB(0, 100, 0));
	line((int)lx - 20, (int)ly - 20, (int)lx - 20, (int)ry + 20);	// ����
	line((int)lx - 20, (int)ly - 20, (int)rx + 20, (int)ly - 20);	// �Ϻ�
	line((int)lx - 20, (int)ry + 20, (int)rx + 20, (int)ry + 20);	// �º�
	line((int)rx + 20, (int)ly - 20, (int)rx + 20, (int)ry + 20);	// ����
	setlinestyle(PS_NULL);

	IMAGE map2;
	const float asptime = 1;
	getimage(&map2, (int)(player->x - WIDTH * .5 - player->r * asptime), (int)(player->y - HEIGHT * .5 - player->r * asptime),
		(int)(WIDTH + player->r * asptime * 2), (int)(HEIGHT + player->r * asptime * 2));
	float aspx = WIDTH / (WIDTH + player->r * 2);
	float aspy = HEIGHT / (HEIGHT + player->r * 2);
	SetWorkingImage();
	setaspectratio(aspx, aspy);
	putimage(0, 0, &map2);

	const int mapw = 180;
	const int maph = 130;
	IMAGE map((int)(mapw / aspx), (int)(maph / aspy));			// С��ͼ
	SetWorkingImage(&map);
	setbkcolor(RGB(120, 165, 209));	// ǳ��ɫ����
	cleardevice();

	for (int i = 0; i < AINUM; i++)	// �� AI
	{
		if (ai[i].life == 0) continue;
		setfillcolor(ai[i].color);
		fillcircle((int)(ai[i].x * mapw / WIDTH / 4 / aspx), (int)(ai[i].y * maph / HEIGHT / 4 / aspy),
			int(((ai[i].r * 2) / (aspx + aspy)) / ((MAPH / HEIGHT) * (MAPH / HEIGHT)) - 0.5));
	}

	setfillcolor(player->color);		// �����
	fillcircle((int)(player->x * mapw / WIDTH / 4 / aspx), (int)(player->y * maph / HEIGHT / 4 / aspy),
		int(((player->r * 2) / (aspx + aspy)) / ((MAPH / HEIGHT) * (MAPH / HEIGHT) - 0.5)));

	SetWorkingImage();
	putimage((int)(WIDTH - map.getwidth() + player->r * asptime * 2), 0, &map);
	setlinecolor(LIGHTGRAY);	// �ı���ɫ   ״̬
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, (int)(3 / aspx));
	line(map2.getwidth() - map.getwidth(), 0, map2.getwidth() - map.getwidth(), map.getheight());
	line(map2.getwidth() - map.getwidth(), map.getheight(), map2.getwidth(), map.getheight());

	setlinestyle(PS_NULL);		// �ָ���
	settextstyle((int)(40 / (aspx + aspy)), 0, _T("����"));
	TCHAR str[16];
	sprintf_s(str, _T("����:%.1f kg"), (float)(player->r * player->r * PI / 300));
	settextcolor(BLUE);			// ������
	outtextxy(0, 0, str);

}

// ������Ϸ
void run()
{
	if (player->r <= 0)	player->life = false;

	if (!player->life)	// �ж���Ϸ�Ƿ����
	{
		HWND hwnd = GetHWnd();
		MessageBox(hwnd, _T("����!�㱻����!"), _T("��Ϸ����"), MB_OK | MB_ICONEXCLAMATION);	// ����
		closegraph();
		exit(0);
	}
	int eaten = 0;
	for (int i = 0; i < AINUM; i++)
		if (ai[i].life == 0)
			eaten++;
	if (eaten >= AINUM)	// �Ƿ�Ե����� AI
	{
		HWND hwnd = GetHWnd();
		MessageBox(hwnd, _T("����������!��ϲ����!"), _T("��Ϸ����"), MB_OK | MB_ICONEXCLAMATION);	// ����
		closegraph();
		exit(0);
	}

	// ���
	player->control();
	player->lostweight();

	// ai
	for (int i = 0; i < AINUM; i++)
	{
		if (ai[i].r <= 0)	ai[i].life = false;
		if (ai[i].life)
		{
			ai[i].lostweight();
			ai[i].move();
			player->eat(ai[i]);
			ai[i].eat(*player);
			for (int j = 0; j < AINUM; j++)
			{
				if (ai[j].life)
				{
					if (i == j) continue;
					ai[i].eat(ai[j]);
					ai[j].eat(ai[i]);
				}
			}
		}
	}

	// ʳ��
	for (int i = 0; i < FNUM; i++)
	{
		food[i].newfood();
		food[i].eaten(*player);
		food[i].lostweight();

		for (int j = 0; j < AINUM; j++)
			food[i].eaten(ai[j]);
	}

	// ��Ȧ
	lx += 0.35f;
	ly += 0.3f;
	rx -= 0.35f;
	ry -= 0.3f;
}

void delay(DWORD ms)
{
	static DWORD oldtime = GetTickCount();

	if (GetTickCount() - oldtime < ms)
		Sleep(1);
	oldtime = GetTickCount();
}

void start()
{
	setbkcolor(WHITE);		// ��ɫ����
	cleardevice();			// ��ʼ������
	settextcolor(RED);		// ������
	setbkmode(TRANSPARENT);
	settextstyle(128, 0, _T("����"));
	outtextxy(320, 40, _T("̰����"));
	settextstyle(32, 0, _T("����"));
	outtextxy(740, 135, _T("Ver 2.0"));
	settextcolor(BLUE);		// ������
	outtextxy(304, 240, _T("W���ơ�S���ơ�A���ơ�D����"));
	outtextxy(112, 340, _T("��ܴ��򡡡���׷��С�򡡡���̰��ʳ�������ǿʵ��"));
	settextcolor(BLACK);	//������
	settextstyle(32, 0, _T("����"));
	outtextxy(384, 500, _T("���������ʼ��Ϸ"));
	settextstyle(20, 0, _T("����"));
	outtextxy(810, 10, _T("���� QQ: 2190038793"));
	_getch();
}

// ����ĺ���
Ball::Ball()
{
	life = 1;
}

Ball::~Ball() {}

// ʳ��ĺ���
Food::Food()
{
	shape = rand() % 10 + 1;
}

Food::~Food() {}

void Food::draw()
{
	if (life == 0) return;
	setfillcolor(color);
	switch (shape)		// ��״
	{
	case 1:		solidellipse((int)x, (int)y, (int)x + 2, (int)y + 4);				break;
	case 2:		solidellipse((int)x, (int)y, (int)x + 4, (int)y + 2);				break;
	case 3:		solidrectangle((int)x, (int)y, (int)x + 4, (int)y + 2);				break;
	case 4:		solidrectangle((int)x, (int)y, (int)x + 2, (int)y + 4);				break;
	case 5:		solidroundrect((int)x, (int)y, (int)x + 2, (int)y + 4, 2, 2);		break;
	case 6:		solidroundrect((int)x, (int)y, (int)x + 4, (int)y + 2, 2, 2);		break;
	case 7:		solidroundrect((int)x, (int)y, (int)x + 4, (int)y + 2, 4, 2);		break;
	case 8:		solidroundrect((int)x, (int)y, (int)x + 4, (int)y + 2, 2, 4);		break;
	case 9:		solidroundrect((int)x, (int)y, (int)x + 4, (int)y + 2, 1, 1);		break;
	case 10:	fillcircle((int)x, (int)y, 3);										break;
	}
}

void Food::newfood()
{
	if (!life)
	{
		life = 1;
		color = RGB(rand() % 256, rand() % 256, rand() % 256);
		x = (float)(rand() % MAPW);
		y = (float)(rand() % MAPH);
		shape = rand() % 10 + 1;
	}
}

void Food::eaten(Monster& compare)
{
	if (!life)	return;
	if (DISTANCE(compare.x, compare.y, x, y) < compare.r)
	{
		compare.r = (float)sqrt(compare.r * compare.r + 16);
		life = 0;				// ʳ�ﱻ��
	}
}

void Food::lostweight()
{
	if (x > rx || x < lx || y < ly || y >ry)
		life = 0;
}

// ����ĺ���
Monster::Monster()
{
	r = 10.0f + rand() % 5;
}

Monster::~Monster() {}

void Monster::draw()
{
	if (life == 0) return;
	setfillcolor(color);		// ������
	fillcircle((int)x, (int)y, int(r + 0.5));
}

void Monster::move()
{
	if (life == 0)	return;
	double min_DISTANCE1 = 15000000;
	double min_DISTANCE2 = 15000000;
	int min1 = -1, min2 = -1, k, q;
	for (k = 0; k < AINUM; k++)		// AI ���� AI
	{
		if ((r > ai[k].r + 3) && (ai[k].life == 1))
		{
			if (DISTANCE(x, ai[k].x, y, ai[k].y) < min_DISTANCE1)
			{
				min_DISTANCE1 = DISTANCE(x, ai[k].x, y, ai[k].y);
				min1 = k;
			}
		}
	}
	for (q = 0; q < FNUM; q++)		// AI ���� ʳ��
	{
		if (food[q].life == 1)
		{
			if (DISTANCE(x, food[q].x, y, food[q].y) < min_DISTANCE2)
			{
				min_DISTANCE2 = DISTANCE(x, food[q].x, y, food[q].y);
				min2 = q;
			}
		}
	}
	if (x > rx - 20) x--;
	if (x < lx + 20) x++;
	if (y > ry - 20) y--;
	if (y < ly + 20) y++;

	if (min_DISTANCE1 > min_DISTANCE2) // ʳ���
	{
		if (rand() % 5 > 3)	return;
		if (rand() % 2)
		{
			if (x > food[min2].x)	x--;
			else x++;
		}
		else
		{
			if (y > food[min2].y)	y--;
			else y++;
		}
	}
	else
	{
		if (rand() % 5 > 3)	return;
		if (rand() % 2)
		{
			if (x < ai[min1].x) x++;
			else x--;
		}
		else
		{
			if (y < ai[min1].y) y++;
			else y--;
		}
	}
}

// �ƶ����ƺ���
void Monster::control()
{
	if (!life)	return;
	// �ȴպ���
	if (GetAsyncKeyState(65) & 0x8000)  player->x -= 2;	// ���
	if (GetAsyncKeyState(87) & 0x8000)  player->y -= 2;	// ����
	if (GetAsyncKeyState(83) & 0x8000)  player->y += 2;	// ����
	if (GetAsyncKeyState(68) & 0x8000)  player->x += 2;	// �ұ�

	// if (GetAsyncKeyState(VK_SPACE) & 0x8000)  player->r += 5;	// ���׵��� �ǵ�  �ǵ� �ǵ�ɾ
}

void Monster::eat(Monster& compare)
{
	if (r > compare.r)
	{
		if (DISTANCE(x, y, compare.x, compare.y) < 4 / 5.0 * r + compare.r)
		{
			r = (float)sqrt(r * r + compare.r * compare.r);
			compare.life = 0;
			compare.r = 0;
		}
	}
}

void Monster::lostweight()
{
	if (r * r * PI > 120000)
		r -= 1 / r;
	if (x > (rx - r) || x - r < lx || y - r < ly || y >(ry - r))
		r -= 1.f;
}