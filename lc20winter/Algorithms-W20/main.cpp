/*
 * Lecture code for Lecture 8, Functions and Algorithms.
 *
 * Avery Wang - last updated 1/29/2020
 */

#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>

// We will represent a course on Carta/explorecourses with this struct.
struct Course {
    std::string name;
    double rating;
};

// This function allows you to print a Course struct to any ostream.
// Usage: std::cout << c << std::endl;
// We'll cover how to overload operators in about a week.
std::ostream& operator<<(std::ostream& os, const Course& c) {
    os << std::setw(15) << std::setfill(' ') << c.name << "   " << c.rating;
    return os;
}

// This is the function template we wrote last lecture.
// Solves the problem "how many times does [type] [val] appear in [range of elements]"
template <typename InputIt, typename UniPred>
int countOccurences(InputIt begin, InputIt end, UniPred pred) {
    int count = 0;
    for (auto iter = begin; iter != end; ++iter) {
        if (pred(*iter)) ++count;
    }
    return count;
}

bool equals5(int val) { return val == 5; }

// A predicate function that is specialized to limit = 5.
bool isLessThan5(int val) {
    return val < 5;
}

// A predicate function, returns true if val < limit, false otherwise.
bool isLessThanLimit(int val, int limit) {
    return val < limit;
}

// A function which returns a fixed vector.
// This is just a quick survey of common courses.
// Sorry for the bias towards the CS core.
std::vector<Course> readCourses() {
    std::vector<Course> v = {{"CS 106A", 4.4337}, {"CS 106B", 4.4025},
        {"CS 107", 4.6912}, {"CS 103", 4.0532},
        {"CS 109", 4.6062}, {"CS 110", 4.343},
        {"Math 51", 3.6119}, {"Math 52", 4.325},
        {"Math 53", 4.3111}, {"Econ 1", 4.2552},
           {"Anthro 3", 3.71}, {"Educ 342", 4.55},
           {"Chem 33", 3.50}, {"German 132", 4.83},
           {"Econ 137", 4.84}, {"CS 251", 4.24},
           {"TAPS 103", 4.79}, {"Music 21", 4.37},
           {"English 10A", 4.41}};
    std::random_shuffle(v.begin(), v.end());
    return v;
}

// A function which returns a vector of a bunch of numbers.
std::vector<double> readNumbers() {
    std::vector<double> numbers;
    std::generate_n(std::back_inserter(numbers), 500, std::rand);
    return numbers;
}

int main() {
    // Count how many times 5 appears in the second half of a vector<int>.
    std::vector<int> phoneNumber{5, 5, 5, 8, 2, 6, 5, 5, 3, 5};
    int times1 = countOccurences(phoneNumber.begin() + phoneNumber.size()/2,
                                 phoneNumber.end(), equals5);
    std::cout << "the second half of phoneNumber contains " << times1
              << " elements of 5" << std::endl;

    // Count how many elements in the second half of a vector<int> are less than 5.
    // int times2 = 0; // TODO: Edit this
    int times2 = countOccurences(phoneNumber.begin() + phoneNumber.size()/2,
                    phoneNumber.end(), isLessThan5);
    std::cout << "the second half of phoneNumber contains " << times2
              << " elements that are at less than 5" << std::endl;

    // Fun with algorithms.
    auto courses = readCourses();
    auto numbers = readNumbers();
    // original sorting
    std::copy(courses.begin(), courses.end(),
              std::ostream_iterator<Course>(std::cout, "\n"));

    // Your code with algorithms
    // 1. find the middle number by value, old ways
    std::sort(numbers.begin(), numbers.end());
    std::cout << "the first number is "
              << numbers.at(0) << std::endl;
    std::cout << "the middle number is "
              << numbers.at(numbers.size() / 2) << std::endl;
    std::cout << "the last  number is "
              << numbers.at(numbers.size() - 1) << std::endl;

    auto compareRating = [](const Course& a, const Course& b) {
        return a.rating < b.rating;
    };
    // std::sort(courses.begin(), courses.end(), compareRating);
    // 2. one way of output as above
    // std::copy(courses.begin(), courses.end(),
    //           std::ostream_iterator<Course>(std::cout, "\n"));

    // 3. the nth element function
    std::nth_element(courses.begin(), courses.begin() + courses.size() / 2, courses.end(), compareRating);
    std::cout << "the middle rating class is "
              << courses[courses.size() / 2] << std::endl;

    // 4. stable partition
    std::string dep = "CS";
    auto isDep = [dep](const auto& course) {
        return course.name.size() >= dep.size() &&
               course.name.substr(0, dep.size()) == dep;
    };
    auto iter = std::stable_partition(courses.begin(),
                                      courses.end(), isDep);
    std::copy(courses.begin(), courses.end(),
              std::ostream_iterator<Course>(std::cout, "\n"));
    // erase anything not "CS" begun
    // courses.erase(iter, courses.end());
    // std::copy(courses.begin(), courses.end(),
    //          std::ostream_iterator<Course>(std::cout, "\n"));

    // 5. copy if
    std::vector<Course> csCourses;
    // std::copy_if(Courses.begin(), Courses.end(),
    //              csCourses, isDep);
    // unitialised vector has limited space
    std::copy_if(courses.begin(), courses.end(),
                 back_inserter(csCourses), isDep);
    std::cout << "copy if will not erase the copied items" << std::endl;
    std::copy(csCourses.begin(), csCourses.end(),
              std::ostream_iterator<Course>(std::cout, "\n"));

    // FILL IN YOUR CODE HERE
    int times_called = 0;
    std::vector<int> vec{1, 3, 5, 7, 9};
    int limit = 5;
    auto lessThanLimit = [limit, &times_called](auto val) -> bool {
        ++times_called;
        return val < limit;
    };
    int times3 = countOccurences(vec.begin(), vec.end(), lessThanLimit);
    std::cout << "the vector contains " << times3
              << " elements that are at less than 5" << std::endl;
    std::cout << "lessThanLimit called " << times_called
              << " times" << std::endl;

    // or just write it in the parameters
    int times4 = countOccurences(vec.begin(), vec.end(),
                                 [limit](auto val) { return val > limit; });
    std::cout << "the vector contains " << times4
              << " elements that are at greater than 5" << std::endl;
    return 0;
}



