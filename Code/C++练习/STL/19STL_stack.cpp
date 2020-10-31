#include<stdio.h>
#include<string.h>
#include<stack>
using namespace std;

/*
结构特点：
  后进先出（FILO）
常用的方法：
  stack<char> s;
  s.push()------入栈，压栈；
  s.pop()------出栈，弹出；
  s.empty()----判栈空；
  s.top()----得到栈顶元素；
应用范围：
  DFS，迷宫问题等等。
经典例题：
   Train Problem I
 火车按照给定顺序进站，判断是否可以按给定顺序出站,若能这输出YES.和  in，out的顺序和最后FINISH，否则输出NO.和FINISH
*/
int main()
{
    int n, i, j, k, flag[50];//记录in out的数组
    char s1[15], s2[15];
    stack <char> s;
    while(~scanf("%d %s%s",&n,s1,s2))
    {
        while(!s.empty())  
        s.pop();      //清空栈，类似于set.clear();
        memset(flag,-1,sizeof(flag));
        j = k = 0;
        for(i = 0; i < n; i++)
        {
            s.push(s1[i]);
            flag[k++] = 1;
            while(!s.empty() && s.top() == s2[j])
            {
                flag[k++] = 0;//当栈顶元素与s2(出站顺序一样时就出站)；
                s.pop();
                j++;
            }
        }
        if(j == n)   //当所有元素都出站，就符合要求；
        {      
            printf("Yes.\n");
            for(i = 0; i < k; i++)
            {
                if(flag[i])
                    printf("in\n");
                else
                    printf("out\n");
            }
        }
        else
            printf("No.\n");
        printf("FINISH\n");
    }
    return 0;
}