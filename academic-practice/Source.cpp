#include <iostream>   // to get std::cout
#include <cassert>    // to get assert() and static assert()
#include <iterator>   // to get iterators' tags
#include <cstddef>    // to get std::ptrdiff_t
#include <limits.h> 
#include <memory>   
// #include <sal.h>
#include <utility>    // to get std::pair<,>
#include <map>        // to get std::map<,>
// #define NDEBUG

#define _STD       ::std::
#define _MYBASE   MYBASE::

// TODO: move semantics



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


// ****************************************************************************
// ************************************ pair **********************************
// ****************************************************************************

    // i'm done
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

// ****************************************************************************
// ************************* ContainerNodeInterface ***************************
// ****************************************************************************

    template <
        class Vty_
    > 
    class ContainerNodeInterface {
    public:

        // tags:
        using value_type      = Vty_;          
        using pointer         = Vty_*;
        using const_pointer   = const Vty_*;  
        using reference       = Vty_&; 
        using const_reference = const Vty_&; 



        ContainerNodeInterface();
        virtual ~ContainerNodeInterface() = 0;


    };


// ****************************************************************************
// ********************************* TreeNode *********************************
// ****************************************************************************
// template <typename Kty_, typename Ity_> class TreeNode : public ContainerNodeInterface {
    template <
        class Kty_,
        class Ity_,
        class Pr_  = std::less<Kty_>
    > 
    class TreeNode : public ContainerNodeInterface<std::pair<const Kty_, Ity_>> {
    // class TreeNode {
    public:

        // tags:
        using key_type        = Kty_;
        using value_type      = std::pair<const Kty_, Ity_>;           // the type the TreeNode iterates over 
        using pointer         = std::pair<const Kty_, Ity_>*;
        using const_pointer   = const std::pair<const Kty_, Ity_>*;  
        using reference       = std::pair<const Kty_, Ity_>&; 
        using const_reference = const std::pair<const Kty_, Ity_>&; 



    // https://stackoverflow.com/questions/74764195/why-does-the-compiler-declare-a-class-method-deleted
        TreeNode(
            const_reference             value,
            unsigned short int          height     = 0,
            TreeNode<const Kty_, Ity_> *parent     = nullptr,
            TreeNode<const Kty_, Ity_> *left       = nullptr,
            TreeNode<const Kty_, Ity_> *right      = nullptr
        ) noexcept :
            _left(left),
            _parent(parent),
            _right(right),
            _value(value),
            _height(height)
        {}

        // TODO 
        TreeNode (const TreeNode *otherptr) noexcept {
            assert(otherptr != nullptr);

            _left     = otherptr->_left;
            _parent   = otherptr->_parent;
            _right    = otherptr->_right;
            _value    = otherptr->_value;
            _height   = otherptr->_height;
        }

        // virtual TreeNode *operator= (const TreeNode *otherptr) noexcept { // do i need a virtual assigment operator 
        //     // assert(other != nullptr);  // TODO: what is other == nullptr

        //     _left       = otherptr->_left;
        //     _parent     = otherptr->_parent;
        //     _right      = otherptr->_right;
        //     _height     = otherptr->_height;

        //     // const_cast<key_type>(_value.first);
        //     _value.second = otherptr->_value.second;
        //     // _value.first = otherptr->_value.first;

        //     return this;
        // }

        virtual ~TreeNode() {
            delete _left;   _left   = nullptr;
            delete _right;  _right  = nullptr;
            delete _parent; _parent = nullptr;
        }



        virtual void setValue (reference value) noexcept {
            // _value = std::make_pair(value.first, value.second);
            // auto newThis = new TreeNode<Kty_, Ity_>(
            //                                              value,
            //                                              this->_height,
            //                                              this->_parent,
            //                                              this->_left,
            //                                              this->_right
            //                                              ); 
            // delete this; this = &newThis;

        } 

        // virtual const_reference getValue() const noexcept { return _value; }
        virtual const std::pair<const Kty_, Ity_> &getValue() const noexcept { return _value; } 
        // virtual const_reference getValue() = 0;



        TreeNode *getLeft() noexcept { return _left; }
        
        TreeNode *getParent() noexcept { return _parent; }
        
        TreeNode *getRight() noexcept { return _right; } 

        TreeNode *getChild() noexcept { // get any child
            if (_left != nullptr) {
                return _left;
            }

            return _right;
        }
        
        
        
        const key_type &getKey() const noexcept { return _value.first; }

        const Ity_ &getItem() const noexcept { return _value.second; }
        
        unsigned short int getHeight() noexcept { return _height; }



        void setLeft (TreeNode *left) noexcept { _left = left; }
        
        void setParent (TreeNode *parent) noexcept { _parent = parent; }
        
        void setRight (TreeNode *right) noexcept { _right = right; }
        
        void setItem (const Ity_ &item) noexcept { _value.second = const_cast<Ity_>(item); }
        
        void setHeight (const unsigned short int &height) { _height = height; }


        
        explicit operator bool () const {
           return _value;
        }



        virtual bool operator== (const TreeNode *node) const noexcept {
            return (_value.first == node->_value.first && _value.second == node->_value.second);
        }

        virtual bool operator != (const TreeNode *node) const noexcept {
            return !(this == node);
        }

        // bool operator > (const TreeNode *node) const noexcept {
        //     assert(this != nullptr && node != nullptr);

        //     return (_value.first > node->_value.first);
        // }

        // bool operator >= (const TreeNode *node) const noexcept {
        //     return (_value.first > node->_value.first || _value.first == node->_value.first);
        // }

        // bool operator < (const TreeNode *node) const noexcept {
        //     return !(this >= node);
        // }

        // bool operator <= (const TreeNode *node) const noexcept {
        //     return !(this > node);
        // }



    protected:
        TreeNode<const Kty_, Ity_> *_left;   // left subtree, or smallest element if head
        TreeNode<const Kty_, Ity_> *_parent; // parent, or root of tree if head
        TreeNode<const Kty_, Ity_> *_right;  // right subtree, or largest element if head
        
        value_type                  _value;
        unsigned short int          _height;
    };



// ****************************************************************************
// ******************************* iterator_base ******************************
// ****************************************************************************

    template <
        class Ity_
    >
    class iterator_base {
    public: 
        
        // tags:
        using iterator_category  = std::bidirectional_iterator_tag; 
        using deffirence_type    = std::ptrdiff_t;
        using value_type         = Ity_;
        using pointer            = Ity_*;
        using const_pointer      = const Ity_*;
        using reference          = Ity_&;
        using const_reference    = const Ity_&;



        explicit iterator_base (pointer item = nullptr) : _item(item) {}
        
        iterator_base (const iterator_base&) = default;
        
        iterator_base (iterator_base&&) noexcept = default;
        
        iterator_base& operator= (const iterator_base&) = default;
        
        iterator_base& operator= (iterator_base&&) noexcept = default;
        
        iterator_base& operator= (pointer item) {
            _item = item;
            return *this;
        }

        ~iterator_base() = default;



        explicit operator bool() const {
            return _item; // is nullptr
        }



        bool operator== (const iterator_base& itt_ref) const noexcept { return _item == itt_ref._item; }
       
        bool operator!= (const iterator_base& itt_ref) const noexcept {return !(*this == itt_ref); }

        iterator_base& operator++ () noexcept {
            ++_item; // why not item_++;
            return *this;
        }

        iterator_base operator++(int) noexcept {
            auto tmp = *this;
            ++_item;

            return tmp;
        }

        iterator_base& operator-- () noexcept {
            --_item; // why not item_++;
            return *this;
        }

        iterator_base operator--(int) noexcept {
            auto tmp = *this;
            --_item;

            return tmp;
        }



        reference operator* () { return *_item; }

        const_reference operator* () const { return *_item; }
        
        pointer operator-> () const { return _item; }



    private:
        pointer _item;

    };




// ****************************************************************************
// ***************************** BinarySearchTree *****************************
// ****************************************************************************


// TODO: inherate from ContainerInterface
// TODO: change std::pait to my own pait class
// BinarySearchTree dosn't allow store values with the same keys
// TODO: make a container that allow store values with the same keys based on BinarySearchTree
template <
    class Kty_,
    class Ity_, 
    class Pr_    = std::less<Kty_>,
    class Alloc_ = std::allocator<std::pair<const Kty_, Ity_>>
>
class BinarySearchTree {
public:
    
    // tags:
    using value_type      = typename std::pair<const Kty_, Ity_>; // a type that BST store                     
    using mapped_type     = Ity_;
    using key_type        = Kty_;
    using Nodeptr         = TreeNode<const Kty_, Ity_>*;          // a pointer to node of BST
    using reference       = std::pair<const Kty_, Ity_>&;                        
    using const_reference = const std::pair<const Kty_, Ity_>&;

    using iterator        = iterator_base<TreeNode<const Kty_, Ity_>>;
    using const_iterator  = iterator_base<const TreeNode<const Kty_, Ity_>>;



    BinarySearchTree() { root_ = nullptr; size_ = 0; }

    BinarySearchTree(const BinarySearchTree &otherref) {
        root_ = otherref.root_;
        size_ = otherref.size_;
    }

    BinarySearchTree &operator= (const BinarySearchTree &otherref) {
        this->_CLEAR_SUBTREE(root_);

        root_ = otherref->root_;
        size_ = otherref->size_;

        return *this;
    }

    ~BinarySearchTree() = default;
    
    

    const Ity_ &at (const Kty_ &key) const {}

    Ity_ &operator[] (const Kty_ &key) const {}



    iterator begin() noexcept { }
    // reverse_iterator rbegin() noexcept {}
    const_iterator cbegin() const noexcept {}

    iterator end() noexcept {}
    // reverse_iterator rend() const noexcept {}
    const_iterator cend() const noexcept {}



    virtual bool empty() const noexcept final {
        return size() == 0;
    }

    virtual size_t size() const noexcept final {
        return size_;
    }

    virtual Nodeptr getRoot() const noexcept final {
        return root_;
    }

    virtual void clear() noexcept final {
        this->_CLEAR_SUBTREE(root_);
    }



    // O(h) // TODO
    std::pair<iterator, bool> insert (const_reference value) {
        assert (size_ < SIZE_MAX );

        Nodeptr node = root_;
        Nodeptr node_parent = root_;

        // TODO
        // Nodeptr node_p = root_;
        // Nodeptr node_c = (key > node_p->getKey() : node_p->getRight() : node_p->getLeft());

        auto key = value.first;
        
        bool key_exists = false;  // is node with the same key already exsists in the tree
        bool is_right_child = false; // is inserting value would be a right child of his parent  


        while ( node != nullptr ) {
            node_parent = node;

            if ( key > node->getKey() ) {
                node = node->getRight();
                is_right_child = true;
            }
            else if ( key == node->getKey() ) {
                key_exists = true;
                break;
            }
            else {
                node = node->getLeft();
                is_right_child = false;
            }
        }

        if (key_exists != true) { // value with the same key doens't exists 
            Nodeptr nodeptrInserting = new TreeNode<const Kty_, Ity_>(
                                                                      value,
                                                                     (size_ > 0 ? node_parent->getHeight() + 1 : 1),
                                                                      node_parent, nullptr, nullptr
                                                                     );

            if ( size_ > 0 ) { 
                (is_right_child) ? node_parent->setRight(nodeptrInserting) : node_parent->setLeft(nodeptrInserting);
            }
            else {
                root_ = nodeptrInserting;
            }
            
            
            size_++;
            return std::make_pair(iterator(nodeptrInserting), !(key_exists));
        }

        return std::make_pair(iterator(node_parent), !(key_exists)); // value with the same key already exists
    }
    // TODO
    iterator insert (const_iterator pos, const_reference value) { // TODO

    }

    void insert (std::initializer_list<Ity_> ilist) {}  // TODO
    
    std::pair<iterator, bool> insert_or_assign (const key_type &key, const mapped_type &item) {
        assert (size_ < SIZE_MAX );

        Nodeptr node = root_;
        Nodeptr node_parent = root_;

        // TODO
        // Nodeptr node_p = root_;
        // Nodeptr node_c = (key > node_p->getKey() : node_p->getRight() : node_p->getLeft());
        
        bool key_exists = false;  // is node with the same key already exsists in the tree
        bool is_right_child = false; // is inserting value would be a right child of his parent  


        while ( node != nullptr ) {
            node_parent = node;

            if ( key > node->getKey() ) {
                node = node->getRight();
                is_right_child = true;
            }
            else if ( key == node->getKey() ) {
                key_exists = true;
                break;
            }
            else {
                node = node->getLeft();
                is_right_child = false;
            }
        }

        if (key_exists != true) { // value with the same key doens't exists 
            Nodeptr nodeptrInserting = new TreeNode<const Kty_, Ity_>(
                                                                      std::map<Kty_, Ity_>(key, item),
                                                                     (size_ > 0 ? node_parent->getHeight() + 1 : 1),
                                                                      node_parent, nullptr, nullptr
                                                                     );

            if ( size_ > 0 ) { 
                (is_right_child) ? node_parent->setRight(nodeptrInserting) : node_parent->setLeft(nodeptrInserting);
            }
            else {
                root_ = nodeptrInserting;
            }
            
            size_++;
            return std::make_pair(iterator(nodeptrInserting), !(key_exists));
        }
        else {
            node->setItem(item);
        }

        return std::make_pair(iterator(node_parent), !(key_exists)); // value with the same key already exists
    } // TODO

    iterator erase (const_iterator pos) {
        // return iterator(_ERASE_NODE( static_cast<Nodeptr>(*pos) )); // TODO
        this->_ERASE_NODE( static_cast<Nodeptr>( &(*pos) ) );
    }

    // O(h) 
    Nodeptr _ERASE_NODE (Nodeptr nodeptrErasing) { // TODO: const_iterator // 
        // case 1: no child 
        // case 2: only child
        // case 3: two children
        
        Nodeptr nodeptrTmp = nodeptrErasing;

        if ( nodeptrErasing->getRight() == nullptr && nodeptrErasing->getLeft() == nullptr) { // case 1
            nodeptrTmp = nodeptrErasing->getParent();
            _DELETE_NODE_UNCHECK(nodeptrErasing);

            return nodeptrTmp;
        } 
        else if ( nodeptrErasing->getRight() != nullptr || nodeptrErasing->getLeft() != nullptr ) { // case 2
            nodeptrTmp = nodeptrErasing->getChild();
            _SWAP_NODES_VALUES(nodeptrTmp, nodeptrErasing);
            _DELETE_NODE_UNCHECK(nodeptrTmp);

            return nodeptrErasing;

        }   
        else { // case 3
            nodeptrTmp = _MIN(nodeptrErasing->getRight());
            _SWAP_NODES_VALUES(nodeptrTmp, nodeptrErasing);
            _DELETE_NODE_UNCHECK(nodeptrTmp);

            return nodeptrErasing;
        }
    }

    // O(h * std::ptrdiff_t(first, last))
    iterator erase (const_iterator first, const_iterator last) {  
        while (first != last) {
            // this->_ERASE_NODE( static_cast<Nodeptr>(*first) ); // TODO
            this->_ERASE_NODE( static_cast<Nodeptr>( &(*first) ) ); 
            first++;
        }

        return const_cast<iterator>(last);
    }

    // O(h + cont.count(key)) ~ O(h)
    size_t erase (const key_type &key) {

        auto nodeptrErasing = _FIND(root_, key);

        if ( nodeptrErasing != nullptr ) {
            this->_ERASE_NODE(nodeptrErasing);
            return 1;
        }

        return 0;
    }

    // O(1)
    void swap (BinarySearchTree &other) noexcept { // TODO: move constructor or somthing like that
        if (this != IMPL::MY_BASE::addressof(other)) { 
            MY_BASE::swap(this->size_, other.size_);
            MY_BASE::swap(*(this->root_), *(other.root_));
        }
    }

    // O(1)
    size_t count (const key_type &key) const noexcept {
        return static_cast<size_t>(contains(key)); // return 0 or 1
    } 

protected:

    // O(1)
    Nodeptr _INSERT(Nodeptr parentptr, const_reference value) {
        
        Nodeptr nodeptrInserting = new TreeNode<Kty_, Ity_>(
                                                            value,
                                                            (parentptr == nullptr ? 1 : parentptr->getHeight() + 1),
                                                            parentptr, nullptr, nullptr);
        if (parentptr != nullptr) {
            value.first > parentptr->getKey() ? parentptr->setRight(nodeptrInserting) : parentptr->setLeft(nodeptrInserting);
        }
        else {
            root_ = nodeptrInserting;
        }

        size_++;

        return nodeptrInserting;
    }

    // O(h)
    void _CLEAR_SUBTREE (Nodeptr subTreeRoot) noexcept {
        if (subTreeRoot == nullptr) { // recursion stop point 
            return;
        }
        else { // recursion base
            if (subTreeRoot->getLeft() != nullptr && subTreeRoot->getRight() != nullptr) {
                delete subTreeRoot;
                subTreeRoot = nullptr;
            }
            else { // recursion step
                _CLEAR_SUBTREE(subTreeRoot->getLeft());
                _CLEAR_SUBTREE(subTreeRoot->getRight());
            }
        }

    }

    // O(h) 
    void _INSERT (Nodeptr parent, reference value) noexcept {
        if (parent == nullptr) {
            Nodeptr node = new TreeNode<const Kty_, Ity_>(value, parent);

        }
        // parent->getKey() > value.first ? parent->setRight(TreeNode<Kty_, Ity_> *right)

    }

    // O(1)
    void _DELETE_NODE_UNCHECK (Nodeptr node) noexcept { // TODO does assert have access to private fields c++
        // assert(node->getRight() == nullptr && node->getLeft() != nullptr);

        delete node;
        node = nullptr;
    } 

    // O(1); 
    void _SWAP_NODES_VALUES (Nodeptr a, Nodeptr b) {  
        assert(a != nullptr && b != nullptr);
        // MY_BASE::swap(*a, *b);

        auto tmp = *a;
        a->setValue(*b);
        b->setValue(tmp);
    }

    // O(h), h - height of the tree
    Nodeptr _FIND (const Nodeptr subTreeRoot, const Kty_ &key) const noexcept {
        if ( subTreeRoot == nullptr ) {
            return nullptr;
        }
        else if ( subTreeRoot->getKey() == key ) {
            return subTreeRoot;
        }
        else if ( subTreeRoot->getKey() > key ) {
            return _FIND(subTreeRoot->getLeft(), key);
        }
        else {
            return _FIND(subTreeRoot->getRight(), key);
        }
    }

    // O(h)
    Nodeptr _MAX (const Nodeptr subTreeRoot) const noexcept {
        // assert(root_ != nullptr); // is empty tree
        
        if ( subTreeRoot == nullptr ) { return subTreeRoot; }
        
        Nodeptr result = subTreeRoot; // TODO static or dynamic
        while ( true ) {
            if ( result->getRight() == nullptr ) {
                break;
            }
            else {
                result = result->getRight();
            }
        }

        return result;
    }

    // O(h)
    Nodeptr _MIN (const Nodeptr subTreeRoot) const noexcept {
        // assert(root_ != nullptr); // is empty tree
        
        if ( subTreeRoot == nullptr ) { return subTreeRoot; }
        
        Nodeptr result = subTreeRoot;
        while ( true ) {
            if ( result->getLeft() == nullptr ) {
                break;
            }
            else {
                result = result->getLeft();
            }
        }

        return result;
    }

public:

    // O(h)
    iterator find (const key_type &key) {
        return iterator(_FIND(root_, key));
    }

    // O(h)
    const_iterator find (const key_type &key) const {
        return const_iterator(_FIND(root_, key));
    }

    // O(h)
    bool contains (const key_type &key) const {
        return (_FIND(root_, key) != nullptr);
    }

protected:

    // O(h), h - height of the tree; not less; the key of found node mustn't equals kye 
    Nodeptr _FIND_LOWER_BOUND (Nodeptr node, const key_type &key) const { 
       
        assert(node != nullptr);   // is value with that key exists

        if ( node->right != nullptr ) 
        {
            node = node->_right;
            
            while ( true )
            {
                if ( node->_left != nullptr ) {
                    node = node->_left;
                }
                else { break; } 
            }

            return node; 
        } 
        else if (node == _MAX()) { return node->_parent; }
        else {

            auto parent_node = node->_parent;

            if (node == parent_node->_left) // node is MIN in subTree
            {
                return parent_node->_right;
            }
            else {                          // node is MAX in subTree
                return node->_parent->_parent; 
            }
        }
        
        return this->end();
    }

    // O(h); return firts greater; equivalent _FIND_LOWER_BOUND because of container doesn't allow store
                                // value_types with the same keys
    Nodeptr _FIND_UPPER_BOUND (Nodeptr node, const key_type &key) const {
        return _FIND_LOWER_BOUND(node, key);  
    }

public:
    
    iterator lower_bound (const key_type &key) {
        auto node = _FIND(root_, key);
        
        return iterator(_FIND_LOWER_BOUND(node, key));
    }

    const_iterator lower_bound (const key_type &key) const {
        auto node = _FIND(root_, key);
        
        return const_iterator(_FIND_LOWER_BOUND(node, key));
    }

    iterator upper_bound (const key_type &key) {
        auto node = _FIND(root_, key);
        
        return iterator(_FIND_UPPER_BOUND(node, key));
    }
    const_iterator upper_bound (const key_type &key) const { 
        auto node = _FIND(root_, key);
        
        return const_iterator(_FIND_UPPER_BOUND(node, key));
    }

    void print (Nodeptr node) const noexcept {
        if (node == nullptr) {
            return;
        }

        print(node->getLeft());
        std::cout << node->getItem() << " ";
        
        print(node->getRight());
    }



protected:
    Nodeptr  root_;
    size_t   size_;
};





int main() {
    

    //TreeNode<int> node(1);
    //std::cout << node.getData();
    
    
    // std::map<int, int>;

    BinarySearchTree<int,int> bstree;
    bstree.insert( std::make_pair<int,int>(1,1) );
    bstree.insert( std::make_pair<int,int>(9,9) );  
    bstree.insert( std::make_pair<int,int>(8,8) );  
    bstree.insert( std::make_pair<int,int>(1,1) );
    bstree.insert( std::make_pair<int,int>(2,2) );
    bstree.insert( std::make_pair<int,int>(7,7) );  
    bstree.insert( std::make_pair<int,int>(3,3) );
    bstree.insert( std::make_pair<int,int>(6,6) );  
    bstree.insert( std::make_pair<int,int>(4,4) );  
    bstree.insert( std::make_pair<int,int>(10,10) );  
    bstree.insert( std::make_pair<int,int>(3,3) );
    bstree.insert( std::make_pair<int,int>(11,11) );  
    bstree.insert( std::make_pair<int,int>(5,5) );  

    bstree.print(bstree.getRoot()); 
    std::cout << '\n' << "bstree count: " << bstree.size() << '\n';

    // bstree.erase(1);
    // bstree.erase(6);

    // bstree.print(bstree.getRoot());

    // BinarySearchTree<int,int> tree;
    // tree.insert( std::make_pair<int,int>(7,7) );  
    // tree.insert( std::make_pair<int,int>(1,1) );
    // tree.insert( std::make_pair<int,int>(9,9) );  
    // tree.insert( std::make_pair<int,int>(3,3) );
    // tree.insert( std::make_pair<int,int>(8,8) );  
    // tree.insert( std::make_pair<int,int>(1,1) );
    // tree.insert( std::make_pair<int,int>(6,6) );  
    // tree.insert( std::make_pair<int,int>(2,2) );

    // tree.print(tree.getRoot());
    // std::cout << '\n' << "tree count" << tree.size() << '\n';

    // tree.swap(bstree);

    // bstree.print(bstree.getRoot()); 
    // std::cout << '\n' << "bstree count" << bstree.size() << '\n';
    
    // tree.print(tree.getRoot());
    // std::cout << '\n' << "tree count" << tree.size() << '\n';


    return 0;
}




















