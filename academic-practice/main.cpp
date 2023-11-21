#include <iostream>
#include <map>
#include <vector>

#include "view.hpp"


#define TASK_2_1 1
#define TASK_2_2 1
#define TASK_2_3 1
#define TASK_2_4 1
#define TASK_2_5 1
#define TASK_2_6 1


int main() {

    alias::laptop_map lmap = create_laptop_map(13);


    alias::laptop_multimap lmmap(lmap.begin(), lmap.end());
    lmmap.emplace(laptop_key("Factory 1", "Model 1"), laptop());
    lmmap.emplace(laptop_key("Factory 1", "Model 1"), laptop());
    lmmap.emplace(laptop_key("Factory 2", "Model 2"), laptop());
    lmmap.emplace(laptop_key("Factory 2", "Model 2"), laptop());


#if TASK_2_1
        msl::print(lmap);

        task2_1_1_presentation(13);
        task2_1_2_presentation(lmap);
        msl::print(lmap);
        task2_1_4_presentation(lmap);
        task2_1_5_presentation(lmap);
        task2_1_6_presentation(lmap);
#endif

#if TASK_2_2
        msl::print(lmmap);

        task2_2_1_presentation();
        task2_2_2_presentation(lmmap);
        task2_2_4_presentation(lmmap);
        task2_2_7_presentation(lmmap, {"Factory 1", "Model 1"});
#endif

#if TASK_2_3
        task2_3_presentation(13);
#endif

#if TASK_2_4
        task2_4presentation();
#endif

#if TASK_2_5
        task2_5presentation();
#endif

#if TASK_2_6
        // [NOTE]: Store not laptops, but ints to easier
        //         representation, all we need from stored
        //         type 1. it should be object type
        //              2. operator< or other binary compare Predicate
        task2_6_presentation();
#endif
}
