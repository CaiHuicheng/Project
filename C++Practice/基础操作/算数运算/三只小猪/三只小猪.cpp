#include<iostream>
using namespace std;

int main() {

	//三只小猪称体重，判断那只最重

	int num1 = 0, num2 = 0, num3 = 0;
	cout << "请输入小猪A体重：" << endl;
	cin >> num1;

	cout << "请输入小猪B体重：" << endl;
	cin >> num2;

	cout << "请输入小猪C体重：" << endl;
	cin >> num3;

	cout << "小猪A的重量为：" << num1 << "kg" << endl;
	cout << "小猪B的重量为：" << num2 << "kg" << endl;
	cout << "小猪C的重量为：" << num3 << "kg" << endl;

	if (num1==num2&&num2==num3&&num1==num3)
	{
		cout << "三只一样重" << endl;
	}
	else {
		if (num1 > num2)
		{
			if (num1 > num3)
			{
				cout << "小猪A最重" << endl;
			}
			else
			{
				cout << "小猪C最重" << endl;
			}
		}
		else
		{
			if (num2 > num3)
			{
				cout << "小猪B最重" << endl;
			}
			cout << "小猪C最重" << endl;
		}
	}
	system("pause");
	return 0;
}