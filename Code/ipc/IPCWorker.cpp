#include <Windows.h>
#include <tchar.h> //_tcscmp() _TCHAR*

#define COMMUNICATION_OBJECT_NAME TEXT("__FILE_MAPPING__")
#define SYNCHRONIZING_MUTEX_NAME TEXT("__TEST_MUTEX__")

typedef struct _tagCOMMUNICATIONOBJECT 
{
	HWND hWndClient;
	BOOL bExitLoop;
	LONG lSleepTimeout;
}COMMUNICATIONOBJECT, *PCOMMUNICATIONOBJECT;

int main(int argc, _TCHAR* argv[])
{
	HBRUSH hBrush = NULL;

	if (_tcscmp(TEXT("blue"), argv[0]) == 0)
	{
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
	}
	else
	{
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
	}

	HWND hWnd = NULL;
	HDC hDC = NULL;
	RECT rectClient = { 0 };
	LONG lWaitTimeout = 0;
	HANDLE hMapping = NULL;
	PCOMMUNICATIONOBJECT pCommObject = NULL;
	BOOL bContinueLoop = TRUE;

    //OpenMutex获得该已命名互斥量的句柄(如果有的话)
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, SYNCHRONIZING_MUTEX_NAME);
	hMapping = OpenFileMapping(FILE_MAP_READ, FALSE, COMMUNICATION_OBJECT_NAME);

	if (hMapping)
	{
		while (bContinueLoop)
		{
			WaitForSingleObject(hMutex, INFINITE);
			//获得指向文件映像对象的句柄
			pCommObject = (PCOMMUNICATIONOBJECT)MapViewOfFile(hMapping,
				FILE_MAP_READ, 0, 0, sizeof(COMMUNICATIONOBJECT));

			if (pCommObject)
			{
				bContinueLoop = !pCommObject->bExitLoop;
				hWnd = pCommObject->hWndClient;
				lWaitTimeout = pCommObject->lSleepTimeout;
				UnmapViewOfFile(pCommObject);
				hDC = GetDC(hWnd);
				if (GetClientRect(hWnd, &rectClient))
				{
					FillRect(hDC, &rectClient, hBrush);
				}

				ReleaseDC(hWnd, hDC);
				Sleep(lWaitTimeout); //故意的,因为记录的时候,进程切换太快根本注意不到
			}
			ReleaseMutex(hMutex); //释放互斥量的所有权,让其它进程可以获得互斥量,继续执行其他任务
		}
	}

	CloseHandle(hMapping);
	CloseHandle(hMutex);
	DeleteObject(hBrush);
	return 0;
}
