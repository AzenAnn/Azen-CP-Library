#include <bits/stdc++.h>
using namespace std;
using ll=long long;

void solve() {
    int n ;cin>> n;
    while(n--){
        string s; cin>> s;
        bool ok =false;
        //s.size() 一定会返回无符号整数，会发生无符号整数下一
        // s.size() ==1 的时候 1-2 发生无符号整数往下溢出
        // 
        int n = s.size();
        for(int i=2;i<=n-2;i++){
            string pre = s.substr(0,i);
            string nx  = s.substr(i);
            string pr = pre; reverse(pr.begin(),pr.end());
            string nr = nx; reverse(nr.begin(),nr.end());
            if(pr == pre && nr==nx){
                cout<<"Yes\n";
                ok = true;
                break;
            }
        }
        if(!ok){
            cout<<"No\n";
        }
    }    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   
    solve();
    
    return 0;
}