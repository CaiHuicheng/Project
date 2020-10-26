#include<iostream>
#include<map>
#include<string>
#include<math.h>

using namespace std;

int max(int a, int b) {
	return a > b ? a : b;
}

/*
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:

输入: "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

*/
//滑动窗口
//思路链接：https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/solution/wu-zhong-fu-zi-fu-de-zui-chang-zi-chuan-cshi-xian-/


class Solution01 {
public:
	int lengthOfLongestSubstring(string s) {
		int start(0), end(0), len(0), result(0);
		int sSize = int(s.size());
		char tmpChar;
		while (end<sSize) {
			tmpChar = s[end];
			for (int i = start; i<end; i++) {
				if (tmpChar == s[i]) {
					start = i + 1;
					len = end - start;
					break;
				}
			}
			end++;
			len++;
			result = max(result, len);
		}
		return result;
	}
};


//利用hashmap
class Solution02 {
public:
	int lengthOfLongestSubstring(string s) {
		int start(0), end(0), len(0), result(0);
		int sSize = int(s.size());
		//unordered_map<char, int> hash;
		map<char, int> hash;
		while (end<sSize) {
			char tempChar = s[end];
			if (hash.find(tempChar) != hash.end() && hash[tempChar] >= start) {
				start = hash[tempChar] + 1;
				len = end - start;
			}
			hash[tempChar] = end;
			end++;
			len++;
			result = max(result, len);
		}
		return result;
	}
};

int main() {
	cout << max(3, 4) << endl;
	system("pause");
	return 0;
}