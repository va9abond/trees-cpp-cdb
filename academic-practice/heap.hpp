#ifndef HEAP_HPP
#define HEAP_HPP


#include "myutils.hpp"
#include <vector>


#define EXPERIMENTAL_FEATURES 0


template < class Ty,
           class Cont_t = std::vector<Ty>,
           class Compr_t = std::less<typename Cont_t::value_type>
         >
class heap { // max heap := root contain max key
public:
    using value_type = typename Cont_t::value_type;
    using reference = typename Cont_t::reference;
    using const_reference = typename Cont_t::const_reference;
    using size_type = typename Cont_t::size_type;
    using container_type = Cont_t;
    using value_compare = Compr_t;


    static_assert(std::is_same_v<Ty, value_type>, "container adaptors require consistent types");
    static_assert(std::is_object_v<Ty>, "The C++ Standard forbids container adaptors of non-object types "
                                        "because of [container.requirements].");


    heap() = default;

    explicit heap (const Compr_t& Pred) noexcept
        : Mycont(), Mycomp(Pred) {}

    heap (const Compr_t& Pred, const Cont_t& Cont)
        : Mycont(Cont), Mycomp(Pred) {
        make_heap(Mycont.begin(), Mycont.end(), Mycomp);
    }

    heap (const Compr_t& Pred, const Cont_t&& Cont)
        : Mycont(std::move(Cont)), Mycomp(Pred) {
        make_heap(Mycont.begin(), Mycont.end(), Mycomp);
    }


    bool empty() const noexcept(noexcept(Mycont.empty())) {
        return Mycont.empty();
    }

    size_type size() const noexcept(noexcept(Mycont.size())) {
        return Mycont.size();
    }

    size_type max_size() const noexcept(noexcept(Mycont.max_size())) {
        return Mycont.max_size();
    }

    const_reference top() const noexcept(noexcept(Mycont.front())) {
        return Mycont.front();
    }

    void push (const value_type& Val) {
        Mycont.push_back(Val); // increase capacity inside
        Sift_up(size() - 1);
    }

    void push (value_type&& Val) {
        Mycont.push_back(std::move(Val)); // increase capacity inside
        Sift_up(size() - 1);
    }

    template <class... Valty>
    void emplace (Valty&&... Vals) {
        Mycont.emplace_back(std::forward<Valty>(Vals)...);
        Sift_up(size() - 1);
    }

    void pop() { // remove root (max priority = max value) from heap
        // 1. swap root with last inserted element(the last element in Mycont)
        // 2. remove last element
        // 3. Heapify_down new root
        Swap(0, size() - 1);
        Mycont.pop_back();
        Heapify(0);
    }

private:
    // [WARNING]: do not check capacity, max_size
    size_type Parent_index (size_type i) const { // 0 <= result <= max_size()
        if (i < 0) {
            throw std::invalid_argument("invalid index");
        }

        return ( (i - 1) >> 1 ) * (i > 0);
    }

// [WARNING]: do not check capacity, max_size
    size_type Right_index (size_type i) const { // 0 <= result <= max_size()
        if (i < 0) {
            throw std::invalid_argument("invalid index");
        }

        return (i << 1) + 2;
    }

// [WARNING]: do not check capacity, max_size
    size_type Left_index (size_type i) const { // 0 <= result <= max_size()
        if (i < 0) {
            throw std::invalid_argument("invalid index");
        }
        return (i << 1) + 1;
    }

    void Swap (size_type k, size_type m) {
        std::swap(Mycont.at(k), Mycont.at(m));
    }

    void Sift_up (size_type Inow) {
        // size_type Inext = Parent_index(Inow);
        size_type Inext = (Inow - 1) >> 1;
        while (Inow > 0 && Mycont[Inow] > Mycont[Inext]) {
            Swap(Inow, Inext);
            Inow = Inext; Inext = Parent_index(Inow);
        }
    }

    void Heapify (size_type Inow = 0) {
        // size_type Iright = Right_index(Inow);
        size_type Iright = 2*Inow + 1;

        // size_type Ileft = Left_index(Inow);
        size_type Ileft = 2*Inow + 2;

        size_type Iswap = Inow;

        if (Ileft < size() && Mycont[Ileft] > Mycont[Iswap]) {
            Iswap = Ileft;
        }

        if (Iright < size() && Mycont[Iright] > Mycont[Iswap]) {
            Iswap = Iright;
        }

        if (Iswap != Inow) {
            Swap(Iswap, Inow);
            Heapify(Iswap);
        }
    }

public:
#if EXPERIMENTAL_FEATURES

    void print_heap_experimental() {
        printf("\n");

        // on each level level we have not greater
        // then 2^level nodes
        auto max_level = msl::lower_bound_power2(size());
        int level = 0;

        size_type lower_bound = 0;
        size_type upper_bound = 0;

        for (int l = 0; l < max_level; ++l) {

            // print tabs
            for (auto t = 0; t < ( (2^max_level) - (2^level) ) / 2 ; ++t) {
                printf("\t");
            }

            // print values
            lower_bound = upper_bound;
            upper_bound = 2^level;
            for (auto i = lower_bound; i < upper_bound; ++i) {
                std::cout << Mycont[i] << " ";
            }

            // print new line
            printf("\n");
        }
    }
#endif

private:
    Cont_t Mycont{};
    Compr_t Mycomp{};
};


namespace msl {
    template <class Ty>
    inline void print_heap (heap<Ty> h) {
        printf("\n");
        while (!h.empty()) {
            printf("%d ", h.top());
            h.pop();
        }
        printf("\n");
    }
}



#endif // HEAP_HPP
