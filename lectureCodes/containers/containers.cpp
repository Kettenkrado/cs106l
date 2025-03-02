#include <map>
#include <set>
#include <iostream>
#include <string>

struct MyType {
    int tomorrow;
};

struct Less {
    bool operator()(const MyType& a, const MyType& b) {
        // Return true if `a` is less than `b`
    }
};

auto comp = [](const MyType& a, const MyType& b){ 
    // Return true if `a` is less than `b`
};

int main() {
    std::map<std::string, std::string> famous {
        { "Bjarne", "Stroustrup" },
        { "Herb", "Sutter" },
        { "Alexander", "Stepanov" }
    };

    for (const auto& [key, value] : famous) {
    std::cout << key << ": " << value << std::endl;
    }

    // Output (notice keys are sorted):
    //  Alexander: Stepanov
    //  Bjarne: Stroustrup
    //  Herb: Sutter

    std::map<MyType, double, decltype(comp)> my_map1(comp);
    std::set<MyType, decltype(comp)> my_set1(comp);

    std::map<MyType, double, Less> my_map;
    std::set<MyType, Less> my_set; 

    return 0;
}