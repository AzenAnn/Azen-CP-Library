#include <bits/stdc++.h>
using namespace std;
using ll=long long;

void solve() {
    int n ; cin>> n;
    int cnt = 0 ;
    int a[3];
    while(n!= 495){
        a[0] = n % 10;
        a[1] = n/10 %10;
        a[2] = n/100;
        sort(a,a+3);
        n =  a[2]*100 +a[1]*10 + a[0] -(a[0]*100+a[1]*10+a[2]);
        cnt++; 
    }
    cout<<cnt<<'\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   
    solve();
    
    return 0;
}