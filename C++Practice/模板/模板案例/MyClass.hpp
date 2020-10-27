//自己的通用数组类
#pragma once
#include<iostream>
#include<string>
using namespace std;

template<class T>
class MyArray
{
public:
	//有参构造  参数 容量
	MyArray(int capacity) {
		/*cout << "有参构造" << endl;*/
		this->m_Capacity = capacity;
		this->m_Size = 0;
		this->pAddress = new T[this->m_Capacity];
	}

	//拷贝函数
	MyArray(const MyArray& arr) {
		/*cout << "拷贝函数" << endl;*/
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		//深拷贝
		this->pAddress = new T[arr.m_Capacity];
		for (int i = 0; i < arr.m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}

	MyArray& operator=(const MyArray & arr) {
		//先判断堆区是否有数据
		/*cout << "operator=函数" << endl;*/
		if (this->pAddress!=NULL)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}
		//深拷贝
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[arr.m_Capacity];
		for (int i = 0; i <this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}

	//尾插法
	void Push_Back(const T & val) {
		if (this->m_Capacity == this->m_Size)
		{
			return;
		}
		this->pAddress[this->m_Size] = val;
		this->m_Size++;
	}

	//尾删法
	void Pop_Back() {
		if (this->m_Size==0)
		{
			return;
		}
		this->m_Size--;
	}

	//通过下标访问数据
	T& operator[](int index) {
		return this->pAddress[index];
	}
	//返回数组容量
	int getCapacity() {
		return this->m_Capacity;
	}
	//返回数据大小
	int getSize() {
		return this->m_Size;
	}
	//祈构函数
	~MyArray() {
		if (this->pAddress!=NULL)
		{
			/*cout << "祈构函数" << endl;*/
			delete[] this->pAddress;
			this->pAddress = NULL;
		}
	}
private:
	T * pAddress;//指针指向堆区的真实数组
	int m_Capacity;//数组数目
	int m_Size;//数组大小
};