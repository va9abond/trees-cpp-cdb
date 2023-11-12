#ifndef MYUTILS_CPP
#define MYUTILS_CPP


#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <random>
#include <format>
#include <algorithm>


namespace alias {
    template <class T> using v = std::vector<T>;
}


namespace msl {

    template <class Num_t, typename Gen_t = std::mt19937>
    Num_t random (const Num_t lower_bound, const Num_t upper_bound) {
        static Gen_t generator(std::random_device{}());

        using unfdist_type = typename std::conditional <
            std::is_integral<Num_t>::value,
            std::uniform_int_distribution<Num_t>,
            std::uniform_real_distribution<Num_t>
        >::type;

        static unfdist_type unfdist;
        return unfdist(
                generator,
                typename unfdist_type::param_type{lower_bound, upper_bound});
    }


    template <class T>
    decltype(auto) rand (const T lower_bound, const T upper_bound, uint8_t amount = 1) {}

    template<>
    inline decltype(auto) rand (const int lower_bound, const int upper_bound, uint8_t amount) {
        static std::default_random_engine eng;
        static std::uniform_int_distribution<int> unfdist(lower_bound, upper_bound);

        std::vector<int> rands;
        for (uint8_t ui {0}; ui < amount; ++ui) {
            rands.push_back(unfdist(eng));
        }

        return rands;
    }

    template<>
    inline decltype(auto) rand (const double lower_bound, const double upper_bound, uint8_t amount) {
        static std::default_random_engine eng;
        static std::uniform_real_distribution<double> unfdist(lower_bound, upper_bound);

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
