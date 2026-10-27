#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

char s[110][110];
int ans[110][110];


void solve() {
    int n , m ;cin>> n>>m;
    for(int i =1; i <=n;i++){
        for(int j =1; j<=m;j ++){
            cin>>s[i][j];
        }
    }

    auto check = [&] (int x,int y ){
        if(x< 1 ||x> n ||y<1 ||y >m) return 0;
        if(s[i][j] == 'X') return 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}