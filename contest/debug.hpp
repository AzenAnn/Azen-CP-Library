// 本地调试输出：编译时加 -DLOCAL 才生效（run.sh 已经加了），提交到 OJ 时 debug(...) 会变成空语句。
// 用法：debug(n, a, mp);  输出到 stderr，例如  [n, a, mp] = 3, {1, 2, 3}, {(1, 2), (3, 4)}
#pragma once
#include <bits/stdc++.h>

namespace dbg {
template <class T, class = void>
struct is_container : std::false_type {};
template <class T>
struct is_container<T, std::void_t<decltype(std::begin(std::declval<T>()))>> : std::true_type {};

template <class T>
void print(const T &x);
template <class A, class B>
void print(const std::pair<A, B> &p) {
    std::cerr << '(';
    print(p.first);
    std::cerr << ", ";
    print(p.second);
    std::cerr << ')';
}
template <class... Ts>
void print(const std::tuple<Ts...> &t) {
    std::cerr << '(';
    int i = 0;
    std::apply([&](const auto &...xs) { ((std::cerr << (i++ ? ", " : ""), print(xs)), ...); }, t);
    std::cerr << ')';
}
template <class T>
void print(const T &x) {
    if constexpr (std::is_convertible_v<T, std::string_view>) {
        std::cerr << '"' << x << '"';
    } else if constexpr (std::is_same_v<T, __int128>) {
        std::cerr << (long double)x;
    } else if constexpr (is_container<T>::value) {
        std::cerr << '{';
        bool first = true;
        for (auto &&e : x) {
            if (!first) std::cerr << ", ";
            first = false;
            print(e);
        }
        std::cerr << '}';
    } else {
        std::cerr << x;
    }
}
template <class... Ts>
void out(int line, const char *names, const Ts &...xs) {
    std::cerr << "\033[33m" << line << ": [" << names << "] = ";
    int i = 0;
    ((std::cerr << (i++ ? ", " : ""), print(xs)), ...);
    std::cerr << "\033[0m\n";
}
}  // namespace dbg

#define debug(...) dbg::out(__LINE__, #__VA_ARGS__, __VA_ARGS__)
