#include <array>
#include <functional>
#include <utility>

#define ll long long
#define ld long double

namespace sm {

    template <std::size_t param_c>
    std::pair<ld, std::array<ld, param_c>> train(
        std::function<ld(const std::array<ld, param_c>&)> eval,
        ll gen_c,
        ll child_c,
        ld var,
        const std::array<ld, param_c> init
    );

};
