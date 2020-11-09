// 动态规划法解决最长子序列.cpp : 定义控制台应用程序的入口点。
//
#include <string>
#include <iostream>

#ifndef MAX
#define MAX(X,Y) ((X>=Y)? X:Y)
#endif

using namespace std;

int **Lcs_length(string X, string Y, int **B)
{
	int x_len = X.length();
	int y_len = Y.length();

	int **C = new int *[x_len + 1];
	for (int i = 0; i <= x_len; i++)
	{
		C[i] = new int[y_len + 1];        //定义一个存放最优解的值的表；
	}

	for (int i = 1; i <= x_len; i++)
	{
		C[i][0] = 0;
		B[i][0] = -2;                     //-2表示没有方向
	}


	for (int j = 0; j <= y_len; j++)
	{
		C[0][j] = 0;
		B[0][j] = -2;
	}

	for (int i = 1; i <= x_len; i++)
	{
		for (int j = 1; j <= y_len; j++)
		{

			if (X[i - 1] == Y[j - 1])
			{
				C[i][j] = C[i - 1][j - 1] + 1;

				B[i][j] = 0;             //0表示斜向左上
			}
			else
			{
				if (C[i - 1][j] >= C[i][j - 1])
				{
					C[i][j] = C[i - 1][j];
					B[i][j] = -1;       //-1表示竖直向上；
				}
				else
				{
					C[i][j] = C[i][j - 1];
					B[i][j] = 1;        //1表示横向左
				}
			}

		}
	}
	return C;
}

void OutPutLCS(int **B, string X, int str1_len, int str2_len)
{

	if (str1_len == 0 || str2_len == 0)
	{
		return;
	}
	if (B[str1_len][str2_len] == 0)   //箭头左斜
	{
		OutPutLCS(B, X, str1_len - 1, str2_len - 1);
		printf("%c", X[str1_len - 1]);
	}
	else if (B[str1_len][str2_len] == -1)
	{
		OutPutLCS(B, X, str1_len - 1, str2_len);
	}
	else
	{
		OutPutLCS(B, X, str1_len, str2_len - 1);
	}
}

int main()
{
	string X = "1AB2345CD";
	string Y = "12345EF";

	int x_len = X.length();
	int y_len = Y.length();

	int **C;

	int **B = new int *[x_len + 1];
	for (int i = 0; i <= x_len; i++)
	{
		B[i] = new int[y_len + 1];
	}


	C = Lcs_length(X, Y, B);

	for (int i = 0; i <= x_len; i++)
	{
		for (int j = 0; j <= y_len; j++)
		{
			cout << C[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;

	for (int i = 0; i <= x_len; i++)
	{
		for (int j = 0; j <= y_len; j++)
		{
			cout << B[i][j] << " ";
		}
		cout << endl;
	}

	OutPutLCS(B, X, x_len, y_len);
	cout << endl;
	system("pause");
	return 0;
}