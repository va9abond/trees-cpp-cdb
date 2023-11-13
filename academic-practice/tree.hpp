#ifndef TREE_HPP
#define TREE_HPP


#include "myutils.hpp"


template <class Value_type>
struct Tree_node {
    using Nodeptr = Tree_node<Value_type>*;
    using value_type = Value_type;

    Nodeptr Left;   // left subtree, or smallest element if head
    Nodeptr Right;  // right subtree, or largest element if head
    Nodeptr Parent; // parent, or root of the tree if head
    value_type Myval; // the stored value, unused if head



    Tree_node() = default;
    Tree_node (const Tree_node&) = delete;
    Tree_node& operator= (const Tree_node&) = delete;

    static Nodeptr Buy_head_node() {
        Nodeptr Node = new Tree_node();
        Node->Left = Node; Node->Right = Node; Node->Parent = Node;
        return Node;
    }

    template <class... Valty>
    static Nodeptr Buy_node (Nodeptr Myhead, Valty&&... Val) {
        Nodeptr Newnode = new Tree_node();
        ::new(static_cast<void*>(std::addressof(Newnode->Myval))) value_type(std::forward<Valty>(Val)...);
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

// template <class Traits>
// class mytree {
// public:
//     using key_type = typename Traits::key_type;
//     using value_type = typename Traits::value_type;
//     using Node = Tree_node<value_type>;
//     using Nodeptr = Node*;
// };

















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
