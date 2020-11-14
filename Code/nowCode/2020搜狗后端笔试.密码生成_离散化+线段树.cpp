#include<cstdio>
#include<cstring>
#include<algorithm>
#define Lchild(x) ((x) << 1)
#define Rchild(x) (((x) << 1) + 1)
using namespace std;
typedef long long ll;
const ll MOD = 100000009;
const int maxn = 1000010;
inline void write(ll x) {
    if (x < 0)putchar('-'), x = -x;
    if (x > 9)write(x / 10);
    putchar(x % 10 + 48);
}
inline int read() {
    int k = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9') {
        if (c == '-')f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        k = (k << 1) + (k << 3) + c - 48;
        c = getchar();
    }
    return k * f;
}
struct op {
    int l, r;
}a[maxn];
//[l, r]的区间和
inline ll sum(ll l, ll r) {return (l + r) * (r - l + 1) / 2;}
int n, m;
int x[maxn << 1], x_size, realx_size, c[maxn << 1];
int L, R;
ll ans;
struct SegmentTree {
    struct Node {
        int value, tag_Set;
    }nodes[maxn << 3];
    SegmentTree() {
        memset(nodes, 0, sizeof(nodes));
    }
    inline void pushup(int root) {
        nodes[root].value = nodes[Lchild(root)].value + nodes[Rchild(root)].value;
    }
    inline void build(int root, int l, int r) {
        nodes[root].tag_Set = 0;
        if (l == r)nodes[root].value = 0;
        else {
            int m = (l + r) >> 1;
            build(Lchild(root), l, m);
            build(Rchild(root), m + 1, r);
            pushup(root);
        }
    }
    inline void pushdown(int root, int l, int r) {
        int m = (l + r) >> 1;
        if(nodes[root].tag_Set) {
            nodes[Lchild(root)].tag_Set = nodes[Rchild(root)].tag_Set = nodes[root].tag_Set;
            nodes[Lchild(root)].value = (m - l + 1) * nodes[root].tag_Set;
            nodes[Rchild(root)].value = (r - m) * nodes[root].tag_Set;
            nodes[root].tag_Set = 0;
        }
    }
    inline void updateSet(int root, int curl, int curr, int tarl, int tarr, int k) {
        if (tarr < curl || curr < tarl)return;
        if (tarl <= curl && curr <= tarr) {
            nodes[root].tag_Set = k;
            nodes[root].value = (curr - curl + 1) * k;
            return;
        }
        pushdown(root, curl, curr);
        int m = (curl + curr) >> 1;
        if (tarl <= m) updateSet(Lchild(root), curl, m, tarl, tarr, k);
        if (tarr > m) updateSet(Rchild(root), m + 1, curr, tarl, tarr, k);
        pushup(root);
    }
    inline int query(int root, int curl, int curr, int tarl, int tarr) {
        if (tarr < curl || curr < tarl)return 0;
        if (tarl <= curl && curr <= tarr) {
            return nodes[root].value;
        }
        pushdown(root, curl, curr);
        int m = (curl + curr) >> 1;
        int ret = 0;
        if (tarl <= m) ret += query(Lchild(root), curl, m, tarl, tarr);
        if (tarr > m) ret += query(Rchild(root), m + 1, curr, tarl, tarr);
        return ret;
    }
    
};
SegmentTree tree;

int main() {
    n = read(), m = read();
    for(int i = 1; i <= m; ++i) {
        x[++x_size] = a[i].l = read();
        x[++x_size] = a[i].r = read();
    }
    sort(x + 1, x + x_size + 1);
    realx_size = unique(x + 1, x + x_size + 1) - x - 1;
    x_size = realx_size;
    for(int i = 2; i <= x_size; ++i)
        if(x[i] - x[i - 1] > 1) x[++realx_size] = x[i] - 1, x[++realx_size] = x[i - 1] + 1;
    x_size = realx_size;
    sort(x + 1, x + x_size + 1);
    realx_size = unique(x + 1, x + x_size + 1) - x - 1;
    tree.build(1, 1, realx_size);
    for(int i = 1; i <= m; ++i) {
        L = lower_bound(x + 1, x + realx_size + 1, a[i].l) - x;
        R = lower_bound(x + 1, x + realx_size + 1, a[i].r) - x;
        tree.updateSet(1, 1, realx_size, L, R, i);
    }
    for(int i = 1; i <= realx_size; ++i)
        c[i] = tree.query(1, 1, realx_size, i, i);
    for(int i = 1; i < realx_size; ++i)
        ans = (ans + sum(x[i], x[i + 1] - 1) * (1ll * c[i])) % MOD;
    ans = (ans + x[realx_size] * (1ll * c[realx_size])) % MOD;
    write(ans);
}
