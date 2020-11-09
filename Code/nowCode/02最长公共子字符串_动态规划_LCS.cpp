#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Solution {

public:
	/**
	* longest common substring
	* @param str1 string字符串 the string
	* @param str2 string字符串 the string
	* @return string字符串
	*/
	int max(int a, int b) {
		return a>b ? a : b;
	}

	string LCS(string str1, string str2) {
		// write code here
		const int l1 = str1.size();
		const int l2 = str2.size();
		//动态规划
		vector<vector<int>> dp(l1 + 1, vector<int>(l2 + 1, 0));
		string res;
		int len = LCS_length(str1, str2, dp);
		cout << len << endl;
		res = getLCS(str1, str2, dp, l1, l2);
		for (auto d : dp) {
			for (auto p : d) {
				cout << p;
			}
			cout << endl;
		}
		return res;
	}
	int LCS_length(string str1, string str2, vector<vector<int>>&dp) {
		if (str1 == "" || str2 == "")
			return 0;
		//动态方程
		/*
		if str1 == str2：
		dp[i][j] = dp[i-1]dp[j-1]+1;
		else
		dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
		*/
		for (int i = 1; i < str1.length() + 1; i++) {
			for (int j = 1; j < str2.length() + 1; j++) {
				if (str1[i - 1] == str2[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1] + 1;
				}
				else {
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				}
			}
		}
		return dp[str1.length()][str2.length()];
	}
	string getLCS(string str1, string str2, vector<vector<int>>&dp, int i, int j) {
		string res;
		while (i > 0 && j > 0) {
			if (str1[i - 1] == str2[j - 1]) {
				res = str1[i - 1] + res;
				--i;
				--j;
			}
			else {
				if (dp[i - 1][j] >= dp[i][j - 1])
					--i;
				else// if (dp[i - 1][j] < dp[i][j - 1])
					--j;
				/*else {
				res = getLCS(str1, str2, dp, i - 1, j);
				res = getLCS(str1, str2, dp, i, j - 1);
				return res;
				}*/
			}
		}
		return res;
	}
};

//
//int main() {
//	Solution s;
//	string str1 = "ABAABABBABAABA", str2 = "BABABA";
//	//string str1 = "1AB2345CD", str2 = "12345EF";
//	string str = s.LCS(str1, str2);
//	cout << str << endl;
//	system("pause");
//	return 0;
//}