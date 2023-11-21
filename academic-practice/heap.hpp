#ifndef HEAP_HPP
#define HEAP_HPP


#include "myutils.hpp"
#include <vector>


#define EXPERIMENTAL_FEATURES 0


template < class Ty,
           class Cont_t = std::vector<Ty>,
           class Compr_t = std::less<typename Cont_t::value_type> >
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

    value_type pop() { // remove root (max priority = max value) from heap
        value_type Poped = Mycont.back();

        // 1. swap root with last inserted element(the last element in Mycont)
        // 2. remove last element
        // 3. Heapify_down new root
        Swap(0, size() - 1);
        Mycont.pop_back();
        Heapify(0);

        return Poped;
    }

    value_compare value_comp() const {
        return Compr_t{};
    }

private:
    bool Is_equivalent (const value_type& Rhs, const value_type& Lhs) const {
        value_compare Pred = value_comp();
        return !Pred(Rhs, Lhs) && !Pred(Lhs, Rhs);
    }

public:
    bool remove_val (const value_type& Val) {
        value_compare Pred = value_comp();

        size_type Pos = size();
        for (size_type i = 0; i < size(); ++i) {
            if ( Pred(Mycont[i], Val) ) { Pos = i; break; }
        }

        if ( Pos < size() ) {
            Swap(Pos, size() - 1);
            Mycont.pop_back();
            Heapify(Pos);

            return true;
        }

        return false;
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

    void Sift_up (size_type Posnow) {
        value_compare Pred = value_comp();

        // size_type Inext = Parent_index(Posnow);
        size_type Inext = (Posnow - 1) >> 1;
        while ( Posnow > 0 && Pred(Mycont[Inext], Mycont[Posnow]) ) {
            Swap(Posnow, Inext);
            Posnow = Inext; Inext = Parent_index(Posnow);
        }
    }

    void Heapify (size_type Posnow = 0) {
        value_compare Pred = value_comp();

        // size_type Posright = Right_index(Posnow);
        size_type Posright = 2*Posnow + 1;

        // size_type Posleft = Left_index(Posnow);
        size_type Posleft = 2*Posnow + 2;

        size_type Iswap = Posnow;

        if (Posleft < size() && Pred(Mycont[Iswap], Mycont[Posleft])) {
            Iswap = Posleft;
        }

        if (Posright < size() && Pred(Mycont[Iswap], Mycont[Posright])) {
            Iswap = Posright;
        }

        if (Iswap != Posnow) {
            Swap(Iswap, Posnow);
            Heapify(Iswap);
        }
    }

    void Check_index (size_type Pos) {
        if (Pos < 0 || Pos >= size()) {
            throw std::invalid_argument("Invalid Position Index");
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
