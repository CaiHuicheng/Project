#include<iostream>
#include<string>
#include"point.h"
#include"circle.h"
using namespace std;
////����
//class Point {
//public:
//	void setX(double X) {
//		x = X;
//	}
//	double getX() {
//		return x;
//	}
//	void setY(double Y) {
//		y = Y;
//	}
//	double getY() {
//		return y;
//	}
//private:
//	double x;
//	double y;
//};
//class Circle {
//public:
//	void setR(double R) {
//		r = R;
//	}
//	double getR() {
//		return r;
//	}
//	void setCenter(Point Center) {
//		 center = Center;
//	}
//	Point getCenter() {
//		return center;
//	}
//
//private:
//	double r;
//	Point center;
//
//};

//�жϵ��Բ�Ĺ�ϵ
void isInCircle(Circle &c, Point &p) {
	double disance =
		(c.getCenter().getX() - p.getX())*(c.getCenter().getX() - p.getX()) +
		(c.getCenter().getY() - p.getY())*(c.getCenter().getY() - p.getY());

	double rDisance = c.getR() * c.getR();
		if (disance==rDisance)
		{
			cout << "����Բ��" << endl;
		}
		else if (disance>rDisance)
		{
			cout << "����Բ��" << endl;
		}
		else {
			cout << "����Բ��" << endl;
		}
}

int main() {
	Circle c;
	c.setR(10);
	Point center;
	center.setX(10);
	center.setY(10);
	c.setCenter(center);

	Point p;
	p.setX(11);
	p.setY(11);

	isInCircle(c,p);
	system("pause");
	return 0;
}

