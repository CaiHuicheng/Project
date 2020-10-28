//售票系统
void Test2()
{
    //创建一个互斥量
    g_hMutex = CreateMutex(NULL, FALSE, NULL);

    //初始化火车票
    TICKET ticket;
    ticket.nCount = 100;
    strcpy(ticket.strTicketName, "北京-->赣州");

    const int THREAD_NUMM = 8;
    THD_DATA threadSale[THREAD_NUMM];
    HANDLE hThread[THREAD_NUMM];
    for(int i = 0; i < THREAD_NUMM; ++ i)
    {
        threadSale[i].pTicket = &ticket;
        string strThreadName = convertToString(i);

        strThreadName = "窗口" + strThreadName;

        strcpy(threadSale[i].strThreadName, strThreadName.c_str());

        //创建线程
        hThread[i] = CreateThread(NULL, NULL, SaleTicket, &threadSale[i], 0, NULL);

        //请求获得一个互斥量锁
        WaitForSingleObject(g_hMutex, INFINITE);
        cout << threadSale[i].strThreadName << "开始出售 " << threadSale[i].pTicket->strTicketName << " 的票..." << endl;
        //释放互斥量锁
        ReleaseMutex(g_hMutex);

        //关闭线程
        CloseHandle(hThread[i]);
    }

    system("pause");
}