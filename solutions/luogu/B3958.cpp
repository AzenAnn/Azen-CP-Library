#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = (1LL << 62);

void solve() {
    int t; cin>>t;
    while(t--){
        string  a, b ; cin>>a>>b;
        int n = a.size() , m = b.size();
        
        if(n==m){
            int cnt=0;
            for(int i =0;i<n;i++){
                if(a[i] != b[i] ){
                    cnt ++;
                }
            }
            if(cnt ==1 ||cnt ==0){
                cout<<"similar\n";
            }else{
                cout<<"not similar\n";
            }
        }else if (abs(n-m) == 1){
            if(n>m){
                swap(a,b);
            }
                int  i =0;
                while(i<min(m,n) && a[i] == b[i]){
                    i++;
                }
                if(b.substr(i+1) == a.substr(i)){
                    cout<<"similar\n";
                }else{
                    cout<<"not similar\n";
                }
        }else{
            cout<<"not similar\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}