#include <array>
#include <functional>
#include <utility>
#include <cstdlib>
#include <limits>
#include <thread>
#include <vector>

#include "based_ga.hpp"

#define ull unsigned long long
#define ld long double 

template <std::size_t param_c>
std::array<ld, param_c> based_ga::train(
    std::function<ld(const std::array<ld, param_c>&)> eval,
    ull gen_c,
    ull child_c,
    ld var,
    ull thread_c // defaults to 1
){
    std::vector<std::pair<ld, std::array<ld, param_c>>> results(thread_c, {std::numeric_limits<long double>::max(), {0}});
    std::vector<std::thread> threads;
    std::array<ld, param_c> cur_parent = {0};

    while (gen_c--){
        
        for (ull idx=0; idx<thread_c; ++idx){
            threads.emplace_back([&](ull idx) {

                std::array<ld, param_c> cur = {0};

                for (ull n=0; n < child_c/thread_c; ++n){
                    for (std::size_t i=0; i<param_c; ++i)
                        cur[i] = cur_parent[i] - var + (((ld)std::rand())/RAND_MAX * 2 * var);
                        
                    ld score = eval(cur);
                    if (score < results[idx].first){
                        results[idx].first = score;
                        results[idx].second = cur;
                    }
                }

            }, idx);
        }

        for (std::thread& t : threads)
            if (t.joinable()) t.join();
        threads.clear();

        // first result holds the running min of all results
        for (auto& res : results){
            if (res.first < results[0].first)
                results[0] = res;
        }

        cur_parent = results[0].second;
    }

    return results[0].second;
}
