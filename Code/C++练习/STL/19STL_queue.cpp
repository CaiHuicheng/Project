#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
/*
结构特点：
  先进先出（FIFO）
常用的方法：
  queue<int> q;
  q.push()------入队；
  q.pop()------出队；
  q.empty()----判队空；
  q.front()----得到队头元素；
  q.back()----得到队尾元素；
 应用范围：
  BFS，搜索问题等等。
 经典例题
   A strange lift
   此电梯每层只有上下两个按钮，且只能跨越固定的楼数，给出出发点A和目的地B，求最少按电梯多少次？ 
*/
int T,N,A,B;
int mp[220],f[220];
//mp表示每层楼的跨度，f表示该楼层是按第几次按钮到达的；
void BFS_Find(){
    queue<int>q;
    q.push(A);
    f[A]=1;
    int t;
    while(!q.empty()){
        t=q.front();
        q.pop();
        if(t==B)break;     //对于每个上下的选择造成的二叉树进行遍历。
        int next=t+mp[t];
        if(next>=1&&next<=B&&f[next]==0){
            q.push(next);
            f[next]=f[t]+1;
        }
        next=t-mp[t];
        if(next>=0&&next<=B&&f[next]==0){
            q.push(next);
            f[next]=f[t]+1;
        }
    }
    if(t!=B)
        f[B]=0;
}
int main()
{
    int i,j;
    while(scanf("%d",&N)&&N){
        if(N==0)break;
        scanf("%d%d",&A,&B);
        for(i=1;i<=N;i++)
        scanf("%d",&mp[i]);
        memset(f,0,sizeof(f));
        BFS_Find();
        printf("%d\n",f[B]-1);
    }
    return 0;
}


