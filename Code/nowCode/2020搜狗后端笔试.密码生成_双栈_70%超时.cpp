#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int n, m, i, j;
int main() {
    cin >> n >> m;
    vector<int> v(n, 0);
    stack<vector<int>> s1, s2;
    for (int k = 1; k <= m; k++) {
        cin >> i >> j;
        if (s1.empty()) {
            s1.push({i, k, 0});
            s1.push({j, k, 1});
        } else {
            if (s1.top()[0] < i) {
                s1.push({i, k, 0}); //0代表左区间，1代表右区间
                s1.push({j, k, 1});
            } else {
                while (!s1.empty() && s1.top()[0] >= i) {
                    s2.push(s1.top());s1.pop();
                }
                if (!s1.empty() && i - s1.top()[0] != 1 && !s2.empty()) {
                    s1.push({i-1, s2.top()[1], s2.top()[2]});
                }
                s1.push({i,k,0});
                while (!s2.empty() && s2.top()[0] <= j) {
                    s2.pop();
                }
                s1.push({j,k,1});
                while (!s2.empty()) {
                    s1.push(s2.top());
                    s2.pop();
                }
            }
        }
    }
    char um[2] = {'l', 'r'};
    int end, beg;
    while (s1.size() > 1) {
        end = s1.top()[0];
        int val1 = s1.top()[1];
        char c1 = um[s1.top()[2]];
        s1.pop();
        beg = s1.top()[0];
        int val2 = s1.top()[1];
        char c2 = um[s1.top()[2]];
        if (c1 == 'r' && c2 == 'r') {
            for (int i = end; i > beg; i--) {
                v[i] = val1;
            }
        } else if (c2 == 'l' && c1 == 'l'){
            for (int i = beg; i < end; i++) {
                v[i] = val2;
            }
        } else if (c2 == 'l' && c1 == 'r') {
            for (int i = beg; i <= end; i++) {
                v[i] = val2;
            }
        }
    }
    long long res = 0;
    for (int i = 1; i < n; i++) {
        res += i * v[i];
        res %= 100000009;
    }
    cout << res << endl;
}