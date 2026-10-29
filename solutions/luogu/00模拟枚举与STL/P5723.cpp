#include<stdio.h>

bool ok(int n){ //判断一个数是不是质数
    for(int i=2 ;i*i<=n;i++){
        if(n%i==0)return false;
    }
    return true;
}
// 思路： 从2开始枚举到100000，因为l都不超过100000
// 这个范围肯定够了，判断当前的数是不是质数（调用函数）
// 如果是的话，就给cnt++ 让l -= 当前的质数
// 循环结束的条件就是 i已经超过l了！哪怕你是质数也不够减少了。

// 当然啦，也可以用判断法，比如l是一直减少的，又遇到一个质数的时候
// 我只要判断是不是已经不够减了，自然也就该退出
// 最后记得打印cnt
int main(){
     int l ; scanf("%d",&l);
     int cnt = 0;
     for(int i=2;i<=100000 && i<=l;i++){
        if(ok(i) && l>=i){
            l-=i;
            cnt++;
            printf("%d\n",i);
        }
     }
     printf("%d",cnt);
}
