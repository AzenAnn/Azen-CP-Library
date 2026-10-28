#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int num(char c){
    if(islower(c)){
        return c - 'a' +1;
    }else{
        return -(int)c;
    }
}

void solve() {
    int n ; string s; cin>> n>>s;
    ll sum = 0;
    for(auto c:s){
        if(c>='a' && c<='z') sum += c-'a'+1;
        else sum -= c;
    }
    cout<<sum;

    // int n;  cin>> n
    // string s; cin>> s;
    // ll sum = 0;
    // for(auto c:s){
    //     sum += num(c);
    // }
    // cout<< sum<<'\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   
    solve();
    
    return 0;
}