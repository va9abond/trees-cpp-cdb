#include <iostream>
#include <map>
#include <vector>

#include "view.hpp"
#include "tree.hpp"


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
#if 1
    alias::laptop_map lmap = create_laptop_map(13);
    msl::print(lmap);

    // std::cout << recursin(10);
    // std::cout << std::max(1,1);

    // auto it1 = lmap.begin();
    // auto it2 = std::next(it1);

    // Tree_traits<laptop_key, laptop, std::less<laptop_key>> tr{};
    // msl::print(tr.Kfn(*it1));
    // msl::print(tr.Kfn(*it2));


    avltree<int, int> tree;
    tree.emplace(51,  12);
    tree.emplace(924, 32094);
    tree.emplace(3,   80);
    tree.emplace(23,  91);
    tree.emplace(12,  15);
    tree.emplace(83,  42);
    tree.emplace(13,  13);
    tree.emplace(1,   4);
    tree.emplace(99,  34);
    tree.emplace(99, 233);

    auto iter = tree.begin();
    while (iter != tree.end()) {
        printf("{%d, %d}, h = %u\n", iter->first, (*iter).second, iter.Myptr->Height);
        ++iter;
    }


    // std::function<void(const std::pair<const int, int>&)> Pred = [](const std::pair<const int, int>& p) {
    //                                                             printf("(%d): %d", p.first, p.second);
    //                                                         };
    // tree.print_tree(Pred);

    // alias::laptop_multimap lmmap(lmap.begin(), lmap.end());
    // lmmap.emplace(laptop_key("Factory 1", "Model 1"), laptop());
    // lmmap.emplace(laptop_key("Factory 1", "Model 1"), laptop());
    // lmmap.emplace(laptop_key("Factory 2", "Model 2"), laptop());
    // lmmap.emplace(laptop_key("Factory 2", "Model 2"), laptop());
    //
    // msl::print(lmmap);
#endif
    // std::pair<int, int> a{1,323};
    // auto it1 = lmap.end();
    // --it1;
    // msl::print(it1);
    // it1 = lmap.end();
    // auto it2 = lmap.end();
    // ++it2;
    // msl::print(it2);
    // if (++it2 == lmap.end()) {
    //     std::cout << "LFJDLKFJSDLKJF";
    // }
    // msl::print(lmap.begin());


    // using Pred = std::less<laptop_key>;

    // auto key1 = laptop_key("Factory 1", "Model 1");
    // auto key2 = laptop_key("Factory 2", "Model 2");
    // if (Pred{}(

    // if (
    //             laptop_key("Factory 1", "Model 1") <
    //             laptop_key("Factory 2", "Model 2")
    // ) {
    //     std::cout << "\n==== HEI ====\n";
    // }


#if 0
    task2_1_1_presentation(13);
    task2_1_2_presentation(lmap);
    msl::print(lmap);
    task2_1_4_presentation(lmap);
    task2_1_5_presentation(lmap);
    task2_1_6_presentation(lmap);
#endif

#if 0
    task2_2_1_presentation();
    task2_2_2_presentation(lmmap);
    task2_2_4_presentation(lmmap);
    task2_2_7_presentation(lmmap, {"Factory 1", "Model 1"});
#endif

#if 0
    task2_3_presentation(13);
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
