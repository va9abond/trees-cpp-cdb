#ifndef VIEW_HPP
#define VIEW_HPP


#include "laptop.hpp"
#include "myutils.hpp"



// =============================================================================
// ================================ 2_1_1 ======================================
// =============================================================================
template <class Iter_t>
inline void print_insertion_status (Iter_t iter, bool status) {
    using std::cout;

    cout << "Insertion of "; cout.width(2); cout << iter->second.id;
    cout << (status ? " succeeded\n" : " failed\n");
}


inline decltype(auto) create_laptop_map (int count) {
    std::vector<laptop_key> keys;
    std::vector<laptop>     laptops;

    std::map<laptop_key, laptop> laptop_map;

    for (int i = 1; i <= count; ++i) {
        laptop_key key (
                std::string("Factory " + std::to_string(i)),
                std::string("Model " + std::to_string(i))
        );
        laptop lap;

        keys.push_back(key); laptops.push_back(lap);

        const auto [iter, status] = laptop_map.insert({key,lap});
        print_insertion_status(iter, status);
    }
    return laptop_map;
}


inline void task2_1_1_presentation (int count) {
    msl::print(create_laptop_map(count));
}
// =============================================================================
// ================================ 2_1_2 ======================================
// =============================================================================

































#endif // VIEW_HPP
