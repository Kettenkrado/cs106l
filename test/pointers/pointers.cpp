#include <iostream>
#include <sstream>

using namespace std;

int main() {
    auto ptr1 = new std::pair<int, double>;
    auto ptr2 = new std::pair<int, double> { 106, 3.14 };
    auto ptr3 = new std::pair<int, double>();

    cout << ptr1->first << ' ' << ptr1->second << endl;
    cout << ptr2->first << ' ' << ptr2->second << endl;
    cout << ptr3->first << ' ' << ptr3->second << endl;

    delete ptr1; delete ptr2; delete ptr3;

    int* int_ptr = new int[100]();
    double* double_ptr = new double[5]{ 1, 2, 3, 4, 5 };

    for (int i = 0; i < 100; ++i) 
        cout << int_ptr[i] << ' ';
    cout << endl;

    for (int i = 0; i < 5; ++i) 
        cout << double_ptr[i] << ' ';
    cout << endl;

    delete int_ptr; delete double_ptr;

    double pi = 3.14;
    double e = 2.72;

    // We can rebind pointers, changing what data they point to
    double* ptr = &pi;
    ptr = &e;
    cout << pi << ' ' << e << endl;

    // However, we cannot do the same with references
    double& ref = pi;
    ref = e;  // This line changed *pi*, not ref!
    cout << pi << ' ' << e << endl;

    return 0;
}