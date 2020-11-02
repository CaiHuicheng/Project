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

		switch(state)
		{
		case GET_UP:
			GetUp(); //具体调用的函数
			state = GO_TO_SCHOOL;  //状态的转移
			break;
		case GO_TO_SCHOOL:
			Go2School();
			state = HAVE_LUNCH;
			break;
		case HAVE_LUNCH:
			HaveLunch();
			state = GO_HOME;
			break;
			...
		default:
			break;
	    }
	}

	return 0;
}
