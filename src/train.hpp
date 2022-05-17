#include <array>
#include <functional>
#include <utility>

#define ull unsigned long long
#define ld long double 

namespace sm {

template <std::size_t param_c>
std::array<ld, param_c> train(
    std::function<ld(const std::array<ld, param_c>&)> eval,
    ull gen_c,
    ull child_c,
    ld var
);

};
