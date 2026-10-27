#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

/*
做两次前缀和，一个是左往右，一个是从右往左
分别记录的就是起始点到终点的最小费用

注意到一段距离可以拆成若干段普通距离之和
*/

void solve() {
    int t;  cin>> t;
    while(t--){
        ll n; cin >> n ;
        vector<ll>a(n+2); //为什么要开n+2？
        for(int i=1;i<=n;i++) cin>>a[i];
        auto check =  [&] (ll x){
            if( x == 1 ) return 2LL; //  lanmuda表达式的返回类型错误太夸张了
            if( x == n ) return n-1;
            return (a[x]-a[x-1] < a[x+1]-a[x]) ?  x-1 :x+1;
        };
        vector<ll>r(n+2,0), l(n+1,0);
        for(int i=2;i<=n;i++){
            r[i]  = r[i-1] + ((check(i-1) == i) ? 1 : a[i]-a[i-1]);
            l[i]  = l[i-1] + ((check(i) == i-1) ? 1: a[i] -a[i-1]);
            //  三目运算符的 运算顺序
        }
        ll m ;cin>> m;
        while(m--){
            ll x,y ;cin>> x >>y;
            cout<< (( x < y) ? r[y] -r[x] : l[x] - l[y])<<'\n';
        }// cout中的 括号的三目运算符
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}