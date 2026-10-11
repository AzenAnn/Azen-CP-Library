#include "../common.hpp"
#include "../../templates/05_math/12_game.hpp"

int main() {
    // Nim：三堆，暴力 DP
    const int N = 7;
    static bool win[N + 1][N + 1][N + 1];
    for (int s = 0; s <= 3 * N; s++)
        for (int a = 0; a <= N; a++)
            for (int b = 0; b <= N; b++) {
                int c = s - a - b;
                if (c < 0 || c > N) continue;
                bool w = false;
                for (int k = 1; k <= a; k++) w |= !win[a - k][b][c];
                for (int k = 1; k <= b; k++) w |= !win[a][b - k][c];
                for (int k = 1; k <= c; k++) w |= !win[a][b][c - k];
                win[a][b][c] = w;
                CHECK(nim_first_wins({a, b, c}) == w);
            }
    // 巴什博弈
    for (int m = 1; m <= 10; m++) {
        vector<bool> w(60, false);
        for (int n = 1; n < 60; n++)
            for (int k = 1; k <= m && k <= n; k++) w[n] = w[n] | !w[n - k];
        for (int n = 0; n < 60; n++) CHECK(bash_first_wins(n, m) == w[n]);
    }
    // 威佐夫博弈
    const int W = 60;
    vector<vector<bool>> ww(W, vector<bool>(W, false));
    for (int a = 0; a < W; a++)
        for (int b = 0; b < W; b++) {
            bool w = false;
            for (int k = 1; k <= a; k++) w = w || !ww[a - k][b];
            for (int k = 1; k <= b; k++) w = w || !ww[a][b - k];
            for (int k = 1; k <= min(a, b); k++) w = w || !ww[a - k][b - k];
            ww[a][b] = w;
            CHECK(wythoff_first_wins(a, b) == w);
        }
    // SG：减法游戏，SG = 0 ⇔ 必败
    vector<int> S = {1, 3, 4};
    auto sg = sg_subtraction(100, S);
    vector<bool> w(101, false);
    for (int x = 1; x <= 100; x++)
        for (int s : S)
            if (s <= x && !w[x - s]) w[x] = true;
    for (int x = 0; x <= 100; x++) CHECK((sg[x] != 0) == w[x]);
    CHECK(mex({0, 1, 3, 1}) == 2 && mex({}) == 0 && mex({1, 2}) == 0);
    return 0;
}
