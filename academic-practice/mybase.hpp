#ifndef MYBASE_HPP
#define MYBASE_HPP


#include <iostream>

#define SWITCH_SWAP_PROXY_AND_ITERATORS 0

namespace msl {
    inline void _MSL_REPORT_ERROR_f (const char* mesg) noexcept {
        std::cerr << "\n" << mesg << "\n"; std::exit(134);
    }

    inline void _MSL_VERIFY_f (bool cond, const char* mesg) noexcept {
        if (!cond) return _MSL_REPORT_ERROR_f(mesg);
    }
}

struct Iterator_base;
struct Container_base;


struct Container_proxy {
    Container_proxy() noexcept = default;
    Container_proxy (Container_base* Mycont) noexcept : Mycont(Mycont) {}


    const   Container_base* Mycont      = nullptr;
    mutable Iterator_base*  Myfirstiter = nullptr;
};


struct Container_base {

    Container_base() noexcept = default;

    Container_base (const Container_base&)            = delete;
    Container_base& operator= (const Container_base&) = delete;

    ~Container_base() {
        Orphan_all();
        Free_proxy();
    }

    void Orphan_all() noexcept;
#if SWITCH_SWAP_PROXY_AND_ITERATORS
    void Swap_proxy_and_iterators (Container_base&) noexcept;
#endif
    void Alloc_proxy() {
        Myproxy = new Container_proxy(this);
    }

    void Free_proxy() noexcept {
        if (Myproxy) {
            Myproxy->Mycont = nullptr; Myproxy->Myfirstiter = nullptr;
            delete Myproxy; Myproxy = nullptr;
        }
    }


    Container_proxy* Myproxy = nullptr;
};


struct Iterator_base {
public:
    Iterator_base() noexcept = default; // construct orphaned iterator

    Iterator_base (const Iterator_base& Rhs) noexcept {
        *this = Rhs;
    }

    Iterator_base& operator= (const Iterator_base& Rhs) noexcept {
        Assign(Rhs);
        return *this;
    }

    ~Iterator_base() noexcept { // NOTE: mb i need to free allocated memory
        Orphan_me_v2();
    }

    void _Adopt_by_cont (const Container_base* Parent) noexcept {
        return Adopt_me(Parent);
    }

    const Container_base* Getcont() const noexcept {
        return Myproxy ? Myproxy->Mycont : nullptr;
    }


    mutable Container_proxy* Myproxy    = nullptr;
    mutable Iterator_base*   Mynextiter = nullptr;

private:
    // Assign self to other container by given iterator
    // from other container
    void Assign (const Iterator_base& Rhs) noexcept {
        if (Myproxy == Rhs.Myproxy) { return; }
        if (Rhs.Myproxy) { // != nullptr => do adoption
            Adopt_me(Rhs.Myproxy->Mycont);
        } else { // == nullptr => no parent container now
            Orphan_me_v2();
        }
    }

    // adopt self by other parent container
    void Adopt_me (const Container_base* Other_parent) noexcept {
        if (!Other_parent) { // other parent container is nullptr, no parent cont now
            Orphan_me_v2();
            return;
        }

        // do adoption
        Container_proxy* Other_parent_proxy = Other_parent->Myproxy;
        if (Myproxy != Other_parent_proxy) { // change parentage
            if (Myproxy) { // already adopted, remove self from current list
                Orphan_me_v2();
            }

            // insert at the beginning of list
            Mynextiter = Other_parent_proxy->Myfirstiter;
            Other_parent_proxy->Myfirstiter = this;
            Myproxy = Other_parent_proxy;
        }
    }

    // remove self from parent container
    void Orphan_me_v1() noexcept {
        if (!Myproxy) { return; } // already orphaned

        // remove self from current list
        Iterator_base** Pnext = &Myproxy->Myfirstiter;
        // Iterator_base** because _Myfirsiter may equals nullptr
        while (*Pnext && (*Pnext)->Mynextiter != this) {
            Pnext = &(*Pnext)->Mynextiter;
        }

        msl::_MSL_VERIFY_f(*Pnext, "ITERATOR LIST CORRUPTED");
        (*Pnext)->Mynextiter = Mynextiter;
        Mynextiter = nullptr; Myproxy = nullptr;
    }

    void Orphan_me_v2() noexcept {
        if (!Myproxy) { return; } // already orphaned

        // remove self from current list
        Iterator_base** Pnext = &Myproxy->Myfirstiter;
        while (*Pnext && *Pnext != this) {
            Pnext = &(*Pnext)->Mynextiter;
        }

        msl::_MSL_VERIFY_f(*Pnext, "ITERATOR LIST CORRUPTED");
        *Pnext = Mynextiter; // <=> this = _Mynextiter, but we need there Pnext
                              // to make assign, expression (this = _Mynextiter)
                              // or (this = *_Mynextiter) cause error(idk why) 
                              // INCORRECT ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        // this and *Pnext point to same memory cell, and all those pointers that
        // point to the memory cell this alse point to *Pnext, and if we change 
        // *Pnext to another address, than all pointers will point to the cell
        // corressponding to new adress // TODO: how it works?
        Myproxy = nullptr; // why Myproxy should be nullptr now, this points to
                            // _Mynextiter, doesn't it? And _Mynextiter still
                            // child of current container
                            // INCORRECT ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    }
};


inline void Container_base::Orphan_all() noexcept {
    if (!Myproxy) { return; } // no any iterators

    Iterator_base* Pnext = Myproxy->Myfirstiter; Myproxy->Myfirstiter = nullptr;
    while (Pnext) {
        Pnext->Myproxy = nullptr;
        Pnext = Pnext->Mynextiter;
    }
    // NOTE: after that whihe loop we have iterators list somewhere in memory,
    // they don't rely with any container, but it still a connected list.
    // Firstly, if we have some iterator we can go to next one throught _Mynextiter,
    // Secondly, does we still can to get access to data throught these iterators?
}

#if SWITCH_SWAP_PROXY_AND_ITERATORS
// swap owners of proxy and iterators
inline void Container_base::Swap_proxy_and_iterators (Container_base& Rhs) noexcept {
    // swap proxy
    Container_proxy* Temp = Myproxy;
    Myproxy = Rhs.Myproxy;
    Rhs.Myproxy = Temp;

    // swap proxy owners
    if (Myproxy) { Myproxy->Mycont = this; }
    if (Rhs.Myproxy) { Rhs.Myproxy->Mycont = &Rhs; }
}
#endif


#endif // MYBASE_HPP
