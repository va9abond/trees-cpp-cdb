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

int main() {
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
