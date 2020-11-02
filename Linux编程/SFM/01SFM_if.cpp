#include<iostream>

using namespace std;
//比如我们定义了小明一天的状态如下
enum
{
	GET_UP,
	GO_TO_SCHOOL,
	HAVE_LUNCH,
	GO_HOME,
	DO_HOMEWORK,
	SLEEP,
};


int main()
{
	int state = GET_UP;
	//小明的一天
	while (1)
	{
		if (state == GET_UP)
		{
			GetUp(); //具体调用的函数
			state = GO_TO_SCHOOL;  //状态的转移
		}
		else if (state == GO_TO_SCHOOL)
		{
			Go2School();
			state = HAVE_LUNCH;
		}
		else if (state == HAVE_LUNCH)
		{
			HaveLunch();
		}
		...
		else if (state == SLEEP)
		{
			Go2Bed();
			state = GET_UP;
		}
	}

	return 0;
}
