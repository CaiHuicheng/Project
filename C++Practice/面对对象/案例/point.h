#pragma once
#include<iostream>
#include<string>
using namespace std;

//µ„¿‡
class Point {
public:
	void setX(double X);
	double getX();
	void setY(double Y);
	double getY();
private:
	double x;
	double y;
};