#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

int mon[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

void solve() {
    int a, b ; cin>>a>> b;
    int ans=0;
    // 注意： 输入的a b 是完整的日期！ 
    // 你要枚举年份？ 那就截断后面四位，也就是说处以10000
    for(int i = a/10000;i<=b/10000;i++){
        if(i% 400 == 0 || (i%4==0 && i%100!=0)){
            mon[2]=29;
        }else{
            mon[2]= 28;
        }
        for(int j=1;j<=12;j++){
            int date = mon[j];
            for(int k =1;k<=date;k++){
                int cur  = i*10000 + j*100 +k;
                if(cur< a || cur> b ) continue;
                // 绝妙修改 
                string  y, m ,d;
                y =to_string(i);
                if(j<10){
                  m = "0" + to_string(j);  
                }else{
                  m = to_string(j);
                }
                if(k<10){
                  d = "0" + to_string(k);
                }else{
                  d = to_string(k);
                }
                string s =  y + m +d;
                string t= s ; reverse(t.begin(),t.end());
                if(t==s)ans++;
            }
        }
    }
    cout<<ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}