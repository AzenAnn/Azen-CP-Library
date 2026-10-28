#include <bits/stdc++.h>
using namespace std;
using ll=long long;

bool check(int n){
    int cnt= 1;
    while(n!=0){
        int r =n %10;
        if(r%2 != cnt%2){
            return false;
        }
        n/=10;
        cnt++;
    }
    return true;
}

void solve() {
    int n; cin>> n;
    int cnt = 0;
    for(int i=1;i<=n;i++){
        if(check(i))cnt++;
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