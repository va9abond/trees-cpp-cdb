#ifndef VIEW_HPP
#define VIEW_HPP


#include "laptop.hpp"
#include "myutils.hpp"
#include "avltree.hpp"
#include "heap.hpp"


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
    using std::cout;
    using std::right;
    printf("\n##############################\n");
    std::cout.width(30); cout << right << "@ task 2.1.1" << "\n";


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
    using std::cout;
    using std::right;
    printf("\n##############################\n");
    std::cout.width(30); cout << right << "@ task 2.1.2" << "\n";


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
    printf("\n##############################\n");
    std::cout.width(30); cout << right << "@ task 2.1.4" << "\n";


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
    msl::print(iter);

    return iter;
}


inline void task2_1_5_presentation (alias::laptop_map& map) {
    using std::cout;
    using std::right;
    printf("\n##############################\n");
    std::cout.width(30); cout << right << "@ task 2.1.5" << "\n";


    // insert(map, {"Factory 5", "Model 5"}, laptop());
    insert(map, {"Factory 287", "Model 287"}, laptop());
}
// =============================================================================
// ================================ 2_1_6 ======================================
// =============================================================================
inline std::vector<laptop> unique_values (const alias::laptop_map& map) {
    std::set<laptop> set;

    for (const auto& [key, value] : map) {
        set.emplace(value);
    }

    return std::vector<laptop>(set.begin(), set.end());
}


inline void task2_1_6_presentation (const alias::laptop_map& map) {
    using std::cout;
    using std::right;
    printf("\n##############################\n");
    std::cout.width(30); cout << right << "@ task 2.1.6" << "\n";


    msl::print(unique_values(map));
}
// =============================================================================
// ================================ 2_2_1 ======================================
// =============================================================================
inline void task2_2_1_presentation () {
    using std::cout;
    using std::right;
    printf("\n##############################\n");
    std::cout.width(30); cout << right << "@ task 2.2.1" << "\n";


    // create laptop map
    //               ---
    alias::laptop_map map = create_laptop_map(10, false);

    // move map [key, value] into multimap
    alias::laptop_multimap multimap(map.begin(), map.end());

    // add some existing keys
    multimap.emplace(laptop_key("Factory 1", "Model 1"), laptop());
    multimap.emplace(laptop_key("Factory 1", "Model 1"), laptop());
    // and some more
    multimap.emplace(laptop_key("Factory 2", "Model 2"), laptop());
    multimap.emplace(laptop_key("Factory 2", "Model 2"), laptop());

    msl::print(multimap);
}
// =============================================================================
// ================================ 2_2_2 ======================================
// =============================================================================
template <
    class Iter_t = alias::lmm_const_iter
>
// [WARNING]: There are no guarantees that First and Last belog to the same
//            container
inline std::vector<Iter_t> find_by_key (
        Iter_t First, Iter_t Last,
        const laptop_key& key
    ) {
    std::vector<Iter_t> iters;
    for (auto iter = First; iter != Last; ++iter) {
        if (!(iter->first < key) && !(key < iter->first)) {
            iters.push_back(iter);
        }
    }
    return iters;
}


template <
    class Iter_t = alias::lmm_const_iter
>
// [WARNING]: There are no guarantees that First and Last belog to the same
//            container
inline std::vector<Iter_t> find_by_value (
        Iter_t First, Iter_t Last,
        const laptop& value
        ) {
    std::vector<Iter_t> iters;
    for (auto iter = First; iter != Last; ++iter) {
        if (iter->second == value) {
            iters.push_back(iter);
        }
    }
    return iters;
}


inline void task2_2_2_presentation (const alias::laptop_multimap& mmap) {
    using std::cout;
    using std::right;
    printf("\n##############################\n");
    std::cout.width(30); cout << right << "@ task 2.2.2" << "\n";


    auto iters1 = find_by_key(mmap.begin(), mmap.end(), laptop_key("Factory 1", "Model 1"));
    if (iters1.size() > 0) {
        std::cout << "{";
        for (const auto& iter : iters1) {
            std::cout << " " << iter->second.id;
        }
        std::cout << " }\n";
    } else {
        std::cout << "There is no value with passed key\n";
    }

    auto iters2 = find_by_value(mmap.begin(), mmap.end(), mmap.begin()->second);
    if (iters2.size() > 0) {
        std::cout << "{";
        for (const auto& iter : iters2) {
            std::cout << " " << iter->second.id;
        }
        std::cout << " }\n";
    } else {
        std::cout << "There is no passed value";
    }
}
// =============================================================================
// ================================ 2_2_4 ======================================
// =============================================================================
template <
    class Iter_t = alias::lmm_const_iter,
    class Pred_t
>
inline alias::laptop_multimap filter (Iter_t First, Iter_t Last, Pred_t Pred) {
    alias::laptop_multimap result;

    for (auto iter = First; iter != Last; ++iter) {
        if (Pred(iter->second)) {
            result.insert({iter->first, iter->second});
        }
    }
    return result;
}


inline void task2_2_4_presentation (const alias::laptop_multimap& mmap) {
    using std::cout;
    using std::right;
    printf("\n##############################\n");
    std::cout.width(30); cout << right << "@ task 2.2.4" << "\n";

    std::function<bool(const laptop&)> pred = [](const laptop& lap) {
        return lap.id % 13 < 5;
    };

    printf("\n==============================\n");
                                       // print filtered map
    cout.width(30); cout << right << "FILTER START" << "\n";
    msl::print(filter(mmap.begin(), mmap.end(), pred));
    cout.width(30); cout << right << "FILTER END" << "\n";
    printf("==============================\n");
}
// =============================================================================
// ================================ 2_2_7 ======================================
// =============================================================================
template <
    class Iter_t = alias::lmm_const_iter
>
inline std::vector<laptop> filter_by_key (
        Iter_t First, Iter_t Last,
        const laptop_key& key
    ) {
    std::vector<laptop> laptops;
    for (auto iter = First; iter != Last; ++iter) {
        if (!(iter->first < key) && !(key < iter->first)) {
            laptops.push_back(iter->second);
        }
    }
    return laptops;
}


inline void task2_2_7_presentation (
    const alias::laptop_multimap& mmap,
    const laptop_key& key
    ) {
    using std::cout;
    using std::right;
    printf("\n##############################\n");
    std::cout.width(30); cout << right << "@ task 2.2.4" << "\n";


    std::vector<laptop> laptops = filter_by_key(mmap.begin(), mmap.end(), key);
    msl::print(laptops);
}
// =============================================================================
// ================================= 2_3 =======================================
// =============================================================================
inline void task2_3_presentation (int count) {
    using std::cout;
    using std::right;
    printf("\n##############################\n");
    std::cout.width(30); cout << right << "@ task 2.3" << "\n";


    msl::print(create_laptop_prq(count));
}
// =============================================================================
// ================================ 2_4_1 ======================================
// =============================================================================
template <
    class Iter_t = alias::tr_const_iter,
    class Kty
>
inline Iter_t find_by_key (const avltree<int, int>& tree, const Kty& key) {
    return tree.find(key);
}

template <
    class Iter_t = alias::tr_const_iter
>
inline Iter_t find_by_value (const avltree<int, int>& tree, const int Val) {
    auto iter = tree.begin();
    while (iter != tree.end()) {
        if (iter->second == Val) {
            break;
        }
        ++iter;
    }
    return iter;
}

inline void task2_4presentation() {
    using std::cout;
    using std::right;
    printf("\n##############################\n");
    std::cout.width(30); cout << right << "@ task 2.4" << "\n";
    printf("Output tree by iterators\n");

    // Use <int, int> not <laptop_key, laptop> to
    // make size of output smaller
    avltree<int, int> tree;
    tree.emplace(51,  12);
    tree.emplace(924, 320);
    tree.emplace(3,   80);
    tree.emplace(23,  91);
    tree.emplace(12,  15);
    tree.emplace(83,  42);
    tree.emplace(13,  13);
    tree.emplace(1,   4);
    tree.emplace(99,  34);
    tree.emplace(99, 233);
    tree.emplace(100, 14);
    tree.emplace(1000, 7);
    tree.emplace(0, 32);

    tree.print_tree();

    std::cout << "\n";
    std::cout.width(30); cout << right << "Ascending order" << "\n";

    std::cout.width(30); cout << right << "{x, y}, z" << "\n";
    std::cout.width(30); cout << right << "x - key" << "\n";
    std::cout.width(30); cout << right << "y - value" << "\n";
    std::cout.width(30); cout << right << "z - node height" << "\n";

    auto iter = tree.begin();
    while (iter != tree.end()) {
        printf("{%d, %d}, h = %u\n", iter->first, (*iter).second, iter.Myptr->Height);
        ++iter;
    }

    std::cout.width(30); cout << right << "Descending order" << "\n";

    while (iter != tree.begin()) {
        --iter;
        printf("{%d, %d}, h = %u\n", iter->first, (*iter).second, iter.Myptr->Height);
    }


    std::cout.width(30); cout << right << "max(), min()\n" << "\n";
    iter = tree.max();
    msl::print_tree_iter(iter);
    iter = tree.min();
    msl::print_tree_iter(iter);


    std::cout.width(30); cout << right << "find by key, key = 3" << "\n";
    std::cout << "finded iterator: ";
    auto find_iter = find_by_key(tree, 3);
    if (find_iter != tree.end()) { msl::print_tree_iter(find_iter); }
    std::cout << "\n";

    std::cout.width(30); cout << right << "find by value, value = 42" << "\n";
    std::cout << "finded iterator: ";
    find_iter = find_by_value(tree, 42);
    if (find_iter != tree.end()) { msl::print_tree_iter(find_iter); }
    std::cout << "\n";


    std::cout.width(30); cout << right << "Erasing" << "\n";

    iter = tree.begin();
    while (iter != tree.end()) {
        printf("ERASE: %d\n", iter->first);
        const auto& [it, success] = tree.erase(iter->first);
        if (success == false) {
            printf("\nSTOP STOP STOP STOP STOP STOP STOP STOP STOP\n");
        }
        tree.print_tree();
        printf("\n\n");
        iter = it;
    }
}


inline void task2_5presentation() {
    using std::cout;
    using std::right;
    printf("\n##############################\n");
    std::cout.width(30); cout << right << "@ task 2.5" << "\n";
    printf("Output tree by iterators\n");

    // Use <int, int> not <laptop_key, laptop> to
    // make size of output smaller
    avltree<int, int> tree;
    tree.emplace(51,  12);
    tree.emplace(51,  24);
    tree.emplace(1,   4);
    tree.emplace(1,   8);
    tree.emplace(99,  34);
    tree.emplace(99, 233);
    tree.emplace(0, 32);

    tree.print_tree();

    // msl::print_tree_iter(tree[4]); // throw exception
    msl::print_tree_iter(tree[51]);
    msl::print_tree_iter(tree[0]);
    msl::print_tree_iter(tree[1]);
}
// =============================================================================
// ================================ 2_6 ======================================
// =============================================================================
inline void task2_6_presentation() {
    using std::cout;
    using std::right;
    printf("\n##############################\n");
    std::cout.width(30); cout << right << "@ task 2.6" << "\n";


    heap<int> myheap;

    myheap.push(13);
    myheap.push(11);
    myheap.push(81);
    myheap.push(99);
    myheap.emplace(41);
    myheap.emplace(23);
    myheap.emplace(83);
    myheap.emplace(12);
    myheap.emplace(88);
    myheap.emplace(101);
    myheap.emplace(10);
    myheap.emplace(51);
    myheap.emplace(42);
    myheap.emplace(67);
    myheap.emplace(74);
    myheap.emplace(24);
    myheap.emplace(96);

    std::cout << "\n";
    std::cout.width(30); cout << right << "Constructing heap";
    msl::print_heap(myheap);

    std::cout << "\n";
    std::cout.width(30); cout << right << "Pop from the top" << "\n\n";

    std::cout.width(30); cout << right << "Pop 1";
    myheap.pop();
    msl::print_heap(myheap);

    std::cout.width(30); cout << right << "Pop 2";
    myheap.pop();
    msl::print_heap(myheap);

    std::cout.width(30); cout << right << "Pop 3";
    myheap.pop();
    msl::print_heap(myheap);

    std::cout.width(30); cout << right << "Pop 4";
    myheap.pop();
    msl::print_heap(myheap);


    std::cout << "\n";

    std::cout.width(30); cout << right << "Remove by value" << "\n\n";
    std::cout.width(30); cout << right << "Remove 83";
    myheap.remove_val(83);
    msl::print_heap(myheap);

    std::cout.width(30); cout << right << "Remove 2";
    myheap.remove_val(2);
    msl::print_heap(myheap);

    std::cout.width(30); cout << right << "Remove 10";
    myheap.remove_val(10);
    msl::print_heap(myheap);

    std::cout.width(30); cout << right << "Remove 13";
    myheap.remove_val(13);
    msl::print_heap(myheap);
}
#endif // VIEW_HPP
