class Solution {
public:
    enum State {
        STATE_INITIAL,
        STATE_INT_SIGN,
        STATE_INTEGER,
        STATE_POINT,
        STATE_POINT_WITHOUT_INT,
        STATE_FRACTION,
        STATE_EXP,
        STATE_EXP_SIGN,
        STATE_EXP_NUMBER,
        STATE_END,
    };

    enum CharType {
        CHAR_NUMBER,
        CHAR_EXP,
        CHAR_POINT,
        CHAR_SIGN,
        CHAR_SPACE,
        CHAR_ILLEGAL,
    };

    CharType toCharType(char ch) {
        if (ch >= '0' && ch <= '9') {
            return CHAR_NUMBER;
        } else if (ch == 'e' || ch == 'E') {
            return CHAR_EXP;
        } else if (ch == '.') {
            return CHAR_POINT;
        } else if (ch == '+' || ch == '-') {
            return CHAR_SIGN;
        } else if (ch == ' ') {
            return CHAR_SPACE;
        } else {
            return CHAR_ILLEGAL;
        }
    }

    bool isNumber(string s) {
        unordered_map<State, unordered_map<CharType, State>> transfer{
            {
                STATE_INITIAL, {
                    {CHAR_SPACE, STATE_INITIAL},
                    {CHAR_NUMBER, STATE_INTEGER},
                    {CHAR_POINT, STATE_POINT_WITHOUT_INT},
                    {CHAR_SIGN, STATE_INT_SIGN},
                }
            }, {
                STATE_INT_SIGN, {
                    {CHAR_NUMBER, STATE_INTEGER},
                    {CHAR_POINT, STATE_POINT_WITHOUT_INT},
                }
            }, {
                STATE_INTEGER, {
                    {CHAR_NUMBER, STATE_INTEGER},
                    {CHAR_EXP, STATE_EXP},
                    {CHAR_POINT, STATE_POINT},
                    {CHAR_SPACE, STATE_END},
                }
            }, {
                STATE_POINT, {
                    {CHAR_NUMBER, STATE_FRACTION},
                    {CHAR_EXP, STATE_EXP},
                    {CHAR_SPACE, STATE_END},
                }
            }, {
                STATE_POINT_WITHOUT_INT, {
                    {CHAR_NUMBER, STATE_FRACTION},
                }
            }, {
                STATE_FRACTION,
                {
                    {CHAR_NUMBER, STATE_FRACTION},
                    {CHAR_EXP, STATE_EXP},
                    {CHAR_SPACE, STATE_END},
                }
            }, {
                STATE_EXP,
                {
                    {CHAR_NUMBER, STATE_EXP_NUMBER},
                    {CHAR_SIGN, STATE_EXP_SIGN},
                }
            }, {
                STATE_EXP_SIGN, {
                    {CHAR_NUMBER, STATE_EXP_NUMBER},
                }
            }, {
                STATE_EXP_NUMBER, {
                    {CHAR_NUMBER, STATE_EXP_NUMBER},
                    {CHAR_SPACE, STATE_END},
                }
            }, {
                STATE_END, {
                    {CHAR_SPACE, STATE_END},
                }
            }
        };

        int len = s.length();
        State st = STATE_INITIAL;

        for (int i = 0; i < len; i++) {
            CharType typ = toCharType(s[i]);
            if (transfer[st].find(typ) == transfer[st].end()) {
                return false;
            } else {
                st = transfer[st][typ];
            }
        }
        return st == STATE_INTEGER || st == STATE_POINT || st == STATE_FRACTION || st == STATE_EXP_NUMBER || st == STATE_END;
    }
};
class SolutionERROR {
public:
	bool isNumber(string s) {
		vector<map<char, int>> states;
		map<char, int> temp;
		// s代表sign，正负号
		// d代表digit，数字

		// 所有表之外的状态转移即为非法数字

		// 0，头部空格状态
		temp[' '] = 0;  // 输入 空格 还是 空格状态0
		temp['s'] = 1;  // 输入 正负号 进入 符号状态1
		temp['d'] = 2;  // 输入 数字 进入 小数点前数字状态2
		temp['.'] = 4;	// 输入 小数点 进入 前为空小数点后首位数字状态4
		states.push_back(temp);
		temp.clear();
		// 1，符号状态
		temp['d'] = 2;  // 输入 数字 进入 小数点前的数字状态2
		temp['.'] = 4;  // 输入小数点 进入 前为空小数点后首位数字状态4
		states.push_back(temp);
		temp.clear();
		// 2，小数点前数字状态
		temp['d'] = 2;  // 输入 数字 还是 小数点前的数字状态2
		temp['.'] = 3;  // 输入 小数点 进入 前非空小数点后的数字状态3
		temp['e'] = 5;	// 输入 e 进入 指数符号状态5
		temp[' '] = 8;	// 输入 空格 进入 尾部空格状态8
		states.push_back(temp);
		temp.clear();
		// 3，前非空小数点后的数字状态
		temp['d'] = 3;	// 输入 数字 还是 前非空小数点后的数字状态3
		temp['e'] = 5;	// 输入 e 进入 指数符号状态5
		temp[' '] = 8; 	// 输入 空格 进入尾部空格状态8
		states.push_back(temp);
		temp.clear();
		// 4，前为空小数点后首位数字状态4
		temp['d'] = 3; 	// 输入 数字 进入 前非空小数点后的数字状态3
		states.push_back(temp);
		temp.clear();
		// 5，指数符号状态5
		temp['s'] = 6;  // 输入 正负号 进入 指数后的符号状态6
		temp['d'] = 7;	// 输入 数字 进入 指数位置数字状态7
		states.push_back(temp);
		temp.clear();
		// 6，指数后的符号状态
		temp['d'] = 7;  // 输入 数字 进入 指数位置数字状态7
		states.push_back(temp);
		temp.clear();
		// 7，指数位置数字状态
		temp['d'] = 7;  // 输入 数字 还是 指数位置数字状态7
		temp[' '] = 8;  // 输入 空格 进入 尾部空格状态8
		states.push_back(temp);
		temp.clear();
		// 8，尾部空格状态
		temp[' '] = 8;  // 输入 空格 还是 尾部空格状态8
		states.push_back(temp);
		temp.clear();
		
		// 初始状态，在0状态
		int p = 0;
		// 状态转移的输入key
		char t;
		// 逐字符
		for (int i = 0; i < s.length();i++) {
			char c = s[i];
			// 如果是数字，key='d'
			if (c >= '0'&&c <= '9') {
				t = 'd';
			}
			// 如果是正负号，key='s'
			else if (c == '+' || c == '-') {
				t = 's';
			}
			// 如果是其他字符，key='c'，包含了'.' ' ' 其他非法字符
			else {
				t = c;
			}
			map<char, int>::iterator it = states[p].find(t);
			// 如果找不到这个状态转移，则非法数字
			if (it == states[p].end()) {
				return false;
			}
			// 如果找到，获取转移后的状态
			p = (int)it->second;
		}
		// 是否在允许结尾的状态2 3 7 8
		return p == 2 || p == 3 || p == 7 || p == 8;
	}
};