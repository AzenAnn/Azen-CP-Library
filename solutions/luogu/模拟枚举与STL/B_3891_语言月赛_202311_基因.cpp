/*
    学习使用字符串的find函数
    尤其是代码里面的 first find of
*/



// gpt优化代码
// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;

// // 返回 DNA 碱基对应的互补碱基
// char complement(char c) {
//     switch (c) {
//         case 'A': return 'T';
//         case 'T': return 'A';
//         case 'C': return 'G';
//         case 'G': return 'C';
//         default:  return '\0';
//     }
// }

// void solve() {
//     int t;
//     cin >> t;

//     while (t--) {
//         int n;
//         string s;
//         cin >> n >> s;

//         // 检查是否包含非法字符
//         if (s.find_first_not_of("ATCG") != string::npos) {
//             cout << 0 << '\n';
//             continue;
//         }

//         ll cnt = 0;

//         // 只需要枚举前半部分
//         for (int i = 0; i < n / 2; ++i) {
//             if (complement(s[i]) == s[n - 1 - i]) {
//                 cnt += n + 1LL;
//             }
//         }

//         cout << cnt << '\n';
//     }
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     solve();
//     return 0;
// }


#include <bits/stdc++.h>
using namespace std;
using ll=long long;

bool check (char s,char t){
    if(s== 'A' && t=='T'
    || s=='T'  && t=='A'
    || s=='C' && t=='G'
    || s=='G' && t=='C'
    ){
        return true;
    }
    return false;
}

bool ok (char c){
    if(c!= 'A' && c!='T' && c!='C' && c!='G'){
        return false;
    }
    return true;
} 
// 有点冗杂？ 如何优化？ 
void solve() {
    int t ;cin>> t;
    while(t--){
        int n ; string s; cin>> n>> s;
        string r = s;
        reverse(r.begin(),r.end());
        ll  cnt =0; // 计数器要有开ll 的好习惯！
        for(int i=0;i<n;i++){
            if(!ok(s[i])) {
                cnt = 0;
                break;
            }
            
            if(check(s[i] ,r[i])){
                cnt += i+1;
            }
        }
        cout<<cnt<<'\n';
    }       
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   
    solve();
    
    return 0;
}