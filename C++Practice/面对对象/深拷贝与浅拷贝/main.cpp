#include<iostream>
#include<string>
using namespace std;

//简单的赋值拷贝
//在堆区重新申请空间，进行拷贝操作

class Person {
public:
	Person() {
		cout << "默认" << endl;
	}
	Person(int age,int h) {
		cout << "有参" << endl;
		m_age = age;
		m_h = new int(h);

	}
	~Person() {
		if (m_h !=NULL)
		{
			delete m_h;
			m_h = NULL;
		}
		cout << "祈构" << endl;
	}
	Person(const Person &p) {
		cout << "拷贝调用" << endl;
		m_age = p.m_age;
		m_h = new int(*p.m_h);
	}
	int m_age;
	int *m_h;
};

int main() {
	Person p1(16,180);
	cout << p1.m_age<<"  " << *p1.m_h << endl;
	//堆区的资源重复释放 p1所占的内存还没删除p2也要占用
	/*Person p2(p1);*/

	//可以通过自己实现拷贝构造函数 解决上述问题
	Person p2(p1);

	cout << p2.m_age << "  " << *p2.m_h << endl;
	system("pause");
	return 0;
}
