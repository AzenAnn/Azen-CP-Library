#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    string s;cin>> s;
    stack<char>st;
    int cnt =  0;
    int ans =  0;
    for(auto c : s){
        if(c==')'){
            if(cnt>0) {
                cnt --;
                ans ++;
            }
        }else{
            cnt++;
        }
    }
    int n =s.size();
    cout<<ans *2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}