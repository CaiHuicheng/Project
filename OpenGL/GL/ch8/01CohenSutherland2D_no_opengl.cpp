#include <iostream>

using namespace std;

float wxl, wxr, wyb, wyt;//定义全局变量，方便各函数使用


int cohensutherland(int d[], float &x, float &y, float k)//直线段剪裁函数，根据窗口外的端点和斜率找到线段与窗口边界的交点
{
	if (d[0] == 1)//如果端点在左侧（1001，0001，0101三个区域）
	{
		y = k*(wxl - x) + y;
		x = wxl;//找到线段和x=wxl的交点
	}
	if (d[1] == 1)//如果端点在右侧（1010，0010，0110三个区域）
	{
		y = k*(wxr - x) + y;
		x = wxr;//找到线段和x=wxr的交点
	}
	if ((d[2] == 1) && (d[0] == 0) && (d[1] == 0) && (d[3] == 0))//如果端点在下侧（0100一个区域）
	{
		x = (wyb - y) / k + x;
		y = wyb;//算出线段和窗口下侧边界的交点
	}
	if ((d[3] == 1) && (d[0] == 0) && (d[1] == 0) && (d[2] == 0))//如果端点在上侧（1000一个区域）
	{
		x = (wyt - y) / k + x;
		y = wyt;//算出线段和窗口上侧边界的交点
	}
	return 0;
}


int code(int a[], float x, float y)//对两端点坐标编码
{
	if (x<wxl) a[0] = 1;
	else a[0] = 0;
	if (x>wxr) a[1] = 1;
	else a[1] = 0;
	if (y<wyb) a[2] = 1;
	else a[2] = 0;
	if (y>wyt) a[3] = 1;
	else a[3] = 0;
	return 0;
}

int main()
{
	int d1[4] = { 0,0,0,0 };
	int d2[4] = { 0,0,0,0 };//端点的区域编码，用数组来表示
	float x1, y1, x2, y2;
	cout << "分别输入两点坐标和窗口的四条边界坐标：";
	cout << endl << "x1=";
	cin >> x1;
	cout << "y1=";
	cin >> y1;
	cout << "x2=";
	cin >> x2;
	cout << "y2=";
	cin >> y2;
	cout << "wxl=";
	cin >> wxl;
	cout << "wxr=";
	cin >> wxr;
	cout << "wyb=";
	cin >> wyb;
	cout << "wyt=";
	cin >> wyt;


	while (1)
	{
		code(d1, x1, y1);//对端点p1进行区域编码
		code(d2, x2, y2);//对端点p2进行区域编码
		if ((d1[0] == 0) && (d1[1] == 0) && (d1[2] == 0) && (d1[3] == 0) && (d2[0] == 0) && (d2[1] == 0) && (d2[2] == 0) && (d2[3] == 0))//code1|code2=0
		{
			cout << "在窗口内的两点坐标：" << "(" << x1 << "," << y1 << ")" << "(" << x2 << "," << y2 << ")"; break;
		}
		else if ((d1[0] & d2[0]) | (d1[1] & d2[1]) | (d1[2] & d2[2]) | (d1[3] & d1[3]))//code1&code2=1
		{
			cout << "直线段在窗口外"; break;
		}
		else//和边界有交点（实交点和虚交点）
		{
			float k = (y2 - y1) / (x2 - x1);
			if (!(d1[0] | d1[1] | d1[2] | d1[3]))//p1点在窗口内，则交换p1和p2的坐标值和编码值
			{
				float x, y;
				int t, i;
				x = x2; x2 = x1; x1 = x;
				y = y2; y2 = y1; y1 = y;
				for (i = 0; i <= 3; i++)
				{
					t = d2[i];
					d2[i] = d1[i];
					d1[i] = t;
				}
			}
			cohensutherland(d1, x1, y1, k);//对p1进行裁剪
		}
	}

	system("pause");
	return 0;
}