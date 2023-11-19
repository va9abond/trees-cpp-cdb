#include <iostream>
#include <map>
#include <vector>

#include "view.hpp"
#include "avltree.hpp"


int recursin (int v) {
    static int val = 555;
    if (v == 0) {
        return val;
    } else {
        printf("v: %d\n", v);
        if (val == 555) {
            printf("DKLFJDKFJDKLJFDLKJF\n");
        }
        val = v + 1;
        return recursin(v-1);
    }
}

int main()
{
#if 0

    std::cout << recursin(10);
    std::cout << std::max(1,1);

    auto it1 = lmap.begin();
    auto it2 = std::next(it1);

    Tree_traits<laptop_key, laptop, std::less<laptop_key>> tr{};
    msl::print(tr.Kfn(*it1));
    msl::print(tr.Kfn(*it2));


    avltree<int, int> tree;
    std::cout << (tree.Is_equivalent(3, 4) ? "yes" : "no") << "\n";
    tree.emplace(51,  12);
    tree.print_tree();
    tree.erase(4241);
    tree.print_tree();
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

    auto iter = tree.begin();
    while (iter != tree.end()) {
        printf("{%d, %d}, h = %u\n", iter->first, (*iter).second, iter.Myptr->Height);
        ++iter;
    }

    tree.print_tree();

    printf("\n");
    iter = tree.end();
    auto& key1 = iter.Myptr->Left->Myval.first;
    printf("(%d)\n", key1);
    auto& key2 = iter.Myptr->Right->Myval.first;
    printf("(%d)\n", key2);


    tree.erase(1000);
    tree.print_tree();
    tree.erase(924);
    tree.print_tree();
    tree.erase(12);
    tree.print_tree();
    tree.erase(99);
    tree.print_tree();
    tree.erase(99);
    tree.print_tree();
    tree.erase(23);
    tree.print_tree();

    traversal_order_tag inorder = traversal_order_tag::in_order;
    tree.traversal<inorder,>();

    tree.erase(12);
    tree.print_tree();
    tree.erase(1);
    tree.print_tree();

    printf("\n===============================\n");
    std::cout << (tree.find(13).Myptr)->Parent->Myval.first;
    printf("\n===============================\n");

    tree.erase(3);
    tree.print_tree();
    tree.erase(99);
    tree.print_tree();


    iter = tree.begin();
    while (iter != tree.end()) {
        printf("{%d, %d}, h = %u\n", iter->first, (*iter).second, iter.Myptr->Height);
        ++iter;
    }

    iter = tree.begin();
    while (iter != tree.end()) {
        printf("ERASE: %d\n", iter->first);
        const auto& [it, success] = tree.erase(iter->first);
        if (success == false) {
            printf("\nSTOP STOP STOP STOP STOP STOP STOP STOP STOP\n");
        }
        tree.print_tree();
        iter = it;
    }
    while (iter != tree.begin()) {
        --iter;
    }

    std::cout << tree.max_size();


    std::function<void(const std::pair<const int, int>&)> Pred = [](const std::pair<const int, int>& p) {
                                                                printf("(%d): %d", p.first, p.second);
                                                            };
    tree.print_tree(Pred);

    alias::laptop_multimap lmmap(lmap.begin(), lmap.end());
    lmmap.emplace(laptop_key("Factory 1", "Model 1"), laptop());
    lmmap.emplace(laptop_key("Factory 1", "Model 1"), laptop());
    lmmap.emplace(laptop_key("Factory 2", "Model 2"), laptop());
    lmmap.emplace(laptop_key("Factory 2", "Model 2"), laptop());

    msl::print(lmmap);

    std::pair<int, int> a{1,323};
    auto it1 = lmap.end();
    --it1;
    msl::print(it1);
    it1 = lmap.end();
    auto it2 = lmap.end();
    ++it2;
    msl::print(it2);
    if (++it2 == lmap.end()) {
        std::cout << "LFJDLKFJSDLKJF";
    }
    msl::print(lmap.begin());


    using Pred = std::less<laptop_key>;

    auto key1 = laptop_key("Factory 1", "Model 1");
    auto key2 = laptop_key("Factory 2", "Model 2");
    if (Pred{}(

    if (
                laptop_key("Factory 1", "Model 1") <
                laptop_key("Factory 2", "Model 2")
        STD::COUT << "\N==== HEI ====\N";
    }
    ) {
#endif

alias::laptop_map lmap = create_laptop_map(13);
msl::print(lmap);


alias::laptop_multimap lmmap(lmap.begin(), lmap.end());
lmmap.emplace(laptop_key("Factory 1", "Model 1"), laptop());
lmmap.emplace(laptop_key("Factory 1", "Model 1"), laptop());
lmmap.emplace(laptop_key("Factory 2", "Model 2"), laptop());
lmmap.emplace(laptop_key("Factory 2", "Model 2"), laptop());


msl::print(lmmap);

#if 1
    task2_1_1_presentation(13);
    task2_1_2_presentation(lmap);
    msl::print(lmap);
    task2_1_4_presentation(lmap);
    task2_1_5_presentation(lmap);
    task2_1_6_presentation(lmap);
#endif

#if 1
    task2_2_1_presentation();
    task2_2_2_presentation(lmmap);
    task2_2_4_presentation(lmmap);
    task2_2_7_presentation(lmmap, {"Factory 1", "Model 1"});
#endif

#if 1
    task2_3_presentation(13);
#endif

#if 1
    task2_4presentation();
    task2_5presentation();
#endif

    // Tree_node<laptop> node1;
    // msl::print(node1.Myval);

    // auto node2 = Tree_node<laptop_key>::Buy_node(nullptr, "ddfa", "dfjw");
    // auto node3 = Tree_node<laptop_key>::Buy_node(nullptr, "213", "cnwooj;");
    //
    // msl::print(node2->Myval);
    // msl::print(node3->Myval);
    //
    // Tree_node<laptop_key>::Free_node(node2);
    // Tree_node<laptop_key>::Free_node(node3);
    // std::set<laptop_key> set;
    // set.emplace("djlfsjd", "fjladkfj");
    // msl::print(*set.begin());
}
