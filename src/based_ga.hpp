#include <array>
#include <functional>
#include <utility>
#include <cstdlib>
#include <limits>
#include <thread>
#include <vector>
#include <iostream>

#define ull unsigned long long
#define ld long double 

namespace based_ga {

template <std::size_t param_c>
inline std::array<ld, param_c> train(
    std::function<ld(const std::array<ld, param_c>&)> eval,
    ull gen_c,
    ull child_c,
    ld var,
    ull thread_c = 1
){
    std::vector<std::pair<ld, std::array<ld, param_c>>> results(thread_c, {std::numeric_limits<long double>::max(), {0}});
    std::vector<std::thread> threads;
    std::array<ld, param_c> cur_parent = {0};

    for (ull gen=1; gen<=gen_c; ++gen){
        
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

        auto bst = results.begin();
        for (auto it=results.begin()+1; it!=results.end(); ++it){
            if (it->first < bst->first)
                bst = it;
        }

        cur_parent = bst->second;

        #ifdef BASEDGA_VERBOSE
            std::cout << "[based_ga] Generation " << gen << " done; ";
            std::cout << "best=" << bst->first << '\n';
        #endif 
    }

    return cur_parent;
}

}