#include <iostream>
#include <array>
#include <cmath>

#include "based_ga.hpp"

#define ld long double

class Graph {
    public:
    static std::vector<std::pair<ld, ld>> data;
    
    // Given quadratic equation ax^2 + bx + c, return the MSE when fitted to points in Graph::data
    static ld quadeq_mse(const std::array<ld, 3>& params){
        ld error = 0;
        for (const auto& pt : data){
            ld expected = (
                params[0] * pt.first*pt.first +
                params[1] * pt.first + 
                params[2]
            );
            error += std::abs((pt.second-expected) * (pt.second-expected));
        }
        return error / (sizeof(data) / (sizeof(ld)*2));
    }
};



int main(){
    Graph::data = {
        {-10.0, -11.0},
        {-4.3, -19.053},
        {-2.9, -19.177},
        {1.0, -8.2},
        {3.7, 3.607}
    };

    std::array<ld, 3> fit = based_ga::train<3>(
        std::function(Graph::quadeq_mse),
        100, // generation count
        100, // children/generation
        0.5, // max variation
        8 // thread count
    );

    std::cout << "Lowest MSE: " << Graph::quadeq_mse(fit) << '\n';
    std::cout << "Regression result:\n";
    std::cout << "f(x) = " << fit[0] << "x^2 + " << fit[1] << "x + " << fit[2] << '\n';
}
