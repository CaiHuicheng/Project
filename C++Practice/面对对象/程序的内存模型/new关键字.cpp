#include<iostream>
using namespace std;
//new关键字 堆区利用new开辟数据 
int * func() {
	//在堆区创建整型数据
	//new返回的是该数据类型的指针
	int * p = new int(10);
	return p;
}

//new关键字 堆区利用new开辟数组
void func2() {
	int * arr = new int[10];
	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 100;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << "\t" << endl;
	}
	//删除多个数据（数组）时加上【】
	delete[] arr;
}

int main() {
	int * p = func();
	cout << *p << endl;
	cout << *p << endl;
	cout << *p << endl;
	func2();
	//堆区的数据由程序员管理开辟，程序员管理释放
	//如果想要释放堆区的数据，利用关键字 delete
	delete p;
	//cout << *p << endl; //内存已经释放了，不能进行访问否则报错
	system("pause");
	return 0;
}