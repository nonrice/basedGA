#include <iostream>
#include <array>
#include <cmath>

#define BASEDGA_VERBOSE 1
#include "based_ga.hpp"

#define ld long double

// Given 3 parameters (a, b, c) for quadratic equation ax^2 + bx + c,
// return the mse when fitted to the vector of 2d points data
ld quadratic_eq_mse(
    const std::array<ld, 3>& params,
    const std::vector<std::pair<ld, ld>>& data
){
    ld error = 0;
    for (const auto& pt : data){
        ld expected = (
            params[0] * pt.first*pt.first +
            params[1] * pt.first + 
            params[2]
        );
        error += std::abs((pt.second-expected) * (pt.second-expected));
    }
    return error / data.size();
}

int main(){
    std::vector<std::pair<ld, ld>> data = {
        {-10.0, -11.0},
        {-4.3, -19.053},
        {-2.9, -19.177},
        {1.0, -8.2},
        {3.7, 3.607}
    };

    std::array<ld, 3> fit = based_ga::train<3>(
        std::bind(quadratic_eq_mse, std::placeholders::_1, data),
        100,
        10000,
        0.5,
        8
    );

    std::cout << "Lowest MSE: " << quadratic_eq_mse(fit, data) << '\n';
    std::cout << "Regression result:\n";
    std::cout << "f(x) = " << fit[0] << "x^2 + " << fit[1] << "x + " << fit[2] << '\n';
}
