#ifndef TREE_HPP
#define TREE_HPP

#define CHECK_TREE_SIZE 0
#define RELEASE_FEATURE 1

#include "myutils.hpp"


enum class traversal_order_tag {
    in_order,
    pre_order,
    post_order
};


template <
    class Mytree,
    traversal_order_tag Order = traversal_order_tag::in_order
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

    pointer operator->() const noexcept {
        return &(Myptr->Myval);
    }

    Tree_const_iterator& operator++() noexcept {
        switch (Order) {
            case traversal_order_tag::in_order:
                if ( Myptr->Right->Ishead ) {
                    Nodeptr Pnode = nullptr;
                    while ( !(Pnode = Myptr->Parent)->Ishead && Myptr == Pnode->Right ) {
                        Myptr = Pnode;
                    }
                    Myptr = Pnode;
                } else {
                    Myptr = Mytree::Min_(Myptr->Right);
                }
                return *this;
                break;


            case traversal_order_tag::pre_order:
                break;


            case traversal_order_tag::post_order:
                break;
        }
    }

    Tree_const_iterator& operator++(int) noexcept {
        Tree_const_iterator Tmp = *this;
        ++*this;
        return Tmp;
    }


    Tree_const_iterator& operator--() noexcept {
        switch (Order) {
            case traversal_order_tag::in_order:
                if (Myptr->Ishead) { // --end() ==> rightmost
                    Myptr = Myptr->Right;
                } else if (Myptr->Left->Ishead) {
                    Nodeptr Pnode = nullptr;
                    while ( !(Pnode = Myptr->Parent)->Ishead && Myptr == Pnode->Left ) {
                        Myptr = Pnode;
                    }
                    if (!Myptr->Ishead) { // decrement non-begin()
                        Myptr = Pnode;    // if Myptr->Ishead, then Myptr was
                                          // always a left child during we have
                                          // been climbind up the tree
                    }
                } else {
                    Myptr = Mytree::Max_(Myptr->Left);
                }
                return *this;
                break;


            case traversal_order_tag::pre_order:
                break;


            case traversal_order_tag::post_order:
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


template <
    class Mytree,
    traversal_order_tag Order = traversal_order_tag::in_order
> // Tree_unchecked_iterator
class Tree_iterator : public Tree_const_iterator<Mytree, Order> {
public:
    using Mybase = Tree_const_iterator<Mytree, Order>;
    using iterator_category = std::bidirectional_iterator_tag;

    using Nodeptr         = typename Mytree::Nodeptr;
    using value_type      = typename Mytree::value_type;
    using difference_type = typename Mytree::difference_type;
    using pointer         = typename Mytree::pointer;
    using reference       = value_type&;

    using Mybase::Mybase; // inherit base class constructors

    reference operator*() const noexcept {
        return const_cast<reference>(Mybase::operator*());
    }

    pointer operator->() const noexcept {
        return const_cast<pointer>(Mybase::operator->());
    }

    Tree_iterator& operator++() noexcept {
        Mybase::operator++();
        return *this;
    }

    Tree_iterator& operator++(int) noexcept {
        Tree_iterator Tmp = *this;
        Mybase::operator++();
        return Tmp;
    }

    Tree_iterator& operator--() noexcept {
        Mybase::operator--();
        return *this;
    }

    Tree_iterator& operator--(int) noexcept {
        Tree_iterator Tmp = *this;
        Mybase::operator--();
        return Tmp;
    }
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
        Nodeptr Headptr = new Tree_node();
        Headptr->Ishead = true;
        Headptr->Height = 0;
        Headptr->Left = Headptr; Headptr->Right = Headptr; Headptr->Parent = Headptr;
        return Headptr;
    }

    template <class... Valty>
    static Nodeptr Buy_node (Nodeptr Myhead, Valty&&... Val) {
        Nodeptr Newnode = new Tree_node();
        ::new(static_cast<void*>(std::addressof(Newnode->Myval))) value_type(std::forward<Valty>(Val)...);
        Newnode->Ishead = false;
        Newnode->Left = Myhead;
        Newnode->Right = Myhead;
        Newnode->Parent = Myhead;
        Newnode->Height = 1;
        return Newnode;
    }

    static void Free_node0 (Nodeptr Ptr) noexcept { // deallocate node with no data (Myhead)
        Ptr->Left = nullptr; Ptr->Right = nullptr; Ptr->Parent = nullptr;
        delete Ptr; Ptr = nullptr;
    }

    static void Free_node (Nodeptr Ptr) noexcept { // deallocate node with data
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
            return comp(Rhs.first, Lhs.first);
        }

        key_compare comp;
    };

    template <class Ty1, class Ty2>
    static const key_type& Kfn (const std::pair<Ty1, Ty2>& Val) { // extract key from value
        return Val.first;
    }
};


#if RELEASE_FEATURE
enum class Tree_child {
    Right, // perf note: compare with _Right rather than _Left where possible for comparison with zero
    Left,
    Unused // indicates that tree child should never be used for insertion
};

template <class Nodeptr>
struct Tree_find_result {
    Nodeptr Parent; // the leaf node under which a new node should be inserted
    Tree_child Child;
    Nodeptr Bound;
};
#endif


template <
    class Kty,
    class Ty,
    class Compr_t = std::less<Kty>
>
class avltree {
public:
    using Traits = Tree_traits<Kty, Ty, Compr_t>;

    using Nodeptr         = typename Traits::Nodeptr;
    using Node            = typename Traits::Node;
    using key_type        = Kty;
    using mapped_type     = Ty;
    using key_compare     = Compr_t;
    using value_compare   = typename Traits::value_compare;
    using value_type      = std::pair<const Kty, Ty>;
    using size_type       = typename Traits::size_type;
    using difference_type = typename Traits::difference_type;
    using pointer         = typename Traits::pointer;
    using const_pointer   = typename Traits::const_pointer;
    using reference       = typename Traits::reference;
    using const_reference = typename Traits::const_reference;

    template <class, traversal_order_tag>
    friend class Tree_iterator;

    template <class, traversal_order_tag>
    friend class Tree_const_iterator;

    template <class>
    friend struct Tree_node;

    using Self = avltree<Kty, Ty, Compr_t>;

    using iterator = Tree_iterator <
        Self, traversal_order_tag::in_order
    >;

    using const_iterator = Tree_const_iterator <
        Self, traversal_order_tag::in_order
    >;


//          BST in general, but not an avl
// [TODO]: Ctor    [x]
// [TODO]: Dtor    [x]
// [TODO]: Emplace [x]
//          balancing, convert BST to an avltree
// [TODO]: Lrotate []
// [TODO]: Rrotate []
// [TODO]: manage node height
// [TODO]: Balance
//          sugar
// [TODO]: Erase
// [TODO]: (iterator case) pre_order, post_order

    avltree() noexcept : Myhead(), Mysize(0) {
        Myhead = Node::Buy_head_node();
    }

    ~avltree() noexcept {
        Erase_head();
    }

private:
    void Erase_head() noexcept {
        Erase_tree(Myhead->Parent);
        Node::Free_node0(Myhead);
    }

    void Erase_tree (Nodeptr Rootnode) noexcept {
        while (!Rootnode->Ishead) {
            Erase_tree(Rootnode->Right);
            Node::Free_node(std::exchange(Rootnode, Rootnode->Left));
        }
    }

public:
    void clear() noexcept { // get back tree to init state
        Erase_tree(Myhead->Parent);
        Myhead->Parent = Myhead;
        Myhead->Left = Myhead;
        Myhead->Right = Myhead;
        Mysize = 0;
    }

private:
    static Nodeptr Max_ (Nodeptr Pnode) noexcept { // return rightmost node
                                                   // in subtree at Pnode
        while (!Pnode->Right->Ishead) {
            Pnode = Pnode->Right;
        }

        return Pnode;
    }

    static Nodeptr Min_ (Nodeptr Pnode) noexcept { // return leftmost node
                                                   // in subtree at Pnode
        while (!Pnode->Left->Ishead) {
            Pnode = Pnode->Left;
        }

        return Pnode;
    }

public:
    iterator begin() noexcept {
        return iterator(Myhead->Left);
    }

    const_iterator begin() const noexcept {
        return const_iterator(Myhead->Left);
    }

    iterator end() noexcept {
        return iterator(Myhead);
    }

    const_iterator end() const noexcept {
        return const_iterator(Myhead);
    }

    size_type size() const noexcept {
        return Mysize;
    }

    bool empty() const noexcept {
        return Mysize == 0;
    }

    key_compare key_comp() const {
        return Compr_t{};
    }

    value_compare value_comp() const {
        return value_compare(key_comp());
    }

#if CHECK_TREE_SIZE
    size_type max_size() const noexcept {
        return static_cast<size_type>(std::numeric_limits<difference_type>::max);
    }
#endif

    template <class... Valtys>
    std::pair<iterator, bool> emplace (Valtys&&... Vals) {
        const auto Result = Emplace(std::forward<Valtys>(Vals)...);
        return { iterator(Result.first), Result.second };
    }

private:
    bool Is_equivalent (const key_type& Rhs, const key_type& Lhs) {
        return !key_compare{}(Rhs, Lhs) && !key_compare{}(Lhs, Rhs);
    }

public:
    template <traversal_order_tag Order, class Pred_t>
    void traversal (Nodeptr Where, Pred_t Pred) {
        if (Where) {
            switch (Order) {
                case traversal_order_tag::in_order:
                    traversal<traversal_order_tag::in_order, Pred_t>(Where->Left, Pred);
                    Pred(Where->Myval);
                    traversal<traversal_order_tag::in_order, Pred_t>(Where->Right, Pred);
                    break;


                case traversal_order_tag::pre_order:
                    Pred(Where->Myval);
                    traversal<traversal_order_tag::in_order, Pred_t>(Where->Left, Pred);
                    traversal<traversal_order_tag::in_order, Pred_t>(Where->Right, Pred);
                    break;


                case traversal_order_tag::post_order:
                    traversal<traversal_order_tag::in_order, Pred_t>(Where->Left, Pred);
                    traversal<traversal_order_tag::in_order, Pred_t>(Where->Right, Pred);
                    Pred(Where->Myval);
                    break;
            }
        }
    }

#if CHECK_TREE_SIZE
private:
    void Check_grow_by_1() {
        if (max_size() == Mysize) {
            throw std::length_error("tree too long");
        }
    }
#endif

#if RELEASE_FEATURE
    Tree_find_result<Nodeptr> Find_lower_bound (const key_type& key, bool update = true) const {
        Tree_find_result<Nodeptr> Loc { Myhead->Parent, Tree_child::Right, Myhead };
        Nodeptr Trynode = Loc.Parent;
        key_compare Pred = key_comp();

        while (Trynode && Trynode != Myhead) {
            Loc.Parent = Trynode;

            if (update) {
                ++Trynode->Height;
            }

            if (Pred(Traits::Kfn(Trynode->Myval), key)) {
                Loc.Child = Tree_child::Right;
                Trynode = Trynode->Right;
            } else {
                Loc.Child = Tree_child::Left;
                Loc.Bound = Trynode;
                Trynode = Trynode->Left;
            }
        }
        return Loc;
    }

private:
    template <class... Valtys>
    std::pair<Nodeptr, bool> Emplace (Valtys&&... Vals) {
        Nodeptr Inserted = Node::Buy_node(Myhead, std::forward<Valtys>(Vals)...);
        const key_type& key = Traits::Kfn(Inserted->Myval);
        Tree_find_result<Nodeptr> Loc = Find_lower_bound(key);
        // Check_grow_by_1();

        return { Insert_node(Loc, Inserted), true };
    }

    Nodeptr Insert_node (const Tree_find_result<Nodeptr> Loc, const Nodeptr Newnode) noexcept {
        ++Mysize;
        Newnode->Parent = Loc.Parent;
        if (Loc.Parent == Myhead) {    // <=> Mysize == 0,
                                       // first node in tree, just set head values
            Myhead->Left = Newnode;   // set min()
            Myhead->Right = Newnode;  // set max()
            Myhead->Parent = Newnode; // set root
            return Newnode;
        }

        if (Loc.Child == Tree_child::Right) { // add to right of Loc.Parent
            Loc.Parent->Right = Newnode;
            if (Loc.Parent == Myhead->Right) { // if Newnode right of max(), then Newnode is new max()
                Myhead->Right = Newnode;
            }
        } else {
            Loc.Parent->Left = Newnode;
            if (Loc.Parent == Myhead->Left) { // if Newnode left of min(), then Newnode is new min()
                Myhead->Left = Newnode;
            }
        }

        Newnode->Height = Loc.Parent->Height - 1;

        // [TODO]: Balance

        return Newnode;
    }
#endif

void Rrotate (Nodeptr Where) noexcept { // promote left child to root of subtree
    Nodeptr Newroot = Where->Left;
    Where->Left = Newroot->Right;

    if (!Newroot->Right->Ishead) {
        Newroot->Right->Parent = Where;
    }

    Newroot->Parent = Where->Parent;

    if (Where == Myhead->Parent) {
        Myhead->Parent = Newroot;
    } else if (Where == Where->Parent->Right) {
        Where->Parent->Right = Newroot;
    } else {
        Where->Parent->Left = Newroot;
    }

    Newroot->Right = Where;
    Where->Parent = Newroot;

    Update_height(Where);
    Update_height(Newroot);
}

void Lrotate (Nodeptr Where) noexcept { // promote right child to root of subtree
    Nodeptr Newroot = Where->Right;
                                       // transfer B subtree
    Where->Right = Newroot->Left;
                                       // if subtree B not nullptr then change is's parent
    if (!Newroot->Left->Ishead) {
        Newroot->Left->Parent = Where;
    }
                                       // change Parent of Newroot
    Newroot->Parent = Where->Parent;
                                       // change Parent ptr to Newroot
    if (Where == Myhead->Parent) {     // if where is root of entire tree
        Myhead->Parent = Newroot;
    } else if (Where->Parent->Right == Where) { // if Where is right child
        Where->Paretn->Right = Newroot;
    } else {                                    // if Where is left child
        Where->Paretn->Left = Newroot;
    }

    Newroot->Left = Where;
    Where->Parent = Newroot;

    Update_height(Where);
    Update_height(Newroot);
}

unsigned Subtree_height (Nodeptr Subroot) const noexcept {
    return (Subroot->Ishead ? 0 : Subroot->Height);
}

int Skew (Nodeptr Subroot) const noexcept { // balance factor
    return (Subroot->Ishead ? 0 : Subtree_height(Subroot->Left) - Subtree_height(Subroot->Right));
}

void Update_height (Nodeptr Where) noexcept {
    Where->Height = std::max(Subtree_height(Where->Left), Subtree_height(Where->Right)) + 1;
}

public:
    Nodeptr Myhead; // pointer to head node
                    // Myhead->Parent is root of entire tree
                    // Myhead->Parent->Parent is Myhead
                    // Myhead->Right rightmost leaf in tree
                    // Myhead->Left leftmost leaf in tree
    size_type Mysize; // number of elements
};






#endif // TREE_HPP
