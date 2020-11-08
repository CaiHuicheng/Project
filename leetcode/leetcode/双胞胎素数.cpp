#include <stdio.h>
//若两个素数之差为2，则称该素数为双胞胎数。求出[2,300]之内：
//（1）所有素数并保存到文件prime.txt中
//（2）有多少对双胞胎数；
//（3）最大一对双胞胎数
int is_Sushu(int n){//返回值是1表示是素数
	int i=0;
	if(n==2){
		return 1;
	}else{
		for(i=2;i<n;i++){
			if(n%i==0)
				return 0;//表示n不是素数
		}
		return 1;
	}
}
 
int main()
{
	int is_Sushu(int n);//返回值是1表示是素数
	int i=0;
	int count=0;
	int max=0;
	FILE *fp = fopen("e:\\data\\prime.txt","w");
	for(i=2;i<=298;i++){
		if(is_Sushu(i)){
			fprintf(fp,"%d\n",i);
			if(is_Sushu(i+2)){
				count++;	
				max=i;
			}
		}
	}
	printf("一共有双胞胎%d对\n",count);
	printf("最大的双胞胎对 %d %d\n",max,max+2);
	return 0;
}