#ifndef TREE_HPP
#define TREE_HPP


#include "myutils.hpp"


enum class traveling_order_tag {
    in_order,
    pre_order,
    post_order
};


template <
    class Mytree,
    traveling_order_tag Trot = traveling_order_tag::in_order
>
class Tree_const_iterator { // Tree_const_unchecked_iterator
public:
    using iterator_category = std::bidirectional_iterator_tag;

    using Nodeptr         = typename Mytree::Nodeptr;
    using value_type      = typename Mytree::value_type;
    using difference_type = typename Mytree::difference_type;
    using pointer         = typename Mytree::const_pointer;
    using reference       = const value_type&;


    Tree_const_iterator (Nodeptr Rhs = nullptr) noexcept : Myptr(Rhs) {}

    Tree_const_iterator& operator= (const Tree_const_iterator& Rhs) {
        Myptr = Rhs.Myptr;
    }

    reference operator*() const noexcept {
        return Myptr->Myval;
    }

    pointer operator->() {
        return std::addressof(Myptr->Myval);
    }

    Tree_const_iterator& operator++() noexcept {
        switch (Trot) {
            case traveling_order_tag::in_order:
                if ( Myptr->Right == nullptr ) {
                    Nodeptr Pnode = Myptr;
                    while ( (Pnode = Myptr->Parent) && Myptr == Pnode->Right ) {
                        Myptr = Pnode;
                    }
                    Myptr = Pnode;
                } else {
                    Myptr = Mytree::Min(Myptr->Right);
                }
                return &this;
                break;
            case traveling_order_tag::pre_order:

                break;
            case traveling_order_tag::post_order:

                break;
        }
    }

    Tree_const_iterator& operator++(int) noexcept {
        Tree_const_iterator Tmp = *this;
        ++*this;
        return Tmp;
    }


    Tree_const_iterator& operator--() noexcept {
        switch (Trot) {
            case traveling_order_tag::in_order:
                if (Myptr->Ishead) { // --end() ==> rightmost
                    Myptr = Myptr->Right;
                } else if (Myptr->Left == nullptr) {
                    Nodeptr Pnode = Myptr;
                    while ( (Pnode = Myptr->Parent) && Myptr == Pnode->Left ) {
                        Myptr = Pnode;
                    }
                    if (!Myptr->Ishead) { // decrement non-head
                        Myptr = Pnode;
                    }
                } else {
                    Myptr = Mytree::max(Myptr->Left);
                }
                return *this;
                break;
            case traveling_order_tag::pre_order:

                break;
            case traveling_order_tag::post_order:

                break;
        }
    }

    Tree_const_iterator& operator--(int) noexcept {
        Tree_const_iterator Tmp = *this;
        --*this;
        return Tmp;
    }

    bool operator== (const Tree_const_iterator& Rhs) const noexcept {
        return Myptr == Rhs.Myptr;
    }

    bool operator!= (const Tree_const_iterator& Rhs) const noexcept {
        return !(Myptr == Rhs.Myptr);
    }


    Nodeptr Myptr;
};





template <class Value_type>
struct Tree_node {
    using Nodeptr = Tree_node<Value_type>*;
    using value_type = Value_type;

    Nodeptr Left;   // left subtree, or smallest element if head
    Nodeptr Right;  // right subtree, or largest element if head
    Nodeptr Parent; // parent, or root of the tree if head
    value_type Myval; // the stored value, unused if head
    bool Ishead;      // true only if head node
    unsigned Height; // to easy detect unbalanced tree



    Tree_node() = default;
    Tree_node (const Tree_node&) = delete;
    Tree_node& operator= (const Tree_node&) = delete;

    static Nodeptr Buy_head_node() {
        Nodeptr Node = new Tree_node();
        Node->Ishead = true;
        Node->Left = Node; Node->Right = Node; Node->Parent = Node;
        return Node;
    }

    template <class... Valty>
    static Nodeptr Buy_node (Nodeptr Myhead, Valty&&... Val) {
        Nodeptr Newnode = new Tree_node();
        ::new(static_cast<void*>(std::addressof(Newnode->Myval))) value_type(std::forward<Valty>(Val)...);
        Newnode->Ishead = false;
        Newnode->Left = Myhead;
        Newnode->Right = Myhead;
        Newnode->Parent = Myhead;
        return Newnode;
    }

    static void Free_node0 (Nodeptr Ptr) noexcept {
        Ptr->Left = nullptr; Ptr->Right = nullptr; Ptr->Parent = nullptr;
        delete Ptr; Ptr = nullptr;
    }

    static void Free_node (Nodeptr Ptr) noexcept {
        Ptr->Myval.~Value_type();
        Free_node0(Ptr);
    }
};


template <
    class Kty,
    class Ty,
    class Compr_t
>
struct Tree_traits {
    using key_type        = Kty;
    using value_type      = std::pair<const Kty, Ty>;
    using key_compare     = Compr_t;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using Node            = Tree_node<value_type>;
    using Nodeptr         = Tree_node<value_type>*;

    struct value_compare {
        value_compare (key_compare Pred) : comp(Pred) {}

        bool operator() (const value_type& Rhs, const value_type& Lhs) const {
            return comt(Rhs.first, Lhs.first);
        }

        key_compare comp;
    };
};


template <
    class Kty,
    class Ty,
    class Compr_t = std::less<Kty>
>
class avltree {
public:
    using Traits = Tree_traits<Kty, Ty, Compr_t>;

    using Nodeptr         = typename Traits::Nodeptr;
    using key_type        = Kty;
    using mapped_type     = Ty;
    using key_compare     = Compr_t;
    using value_compare   = typename Traits::value_compare;
    using value_type      = std::pair<const Kty, Ty>;
    using size_type       = typename Traits::size_type;
    using difference_type = typename Traits::difference_type;
    using pointer         = typename Traits::pointer;
    using const_pointre   = typename Traits::const_pointer;
    using reference       = typename Traits::reference;
    using const_reference = typename Traits::const_reference;

    using Self = avltree<Kty, Ty, Compr_t>;
    // using iterator = Tree_iterator<Traits, traveling_order_tag::in_order>;
    using const_iterator = Tree_const_iterator<
        Self, traveling_order_tag::in_order
    >;


    avltree() noexcept : Myhead(), Mysize(0) {}

    static Nodeptr max (Nodeptr Pnode) noexcept { // return rightmost node
                                                  // in subtree at Pnode
        while (Pnode->Right != nullptr) {
            Pnode = Pnode->Right;
        }

        return Pnode;
    }

    static Nodeptr min (Nodeptr Pnode) noexcept { // return leftmost node
                                                  // in subtree at Pnode
        while (Pnode->Left) {
            Pnode = Pnode->Left;
        }

        return Pnode;
    }




    Nodeptr Myhead; // pointer to head node
    size_type Mysize; // number of elements
};

















template <
    class Kty,                    // key type
    class Mty,                    // mapped type
    class Compr_t = std::less<Kty> // key comparator type
> class map {
public:
    template <class U, class V> using pair = std::pair<U,V>;
    // using Mybase  = ...
    // using Nodeptr = ...
    using key_type = Kty;
    using mapped_type = Mty;
    using key_compare = Compr_t;
    using value_type = pair<const Kty, Mty>;
    // using size_type = ...
    // using difference_type = ...
    // using pointer = ...
    // using const_pointer = ...
    using reference = value_type&;
    using const_reference = const value_type&;
    // using iterator = ...;
    // using const_iterator = ...;
    // using reverse_iteratoor = ...;
    // using const_reverse_iterator = ...;



    // mytree() : Mybase(key_compare()) {}
};














#endif // TREE_HPP
