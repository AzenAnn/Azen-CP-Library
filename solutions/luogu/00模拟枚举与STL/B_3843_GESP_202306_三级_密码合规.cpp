#include <bits/stdc++.h>
using namespace std;
using ll=long long;

bool check1(string s){
    for(auto c: s){
        if(!isalnum(c) && c!='!' && c!='@' && c!='#' && c!='$'){
            return false; 
        }
    }
    
    if(s.size()>12 || s.length()<6)return false;
    return true; // 只判断1 、2 
}

bool check2 (string s){
    bool ok1 =false ,ok2 = false,ok3= false;
    for(auto c : s){
        if(isupper(c)){
            ok1 = true;
        }else if(islower(c)){
            ok2 = true;
        }else if(isdigit(c)){
            ok3 = true;
        }
    }
    int cnt =  ok1 + ok2  +ok3;
    bool ok4 =false;
    for(auto c: s){
        if(c=='!'|| c=='@' || c=='#' || c=='$'){
            ok4 = true;
            break;
        }
    }

    return (cnt >=2 && ok4);
}

void solve() {
    string line;
    getline(cin,line); // 读取整行


    stringstream ss(line);

    string s;
    while(getline(ss,s,',')){
        if(check1(s) && check2(s)){
            cout<<s<<"\n";
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