#include <bits/stdc++.h>
using namespace std;
using ll=long long;

string sm[4][5]={
    ".....",".***.",".***.",".***.",".....",
    "****.","****.","****.","****.","****.",
    ".....","****.",".....",".****",".....",
    ".....","****.",".....","****.","....."
};

void solve() {
    string s; cin>> s;
    for(int r= 0;r<5;r++){ // 有五行
        for(auto c:s){
            cout<<sm[c-'0'][r];
        }
        cout<<'\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   
    solve();
    
    return 0;
}
