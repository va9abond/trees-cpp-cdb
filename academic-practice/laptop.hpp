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
    laptop (std::string model_ = "unknown") :
        model(model_),
        price(msl::rand<double>(1.0, 1000.99)[0]),
        diagonal(msl::rand<double>(1.0, 20.11)[0]),
        coresNum(msl::rand<int>(1, 100)[0]),
        ram(msl::rand<int>(1,100)[0]),
        id(id_generator())
    {}

private:
    static int id_generator() {
        static int id = 0;
        return ++id;
    }

public:
    const   std::string model;
            double      price;
    const   double      diagonal;
    mutable int         coresNum;
            int         ram;
    const   int         id;

private:
    static int laptop_id;
};


namespace msl {
    inline void print (const laptop& lap) {
        using std::cout;
        using std::right;
        using std::left;

        printf("\n==============================\n");
        cout.width(10); cout << left << "Laptop: "; cout << lap.model;

        cout.width(30-lap.model.size()+1-10); cout << right << std::format("(id: {})\n", lap.id);

        cout.width(10); cout << left << "Price: ";    cout << lap.price    << "\n";
        cout.width(10); cout << left << "Diagonal: "; cout << lap.diagonal << "\n";
        cout.width(10); cout << left << "Cores: ";    cout << lap.coresNum << "\n";
        cout.width(10); cout << left << "Ram: ";      cout << lap.ram      << "\n";
        printf("==============================\n");
    }
}

#endif // LAPTOP_HPP
