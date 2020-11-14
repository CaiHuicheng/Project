#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int solution(string str1[],string str2,int m)
{
	int j=0,k=0;
	for (int i = 0; i < m; i++)
	{
		// 判断规则中是否有*号存在
		if (str1[i].find('*') == string::npos)
		{
			if(str1[i].compare(str2) == 0)
				return 1; // 过滤掉了
		}
		else if (str1[i].find('*') == 0)
		{
			// * 号在前,从后往前比
			j = str1[i].size()-1;
			k = str2.size()-1;
			for(;j>=0,k>=0;j--,k--)
			{
				if (str1[i].c_str()[j] != str2.c_str()[k])
					break;				
			}			
		}
		else
		{
			// * 号在后,从前往后比
			j=0,k=0;
			for(;j<=str1[i].size()-1,k<=str2.size()-1;j++,k++)
			{
				if (str1[i].c_str()[j] != str2.c_str()[k])		
					break;				
			}			
		}
		if (str1[i].c_str()[j] == '*')
		{
			return 1; // 如果只有*不等表示其他都一样还是要过滤掉
		}
	}
	return 0;// 循环结束后都不符合要求表示不过滤掉

}
int  main()
{
	int m,n;// m 规则，n条数
	cin>>m;
	cin>>n;
	string * arr1 = new string[m];// m 条规则
	string  * arr2 = new string[n];// n 条ip
	int * arr = new int[n];
	for (int i = 0; i < m; i++)
	{
		cin>>arr1[i];
	}
	for (int j = 0; j < n; j++)
	{
		cin>>arr2[j];
	}
	for (int k = 0; k < n; k++)
	{
		arr[k]= solution(arr1,arr2[k],m);
		cout<<arr[k]<<" ";
	}
	cout<<endl;
	return 0;
}