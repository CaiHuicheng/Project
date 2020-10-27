#include<iostream>
#include<string>
using namespace std;

class Cube {
public:
	void setL(double L) {
		m_L = L;
	}
	double getL() {
		return m_L;
	}
	void setW(double W) {
		m_W = W;
	}
	double getW() {
		return m_W;
	}
	void setH(double H) {
		m_H = H;
	}
	double getH() {
		return m_H;
	}

	double calculateS() {
		return 2 * m_L*m_W + 2 * m_W*m_H + 2 * m_L*m_H;
	}
	double calculateV() {
		return m_L * m_H*m_W;
	}
	bool isSameByClass(Cube & c) {
		if (m_H == c.getH() && m_L == c.getL() && m_W == c.getW()) {
			return true;
		}
		return false;
	}

private:
	double m_L;
	double m_W;
	double m_H;
};

//利用全局变量判断是否相等
bool isSame(Cube &c1, Cube &c2) {
	//cout << c1.getH() << c2.getH() << endl;
	if (c1.getH() == c2.getH()&&c1.getL() == c2.getL()&&c1.getW() == c2.getW()) {
		return true;
	}
	return false;
}

int main() {

	Cube c1;
	c1.setL(10);
	c1.setW(10);
	c1.setH(10);

	cout << c1.calculateS() << endl;

	cout << c1.calculateV() << endl;
	Cube c2;
	c2.setL(10);
	c2.setW(10);
	c2.setH(10);

	bool ret = isSame(c1, c2);
	cout << ret << endl;
	if (ret)
	{
		cout << "c1与c2相同" << endl;
	}
	bool ret2 = c1.isSameByClass(c2);
	if (ret2)
	{
		cout << "class中 c1与c2相同" << endl;
	}
	system("pause");
	return 0;
}