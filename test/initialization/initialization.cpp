#include <iostream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

struct IDCard {
    std::string name;
    int number;
    std::string email;
};

std::tuple<std::string, std::string, std::string> getClassInfo();

int main() {
    // direct initialization
    int foo = 12.08; // double will be turned into int
    int foo1(12.99); // throw the fraction part, a narrowing conversion
    cout << foo << ' ' << foo1 << endl;

    // uniform initializtion
    IDCard id { "Miguel de Cervantes", 1605, "miguel@quijote.edu" };
    cout << id.name << ' ' << id.number << ' ' << id.email << endl;
    auto [var1, var2, var3] = id;

    std::vector<int> v{1, 2, 3, 4, 5};

    std::map<std::string, int> ages{
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 35}
    };

    // Accessing map elements
    std::cout << "Alice's age: " << ages["Alice"] << std::endl;
    std::cout << "Bob's age: " << ages.at("Bob") << std::endl;

    auto [className, location, language] = getClassInfo();
    std::cout << "Join us " << location << " for " << className << " to learn " << language << "!" << std::endl;
    return 0;

    return 0;
}

std::tuple<std::string, std::string, std::string> getClassInfo() {
    std::string className = "CS106L";
    std::string location = "online";
    std::string language = "C++";
    return {className, location, language};
}