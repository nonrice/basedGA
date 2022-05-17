#include <iostream>
#include <array>
#include <cmath>

#include "train.cpp"

#define ld long double

class Model {
    public:
    static constexpr ld data[][2] = {
        {-10.0, -12.0},
        {-4.3, -19.353},
        {-2.9, -18.177},
        {1.0, -8.7},
        {3.7, 3.207}
    };
    
    static ld quadeq_mse(const std::array<ld, 3>& params){
        ld error = 0;
        for (const ld* pt : data){
            ld expected = (
                params[0] * pt[0]*pt[0] +
                params[1] * pt[0] + 
                params[2]
            );
            error += std::abs((pt[1]-expected) * (pt[1]-expected));
        }
        return error / (sizeof(data) / (sizeof(ld)*2));
    }
};

int main(){
    auto fit = sm::train<3>(
        std::function(Model::quadeq_mse),
        1000,
        1000,
        0.5
    );

    std::cout << "Lowest MSE: " << Model::quadeq_mse(fit) << '\n';
    std::cout << "Regression result:\n";
    std::cout << "f(x) = " << fit[0] << "x^2 + " << fit[1] << "x + " << fit[2];
}
