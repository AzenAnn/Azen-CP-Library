#include <bits/stdc++.h>
using namespace std;
using ll=long long;


int bonus(int n ){
    if(n>=1 && n<3)return 1;
    else if(n>=3 && n<7)return 2;
    else if(n>=7 && n<30)return 3;
    else if(n>=30 && n<120)return 4;
    else if(n>=120 && n<365)return 5;
    else if(n>=365) return 6;
    
}


void solve() {
    int n;cin>>n;
    int cons = 0 ,k = 0 , sum = 0;
    bool flag =false;
    while(n--){
        int x; cin>> x;
        if(x==0){
            flag =false;
            k++;
        }else{
            flag =true;
            if(k>=11){
                cons = 0;
            }else if(k>0){// 数据范围和溢出
                cons = max(0,cons-(1<< (k - 1)));
                if(cons<=0) cons =0;
            }
            k=0;        
            cons++;
            sum +=  bonus(cons);
        }
    }        
    cout<<sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   
    solve();
    
    return 0;
}