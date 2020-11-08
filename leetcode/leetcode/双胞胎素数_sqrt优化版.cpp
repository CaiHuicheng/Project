//若两个素数之差为2，则称该素数为双胞胎数。求出[2,300]之内：
//（1）所有素数并保存到文件prime.txt中
//（2）有多少对双胞胎数；
//（3）最大一对双胞胎数
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>

using namespace std;

bool is_SuShu(int n) {
	//两个比较小的数
	if (n == 2 || n == 3) return true;
	//质数分布的规律：大于等于5的质数一定和6的倍数相邻。例如5和7，11和13,17和19等等
	if (n % 6 != 1 && n % 6 != 5) return false;
	//一个数若可以进行因数分解，那么分解时得到的两个数一定是一个小于等于sqrt(n)，一个大于等于sqrt(n)
	int tmp = sqrt(n);
	for (int i = 5; i <=tmp; i+=6)
	{
		if (n%i == 0 || n % (i + 2) == 0) {
			return false;
		}
	}
	return true;
}


int main() {
	int n = 1000;
	int i = 0;
	int count = 0;
	int max = 0;
	FILE * fp = fopen("prime.txt", "w");
	for (i = 2; i <= n; i++) {
		if (is_SuShu(i)) {
			fprintf(fp, "%d\n", i);
			if (is_SuShu(i + 2)) {
				count++;
				max = i;
			}
		}
	}
	cout << "一共有双胞胎:" << count << "对" << endl;
	cout << "最大的双胞胎对" << max<<" "<< max+2 << endl;
	system("pause");
	return 0;
}