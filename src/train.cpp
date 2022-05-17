#include <array>
#include <functional>
#include <utility>
#include <cstdlib>
#include <limits>

#include "train.hpp"

#define ull unsigned long long
#define ld long double 

template <std::size_t param_c>
std::array<ld, param_c> sm::train(
    std::function<ld(const std::array<ld, param_c>&)> eval,
    ull gen_c,
    ull child_c,
    ld var
){
    std::pair<ld, std::array<ld, param_c>> best = {std::numeric_limits<long double>::max(), {0}};
    std::array<ld, param_c> cur_parent = {0};
    std::array<ld, param_c> cur = {0};

    while (gen_c--){
        for (ull n=0; n<child_c; ++n){
            for (std::size_t i=0; i<param_c; ++i)
                cur[i] = cur_parent[i] - var + (((ld)std::rand())/RAND_MAX * 2 * var);
                
            ld score = eval(cur);
            if (score < best.first){
                best.first = score;
                best.second = cur;
            }
        }
        cur_parent = best.second;
    }

    return best.second;
}
