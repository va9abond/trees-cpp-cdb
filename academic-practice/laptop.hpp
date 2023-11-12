#ifndef LAPTOP_HPP
#define LAPTOP_HPP


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

bool operator== (const laptop& Lhs, const laptop& Rhs) {
    return Lhs.id == Rhs.id;
}


bool operator< (const laptop& Lhs, const laptop& Rhs) {
    return Lhs.id < Rhs.id;
}


struct laptop_key {
    laptop_key (std::string_view factory_ = "unknown", std::string_view model_ = "unknown") :
        factory(factory_),
        model(model_)
    {}

    bool operator< (const laptop_key& Rhs) const noexcept {
        if (factory != Rhs.factory) {
            return factory < Rhs.factory;
        } else if (model != Rhs.model) {}
        return model < Rhs.model;
    }

    const std::string factory;
    const std::string model;
};

#if 0
bool operator== (const laptop_key& Rhs, const laptop_key Lhs) {
    return (Lhs.factory == Rhs.factory && Lhs.model == Rhs.model);
}
#endif

#if 0
bool operator< (const laptop_key& Lhs, const laptop_key& Rhs) {
    if (Lhs.factory != Rhs.factory) {
        return Lhs.factory < Rhs.factory;
    }
    return Lhs.model < Rhs.model;
}
#endif


namespace alias {
    using laptop_map = std::map<laptop_key, laptop>;
    using laptop_multimap = std::multimap<laptop_key, laptop>;
    using lm_const_iter = std::map<laptop_key, laptop>::const_iterator;
    using lm_iter = std::map<laptop_key, laptop>::iterator;
    using lmm_const_iter = std::multimap<laptop_key, laptop>::const_iterator;
    using lmm_iter = std::multimap<laptop_key, laptop>::iterator;
}

namespace msl {
    inline void print (const laptop& lap) {
        using std::cout;
        using std::right;
        using std::left;

        printf("\n==============================\n");
        cout.width(30); cout << right << std::format("(id: {})", lap.id) << "\n";

        cout.width(10); cout << left << "Price: ";    cout << lap.price    << "\n";
        cout.width(10); cout << left << "Diagonal: "; cout << lap.diagonal << "\n";
        cout.width(10); cout << left << "Cores: ";    cout << lap.coresNum << "\n";
        cout.width(10); cout << left << "Ram: ";      cout << lap.ram      << "\n";
        printf("==============================\n");
    }


    inline void print (const laptop_key& key) {
        using std::cout;
        using std::right;
        using std::left;

        printf("\n==============================\n");
        cout.width(9); cout << left << "Factory: "; cout << key.factory << "\n";
        cout.width(9); cout << left << "Model: ";   cout << key.model   << "\n";
        printf("==============================\n");
    }


    template <
        class Iter_t = alias::laptop_map::const_iterator
    >
    inline void print (Iter_t iter) {
        using std::cout;
        using std::right;
        using std::left;
        // const laptop_key& key = iter->first;
        // const laptop& value = iter->second;
        const auto& [key, value] = *iter;

        printf("\n==============================\n");
                                            // print key
        cout.width(30); cout << right << "KEY" << "\n";
        cout.width(9);  cout << left << "Factory: "; cout << key.factory << "\n";
        cout.width(9);  cout << left << "Model: ";   cout << key.model   << "\n";

                                          // print value
        cout.width(30); cout << right << "VALUE" << "\n";
        cout.width(30); cout << right << std::format("(id: {})", value.id) << "\n";
        cout.width(10); cout << left << "Price: ";    cout << value.price    << "\n";
        cout.width(10); cout << left << "Diagonal: "; cout << value.diagonal << "\n";
        cout.width(10); cout << left << "Cores: ";    cout << value.coresNum << "\n";
        cout.width(10); cout << left << "Ram: ";      cout << value.ram      << "\n";
        printf("==============================\n");
    }


    inline void print (const alias::laptop_map& map) {
        using std::cout;
        using std::right;
        using std::left;
                                              // C++98 Style
#if 1
        for (
            alias::laptop_map::const_iterator iter = map.begin();
            iter != map.end();
            ++iter
        ) {
            cout << "Model: "; cout.width(8); cout << left << iter->first.model
                 << " | ";
            cout << "id: "; cout.width(2); cout << iter->second.id << "\n";
        }
#endif
                                              // C++17 Style
#if 0
        for (const auto& [key, value] : map) {
            cout << "Model: "; cout.width(8); cout << left << key.model
                 << " | ";
            cout << "id: "; cout.width(2); cout << value.id << "\n";
        }
#endif
    }


    inline void print (const alias::laptop_multimap& multimap) {
        using std::cout;
        using std::right;
        using std::left;
                                              // C++98 Style
#if 0
        for (
            alias::lmm_const_iter iter = multimap.begin();
            iter != map.end();
            ++iter
        ) {
            cout << "Model: "; cout.width(8); cout << left << iter->first.model
                 << " | ";
            cout << "id: "; cout.width(2); cout << iter->second.id << "\n";
        }
#endif
                                              // C++17 Style
#if 1
        for (const auto& [key, value] : multimap) {
            cout << "Model: "; cout.width(8); cout << left << key.model
                 << " | ";
            cout << "id: "; cout.width(2); cout << value.id << "\n";
        }
#endif
    }


    inline void print (const std::vector<laptop>& laptops) {
        using std::cout;
        using std::right;
        using std::left;

        std::cout << "{";
        for (const auto& lap : laptops) {
            std::cout << " " << lap.id;
        }
        std::cout << " }\n";
    }
}


#endif // LAPTOP_HPP
