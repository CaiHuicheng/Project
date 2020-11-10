#include <windows.h>
#include <process.h>
#include <iostream>


const int THREADNUM = 5;

class CSingleton
{
private:
	CSingleton()
	{
		std::cout << "构造" << std::endl;
	}
	~CSingleton()
	{
		std::cout << "析构" << std::endl;
	}

public:
	static CSingleton* GetInstance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSingleton();
		}
		return m_pInstance;
	}

private:
	static CSingleton* m_pInstance;
};

CSingleton* CSingleton::m_pInstance = nullptr;

unsigned int __stdcall SingletonProc(void* pram)
{
	CSingleton* pInstance = CSingleton::GetInstance();

	Sleep(50);
	std::cout << "pInstance：" << pInstance << std::endl;

	return 0;
}

int main()
{

	HANDLE hHandle[THREADNUM] = {};
	int nCurThread = 0;

	while (nCurThread < THREADNUM)
	{
		hHandle[nCurThread] = (HANDLE)_beginthreadex(NULL, 0, SingletonProc, NULL, 0, NULL);
		nCurThread++;
	}
	WaitForMultipleObjects(THREADNUM, hHandle, TRUE, INFINITE);
	system("pause");
	return 0;
}