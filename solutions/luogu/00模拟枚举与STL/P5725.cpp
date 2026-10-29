#include<stdio.h>

int main() {
    int n;scanf("%d",&n);
    // //第一块 直接打印就好了了，相当于就是直接打印一个正方形呗
    // 每一个数字的数值就是按照自然数增长的1，2，一直到n的平方
    // 只不过这里要把个位数的都用0来补齐两个站位
    int cnt=1; // 我用cnt来表达这个自然增长的计数
    for(int i=1 ;i<=n;i++){
        for(int j =1;j<=n;j++){
            printf("%02d",cnt);
            cnt++;
        }
        printf("\n");
    }
    printf("\n");//这里有个换行哟
    cnt =1; //清零
    /*
        第二块的话，观察一下，第i行有i个数，所以
        数的增长其实是1 + 2 + 3 +... 到n的
        第n行是最长的，没有空格，每一行有i个数
        就会相比与最长的n个数少了n-i个数
        那么我就打印 n-i个 “  ”两个空格就好了
    */
    for(int i=1;i<=n;i++){
        for(int k=1;k<=n-i;k++)printf("  "); //打印空格
        for(int j=1;j<=i;j++){
            printf("%02d",cnt); //打印数字
            cnt++;
        }
        printf("\n");
    }
}