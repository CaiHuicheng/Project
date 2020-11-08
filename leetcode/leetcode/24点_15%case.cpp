#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

char ope[4] = { '+','-','*','/' };

int getNum(map<char, int> map, char ch) {
	if (map.count(ch)) {
		return map[ch];
	}
	return -1;
}
int calcute(int a, int b, char index)
{
	if (index == '+') return a + b; //若为+，则返回相应结果 
	else if (index == '-') return a - b;
	else if (index == '*') return a*b;
	else if (index == '/')
		if (b != 0)
			return a / b; //只有当分母不为0时，返回结果
	return -1;
}

void equal_24(map<char, int> map, string inn, string &res) {
	int nums[4], i = 0;
	for (auto c : inn) {
		nums[i] = getNum(map, c);
		i++;
	}
	/*
	1.((a#b)#c)#d
	2.(a#(b#c))#d
	3.a#((b#c)#d)
	4.(a#b)#(c#d)
	5.a#(b#(c#d))
	*/
	for (int i = 0; i<inn.length(); i++) {
		for (int j = 0; j<inn.length(); j++) {
			for (int k = 0; k<inn.length(); k++) {
				int ret = calcute(calcute(calcute(nums[0], nums[1], ope[i]), nums[2], ope[j]), nums[3], ope[k]);
				if (ret == 24) {
					cin >> nums[0] >> ope[i] >> nums[1] >> ope[j] >> nums[2] >> ope[k] >> nums[3] >> res;
				}
				ret = calcute(calcute(nums[0], calcute(nums[1], nums[2], ope[i]), ope[j]), nums[3], ope[k]);
				if (ret == 24) {
					cin >> nums[0] >> ope[i] >> nums[1] >> ope[j] >> nums[2] >> ope[k] >> nums[3] >> res;
				}
				ret = calcute(nums[0], calcute(calcute(nums[1], nums[2], ope[i]), nums[3], ope[j]), ope[k]);
				if (ret == 24) {
					cin >> nums[0] >> ope[i] >> nums[1] >> ope[j] >> nums[2] >> ope[k] >> nums[3] >> res;
				}
				ret = calcute(calcute(nums[0], nums[1], ope[i]), calcute(nums[3], nums[2], ope[j]), ope[k]);
				if (ret == 24) {
					cin >> nums[0] >> ope[i] >> nums[1] >> ope[j] >> nums[2] >> ope[k] >> nums[3] >> res;
				}
				ret = calcute(nums[0], calcute(nums[1], calcute(nums[2], nums[3], ope[i]), ope[j]), ope[k]);
				if (ret == 24) {
					cin >> nums[0] >> ope[i] >> nums[1] >> ope[j] >> nums[2] >> ope[k] >> nums[3] >> res;
				}
			}
		}
	}

}


int main() {
	map<char, int> map{
		{ 'A',1 },{ '2',2 },{ '3',3 },{ '4',4 },{ '5',5 },{ '6',6 },
		{ '7',7 },{ '8',8 },{ '9',9 },{ '10',10 },{ 'J',11 },{ 'Q',12 },
		{ 'K',13 }
	};
	string inn_o;
	while (getline(cin, inn_o)) {
		string inn;
		int rf1 = inn_o.find("Ker");
		int rf2 = inn_o.find("KER");
		if (rf1 >= 0 || rf2 >= 0) cout << "ERROR" << endl;
		else {
			unsigned int i;
			for (i = 0; i<inn_o.length(); i++) {
				if (inn_o[i] == ' ') continue;
				inn.push_back(inn_o[i]);
			}
			string res;
			equal_24(map, inn, res);
			if (res.size() == 0) cout << "NONE" << endl;
			else {
				cout << res << endl;
			}
		}
	}
	return 0;
}
}