#include<iostream>
#include<string>
#include"MyClass.hpp"
using namespace std;

void printIntArray(MyArray <int>& arr) {
	for (int i = 0; i <arr.getSize(); i++)
	{
		cout << arr[i] << " ";
	}
}

class Person
{
public:
	Person() {};
	Person(string name, int age) {
		this->m_Name = name;
		this->age = age;
	}
	string m_Name;
	int age;
};

void printPersonArray(MyArray <Person>& arr) {
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << arr[i].m_Name << " ";
		cout << arr[i].age << endl;
	}
}


void test01(){
	MyArray <int> arr1(5);
	for (int i = 0; i < 5; i++)
	{
		arr1.Push_Back(i);
	}
	printIntArray(arr1);
}

void test02() {
	MyArray <Person> arr2(10);
	Person p1("猴子", 1003);
	Person p2("韩跳跳", 2000);
	Person p3("安其拉", 3000);
	Person p4("满级啦", 2000);
	Person p5("哈哈哈", 0000);
	arr2.Push_Back(p1);
	arr2.Push_Back(p2);
	arr2.Push_Back(p3);
	arr2.Push_Back(p4);
	arr2.Push_Back(p5);
	printPersonArray(arr2);
    
	cout << arr2.getCapacity() << "   " << arr2.getSize()<< endl;


}


int main() {

	test02();

	system("pause");
	return 0;
}