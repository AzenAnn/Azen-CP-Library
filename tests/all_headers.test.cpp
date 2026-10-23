// 总头文件应能独立引入，且重复引入不会产生重复定义。
#include "../templates/all.hpp"
#include "../templates/all.hpp"
#include "common.hpp"

int main() {
    // 同时调用不同专题，检查聚合引入后的接口可用性。
    Fenwick f(3);
    f.add(1, 3000000000LL);
    f.add(3, -2);
    CHECK(f.sum(1, 3) == 2999999998LL);

    DSU d(3);
    CHECK(d.merge(0, 2));
    CHECK(d.same(0, 2) && !d.same(0, 1));
    CHECK(d.size(0) == 2);

    mint x = 5;
    CHECK(x * 3 - 1 == mint(14));
    CHECK(kmp_search("ababa", "aba") == vector<int>({0, 2}));
    return 0;
}
