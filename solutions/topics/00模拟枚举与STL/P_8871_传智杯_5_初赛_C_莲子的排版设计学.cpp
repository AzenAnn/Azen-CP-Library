#include <bits/stdc++.h>
using namespace std;
using ll=long long;

void solve() {
    vector<string>s;
    s.push_back("");
    string line;
    while(getline(cin,line)){
        s.push_back(line);
    } 
    int m =  s.size() -1;
    int w = to_string(m).size();

    for(int i=1;i<s.size();i++){
        cout<<setw(w)<<i<<" "<<s[i]<<'\n';
    }      
    return ;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   
    solve();
    
    return 0;
}