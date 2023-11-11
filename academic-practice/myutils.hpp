#ifndef MYUTILS_CPP
#define MYUTILS_CPP

#include <iostream>
#include <random>
#include <vector>
#include <stdint.h>

namespace alias {
    template <class T> using v = std::vector<T>;
}

namespace msl {

    template <class T>
    decltype(auto) rand (const T lower_bound, const T upper_bound, uint8_t amount = 1) {}

    template<>
    inline decltype(auto) rand (const int lower_bound, const int upper_bound, uint8_t amount) {
        std::default_random_engine eng;
        std::uniform_int_distribution<int> unfdist(lower_bound, upper_bound);

        std::vector<int> rands;
        for (uint8_t ui {0}; ui < amount; ++ui) {
            rands.push_back(unfdist(eng));
        }

        return rands;
    }

    template<>
    inline decltype(auto) rand (const double lower_bound, const double upper_bound, uint8_t amount) {
        std::default_random_engine eng;
        std::uniform_real_distribution<double> unfdist(lower_bound, upper_bound);

        std::vector<double> rands;
        for (uint8_t ui {0}; ui < amount; ++ui) {
            rands.push_back(unfdist(eng));
        }

        return rands;
    }

    template <
        template <class... > class container_type,
        class value_type
    >
    void print (const container_type<value_type>& cont) {
        printf("\n{ ");

        auto it = cont.begin();
        while (it != cont.end()) {
            std::cout << *(it++) << " ";
        }

        printf("};\n");
    }
}



#endif // MYUTILS_CPP
