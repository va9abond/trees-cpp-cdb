// #include <memory>
#include <utility>




#define _MYBASE   MYBASE::

namespace MYBASE {


    template <class Ty>
    Ty* addressof (Ty &arg) {
        return &arg;
    }        

    template <class Ty>
    void swap (Ty &a, Ty &b) {     
    // it's just a copy of std::swap() implementation
        if (_MYBASE addressof(a) == _MYBASE addressof(b)) {
            return;
        }

        Ty tmp = std::move(a);
        a      = std::move(b);
        b = std::move(tmp);
    }
}


template <
    class Ty1_,
    class Ty2_
>
struct mypair {
public:

    // tags:
    using first_type  = Ty1_;
    using second_type = Ty2_;



    mypair (const Ty1_ &Val1, const Ty2_ &Val2) noexcept :
        first(Val1),
        second(Val2)
    {}

    ~mypair() = default;

    // template <
    //     class _Other1,
    //     class _Other2
    // >
    // explicit mypair(_Other1 &&Val1, _Other2 &&Val2) noexcept :
    //     first(std::forward<_Other1>(Val1)),
    //     second(std::forward<_Other2>(Val2)) 
    // {}

    mypair& operator= (const volatile mypair&) = delete;

    // _CONSTEXPR20 pair& operator=(const pair<_Other1, _Other2>& _Right) noexcept(
    // is_nothrow_assignable_v<_Ty1&, const _Other1&>&&
    // is_nothrow_assignable_v<_Ty2&, const _Other2&>) /* strengthened */ {
    // first  = _Right.first;
    // second = _Right.second;
    // return *this;
    // }

    mypair (const mypair&) = default;
    
    mypair (mypair&&) = default;

    void swap (mypair &other) {
        if (this != std::addressof(other)) {
            _MYBASE swap(first , other.first );
            _MYBASE swap(second, other.second);
        }
    }



    Ty1_ first;
    Ty2_ second;

};








// #include <map>
#include <string>

#include <iostream>

int main() {

    mypair<int, int> pair1(12,234);
    std::cout << pair1.first << " " << pair1.second << '\n';

    mypair<int, int> pair2(5,546);
    std::cout << pair2.first << " " << pair2.second << '\n';

    mypair<int, std::string> pairs(12, "fjg");     
    std::cout << pairs.first << " " << pairs.second << '\n';

    pair1 = pair2;
    



    // std::map<std::string, int> m;
    // // …
    // for (const auto& [key, value] : m) {
    //   // …
    // }
}