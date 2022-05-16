#include <array>
#include <functional>
#include <utility>
#include <cstdlib>

#include "Population.hpp"

template <std::size_t param_c>
std::pair<ld, std::array<ld, param_c>> sm::train(
    std::function<ld(const std::array<ld, param_c>&)> eval,
    ll gen_c,
    ll child_c,
    ld var,
    const std::array<ld, param_c> init
){
    std::pair<ld, std::array<ld, param_c>> best = {0, {0}};
    std::pair<ld, std::array<ld, param_c>> cur = {0, {0}};
    std::pair<ld, std::array<ld, param_c>> cur_parent = {0, {0}};

    while (gen_c--){
        cur_parent = best;
        for (int i=0; i<child_c; ++i){
            for (std::size_t p=0; p<param_c; ++p){
                cur.second[p] = cur_parent.second[p] + var/2 - (var * (std::rand()/RAND_MAX));
            }
            cur.first = eval(cur.second);
            if (cur.first > best.first){
                best = cur;
            }
        }
    }

    return best;
}
