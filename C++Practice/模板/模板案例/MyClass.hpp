//�Լ���ͨ��������
#pragma once
#include<iostream>
#include<string>
using namespace std;

template<class T>
class MyArray
{
public:
	//�вι���  ���� ����
	MyArray(int capacity) {
		/*cout << "�вι���" << endl;*/
		this->m_Capacity = capacity;
		this->m_Size = 0;
		this->pAddress = new T[this->m_Capacity];
	}

	//��������
	MyArray(const MyArray& arr) {
		/*cout << "��������" << endl;*/
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		//���
		this->pAddress = new T[arr.m_Capacity];
		for (int i = 0; i < arr.m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}

	MyArray& operator=(const MyArray & arr) {
		//���ж϶����Ƿ�������
		/*cout << "operator=����" << endl;*/
		if (this->pAddress!=NULL)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}
		//���
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[arr.m_Capacity];
		for (int i = 0; i <this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}

	//β�巨
	void Push_Back(const T & val) {
		if (this->m_Capacity == this->m_Size)
		{
			return;
		}
		this->pAddress[this->m_Size] = val;
		this->m_Size++;
	}

	//βɾ��
	void Pop_Back() {
		if (this->m_Size==0)
		{
			return;
		}
		this->m_Size--;
	}

	//ͨ���±��������
	T& operator[](int index) {
		return this->pAddress[index];
	}
	//������������
	int getCapacity() {
		return this->m_Capacity;
	}
	//�������ݴ�С
	int getSize() {
		return this->m_Size;
	}
	//������
	~MyArray() {
		if (this->pAddress!=NULL)
		{
			/*cout << "������" << endl;*/
			delete[] this->pAddress;
			this->pAddress = NULL;
		}
	}
private:
	T * pAddress;//ָ��ָ���������ʵ����
	int m_Capacity;//������Ŀ
	int m_Size;//�����С
};