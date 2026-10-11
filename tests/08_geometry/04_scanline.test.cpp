#include "../common.hpp"
#include "../../templates/08_geometry/04_scanline.hpp"

int main() {
    for (int it = 0; it < 2000; it++) {
        int n = rnd(0, 8);
        vector<array<ll, 4>> rs;
        for (int i = 0; i < n; i++) {
            ll x1 = rnd(-10, 9), x2 = rnd(x1 + 1, 10), y1 = rnd(-10, 9), y2 = rnd(y1 + 1, 10);
            rs.push_back({x1, y1, x2, y2});
        }
        ll cells = 0;   // 暴力：数被覆盖的单位格子
        for (ll x = -10; x < 10; x++)
            for (ll y = -10; y < 10; y++) {
                bool cov = false;
                for (auto &r : rs) cov |= r[0] <= x && x < r[2] && r[1] <= y && y < r[3];
                cells += cov;
            }
        CHECK(rect_union_area(rs) == cells);
    }
    CHECK(rect_union_area({{0, 0, 1000000000, 1000000000}, {0, 0, 1000000000, 1000000000}}) == 1000000000000000000LL);
    return 0;
}
