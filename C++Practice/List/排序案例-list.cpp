#include<iostream>
#include<string>
#include<list>
using namespace std;

//list排序案例


class Person {
public:
	Person(string name, int age,int height) {
		this->m_Name = name;
		this->Age = age;
		this->height = height;
	}
	string m_Name;
	int Age;
	int height;
};

bool comparePerson(Person &p1,Person &p2) {
	//按照年龄排序 升序
	if (p1.Age==p2.Age)
	{
		//年龄相同 按照身高排序
		return p1.height > p2.height;
		
	}
	else {
		return p1.Age > p2.Age;
	}
	
}

void test01() {
	list<Person> L;//创建容器

	//录入数据
	Person p1("刘备", 35, 175);
	Person p2("关于", 30, 185);
	Person p3("张飞", 29, 180);
	Person p4("赵云", 25, 187);
	Person p5("诸葛", 35, 170);
	Person p6("刘墉", 50, 165);

	//插入数据
	L.push_back(p1);
	L.push_back(p2);
	L.push_back(p3);
	L.push_back(p4);
	L.push_back(p5);
	L.push_back(p6);

	for (list<Person>::iterator it = L.begin(); it != L.end(); it++) {
		cout << "姓名:" << (*it).m_Name << "\t年龄:" << (*it).Age << "\t身高:" << (*it).height << endl;

	}

	//排序
	cout << "--------------------------------" << endl;
	cout << "排序后:" << endl;
	L.sort(comparePerson);

	for (list<Person>::iterator it = L.begin(); it != L.end(); it++) {
		cout << "姓名:" << (*it).m_Name << "\t年龄:" << (*it).Age << "\t身高:" << (*it).height << endl;

	}

}


int main() {

	test01();
	system("pause");
	return 0;
}