#pragma once
#include<iostream>
#include<string>
#include"point.h"
using namespace std;
class Circle {
public:
	void setR(double R);
		double getR();
		void setCenter(Point Center);
		Point getCenter();

private:
	double r;
	Point center;

};