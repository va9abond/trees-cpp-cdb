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


inline decltype(auto) create_laptop_map (int count, bool log_status = false) {
    std::vector<laptop_key> keys;
    std::vector<laptop>     laptops;

    std::map<laptop_key, laptop> laptop_map;

    for (int i = 1; i <= count; ++i) {
        laptop lap;
        laptop_key key (
                std::string("Factory " + std::to_string(i)),
                std::string("Model " + std::to_string(i))
        );

        keys.push_back(key); laptops.push_back(lap);

        const auto& [iter, status] = laptop_map.insert({key,lap});
        if (log_status) {
            print_insertion_status(iter, status);
        }
    }
    return laptop_map;
}


inline void task2_1_1_presentation (int count) {
    msl::print(create_laptop_map(count, true));
    std::cout << std::endl;
}
// =============================================================================
// ================================ 2_1_2 ======================================
// =============================================================================
// [WARNING]: It's not safe, cause I can't check is returned iterator is valid
//            (safe dereferencing) where I don't have an access to map
template <
    class Iter_t = alias::lm_const_iter
>
inline Iter_t find_by_key (const alias::laptop_map& map, const laptop_key& key) {
    Iter_t iter = map.find(key);
    return iter;
}


// [WARNING]: It's not safe, cause I can't check is returned iterator is valid
//            (safe dereferencing) where I don't have an access to map
template <
    class Iter_t = alias::lm_const_iter
>
inline Iter_t find_by_value (const alias::laptop_map& map, const laptop& value) {
    for (auto iter = map.begin(); iter != map.end(); ++iter) {
        if (iter->second == value) {
            return iter;
        }
    }
    return map.end();
}


inline void task2_1_2_presentation (const alias::laptop_map& map) {
    auto iter1 = find_by_key(map, laptop_key("Factory 5", "Model 5"));
    if (iter1 != map.end()) {
        msl::print(iter1);
    } else {
        std::cout << "Iterator is not valid\n";
    }

    auto iter2 = find_by_value(map, map.begin()->second);
    if (iter2 != map.end()) {
        msl::print(iter2);
    } else {
        std::cout << "Iterato is not valid\n";
    }
}
// =============================================================================
// ================================ 2_1_4 ======================================
// =============================================================================
template <class Pred_t>
inline alias::laptop_map filter (const alias::laptop_map& map, Pred_t pred) {
    alias::laptop_map result;

    for (const auto& [key, value] : map) {
        if (pred(value)) {
            result.insert({key, value});
        }
    }
    return result;
}

inline void task2_1_4_presentation (const alias::laptop_map& map) {
    using std::cout;
    using std::right;

    std::function<bool(const laptop&)> pred = [](const laptop& lap) {
        return lap.id > 5;
    };

    printf("\n==============================\n");
                                       // print filtered map
    cout.width(30); cout << right << "FILTER START" << "\n";
    msl::print(filter(map, pred));
    cout.width(30); cout << right << "FILTER END" << "\n";
    printf("==============================\n");
}
// =============================================================================
// ================================ 2_1_5 ======================================
// =============================================================================
template <
    class Iter_t = alias::lm_const_iter
>
inline Iter_t insert (
        alias::laptop_map& map,
        const laptop_key& key,
        const laptop& value
    ) {

    const auto& [iter, success] = map.insert({key, value});
    if (!success) {
        throw std::runtime_error("The element with the passed key already exists");
    }
    std::cout << "Insertion succeeded\n";
    return iter;
}


inline void task2_1_5_presentation (alias::laptop_map& map) {
    insert(map, {"Factory 5", "Model 5"}, laptop());
}
// =============================================================================
// ================================ 2_1_6 ======================================
// =============================================================================





// =============================================================================
// ================================ 2_1_3 ======================================
// =============================================================================




// =============================================================================
// ================================ 2_1_3 ======================================
// =============================================================================



// =============================================================================
// ================================ 2_1_3 ======================================
// =============================================================================


#endif // VIEW_HPP
