#ifndef LAPTOP_HPP
#define LAPTOP_HPP


#include <cstdlib>
#include <iostream>
#include <format>
#include <string>
#include <random>
#include "myutils.hpp"


class laptop {
public:
#if 1
    laptop () :
        price(msl::rand<double>(1.0, 1000.99)[0]),
        diagonal(msl::rand<double>(1.0, 20.11)[0]),
        coresNum(msl::rand<int>(1, 100)[0]),
        ram(msl::rand<int>(1,100)[0]),
        id(id_generator())
    {}
#endif

#if 0
    laptop () :
        price(msl::random<double>(1.0, 1000.99)),
        diagonal(msl::random<double>(1.0, 20.11)),
        coresNum(msl::random<int>(1,100)),
        ram(msl::random<int>(1,100)),
        id(id_generator())
    {}
#endif

private:
    static int id_generator() { // mb I should remove static here, it's about design
        static int id = 0;
        return ++id;
    }

public:
            double      price;
    const   double      diagonal;
    mutable int         coresNum;
    mutable int         ram;
    const   int         id;
};


namespace msl {
    inline void print (const laptop& lap) {
        using std::cout;
        using std::right;
        using std::left;

        printf("\n==============================\n");
        // cout.width(10); cout << left << "Factory: "; cout << lap.factory << "\n";
        // cout.width(10); cout << left << "Model: "; cout << lap.model;

        cout.width(30); cout << right << std::format("(id: {})", lap.id) << "\n";

        cout.width(10); cout << left << "Price: ";    cout << lap.price    << "\n";
        cout.width(10); cout << left << "Diagonal: "; cout << lap.diagonal << "\n";
        cout.width(10); cout << left << "Cores: ";    cout << lap.coresNum << "\n";
        cout.width(10); cout << left << "Ram: ";      cout << lap.ram      << "\n";
        printf("==============================\n");
    }
}

#endif // LAPTOP_HPP
