#include "../common.hpp"
#include <unistd.h>
#include "../../templates/01_basic/01_io.hpp"

int main() {
    vector<ll> v = {0, 7, -7, 123456789012345LL, LLONG_MAX, LLONG_MIN};
    for (int i = 0; i < 2000; i++) v.push_back(rnd(LLONG_MIN, LLONG_MAX));
    char path[] = "/tmp/cplib_io_XXXXXX";
    close(mkstemp(path));
    // 用 write 写到文件，检查文本和 to_string 一致；再用 read 读回来
    CHECK(freopen(path, "w", stdout));
    for (ll x : v) write(x), putchar(' ');
    __int128 big = (__int128)LLONG_MAX * 1000 + 5;
    write(big), putchar('\n');
    fflush(stdout);
    string expect;
    for (ll x : v) expect += to_string(x) + ' ';
    expect += "9223372036854775807005\n";
    ifstream fin(path);
    string got((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    CHECK(got == expect);
    CHECK(freopen(path, "r", stdin));
    for (ll x : v) {
        ll y;
        read(y);
        CHECK(x == y);
    }
    __int128 b2;
    read(b2);
    CHECK(b2 == big);
    remove(path);
    return 0;
}
